#include "bconst.h"

double bConst::epsilon    = DEF_EPSILON;
double bConst::friction   = DEF_FRICT_F;
double bConst::springness = DEF_SPRING_F;

double bConst::get_epsilon()
{
    return epsilon;
}

double bConst::get_frict_f()
{
    return friction;
}

double bConst::get_spring_f()
{
    return springness;
}

void bConst::set_epsilon( double e )
{
    epsilon = e;
}

void bConst::set_frict_f( double f )
{
    friction = f;
}

void bConst::set_spring_f( double s )
{
    springness = s;
}
