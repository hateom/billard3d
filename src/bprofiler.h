#ifndef __B_PROFILER_H__
#define __B_PROFILER_H__

#include "btypes.h"
#include "bsingleton.h"

#define SAMPLES_COUNT 50

#define Profiler bProfiler::get_singleton()

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

#endif // __B_PROFILER_H__
