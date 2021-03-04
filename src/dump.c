/*****************************************************************************
*** Name      : dump.c                                                     ***
*** Purpose   : Defines the dump types and routines                        ***
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
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "dump.h"

/* --- Local data {{{1 */

static FILE *fp = NULL;

/* --- Local prototypes {{{1 */

/* --- Global functions {{{1 */

void interactiveOutput() /*{{{2*/
{
    printf("\nTo file (ENTER = no): "); fflush(stdout);
    char filename[1024];
    fgets(filename, 1024, stdin);
    int len = strlen(filename);
    if (len > 1) {
        /* Replace '\n' with '\0' */
        filename[len-1] = '\0';
        fp = fopen(filename, "w");
        if (fp == NULL) {
            fprintf(stderr, "Cannot open file %s for writing\n", filename);
        }
    }
} /*}}}2*/

void getOutput(const char *filename, const char *mode) /*{{{2*/
{
    fp = fopen(filename, mode);
    if (fp == NULL) {
        fprintf(stderr, "Cannot open file %s for writing\n", filename);
        exit(0);
    }
} /*}}}2*/

void outp(const char *fmt, ...) /*{{{2*/
{
    va_list ap;

    va_start(ap, fmt);
    if (fp == NULL) {
        /* To stdout */
        vprintf(fmt, ap);
    }
    else {
        vfprintf(fp, fmt, ap);
    }
    va_end(ap);
} /*}}}2*/

void outp_close() /*{{{2*/
{
    if (fp != NULL) fclose(fp);
} /*}}}2*/

void fatal(const char *str) /*{{{2*/
{
    fprintf(stderr, "FATAL: %s\n", str);
    exit(1);
}

