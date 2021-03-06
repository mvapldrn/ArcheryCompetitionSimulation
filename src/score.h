/*****************************************************************************
*** Name      : score.h                                                    ***
*** Purpose   : Defines the types and routines for scoring model           ***
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

#ifndef _SCORE_H
#define _SCORE_H

/* --- Includes {{{1 */

#include "archer.h"
#include "team.h"
#include "mixedteam.h"
#include "format.h"

/* --- Constants {{{1 */

typedef enum {
    LEFT_WINS           = 2,
    LEFT_WINS_SHOOTOFF  = 1,
    DRAW                = 0,
    RIGHT_WINS_SHOOTOFF =-1,
    RIGHT_WINS          =-2
} Result;

/* --- Prototypes {{{1 */
Result scoreCompare(double left_score, double right_score);
Result shootoffCompare(double left_distance_from_center, double right_distance_from_center);
Result teamShootoffCompare(const Team *left, double left_d[3], const Team *right, double right_d[3], const Face *face);
Result mixedTeamShootoffCompare(const MixedTeam *left, double left_d[2], const MixedTeam *right, double right_d[2], const Face *face);
double getScore(double lvl, const Face *face, double dist, int n_arrows);
double getArrowValue(double lvl, const Face *face, double dist);
double getArrowPosition(double lvl, double dist);
double getScoreBySkillLevel(double lvl, const Face *face, double dist, int n_arrows);

#endif
