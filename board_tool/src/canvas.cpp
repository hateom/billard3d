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
        plist.push_back( new QPoint( 5*BS+(int)((board_data[i].x-BMINX)*50.0), 5*BS+(int)((board_data[i].y-BMINY)*50.0) ) );
    }
    
    for( int i=0; i<BOARD_SEGMENTS; ++i ) {
        flist.push_back( new QPoint( 5*BS+(int)((band_data[i].x-BMINX)*50.0), 5*BS+(int)((band_data[i].y-BMINY)*50.0) ) );
    }
    
    for( int i=0; i<DESK_SEGMENTS; ++i ) {
        dlist.push_back( new QPoint( 5*BS+(int)((desk_data[i].x-BMINX)*50.0), 5*BS+(int)((desk_data[i].y-BMINY)*50.0) ) );
    }
    
    for( int i=0; i<BALL_COUNT; ++i ) {
        blist.push_back( new QPoint( 5*BS+(int)((ball_data[i].x-BMINX)*50.0), 5*BS+(int)((ball_data[i].y-BMINY)*50.0) ) );
    }
}

Canvas::~Canvas()
{
    for( size_t i=0; i<plist.size(); ++i ) {
        delete plist[i];
    }
    plist.clear();
    for( size_t i=0; i<flist.size(); ++i ) {
        delete flist[i];
    }
    flist.clear();
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
    
    painter.setPen( QColor(100,100,100) );
    if( flist.size() > 1 ) {
        for( size_t i=1; i<flist.size(); ++i ) {
            painter.drawLine( flist[i-1]->x(), flist[i-1]->y(), flist[i]->x(), flist[i]->y() );
        }
    }
    
    painter.setPen( QColor(100,100,250) );
    if( dlist.size() > 1 ) {
        for( size_t i=1; i<dlist.size(); ++i ) {
            painter.drawLine( dlist[i-1]->x(), dlist[i-1]->y(), dlist[i]->x(), dlist[i]->y() );
        }
    }
    
    painter.setPen( QColor(0,100,0) );
    if( btlist.size() > 1 ) {
        for( size_t i=1; i<btlist.size(); ++i ) {
            painter.drawLine( btlist[i-1]->x(), btlist[i-1]->y(), btlist[i]->x(), btlist[i]->y() );
        }
    }
    
    painter.setPen( QColor(250,0,0) );
    for( size_t i=0; i<blist.size(); ++i ) {
        int px = blist[i]->x(), py = blist[i]->y();
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
    
    if( mode == C_ADD && (plist.size() > 0) ) {
        own->set_info( QString::number(plist[plist.size()-1]->x()-mx) + tr(", ") + QString::number(plist[plist.size()-1]->y()-my) );
    }
    
    update();
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
    if( it != NULL ) plist.erase( *it );   
}

void Canvas::add_frame()
{
    if( plist.size() <= 1 ) return;
    
    Vector2 p0, p1, p2, v2, v1, r2, n2, n1, o1a, o1b, o2a, o2b;
    
    p2.x = (double)(plist[plist.size()-1]->x());
    p2.y = (double)(plist[plist.size()-1]->y());
    p1.x = (double)(plist[plist.size()-2]->x());
    p1.y = (double)(plist[plist.size()-2]->y());
    
    if( plist.size() > 2 ) {
        p0.x = (double)(plist[plist.size()-3]->x());
        p0.y = (double)(plist[plist.size()-3]->y());
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
    
    if( flist.size() > 1 ) {
        v1.x = p1.x - p0.x;
        v1.y = p1.y - p0.y;
        
        n1.x = v1.x;
        n1.y = v1.y;
        
        o2a.x = flist[flist.size()-2]->x();
        o2a.y = flist[flist.size()-2]->y();
    
        o2b.x = flist[flist.size()-1]->x();
        o2b.y = flist[flist.size()-1]->y();
        
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
        
        delete flist.back();
        flist.pop_back();
        
        flist.push_back( new QPoint( (int)ip.x, (int)ip.y ) );
        //flist.push_back( new QPoint( (int)o1a.x, (int)o1a.y ) );
    } else {
        flist.push_back( new QPoint( (int)o1a.x, (int)o1a.y ) );
    }
    
    flist.push_back( new QPoint( (int)o1b.x, (int)o1b.y ) );
    //printf( "%2.2f %2.2f %2.2f %2.2f\n", f.x, f.y, v.x, v.y );
}

void Canvas::mouseReleaseEvent(QMouseEvent * event)
{
    if( mode == C_ADD ) {
        if( event->button() == Qt::RightButton ) {
            if( plist.size() == 0 ) return;
            delete plist.back();
            plist.pop_back();
            delete flist.back();
            flist.pop_back();
        } else {
            plist.push_back( new QPoint( mx, my ) );
            add_frame();
        }
    } else if( mode == C_BOTTOM ) {
        if( event->button() == Qt::RightButton ) {
            if( btlist.size() == 0 ) return;
            delete btlist.back();
            btlist.pop_back();
        } else {
            btlist.push_back( new QPoint( mx, my ) );
        }
    } else if( mode == C_BALL ) {
        if( event->button() == Qt::RightButton ) {
            if( blist.size() == 0 ) return;
            delete blist.back();
            blist.pop_back();
        } else {
            blist.push_back( new QPoint( mx, my ) );
        }
    } else if( mode == C_DESK ) {
        if( event->button() == Qt::RightButton ) {
            if( dlist.size() == 0 ) return;
            delete dlist.back();
            dlist.pop_back();
        } else {
            dlist.push_back( new QPoint( mx, my ) );
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
    out << "#define BAND_SEGMENTS  " << flist.size() << "\n";
    
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
    
    out << "\n};\n\n";
    
    if( dlist.size() > 0 ) {
        
        out << "#define DESK_SEGMENTS " << dlist.size() << "\n\n";
        out << "struct tpoint {\n\tdouble x;\n\tdouble y;\n\tdouble tx;\n\tdouble ty;\n};\n\n";
        out << "static tpoint desk_data[] = {\n\t";
    
        double dmaxx = dlist[0]->x(), dmaxy = dlist[0]->y(), dminx = dmaxx, dminy = dmaxy;
        
        for( size_t i=0; i<dlist.size(); ++i ) {
            if( dlist[i]->x() < dminx ) dminx = dlist[i]->x();
            if( dlist[i]->y() < dminy ) dminy = dlist[i]->y();
            if( dlist[i]->x() > dmaxx ) dmaxx = dlist[i]->x();
            if( dlist[i]->x() > dmaxy ) dmaxy = dlist[i]->y();
        }
        
        double ccx, ccy;
        
        for( size_t i=0; i<dlist.size(); ++i ) {
            ccx = ((double)dlist[i]->x());
            ccy = ((double)dlist[i]->y());
            
            out << "{ " << (ccx-cx)/50.0 << ", " << (ccy-cy)/50.0 << ", ";
            out << (ccx-dminx)/(dmaxx-dminx) << ", " << (ccy-dminy)/(dmaxy-dminy) << " }, ";
            if( i && (i % 5) == 0 ) out << "\n\t";
        }
    
        out << "\n};\n\n";
    
    }
    
    out << "#define BALL_COUNT " << blist.size() << "\n\n";
    out << "static point ball_data[] = {\n\t";
    
    for( size_t i=0; i<blist.size(); ++i ) {
        out << "{ " << ((double)blist[i]->x()-cx)/50.0 << ", " << ((double)blist[i]->y()-cy)/50.0 << " }, ";
        if( i && (i % 5) == 0 ) out << "\n\t";
    }
    
    out << "\n};\n\n";
    
    out << "#define BOTTOM_SEGMENTS " << btlist.size() << "\n\n";
    out << "static point bottom_data[] = {\n\t";
    
    for( size_t i=0; i<btlist.size(); ++i ) {
        out << "{ " << ((double)btlist[i]->x()-cx)/50.0 << ", " << ((double)btlist[i]->y()-cy)/50.0 << " }, ";
        if( i && (i % 5) == 0 ) out << "\n\t";
    }
    
    out << "\n};\n\n";
    
    out << "static point band_data[] = {\n\t";
    
    for( size_t i=0; i<flist.size()-1; ++i ) {
        out << "{ " << ((double)flist[i]->x()-cx)/50.0 << ", " << ((double)flist[i]->y()-cy)/50.0 << " }, ";
        if( i && (i % 5) == 0 ) out << "\n\t";
    }
    
    out << "{ " << ((double)flist[0]->x()-cx)/50.0 << ", " << ((double)flist[0]->y()-cy)/50.0 << " }";
    
    out << "\n};\n\n#endif\n";
    
    file.close();
}

void Canvas::clear()
{
    for( size_t i=0; i<plist.size(); ++i ) {
        delete plist[i];
    }
    plist.clear();
    for( size_t i=0; i<flist.size(); ++i ) {
        delete flist[i];
    }
    flist.clear();
    for( size_t i=0; i<dlist.size(); ++i ) {
        delete dlist[i];
    }
    dlist.clear();
    for( size_t i=0; i<blist.size(); ++i ) {
        delete blist[i];
    }
    blist.clear();
    for( size_t i=0; i<blist.size(); ++i ) {
        delete btlist[i];
    }
    btlist.clear();
    update();
}
