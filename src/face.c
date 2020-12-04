/*****************************************************************************
*** Name      : face.c                                                     ***
*** Purpose   : Defines the target face types and routines                 ***
*** Author    : Marcel van Apeldoorn <mvapldrn@gmail.com>                  ***
*** Copyright : 2013                                                       ***
*****************************************************************************/

/* --- Includes {{{1 */
#include <string.h>
#include <malloc.h>

#include "face.h"

/* --- Local data {{{1 */

static Face face[N_FACES];
static int faceinit = 0;

/* --- Local prototypes {{{1 */

static void faceInit(void);

/* --- Implementation {{{1*/

Face *getFace(FaceType type) /*{{{2*/
{
    /* Lazy face initialization */
    faceInit();
    return &face[type];
} /*}}}2*/

/* --- Local functions {{{1 */

static void faceInit(void) /*{{{2*/
{
    if (faceinit) return;

    Face *f;
    int i;

    /* I KNOW...... This could be done with for-loops instead of unrolled loops.
     * The loops are unrolled to make it more clear how the target faces are setup
     */

    /*
     * Official World archery 122cm target face
     * With 10 scoring zones 10,9,8,7,6,5,4,3,2,1
     */
    f = &face[WA_122CM_10RINGS];
    f->name = strdup("World Archery 122cm, 10 rings");
    f->n_rings = 10;
    f->radius = calloc(f->n_rings, sizeof(double));
    f->radius[0] = 610.0; /*[mm]*/
    f->radius[1] = 549.0; /*[mm]*/
    f->radius[2] = 488.0; /*[mm]*/
    f->radius[3] = 427.0; /*[mm]*/
    f->radius[4] = 366.0; /*[mm]*/
    f->radius[5] = 305.0; /*[mm]*/
    f->radius[6] = 244.0; /*[mm]*/
    f->radius[7] = 183.0; /*[mm]*/
    f->radius[8] = 122.0; /*[mm]*/
    f->radius[9] =  61.0; /*[mm]*/
    f->value = calloc(f->n_rings, sizeof(double));
    f->value[0]  = 1.0;
    f->value[1]  = 2.0;
    f->value[2]  = 3.0;
    f->value[3]  = 4.0;
    f->value[4]  = 5.0;
    f->value[5]  = 6.0;
    f->value[6]  = 7.0;
    f->value[7]  = 8.0;
    f->value[8]  = 9.0;
    f->value[9]  = 10.0;
    f->significant_decimals = 0;
    f->ring_for_2nd_so = 9;

    /*
     * Official World archery 80cm target face
     * With 10 scoring zones 10,9,8,7,6,5,4,3,2,1
     */
    f = &face[WA_80CM_10RINGS];
    f->name = strdup("World Archery 80cm, 10 rings");
    f->n_rings = 11;
    f->radius = calloc(f->n_rings, sizeof(double));
    f->radius[0]  = 400.0; /*[mm]*/
    f->radius[1]  = 360.0; /*[mm]*/
    f->radius[2]  = 320.0; /*[mm]*/
    f->radius[3]  = 280.0; /*[mm]*/
    f->radius[4]  = 240.0; /*[mm]*/
    f->radius[5]  = 200.0; /*[mm]*/
    f->radius[6]  = 160.0; /*[mm]*/
    f->radius[7]  = 120.0; /*[mm]*/
    f->radius[8]  =  80.0; /*[mm]*/
    f->radius[9]  =  40.0; /*[mm]*/
    f->radius[10] =  20.0; /*[mm]*/
    f->value = calloc(f->n_rings, sizeof(double));
    f->value[0]   = 1.0;
    f->value[1]   = 2.0;
    f->value[2]   = 3.0;
    f->value[3]   = 4.0;
    f->value[4]   = 5.0;
    f->value[5]   = 6.0;
    f->value[6]   = 7.0;
    f->value[7]   = 8.0;
    f->value[8]   = 9.0;
    f->value[9]   = 10.0;
    f->value[10]  = 10.0;
    f->significant_decimals = 0;
    f->ring_for_2nd_so = 10;

    /*
     * Official World archery 80cm target face
     * With 6 scoring zones 10,9,8,7,6,5
     */
    f = &face[WA_80CM_6RINGS];
    f->name = strdup("World Archery 80cm, 6 rings");
    f->n_rings = 7;
    f->radius = calloc(f->n_rings, sizeof(double));
    f->radius[0] = 240.0; /*[mm]*/
    f->radius[1] = 200.0; /*[mm]*/
    f->radius[2] = 160.0; /*[mm]*/
    f->radius[3] = 120.0; /*[mm]*/
    f->radius[4] =  80.0; /*[mm]*/
    f->radius[5] =  40.0; /*[mm]*/
    f->radius[6] =  20.0; /*[mm]*/
    f->value = calloc(f->n_rings, sizeof(double));
    f->value[0]  = 5.0;
    f->value[1]  = 6.0;
    f->value[2]  = 7.0;
    f->value[3]  = 8.0;
    f->value[4]  = 9.0;
    f->value[5]  = 10.0;
    f->value[6]  = 10.0;
    f->significant_decimals = 0;
    f->ring_for_2nd_so = 6;

    /*
     * Official World Archery 60cm target face
     * With 10 scoring zones 10,9,8,7,6,5,4,3,2,1
     */
    f = &face[WA_60CM_10RINGS];
    f->name = strdup("World Archery 60cm, 10 rings");
    f->n_rings = 10;
    f->radius = calloc(f->n_rings, sizeof(double));
    f->radius[0] = 300.0; /*[mm]*/
    f->radius[1] = 270.0; /*[mm]*/
    f->radius[2] = 240.0; /*[mm]*/
    f->radius[3] = 210.0; /*[mm]*/
    f->radius[4] = 180.0; /*[mm]*/
    f->radius[5] = 150.0; /*[mm]*/
    f->radius[6] = 120.0; /*[mm]*/
    f->radius[7] =  90.0; /*[mm]*/
    f->radius[8] =  60.0; /*[mm]*/
    f->radius[9] =  30.0; /*[mm]*/
    f->value = calloc(f->n_rings, sizeof(double));
    f->value[0]  = 1.0;
    f->value[1]  = 2.0;
    f->value[2]  = 3.0;
    f->value[3]  = 4.0;
    f->value[4]  = 5.0;
    f->value[5]  = 6.0;
    f->value[6]  = 7.0;
    f->value[7]  = 8.0;
    f->value[8]  = 9.0;
    f->value[9]  = 10.0;
    f->significant_decimals = 0;
    f->ring_for_2nd_so = -1;

    /*
     * Official World Archery 60cm target face
     * With 5 scoring zones 10,9,8,7,6
     */
    f = &face[WA_60CM_5RINGS];
    f->name = strdup("World Archery 60cm, 5 rings");
    f->n_rings = 5;
    f->radius = calloc(f->n_rings, sizeof(double));
    f->radius[0] = 150.0; /*[mm]*/
    f->radius[1] = 120.0; /*[mm]*/
    f->radius[2] =  90.0; /*[mm]*/
    f->radius[3] =  60.0; /*[mm]*/
    f->radius[4] =  30.0; /*[mm]*/
    f->value = calloc(f->n_rings, sizeof(double));
    f->value[0]  = 6.0;
    f->value[1]  = 7.0;
    f->value[2]  = 8.0;
    f->value[3]  = 9.0;
    f->value[4]  = 10.0;
    f->significant_decimals = 0;
    f->ring_for_2nd_so = -1;

    /*
     * Official World archery 40cm target face for recurve
     * With 5 scoring zones 10,9,8,7,6
     */
    f = &face[WA_40CM_5RINGS_RECURVE];
    f->name = strdup("World Archery 40cm, 5 rings, recurve");
    f->n_rings = 5;
    f->radius = calloc(f->n_rings, sizeof(double));
    f->radius[0] = 100.0; /*[mm]*/
    f->radius[1] =  80.0; /*[mm]*/
    f->radius[2] =  60.0; /*[mm]*/
    f->radius[3] =  40.0; /*[mm]*/
    f->radius[4] =  20.0; /*[mm]*/
    f->value = calloc(f->n_rings, sizeof(double));
    f->value[0]  = 6.0;
    f->value[1]  = 7.0;
    f->value[2]  = 8.0;
    f->value[3]  = 9.0;
    f->value[4]  = 10.0;
    f->significant_decimals = 0;
    f->ring_for_2nd_so = -1;

    /*
     * Official World archery 40cm target face for compound
     * With scoring zones x,9,8,7,6
     */
    f = &face[WA_40CM_5RINGS_COMPOUND];
    f->name = strdup("World Archery 40cm, 5 rings, compound");
    f->n_rings = 5;
    f->radius = calloc(f->n_rings, sizeof(double));
    f->radius[0] = 100.0; /*[mm]*/
    f->radius[1] =  80.0; /*[mm]*/
    f->radius[2] =  60.0; /*[mm]*/
    f->radius[3] =  40.0; /*[mm]*/
    f->radius[4] =  10.0; /*[mm]*/
    f->value = calloc(f->n_rings, sizeof(double));
    f->value[0]  = 6.0;
    f->value[1]  = 7.0;
    f->value[2]  = 8.0;
    f->value[3]  = 9.0;
    f->value[4]  = 10.0;
    f->significant_decimals = 0;
    f->ring_for_2nd_so = -1;

    /*
     * Experimental 38cm target face for compound
     * With scoring zones x,9,8,7,6
     * Rings 10 30 50 70 90mm
     */
    f = &face[EXP_38CM_5RINGS_COMPOUND];
    f->name = strdup("Experimental 38cm, 5 rings, compound (10 30 50 70 90mm)");
    f->n_rings = 5;
    f->radius = calloc(f->n_rings, sizeof(double));
    f->radius[0] = 90.0; /*[mm]*/
    f->radius[1] = 70.0; /*[mm]*/
    f->radius[2] = 50.0; /*[mm]*/
    f->radius[3] = 30.0; /*[mm]*/
    f->radius[4] = 10.0; /*[mm]*/
    f->value = calloc(f->n_rings, sizeof(double));
    f->value[0]  = 6.0;
    f->value[1]  = 7.0;
    f->value[2]  = 8.0;
    f->value[3]  = 9.0;
    f->value[4]  = 10.0;
    f->significant_decimals = 0;
    f->ring_for_2nd_so = -1;

    /*
     * Experimental 40cm target face for compound
     * With scoring zones x=11,10=10,9,8,7,6
     */
    f = &face[EXP_40CM_6RINGS_COMPOUND_X11];
    f->name = strdup("Experimental 40cm, 6 rings, compound, (10 20 40 60 80 100mm), X=11, 10=10, etc");
    f->n_rings = 6;
    f->radius = calloc(f->n_rings, sizeof(double));
    f->radius[0] = 100.0; /*[mm]*/
    f->radius[1] =  80.0; /*[mm]*/
    f->radius[2] =  60.0; /*[mm]*/
    f->radius[3] =  40.0; /*[mm]*/
    f->radius[4] =  20.0; /*[mm]*/
    f->radius[5] =  10.0; /*[mm]*/
    f->value = calloc(f->n_rings, sizeof(double));
    f->value[0]  = 6.0;
    f->value[1]  = 7.0;
    f->value[2]  = 8.0;
    f->value[3]  = 9.0;
    f->value[4]  = 10.0;
    f->value[5]  = 11.0;
    f->significant_decimals = 0;
    f->ring_for_2nd_so = -1;

    /*
     * Experimental 20cm target face for compound
     * With scoring zones 10,9,8,7,6,5,4,3,2,1
     */
    f = &face[EXP_20CM_10RINGS_COMPOUND];
    f->name = strdup("Experimental 20cm, 10 rings, compound");
    f->n_rings = 10;
    f->radius = calloc(f->n_rings, sizeof(double));
    f->radius[0] = 100.0; /*[mm]*/
    f->radius[1] =  90.0; /*[mm]*/
    f->radius[2] =  80.0; /*[mm]*/
    f->radius[3] =  70.0; /*[mm]*/
    f->radius[4] =  60.0; /*[mm]*/
    f->radius[5] =  50.0; /*[mm]*/
    f->radius[6] =  40.0; /*[mm]*/
    f->radius[7] =  30.0; /*[mm]*/
    f->radius[8] =  20.0; /*[mm]*/
    f->radius[9] =  10.0; /*[mm]*/
    f->value = calloc(f->n_rings, sizeof(double));
    f->value[0]  = 1.0;
    f->value[1]  = 2.0;
    f->value[2]  = 3.0;
    f->value[3]  = 4.0;
    f->value[4]  = 5.0;
    f->value[5]  = 6.0;
    f->value[6]  = 7.0;
    f->value[7]  = 8.0;
    f->value[8]  = 9.0;
    f->value[9]  = 10.0;
    f->significant_decimals = 0;
    f->ring_for_2nd_so = -1;

    /*
     * Experimental 36cm target face for compound
     * with scoring zones 10,9,8,7,6
     * Rings 9 27 45 63 81mm
     */
    f = &face[EXP_36CM_5RINGS_COMPOUND];
    f->name = strdup("Experimental 36cm, 5 rings, compound, (9 27 45 63 81mm)");
    f->n_rings = 5;
    f->radius = calloc(f->n_rings, sizeof(double));
    f->radius[0] = 81.0; /*[mm]*/
    f->radius[1] = 63.0; /*[mm]*/
    f->radius[2] = 45.0; /*[mm]*/
    f->radius[3] = 27.0; /*[mm]*/
    f->radius[4] =  9.0; /*[mm]*/
    f->value = calloc(f->n_rings, sizeof(double));
    f->value[0]  = 6.0;
    f->value[1]  = 7.0;
    f->value[2]  = 8.0;
    f->value[3]  = 9.0;
    f->value[4]  = 10.0;
    f->significant_decimals = 0;
    f->ring_for_2nd_so = -1;

    /*
     * Experimental 32cm target face for compound
     * with scoring zones 10,9,8,7,6
     * Rings 8 24 40 56 72mm
     */
    f = &face[EXP_32CM_5RINGS_COMPOUND];
    f->name = strdup("Experimental 32cm, 5 rings, compound, (8 24 40 56 72mm)");
    f->n_rings = 5;
    f->radius = calloc(f->n_rings, sizeof(double));
    f->radius[0] = 72.0; /*[mm]*/
    f->radius[1] = 56.0; /*[mm]*/
    f->radius[2] = 40.0; /*[mm]*/
    f->radius[3] = 24.0; /*[mm]*/
    f->radius[4] =  8.0; /*[mm]*/
    f->value = calloc(f->n_rings, sizeof(double));
    f->value[0]  = 6.0;
    f->value[1]  = 7.0;
    f->value[2]  = 8.0;
    f->value[3]  = 9.0;
    f->value[4]  = 10.0;
    f->significant_decimals = 0;
    f->ring_for_2nd_so = -1;

    /*
     * Experimental 80cm target face
     * With scoring zones x=11,10,9,8,7,6,5
     * where X scores 11
     */
    f = &face[EXP_80CM_6RINGS_X_SCORES_11];
    f->name = strdup("Experimental 80cm, 7 rings with X scores 11");
    f->n_rings = 7;
    f->radius = calloc(f->n_rings, sizeof(double));
    f->radius[0] = 240.0; /*[mm]*/
    f->radius[1] = 200.0; /*[mm]*/
    f->radius[2] = 160.0; /*[mm]*/
    f->radius[3] = 120.0; /*[mm]*/
    f->radius[4] =  80.0; /*[mm]*/
    f->radius[5] =  40.0; /*[mm]*/
    f->radius[6] =  20.0; /*[mm]*/
    f->value = calloc(f->n_rings, sizeof(double));
    f->value[0]  = 5.0;
    f->value[1]  = 6.0;
    f->value[2]  = 7.0;
    f->value[3]  = 8.0;
    f->value[4]  = 9.0;
    f->value[5]  = 10.0;
    f->value[6]  = 11.0;
    f->significant_decimals = 0;
    f->ring_for_2nd_so = -1;

    /*
     * Experimental 80cm 6 rings target face with decimal scoring
     */
    f = &face[EXP_80CM_6RINGS_DECIMAL_SCORING];
    f->name = strdup("Experimental 80cm 6 rings with decimal scoring");
    f->n_rings = 60;
    f->radius = calloc(f->n_rings, sizeof(double));
    f->value = calloc(f->n_rings, sizeof(double));
    for (i = 0; i < 60; i++) {
        f->radius[i] = 240.0 - 4.0*i; /*[mm]*/
        f->value[i] = 5.0 + i/10.0;
    }
    f->significant_decimals = 1;
    f->ring_for_2nd_so = -1;

    /*
     * Experimental (and theoretical) 122cm target face
     * With scoring zones 100,10,9,8,7,6,5,4,3,2,1
     * Creatign a pinhole with extreme score, to show that non-linear scoring might
     * introduce unfairness as well
     */
    f = &face[EXP_122CM_PINHOLE_EXTREMESCORE];
    f->name = strdup("Experimental 122cm, 11 rings, with pinhole scores 100,10,9,8,7,6,5,4,3,2,1");
    f->n_rings = 11;
    f->radius = calloc(f->n_rings, sizeof(double));
    f->radius[0] = 610.0; /*[mm]*/
    f->radius[1] = 549.0; /*[mm]*/
    f->radius[2] = 488.0; /*[mm]*/
    f->radius[3] = 427.0; /*[mm]*/
    f->radius[4] = 366.0; /*[mm]*/
    f->radius[5] = 305.0; /*[mm]*/
    f->radius[6] = 244.0; /*[mm]*/
    f->radius[7] = 183.0; /*[mm]*/
    f->radius[8] = 122.0; /*[mm]*/
    f->radius[9] =  61.0; /*[mm]*/
    f->radius[10]=   9.0; /*[mm]*/
    f->value = calloc(f->n_rings, sizeof(double));
    f->value[0]  = 1.0;
    f->value[1]  = 2.0;
    f->value[2]  = 3.0;
    f->value[3]  = 4.0;
    f->value[4]  = 5.0;
    f->value[5]  = 6.0;
    f->value[6]  = 7.0;
    f->value[7]  = 8.0;
    f->value[8]  = 9.0;
    f->value[9]  = 10.0;
    f->value[10] = 100.0;
    f->significant_decimals = 0;
    f->ring_for_2nd_so = -1;

    /*
     * Experimental World archery 110cm target face
     * With scoring zones 10,9,8,7,6,5,4,3,2,1
     */
    f = &face[EXP_110CM_10RINGS];
    f->name = strdup("Experimental 110cm, 10 rings");
    f->n_rings = 10;
    f->radius = calloc(f->n_rings, sizeof(double));
    f->radius[0] = 550.0; /*[mm]*/
    f->radius[1] = 495.0; /*[mm]*/
    f->radius[2] = 440.0; /*[mm]*/
    f->radius[3] = 385.0; /*[mm]*/
    f->radius[4] = 330.0; /*[mm]*/
    f->radius[5] = 275.0; /*[mm]*/
    f->radius[6] = 220.0; /*[mm]*/
    f->radius[7] = 165.0; /*[mm]*/
    f->radius[8] = 110.0; /*[mm]*/
    f->radius[9] =  55.0; /*[mm]*/
    f->value = calloc(f->n_rings, sizeof(double));
    f->value[0]  = 1.0;
    f->value[1]  = 2.0;
    f->value[2]  = 3.0;
    f->value[3]  = 4.0;
    f->value[4]  = 5.0;
    f->value[5]  = 6.0;
    f->value[6]  = 7.0;
    f->value[7]  = 8.0;
    f->value[8]  = 9.0;
    f->value[9]  = 10.0;
    f->significant_decimals = 0;
    f->ring_for_2nd_so = -1;

    /*
     * Experimental World archery 100cm target face
     * With scoring zones 10,9,8,7,6,5,4,3,2,1
     */
    f = &face[EXP_100CM_10RINGS];
    f->name = strdup("Experimental 100cm, 10 rings");
    f->n_rings = 10;
    f->radius = calloc(f->n_rings, sizeof(double));
    f->radius[0] = 500.0; /*[mm]*/
    f->radius[1] = 450.0; /*[mm]*/
    f->radius[2] = 400.0; /*[mm]*/
    f->radius[3] = 350.0; /*[mm]*/
    f->radius[4] = 300.0; /*[mm]*/
    f->radius[5] = 250.0; /*[mm]*/
    f->radius[6] = 200.0; /*[mm]*/
    f->radius[7] = 150.0; /*[mm]*/
    f->radius[8] = 100.0; /*[mm]*/
    f->radius[9] =  50.0; /*[mm]*/
    f->value = calloc(f->n_rings, sizeof(double));
    f->value[0]  = 1.0;
    f->value[1]  = 2.0;
    f->value[2]  = 3.0;
    f->value[3]  = 4.0;
    f->value[4]  = 5.0;
    f->value[5]  = 6.0;
    f->value[6]  = 7.0;
    f->value[7]  = 8.0;
    f->value[8]  = 9.0;
    f->value[9]  = 10.0;
    f->significant_decimals = 0;
    f->ring_for_2nd_so = -1;

    /*
     * Theoretical target that scores 10 in 1 ring only
     */
    f = &face[EXP_200CM_1RING];
    f->name = strdup("Experimental 200cm, 1 ring with score 10");
    f->n_rings = 1;
    f->radius = calloc(f->n_rings, sizeof(double));
    f->radius[0] = 1000.0; /*[mm]*/
    f->value = calloc(f->n_rings, sizeof(double));
    f->value[0]  = 10.0;
    f->significant_decimals = 0;
    f->ring_for_2nd_so = -1;

    /*
     * Experimental target 80cm 12 rings, (halves of normal)
     * With 20 scoring zones 20, 19, 18, 17 .. etc
     */
    f = &face[EXP_80CM_12RINGS];
    f->name = strdup("Exprimental 80cm 20 rings (only 12 scoring rings)");
    f->n_rings = 12;
    f->radius = calloc(f->n_rings, sizeof(double));
    f->radius[0]  = 240.0; /*[mm]*/
    f->radius[1]  = 220.0; /*[mm]*/
    f->radius[2]  = 200.0; /*[mm]*/
    f->radius[3]  = 180.0; /*[mm]*/
    f->radius[4]  = 160.0; /*[mm]*/
    f->radius[5]  = 140.0; /*[mm]*/
    f->radius[6]  = 120.0; /*[mm]*/
    f->radius[7]  = 100.0; /*[mm]*/
    f->radius[8]  =  80.0; /*[mm]*/
    f->radius[9]  =  60.0; /*[mm]*/
    f->radius[10] =  40.0; /*[mm]*/
    f->radius[11] =  20.0; /*[mm]*/
    f->value = calloc(f->n_rings, sizeof(double));
    f->value[0]  =  4.5;
    f->value[1]  =  5.0;
    f->value[2]  =  5.5;
    f->value[3]  =  6.0;
    f->value[4]  =  6.5;
    f->value[5]  =  7.0;
    f->value[6]  =  7.5;
    f->value[7]  =  8.0;
    f->value[8]  =  8.5;
    f->value[9]  =  9.0;
    f->value[10] =  9.5;
    f->value[11] = 10.0;
    f->significant_decimals = 1;
    f->ring_for_2nd_so = -1;

    faceinit = 1;
} /*}}}2*/

