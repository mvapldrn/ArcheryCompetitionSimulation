/*****************************************************************************
*** Name      : qualification.c                                            ***
*** Purpose   : Defines the qualification round routines                   ***
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
#include <math.h>
#include <stdlib.h>

#include "qualification.h"

#include "debug.h"
#include "dump.h"
#include "mixedteam.h"
#include "team.h"
#include "archer.h"
#include "score.h"
#include "format.h"
#include "stats.h"

/* --- Global data {{{1*/

extern int pretty_print;

int q_nruns = 5000;
QualificationStatistics qstats;

/* --- Local prototypes {{{1*/

static void createQualificationRanking(int signdec);
static double getQualificationRankCorrectness(void);
static int isTied(int sign_dec, double s1, double s2);
static void randomizeRange(int from, int to);

/* --- Implementation {{{1*/

void initQualificationStats(void) /*{{{2*/
/*
 * Initialize (set zero) qualification statisttics
 */
{
    for (int i = 0; i < 104; i++) {
        resetStat(&(archer[i].q_score_stat));
    }
    qstats.n = 0;
    resetStat(&(qstats.n_ties));
    resetStat(&(qstats.fc));
} /*}}}2*/

void doQualificationRound(void) /*{{{2*/
/*
 * Perform a single qualification round for archers in set format
 */
{
    const Face *face = getFace(q_format.facetype);
    const double dist = q_format.distance;
    const int narrows = q_format.narrows;
    int i;
    int n_tie;

    for (i = 0; i < 104; i++) {
        /* Compute score (theoretical) based on skill level */
        archer[i].lvl_score = getScoreBySkillLevel(archer[i].lvl, face, dist, narrows);

        /* Simulate Q round */
        archer[i].q_score = getScore(archer[i].lvl, face, dist, narrows);

        /* Following parameters are needed for multiple Q rounds */
        addStat(&(archer[i].q_score_stat), archer[i].q_score);
    }

    /* Create the qualification ranking */
    createQualificationRanking(face->significant_decimals);

    /* Add some statistics (e.g. ranking statistics) */

    /* Determine and add number of ties */
    n_tie = 0;
    for (i = 0; i < 103; i++) {
        if (isTied(face->significant_decimals, archerrank[i]->q_score, archerrank[i+1]->q_score)) {
            n_tie++;
        }
    }
    addStat(&(qstats.n_ties), n_tie);
    /* Add qualification rank correctness */
    addStat(&(qstats.fc), getQualificationRankCorrectness());

    qstats.n = qstats.n + 1;
} /*}}}2*/

void doQualificationRounds(int n) /*{{{2*/
/*
 * Perform n qualification rounds for archers in given format, compute their average and stddev
 * format : this format
 */
{
    const Face *face = getFace(q_format.facetype);
    const double dist = q_format.distance;
    const int narrows = q_format.narrows;
    double sum = 0.0;
    int i, j;

    initQualificationStats();

    /* Simulate n Q rounds */
    for (j = 0; j < n; j++) {
        doQualificationRound();
    }
    for (i = 0; i < 104; i++) {
        /* Replace last q_score for average to get sorting right */
        archer[i].q_score = archer[i].q_score_stat.avg;
    }

    rankArchersOnQualifyingScore(1, 104);
    for (i = 0; i < 104; i++) {
        archerrank[i]->q_rank = (i+1);
    }

} /*}}}2*/

void doTeamQualificationRound(void) /*{{{2*/
/*
 * Perform a single qualification round for teams in given format
 * format : this format
 */
{
    const Face *face = getFace(q_format.facetype);
    const double dist = q_format.distance;
    const int narrows = q_format.narrows;
    int i;

    for (i = 0; i < 16; i++) {
        /* Simulate Q round */
        team[i].archer[0].q_score = getScore(team[i].archer[0].lvl, face, dist, narrows);
        team[i].archer[1].q_score = getScore(team[i].archer[1].lvl, face, dist, narrows);
        team[i].archer[2].q_score = getScore(team[i].archer[2].lvl, face, dist, narrows);
    }

    for (i = 0; i < 16; i++) {
        teamrank[i] = &(team[i]);
    }
    rankTeams(1, 16);
    for (i = 0; i < 16; i++) {
        teamrank[i]->q_rank = (i+1);
    }

} /*}}}2*/

void doMixedTeamQualificationRound(void) /*{{{2*/
/*
 * Perform a single qualification round for mixedteams in given format
 * format : this format
 */
{
    const Face *face = getFace(q_format.facetype);
    const double dist = q_format.distance;
    const int narrows = q_format.narrows;
    int i;

    for (i = 0; i < 24; i++) {
        /* Simulate Q round */
        mixedteam[i].archer[0].q_score = getScore(team[i].archer[0].lvl, face, dist, narrows);
        mixedteam[i].archer[1].q_score = getScore(team[i].archer[1].lvl, face, dist, narrows);
    }

    for (i = 0; i < 24; i++) {
        mixedteamrank[i] = &(mixedteam[i]);
    }
    rankMixedTeams(1, 24);
    for (i = 0; i < 24; i++) {
        mixedteamrank[i]->q_rank = (i+1);
    }

} /*}}}2*/

void dumpQualificationStats(void) /*{{{2*/
{
    if (pretty_print) {
        outp("\nQualification statistics\n");
        outp("========================\n");
        outp("Population: %s\n", name_of_population);
        outp("Format    : %s\n", getFormatName(&q_format));
        outp("Runs      : %ld\n\n", q_nruns);
        outp("Results\n");
        outp("Average number of ties : %5.2lf\n", qstats.n_ties.avg);
        outp("                StdDev : %5.2lf\n", qstats.n_ties.stdev);
        outp("Average correctness    : %lf\n", qstats.fc.avg);
        outp("                StdDev : %lf\n\n", qstats.fc.stdev);
    }
    else {
        outp("\"%s\";%s;%lf;%lf;%lf;%lf;%ld\n",
                name_of_population,
                getFormatName(&q_format), qstats.n_ties.avg, qstats.n_ties.stdev, qstats.fc.avg, qstats.fc.stdev,q_nruns);
    }
} /*}}}2*/

/* --- Local functions {{{1 */

static double getQualificationRankCorrectness(void) /*{{{2*/
/*
 * Compute the correctness factor for this ranking
 *
 * Correctness is defined as:
 *
 *               N(104)
 * correctness =  SUM ( archer[i].lvl_rank - archer[i].q_rank )^2   ) / N
 *                i=1
 *
 * This indicates how well the final ranking fits the perfect ranking. The smaller
 * this number, the better the fit
 */
{
    double f = 0.0;
    int i;

    for (i = 0; i < 104; i++) {
        f += (archer[i].lvl_rank - archer[i].q_rank) * (archer[i].lvl_rank - archer[i].q_rank);
    }
    f = f/104.0;
    return f;
} /*}}}2*/

static void createQualificationRanking(int signdec) /*{{{2*/
/*
 * Order a single qualification round a bit according to WA rules.
 * We do not order with 'X' count, but if there is a tie, a coin toss
 * is done
 */
{
    int i, j;
    double sc1, sc2;

#ifdef DEBUG
    dumpArcher(NULL);
    for (i = 0; i < 104; i++) {
        /* Have each archerrank point to an archer */
        archerrank[i] = &(archer[i]);
        dumpArcher(archerrank[i]);
    }
#endif

    /* Order them to score */
    for (i = 0; i < 103; i++) {
        int max_idx = i;
        double max_value = archerrank[i]->q_score;
        for (j = i+1; j < 104; j++) {
            if (archerrank[j]->q_score > max_value) {
                max_idx = j;
                max_value = archerrank[max_idx]->q_score;
            }
        }
        if (max_idx != i) {
            /* swap */
            D("Sort swap %d with %d\n", i+1, max_idx+1);
            Archer *tmp = archerrank[i];
            archerrank[i] = archerrank[max_idx];
            archerrank[max_idx] = tmp;
        }
    }

#ifdef DEBUG
    dumpArcher(NULL);
    for (i = 0; i < 104; i++) {
        /* Have each archerrank point to an archer */
        dumpArcher(archerrank[i]);
    }
#endif

    /* Now scan for ties */
    for (i = 0; i < 103;) {
        D("Scan for ties from %d\n", i);
        sc1 = archerrank[i]->q_score;
        j = 0;
        do {
            j++;
            sc2 = archerrank[i+j]->q_score;
        } while ((i+j<103) && isTied(signdec, sc1, sc2));
        if (j >= 2) {
            /* 2-way or more */
            D("Found a %d-way tie\n", j);
            randomizeRange(i, i+(j-1));
        }
        i = i + j;
        D("Next is %d\n", i);
    }

    /* Set qualification ranking value */
    for (i = 0; i < 104; i++) {
        archerrank[i]->q_rank = (i+1);
    }

#ifdef DEBUG
    dumpArcher(NULL);
    for (i = 0; i < 104; i++) {
        /* Have each archerrank point to an archer */
        dumpArcher(archerrank[i]);
    }
#endif

} /*}}}2*/

static int isTied(int sign_dec, double s1, double s2) /*{{{2*/
{
    D("isTied(%d,%lf, %lf)\n", sign_dec, s1, s2);
    long ls1 = (long)round(pow(10.0, sign_dec) * s1);
    long ls2 = (long)round(pow(10.0, sign_dec) * s2);
    int istied = (ls1 == ls2)?1:0;

    D("Is tied (signdec=%d) %ld %ld -> %s\n", sign_dec, ls1, ls2, (istied==1)?"yes":"no");

    return istied;
} /*}}}2*/

static void randomizeRange(int from, int to) /*{{{2*/
/*
 * Range <from> to <to> (to including) has tied, randomize these
 * tied archers
 */
{
    D("randomizeRange(%d,%d)\n", from, to);
    Archer *tmp;

    if (from == to) {
        /* One-way tie does not exist, return */
        return;
    }
    int n = to - from;
    D("Solving a %d-way tie\n", n+1);

    /* Randomize a number between 0 and n, pick that one to go on top and repeat */
    int pick = (int)round((1.0 * n * (1.0 * rand() / RAND_MAX) )); /* 0 <= pick <= n */

    if (pick > 0) {
        /* swap */
        D("..swap %d(asl=%lf) with %d(asl=%lf)\n", from, archerrank[from]->lvl, from+pick, archerrank[from+pick]->lvl);
        tmp = archerrank[from];
        archerrank[from] = archerrank[from+pick];
        archerrank[from+pick] = tmp;
    }
    else {
        D("..No swap %d\n", from);
    }

    randomizeRange(from+1, to);
} /*}}}2*/

