#ifndef __BOARD_OBJECT_H__
#define __BOARD_OBJECT_H__

#include <QPoint>
#include <vector>

typedef std::vector<QPoint*> pVector;
typedef std::vector<QPoint*>::iterator pIter;

class BoardObject
{
public:
    BoardObject();
    ~BoardObject();

    bool load( const char * filename );
    bool save( const char * filename );

    void release();
    
public:
    pVector plist; // board band points
    pVector flist; // board borders (frame)
    pVector dlist; // desk
    pVector blist; // balls
    pVector btlist;// board bottom
};

#endif // __BOARD_OBJECT_H__

