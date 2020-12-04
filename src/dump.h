/*****************************************************************************
*** Name      : dump.h                                                     ***
*** Purpose   : Defines the dump types and routines                        ***
*** Author    : Marcel van Apeldoorn <mvapldrn@gmail.com>                  ***
*** Copyright : 2013                                                       ***
*****************************************************************************/

#ifndef _DUMP_H
#define _DUMP_H

/* --- Includes {{{1 */

#include <stdio.h>

/* --- Interface {{{1 */

void getOutput(const char *filename, const char *mode);
void interactiveOutput();
void outp(const char *fmt, ...);
void outp_close();
void fatal(const char *str);

#endif
