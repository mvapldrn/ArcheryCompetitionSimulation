/*****************************************************************************
*** Name      : modes                                                      ***
*** Purpose   : Different simulation modes                                 ***
*** Author    : Marcel van Apeldoorn <mvapldrn@gmail.com>                  ***
*** Copyright : 2013                                                       ***
*****************************************************************************/

/* --- Includes {{{1 */

#include <stdio.h>
#include <stdlib.h>

#include "skilllevelscores.h"
#include "interactive.h"
#include "dump.h"
#include "format.h"
#include "qualification.h"
#include "elimination.h"

/* --- Global data {{{1*/

extern int pretty_print;
extern int with_progress;
extern int interactive;

/* --- Implementation {{{1*/

void modeScore(void) /*{{{2*/
{
    q_format.best_of = 0;
    q_format.type = CUMULATIVE;
    if (interactive) interactiveASLSimulation();
    ASLSimulation();
} /*}}}2*/

void modeQualification(void) /*{{{2*/
{
    int i;

    initQualificationStats();

    if (interactive) interactiveQualificationRoundSimulation();

    setArchers();

    doQualificationRounds(q_nruns);

    dumpQualificationStats();
#if 1
    dumpArcher(NULL); /* Force dump header */
    for (i = 0; i < 104; i++) {
        dumpArcher(archerrank[i]);
    }
#endif
} /*}}}2*/

void modeElimination(void) /*{{{2*/
{
    if (interactive) interactiveEliminationStats();
    computeEliminationStats();
} /*}}}2*/

void modeTeamElimination(void) /*{{{2*/
{
    if (interactive) interactiveTeamEliminationStats();
    computeTeamEliminationStats();
} /*}}}2*/

void modeMixedTeamElimination(void) /*{{{2*/
{
    if (interactive) interactiveMixedTeamEliminationStats();
    computeMixedTeamEliminationStats();
} /*}}}2*/

void modeCompetition(void) /*{{{2*/
{
    int i;

    initQualificationStats();
    initEliminationStats();

    if (interactive) interactiveCompetitionSimulation();

    setArchers();

    doQualificationRound();

    dumpQualificationStats();
    dumpArcher(NULL); /* Force dump header */
    for (i = 0; i < 104; i++) {
        dumpArcher(archerrank[i]);
    }

    doEliminationRound();

    dumpEliminationStats();
    dumpArcher(NULL); /* Force dump header */
    for (i = 0; i < 104; i++) {
        dumpArcher(archerrank[i]);
    }
} /*}}}2*/

void modeCompetitions(void) /*{{{2*/
{
    int j;
    int i;

    initQualificationStats();
    initEliminationStats();

    if (interactive) interactiveCompetitionsSimulation();

    setArchers();

    if (with_progress && q_nruns>50) {
        printf("\n0----------------------------------------------100\n");
    }

    for (j = 0; j < q_nruns; j++) {
        doQualificationRound();

        /* Elimination */
        doEliminationRound();

        if (with_progress && q_nruns>50 && j%(q_nruns/50)==0) {
            printf("#"); fflush(stdout);
        }
    }
    if (with_progress && q_nruns>50) {
        printf("\n");
    }

    dumpEliminationStats();
} /*}}}2*/

