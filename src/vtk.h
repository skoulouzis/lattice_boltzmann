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
#ifndef VTK_H
#define VTK_H

#include <qwidget.h>
#include <vtkRenderWindow.h>
#include <QVTKWidget.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>

#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkConeSource.h>
#include <vtkCubeSource.h>
#include <vtkTextSource.h>
#include <vtkSphereSource.h>
#include <vtkVectorText.h>
#include <vtkEarthSource.h>
#include <vtkPointSource.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkLinearExtrusionFilter.h>
#include <vtkOBJReader.h>
#include <vtkProp3D.h>



#include <qtextstream.h>
#include <qpainter.h>
#include <qpaintdevicemetrics.h>
#include <qwhatsthis.h>
#include <qgroupbox.h>
#include <qpushbutton.h>
#include <qframe.h>
#include <qlayout.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qlabel.h>
#include <qcombobox.h>

#include <dirent.h>

class VTK : public QWidget {
	Q_OBJECT
		
	private:
		vtkTextSource *textSource;
		vtkConeSource *coneSource;
		vtkCubeSource *cubeSource;
		vtkSphereSource *sphereSource;
		vtkVectorText *vectorText;
		vtkEarthSource *earthSource;
		vtkPointSource *point;
		
		vtkActor *actor;
		vtkActor *enterpriseActor;
		vtkActorCollection *actorCollection;
		
		vtkPolyDataMapper *polyDataMapper;
		vtkRenderer *renderer;
		QVTKWidget *vtkWidget;
		vtkRenderWindow *renderWindow;
		
		int theSelection;
		int NumOfActors;
		bool isExapleCreated;

		char *workingDirectory;
		
// 		double enterpriseX;
// 		double enterpriseY;
// 		double enterpriseZ;
	
	public:
		VTK(QWidget *parent);
		~VTK();
		
		
	private:
		//VTK EXamples
		void cone(int numOfCones);
		void cube();
		void sphere(int startTheta);
		void vetkText();
		void multipleCones();
		void enterprise();
		void earth();
		void moon();
		void stars();
		void erthAndEnterprise();
		
		void makeVtkWidget();
		
	public:
		void deleteObjects();
		void changeRenderWindow(int);
		void setSelection(int);
		void setText(QString);	
		void alignmentChanged(int);
		void render();
};

#endif

