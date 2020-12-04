/*****************************************************************************
*** Name      : team.h                                                     ***
*** Purpose   : Defines the team types and routines                        ***
*** Author    : Marcel van Apeldoorn <mvapldrn@gmail.com>                  ***
*** Copyright : 2013                                                       ***
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

