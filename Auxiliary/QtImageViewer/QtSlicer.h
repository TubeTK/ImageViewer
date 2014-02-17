#ifndef QtSlicer_h
#define QtSlicer_h

//#include <QtGui>
#include <QDialog>

#include <itkImage.h>
#include "ui_QtSlicerGUI.h"
#include "ui_QtSlicerHelpGUI.h"


class QtSlicer : public QDialog, public Ui::GuiDialogBase
{
  Q_OBJECT
public:
    
  QtSlicer( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WindowFlags fl = 0 );
  ~QtSlicer();
  
  typedef itk::Image<double,3> ImageType;
public slots:

  void setDisplayPosition(int x, int y , int z, double value);
  void setInputImage(ImageType * newImData);
  void setDisplaySliceNumber(int number);
  void setDisplayIMin(int value);
  void setDisplayIMax(int value);
};

#endif
