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


#ifndef QTRIPP_H
#define QTRIPP_H

#include "vtk.h"
#include "flowfield.h"

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
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkLinearExtrusionFilter.h>
#include <vtkOBJReader.h>
#include <vtkProp3D.h>

#include <qmainwindow.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qpopupmenu.h>
#include <qmenubar.h>
#include <qtextedit.h>
#include <qfile.h>
#include <qfiledialog.h>
#include <qstatusbar.h>
#include <qmessagebox.h>
#include <qprinter.h>
#include <qapplication.h>
#include <qaccel.h>
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
#include <qlineedit.h>
#include <qcheckbox.h>
#include <qspinbox.h>

class QTextEdit;

class qtRipp: public QWidget {
    Q_OBJECT
	
	public:
		qtRipp();
		~qtRipp();

	private:
		void constructSelectionGroup();
		void constructControlGroup();
		void makeConnections();
		void constructVTKGroup();
		void constructFieldGroup();

	private slots:
		void showControls();
		void showVTK();
		void render();
		void toggleActor();
		void incrementSpinBox();
		void setValue();
// 		void setNumOfPoins();

private:
    //VTK
    VTK *theVTK;
    
    FlowField *theField;
    //selection
    QHBoxLayout *mainLayout;
    QPushButton *goButton;
    QPushButton *renderButton;
    QComboBox *selectionComboBox;
    //controls 
    QLabel *controlLabel;
    QLabel *label;
    QComboBox *controlComboBox;
    QLineEdit *controlLineEdit;
    QCheckBox *cb1;
    QSpinBox *intSpinBox;
    QSpinBox *decimalSpinBox;
    QSpinBox *spinBox1;
    
    bool isExampleCreated;
    int theSelection;
};


#endif
