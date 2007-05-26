#include "draw_manager.h"

void DrawManager::init( Canvas * i_canvas )
{
	canvas = i_canvas;
}

void DrawManager::release()
{
	canvas = NULL;
}

void DrawManager::draw( int x, int y, unsigned long rgb )
{
	if( !canvas ) return;
	canvas->set_pixel( x, y, rgb );
}
