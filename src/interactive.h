/*****************************************************************************
*** Name      : interactive.h                                              ***
*** Purpose   : Interactive routines                                       ***
*** Author    : Marcel van Apeldoorn <mvapldrn@gmail.com>                  ***
*** Copyright : 2013                                                       ***
*****************************************************************************/

#ifndef _INTERACTIVE_H
#define _INTERACTIVE_H

/* --- Includes {{{1 */

/* --- Interface {{{1*/

extern int interactive;

void interactiveASLSimulation(void);
void interactiveQualificationRoundSimulation(void);
void interactiveEliminationStats(void);
void interactiveTeamEliminationStats(void);
void interactiveMixedTeamEliminationStats(void);
void interactiveCompetitionSimulation(void);
void interactiveCompetitionsSimulation(void);

#endif
