/*****************************************************************************
*** Name      : modes.h                                                      ***
*** Purpose   : Different simulation modes                                 ***
*** Author    : Marcel van Apeldoorn <mvapldrn@gmail.com>                  ***
*** Copyright : 2013                                                       ***
*****************************************************************************/

#ifndef _MODES_H
#define _MODES_H

/* --- Includes {{{1 */

#include "format.h"

/* --- Interface {{{1 */

#define MODE_SCORE                      1
#define MODE_QUALIFICATION              2
#define MODE_ELIMINATION                3
#define MODE_TEAM_ELIMINATION           4
#define MODE_MIXED_TEAM_ELIMINATION     5
#define MODE_COMPETITION                6
#define MODE_COMPETITIONS               7

void modeScore(void);
void modeQualification(void);
void modeElimination(void);
void modeTeamElimination(void);
void modeMixedTeamElimination(void);
void modeCompetition(void);
void modeCompetitions(void);

#endif
