#include "canvas.h"
#include <QPainter>
#include <QMouseEvent>
#include <QImage>
#include <QFile>
#include <QTextStream>
#include "draw_manager.h"
#include "board.h"

#define BW 1024
#define BH 768

#define BS 10

Canvas::Canvas(QWidget *parent) : QWidget(parent), mx(BS), my(BS), mode(C_ADD), selected(NULL)
{
	buffer = new QImage(BW,BH,QImage::Format_RGB32);
    setMouseTracking( true );
    
    for( int i=0; i<BOARD_SEGMENTS; ++i ) {
        plist.push_back( new QPoint( 3*BS+(int)(board_data[i].x*80.0), 3*BS+(int)(board_data[i].y*80.0) ) );
    }
}

Canvas::~Canvas()
{
	delete buffer;
}

void point( QImage * img, int x, int y, unsigned int color )
{
    img->setPixel( x, y, color );
    
    img->setPixel( x+1, y+1, color );
    img->setPixel( x-1, y-1, color );
    img->setPixel( x+1, y-1, color );
    img->setPixel( x-1, y+1, color );
    
    img->setPixel( x, y+1, color );
    img->setPixel( x, y-1, color );
    img->setPixel( x+1, y, color );
    img->setPixel( x-1, y, color );
    
    img->setPixel( x+2, y+2, color );
    img->setPixel( x-2, y-2, color );
    img->setPixel( x+2, y-2, color );
    img->setPixel( x-2, y+2, color );
}

void Canvas::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
    
    buffer->fill( MRGB(32,160,64) );
    
    for( int y=BS; y<BH; y += BS ) {
        for( int x=BS; x<BW; x += BS ) {
            buffer->setPixel( x, y, MRGB(255,255,255) );
        }
    }
    
    buffer->setPixel( mx+1, my+1, MRGB(255,255,255) );
    buffer->setPixel( mx-1, my-1, MRGB(255,255,255) );
    buffer->setPixel( mx+1, my-1, MRGB(255,255,255) );
    buffer->setPixel( mx-1, my+1, MRGB(255,255,255) );
        
    for( size_t i=0; i<plist.size(); ++i ) {
        int px = plist[i]->x(), py = plist[i]->y();
        point( buffer, px, py, MRGB(0,0,0) );
    }
    
	painter.drawImage( 0, 0, *buffer );
    painter.setPen( QColor(0,0,0) );
    if( plist.size() > 1 ) {
        for( size_t i=1; i<plist.size(); ++i ) {
            painter.drawLine( plist[i-1]->x(), plist[i-1]->y(), plist[i]->x(), plist[i]->y() );
        }
    }
    
    painter.setPen( QColor(32,140,64) );
    painter.drawLine( BS, my, BW-BS, my );
    painter.drawLine( mx, BS, mx, BH-BS );
}

void Canvas::set_pixel( int x, int y, unsigned long rgb )
{
	buffer->setPixel( x, y, rgb );
}

void Canvas::mouseMoveEvent(QMouseEvent * event)
{
    mx = event->x();
    my = event->y();
    
    mx += BS/2;
    my += BS/2;
    
    mx /= BS; mx *= BS;
    my /= BS; my *= BS;
    
    if( mx < BS ) mx = BS;
    if( my < BS ) my = BS;
    if( mx > BW-BS ) mx = BW-BS;
    if( my > BH-BS ) my = BH-BS;
    
    update();
}

void Canvas::mousePressEvent(QMouseEvent * event)
{

}

bool Canvas::insert_after( pIter * it )
{
    if( !it ) return false;
    plist.insert( *it, new QPoint(mx, my) );
    return true;   
}

Canvas::pIter * Canvas::find( int x, int y )
{
    static pIter it, bg = plist.begin(), ed = plist.end();
    
    for( it=bg; it < ed; ++it ) {
        if( (*it)->x() == x && (*it)->y() == y ) {
            return &it;
        }
    }
    
    return NULL;
}

void Canvas::remove_point( int x, int y )
{
    pIter * it = find( x, y );
    if( *it != plist.end() ) plist.erase( *it );   
}

void Canvas::mouseReleaseEvent(QMouseEvent * event)
{
    if( mode == C_ADD ) {
        if( event->button() == Qt::RightButton ) {
            if( plist.size() == 0 ) return;
            delete plist.back();
            plist.pop_back();
        } else {
            plist.push_back( new QPoint( mx, my ) );
        }
    } else if( mode == C_REMOVE ) {
        remove_point( mx, my );
    } else if( mode == C_INSERT ) {
        if( selected == NULL ) {
            selected = find( mx, my );
        } else {
            if( insert_after( selected ) ) {
                selected = NULL;
            }
        }
    }
    
    update();
}

int Canvas::getWidth()
{
    return BW;
}

int Canvas::getHeight()
{
    return BH;
}

void Canvas::save_file( QString name )
{
    QFile file(name);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    int minx = plist[0]->x(), miny = plist[0]->y();
    int maxx = minx, maxy = miny;
    
    for( size_t i=0; i<plist.size(); ++i ) {
        if( plist[i]->x() < minx ) minx = plist[i]->x();
        if( plist[i]->y() < miny ) miny = plist[i]->y();
        if( plist[i]->x() > maxx ) maxx = plist[i]->x();
        if( plist[i]->y() > maxy ) maxy = plist[i]->y();
    }
    
    int cx = (maxx+minx)/2;
    int cy = (maxy+miny)/2;
    
    out << "/* Generated by board_tool - Tomasz Huczek */\n\n";
    out << "#ifndef __BOARD_DATA_H__\n#define __BOARD_DATA_H__\n\n";
    out << "#define BOARD_SEGMENTS " << plist.size() << "\n\n";
    
    out << "#define BMAXX " << (double)(maxx-cx)/50.0 << "\n";
    out << "#define BMAXY " << (double)(maxy-cy)/50.0 << "\n";
    out << "#define BMINX " << (double)(minx-cx)/50.0 << "\n";
    out << "#define BMINY " << (double)(miny-cy)/50.0 << "\n\n";
    
    out << "struct point {\n\tdouble x;\n\tdouble y;\n};\n\n";
    out << "static point board_data[] = {\n\t";
    
    for( size_t i=0; i<plist.size(); ++i ) {
        out << "{ " << ((double)plist[i]->x()-cx)/50.0 << ", " << ((double)plist[i]->y()-cy)/50.0 << " }, ";
        if( i && (i % 5) == 0 ) out << "\n\t";
    }
    
    out << "\n};\n\n#endif\n";
    
    file.close();
}

void Canvas::clear()
{
    for( size_t i=0; i<plist.size(); ++i ) {
        delete plist[i];
    }
    plist.clear();
    update();
}
