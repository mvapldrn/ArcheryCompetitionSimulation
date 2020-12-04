/*****************************************************************************
*** Name      : format.c                                                   ***
*** Purpose   : Defines the format of competition (i.e. distance, number   ***
***             of arrows to be shot and the target face (with scoring     ***
***             values)                                                    ***
*** Author    : Marcel van Apeldoorn <mvapldrn@gmail.com>                  ***
*** Copyright : 2013                                                       ***
*****************************************************************************/

/* --- Includes {{{1 */

#include <stdio.h>
#include <malloc.h>

#include "format.h"

/* --- Global data {{{1 */

extern int pretty_print;

Format q_format = {
    "QFormat",
    50.0,
    WA_80CM_6RINGS,
    72,
    0,
    CUMULATIVE
};

Format e_format = {
    "EFormat",
    50.0,
    WA_80CM_6RINGS,
    15,
    0,
    CUMULATIVE
};

/* --- Local prototypes {{{1 */

static const char *getMatchTypeString(const Format *format);

/* --- Implementation {{{1*/

const char *getFormatName(const Format *format) /*{{{2*/
{
    char *buf;

    const Face *face = getFace(format->facetype);

    buf = calloc(1024, sizeof(char));
    if (pretty_print) {
        snprintf(buf, 1024, "%4.1lfm at %s target face, Scoring system: %s (%s)",
                 format->distance,
                 face->name,
                 getMatchTypeString(format),
                 format->name);
    }
    else {
        snprintf(buf, 1024, "%4.1lf;\"%s\";%s;\"%s\"",
                 format->distance,
                 face->name,
                 getMatchTypeString(format),
                 format->name);
    }

    return buf;
} /*}}}2*/

static const char *getMatchTypeString(const Format *format) /*{{{2*/
{
    static char buf[80];

    switch (format->type) {
    case CUMULATIVE:
        if (pretty_print) {
            sprintf(buf, "Cumulative %d arrows", format->narrows);
        }
        else {
            sprintf(buf, "C;%d;0", format->narrows);
        }
        break;
    case SETSYSTEM:
        if (pretty_print) {
            sprintf(buf, "Set-system %d arrow sets, best of %d sets", format->narrows, format->best_of);
        }
        else {
            sprintf(buf, "S;%d;%d", format->narrows, format->best_of);
        }
        break;
    case SHOOTOFF:
        if (pretty_print) {
            sprintf(buf, "Single arrow shoot-off");
        }
        else {
            sprintf(buf, "SO;1;0");
        }
        break;
    case RANDOM:
        if (pretty_print) {
            sprintf(buf, "Random");
        }
        else {
            sprintf(buf, "R;0;0");
        }
        break;
    }

    return buf;
} /*}}}2*/
