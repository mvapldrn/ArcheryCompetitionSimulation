/*****************************************************************************
*** Name      : interactive.h                                              ***
*** Purpose   : Interactive routines                                       ***
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

#ifndef _INTERACTIVE_H
#define _INTERACTIVE_H

/* --- Includes {{{1 */

/* --- Interface {{{1*/

extern int interactive;

void interactiveASLSimulation(void);
void interactiveQualificationRoundSimulation(void);
void interactiveEliminationStats(void);
void interactiveTeamEliminationStats(void);
void interactiveMixedTeamEliminationStats(void);
void interactiveCompetitionSimulation(void);
void interactiveCompetitionsSimulation(void);

#endif
