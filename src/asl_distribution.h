/*****************************************************************************
*** Name      : asl_distribution.h                                         ***
*** Purpose   : Several skill level distributions from real tournaments    ***
*** Author    : Marcel van Apeldoorn <mvapldrn@gmail.com>                  ***
*** Copyright : 2013                                                       ***
*****************************************************************************/

#ifndef _ASL_DISTRIBUTION_H
#define _ASL_DISTRIBUTION_H

#ifdef ASL_RM

#define POPULATION_FROM "ASL distribution for Recurve Men"
#define ARROW_DIAMETER 5.0
double asl1   = 118.0;
double asl8   = 105.8;
double asl16  = 101.9;
double asl32  =  99.3;
double asl56  =  95.0;
double asl104 =  82.0;

#elif ASL_RW

#define POPULATION_FROM "ASL distribution for Recurve Women"
#define ARROW_DIAMETER 5.0
double asl1   = 108.0;
double asl8   = 101.9;
double asl16  =  97.1;
double asl32  =  92.8;
double asl56  =  89.2;
double asl104 =  73.7;

#elif ASL_CM_INDOOR

#define POPULATION_FROM "ASL distribution for Compound Men Indoor (from Nimes 2017)"
#define ARROW_DIAMETER 9.3
double asl1   = 134.0;
double asl4   = 128.5;
double asl8   = 125.5;
double asl16  = 124.0;
double asl32  = 121.5;
double asl56  = 117.0;
double asl104 = 110.5;

#elif ASL_CM_OUTDOOR

#define POPULATION_FROM "ASL distribution for Compound Men Outdoor (2019 World Championships 's Hertogenbosch)"
#define ARROW_DIAMETER 4.5
double asl1   = 131.2;
double asl4   = 125.2;
double asl8   = 123.6;
double asl16  = 122.0;
double asl32  = 120.0;
double asl56  = 116.8;
double asl104 = 109.0;

#elif ASL_CW_INDOOR

#define POPULATION_FROM "ASL distribution for Compound Women Indoor (from Nimes 2017)"
#define ARROW_DIAMETER 9.3
double asl1   = 123.0;
double asl4   = 120.0;
double asl8   = 118.0;
double asl16  = 114.5;
double asl32  = 108.5;
double asl56  = 100.0;
double asl104 =  64.0;

#endif

#define TEAM_POPULATION_FROM "Default team distribution"
double t1asl1 = 105.0;
double t1asl2 = 100.0;
double t1asl3 =  97.0;
double t2asl1 = 105.0;
double t2asl2 =  96.0;
double t2asl3 =  95.0;

#define MIXEDTEAM_POPULATION_FROM "Default mixedteam distribution"
double xt1asl1 = 118.0;
double xt1asl2 = 108.0;
double xt2asl1 = 106.0;
double xt2asl2 = 101.0;

#endif
