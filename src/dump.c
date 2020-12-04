/*****************************************************************************
*** Name      : dump.c                                                     ***
*** Purpose   : Defines the dump types and routines                        ***
*** Author    : Marcel van Apeldoorn <mvapldrn@gmail.com>                  ***
*** Copyright : 2013                                                       ***
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

