/*****************************************************************************
*** Name      : skilllevelscores.c                                         ***
*** Purpose   : Routine to compute average scores based on skill level     ***
*** Author    : Marcel van Apeldoorn <mvapldrn@gmail.com>                  ***
*** Copyright : 2013                                                       ***
*****************************************************************************/

/* --- Includes {{{1 */
#include <math.h>

#include "dump.h"
#include "archer.h"
#include "score.h"
#include "format.h"
#include "qualification.h"

/* --- Global data {{{1*/

extern int pretty_print;
extern double start_asl;
extern double end_asl;
extern double step_asl;

/* --- Local prototypes {{{1*/

/* --- Implementation {{{1*/

void ASLSimulation(void) /*{{{2*/
/*
 * Computes the score and some statistics on the score, that an archer would shoot based on its skill level
 * and loops over skill levels
 * start_asl : starting skill level
 * end_asl   : ending skill level (incl. if possible with step)
 * step_asl  : with this step (in skill level)
 * format    : format of the round
 * nsims     : number of simulations (to base stats on)
 */
{
    double asl;
    int n, j;
    double mean;
    double m2;
    double delta;
    double x;

    const Face *face = getFace(q_format.facetype);
    const double dist = q_format.distance;
    const int narrows = q_format.narrows;

    if (pretty_print) {
        outp("Format               : %s\n", getFormatName(&q_format));
        outp("Number of simulations: %d\n", q_nruns);
        outp("| Archers Skill Level |  Score   | Stddev |\n");
        outp("+---------------------+----------+--------|\n");
        /*    |     XXX.XX          |  XXXX.X  | XX.XXX | */
    }
    else {
        outp("\"%s\";%d\n", getFormatName(&q_format), q_nruns);
        outp("\"asl\";\"asl-score\";\"mean-score\";\"stddev-score\"\n");
    }
    for (asl = start_asl; asl <= end_asl; asl += step_asl) {
        n = 0;
        mean = 0.0;
        m2 = 0.0;
        for (j = 0; j < q_nruns; j++) {
            x = getScore(asl, face, dist, narrows);
            /* Compute mean and variance */
            n++;
            delta = x - mean;
            mean += delta/n;
            m2 += delta*(x-mean);
        }
        /* Dump mean and variance */
        double stddev = sqrt(m2/(n-1.0));
        if (pretty_print) {
            outp("|     %6.2lf          |  %6.1lf  | %6.3lf |\n", asl, mean, stddev);
        }
        else {
            outp("%lf;%lf;%lf;%lf;%lf\n",
                    asl,
                    getScoreBySkillLevel(asl, face, dist, narrows),
                    mean,
                    stddev);
        }
    }

    outp_close();
} /*}}}2*/


