/*****************************************************************************
*** Name      : mixedteam.c                                                ***
*** Purpose   : Defines the mixedteam types and routines                   ***
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

/* --- Includes {{{1 */
#include <stdio.h>

#include "dump.h"
#include "mixedteam.h"
#include "archer.h"

/* --- Global data {{{1 */

MixedTeam  mixedteam[24];
MixedTeam *mixedteamrank[24];

extern int pretty_print;

/* --- Local prototypes {{{1*/

/* --- Implementation {{{1*/

void setMixedTeam(MixedTeam *mixedteam, double lvl[2]) /*{{{2*/
{
    int i;

    setArcher(&(mixedteam->archer[0]), 1, lvl[0]);
    setArcher(&(mixedteam->archer[1]), 2, lvl[1]);
    mixedteam->q_rank = 0;
    mixedteam->e_rank = 0;
} /*}}}2*/

void setMixedTeams(double lvl_1[2], double lvl_4[2], double lvl_8[2], double lvl_16[2], double lvl_24[2]) /*{{{2*/
/*
 * Setup an array of teams with different skill levels
 * where;
 * lvl_1    = array of level of archers of highest ranked mixedteam
 * lvl_4    = array of level of archers of 4th ranked mixedteam
 * lvl_8    = array of level of archers of 8th ranked mixedteam
 * lvl_16   = array of level of archers of 16th ranked mixedteam
 * lvl_24   = array of level of archers of 24th ranked mixedteam
 *
 * Returns nothing, but fills the archers array
 */
{
    double lvl[2];
    double dlvl[2];
    int i, j;

    /* team 1..4 */
    dlvl[0] = (lvl_1[0]-lvl_4[0])/3.0;
    dlvl[1] = (lvl_1[1]-lvl_4[1])/3.0;
    for (i = 0; i < 4; i++) {
        lvl[0] = lvl_1[0] - i*dlvl[0];
        lvl[1] = lvl_1[1] - i*dlvl[1];
        setMixedTeam(&mixedteam[i], lvl);
    }

    /* team 5..8 */
    dlvl[0] = (lvl_4[0]-lvl_8[0])/3.0;
    dlvl[1] = (lvl_4[1]-lvl_8[1])/3.0;
    for (i = 4; i < 8; i++) {
        lvl[0] = lvl_4[0] - (i-4)*dlvl[0];
        lvl[1] = lvl_4[1] - (i-4)*dlvl[1];
        setMixedTeam(&mixedteam[i], lvl);
    }

    /* 9..16 */
    dlvl[0] = (lvl_8[0]-lvl_16[0])/8.0;
    dlvl[1] = (lvl_8[1]-lvl_16[1])/8.0;
    for (i = 8; i < 16; i++) {
        lvl[0] = lvl_8[0] - (i-8)*dlvl[0];
        lvl[1] = lvl_8[1] - (i-8)*dlvl[1];
        setMixedTeam(&mixedteam[i], lvl);
    }

    /* 17..24 */
    dlvl[0] = (lvl_16[0]-lvl_24[0])/8.0;
    dlvl[1] = (lvl_16[1]-lvl_24[1])/8.0;
    for (i = 16; i < 24; i++) {
        lvl[0] = lvl_8[0] - (i-16)*dlvl[0];
        lvl[1] = lvl_8[1] - (i-16)*dlvl[1];
        setMixedTeam(&mixedteam[i], lvl);
    }
} /*}}}2*/

double getMixedTeamScore(const MixedTeam *mixedteam) /*{{{2*/
{
    return mixedteam->archer[0].q_score + mixedteam->archer[1].q_score;
} /*}}}2*/

void dumpMixedTeam(const MixedTeam *mixedteam) /*{{{2*/
{
    if (mixedteam == NULL) {
        /* Forced to dump header */
        if (pretty_print) {
            outp("\n  Qualification round results\n");
            outp("================================\n");
            outp("| Q Rank |   | E Rank |  Score |\n");
            outp("+--------+---+--------+--------+\n");
        /*        |   XXX  | + |   XXX  |  XXXXX.XX (XXXX.X, XXXX.X, XXXX.X) | */
        }
        else {
            outp("\"Results\"\n");
            outp("\"q-rank\";\"up-down\";\"e-rank\";\"score\";\"archer1\";\"archer2\"\n");
        }
        return;
    }

    if (pretty_print) {
        outp("|   %3d  | %s |   %3d  |  %8.2lf (%6.1lf, %6.1lf) |\n",
                mixedteam->q_rank, ' ', mixedteam->e_rank, getMixedTeamScore(mixedteam),
                mixedteam->archer[0].q_score, mixedteam->archer[1].q_score);
    }
    else {
        outp("%d;\"%s\";%d;%lf;%lf;%lf\n",
               mixedteam->q_rank, ' ', mixedteam->e_rank, getMixedTeamScore(mixedteam),
               mixedteam->archer[0].q_score, mixedteam->archer[1].q_score);
    }
} /*}}}2*/

void rankMixedTeams(int from_rank, int to_rank) /*{{{2*/
{
    int i, j;
    int start_idx = from_rank-1;
    int end_idx = to_rank-1;
    MixedTeam *tmp, *max;
    int j_found = 0;

    for (i = start_idx; i <= end_idx; i++) {
        max = NULL;
        for (j = i; j <= end_idx; j++) {
            if ( (max == NULL) ||
                 (getMixedTeamScore(mixedteamrank[j]) > getMixedTeamScore(max)) )
            {
                max = mixedteamrank[j];
                j_found = j;
            }
        }
        /* swap */
        tmp = mixedteamrank[i];
        mixedteamrank[i] = max;
        mixedteamrank[j_found] = tmp;
    }
} /*}}}2*/

/* --- Local functions {{{1 */


