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
#ifndef FLOWFIELD_H
#define FLOWFIELD_H

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
#include <vtkArrowSource.h>
#include <vtkEarthSource.h>
#include <vtkPointSource.h>
#include <vtkLineSource.h>
#include <vtkRegularPolygonSource.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkLinearExtrusionFilter.h>
#include <vtkOutlineFilter.h>
#include <vtkOBJReader.h>
#include <vtkProp3D.h>
#include <vtkDataSetReader.h>
#include <vtkDataSetMapper.h>
#include <vtkContourFilter.h>
#include <vtkLookupTable.h>
#include <vtkRibbonFilter.h>
#include <vtkStructuredGridOutlineFilter.h>
#include <vtkStructuredPoints.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>
#include <vtkScalarBarActor.h>

#include <vtkRenderWindowInteractor.h>
#include <vtkStructuredPointsReader.h>
#include <vtkVolume16Reader.h>
#include <vtkOutlineFilter.h>
#include <vtkCamera.h>
#include <vtkPolyDataNormals.h>
#include <vtkContourFilter.h>
#include <vtkOutlineCornerFilter.h>
#include <vtkRungeKutta4.h>
#include <vtkStreamLine.h>
#include <vtkStreamTracer.h>
#include <vtkMapper2D.h>
#include <vtkImageMapper.h>
#include <vtkTubeFilter.h>
#include <vtkRuledSurfaceFilter.h>
#include <vtkMaskPoints.h>
#include <vtkGlyph3D.h>
#include <vtkGlyph2D.h>
#include <vtkRibbonFilter.h>
#include <vtkStructuredGridReader.h>
#include <vtkLineWidget.h>
#include <vtkPolyData.h>
#include <vtkVectorNorm.h>
#include <vtkThresholdPoints.h>
#include <vtkDataSetCollection.h>

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

class FlowField : public QWidget {
	Q_OBJECT
		
	private:
		vtkActor *actor;
		vtkActor *mixerActor;
		vtkActor *streamtubeActor;
		vtkActor *streamtubeActor2;
		vtkActor *streamlineActor;
		vtkActor *glyphActor;
		vtkActorCollection *actorCollection;
		vtkDataSetReader *reader;
		
		vtkPointSource *point;
		
		vtkPolyDataMapper *polyDataMapper;
		vtkRenderer *renderer;
		QVTKWidget *vtkWidget;
		vtkRenderWindow *renderWindow;
		vtkDataSetMapper *dataSetMapper; 
		vtkContourFilter *isosurface;
		vtkDataSetReader *dataSetReader;
		vtkStreamLine *streamLine;
		vtkStreamLine *streamLine2;
		vtkRungeKutta4 *rungeKutta4;
		vtkRibbonFilter *ribbonFilter;
		vtkDataSetCollection *dataSetCollection;
		
		vtkTextActor* text3;
		vtkTextActor* textActor;
		vtkScalarBarActor *barActor;
		vtkMapper2D *mapper2D;
		vtkTubeFilter *tubeFilter;
		vtkLookupTable *lookupTable;
		vtkMaskPoints *maskPoints;
		vtkContourFilter *contourFilter;
		vtkVectorNorm *vectorNorm;
		vtkGlyph3D *glyph;
		
		double *odjectDimentions;
		double *odjectCenter;
		double *scalarRange;
		int theSelection;
		int theControlSelection;
		int theNumOfPoints;
		int theRatio;
		double theTerminalSpeed;
		bool dataLoaded;
	
		char *workingDirectory;
	
	public:
		FlowField(QWidget *parent);
		
		
	private:
		void smrx();
		void tornado();
		void carotid();
		void extractData(char *path,double,bool);
		void srmxStreamlines();
		void tornadoStreamlines();
		void streamtubes();
		void mixingStreamLines();
		void mixingStreamTubes();
		void srmxglyphs();
		void carotidGlyphs();
		void carotidGlyphs(vtkDataSet *aDataSet,vtkPolyData *aSource);
		void tornadoGlyphs();
		void ribbon();
		void arrow();
		void makeVtkWidget();
		void createText(int,int);
		void createColorBar(vtkScalarsToColors *aLookupTable);
		void createTubeFilter(int,vtkStreamLine *astreamLine);
		void counstuctPoints(int,double,double,double);
		vtkStreamLine* counstuctStreamLine();
		void counstuctFluidVisulization();
		void renderSRMX();
		void renderTorado();
		void renderCarotid();
		void glyphs(vtkAlgorithmOutput *anInput,vtkPolyData *aSource,bool,double);
		void streamlines(vtkPolyData *source,vtkAlgorithmOutput *input);
		void getDataSet(char *aPth);
		void test(vtkPolyData *source,vtkAlgorithmOutput *input);
		
	public:
		void render();
		void changeRenderWindow(int);
		void setSelection(int);
		void setControlSelection(int);
		void setTerminalSpeed(int,int);
		void setNumOfPoins(int);
		void setMaskPointRatio(int);
		void toggleActor();
		

};

#endif



