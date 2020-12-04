/*****************************************************************************
*** Name      : qualification.h                                            ***
*** Purpose   : Defines the qualification round routines                   ***
*** Author    : Marcel van Apeldoorn <mvapldrn@gmail.com>                  ***
*** Copyright : 2013                                                       ***
*****************************************************************************/

#ifndef _QUALIFICATION_H
#define _QUALIFICATION_H

/* --- Includes {{{1 */

#include "format.h"
#include "stats.h"

/* --- Types {{{1 */

typedef struct {
    /* Total number of qualification run */
    int          n;

    /* Number of ties in qualification */
    Stat         n_ties;

    /* Qualification ranking fitness function */
    Stat         fc;
} QualificationStatistics;

/* --- Interface {{{1 */

extern int q_nruns;

void initQualificationStats(void);
void doQualificationRound(void);
void doQualificationRounds(int n);
void doTeamQualificationRound(void);
void dumpQualificationStats();

#endif
