/*****************************************************************************
*** Name      : debug.h                                                    ***
*** Purpose   : Debug statements                                           ***
*** Author    : Marcel van Apeldoorn <mvapldrn@gmail.com>                  ***
*** Copyright : 2013                                                       ***
*****************************************************************************/

#ifndef _DEBUG_H
#define _DEBUG_H

#include <stdio.h>

#ifdef DEBUG
#define D(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
#else
#define D(fmt, ...) if (0) fprintf(stderr, fmt, ##__VA_ARGS__)
#endif

#endif
