/*****************************************************************************
*** Name      : random.h                                                   ***
*** Purpose   : Implements Guassian distributed random with Box-Muller     ***
*** Author    : Marcel van Apeldoorn <mvapldrn@gmail.com>                  ***
*** Copyright : 2013                                                       ***
*****************************************************************************/

#ifndef _RANDOM_H
#define _RANDOM_H

#ifdef WITH_GSL
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#endif

/* --- Interface {{{1 */

void initRandomGenerator(void);
double getGaussianRandom(double stddev);

#endif

