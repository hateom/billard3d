#ifndef __CANVAS_H__
#define __CANVAS_H__

#include <QWidget>
#include <QImage>
#include <vector>
#include "boardobj.h"

class MainForm;

class Canvas: public QWidget
{
public:
    enum cMode {
        C_ADD,
        C_INSERT,
        C_REMOVE,
        C_DESK,
        C_BOTTOM,
        C_BALL
    };
    
	Canvas(MainForm * mf,QWidget *parent = 0);
	virtual ~Canvas();

	void set_pixel( int x, int y, unsigned long rgb );

    void clear();
    void set_mode( cMode imode ) { mode = imode; mod = 0; }
    
    static int getWidth();
    static int getHeight();
    
    void save_file( QString name );
    void open_file( QString name );
    
protected:
    MainForm * own;
    
    pIter * find( int x, int y );
    void remove_point( int x, int y );
    bool insert_after( pIter * it );
    
    void add_frame();
            
	void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    
    int mx, my;
    cMode mode;
    int mod;
    
	QImage * buffer;
    pIter * selected;
    
    BoardObject boardObj;
};

#endif // __CANVAS_H__
