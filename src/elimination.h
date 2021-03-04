/*****************************************************************************
*** Name      : elimination.h                                              ***
*** Purpose   : Defines the elimination phase routines                     ***
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

#ifndef _ELIMINATION_H
#define _ELIMINATION_H

/* --- Includes {{{1 */
#include "archer.h"
#include "score.h"
#include "format.h"

#define MAX_SETS 10

#define F48TH    6
#define F24TH    5
#define F16TH    4
#define F8TH     3
#define F4TH     2
#define FSEMI    1
#define FGOLD    0
#define FBRONZE  0

#define MAX_STAGES 7

typedef struct {
    /* Total number of competitions simulated */
    long n_competitions;

    /* Total number of matches in each stage simulated */
    long n_matches[MAX_STAGES];

    /* Number of wins per stage and per number of sets */
    Stat n_win_after_sets[MAX_SETS][MAX_STAGES];

    /* Number of wins that required shootoff */
    Stat n_win_after_shootoff[MAX_STAGES];

    /* Number of wins without shootoff but with equal cumulative score (set system, this is possible) */
    Stat n_win_with_equal_score_no_so[MAX_STAGES];

    /* Number of wins with lower cumulative score (with set system this is possible) */
    Stat n_win_with_lower_score[MAX_STAGES];

    /*
     * 'Expected' is defined as; archer with Q rank X, wins 1/X stage
     *
     *            1/48 1/24 1/16  1/8  1/4  1/2  F/FB
     * Q 1 -  8    V    V    V    V    -    -    -
     *   9 - 16    V    V    V    -    -    -    -
     *  17 - 32    V    V    -    -    -    -    -
     *  33 - 56    V    -    -    -    -    -    -
     *  57 -104    -    -    -    -    -    -    -
     */
    Stat n_expected_wins[MAX_STAGES];

    /* Number that qualified top 4 and ends in top 4 */
    Stat n_top_q4_e4;

    /* Number that qualified top 8 and ends in top 8 */
    Stat n_top_q8_e8;

    /* Number that qualified top 16 and ends in top 16 */
    Stat n_top_q16_e16;;

    /* How often did we need a second shootoff */
    Stat n_second_shootoff_required[MAX_STAGES];

    /* Final ranking fitness function */
    Stat fc;
} EliminationStatistics;

/* --- Interface {{{1 */

extern int e_nruns;

void initEliminationStats(void);
void doEliminationRound(void);
void doTeamEliminationRound(void);
void computeEliminationStats(void);
void computeTeamEliminationStats(void);
void computeMixedTeamEliminationStats(void);
void dumpEliminationStats();

#endif
