/*****************************************************************************
*** Name      : team.c                                                     ***
*** Purpose   : Defines the team types and routines                        ***
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
#include <math.h>

#include "dump.h"
#include "team.h"
#include "archer.h"

/* --- Global data {{{1 */

Team  team[16];
Team *teamrank[16];

extern int pretty_print;

/* --- Local prototypes {{{1*/

/* --- Implementation {{{1*/

void setTeam(Team *team, double lvl[3]) /*{{{2*/
{
    int i;

    setArcher(&(team->archer[0]), 1, lvl[0]);
    setArcher(&(team->archer[1]), 2, lvl[1]);
    setArcher(&(team->archer[2]), 3, lvl[2]);
    team->q_rank = 0;
    team->e_rank = 0;
} /*}}}2*/

void setTeams(double lvl_1[3], double lvl_8[3], double lvl_16[3]) /*{{{2*/
/*
 * Setup an array of teams with different skill levels
 * where;
 * lvl_1    = array of level of archers of highest ranked team
 * lvl_8    = array of level of archers of 8th ranked team
 * lvl_16   = array of level of archers of 16th ranked team
 *
 * Returns nothing, but fills the archers array
 */
{
    double lvl[3];
    double dlvl[3];
    int i, j;

    /* team 1..8 */
    dlvl[0] = (lvl_1[0]-lvl_8[0])/7.0;
    dlvl[1] = (lvl_1[1]-lvl_8[1])/7.0;
    dlvl[2] = (lvl_1[2]-lvl_8[2])/7.0;
    for (i = 0; i < 8; i++) {
        lvl[0] = lvl_1[0] - i*dlvl[0];
        lvl[1] = lvl_1[1] - i*dlvl[1];
        lvl[2] = lvl_1[2] - i*dlvl[2];
        setTeam(&team[i], lvl);
    }

    /* 9..16 */
    dlvl[0] = (lvl_8[0]-lvl_16[0])/8.0;
    dlvl[1] = (lvl_8[1]-lvl_16[1])/8.0;
    dlvl[2] = (lvl_8[2]-lvl_16[2])/8.0;
    for (i = 8; i < 16; i++) {
        lvl[0] = lvl_8[0] - (i-7)*dlvl[0];
        lvl[1] = lvl_8[1] - (i-7)*dlvl[1];
        lvl[2] = lvl_8[2] - (i-7)*dlvl[2];
        setTeam(&team[i], lvl);
    }
} /*}}}2*/

double getTeamScore(const Team *team) /*{{{2*/
{
    return team->archer[0].q_score + team->archer[1].q_score + team->archer[2].q_score;
} /*}}}2*/

void dumpTeam(const Team *team) /*{{{2*/
{
    if (team == NULL) {
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
            outp("\"q-rank\";\"up-down\";\"e-rank\";\"score\";\"archer1\";\"archer2\";\"archer3\"\n");
        }
        return;
    }

    if (pretty_print) {
        outp("|   %3d  | %s |   %3d  |  %8.2lf (%6.1lf, %6.1lf, %6.1lf) |\n",
                team->q_rank, ' ', team->e_rank, getTeamScore(team),
                team->archer[0].q_score, team->archer[1].q_score, team->archer[2].q_score);
    }
    else {
        outp("%d;\"%s\";%d;%lf;%lf;%lf;%lf\n",
               team->q_rank, ' ', team->e_rank, getTeamScore(team),
               team->archer[0].q_score, team->archer[1].q_score, team->archer[2].q_score);
    }
} /*}}}2*/

void rankTeams(int from_rank, int to_rank) /*{{{2*/
{
    int i, j;
    int start_idx = from_rank-1;
    int end_idx = to_rank-1;
    Team *tmp, *max;
    int j_found = 0;

    for (i = start_idx; i <= end_idx; i++) {
        max = NULL;
        for (j = i; j <= end_idx; j++) {
            if ( (max == NULL) ||
                 (getTeamScore(teamrank[j]) > getTeamScore(max)) )
            {
                max = teamrank[j];
                j_found = j;
            }
        }
        /* swap */
        tmp = teamrank[i];
        teamrank[i] = max;
        teamrank[j_found] = tmp;
    }
} /*}}}2*/

/* --- Local functions {{{1 */


