#include <QTimer>
#include <QFileDialog>
#include "mainform.h"
#include "draw_manager.h"

MainForm::MainForm(QWidget *parent, Qt::WindowFlags f) : QDialog(parent, f)
{
	m_form.setupUi(this);
	canvas = new Canvas(this,m_form.groupBox_2);
	canvas->setGeometry( 10, 20, Canvas::getWidth(), Canvas::getHeight() );
	getDrawManager.init( canvas );
    
    connect( m_form.btnSave, SIGNAL(clicked()), this, SLOT(btnSaveClick()) );
    connect( m_form.btnClear, SIGNAL(clicked()), this, SLOT(btnClearClick()) );
    
    connect( m_form.radioAdd, SIGNAL(clicked()), this, SLOT(btnAdd()) );
    connect( m_form.radioInsert, SIGNAL(clicked()), this, SLOT(btnInsert()) );
    connect( m_form.radioRemove, SIGNAL(clicked()), this, SLOT(btnRemove()) );
    connect( m_form.radioDesk, SIGNAL(clicked()), this, SLOT(btnDesk()) );
    connect( m_form.radioBall, SIGNAL(clicked()), this, SLOT(btnBall()) );
    connect( m_form.radioBottom, SIGNAL(clicked()), this, SLOT(btnBottom()) );
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

void MainForm::btnRemove()
{
    if( m_form.radioRemove->isChecked() )
        canvas->set_mode( Canvas::C_REMOVE );
}

void MainForm::btnAdd()
{
    if( m_form.radioAdd->isChecked() )
        canvas->set_mode( Canvas::C_ADD );
}

void MainForm::btnInsert()
{
    if( m_form.radioInsert->isChecked() )
        canvas->set_mode( Canvas::C_INSERT );
}

void MainForm::btnDesk()
{
    if( m_form.radioDesk->isChecked() )
        canvas->set_mode( Canvas::C_DESK );
}

void MainForm::btnBall()
{
    if( m_form.radioBall->isChecked() )
        canvas->set_mode( Canvas::C_BALL );
}

void MainForm::btnBottom()
{
    if( m_form.radioBottom->isChecked() )
        canvas->set_mode( Canvas::C_BOTTOM );
}
