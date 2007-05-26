#ifndef __MAINFORM_H__
#define __MAINFORM_H__

#include <QDialog>
#include <QTimer>
#include "ui_mainform.h"
#include "canvas.h"

class MainForm: public QDialog
{
	Q_OBJECT
public:
	MainForm(QWidget *parent = 0, Qt::WindowFlags f = 0);
	virtual ~MainForm();
    
public slots:
    void btnSaveClick();
    void btnClearClick();

protected:
	Ui::MainForm m_form;
	Canvas * canvas;
};

#endif //__MAINFORM_H__
