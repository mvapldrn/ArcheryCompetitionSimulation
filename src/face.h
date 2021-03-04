/*****************************************************************************
*** Name      : face.h                                                     ***
*** Purpose   : Defines the target face types and routines                 ***
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

#ifndef _FACE_H
#define _FACE_H

/* --- Constants {{{1 */

typedef enum {
    WA_122CM_10RINGS                    = 0,
    WA_80CM_10RINGS                     = 1,
    WA_80CM_6RINGS                      = 2,
    WA_60CM_10RINGS                     = 3,
    WA_60CM_5RINGS                      = 4,
    WA_40CM_5RINGS_RECURVE              = 5,
    WA_40CM_5RINGS_COMPOUND             = 6,
    EXP_38CM_5RINGS_COMPOUND            = 7,
    EXP_40CM_6RINGS_COMPOUND_X11        = 8,
    EXP_20CM_10RINGS_COMPOUND           = 9,
    EXP_36CM_5RINGS_COMPOUND            = 10,
    EXP_32CM_5RINGS_COMPOUND            = 11,
    EXP_80CM_6RINGS_X_SCORES_11         = 12,
    EXP_80CM_6RINGS_DECIMAL_SCORING     = 13,
    EXP_122CM_PINHOLE_EXTREMESCORE      = 14,
    EXP_110CM_10RINGS                   = 15,
    EXP_100CM_10RINGS                   = 16,
    EXP_200CM_1RING                     = 17,
    EXP_80CM_12RINGS                    = 18,

} FaceType;

#define N_FACES 19

/* --- Data types {{{1 */

typedef struct {
    /*
     * Name of the target face
     */
    char   *name;
    /*
     * Number of ring on the target face
     */
    int     n_rings;
    /*
     * Array of n_rings size, defining the radius (in mm) of the
     * target face rings, where ring index 0 is the outermost ring (thus
     * target size)
     */
    double *radius;
    /*
     * The value of the ring, same indices as radius array
     */
    double *value;
    /*
     * Number of siginificant decimals in scoring. This is used to decide
     * whether we use integer scoring (0 significant decimals) or decimal
     * scoring (1/10ths or even 1/100ths)
     */
    int     significant_decimals;
    /*
     * What ring (index) is used to decide a second shoot off (or -1 if
     * there is no second shootoff
     */
    int     ring_for_2nd_so;
} Face;

/* --- Prototypes {{{1 */

Face *getFace(FaceType type);

#endif
