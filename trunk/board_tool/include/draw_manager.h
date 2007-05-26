#ifndef __DRAW_MANAGER_H__
#define __DRAW_MANAGER_H__

#include "canvas.h"

#define getDrawManager DrawManager::get_singleton()
#define MRGB(r,g,b)          ((((unsigned char)(r)|((unsigned short)((unsigned char)(g))<<8))|(((unsigned int)(unsigned char)(b))<<16)))

class DrawManager
{
	Canvas * canvas;

	DrawManager() : canvas(NULL) {}
	~DrawManager() {}

public:
	void init( Canvas * canvas );
	void release();

	void draw( int x, int y, unsigned long rgb );
	void update() { if( canvas ) canvas->update(); }

	static DrawManager & get_singleton() {
		static DrawManager g_mgr;
		return g_mgr;
	}
};

#endif // __DRAW_MANAGER_H__
