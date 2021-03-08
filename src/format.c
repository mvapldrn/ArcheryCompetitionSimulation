/*****************************************************************************
*** Name      : format.c                                                   ***
*** Purpose   : Defines the format of competition (i.e. distance, number   ***
***             of arrows to be shot and the target face (with scoring     ***
***             values)                                                    ***
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

#include <stdio.h>
#include <malloc.h>

#include "format.h"

/* --- Global data {{{1 */

extern int pretty_print;

Format q_format = {
    "QFormat",
    70.0,
    WA_122CM_10RINGS,
    72,
    CUMULATIVE,
    0
};

Format e_format = {
    "EFormat",
    70.0,
    WA_122CM_10RINGS,
    3,
    SETSYSTEM,
    5
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
        snprintf(buf, 1024, "%4.1lf \"%s\" %s \"%s\"",
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
            sprintf(buf, "C %d 0", format->narrows);
        }
        break;
    case SETSYSTEM:
        if (pretty_print) {
            sprintf(buf, "Set-system %d arrow sets, best of %d sets", format->narrows, format->best_of);
        }
        else {
            sprintf(buf, "S %d %d", format->narrows, format->best_of);
        }
        break;
    case SHOOTOFF:
        if (pretty_print) {
            sprintf(buf, "Single arrow shoot-off");
        }
        else {
            sprintf(buf, "SO 1 0");
        }
        break;
    case RANDOM:
        if (pretty_print) {
            sprintf(buf, "Random");
        }
        else {
            sprintf(buf, "R 0 0");
        }
        break;
    }

    return buf;
} /*}}}2*/
