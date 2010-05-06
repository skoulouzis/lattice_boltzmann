/***************************************************************************
 *   Copyright (C) 2007 by S. Koulouzis,,,   *
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
#include "vtk.h"

VTK::VTK(QWidget *parent): QWidget( parent, "VTK", WDestructiveClose ){
// 	theSelection = selection;

	workingDirectory = getcwd(NULL, 0); // or _getcwd

	strcat (workingDirectory,"/data");

	isExapleCreated = false;
	renderWindow = vtkRenderWindow::New();
	renderer = vtkRenderer::New();
	
	actorCollection = vtkActorCollection::New();
	makeVtkWidget();
}

void VTK::setSelection(int selection){
	theSelection = selection;
}

void VTK::cone(int numOfCones){
	NumOfActors = numOfCones;
	polyDataMapper = vtkPolyDataMapper::New();
	
	renderer->Delete();
	renderer = vtkRenderer::New();
	renderer->SetBackground( 0.1, 0.2, 0.4 );
		
	coneSource = vtkConeSource::New();
	coneSource->SetHeight( 3.0 );
	coneSource->SetRadius( 1.0 );
	coneSource->SetResolution( 20 );
		
	polyDataMapper->SetInputConnection(coneSource->GetOutputPort());
	
	for(int i=0;i<NumOfActors;i++){
		actor = vtkActor::New();
		actor->SetMapper(polyDataMapper);
		actor->SetPosition(i,i,0);
		renderer->AddActor(actor);
		actorCollection->AddItem(actor);
	}
	coneSource->Delete();
	deleteObjects();
}

void VTK::cube(){

	cubeSource = vtkCubeSource::New();
	 
	polyDataMapper = vtkPolyDataMapper::New();
	polyDataMapper->SetInputConnection(cubeSource->GetOutputPort());
	
	actor= vtkActor::New();
	actor->SetMapper(polyDataMapper);
		
	renderer->Delete();
	renderer = vtkRenderer::New();
	
	renderer->AddActor(actor);
	actorCollection->AddItem(actor);
	renderer->SetBackground( 0.1, 0.2, 0.4 );

	
	cubeSource->Delete();
	deleteObjects();

}

void VTK::sphere(int startTheta){
	sphereSource = vtkSphereSource::New();
	sphereSource->SetThetaResolution(10);
	sphereSource->SetPhiResolution(10);
	sphereSource->SetRadius( 1.0 );
	sphereSource->SetStartTheta(startTheta);  
	
	polyDataMapper = vtkPolyDataMapper::New();
	polyDataMapper->SetInputConnection(sphereSource->GetOutputPort());
	
	
	actor= vtkActor::New();
	actor->SetMapper(polyDataMapper);

	renderer->Delete();
	renderer = vtkRenderer::New();
	
	renderer->AddActor(actor);
	actorCollection->AddItem(actor);
	
	renderer->SetBackground( 0.1, 0.2, 0.4 );
	
// 	sphereSource->Delete();
	deleteObjects();
}

void VTK::vetkText(){
	vectorText = vtkVectorText::New();
	vectorText->SetText("vtkVectorText");
	
	vtkLinearExtrusionFilter* extrude = vtkLinearExtrusionFilter::New();
	extrude->SetInputConnection( vectorText->GetOutputPort());
	extrude->SetExtrusionTypeToNormalExtrusion();
	extrude->SetVector(0, 0, 1 );
	extrude->SetScaleFactor (0.5);
	
	
	polyDataMapper = vtkPolyDataMapper::New();
	polyDataMapper->SetInputConnection( extrude->GetOutputPort());
		
	actor = vtkActor::New();
	actor->SetMapper(polyDataMapper);
		
	renderer->Delete();
	renderer = vtkRenderer::New();
	
	renderer->AddActor(actor);
	actorCollection->AddItem(actor);
	renderer->SetBackground( 0.1, 0.2, 0.4 );

	deleteObjects();
	
}

void VTK::enterprise(){
	vtkOBJReader *objecReader = vtkOBJReader::New();

	char temp[80];
	sprintf(temp,"%s/ncc1701b.obj",workingDirectory);
// 	objecReader->SetFileName("/home/alogo/workspace/qtExample2/data/ncc1701b.obj");
	objecReader->SetFileName(temp);
	
	polyDataMapper = vtkPolyDataMapper::New();
	polyDataMapper->SetInput(objecReader->GetOutput());
	
	enterpriseActor= vtkActor::New();
	enterpriseActor->SetMapper(polyDataMapper);
	
	if(theSelection!=7){
		renderer->Delete();
		renderer = vtkRenderer::New();
	}

	renderer->AddActor(enterpriseActor);
	actorCollection->AddItem(enterpriseActor);
	
	if(theSelection!=7){
		actorCollection->InitTraversal();
		actorCollection->GetNextActor()->SetOrientation(265,0,0);
		renderer->SetBackground( 0.1, 0.2, 0.4 );
	}
	//-----------------------------------------------------------------
	// Creating an interactor with qt 3.3 the user logs out!!!!!!!!!!! Probably the Xserver is restarting
// 	vtkRenderWindowInteractor* iren = vtkRenderWindowInteractor::New();
// 	renderWindow->SetInteractor( iren );
	//-----------------------------------------------------------------

	objecReader->Delete();
	enterpriseActor->Delete();
	deleteObjects();
}

void VTK::earth(){
	sphere(0);
	sphereSource->SetThetaResolution(25);
	sphereSource->SetPhiResolution(25);
	sphereSource->Delete();
	
	actorCollection->InitTraversal();
	actorCollection->GetNextActor()->GetProperty()->SetColor(0,0.3,0.7);
	
	earthSource = vtkEarthSource::New();
	
	polyDataMapper = vtkPolyDataMapper::New();
	polyDataMapper->SetInputConnection(earthSource->GetOutputPort());
		
	actor = vtkActor::New();
	actor->SetMapper(polyDataMapper);
	
	renderer->AddActor(actor);
	actorCollection->AddItem(actor);
	renderer->SetBackground( 0.1, 0.2, 0.4 );
	
	earthSource->Delete();
	deleteObjects();
}

void VTK::moon(){
	sphereSource = vtkSphereSource::New();
	sphereSource->SetThetaResolution(25);
	sphereSource->SetPhiResolution(25);
	sphereSource->SetRadius( 1.0 );
	
	polyDataMapper = vtkPolyDataMapper::New();
	polyDataMapper->SetInputConnection(sphereSource->GetOutputPort());
	
	
	actor= vtkActor::New();
	actor->SetMapper(polyDataMapper);
	
	renderer->AddActor(actor);
	actorCollection->AddItem(actor);
}

void VTK::stars(){
	point = vtkPointSource::New();
	point->SetNumberOfPoints(1500);
	point->SetRadius(200);
	point->SetDistributionToShell();
	 
	polyDataMapper = vtkPolyDataMapper::New();
	polyDataMapper->SetInputConnection(point->GetOutputPort());
	 
	actor = vtkActor::New();
// 	actor->SetPosition(0,0,0);
	actor->SetMapper(polyDataMapper);
	 
	renderer->AddActor(actor);
	actor->Delete();
	point->Delete();
}

void VTK::erthAndEnterprise(){
	
	earth();
// 	moon();
	stars();
	enterprise();
	actorCollection->InitTraversal();
	for(int i=0;i<(actorCollection->GetNumberOfItems())-1;i++){
		actor = actorCollection->GetNextActor();
		actor->SetPosition(0,0,0);
		actor->SetOrigin(0,0,0);
		actor->SetOrientation(275,0,0);
		actor->SetScale(10);
	}
	actorCollection->InitTraversal();
	actor = actorCollection->GetLastActor();
	
	double enterpriseX;
	double enterpriseY;
	double enterpriseZ;
	
	enterpriseX=20;
	enterpriseY=0;
	enterpriseZ=0;
		
	actor->SetOrientation(270,0,0);
	actor->SetPosition(enterpriseX,enterpriseY,enterpriseZ);
	actor->SetOrigin(0,0,0);
// 	actor->SetPosition(3,5,0);
	actor->SetScale(0.25);
// 	actor->RotateZ(80);
	
	renderer->GetActiveCamera()->SetPosition(0,0,70);
	renderer->SetBackground( 0, 0, 0.1 );
}

void VTK::render(){
	switch (theSelection) {
		case 0:
			if(actorCollection->GetNumberOfItems()==1){
				for (int i = 0; i < 360; ++i){
				// render the image
					renderWindow->Render();
				// rotate the active camera by one degree
					renderer->GetActiveCamera()->Azimuth( 1 );
				}
			}
			break;
		//enterprise	
		case 6:
			actorCollection->InitTraversal();
			for (int i = 0; i < 360; ++i){
				actorCollection->GetLastActor()->RotateZ(1);
				renderWindow->Render();
// 				renderer->Render();
			}
			break;
			
		//enterprise-earth	
		case 7:
			actorCollection->InitTraversal();
			for(int j=0;j<2;j++){
				actor =  actorCollection->GetNextActor();
			}
			enterpriseActor = actorCollection->GetNextActor();
			double enterpriseX;
			double enterpriseY;
			double enterpriseZ;
			
			double cameraX;
			double cameraY;
			double cameraZ;
			
			double step;
			double angle;
			double rotation;
			
			enterpriseX=20;
			enterpriseY=0;
			enterpriseZ=0;
			
			cameraX = 0;
			cameraY = 0;
			cameraZ = 70;
					
			step = 0.015;
			rotation = step * 57;
			
			while(angle <= (M_PI*2.5) ){
				actor->RotateZ(0.2);
				enterpriseX = ((20.0) * cos(angle));
				enterpriseZ = ((20.0) * sin(angle));
				enterpriseActor->SetPosition(enterpriseX,enterpriseY,enterpriseZ);
				enterpriseActor->RotateZ(-rotation);
				renderWindow->Render();
				angle += step;
			}
			for (int i = 0; i < 200; ++i){
				actor->RotateZ(0.2);
				enterpriseX = enterpriseX - pow( 1, 10 );
				if(i <= 180){
					renderer->GetActiveCamera()->SetPosition(enterpriseX-7,enterpriseY,enterpriseZ);
				}
					enterpriseY = enterpriseY + 0.05;
					enterpriseZ = enterpriseZ - 0.07;
				enterpriseActor->SetPosition(enterpriseX,enterpriseY,enterpriseZ);
				renderWindow->Render();
			}
			break;
		default:
			renderWindow->Render();
			break;
	}

}


void VTK::deleteObjects(){
// 	if(theSelection !=6 ){
// 		actor->Delete();
// 	}else{
// 		enterpriseActor->Delete();
// 	}
// 	polyDataMapper->Delete();
}

 void VTK::setText(QString text){
	 if(theSelection==4){
	 	const char *c_str2 = text.latin1();
	 	vectorText->SetText(c_str2);
	 }
 }
 
 void VTK::alignmentChanged(int index){
	 actorCollection->InitTraversal();
	 actorCollection->GetNextActor()->GetProperty()->SetColor(0,0,1);
	 actorCollection->GetNextActor()->GetProperty()->SetColor(0,1,0);
	 actorCollection->GetNextActor()->GetProperty()->SetColor(1,0,0);
	 switch (index) {
		 //top-bottom
		 case 0:
			 actorCollection->InitTraversal();
			 for(int i=0;i<actorCollection->GetNumberOfItems();i++){
				 actorCollection->GetNextActor()->SetPosition((i*3),0,0);
			 }
			 break;
		//side to side
		 case 1:
			 actorCollection->InitTraversal();
			 for(int i=0;i<actorCollection->GetNumberOfItems();i++){
				 actorCollection->GetNextActor()->SetPosition(0,(i*2),0);
			 }
			 break;
	 }
	 this->renderer->ResetCamera();
 
 }
  
 void VTK::makeVtkWidget(){
 
	 vtkWidget = new QVTKWidget(this);
	 vtkWidget->SetRenderWindow(renderWindow);
	
	 QVBoxLayout *optionsFormLayout = new QVBoxLayout( this, 1, 1 );
	 
	 QHBoxLayout *chartTypeLayout = new QHBoxLayout( 0, 0, 1 );

// 	 The chart type label and combobox will be laid out side by side.
	 chartTypeLayout->addWidget( vtkWidget );	 
	 optionsFormLayout->addLayout( chartTypeLayout );
 }
 
 void VTK::changeRenderWindow(int index){

	 actorCollection->InitTraversal();
	 for(int i=0;i<actorCollection->GetNumberOfItems();i++){
		 renderer->RemoveActor(actorCollection->GetNextActor());
	 }
	 
	 renderer->GetActors()->RemoveAllItems();
	 actorCollection->RemoveAllItems();
	 renderWindow->RemoveRenderer(renderer);
	 
	 switch (index) {
		 case 0:
			 cone(1);
			 break;
		 case 1:
			 cube();
			 break;
		 case 2:
			 sphere(0);
			 break;
		 case 3:
			 sphere(60);
			 break;	
		 case 4:
			 vetkText();
			 break;	
		 case 5:
			 cone(3);
			 break;
		 case 6:
			 enterprise();
			 break;
		 case 7:
			 erthAndEnterprise();
			 break;
	 } 
// 	 renderer->ResetCamera();
	 renderWindow->AddRenderer(renderer);
	 renderWindow->Render();

	 
	 actorCollection->InitTraversal(); 
	 isExapleCreated = true;
 }
 
 VTK::~VTK(){
// 	 actor->Delete();
// 	 actorCollection->Delete();
// 	 coneSource->Delete();
// 	 cubeSource->Delete();
// 	 earthSource->Delete();
// 	 enterpriseActor->Delete();
// 	 polyDataMapper->Delete();
// 	 renderer->Delete();
// 	 renderWindow->Delete();
// 	 sphereSource->Delete();
// 	 this->textSource->Delete();
 }


 