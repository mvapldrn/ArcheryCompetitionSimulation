/*****************************************************************************
*** Name      : format.h                                                   ***
*** Purpose   : Defines the format of competition (i.e. distance, number   ***
***             of arrows to be shot and the target face (with scoring     ***
***             values)                                                    ***
*** Author    : Marcel van Apeldoorn <mvapldrn@gmail.com>                  ***
*** Copyright : 2013                                                       ***
*****************************************************************************/

#ifndef _FORMAT_H
#define _FORMAT_H

/* --- Includes {{{1 */

#include "face.h"

/* --- Types {{{1 */

typedef enum {
    CUMULATIVE = 0,
    SETSYSTEM  = 1,
    SHOOTOFF   = 2,
    RANDOM     = 3
} MatchType;

#define FORMAT_NAME_LEN 256

typedef struct {
    char       name[FORMAT_NAME_LEN];  /* Custom name              */
    double     distance;   /* Shot at this distance            [m] */
    FaceType   facetype;   /* Shot on this target face type        */
    int        narrows;    /* This many arrows                     */
    MatchType  type;       /* Type of match (cumulative/set-system */
    int        best_of;    /* >0 if matchtype is set_system        */
} Format;

/* --- Interface {{{1*/

/*
 * Qualification format
 */
extern Format q_format;

/*
 * Elimination format
 */
extern Format e_format;

const char *getFormatName(const Format *format);

#endif
