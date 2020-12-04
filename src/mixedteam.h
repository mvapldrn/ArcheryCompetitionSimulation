/*****************************************************************************
*** Name      : mixedteam.h                                                     ***
*** Purpose   : Defines the team types and routines                        ***
*** Author    : Marcel van Apeldoorn <mvapldrn@gmail.com>                  ***
*** Copyright : 2013                                                       ***
*****************************************************************************/

#ifndef _MIXEDTEAM_H
#define _MIXEDTEAM_H

#include "archer.h"

/* --- Constants {{{1 */

/* --- Data types {{{1 */

typedef struct {
    Archer archer[2];  /* Team of archers                                 */
    int    q_rank;     /* Rank after qualification round                  */
    int    e_rank;     /* Rank after eliminations                         */
} MixedTeam;

/* --- Interface {{{1 */

extern MixedTeam  mixedteam[];
extern MixedTeam *mixedteamrank[];

void setMixedTeam(MixedTeam *mixedteam, double *lvls);
double getMixedTeamScore(const MixedTeam *mixedteam);
void rankMixedTeams(int from_rank, int to_rank);

#endif

