/*****************************************************************************
*** Name      : stats.h                                                    ***
*** Purpose   : Implements a helper for keeping mean/variance              ***
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

#ifndef _STATS_H
#define _STATS_H

/* --- Constants {{{1 */

/* --- Data types {{{1 */

/*
 * Keep a mean and variance of a statistical value in an updateable fashion
 * I.e. every timestep, K, Ex and Ex2 get updated and at the end,
 * mean and variance can be computed
 */
typedef struct {
    long   n;                   /* Number of values                         */
    double val;                 /* Most recent value                        */
    double avg;                 /* Running mean/average of all values       */
    double var;                 /* Running variance of all values           */
    double stdev;               /* Running standard deviation of all values */
} Stat;

/* --- Interface {{{1 */

void resetStat(Stat *stat);
void addStat(Stat *stat, double value);

#endif
