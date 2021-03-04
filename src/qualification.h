/*****************************************************************************
*** Name      : qualification.h                                            ***
*** Purpose   : Defines the qualification round routines                   ***
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

#ifndef _QUALIFICATION_H
#define _QUALIFICATION_H

/* --- Includes {{{1 */

#include "format.h"
#include "stats.h"

/* --- Types {{{1 */

typedef struct {
    /* Total number of qualification run */
    int          n;

    /* Number of ties in qualification */
    Stat         n_ties;

    /* Qualification ranking fitness function */
    Stat         fc;
} QualificationStatistics;

/* --- Interface {{{1 */

extern int q_nruns;

void initQualificationStats(void);
void doQualificationRound(void);
void doQualificationRounds(int n);
void doTeamQualificationRound(void);
void dumpQualificationStats();

#endif
