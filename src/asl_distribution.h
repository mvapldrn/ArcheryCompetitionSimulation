/*****************************************************************************
*** Name      : asl_distribution.h                                         ***
*** Purpose   : Several skill level distributions from real tournaments    ***
*** Author    : Marcel van Apeldoorn <mvapldrn@gmail.com>                  ***
*** Copyright : 2013-2021                                                  ***
***                                                                        ***
*** This file is part of ArcheryCompetitionSimulation.                     ***
***                                                                        ***
*** ArcheryCompetitionSimulation is free software: you can redistribute it ***
*** and/or modify it under the terms of the GNU General Public License as  ***
*** published by the Free Software Foundation, either version 3 of the     ***
*** License, or (at your option) any later version.                        ***
***                                                                        ***
*** ArcheryCompetitionSimulation is distributed in the hope that it will   ***
*** be useful, but WITHOUT ANY WARRANTY; without even the implied warranty ***
*** of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the       ***
*** GNU General Public License for more details.                           ***
***                                                                        ***
*** You should have received a copy of the GNU General Public License      ***
*** along with ArcheryCompetitionSimulation.  If not,                      ***
*** see <https://www.gnu.org/licenses/>.                                   ***
*****************************************************************************/

#ifndef _ASL_DISTRIBUTION_H
#define _ASL_DISTRIBUTION_H

#ifdef ASL_RM_70M_WC2019

#define POPULATION_FROM "ASL distribution for Recurve Men (2019 World Championships 's Hertogenbosch)"
#define ARROW_DIAMETER 5.0
double asl1   = 117.0;
double asl4   = 115.0;
double asl8   = 110.6;
double asl16  = 107.2;
double asl32  = 105.0;
double asl56  = 101.2;
double asl104 =  94.5;

#elif ASL_RW_70M_WC2019

#define POPULATION_FROM "ASL distribution for Recurve Women (2019 World Championship 's Hertogenbosch)"
#define ARROW_DIAMETER 5.0
double asl1   = 114.5;
double asl4   = 107.2;
double asl8   = 104.1;
double asl16  = 101.0;
double asl32  =  98.0;
double asl56  =  94.0;
double asl104 =  85.2;

#elif ASL_CM_50M_WC2019

#define POPULATION_FROM "ASL distribution for Compound Men Outdoor (2019 World Championships 's Hertogenbosch)"
#define ARROW_DIAMETER 4.5
double asl1   = 131.2;
double asl4   = 125.2;
double asl8   = 123.6;
double asl16  = 122.0;
double asl32  = 120.0;
double asl56  = 116.8;
double asl104 = 109.0;

#elif ASL_CM_50M_WCUP2023_4

#define POPULATION_FROM "ASL distribution for Compound Men Worldcup outdoor 2023 Paris"
#define ARROW_DIAMETER 4.5
double asl1   = 129.7;
double asl4   = 129.6;
double asl8   = 127.8;
double asl16  = 125.0;
double asl32  = 120.5;
double asl56  = 115.0;
double asl104 = 100.0;

#elif ASL_CW_50M_WCUP2023_4

#define POPULATION_FROM "ASL distribution for Compound Women Worldcup outdoor 2023 Paris"
#define ARROW_DIAMETER 4.5
double asl1   = 126.7;
double asl4   = 125.0;
double asl8   = 121.1;
double asl16  = 119.0;
double asl32  = 114.1;
double asl56  = 102.3;
double asl104 = 100.0;

#elif ASL_CM_18M_NIMES2017

#define POPULATION_FROM "ASL distribution for Compound Men Indoor (from Nimes 2017)"
#define ARROW_DIAMETER 9.3
double asl1   = 134.0;
double asl4   = 128.5;
double asl8   = 125.5;
double asl16  = 124.0;
double asl32  = 121.5;
double asl56  = 117.0;
double asl104 = 110.5;

#elif ASL_CW_18M_NIMES2017

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
