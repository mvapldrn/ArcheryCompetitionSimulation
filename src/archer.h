/*****************************************************************************
*** Name      : archer.h                                                   ***
*** Purpose   : Defines the archer types and routines                      ***
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

#ifndef _ARCHER_H
#define _ARCHER_H

/* --- Includes {{{1 */
#include "stats.h"

/* --- Data types {{{1 */

typedef struct {
    /*
     * Archers Skill Level, the theoretical ability of the archer
     */
    double lvl;

    /*
     * Archers skill level based rank in the population of archers
     */
    int    lvl_rank;

    /*
     * Qualification score based on skill level (theoretical score)
     * for given qualification format
     */
    double lvl_score;

    /*
     * Simulated (shot) qualification score, based on the total sum of
     * each shot for a given qualification format)
     */
    double q_score;

    /*
     * Number of qualification rounds simulated for this archer
     */
    int    q_n;

    /*
     * Running statistics of qualification score (q_score). The stats keep
     * track (in an iterative fashion) of the mean and variance of the
     * q_score
     */
    Stat q_score_stat;

    /*
     * Rank in the population after qualification round
     */
    int    q_rank;

    /*
     * Rank in the population after elimination round
     */
    int    e_rank;
} Archer;

/* --- Interface {{{1 */

/*
 * An individual (simulated) archer from a pool of arches
 */
extern Archer  archer[];
/*
 * Defines the ranking of an Archer
 */
extern Archer *archerrank[];
/*
 * The next parametsr define the skill level distribution over the population
 *
 * The Archer Skill Level of the #1 archer
 */
extern double asl1;
/*
 * The Archer Skill Level of the #4 archer
 */
extern double asl4;
/*
 * The Archer Skill Level of the #8 archer
 */
extern double asl8;
/*
 * The Archer Skill Level of the #16 archer
 */
extern double asl16;
/*
 * The Archer Skill Level of the #32 archer
 */
extern double asl32;
/*
 * The Archer Skill Level of the #56 archer
 */
extern double asl56;
/*
 * The Archer Skill Level of the #104 archer
 */
extern double asl104;
/*
 * The definition of a 'high loser' is when the final rank is more than
 * 'high_loser' positions lower than the qualifying ranking, but only for the
 * top 'cut_high_loser' positions (archer needs to be within 'cut_high_loser'
 * in qualification round
 */
extern int high_loser;
extern int cut_high_loser;
extern char *name_of_population;

void setArcher(Archer *archer, int lvl_rank, double lvl);
void setArchers(void);
void rankArchersOnQualifyingRank(int from_rank, int to_rank);
void rankArchersOnQualifyingScore(int from_rank, int to_rank);
void dumpArcher(const Archer *archer);
int isHighLoser(const Archer *archer);
int isFinalRankInQRank(int top, const Archer *archer);

#endif

