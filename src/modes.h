/*****************************************************************************
*** Name      : modes.h                                                      ***
*** Purpose   : Different simulation modes                                 ***
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
