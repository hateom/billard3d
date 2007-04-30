#include "bprofiler.h"
#include "bfontmgr.h"
#include "bsdl.h"
#include "btrace.h"

#define HSPC 10

#ifdef WIN32
#include <windows.h>
#else
#include <sys/times.h>
#endif

inline float GetTime()
{
#ifdef WIN32
    return (float)GetTickCount();
#else
    tms tm;
    return (float)times(&tm);
#endif
}

bProfiler::bProfiler()
{
}

bProfiler::~bProfiler()
{
}

void bProfiler::init()
{
    guard(bProfiler::init);
    
	for( uint32 i=0; i<SAMPLES_COUNT; ++i )
	{
		sample[i].valid = false;
		h_sample[i].valid = false;
	}

	start_time = GetTime();
	opened = false;
    
    unguard;
}

void bProfiler::begin( const char * name )
{
    guard(bProfiler::begin);
    
	uint32 i = 0L;

	while( i < SAMPLES_COUNT && sample[i].valid == true )
	{
		if( strcmp( sample[i].name, name ) == 0 )
		{
			sample[i].open_profiles++;
			sample[i].instances_count++;
			sample[i].start_time = GetTime();
			BASSERT( sample[i].open_profiles == 1 );

			return;
		}
		++i;
	}

	if( i >= SAMPLES_COUNT )
	{
		BASSERT( !"Przekroczyles dopuszczalna ilosc probek!" );
		return;
	}

	strcpy( sample[i].name, name );
	sample[i].valid = true;
	sample[i].open_profiles = 1;
	sample[i].parents_count = 1;
	sample[i].accumulator = 0;
	sample[i].start_time = GetTime();
	sample[i].children_sample_time = 0;
    
    unguard;
}

void bProfiler::end( const char * name )
{
    guard(bProfiler::end);
    
	uint32 i = 0L;
	uint32 parents_count = 0L;

	while( i < SAMPLES_COUNT && sample[i].valid == true )
	{
		if( strcmp( sample[i].name, name ) == 0 )
		{
			uint32 inner = 0L;
			int parent = -1;
			float end_time = GetTime();
			sample[i].open_profiles--;

			while( sample[inner].valid == true )
			{
				if( sample[inner].open_profiles > 0 )
				{
					parents_count++;
					if( parent < 0 )
					{
						parent = inner;
					}
					else if( sample[inner].start_time >= sample[parent].start_time )
					{
						parent = inner;
					}
				}
				inner++;
			}
			sample[i].parents_count = parents_count;

			if( parent >= 0 )
			{
				sample[parent].children_sample_time += end_time - sample[i].start_time;
			}

			sample[i].accumulator += end_time - sample[i].start_time;
			return;
		}
		++i;
	}
    
    unguard;
}

void bProfiler::start_frame()
{
	frame_start = GetTime();
}

void bProfiler::StoreProfileHistory( const char * name, float percent )
{
    guard(bfProfiler::StoreProfileHistory);
    
	uint32 i = 0L;
	float old_ratio;
	float new_ratio = 0.8f * (GetTime()-frame_start);
	if( new_ratio > 1.0f )
	{
		new_ratio = 1.0f;
	}
	old_ratio = 1.0f - new_ratio;

	while( i < SAMPLES_COUNT && h_sample[i].valid == true )
	{
		if( strcmp( h_sample[i].name, name ) == 0 )
		{
			h_sample[i].average = (h_sample[i].average * old_ratio) + (percent*new_ratio);
			if( percent < h_sample[i].min )
			{
				h_sample[i].min = percent;
			}
			else
			{
				h_sample[i].min = (h_sample[i].min*old_ratio) + (percent*new_ratio);
			}

			if( h_sample[i].min < 0.0f )
			{
				h_sample[i].min = 0.0f;
			}

			if( percent > h_sample[i].max )
			{
				h_sample[i].max = percent;
			}
			else
			{
				h_sample[i].max = (h_sample[i].max*old_ratio) + (percent*new_ratio);
			}

			return;
		}
		++i;
	}

	if( i < SAMPLES_COUNT )
	{
		strcpy( h_sample[i].name, name );
		h_sample[i].valid = true;
		h_sample[i].average = h_sample[i].min = h_sample[i].max = percent;
	}
	else
	{
		BASSERT( !"Przekroczono maxymalna liczbe probek!" );
		return;
	}
    
    unguard;
}

void bProfiler::GetProfileFromHistory( const char * name, float * ave, float * min, float * max )
{
    guard(bfProfiler::GetProfileFromHistory);
    
	uint32 i = 0L;

	while( i < SAMPLES_COUNT && h_sample[i].valid == true )
	{
		if( strcmp( h_sample[i].name, name ) == 0 )
		{
			*ave = h_sample[i].average;
			*min = h_sample[i].min;
			*max = h_sample[i].max;
			return;
		}
		++i;
	}
	*ave = *min = *max = 0.0f;
    
    unguard;
}

void bProfiler::write( uint32 x, uint32 y, uint32 font )
{
    guard(bProfiler::write);
    
	if( !opened ) return;

	uint32 i = 0L;

	end_time = GetTime();

	PRINT( x, y, font, "B3D Profiler by deely" );
	y += 16;
	PRINTS(     x, y, font, "ave" );
    PRINTS(  x+32, y, font, "min" );
    PRINTS(  x+64, y, font, "max" );
    PRINTS(  x+96, y, font, "num" );
    PRINTS( x+128, y, font, "name" );
    y += HSPC;

	while( i < SAMPLES_COUNT && sample[i].valid == true )
	{
		uint32 ident = 0L;
		float sample_time, percent_time, ave_time, min_time, max_time;
		char /*line[128],*/ name[32], idented_name[32];
		char ave[16], min[16], max[16], num[16];

		if( sample[i].open_profiles < 0 )
		{
			BASSERT( !"End() wywolane bez Begin()!" );
			return;
		}
		else if( sample[i].open_profiles > 0 )
		{
			BASSERT( !"Begin() wywolane bez End()!" );
			return;
		}

		sample_time = sample[i].accumulator - sample[i].children_sample_time;
		percent_time = (sample_time/(end_time-start_time)) * 100.0f;

		ave_time = min_time = max_time = percent_time;

		StoreProfileHistory( sample[i].name, percent_time );
		GetProfileFromHistory( sample[i].name, &ave_time, &min_time, &max_time );

		sprintf( ave, "%3.1f", ave_time );
		sprintf( min, "%3.1f", min_time );
		sprintf( max, "%3.1f", max_time );
		sprintf( num, "%3d", (int)sample[i].parents_count );

		strcpy( idented_name, sample[i].name );

		for( ident = 0; ident<sample[i].parents_count; ++ident )
		{
			sprintf( name, "    %s", idented_name );
			strcpy( idented_name, name );
		}

        PRINTS(     x, y, font, ave );
        PRINTS(  x+32, y, font, min );
        PRINTS(  x+64, y, font, max );
        PRINTS(  x+96, y, font, num );
        PRINTS( x+128, y, font, idented_name );

        y += HSPC;
		++i;
	}
    
    unguard;
}
