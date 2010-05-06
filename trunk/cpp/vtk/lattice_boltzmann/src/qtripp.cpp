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


#include "qtripp.h"


qtRipp::qtRipp() : QWidget( 0, "qtRipp", WDestructiveClose ){
	isExampleCreated = false;
	mainLayout = new QHBoxLayout(this);
	constructSelectionGroup();	
	constructControlGroup();
	constructVTKGroup();
	constructFieldGroup();
	makeConnections();
	
	constructFieldGroup();
// 	resize( 800, 600 );
}


qtRipp::~qtRipp(){

}

 void qtRipp::constructSelectionGroup(){
	 QWidget *selectWidget = new QWidget;
	 QHBoxLayout *secondaryLayout = new QHBoxLayout( selectWidget, 1, 1 );
	 // 	 All the widgets will be laid out within the form's vertical box layout.
	 
	 QVBoxLayout *selectionLayout = new QVBoxLayout( 0, 0, 1 );

// 	 The chart type label and combobox will be laid out side by side.

	 QLabel *selectionLabel = new QLabel( "VTK Example Selection", selectWidget );
	 selectionLayout->addWidget( selectionLabel );

	 selectionComboBox = new QComboBox( selectWidget );
	 selectionComboBox->insertItem( tr("Rotating cone") );
	 selectionComboBox->insertItem( tr("Cube") );
	 selectionComboBox->insertItem( tr("Sphere") );
	 selectionComboBox->insertItem(tr("PacMan"));
	 selectionComboBox->insertItem(tr("Text"));
	 selectionComboBox->insertItem(tr("Multiple Cones"));
	 selectionComboBox->insertItem(tr("Enterprise"));
	 selectionComboBox->insertItem(tr("Earth"));
	 selectionComboBox->insertItem(tr("SMRX reactor"));
	 selectionComboBox->insertItem(tr("Tornado"));
	 selectionComboBox->insertItem(tr("Carotid"));
	 
	 
	 selectionLayout->addWidget( selectionComboBox );
	 
	 goButton = new QPushButton(selectWidget);
	 goButton->setText(tr("Go"));
	 selectionLayout->addWidget(goButton);
	 	 
	 secondaryLayout->addLayout( selectionLayout );
	 selectWidget->show();
 }

 void qtRipp::constructControlGroup(){
// 	 All the widgets will be laid out within the form's vertical box layout.
	 
	 QVBoxLayout *chartTypeLayout = new QVBoxLayout;

// 	 The chart type label and combobox will be laid out side by side.
	 
	 label = new QLabel( "Loading Application...", this );
// 	 label->setMaximumWidth(90);
	 label->hide();
	 chartTypeLayout->addWidget( label );

	 controlLabel = new QLabel( "Aligment", this );
	 controlLabel->hide();
	 chartTypeLayout->addWidget( controlLabel );

	 controlComboBox = new QComboBox( this );
	 controlComboBox->insertItem( tr("Top-Bottom") );
	 controlComboBox->insertItem( tr("Side To Side") );
	 controlComboBox->hide();
	 chartTypeLayout->addWidget( controlComboBox );
	 
	 
	 QHBoxLayout *spinBoxLayout = new QHBoxLayout(chartTypeLayout);
			 
	 intSpinBox = new QSpinBox(this);
	 intSpinBox->setMaximumWidth(40);
	 intSpinBox->setRange(0,1);
	 intSpinBox->setValue(0);
	 decimalSpinBox = new QSpinBox(this);
	 decimalSpinBox->setMaximumWidth(40);
	 decimalSpinBox->setMinValue(-1);
	 decimalSpinBox->setValue(1);
	 intSpinBox->hide();
	 decimalSpinBox->hide();
	 spinBoxLayout->addWidget(controlLabel);
	 spinBoxLayout->addWidget(intSpinBox);
	 spinBoxLayout->addWidget(decimalSpinBox);
	 
	 
	 cb1 = new QCheckBox( this );
	 cb1->setChecked( TRUE );
	 cb1->hide();
	 chartTypeLayout->addWidget(cb1);
	 
	 controlLineEdit = new QLineEdit(this);
	 controlLineEdit->setMaximumWidth(80);
	 controlLineEdit->setFocus();
	 chartTypeLayout->addWidget(controlLineEdit);
	 controlLineEdit->hide();
	 
	 renderButton = new QPushButton(this);
	 renderButton->setText(tr("Render"));
	 chartTypeLayout->addWidget(renderButton);
	 renderButton->hide();
			 
	 mainLayout->addLayout( chartTypeLayout );
 }
 
void qtRipp::constructVTKGroup(){
	QHBoxLayout *vtkLayout = new QHBoxLayout( 0, 0, 1 );
	theVTK = new VTK(this);
	theVTK->hide();
	vtkLayout-> addWidget( theVTK );
	mainLayout->addLayout( vtkLayout );
}

void qtRipp::constructFieldGroup(){
	QHBoxLayout *vtkLayout = new QHBoxLayout( 0, 0, 1 );	
	theField = new FlowField(this);
	theField->hide();
	vtkLayout-> addWidget( theField );
	mainLayout->addLayout( vtkLayout );
}


 void qtRipp::makeConnections(){
	 connect(goButton, SIGNAL(clicked()), this, SLOT(showControls()));
// 	 connect(goButton, SIGNAL(clicked()), this, SLOT(showVTK()));
	 connect(renderButton, SIGNAL(clicked()), this, SLOT(render()));
	 connect(cb1, SIGNAL(toggled(bool)), this, SLOT(toggleActor()));
	 
	 connect(decimalSpinBox, SIGNAL(valueChanged (int)), this, SLOT(incrementSpinBox()));
	 connect(intSpinBox, SIGNAL(valueChanged (int)), this, SLOT(setValue()));
// 	 connect(spinBox1, SIGNAL(valueChanged (int)), this, SLOT( setNumOfPoins() ));	 
 }
 
 void qtRipp::render(){
	 
	 if(selectionComboBox->currentItem() >=0 && selectionComboBox->currentItem() <= 7){
		 switch (selectionComboBox->currentItem()) {
			 case 4:
				 theVTK->setText(controlLineEdit->text());
				 break;
			 case 5:
				 theVTK->alignmentChanged(controlComboBox->currentItem());
				 break;
		 }
		 theVTK->setSelection(selectionComboBox->currentItem());
		 theVTK->render();
	 }else if(selectionComboBox->currentItem() >=8){
		 switch (selectionComboBox->currentItem()) {
			 case 8:
				 break;
		 }
		 theField->setSelection(selectionComboBox->currentItem());
		 theField->setControlSelection(controlComboBox->currentItem());
		 theField->render();
	 }

 }
 
 void qtRipp::showControls(){
	 theVTK->setSelection(selectionComboBox->currentItem());
	 switch (selectionComboBox->currentItem()) {
		 //rotating cone
		 case 0:
			 renderButton->show();
			 controlComboBox->hide(); 
			 controlLineEdit->hide();
			 label->setText(tr("Controls"));
			 label->show();
			 cb1->hide();
			 intSpinBox->hide();
			 decimalSpinBox->hide();
			 controlLabel->hide();
			 break;
		//vtk text
		 case 4:
			 label->setText(tr("Controls"));
			 renderButton->show();
			 controlComboBox->hide(); 
			 controlLineEdit->show();
			 label->show();
			 cb1->hide();
			 intSpinBox->hide();
			 decimalSpinBox->hide();
			 controlLabel->hide();
			 break; 
		//3 cones
		 case 5:
			 label->setText(tr("Controls"));
			 int items;
			 items = controlComboBox->count();
			 for(int i=0;i<items;i++){
				 controlComboBox->removeItem(0);
				 
			 }
			 controlComboBox->insertItem( tr("Top-Bottom") );
			 controlComboBox->insertItem( tr("Side To Side") );
			 controlComboBox->setCurrentItem(0);
			 renderButton->show();
			 controlComboBox->show(); 
			 controlLabel->show();
			 controlLineEdit->hide();
			 label->show();
			 cb1->hide();
			 intSpinBox->hide();
			 decimalSpinBox->hide();
			 controlLabel->hide();
			 break;
			 
		//enertprise
		 case 6:
			 label->setText(tr("Controls"));
			 renderButton->show();
			 label->show();
			 controlComboBox->hide(); 
			 controlLineEdit->hide();
			 cb1->hide();
			 intSpinBox->hide();
			 decimalSpinBox->hide();
			 controlLabel->hide();
			 break;
		//earth
		 case 7:
			 label->setText(tr("Controls"));
			 renderButton->show();
			 controlComboBox->hide(); 
			 controlLineEdit->hide();
			 label->show();
			 cb1->hide();
			 intSpinBox->hide();
			 decimalSpinBox->hide();
			 controlLabel->hide();
			 break;
			 
		//SMRX reactor
		 case 8:
			 label->setText(tr("Controls"));
			 label->show();
			 controlComboBox->hide(); 
			 controlLineEdit->hide();
			 
			 items = controlComboBox->count();
			 for(int i=0;i<items;i++){
				 controlComboBox->removeItem(0);
				 
			 }
			 controlComboBox->insertItem( tr("Streamlines") );
			 controlComboBox->insertItem( tr("Streamtubes") );
			 controlComboBox->insertItem( tr("Mixing streamtubes") );
			 controlComboBox->insertItem( tr("Mixing streamlines") );
			 controlComboBox->insertItem( tr("Glyphs") );
			 controlComboBox->setCurrentItem(0);
			 
			 controlLabel->setText(tr("Terminal Speed"));
			 controlLabel->show();
			 renderButton->show();
			 label->show(); 
			 cb1->setText(tr("Toggle rector on/off"));
			 cb1->show();
			 controlComboBox->show();
			 intSpinBox->setRange(0,1);
			 intSpinBox->setValue(0);

			 intSpinBox->show();
			 decimalSpinBox->show();
			 break;
			 
		 case 9:
			 label->setText(tr("Controls"));
			 label->show();
			 controlComboBox->hide(); 
			 controlLineEdit->hide();
			 
			 items = controlComboBox->count();
			 for(int i=0;i<items;i++){
				 controlComboBox->removeItem(0);
				 
			 }
			 controlComboBox->insertItem( tr("Streamlines") );
			 controlComboBox->insertItem( tr("Streamtubes") );
			 controlComboBox->insertItem( tr("Glyphs") );
			 controlComboBox->insertItem( tr("Ribbons") );
			 controlComboBox->setCurrentItem(0);
			 
			 controlLabel->setText(tr("Mask Points Ratio"));
			 controlLabel->show();
			 renderButton->show();
			 label->show(); 
			 cb1->hide();
			 controlComboBox->show();
			 intSpinBox->setRange(2,900);
			 intSpinBox->setLineStep(2);
			 intSpinBox->setValue(300);
			 intSpinBox->show();
			 decimalSpinBox->hide();
			 break;
			 
		 case 10:
			 label->setText(tr("Controls"));
			 label->show();
			 items = controlComboBox->count();
			 for(int i=0;i<items;i++){
				 controlComboBox->removeItem(0);
				 
			 }
			 controlComboBox->insertItem( tr("Arrow Glyphs") );
			 controlComboBox->insertItem( tr("Cone Glyphs") );
			 controlComboBox->insertItem( tr("Line Glyphs") );
			 controlComboBox->show();
			 controlComboBox->setCurrentItem(0);
			 controlLabel->setText(tr("Mask Points Ratio"));
			 controlLabel->show();
			 renderButton->show();
			 intSpinBox->setRange(2,900);
			 intSpinBox->setLineStep(2);
			 intSpinBox->setValue(300);
			 intSpinBox->show();
			 decimalSpinBox->hide();			
			 break;
		 default:
			 label->hide();
			 renderButton->hide();
			 controlComboBox->hide(); 
			 controlLineEdit->hide();
			 cb1->hide();
			 intSpinBox->hide();
			 decimalSpinBox->hide();
			 break;
	 } 
	 showVTK();
	 update();
 }
 
 void qtRipp::showVTK(){
	 if(selectionComboBox->currentItem() >=0 && selectionComboBox->currentItem() <=7 ){
		 theField->hide();
		 theVTK->changeRenderWindow(selectionComboBox->currentItem());
		 theVTK->update();
		 theVTK->show();
	 }else if(selectionComboBox->currentItem() >=8 ){
		 theVTK->hide();
			
		 theField->changeRenderWindow(selectionComboBox->currentItem());

		 theField->update();
		 theField->show();
	 }else{
		 theVTK->hide();
		 theField->hide();
	 }
 }
 
 void qtRipp::toggleActor(){
	 if(selectionComboBox->currentItem() >=8 ){
		 theField->toggleActor();
	 }
 }
 
 void qtRipp::incrementSpinBox(){
	 if(decimalSpinBox->value() >= 10 /*&& intSpinBox->value() < intSpinBox->maxValue()*/ ){
		 intSpinBox->setValue(intSpinBox->value()+1);
		 decimalSpinBox->setValue(0);
	 }
	 if(decimalSpinBox->value() <= -1){
		 decimalSpinBox->setValue(9);
	 }
	 setValue();
 }
 
 void qtRipp::setValue(){
	 switch(selectionComboBox->currentItem() ){
		 
		 case 8:
			 theField->setTerminalSpeed(intSpinBox->value() , decimalSpinBox->value());
			 theField->setMaskPointRatio(100);
			 break;
			 	 
		 case 9:
			 theField->setMaskPointRatio(intSpinBox->value());
			 break;
			 
		 case 10:
			 theField->setMaskPointRatio(intSpinBox->value());
			 break;
	 }


 }
 
//  void qtRipp::setNumOfPoins(){
// 	 theField->setNumOfPoins(spinBox1->value());
//  }
  
