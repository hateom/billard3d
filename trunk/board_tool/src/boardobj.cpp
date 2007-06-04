#include "boardobj.h"
#include <QFile>

BoardObject::BoardObject()
{
}

BoardObject::~BoardObject()
{
}

bool BoardObject::load( const char * filename )
{
    release();
    
    QFile file(filename);
    if( !file.open( QIODevice::ReadOnly )) {
        return false;
    }
    
    size_t size;
    int cx, cy;
    
    file.read( (char*)&cx, sizeof(int) );
    file.read( (char*)&cy, sizeof(int) );
    
    file.read( (char*)&size, sizeof(size_t) );
    for( size_t i=0; i<size; ++i ) {
        double x, y;
        file.read( (char*)&x, sizeof(double) );
        file.read( (char*)&y, sizeof(double) );
        plist.push_back( new QPoint( (int)(x*50.0)+cx, (int)(y*50.0)+cy ) );
    }
    
    size = flist.size();
    file.read( (char*)&size, sizeof(size_t) );
    for( size_t i=0; i<size; ++i ) {
        double x, y;
        file.read( (char*)&x, sizeof(double) );
        file.read( (char*)&y, sizeof(double) );
        flist.push_back( new QPoint( (int)(x*50.0)+cx, (int)(y*50.0)+cy ) );
    }
    
    size = dlist.size();
    file.read( (char*)&size, sizeof(size_t) );
    
    for( size_t i=0; i<size; ++i ) {
        double x, y, temp;
        file.read( (char*)&x, sizeof(double) );
        file.read( (char*)&y, sizeof(double) );
        file.read( (char*)&temp, sizeof(double) );
        file.read( (char*)&temp, sizeof(double) );
        dlist.push_back( new QPoint( (int)(x*50.0)+cx, (int)(y*50.0)+cy ) );
    }
    
    size = blist.size();
    file.read( (char*)&size, sizeof(size_t) );
    for( size_t i=0; i<size; ++i ) {
        double x, y;
        file.read( (char*)&x, sizeof(double) );
        file.read( (char*)&y, sizeof(double) );
        blist.push_back( new QPoint( (int)(x*50.0)+cx, (int)(y*50.0)+cy ) );
    }
    
    size = btlist.size();
    file.read( (char*)&size, sizeof(size_t) );
    for( size_t i=0; i<size; ++i ) {
        double x, y;
        file.read( (char*)&x, sizeof(double) );
        file.read( (char*)&y, sizeof(double) );
        btlist.push_back( new QPoint( (int)(x*50.0)+cx, (int)(y*50.0)+cy ) );
    }
    
    file.close();
    
    return true;
}

bool BoardObject::save( const char * filename )
{
    QFile file(filename);
    if( !file.open( QIODevice::WriteOnly )) {
        return false;
    }
    
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
    
    file.write( (const char*)&cx, sizeof(int) );
    file.write( (const char*)&cy, sizeof(int) );
    
    size_t size;
    
    size = plist.size();
    file.write( (const char*)&size, sizeof(size_t) );
    for( size_t i=0; i<size; ++i ) {
        double x, y;
        x = ((double)plist[i]->x()-cx)/50.0;
        y = ((double)plist[i]->y()-cy)/50.0;
        file.write( (const char*)&x, sizeof(double) );
        file.write( (const char*)&y, sizeof(double) );
    }
    
    size = flist.size();
    file.write( (const char*)&size, sizeof(size_t) );
    for( size_t i=0; i<size; ++i ) {
        double x, y;
        x = ((double)flist[i]->x()-cx)/50.0;
        y = ((double)flist[i]->y()-cy)/50.0;
        file.write( (const char*)&x, sizeof(double) );
        file.write( (const char*)&y, sizeof(double) );
    }
    
    size = dlist.size();
    file.write( (const char*)&size, sizeof(size_t) );
    
    double dmaxx = dlist[0]->x(), dmaxy = dlist[0]->y(), dminx = dmaxx, dminy = dmaxy;
        
    for( size_t i=0; i<dlist.size(); ++i ) {
        if( dlist[i]->x() < dminx ) dminx = dlist[i]->x();
        if( dlist[i]->y() < dminy ) dminy = dlist[i]->y();
        if( dlist[i]->x() > dmaxx ) dmaxx = dlist[i]->x();
        if( dlist[i]->x() > dmaxy ) dmaxy = dlist[i]->y();
    }
    
    for( size_t i=0; i<size; ++i ) {
        double x, y, tx, ty;
        x = ((double)dlist[i]->x()-cx)/50.0;
        y = ((double)dlist[i]->y()-cy)/50.0;
        file.write( (const char*)&x, sizeof(double) );
        file.write( (const char*)&y, sizeof(double) );
        tx = ((double)dlist[i]->x()-dminx)/(dmaxx-dminx);
        ty = ((double)dlist[i]->y()-dminy)/(dmaxy-dminy);
        file.write( (const char*)&tx, sizeof(double) );
        file.write( (const char*)&ty, sizeof(double) );
    }
    
    size = blist.size();
    file.write( (const char*)&size, sizeof(size_t) );
    for( size_t i=0; i<size; ++i ) {
        double x, y;
        x = ((double)blist[i]->x()-cx)/50.0;
        y = ((double)blist[i]->y()-cy)/50.0;
        file.write( (const char*)&x, sizeof(double) );
        file.write( (const char*)&y, sizeof(double) );
    }
    
    size = btlist.size();
    file.write( (const char*)&size, sizeof(size_t) );
    for( size_t i=0; i<size; ++i ) {
        double x, y;
        x = ((double)btlist[i]->x()-cx)/50.0;
        y = ((double)btlist[i]->y()-cy)/50.0;
        file.write( (const char*)&x, sizeof(double) );
        file.write( (const char*)&y, sizeof(double) );
    }
    
    file.close();
    
    return true;
}

void BoardObject::release()
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
}
