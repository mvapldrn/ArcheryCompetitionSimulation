/*****************************************************************************
*** Name      : random.c                                                   ***
*** Purpose   : Implements a random generator (using Box-Muller algo)      ***
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
#include <stdlib.h>
#include <float.h>
#include <math.h>

#include "random.h"
#include "debug.h"

/* --- Local data {{{1 */

#ifdef WITH_GSL
gsl_rng *gslr;
#endif

extern long seed;

/* --- Local prototypes {{{1*/

static void seedGaussian(unsigned seed);
static double getGaussianBoxMullerRandom(double m, double s);

/* --- Implementation {{{1*/

void initRandomGenerator(void) /*{{{2*/
{
#ifdef WITH_GSL
    /* Setup the GSL random generator */
    const gsl_rng_type *T;
    gsl_rng_env_setup();
    T = gsl_rng_default;
    gslr = gsl_rng_alloc(T);
    if (seed != 0L) gsl_rng_set(gslr, seed);
#else
    if (seed > 0) {
        seedGaussian(seed);
    }
    else if (seed == 0) {
        time_t t;
        seedGaussian((unsigned)time(&t));
    }
#endif
} /*}}}2*/

double getGaussianRandom(double stddev) /*{{{2*/
/*
 * Return a random Gaussian (normal) distributed value with a mean
 * of 0.0 and a given standard deviation
 */
{
#ifdef WITH_GSL
    return gsl_ran_gaussian_ziggurat(gslr, stddev);
#else
    return getGaussianBoxMullerRandom(0.0, stddev);
#endif
} /*}}}2*/

/* --- Local functions {{{1 */

static void seedGaussian(unsigned seed) { /*{{{2*/
    printf("Seeding %d\n", seed);
    srand(seed);
} /*}}}2*/

static double getGaussianBoxMullerRandom(double m, double s) /*{{{2*/
/*
 * Box-Muller transform to generate random values from a standard normal distribution
 */
{
    D("    getGaussianRandom(%lf,%lf)\n", m, s);

    static double z0;
    static double z1;
    static int generated = 0;

    if (generated) {
        generated = 0;
        return z1 * s + m;
    }

    double u1, u2;

    do {
        u1 = rand() * (1.0/RAND_MAX);
        u2 = rand() * (1.0/RAND_MAX);
    } while (u1 <= DBL_MIN);

    z0 = sqrt(-2.0 * log(u1)) * cos(2.0*M_PI * u2);
    z1 = sqrt(-2.0 * log(u1)) * sin(2.0*M_PI * u2);

    generated = 1;

    return z0 * s + m;
} /*}}}2*/


