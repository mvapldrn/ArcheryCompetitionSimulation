/*****************************************************************************
*** Name      : score.c                                                    ***
*** Purpose   : Defines the types and routines for scoring model           ***
*** Author    : Marcel van Apeldoorn <mvapldrn@gmail.com>                  ***
*** Copyright : 2013                                                       ***
*****************************************************************************/

/* --- Includes {{{1 */
#include <math.h>

#include "random.h"
#include "score.h"
#include "team.h"
#include "debug.h"

#define REVISED_ARCHERS_SKILL_LEVEL 1

/* --- External globals {{{1*/

extern double arrow_diameter;
#ifdef WITH_GSL
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
extern gsl_rng *gslr;
#endif

/* --- Constants {{{1 */

const double SCORE_GRANULARITY = 0.1;
const double MIN_MEASURABLE = 1.0;

/* --- Local prototypes {{{1 */

static double getArrowValueFromPosition(double d_from_center, const Face *face);
static double getArrowValueBySkillLevel(double lvl, const Face *face, double dist);
static double computeF(double lvl, const Face *face, double dist, int i);
static double computeW(double lvl, double dist);
static double round_to_n_digits(double x, int n);

/* --- Implementation {{{1 */

Result scoreCompare(double left_score, double right_score) /*{{{2*/
/*
 * Compares two scores, returns DRAW if score is within SCORE_GRANULARITY,
 * else returns LEFT_WINS or RIGHT_WINS
 */
{
    if (fabs(left_score-right_score) < SCORE_GRANULARITY/2.0) return DRAW;
    if (left_score > right_score) return LEFT_WINS;
    return RIGHT_WINS;
} /*}}}2*/

Result shootoffCompare(double left_distance_from_center, double right_distance_from_center) /*{{{2*/
/*
 * Compares two shootoff arrows distances from center. Returns DRAW is arrow positions
 * from center are less than MIN_MEASURABLE (i.e. undecided) else returns LEFT_WINS_SHOOTOFF
 * or RIGHT_WINS_SHOOTOFF
 */
{
    double diff = fabs(left_distance_from_center - right_distance_from_center);
    if (diff < MIN_MEASURABLE) return DRAW;
    if (left_distance_from_center < right_distance_from_center) {
        return LEFT_WINS_SHOOTOFF;
    }
    return RIGHT_WINS_SHOOTOFF;
} /*}}}2*/

Result teamShootoffCompare(const Team *left, double left_d[3], const Team *right, double right_d[3], const Face *face) /*{{{2*/
/*
 * A team consists of 3 archers each shooting a single shoot-off arrow. This routine first compares
 * the score (i.e. highest score wins) if score is equal, the closest arrow to center wins. If undecided, then
 * 2nd cloeset arrow wins (etc)
 * Routine returns DRAW if all undecided or LEFT_WINS_SHOOTOFF or RIGHT_WINS_SHOOTOFF
 */
{
    double left_score = 0.0;
    double right_score = 0.0;

    left_score = getArrowValueFromPosition(left_d[0], face) +
                 getArrowValueFromPosition(left_d[1], face) +
                 getArrowValueFromPosition(left_d[2], face);

    right_score = getArrowValueFromPosition(right_d[0], face) +
                  getArrowValueFromPosition(right_d[1], face) +
                  getArrowValueFromPosition(right_d[2], face);

    Result res = scoreCompare(left_score, right_score);
    if (res != DRAW) {
        /* We have a result */
        return res;
    }

    /* Might do this a bit more smarter, but for now works :-) */

    int l1, l2, l3;
    int r1, r2, r3;

    /* Find indices of smallest to largest for left team and right team */
    if (left_d[0] <= left_d[1] && left_d[0] <= left_d[2]) l1 = 0;
    if (left_d[1] <= left_d[0] && left_d[1] <= left_d[2]) l1 = 1;
    if (left_d[2] <= left_d[1] && left_d[2] <= left_d[0]) l1 = 2;
    switch (l1) {
        case 0:
            if (left_d[1] <= left_d[2]) { l2 = 1; l3 = 2; } else { l2 = 2; l3 = 1; }
            break;
        case 1:
            if (left_d[0] <= left_d[2]) { l2 = 0; l3 = 2; } else { l2 = 2; l3 = 0; }
            break;
        case 2:
            if (left_d[0] <= left_d[1]) { l2 = 0; l3 = 1; } else { l2 = 1; l3 = 0; }
            break;
    }

    if (right_d[0] <= right_d[1] && right_d[0] <= right_d[2]) r1 = 0;
    if (right_d[1] <= right_d[0] && right_d[1] <= right_d[2]) r1 = 1;
    if (right_d[2] <= right_d[1] && right_d[2] <= right_d[0]) r1 = 2;
    switch (r1) {
        case 0:
            if (right_d[1] <= right_d[2]) { r2 = 1; r3 = 2; } else { r2 = 2; r3 = 1; }
            break;
        case 1:
            if (right_d[0] <= right_d[2]) { r2 = 0; r3 = 2; } else { r2 = 2; r3 = 0; }
            break;
        case 2:
            if (right_d[0] <= right_d[1]) { r2 = 0; r3 = 1; } else { r2 = 1; r3 = 0; }
            break;
    }

    /* Now r1 = closest right arrow, l1 is closest left arrow, etc. */

    res = shootoffCompare(left_d[l1], right_d[r1]);
    if (res != DRAW) {
        /* We have a result */
        return res;
    }
    res = shootoffCompare(left_d[l2], right_d[r2]);
    if (res != DRAW) {
        /* We have a result */
        return res;
    }
    res = shootoffCompare(left_d[l3], right_d[r3]);
    if (res != DRAW) {
        /* We have a result */
        return res;
    }

    return DRAW;
} /*}}}2*/

Result mixedTeamShootoffCompare(const MixedTeam *left, double left_d[2], const MixedTeam *right, double right_d[2], const Face *face) /*{{{2*/
/*
 * A mixed-team consists of 2 archers each shooting a single shoot-off arrow. This routine first compares
 * the score (i.e. highest score wins) if score is equal, the closest arrow to center wins. If undecided, then
 * 2nd cloeset arrow wins
 * Routine returns DRAW if all undecided or LEFT_WINS_SHOOTOFF or RIGHT_WINS_SHOOTOFF
 */
{
    double left_score = 0.0;
    double right_score = 0.0;

    left_score = getArrowValueFromPosition(left_d[0], face) +
                 getArrowValueFromPosition(left_d[1], face);

    right_score = getArrowValueFromPosition(right_d[0], face) +
                  getArrowValueFromPosition(right_d[1], face);

    Result res = scoreCompare(left_score, right_score);
    if (res != DRAW) {
        /* We have a result */
        return res;
    }

    /* Might do this a bit more smarter, but for now works :-) */

    int l1, l2;
    int r1, r2;

    /* Find indices of smallest to largest for left team and right team */
    if (left_d[0] <= left_d[1]) {
        l1 = 0;
        l2 = 1;
    }
    else {
        l1 = 1;
        l2 = 0;
    }

    if (right_d[0] <= right_d[1]) {
        r1 = 0;
        r2 = 1;
    }
    else {
        r1 = 1;
        r2 = 0;
    }

    /* Now r1 = closest right arrow, l1 is closest left arrow, etc. */

    res = shootoffCompare(left_d[l1], right_d[r1]);
    if (res != DRAW) {
        /* We have a result */
        return res;
    }
    res = shootoffCompare(left_d[l2], right_d[r2]);
    if (res != DRAW) {
        /* We have a result */
        return res;
    }

    return DRAW;
} /*}}}2*/

double getScore(double lvl, const Face *face, double dist, int n_arrows) /*{{{2*/
/*
 * Returns a score based on the skill level of the archer for given format
 * lvl = Archers Skill Level
 * face = Target face shot on
 * dist = distance shot at in [m]
 * n_arrows = number of arrows shot
 */
{
    double score = 0.0;
    int i;
    for (i = 0; i < n_arrows; i++) {
        score += getArrowValue(lvl, face, dist);
    }
#if 0
    printf ("Return score %lf\n", score);
#endif
    return score;
} /*}}}2*/

double getArrowValue(double lvl, const Face *face, double dist) /*{{{2*/
/*
 * Returns a single arrow score based on the skill level of the archer for given format
 * where;
 * lvl = Archers Skill Level
 * face = Target face shot on
 * dist = distance shot at in [m]
 */
{
    double d_from_center = getArrowPosition(lvl, dist);
    return getArrowValueFromPosition(d_from_center, face);
} /*}}}2*/

double getArrowPosition(double lvl, double dist) /*{{{2*/
/*
 * Returns a single arrow random position (mm from center) based on
 * the skill level of the archer for a given distance
 * where;
 * lvl = Archers Skill Level
 * dist = distance shot at in [m]
 */
{
    double stddev, x, y, d_from_center;
    double r1, r2;

    D("\ngetRandomSingleArrowPosition()\n");
    D("  distance -> %lf\n", dist);
    stddev = computeW(lvl, dist)/dist;
    D("  stddev -> %lf\n", stddev);
    r1 = getGaussianRandom(stddev);
    r2 = getGaussianRandom(stddev);
    D("  r1 -> %lf , r2 -> %lf\n", r1, r2);

    x = r1*dist;
    D("  x -> %lf\n", x);
    y = r2*dist;
    D("  y -> %lf\n", y);
    d_from_center = sqrt(x*x+y*y);
    D("  d_from_center -> %lf\n", d_from_center);

    return d_from_center;
} /*}}}2*/

double getScoreBySkillLevel(double lvl, const Face *face, double dist, int n_arrows) /*{{{2*/
/*
 * Returns the expected score (rounded to a valid value) for an archer based on the
 * theoretical archers skill level, where;
 * lvl = Archers Skill Level
 * face = face shot at
 * dist = distance shot at in [m]
 * n_arrows = number of arrows shot
 */
{
    /* Scoring depends on whether the face allows decimal scoring or integer scoring */
    double score = (n_arrows * getArrowValueBySkillLevel(lvl, face, dist));
    return round_to_n_digits(score, face->significant_decimals);
} /*}}}2*/

/* --- Internals {{{1 */

static double getArrowValueFromPosition(double d_from_center, const Face *face) /*{{{2*/
/*
 * Returns a single arrow score based on distance from center of face (in mm)
 * and a given target face
 * where;
 * d_from_center = Arrow centerline to center of face in mm
 * face = Target face shot on
 */
{
    double touching_radius = d_from_center - arrow_diameter/2.0;
    int i = face->n_rings;
    while (i > 0) {
        i--;
        if ( touching_radius <= face->radius[i]) {
            return face->value[i];
        }
    }
    return 0.0;
} /*}}}2*/

static double getArrowValueBySkillLevel(double lvl, const Face *face, double dist) /*{{{2*/
/*
 * Returns the expected single arrow score for an archer based on the theoretical
 * archers skill level, with:
 * lvl = Archers Skill Level
 * face = face shot at
 * dist = distance shot at in [m]
 */
{
    int n = face->n_rings;
    double score = 0.0;

    int i;
    for (i = n-1; i >= 0; i--) {
        double F1 = computeF(lvl, face, dist, i);
        double F2 = 0.0;
        if (i < n-1) {
            F2 = computeF(lvl, face, dist, i+1);
        }
        score += (F1-F2)*face->value[i];
    }

    return score;
} /*}}}2*/

static double computeF(double lvl, const Face *face, double dist, int i) /*{{{2*/
/*
 * returns the probability that an arrow hits within the radius of ring i
 * where;
 * lvl = Archers Skill Level
 * face = face shot at
 * dist = distance shot at in [m]
 * i = ring i (starting from 0 for the outer ring)
 */
{
    double W = computeW(lvl, dist);
    double f = (face->radius[i] + arrow_diameter/2.0)/W;

    return 1.0 - exp( -0.5*f*f );
} /*}}}2*/

static double computeW(double lvl, double dist) /*{{{2*/
/*
 * This is the revised Australian Model for archery score developed by J.Park (2014)
 * It assumes a circular group with a standard deviation that depends on the distance. The
 * computed value is the probability density function for an archer of level <lvl> shooting
 * at a distance <dist> in [m]
 * The revision takes the fact into account that at longer distances the standard deviation
 * increases not only linearly with distance but also quadratic with distance
 * The probability is in mm's from the center
 */
{
#ifdef REVISED_ARCHERS_SKILL_LEVEL
    const double A =-0.027;
    const double B = 2.570;
    const double E = 0.815;
    const double F = 0.185;

    return dist * (E + F*dist/50.0) * exp(A*lvl + B);
#else
    const double A =-0.027;
    const double B = 2.37;
    const double C = 0.004;

    return dist * exp(A*lvl + B + C*dist);
#endif
} /*}}}2*/

static double round_to_n_digits(double x, int n) /*{{{2*/
{
    double scale = pow(10.0, n);
    return round(x*scale)/scale;
} /*}}}2*/
