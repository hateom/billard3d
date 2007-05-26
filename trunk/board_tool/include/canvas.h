#ifndef __CANVAS_H__
#define __CANVAS_H__

#include <QWidget>
#include <QImage>
#include <vector>

class Canvas: public QWidget
{
public:
	Canvas(QWidget *parent = 0);
	virtual ~Canvas();

	void set_pixel( int x, int y, unsigned long rgb );

    void clear();
    
    static int getWidth();
    static int getHeight();
    
    void save_file( QString name );
    
protected:
	void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    
    int mx, my;
    
	QImage * buffer;
    
    std::vector<QPoint*> plist;
};

#endif // __CANVAS_H__
