#include <QTimer>
#include <QFileDialog>
#include "mainform.h"
#include "draw_manager.h"

MainForm::MainForm(QWidget *parent, Qt::WindowFlags f) : QDialog(parent, f)
{
	m_form.setupUi(this);
	canvas = new Canvas(m_form.groupBox_2);
	canvas->setGeometry( 10, 20, Canvas::getWidth(), Canvas::getHeight() );
	getDrawManager.init( canvas );
    
    connect( m_form.btnSave, SIGNAL(clicked()), this, SLOT(btnSaveClick()) );
    connect( m_form.btnClear, SIGNAL(clicked()), this, SLOT(btnClearClick()) );
}

MainForm::~MainForm()
{
	getDrawManager.release();
    canvas->clear();
	delete canvas;
}

void MainForm::btnClearClick()
{
    canvas->clear();
}

void MainForm::btnSaveClick()
{
    QString filename = QFileDialog::getSaveFileName();
    canvas->save_file( filename );
}
