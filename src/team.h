/*****************************************************************************
*** Name      : team.h                                                     ***
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

#ifndef _TEAM_H
#define _TEAM_H

#include "archer.h"

/* --- Constants {{{1 */

/* --- Data types {{{1 */

typedef struct {
    Archer archer[3];  /* Team of archers                                 */
    int    q_rank;     /* Rank after qualification round                  */
    int    e_rank;     /* Rank after eliminations                         */
} Team;

/* --- Interface {{{1 */

extern Team  team[];
extern Team* teamrank[];

void setTeam(Team *team, double *lvls);
void setTeams(double lvl_1[3], double lvl_8[3], double lvl_16[3]);
double getTeamScore(const Team *team);
void rankTeams(int from_rank, int to_rank);

#endif

