/*****************************************************************************
*** Name      : stats.c                                                    ***
*** Purpose   : Implements a helper for keeping mean/variance              ***
*** Author    : Marcel van Apeldoorn <mvapldrn@gmail.com>                  ***
*** Copyright : 2013                                                       ***
*****************************************************************************/


/* --- Includes {{{1 */
#include <stdlib.h>
#include <float.h>
#include <math.h>

#include "stats.h"


/* --- Global data {{{1 */

/* --- Local prototypes {{{1*/

/* --- Implementation {{{1*/

void resetStat(Stat *stat) /*{{{2*/
{
    stat->n     = 0;
    stat->avg   = 0.0;
    stat->var   = 0.0;
    stat->stdev = 0.0;
}

void addStat(Stat *stat, double value) /*{{{2*/
{
    stat->n = stat->n + 1;

    if (stat->n == 1) {
        /* First entry */
        stat->avg = value;
        stat->var = 0.0;
    }
    else {
        /* Subsequent entries */
        stat->avg   = stat->avg + (value - stat->avg) / stat->n;
        stat->var   = stat->var + (value - stat->avg) * (value - stat->avg);
    }
    stat->stdev = sqrt(stat->var/stat->n);
} /*}}}2*/



