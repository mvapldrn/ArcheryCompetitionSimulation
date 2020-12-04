/*****************************************************************************
*** Name      : stats.h                                                    ***
*** Purpose   : Implements a helper for keeping mean/variance              ***
*** Author    : Marcel van Apeldoorn <mvapldrn@gmail.com>                  ***
*** Copyright : 2013                                                       ***
*****************************************************************************/

#ifndef _STATS_H
#define _STATS_H

/* --- Constants {{{1 */

/* --- Data types {{{1 */

/*
 * Keep a mean and variance of a statistical value in an updateable fashion
 * I.e. every timestep, K, Ex and Ex2 get updated and at the end,
 * mean and variance can be computed
 */
typedef struct {
    long   n;                   /* Number of values                         */
    double val;                 /* Most recent value                        */
    double avg;                 /* Running mean/average of all values       */
    double var;                 /* Running variance of all values           */
    double stdev;               /* Running standard deviation of all values */
} Stat;

/* --- Interface {{{1 */

void resetStat(Stat *stat);
void addStat(Stat *stat, double value);

#endif
