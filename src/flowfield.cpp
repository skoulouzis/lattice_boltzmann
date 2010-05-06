/***************************************************************************
 *   Copyright (C) 2007 by S. Koulouzis   *
 *   alogo@vaio-laptop   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "flowfield.h"

FlowField::FlowField(QWidget *parent): QWidget( parent, "FlowField", WDestructiveClose ){
   	
	workingDirectory = getcwd(NULL, 0); // or _getcwd

	strcat (workingDirectory,"/data");

	dataSetReader = vtkDataSetReader::New();
	polyDataMapper = vtkPolyDataMapper::New();
	dataSetMapper = vtkDataSetMapper::New();
	renderWindow = vtkRenderWindow::New();
	renderer = vtkRenderer::New();
	
	actor = vtkActor::New();
	streamtubeActor = vtkActor::New();
	streamlineActor = vtkActor::New();
	glyphActor = vtkActor::New();
	streamtubeActor2 = vtkActor::New();
	mixerActor = vtkActor::New();
	textActor = vtkTextActor::New();
	text3 = vtkTextActor::New();
	barActor = vtkScalarBarActor::New();
	
	maskPoints = vtkMaskPoints::New();

	odjectCenter = new double;
	streamLine = vtkStreamLine::New();
	
	point = vtkPointSource::New();
	rungeKutta4 = vtkRungeKutta4::New();
	contourFilter = vtkContourFilter::New();	
	actorCollection = vtkActorCollection::New();
	lookupTable  = vtkLookupTable::New();

	vectorNorm = vtkVectorNorm::New();

	glyph = vtkGlyph3D::New();
	
	theTerminalSpeed = 0.1;
	dataLoaded = false;
	theNumOfPoints = 150;
	
	theRatio = 300;
	
	text3->GetTextProperty()->ShadowOff();
	text3->GetTextProperty()->SetLineSpacing(1.0);
	text3->GetTextProperty()->SetFontSize(20);
	text3->SetDisplayPosition(850,700);//( 5,700);
	renderer->AddActor2D(text3);
	makeVtkWidget();
}


void FlowField::changeRenderWindow(int index){
	actorCollection->InitTraversal();
	for(int i=0;i<actorCollection->GetNumberOfItems();i++){
		renderer->RemoveActor(actorCollection->GetNextActor());
	}
	
	for(int i=0;i<renderer->GetActors()->GetNumberOfItems();i++ ){
		renderer->RemoveActor(renderer->GetActors()->GetNextActor());
	}
	
	renderer->GetActors()->RemoveAllItems();
	actorCollection->RemoveAllItems();
	renderWindow->RemoveRenderer(renderer);
	
	switch (index) {
		case 8:
			smrx();
			createText(5,700);
			srmxStreamlines();
			break;
		case 9:
			tornado();
			createText(5,700);
			srmxStreamlines();			
			break;
		case 10:
			carotid();
			carotidGlyphs();
			break;
	}
	
	renderWindow->AddRenderer(renderer);
	renderWindow->Render();
	 
	actorCollection->InitTraversal();
}

void FlowField::makeVtkWidget(){
 
	 vtkWidget = new QVTKWidget(this);
	 vtkWidget->SetRenderWindow(renderWindow);
	
	 QVBoxLayout *optionsFormLayout = new QVBoxLayout( this, 1, 1 );
	 
	 QHBoxLayout *chartTypeLayout = new QHBoxLayout( 0, 0, 1 );

	 chartTypeLayout->addWidget( vtkWidget );	 
	 optionsFormLayout->addLayout( chartTypeLayout );
 }
 
 void FlowField::carotid(){
	 renderer->Delete();
	 renderer = vtkRenderer::New();

	char temp[180];
// 	temp = new char[100];
// 	temp2 = strcat(temp,"/carotid-bifurcation.7800.vtk");
	sprintf(temp,"%s/carotid-bifurcation.7800.vtk",workingDirectory);
	extractData(temp,0.2,true);
	
	 if(!dataLoaded){
		char path[180];
// 		path = new char[100];
		dataSetCollection = vtkDataSetCollection::New();
		
		for(int i=7800;i<8020;i=i+20){
// 			path = new char[100];
			sprintf(path,"%s/carotid-bifurcation.%d.vtk",workingDirectory,i);
// 			sprintf(path,"/carotid-bifurcation.%d.vtk",i);
			getDataSet(path);
			dataSetCollection->AddItem(dataSetReader->GetOutput());
		}
	 	dataLoaded = true;
	 }
 }

 void FlowField::tornado(){
	renderer->Delete();
	renderer = vtkRenderer::New();
	char  temp[80];
	sprintf(temp,"%s/tornado.vtk",workingDirectory);
	extractData(temp,1,false);
// 	extractData("/home/stud/scivis/uvadata/tornado.vtk",1,false);
	scalarRange[1] = 25;
 }
 
 void FlowField::smrx(){
	 renderer->Delete();
	 renderer = vtkRenderer::New();
	char  temp[80];
	sprintf(temp,"%s/SMRX.vtk",workingDirectory);
// 	 extractData("/home/stud/scivis/uvadata/SMRX.vtk",1,false);
	extractData(temp,1,false);
 }
  
 void FlowField::counstuctPoints(int numOfPoints, double centerY, double centerZ,double radius){
	 point->Delete();
	 point = vtkPointSource::New();
	 point->SetNumberOfPoints(numOfPoints);
	 point->SetRadius(radius);
	 point->SetCenter(odjectDimentions[0], centerY , centerZ);
	 point->SetDistributionToUniform();
 }
 
 vtkStreamLine* FlowField::counstuctStreamLine(){
	 vtkStreamLine *aStreamLine = vtkStreamLine::New();
	 aStreamLine->SetIntegrator(rungeKutta4);
	 aStreamLine->SetSource(point->GetOutput());
	 aStreamLine->SetStepLength(1.0);
	 aStreamLine->SetNumberOfThreads(2);
	 aStreamLine->SetIntegrationStepLength(2.0);
	 aStreamLine->SetIntegrationDirectionToIntegrateBothDirections();
	 aStreamLine->SetMaximumPropagationTime(300);
	 aStreamLine->SetTerminalSpeed(0.1);
	 aStreamLine->SpeedScalarsOn();
	 aStreamLine->SetInput(dataSetReader->GetOutput());
	 return aStreamLine;
 }
 
//  void FlowField::streamlines(){
// 
// 	 counstuctPoints(theNumOfPoints,odjectCenter[1] , odjectCenter[2],odjectDimentions[3] / 2);
// 	 // 	 
// // 	 counstuctStreamLines();
// 	 
// 	 streamLine->Delete();
// 	 streamLine = counstuctStreamLine();
// 
// 	 polyDataMapper->Delete();
// 	 polyDataMapper = vtkPolyDataMapper::New(); 
// 	 polyDataMapper->SetInputConnection(streamLine->GetOutputPort());
// 	 polyDataMapper->SetScalarRange(scalarRange);
// 	 polyDataMapper->SetScalarModeToUsePointData();
// 	 polyDataMapper->SetScalarRange(scalarRange[0], scalarRange[1]);
// 	 polyDataMapper->ScalarVisibilityOn();
// 	 
// 	 renderer->RemoveActor(streamtubeActor);
// 	 streamlineActor->Delete();
// 	 streamlineActor = vtkActor::New();
// 	 streamlineActor->SetMapper(polyDataMapper);
// 	 actorCollection->AddItem(streamlineActor);
// 	 renderer->AddActor(streamlineActor);
// // 	 createText();
// 	 createColorBar(polyDataMapper->GetLookupTable());
//  }
 
 void FlowField::createTubeFilter(int NumOfSodes, vtkStreamLine *streamLine){
	 tubeFilter = vtkTubeFilter::New();
	 tubeFilter->SetInput(streamLine->GetOutput());
	 tubeFilter->SetVaryRadiusToVaryRadiusByVector();
	 tubeFilter->SetNumberOfSides(NumOfSodes);
 }
 
 void FlowField::streamtubes(){
	 streamtubeActor2->VisibilityOff();
	 if(theSelection==9){
		 counstuctPoints(20,odjectCenter[1] , odjectCenter[2],odjectDimentions[3] / 2);
	 }else{
		 counstuctPoints(theNumOfPoints,odjectCenter[1] , odjectCenter[2],odjectDimentions[3] / 2);
	 }
	 
// 	 counstuctStreamLines();
	 
	 streamLine = counstuctStreamLine();

	 createTubeFilter(4,streamLine);
	 
	 polyDataMapper->Delete();
	 polyDataMapper = vtkPolyDataMapper::New(); 
	 polyDataMapper->SetInputConnection(tubeFilter->GetOutputPort());
	 polyDataMapper->SetScalarRange(scalarRange);
	 polyDataMapper->SetScalarModeToUsePointData();
	 polyDataMapper->SetScalarRange(scalarRange[0], scalarRange[1]);
	 polyDataMapper->ScalarVisibilityOn();
	 
	 renderer->RemoveActor(streamtubeActor);
	 streamtubeActor->Delete();
	 streamtubeActor = vtkActor::New();
	 streamtubeActor->SetMapper(polyDataMapper);
	 actorCollection->AddItem(streamtubeActor);
	 renderer->AddActor(streamtubeActor);

	 createColorBar(polyDataMapper->GetLookupTable());
 }
 
 void FlowField::mixingStreamLines(){
	 counstuctPoints(theNumOfPoints/2,odjectDimentions[2]+50, odjectCenter[2],odjectDimentions[3] / 2.5);

	 streamLine = counstuctStreamLine();
	 createTubeFilter(4,streamLine);

	 lookupTable = vtkLookupTable::New();
	 lookupTable->SetNumberOfColors(1);
	 lookupTable->SetHueRange(0.0, 0.0);
	 lookupTable->SetSaturationRange(1.0, 1.0);
	 lookupTable->Build();
	 
	 polyDataMapper->Delete();
	 polyDataMapper = vtkPolyDataMapper::New(); 
	 polyDataMapper->SetInputConnection(streamLine->GetOutputPort());
	 polyDataMapper->SetScalarRange(scalarRange);
	 polyDataMapper->SetScalarModeToUsePointData();
	 polyDataMapper->SetScalarRange(scalarRange[0], scalarRange[1]);
	 polyDataMapper->ScalarVisibilityOn();
	 polyDataMapper->SetLookupTable(lookupTable);
	 
	 renderer->RemoveActor(streamtubeActor);
	 streamtubeActor->Delete();
	 streamtubeActor = vtkActor::New();
	 streamtubeActor->SetMapper(polyDataMapper);
	 actorCollection->AddItem(streamtubeActor);
	 renderer->AddActor(streamtubeActor);
	 
	 counstuctPoints(theNumOfPoints/2,odjectDimentions[3]-50, odjectCenter[2],odjectDimentions[3] / 2.5);
	 streamLine2 = counstuctStreamLine();
	 createTubeFilter(4,streamLine2);

	 lookupTable->Delete();
	 lookupTable = vtkLookupTable::New();
	 lookupTable->SetNumberOfColors(1);
	 lookupTable->SetHueRange(0.667, 0.667);
	 lookupTable->SetSaturationRange(1.0, 1.0);
	 lookupTable->Build();
	 
	 polyDataMapper->Delete();
	 polyDataMapper = vtkPolyDataMapper::New(); 
	 polyDataMapper->SetInputConnection(streamLine2->GetOutputPort());
	 polyDataMapper->SetScalarRange(scalarRange);
	 polyDataMapper->SetScalarModeToUsePointData();
	 polyDataMapper->SetScalarRange(scalarRange[0], scalarRange[1]);
	 polyDataMapper->ScalarVisibilityOn();
	 polyDataMapper->SetLookupTable(lookupTable);
	 
	 // 	
	 renderer->RemoveActor( streamtubeActor2 );
	 
	
	 
	 streamtubeActor2->Delete();
	 streamtubeActor2 = vtkActor::New();
// 	 streamtubeActor2->VisibilityOf();
	 streamtubeActor2->SetMapper(polyDataMapper);
	 actorCollection->AddItem(streamtubeActor2);
	 renderer->AddActor(streamtubeActor2);

	 renderer->RemoveActor(barActor);
 
 }
 
 void FlowField::mixingStreamTubes(){
	 counstuctPoints(theNumOfPoints/2,odjectDimentions[2]+50, odjectCenter[2],odjectDimentions[3] / 2.5);

	 streamLine = counstuctStreamLine();
	 createTubeFilter(4,streamLine);

	 lookupTable = vtkLookupTable::New();
	 lookupTable->SetNumberOfColors(1);
	 lookupTable->SetHueRange(0.0, 0.0);
	 lookupTable->SetSaturationRange(1.0, 1.0);
	 lookupTable->Build();
	 
	 polyDataMapper->Delete();
	 polyDataMapper = vtkPolyDataMapper::New(); 
	 polyDataMapper->SetInputConnection(tubeFilter->GetOutputPort());
	 polyDataMapper->SetScalarRange(scalarRange);
	 polyDataMapper->SetScalarModeToUsePointData();
	 polyDataMapper->SetScalarRange(scalarRange[0], scalarRange[1]);
	 polyDataMapper->ScalarVisibilityOn();
	 polyDataMapper->SetLookupTable(lookupTable);
	 
	 renderer->RemoveActor(streamtubeActor);
	 streamtubeActor->Delete();
	 streamtubeActor = vtkActor::New();
	 streamtubeActor->SetMapper(polyDataMapper);
	 actorCollection->AddItem(streamtubeActor);
	 renderer->AddActor(streamtubeActor);
	 
	 counstuctPoints(theNumOfPoints/2,odjectDimentions[3]-50, odjectCenter[2],odjectDimentions[3] / 2.5);
	 streamLine2 = counstuctStreamLine();
	 createTubeFilter(4,streamLine2);

	 lookupTable->Delete();
	 lookupTable = vtkLookupTable::New();
	 lookupTable->SetNumberOfColors(1);
	 lookupTable->SetHueRange(0.667, 0.667);
	 lookupTable->SetSaturationRange(1.0, 1.0);
	 lookupTable->Build();
	 
	 polyDataMapper->Delete();
	 polyDataMapper = vtkPolyDataMapper::New(); 
	 polyDataMapper->SetInputConnection(tubeFilter->GetOutputPort());
	 polyDataMapper->SetScalarRange(scalarRange);
	 polyDataMapper->SetScalarModeToUsePointData();
	 polyDataMapper->SetScalarRange(scalarRange[0], scalarRange[1]);
	 polyDataMapper->ScalarVisibilityOn();
	 polyDataMapper->SetLookupTable(lookupTable);
	 
	 // 	
	 renderer->RemoveActor( streamtubeActor2 );
	 
	
	 
	 streamtubeActor2->Delete();
	 streamtubeActor2 = vtkActor::New();
// 	 streamtubeActor2->VisibilityOf();
	 streamtubeActor2->SetMapper(polyDataMapper);
	 actorCollection->AddItem(streamtubeActor2);
	 renderer->AddActor(streamtubeActor2);

	 renderer->RemoveActor(barActor);
// 	 createColorBar();

 }
 
 void FlowField::srmxglyphs(){
	 
	 vtkConeSource *cone = vtkConeSource::New();
	 cone->SetHeight(2);
	 cone->SetResolution( 20 );
	 cone->SetRadius(0.9);
	 
// 	 glyphs(dataSetReader->GetOutputPort(),cone->GetOutputPort(),true,0.5 );
	glyphs(dataSetReader->GetOutputPort(),cone->GetOutput(),true,0.5 );
 }
 
 void FlowField::tornadoGlyphs(){
	 streamtubeActor2->VisibilityOff();
	 
	 vtkArrowSource *arrow = vtkArrowSource::New();
	 
// 	 glyphs(dataSetReader->GetOutputPort(),arrow->GetOutputPort(),true,0.2);
         glyphs(dataSetReader->GetOutputPort(),arrow->GetOutput(),true,0.2);
 }
 
 void FlowField::carotidGlyphs(){
	 vtkVectorNorm *vectorNorm = vtkVectorNorm::New();
	 vectorNorm->NormalizeOn();
	 vectorNorm->SetInputConnection(dataSetReader->GetOutputPort());
	
	 
	 switch(theControlSelection){
		 case 0:
		 {
			 vtkArrowSource *source = vtkArrowSource::New();
// 			 glyphs(vectorNorm->GetOutputPort(),source->GetOutputPort(),false,10);
			 glyphs(vectorNorm->GetOutputPort(),source->GetOutput(),false,10);
		 }
			 break;

		 case 1:
		 {
			 vtkConeSource *source = vtkConeSource::New();
			 source->SetHeight( 0.5 );
			 source->SetRadius( 0.2 );
			 source->SetResolution( 8 );
// 			 glyphs(vectorNorm->GetOutputPort(),source->GetOutputPort(),false,10);
			 glyphs(vectorNorm->GetOutputPort(),source->GetOutput(),false,10);
		 }
			 break;
		 case 2:
		 {
			 vtkLineSource *source = vtkLineSource::New();
// 			 glyphs(vectorNorm->GetOutputPort(),source->GetOutputPort(),false,10);
			 glyphs(vectorNorm->GetOutputPort(),source->GetOutput(),false,10);
		 }
			 break;
	 }
	 
// 	 vtkArrowSource *arrow = vtkArrowSource::New();
	 
// 	 glyphs(vectorNorm->GetOutputPort(),arrow->GetOutputPort(),false,10);
 }
 
 void FlowField::carotidGlyphs(vtkDataSet *dataSet,vtkPolyData *aSource){
	 vtkVectorNorm *vectorNorm = vtkVectorNorm::New();
	 vectorNorm->NormalizeOn();
	 vectorNorm->SetInput(dataSet);
	 glyphs(vectorNorm->GetOutputPort(),aSource,false,10);
 }
 
 void FlowField::render(){
	 counstuctFluidVisulization();
	 switch (theSelection) {
		 case 8:
			 renderSRMX();
			 break;
		 case 9:
			 renderTorado();
			 break;
		 case 10:
			 renderCarotid();
			 break;
	 }
	 
 }
 
 
 void FlowField::ribbon(){
	 streamtubeActor2->VisibilityOff();
	 maskPoints->Delete();
	 maskPoints = vtkMaskPoints::New();
	 maskPoints->SetOnRatio(theRatio);
	 maskPoints->RandomModeOn();
	 maskPoints->SetInputConnection(dataSetReader->GetOutputPort());
	 
	 vtkRungeKutta4 *rk4 = vtkRungeKutta4::New();
	
	 streamLine->Delete();
	 streamLine = vtkStreamLine::New();
	 streamLine->SetInputConnection(dataSetReader->GetOutputPort());
	 streamLine->SetSource(maskPoints->GetOutput());
	 streamLine->SetMaximumPropagationTime(300);
	 streamLine->SetIntegrationStepLength(2);
	 streamLine->SetStepLength(.01);
	 streamLine->SetNumberOfThreads(2);
	 streamLine->SetIntegrationDirectionToIntegrateBothDirections();
	 streamLine->VorticityOn();
	 streamLine->SpeedScalarsOn();
	
	 streamLine->SetIntegrator(rk4);
	
	 vtkRibbonFilter *rf = vtkRibbonFilter::New();
	 rf->SetInputConnection(streamLine->GetOutputPort());
	 rf->SetWidth(0.2);
	 rf->SetWidthFactor(5);
	
	 polyDataMapper->Delete();
	 polyDataMapper = vtkPolyDataMapper::New();
	 polyDataMapper->SetInputConnection(rf->GetOutputPort());
// 	streamMapper->SetScalarRange(scalarRange);
	 polyDataMapper->SetScalarModeToUsePointData();
	 polyDataMapper->SetScalarRange(scalarRange[0], scalarRange[1]);
	 polyDataMapper->ScalarVisibilityOn();
	
	 streamlineActor->Delete();
	 streamlineActor = vtkActor::New();
// 	 streamline->GetProperty()->SetOpacity(0.1);
	 streamlineActor->SetMapper(polyDataMapper);
// 	streamline->VisibilityOff();
	
	 renderer->AddActor(streamlineActor);
	 
	 createColorBar(polyDataMapper->GetLookupTable());
// 	renderer->AddActor(streamline2);
 
 }
 
 void FlowField::setSelection(int selection){
	 theSelection = selection;
 }
 
 void FlowField::createText(int x,int y){
	 renderer->RemoveActor2D(textActor);
	 textActor->Delete();
	 textActor = vtkTextActor::New();
	 textActor->GetTextProperty()->ShadowOff();
	 textActor->GetTextProperty()->SetLineSpacing(1.0);
	 textActor->GetTextProperty()->SetFontSize(20);
	 textActor->SetDisplayPosition(x,y);//( 5,700);
	 renderer->AddActor2D(textActor);
 }
 
 void FlowField::toggleActor(){
// 	 actorCollection->InitTraversal();
// 	 actor = actorCollection->GetNextActor();
	 if(mixerActor->GetVisibility()){
		 mixerActor->VisibilityOff();
	 }else{
		 mixerActor->VisibilityOn();
	 }
	 renderWindow->Render();
 }
 
 void FlowField::createColorBar(vtkScalarsToColors *lookupTable){
	 renderer->RemoveActor2D(barActor);
	 barActor->Delete();
	 barActor = vtkScalarBarActor::New();
	 barActor->SetOrientationToHorizontal();
	 barActor->GetPositionCoordinate()->SetValue(0.1, 0.01);
	 barActor->SetTitle("Vector field velocity");
	 barActor->SetWidth(0.8);
	 barActor->SetHeight(0.07);
	 barActor->SetLookupTable(lookupTable);
	 renderer->AddActor2D(barActor);
 }
 
 void FlowField::counstuctFluidVisulization(){
	 actorCollection->RemoveItem(streamlineActor);
	 renderer->RemoveActor(streamlineActor);
	 renderer->RemoveActor(streamtubeActor);
	 renderer->RemoveActor(streamtubeActor2);
	 renderer->RemoveActor(streamlineActor);
	 
	 renderer->RemoveActor( glyphActor );
	 renderer->ResetCamera();
	 if(theSelection==8){
		switch(theControlSelection){
			case 0:
				srmxStreamlines();
				break;
			case 1:
				streamtubes();
				break;
			case 2:
				mixingStreamTubes();
				break;
			case 3:
				mixingStreamLines();
				break;
			case 4:
				srmxglyphs();
				break;
		}
	 }else if(theSelection==9){
		 switch(theControlSelection){
			 case 0:
				 srmxStreamlines();
				 break;
			 case 1:
				 streamtubes();
				 break;
			 case 2:
				 tornadoGlyphs();
				 break;
			 case 3:
				 ribbon();
				 break;
		 }
	 
	 }else if(theSelection==10){
		 carotidGlyphs();

	 }
	actorCollection->RemoveAllItems();
 }
 
 void FlowField::setControlSelection(int selection){
	 theControlSelection = selection;
 }
 
 void FlowField::setTerminalSpeed(int integer,int decimal){
	 theTerminalSpeed = integer + (decimal/10.0);
	 
	 if(theTerminalSpeed <= 0.0){
		 theTerminalSpeed = 0.1;
	 }
	 char text[30];
	 sprintf(text,"Terminal Speed: %g",theTerminalSpeed);
	 
	 textActor->SetInput(text); 
 }
 
 void FlowField::setNumOfPoins(int numOfPoints){
	 theNumOfPoints = numOfPoints;
 }

 void  FlowField::renderSRMX(){
// 	 if(theControlSelection >= 0 && theControlSelection <=1){
// 		 char text[30];
// 		int maxPropTime;
// 		maxPropTime = 150;
// 		if(theTerminalSpeed == 0.0 ){
// 			maxPropTime = 80;
// 		}
// 		streamLine->SetTerminalSpeed(theTerminalSpeed);
// 		streamLine->SetMaximumPropagationTime(0);
// 		for(int i=0;i<maxPropTime;i=i++){
// 			if(i>= maxPropTime / 2 ){
// 				i+=1;
// 			}
// 			streamLine->SetMaximumPropagationTime(i);
// 			sprintf(text,"Propagation Time: %d",i);
// 			textActor->SetInput(text);
// 			renderWindow->Render();
// 		}
// 	 }
// 	 if(theControlSelection >= 2  && theControlSelection <= 3){
// 		 char text[30];
// 		 int maxPropTime;
// 		 maxPropTime = 150;
// 		 if(theTerminalSpeed == 0.0 ){
// 			 maxPropTime = 80;
// 		 }
// 		 streamLine->SetTerminalSpeed(theTerminalSpeed);
// 		 streamLine2->SetTerminalSpeed(theTerminalSpeed);
// 		 streamLine->SetMaximumPropagationTime(0);
// 		streamLine2->SetMaximumPropagationTime(0);
// 		 for(int i=0;i<maxPropTime;i=i++){
// 			 if(i>= maxPropTime / 2 ){
// 				 i+=1;
// 			 }
// 			streamLine->SetMaximumPropagationTime(i);
// 			streamLine2->SetMaximumPropagationTime(i);
// 			 sprintf(text,"Propagation Time: %d",i);
// 			 textActor->SetInput(text);
// 			 renderWindow->Render();
// 		 } 
	 
// 	 }
// 	 if(theControlSelection == 4){
// 		 renderWindow->Render();
// 	 }
	 renderWindow->Render();
	 actorCollection->InitTraversal();
	 for(int i=0;i<actorCollection->GetNumberOfItems();i++){
		 renderer->RemoveActor(actorCollection->GetNextActor());
	 }
 
 }
 
 void FlowField::renderCarotid(){

	
	 dataSetCollection->InitTraversal();
	 for(int i=0;i< dataSetCollection->GetNumberOfItems();i++){
		 carotidGlyphs();
// 		 carotidGlyphs(dataSetCollection->GetNextItem(),arrow->GetOutputPort());
		 renderWindow->Render();
	 }

 }
 
 void FlowField::renderTorado(){
	renderWindow->Render();
 }
 
 void FlowField::setMaskPointRatio(int ratio){
	 theRatio = ratio;
 }

 void FlowField::glyphs(vtkAlgorithmOutput *input,vtkPolyData *source,bool vectorMode,double scaleFactor){
	 maskPoints->Delete();
	 maskPoints = vtkMaskPoints::New();
	 maskPoints->SetOnRatio(theRatio);
	 maskPoints->RandomModeOn();
	 maskPoints->SetInputConnection(input);
	 
	 glyph->Delete();
	 glyph = vtkGlyph3D::New();
	 glyph->SetInputConnection(maskPoints->GetOutputPort());
	 glyph->SetScaleFactor(scaleFactor);	 

	 glyph->SetSource(source);
// 	 glyph->SetSourceConnection(source);
	 
	 
	 if(vectorMode){
		 glyph->SetVectorModeToUseVector();
		 glyph->SetColorModeToColorByVector();
		 glyph->SetScaleModeToScaleByVector();
		 glyph->SetIndexModeToVector();
	 }

	 polyDataMapper->Delete();
	 polyDataMapper = vtkPolyDataMapper::New();
	 polyDataMapper->SetInputConnection(glyph->GetOutputPort());
	 polyDataMapper->SetScalarModeToUsePointData();
	 polyDataMapper->SetScalarRange(scalarRange[0], scalarRange[1]);
	 polyDataMapper->ScalarVisibilityOn();
	 
	 
	 renderer->RemoveActor(glyphActor);
	 glyphActor->Delete();
	 glyphActor = vtkActor::New();	 
	 glyphActor->SetMapper(polyDataMapper);
// 	 actorCollection->AddItem(glyphActor);
	 
	 renderer->AddActor(glyphActor);
 }
 
 void FlowField::extractData(char *path,double opacity,bool norm){

	 getDataSet(path);
	  
	  lookupTable->Delete();
	  lookupTable  = vtkLookupTable::New();
	  lookupTable->SetNumberOfColors(1);
	  lookupTable->SetSaturationRange(0, 0.1);
	  lookupTable->Build();
	 
	  polyDataMapper->Delete();
	  polyDataMapper = vtkPolyDataMapper::New();
	  polyDataMapper->SetLookupTable(lookupTable);
	  
	  if(norm){
		  vectorNorm->Delete();
		  vectorNorm = vtkVectorNorm::New();
		  vectorNorm->NormalizeOn();
		  vectorNorm->SetInputConnection(dataSetReader->GetOutputPort());
	 
		  contourFilter->Delete();
		  contourFilter = vtkContourFilter::New();
		  contourFilter->SetValue(0,0.01);
		  contourFilter->SetInput(vectorNorm->GetOutput());
	 
		  polyDataMapper->SetInputConnection(contourFilter->GetOutputPort());
		  polyDataMapper->ScalarVisibilityOn();
		  polyDataMapper->SetScalarModeToUsePointData();
	  }else{
		  contourFilter->Delete();
		  contourFilter = vtkContourFilter::New();
		  contourFilter->SetValue(0,0.1);
		  contourFilter->SetInput(dataSetReader->GetOutput());
	 
		  polyDataMapper->SetInputConnection(contourFilter->GetOutputPort());
		  polyDataMapper->ScalarVisibilityOn();
		  polyDataMapper->SetScalarModeToUsePointData();
	  
	  }

	 
	  renderer->RemoveActor(mixerActor);
	  mixerActor->Delete();
	  mixerActor = vtkActor::New();
	  mixerActor->SetMapper(polyDataMapper);
	  mixerActor->GetProperty()->SetOpacity(opacity);
	  renderer->AddActor(mixerActor);

	  odjectDimentions = dataSetReader->GetOutput()->GetBounds();
	  odjectCenter = dataSetReader->GetOutput()->GetCenter();
	  scalarRange = dataSetReader->GetOutput()->GetScalarRange();
	
// -------------------------------	 
// --------------- Outline-----------

	  vtkOutlineCornerFilter *outlineCornerFilter = vtkOutlineCornerFilter::New();
	  outlineCornerFilter->SetInput(dataSetReader->GetOutput());
	  outlineCornerFilter->SetCornerFactor(0.3);
			 
	  polyDataMapper->Delete();
	  polyDataMapper = vtkPolyDataMapper::New();
	  polyDataMapper->SetInput(outlineCornerFilter->GetOutput());
	 
	  renderer->RemoveActor(actor);
	  actor->Delete();
	  actor = vtkActor::New();
	  actor->SetMapper(polyDataMapper);
// 	  actorCollection->AddItem(actor);
	  renderer->AddActor(actor);
	  renderer->SetBackground(0, 0, 0.2);
  }
  
  void FlowField::getDataSet(char *path){
	  dataSetReader->Delete();
	  dataSetReader = vtkDataSetReader::New();
	  dataSetReader->SetFileName(path);
	  dataSetReader->Update();
  }
  
  void FlowField::streamlines(vtkPolyData *source,vtkAlgorithmOutput *input){


			
	streamLine = vtkStreamLine::New();
	streamLine->SetIntegrator(rungeKutta4);
	streamLine->SetSource(source);
	streamLine->SetStepLength(1.0);
	streamLine->SetNumberOfThreads(2);
	streamLine->SetIntegrationStepLength(2.0);
	streamLine->SetIntegrationDirectionToIntegrateBothDirections();
	streamLine->SetMaximumPropagationTime(300);
	streamLine->SetTerminalSpeed(0.1);
	streamLine->SpeedScalarsOn();
	streamLine->SetInputConnection(input);
	

	  polyDataMapper->Delete();
	  polyDataMapper = vtkPolyDataMapper::New(); 
	  polyDataMapper->SetInputConnection(streamLine->GetOutputPort());
	  polyDataMapper->SetScalarRange(scalarRange);
	  polyDataMapper->SetScalarModeToUsePointData();
	  polyDataMapper->SetScalarRange(scalarRange[0], scalarRange[1]);
	  polyDataMapper->ScalarVisibilityOn();
	 
	  renderer->RemoveActor(streamtubeActor);
	  streamlineActor->Delete();
	  streamlineActor = vtkActor::New();
	  streamlineActor->SetMapper(polyDataMapper);
	  actorCollection->AddItem(streamlineActor);
	  renderer->AddActor(streamlineActor);
// 	 createText();
	  createColorBar(polyDataMapper->GetLookupTable());
  }
  
  void FlowField::srmxStreamlines(){
	  point->Delete();
	  point = vtkPointSource::New();
	  point->SetNumberOfPoints(theNumOfPoints);
	  point->SetRadius(odjectDimentions[3] / 2);
	  point->SetCenter(odjectDimentions[0], odjectCenter[1] , odjectCenter[2]);
	  point->SetDistributionToUniform();		
	  
	  streamlines(point->GetOutput(),dataSetReader->GetOutputPort());
	  
  }
  
   
  
