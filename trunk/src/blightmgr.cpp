#include "blightmgr.h"
#include "bsdl.h"

float bLightMgr::lamb[] = { 0.5f, 0.5f,   0.5f, 1.0f };
float bLightMgr::ldif[] = { 0.8f, 0.8f,   0.8f, 1.0f };
float bLightMgr::lpos[] = { 10.f, 100.0f, 40.0f, 1.0f };

void bLightMgr::set_defaults()
{
	glEnable( GL_LIGHTING );
	glLightfv( GL_LIGHT0, GL_AMBIENT, lamb );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, ldif );
	glLightfv( GL_LIGHT0, GL_POSITION, lpos );
	glEnable( GL_LIGHT0 );
	glEnable( GL_COLOR_MATERIAL );
	glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
}

void bLightMgr::on()
{
	glEnable( GL_LIGHTING );
}

void bLightMgr::off()
{
	glDisable( GL_LIGHTING );
}
