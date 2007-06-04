#include "canvas.h"
#include <QPainter>
#include <QMouseEvent>
#include <QImage>
#include <QFile>
#include <QTextStream>
#include <cmath>
#include "draw_manager.h"
#include "board.h"
#include "vector2.h"
#include "mainform.h"

#define BW 1024
#define BH 768

#define BS 10
#define BF 40.0

Canvas::Canvas(MainForm *mf, QWidget *parent) : QWidget(parent), own(mf), mx(BS), my(BS), mode(C_ADD), selected(NULL)
{
	buffer = new QImage(BW,BH,QImage::Format_RGB32);
    setMouseTracking( true );
    
    for( int i=0; i<BOARD_SEGMENTS; ++i ) {
        boardObj.plist.push_back( new QPoint( 5*BS+(int)((board_data[i].x-BMINX)*50.0), 5*BS+(int)((board_data[i].y-BMINY)*50.0) ) );
    }
    
    for( int i=0; i<BOARD_SEGMENTS; ++i ) {
        boardObj.flist.push_back( new QPoint( 5*BS+(int)((band_data[i].x-BMINX)*50.0), 5*BS+(int)((band_data[i].y-BMINY)*50.0) ) );
    }
    
    for( int i=0; i<DESK_SEGMENTS; ++i ) {
        boardObj.dlist.push_back( new QPoint( 5*BS+(int)((desk_data[i].x-BMINX)*50.0), 5*BS+(int)((desk_data[i].y-BMINY)*50.0) ) );
    }
    
    for( int i=0; i<BALL_COUNT; ++i ) {
        boardObj.blist.push_back( new QPoint( 5*BS+(int)((ball_data[i].x-BMINX)*50.0), 5*BS+(int)((ball_data[i].y-BMINY)*50.0) ) );
    }
}

Canvas::~Canvas()
{
    clear();
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
    if( !event ) return;
    
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
    
    buffer->fill( MRGB(96,220,128) );
    
    for( int y=BS; y<BH; y += BS ) {
        for( int x=BS; x<BW; x += BS ) {
            buffer->setPixel( x, y, MRGB(255,255,255) );
        }
    }
    
    buffer->setPixel( mx+1, my+1, MRGB(255,255,255) );
    buffer->setPixel( mx-1, my-1, MRGB(255,255,255) );
    buffer->setPixel( mx+1, my-1, MRGB(255,255,255) );
    buffer->setPixel( mx-1, my+1, MRGB(255,255,255) );
        
    for( size_t i=0; i<boardObj.plist.size(); ++i ) {
        int px = boardObj.plist[i]->x(), py = boardObj.plist[i]->y();
        point( buffer, px, py, MRGB(0,0,0) );
    }
    
    painter.drawImage( 0, 0, *buffer );
    painter.setPen( QColor(0,0,0) );
    if( boardObj.plist.size() > 1 ) {
        for( size_t i=1; i<boardObj.plist.size(); ++i ) {
            painter.drawLine( boardObj.plist[i-1]->x(), boardObj.plist[i-1]->y(), boardObj.plist[i]->x(), boardObj.plist[i]->y() );
        }
    }
    
    painter.setPen( QColor(100,100,100) );
    if( boardObj.flist.size() > 1 ) {
        for( size_t i=1; i<boardObj.flist.size(); ++i ) {
            painter.drawLine( boardObj.flist[i-1]->x(), boardObj.flist[i-1]->y(), boardObj.flist[i]->x(), boardObj.flist[i]->y() );
        }
    }
    
    painter.setPen( QColor(100,100,250) );
    if( boardObj.dlist.size() > 1 ) {
        for( size_t i=1; i<boardObj.dlist.size(); ++i ) {
            painter.drawLine( boardObj.dlist[i-1]->x(), boardObj.dlist[i-1]->y(), boardObj.dlist[i]->x(), boardObj.dlist[i]->y() );
        }
    }
    
    painter.setPen( QColor(0,100,0) );
    if( boardObj.btlist.size() > 1 ) {
        for( size_t i=1; i<boardObj.btlist.size(); ++i ) {
            painter.drawLine( boardObj.btlist[i-1]->x(), boardObj.btlist[i-1]->y(), boardObj.btlist[i]->x(), boardObj.btlist[i]->y() );
        }
    }
    
    painter.setPen( QColor(250,0,0) );
    for( size_t i=0; i<boardObj.blist.size(); ++i ) {
        int px = boardObj.blist[i]->x(), py = boardObj.blist[i]->y();
        painter.drawEllipse( px-15, py-15, 30, 30 );
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
    
    if( mode == C_ADD && (boardObj.plist.size() > 0) ) {
        own->set_info( QString::number(boardObj.plist[boardObj.plist.size()-1]->x()-mx) + tr(", ") + 
                       QString::number(boardObj.plist[boardObj.plist.size()-1]->y()-my) );
    }
    
    update();
}

bool Canvas::insert_after( pIter * it )
{
    if( !it ) return false;
    boardObj.plist.insert( *it, new QPoint(mx, my) );
    return true;   
}

pIter * Canvas::find( int x, int y )
{
    static pIter it, bg = boardObj.plist.begin(), ed = boardObj.plist.end();
    
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
    if( it != NULL ) boardObj.plist.erase( *it );   
}

void Canvas::add_frame()
{
    if( boardObj.plist.size() <= 1 ) return;
    
    Vector2 p0, p1, p2, v2, v1, r2, n2, n1, o1a, o1b, o2a, o2b;
    
    p2.x = (double)(boardObj.plist[boardObj.plist.size()-1]->x());
    p2.y = (double)(boardObj.plist[boardObj.plist.size()-1]->y());
    p1.x = (double)(boardObj.plist[boardObj.plist.size()-2]->x());
    p1.y = (double)(boardObj.plist[boardObj.plist.size()-2]->y());
    
    if( boardObj.plist.size() > 2 ) {
        p0.x = (double)(boardObj.plist[boardObj.plist.size()-3]->x());
        p0.y = (double)(boardObj.plist[boardObj.plist.size()-3]->y());
    } else {
        p0.x    = p0.y = 0.0;
    }
    
    v2.x = p2.x - p1.x;
    v2.y = p2.y - p1.y;
    n2.x = v2.x;
    n2.y = v2.y;
    n2.normalize();
    
    r2.y = -n2.x;
    r2.x = n2.y;
    
    
    o1a.x = (int)(p1.x+BF*r2.x);
    o1a.y = (int)(p1.y+BF*r2.y);
    
    o1b.x = (int)(p2.x+BF*r2.x);
    o1b.y = (int)(p2.y+BF*r2.y);
    
    if( boardObj.flist.size() > 1 ) {
        v1.x = p1.x - p0.x;
        v1.y = p1.y - p0.y;
        
        n1.x = v1.x;
        n1.y = v1.y;
        
        o2a.x = boardObj.flist[boardObj.flist.size()-2]->x();
        o2a.y = boardObj.flist[boardObj.flist.size()-2]->y();
    
        o2b.x = boardObj.flist[boardObj.flist.size()-1]->x();
        o2b.y = boardObj.flist[boardObj.flist.size()-1]->y();
        
        double a1, a2, c1, c2;
    
        a1 = (o1b.y-o1a.y)/(o1b.x-o1a.x);
        c1 = a1 + o1a.y;
        
        a2 = (o2b.y-o2a.y)/(o2b.x-o2a.x);
        c2 = a2 + o2a.y;
    
        Vector2 ip;
        
        double det, nom1, nom2;
        det = (o1a.x-o1b.x)*(o2a.y-o2b.y) - (o1a.y-o1b.y)*(o2a.x-o2b.x);
        nom1 = o1a.x*o1b.y-o1a.y*o1b.x;
        nom2 = o2a.x*o2b.y-o2a.y*o2b.x;
    
        //ip.x = (c1-c2)/(a2-a1);
        //ip.y = (a2*c1-a1*c2)/(a2-a1);
        
        ip.x = (nom1*(o2a.x-o2b.x)-nom2*(o1a.x-o1b.x))/det;
        ip.y = (nom1*(o2a.y-o2b.y)-nom2*(o1a.y-o1b.y))/det;
        
        printf( "%3.3f %3.3f\n", ip.x, ip.y );
        
        delete boardObj.flist.back();
        boardObj.flist.pop_back();
        
        boardObj.flist.push_back( new QPoint( (int)ip.x, (int)ip.y ) );
        //boardObj.flist.push_back( new QPoint( (int)o1a.x, (int)o1a.y ) );
    } else {
        boardObj.flist.push_back( new QPoint( (int)o1a.x, (int)o1a.y ) );
    }
    
    boardObj.flist.push_back( new QPoint( (int)o1b.x, (int)o1b.y ) );
    //printf( "%2.2f %2.2f %2.2f %2.2f\n", f.x, f.y, v.x, v.y );
}

void Canvas::mouseReleaseEvent(QMouseEvent * event)
{
    if( mode == C_ADD ) {
        if( event->button() == Qt::RightButton ) {
            if( boardObj.plist.size() == 0 ) return;
            delete boardObj.plist.back();
            boardObj.plist.pop_back();
            delete boardObj.flist.back();
            boardObj.flist.pop_back();
        } else {
            boardObj.plist.push_back( new QPoint( mx, my ) );
            add_frame();
        }
    } else if( mode == C_BOTTOM ) {
        if( event->button() == Qt::RightButton ) {
            if( boardObj.btlist.size() == 0 ) return;
            delete boardObj.btlist.back();
            boardObj.btlist.pop_back();
        } else {
            boardObj.btlist.push_back( new QPoint( mx, my ) );
        }
    } else if( mode == C_BALL ) {
        if( event->button() == Qt::RightButton ) {
            if( boardObj.blist.size() == 0 ) return;
            delete boardObj.blist.back();
            boardObj.blist.pop_back();
        } else {
            boardObj.blist.push_back( new QPoint( mx, my ) );
        }
    } else if( mode == C_DESK ) {
        if( event->button() == Qt::RightButton ) {
            if( boardObj.dlist.size() == 0 ) return;
            delete boardObj.dlist.back();
            boardObj.dlist.pop_back();
        } else {
            boardObj.dlist.push_back( new QPoint( mx, my ) );
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
    boardObj.save(name.toStdString().c_str());
    return;
    
    QFile file(name);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    int minx = boardObj.plist[0]->x(), miny = boardObj.plist[0]->y();
    int maxx = minx, maxy = miny;
    
    for( size_t i=0; i<boardObj.plist.size(); ++i ) {
        if( boardObj.plist[i]->x() < minx ) minx = boardObj.plist[i]->x();
        if( boardObj.plist[i]->y() < miny ) miny = boardObj.plist[i]->y();
        if( boardObj.plist[i]->x() > maxx ) maxx = boardObj.plist[i]->x();
        if( boardObj.plist[i]->y() > maxy ) maxy = boardObj.plist[i]->y();
    }
    
    int cx = (maxx+minx)/2;
    int cy = (maxy+miny)/2;
    
    out << "/* Generated by board_tool - Tomasz Huczek */\n\n";
    out << "#ifndef __BOARD_DATA_H__\n#define __BOARD_DATA_H__\n\n";
    out << "#define BOARD_SEGMENTS " << boardObj.plist.size() << "\n\n";
    out << "#define BAND_SEGMENTS  " << boardObj.flist.size() << "\n";
    
    out << "#define BMAXX " << (double)(maxx-cx)/50.0 << "\n";
    out << "#define BMAXY " << (double)(maxy-cy)/50.0 << "\n";
    out << "#define BMINX " << (double)(minx-cx)/50.0 << "\n";
    out << "#define BMINY " << (double)(miny-cy)/50.0 << "\n\n";
    
    out << "struct point {\n\tdouble x;\n\tdouble y;\n};\n\n";
    out << "static point board_data[] = {\n\t";
    
    for( size_t i=0; i<boardObj.plist.size(); ++i ) {
        out << "{ " << ((double)boardObj.plist[i]->x()-cx)/50.0 << ", " << ((double)boardObj.plist[i]->y()-cy)/50.0 << " }, ";
        if( i && (i % 5) == 0 ) out << "\n\t";
    }
    
    out << "\n};\n\n";
    
    if( boardObj.dlist.size() > 0 ) {
        
        out << "#define DESK_SEGMENTS " << boardObj.dlist.size() << "\n\n";
        out << "struct tpoint {\n\tdouble x;\n\tdouble y;\n\tdouble tx;\n\tdouble ty;\n};\n\n";
        out << "static tpoint desk_data[] = {\n\t";
    
        double dmaxx = boardObj.dlist[0]->x(), dmaxy = boardObj.dlist[0]->y(), dminx = dmaxx, dminy = dmaxy;
        
        for( size_t i=0; i<boardObj.dlist.size(); ++i ) {
            if( boardObj.dlist[i]->x() < dminx ) dminx = boardObj.dlist[i]->x();
            if( boardObj.dlist[i]->y() < dminy ) dminy = boardObj.dlist[i]->y();
            if( boardObj.dlist[i]->x() > dmaxx ) dmaxx = boardObj.dlist[i]->x();
            if( boardObj.dlist[i]->x() > dmaxy ) dmaxy = boardObj.dlist[i]->y();
        }
        
        double ccx, ccy;
        
        for( size_t i=0; i<boardObj.dlist.size(); ++i ) {
            ccx = ((double)boardObj.dlist[i]->x());
            ccy = ((double)boardObj.dlist[i]->y());
            
            out << "{ " << (ccx-cx)/50.0 << ", " << (ccy-cy)/50.0 << ", ";
            out << (ccx-dminx)/(dmaxx-dminx) << ", " << (ccy-dminy)/(dmaxy-dminy) << " }, ";
            if( i && (i % 5) == 0 ) out << "\n\t";
        }
    
        out << "\n};\n\n";
    
    }
    
    out << "#define BALL_COUNT " << boardObj.blist.size() << "\n\n";
    out << "static point ball_data[] = {\n\t";
    
    for( size_t i=0; i<boardObj.blist.size(); ++i ) {
        out << "{ " << ((double)boardObj.blist[i]->x()-cx)/50.0 << ", " << ((double)boardObj.blist[i]->y()-cy)/50.0 << " }, ";
        if( i && (i % 5) == 0 ) out << "\n\t";
    }
    
    out << "\n};\n\n";
    
    out << "#define BOTTOM_SEGMENTS " << boardObj.btlist.size() << "\n\n";
    out << "static point bottom_data[] = {\n\t";
    
    for( size_t i=0; i<boardObj.btlist.size(); ++i ) {
        out << "{ " << ((double)boardObj.btlist[i]->x()-cx)/50.0 << ", " << ((double)boardObj.btlist[i]->y()-cy)/50.0 << " }, ";
        if( i && (i % 5) == 0 ) out << "\n\t";
    }
    
    out << "\n};\n\n";
    
    out << "static point band_data[] = {\n\t";
    
    for( size_t i=0; i<boardObj.flist.size()-1; ++i ) {
        out << "{ " << ((double)boardObj.flist[i]->x()-cx)/50.0 << ", " << ((double)boardObj.flist[i]->y()-cy)/50.0 << " }, ";
        if( i && (i % 5) == 0 ) out << "\n\t";
    }
    
    out << "{ " << ((double)boardObj.flist[0]->x()-cx)/50.0 << ", " << ((double)boardObj.flist[0]->y()-cy)/50.0 << " }";
    
    out << "\n};\n\n#endif\n";
    
    file.close();
}

void Canvas::open_file( QString name )
{
    boardObj.load(name.toStdString().c_str());
}

void Canvas::clear()
{
    boardObj.release();
}
