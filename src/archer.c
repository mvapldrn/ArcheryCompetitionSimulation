/*****************************************************************************
*** Name      : archer.c                                                   ***
*** Purpose   : Defines the archer types and routines                      ***
*** Author    : Marcel van Apeldoorn <mvapldrn@gmail.com>                  ***
*** Copyright : 2013                                                       ***
*****************************************************************************/

/* --- Includes {{{1 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "dump.h"
#include "stats.h"
#include "archer.h"

/* --- Global data {{{1 */

/* 104 archers in the competition */
Archer  archer[104];         /* Individual archer */
Archer *archerrank[104];     /* Points to archer ranked idx+1 */

double asl1;
double asl4;
double asl8;
double asl16;
double asl32;
double asl56;
double asl104;

int high_loser = 16;
int cut_high_loser = 16;

extern int pretty_print;

/* --- Local prototypes {{{1*/

static char winSymbol(const Archer *archer);

/* --- Implementation {{{1*/

void setArcher(Archer *archer, int lvl_rank, double lvl) /*{{{2*/
{
    archer->lvl        = lvl;
    archer->lvl_rank   = lvl_rank;
    archer->lvl_score  = -1.0;
    archer->q_score    = -1.0;
    archer->q_n        = 0;
    archer->q_rank     = 0;
    archer->e_rank     = 0;

    resetStat(&(archer->q_score_stat));
} /*}}}2*/

void setArchers(void) /*{{{2*/
/*
 * Setup an array of archers with different skill levels
 * linearly distributed between asl1,4,8,16,32,56 and 104
 * Returns nothing, but fills the archers array
 */
{
    double dlvl;
    int i;

    /* 1..4 */
    dlvl = (asl1-asl4)/3.0;
    for (i = 1; i <= 4; i++) {
        setArcher(&(archer[i-1]), i, asl1 - (i-1)*dlvl);
    }

    /* 5..8 */
    dlvl = (asl4-asl8)/3.0;
    for (i = 5; i <= 8; i++) {
        setArcher(&(archer[i-1]), i, asl4 - (i-5)*dlvl);
    }

    /* 9..16 */
    dlvl = (asl8-asl16)/7.0;
    for (i = 9; i <= 16; i++) {
        setArcher(&(archer[i-1]), i, asl8 - (i-9)*dlvl);
    }

    /* 17..32 */
    dlvl = (asl16-asl32)/15.0;
    for(i = 17; i <= 32; i++) {
        setArcher(&(archer[i-1]), i, asl16 - (i-17)*dlvl);
    }

    /* 32..56 */
    dlvl = (asl32-asl56)/23.0;
    for(i = 33; i <= 56; i++) {
        setArcher(&(archer[i-1]), i, asl32 - (i-33)*dlvl);
    }

    /* 56..104 */
    dlvl = (asl56-asl104)/47.0;
    for(i = 57; i <= 104; i++) {
        setArcher(&(archer[i-1]), i, asl56 - (i-57)*dlvl);
    }

    for (i = 0; i < 104; i++) {
        archerrank[i] = &(archer[i]);
    }
} /*}}}2*/

void dumpArcher(const Archer *archer) /*{{{2*/
{
    if (archer == NULL) {
        /* Forced to dump header */
        if (pretty_print) {
            outp("\n                                                RANKING RESULTS\n");
            outp("=================================================================================================================================\n");
            outp("| Qualification Rank |   | Elimination Rank | Archers Skill Level | Archers Skill Level Score | Simulated Score |    StdDev(%)  |\n");
            outp("|--------------------+---+------------------+---------------------+---------------------------+-----------------+---------------|\n");
        }
        else {
            outp("\"Results\"\n");
            outp("\"q-rank\";\"lvl-rank\";\"up-down\";\"e-rank\";\"asl\";\"asl-score\";\"score\";\"stdev\"\n");
        }
        return;
    }

    if (pretty_print) {
        /*    |        XXX         | + |       XXX        |       XXX.XX        |        XXXX.X             |      XXXX.X     | XX.XXX(XX.X%)  | */
        outp("|        %3d(%3d)    | %c |       %3d        |       %6.2lf        |        %6.1lf             |      %6.1lf     | %6.3lf(%4.1lf%%)  |\n",
               archer->q_rank, archer->lvl_rank,
               winSymbol(archer),
               archer->e_rank, archer->lvl, archer->lvl_score, archer->q_score, archer->q_score_stat.stdev,
               100.0*(sqrt(archer->q_score_stat.stdev)/archer->q_score));
    }
    else {
        outp("%d;%d;\"%c\";%d;%lf;%lf;%lf;%lf\n",
               archer->q_rank, archer->lvl_rank,
               winSymbol(archer),
               archer->e_rank, archer->lvl,
               archer->lvl_score, archer->q_score, archer->q_score_stat.stdev);
    }
} /*}}}2*/

int isHighLoser(const Archer *archer)  /*{{{2*/
{
    int ret = 0;
    /* Needs to be within cut_high_position */
    if (archer->q_rank <= cut_high_loser) {
        if ( (archer->q_rank <= archer->e_rank) &&
             (archer->e_rank - archer->q_rank) >= high_loser) {
            ret = 1;
        }
    }

    return ret;
} /*}}}2*/

void rankArchersOnQualifyingRank(int from_rank, int to_rank) /*{{{2*/
/*
 * Rank archers on qualifying rank (q_rank)
 */
{
    int start_idx = from_rank-1;
    int end_idx = to_rank-1;

    for (int i = start_idx; i <= end_idx; i++) {
        int min_idx = i;
        int min_q_rank = archerrank[i]->q_rank;
        for (int j = i+1; j <= end_idx; j++) {
            if (archerrank[j]->q_rank < min_q_rank) {
                min_idx = j;
                min_q_rank = archerrank[min_idx]->q_rank;;
            }
        }
        if (min_idx != i) {
            /* swap */
            Archer *tmp = archerrank[i];
            archerrank[i] = archerrank[min_idx];
            archerrank[min_idx] = tmp;
        }
    }
} /*}}}2*/

void rankArchersOnQualifyingScore(int from_rank, int to_rank) /*{{{2*/
/*
 * Rank archers on qualifying score (q_score)
 */
{
    int start_idx = from_rank-1;
    int end_idx = to_rank-1;

    for (int i = start_idx; i <= end_idx; i++) {
        int max_idx = i;
        int max_q_score = archerrank[max_idx]->q_score;
        for (int j = i+1; j <= end_idx; j++) {
            if (archerrank[j]->q_score > max_q_score) {
                max_idx = j;
                max_q_score = archerrank[max_idx]->q_score;
            }
        }
        if (max_idx != i) {
            /* swap */
            Archer *tmp = archerrank[i];
            archerrank[i] = archerrank[max_idx];
            archerrank[max_idx] = tmp;
        }
    }
} /*}}}2*/

/* --- Local functions {{{1 */

static char winSymbol(const Archer *archer) /*{{{2*/
{
    if (isHighLoser(archer)) return 'V';
    if (archer->q_rank < archer->e_rank)  return '-';
    if (archer->q_rank == archer->e_rank) return '=';
    return '+';


} /*}}}2*/


