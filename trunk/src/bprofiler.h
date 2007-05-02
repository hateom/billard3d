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


#ifndef B_PROFILER_H
#define B_PROFILER_H

#include "btypes.h"
#include "bsingleton.h"
#include "beventlistener.h"

#define SAMPLES_COUNT 50

#define Profiler bProfiler::get_singleton()

/**
    @author Tomasz Huczek & Andrzej Jasiñski <thuczek@gmail.com>
 */
class bProfiler: public bSingleton<bProfiler>
{
	struct pSample
	{
		bool valid;
		uint32 instances_count;
		uint32 open_profiles;
		char name[32];
		float start_time;
		float accumulator;
		float children_sample_time;
		uint32 parents_count;
	};

	struct pSampleHistory {
		bool valid;
		char name[32];
		float average;
		float min;
		float max;
	};

public:
	bProfiler();
	virtual ~bProfiler();

	void init();
	void start_frame();
	void begin( const char * name );
	void end( const char * name );

	void write( uint32 x, uint32 y, uint32 font );

	inline void on_off( bool flag ) { opened = flag; }
	inline bool is_opened() { return( opened ); }

protected:
	void StoreProfileHistory( const char * name, float percent );
	void GetProfileFromHistory( const char * name, float * ave, float * min, float * max );

private:
	pSample			sample[SAMPLES_COUNT];
	pSampleHistory	h_sample[SAMPLES_COUNT];

	float start_time;
	float end_time;
	float frame_start;
	bool opened;
};

#endif // B_PROFILER_H
