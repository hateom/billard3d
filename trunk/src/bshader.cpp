/***************************************************************************
 *   Copyright (C) 2007 by                                       *
 *                                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/

#include "bshader.h"
#include "bgl.h"
#include "bassert.h"
#include "btrace.h"
#include "blogger.h"
#include <cstdio>
#include <cstring>

bool bShader::s_enabled = true;

bShader::bShader()
{
}

bShader::~bShader()
{
}

bool bShader::is_supported()
{
    return glewIsSupported("GL_ARB_fragment_program") && glewIsSupported("GL_ARB_vertex_program");
}

void bShader::enable( bProgram p )
{
    if( !is_enabled() ) return;
    
    if( p & B_FRAGMENT ) cgGLEnableProfile( fprofile );
    if( p & B_VERTEX )   cgGLEnableProfile( vprofile );
}

void bShader::disable( bProgram p )
{
    if( !is_enabled() ) return;
    
    if( p & B_FRAGMENT ) cgGLDisableProfile( fprofile );
    if( p & B_VERTEX )   cgGLDisableProfile( vprofile );
}

void bShader::bind( bProgram p )
{
    guard(bShader::bind);
    
    if( !is_supported() ) return;
    
    if( p & B_FRAGMENT ) { cgGLBindProgram( fprogram ); }
    if( p & B_VERTEX )   { cgGLBindProgram( vprogram ); }
    
    unguard;
}

void bShader::release()
{
    if( !is_enabled() ) return;
    
    if( vprogram ) { cgDestroyProgram( vprogram ); vprogram = 0; }
    if( vcontext ) { cgDestroyContext( vcontext ); vcontext = 0; }
    
    if( fprogram ) { cgDestroyProgram( fprogram ); fprogram = 0; }
    if( fcontext ) { cgDestroyContext( fcontext ); fcontext = 0; }
}

bool bShader::load_fragment( const char * filename )
{
    guard(bShader::load_fragment);
    
    if( !is_enabled() ) return false;
    
    if( cgGLIsProfileSupported( CG_PROFILE_ARBFP1 ) ) {
        fprofile = CG_PROFILE_ARBFP1;
    } else if( cgGLIsProfileSupported( CG_PROFILE_FP20 ) ) {
        fprofile = CG_PROFILE_FP20;
    } else {
        BLOG("Vertex programming extensions (GL_ARB_vertex_program or GL_NV_vertex_program) not supported!\n");
        return false ;
    }
    
    char * cgfragprog;
    cgfragprog = load_string( filename );
    
    if( !cgfragprog ) return false;
    
    fcontext = cgCreateContext();
    if( !fcontext ) return false;
        
    fprogram = cgCreateProgram( fcontext, CG_SOURCE, cgfragprog, fprofile, NULL, NULL );
    if( !fprogram ) return false;

	//BLOG( "-- Fragment Program:\n");
	//BLOG( "[[\n%s\n]]\n", cgGetProgramString( fprogram, CG_COMPILED_PROGRAM ) );

    cgGLLoadProgram( fprogram );
    
    return true;
    
    unguard;
}

bool bShader::load_vertex( const char * filename )
{
    guard(bShader::load_vertex);
    
    if( !is_enabled() ) return false;
    
    if( cgGLIsProfileSupported( CG_PROFILE_ARBVP1 ) ) {
        vprofile = CG_PROFILE_ARBVP1;
    } else if( cgGLIsProfileSupported( CG_PROFILE_VP20 ) ) {
        vprofile = CG_PROFILE_VP20;
    } else {
        BLOG("Vertex programming extensions (GL_ARB_vertex_program or GL_NV_vertex_program) not supported!\n");
        return false ;
    }
    
    char * cgvertprog;
    cgvertprog = load_string( filename );
    
    if( !cgvertprog ) return false;
    
    vcontext = cgCreateContext();
    if( !vcontext ) return false;
    
    vprogram = cgCreateProgram( vcontext, CG_SOURCE, cgvertprog, vprofile, NULL, NULL );
    if( !vprogram ) return false;
    
	//BLOG( "-- Vertex Program:\n");
    //BLOG( "[[\n%s\n]]\n", cgGetProgramString( vprogram, CG_COMPILED_PROGRAM ) );
    
    cgGLLoadProgram( vprogram );
    
    mvp  = cgGetNamedParameter( vprogram, "ModelViewProj");
    mv   = cgGetNamedParameter( vprogram, "ModelView");
    mp   = cgGetNamedParameter( vprogram, "ModelProj");
    mvi  = cgGetNamedParameter( vprogram, "ModelViewI");
    mvit = cgGetNamedParameter( vprogram, "ModelViewIT");
    
    if( !mvp || !mv || !mp || !mvi || !mvit ) {
        BLOG( "!! shader data not loaded!\n" );
    }
    
    return true;
    
    unguard;
}

char * bShader::load_string(const char * filename)
{
    static char program_string[16384];
    FILE *fp;
    size_t len;

    fp = fopen(filename, "r");
    if(!fp) return NULL;

    len = fread(program_string, 1, 16384, fp);
    program_string[len] = '\0';
    fclose(fp);

    return program_string;
}

void bShader::set_matrices()
{
    if( !is_enabled() ) return;
    
    cgGLSetStateMatrixParameter( mvp,  CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY );
    cgGLSetStateMatrixParameter( mv,   CG_GL_MODELVIEW_MATRIX, CG_GL_MATRIX_IDENTITY );
    cgGLSetStateMatrixParameter( mp,   CG_GL_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY );
    cgGLSetStateMatrixParameter( mvi,  CG_GL_MODELVIEW_MATRIX, CG_GL_MATRIX_INVERSE );
    cgGLSetStateMatrixParameter( mvit, CG_GL_MODELVIEW_MATRIX, CG_GL_MATRIX_INVERSE_TRANSPOSE );
}

