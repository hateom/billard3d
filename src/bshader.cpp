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
    if( p & B_FRAGMENT ) cgGLEnableProfile( fprofile );
    if( p & B_VERTEX )   cgGLEnableProfile( vprofile );
}

void bShader::disable( bProgram p )
{
    if( p & B_FRAGMENT ) cgGLDisableProfile( fprofile );
    if( p & B_VERTEX )   cgGLDisableProfile( vprofile );
}

void bShader::bind( bProgram p )
{
    guard(bShader::bind);
    
    BASSERTM( is_supported(), "Shaders aint supported, dude!" );
    
    if( p & B_FRAGMENT ) { cgGLBindProgram( fprogram ); }
    if( p & B_VERTEX )   { cgGLBindProgram( vprogram ); }
    
    unguard;
}

void bShader::release()
{
    if( vprogram ) { cgDestroyProgram( vprogram ); vprogram = 0; }
    if( vcontext ) { cgDestroyContext( vcontext ); vcontext = 0; }
    
    if( fprogram ) { cgDestroyProgram( fprogram ); fprogram = 0; }
    if( fcontext ) { cgDestroyContext( fcontext ); fcontext = 0; }
}

bool bShader::load_fragment( const char * filename )
{
    guard(bShader::load_fragment);
    
    BASSERTM( is_supported(), "Shaders aint supported, dude!" );
    
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
    fprogram = cgCreateProgram( fcontext, CG_SOURCE, cgfragprog, fprofile, NULL, NULL );
    cgGLLoadProgram( fprogram );
    
    return true;
    
    unguard;
}

bool bShader::load_vertex( const char * filename )
{
    guard(bShader::load_vertex);
    
    BASSERTM( is_supported(), "Shaders aint supported, dude!" );
    
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
    vprogram = cgCreateProgram( vcontext, CG_SOURCE, cgvertprog, vprofile, NULL, NULL );
    
    BLOG( "[[\n%s\n]]\n", cgGetProgramString( vprogram, CG_COMPILED_PROGRAM ) );
    
    cgGLLoadProgram( vprogram );
    
    mvp   = cgGetNamedParameter( vprogram, "ModelViewProj");
    mv    = cgGetNamedParameter( vprogram, "ModelView");
    if( !mvp || !mv ) {
        BLOG( "!! shader data not loaded!\n" );
    }
    
    return true;
    
    unguard;
}

char * bShader::load_string(const char * filename)
{
    static char program_string[16384];
    FILE *fp;
    unsigned int len;

    fp = fopen(filename, "r");
    if(!fp) return NULL;

    len = fread(program_string, 1, 16384, fp);
    program_string[len] = '\0';
    fclose(fp);

    return program_string;
}

void bShader::set_matrices()
{
    cgGLSetStateMatrixParameter( mvp,  CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY );
    cgGLSetStateMatrixParameter( mv,   CG_GL_MODELVIEW_MATRIX, CG_GL_MATRIX_IDENTITY );
}

