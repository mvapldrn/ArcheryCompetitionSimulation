/*****************************************************************************
*** Name      : interactive                                                ***
*** Purpose   : Archery competition simulation                             ***
*** Author    : Marcel van Apeldoorn <mvapldrn@gmail.com>                  ***
*** Copyright : 2013                                                       ***
*****************************************************************************/

/* --- Includes {{{1 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "archer.h"
#include "dump.h"
#include "format.h"
#include "interactive.h"
#include "qualification.h"
#include "elimination.h"

#include "debug.h"

/* --- Global data {{{1*/

/* Default interactive */
int interactive = 0;

extern double start_asl;
extern double end_asl;
extern double step_asl;
extern double t1asl1;
extern double t1asl2;
extern double t1asl3;
extern double t2asl1;
extern double t2asl2;
extern double t2asl3;
extern double xt1asl1;
extern double xt1asl2;
extern double xt2asl1;
extern double xt2asl2;

/* --- Local prototypes {{{1*/

static void interactiveSkillLevelRange(void);
static void interactiveQualificationFormat(void);
static void interactiveEliminationFormat(void);
static void interactiveASLDistribution(double*, double*, double*, double*, double*, double*, double*);
static void interactiveFormatName(Format *format);
static void interactiveTargetFace(Format *fmt);
static void interactiveMatchFormat(Format *fmt);
static double requestDouble(const char *str, double default_val);
static int requestInt(const char *str, int default_val);

/* --- Implementation {{{1*/

void interactiveASLSimulation(void) /*{{{2*/
{
    printf("\n");
    printf("ARCHER SKILL LEVEL SIMULATION\n");
    printf("=============================\n");
    printf("Perform simulations of a qualification round for one archer\n");
    printf("with a range of Skill Levels\n\n");

    interactiveSkillLevelRange();
    q_nruns = requestInt("Number of runs per archer", q_nruns);
    interactiveQualificationFormat();
    interactiveFormatName(&q_format);
    interactiveOutput();
} /*}}}2*/

void interactiveQualificationRoundSimulation(void) /*{{{2*/
{
    printf("\n");
    printf("QUALIFICATION ROUND SIMULATION\n");
    printf("==============================\n");
    printf("Perform a simulation of a qualification round\n");
    printf("With set of archers with distributed Archers Skill Level\n\n");

    interactiveASLDistribution(&asl1, &asl4, &asl8, &asl16, &asl32, &asl56, &asl104);
    interactiveQualificationFormat();
    q_nruns = requestInt("Number of runs per archer", q_nruns);
    interactiveOutput();
} /*}}}2*/

void interactiveCompetitionSimulation(void) /*{{{2*/
{
    printf("\n");
    printf("SINGLE COMPETITION SIMULATION\n");
    printf("=============================\n");
    printf("Perform simulation of a single competition; i.e. a qualification round\n");
    printf("followed by an eliminationround with distributed Archers Skill Levels\n\n");

    interactiveASLDistribution(&asl1, &asl4, &asl8, &asl16, &asl32, &asl56, &asl104);
    interactiveQualificationFormat();
    interactiveEliminationFormat();
    interactiveOutput();

} /*}}}2*/

void interactiveCompetitionsSimulation(void) /*{{{2*/
{
    printf("\n");
    printf("COMPETITIONS SIMULATION\n");
    printf("=======================\n");
    printf("Perform multiple simulations of a qualification round followed by an elimination round\n");
    printf("Performing according to its Archers Skill Level\n\n");

    interactiveASLDistribution(&asl1, &asl4, &asl8, &asl16, &asl32, &asl56, &asl104);
    interactiveQualificationFormat();
    interactiveEliminationFormat();
    q_nruns = requestInt("Number of times for entire round simulation", q_nruns);
    interactiveOutput();
} /*}}}2*/

void interactiveEliminationStats(void) /*{{{2*/
{
    printf("\n");
    printf("ELIMINATION STATISTICS\n");
    printf("======================\n");
    printf("Perform Monte Carlo simulations of a single elimination match between two archers; left and right\n");
    printf("Both archers perform according to their Archers Skill Level\n\n");

    interactiveSkillLevelRange();
    e_nruns = requestInt("Number of simulations", e_nruns);
    interactiveEliminationFormat();
    interactiveFormatName(&e_format);
    interactiveOutput();
} /*}}}2*/

void interactiveTeamEliminationStats() /*{{{2*/
{
    printf("\n");
    printf("TEAM ELIMINATION STATISTICS\n");
    printf("===========================\n");
    printf("Perform Monte Carlo simulations of a single team-elimination match between two teams; left and right\n");
    printf("Both teams perform according to their athletes Archers Skill Levels\n\n");

    printf("Team LEFT\n");
    t1asl1 = requestDouble("Archers Skill Level archer #1", t1asl1);
    t1asl2 = requestDouble("Archers Skill Level archer #2", t1asl2);
    t1asl3 = requestDouble("Archers Skill Level archer #3", t1asl3);
    printf("Team RIGHT\n");
    t2asl1 = requestDouble("Archers Skill Level archer #1", t2asl1);
    t2asl2 = requestDouble("Archers Skill Level archer #2", t2asl2);
    t2asl3 = requestDouble("Archers Skill Level archer #3", t2asl3);

    interactiveSkillLevelRange();
    e_nruns = requestInt("\nNumber of simulations", e_nruns);
    interactiveEliminationFormat();
    interactiveFormatName(&e_format);
    interactiveOutput();
} /*}}}2*/

void interactiveMixedTeamEliminationStats() /*{{{2*/
{
    printf("\n");
    printf("MIXED-TEAM ELIMINATION STATISTICS\n");
    printf("=================================\n");
    printf("Perform Monte Carlo simulations of a single mixed-team-elimination match between two mixed-teams; left and right\n");
    printf("Both teams perform according to their athletes Archers Skill Levels\n\n");

    printf("Mixed-Team LEFT\n");
    xt1asl1 = requestDouble("Archers Skill Level archer #1", xt1asl1);
    xt1asl2 = requestDouble("Archers Skill Level archer #2", xt1asl2);
    printf("Mixed-Team RIGHT\n");
    xt2asl1 = requestDouble("Archers Skill Level archer #1", xt2asl1);
    xt2asl2 = requestDouble("Archers Skill Level archer #2", xt2asl2);
    e_nruns = requestInt("\nNumber of simulations", e_nruns);
    interactiveEliminationFormat();
    interactiveFormatName(&e_format);
    interactiveOutput();
} /*}}}2*/

/* --- Local functions {{{1 */

static void interactiveSkillLevelRange(void) /*{{{2*/
{
    start_asl = requestDouble("Archers Skill Level start value", start_asl);
    end_asl = start_asl;
    end_asl = requestDouble("Archers Skill Level end value", end_asl);
    if (end_asl > start_asl) {
        step_asl = requestDouble("Archers Skill Level step value", step_asl);
    }
} /*}}}2*/

static void interactiveQualificationFormat(void) /*{{{2*/
{
    printf("\n");
    printf("QUALIFICATION FORMAT\n");
    printf("====================\n");
    interactiveTargetFace(&q_format);
    q_format.type = CUMULATIVE;
    q_format.narrows = requestInt("Cumulative scoring for how many arrows", q_format.narrows);
} /*}}}2*/

static void interactiveEliminationFormat(void) /*{{{2*/
{
    printf("\n");
    printf("ELIMINATION FORMAT\n");
    printf("==================\n");
    interactiveTargetFace(&e_format);
    interactiveMatchFormat(&e_format);
} /*}}}2*/

static void interactiveASLDistribution(double *a1, double *a4, double *a8, double *a16, double *a32, double *a56, double *a104) /*{{{2*/
{
    printf("\n");
    printf("ARCHERS SKILL LEVEL DISTRIBUTION\n");
    printf("================================\n");
    *a1   = requestDouble("Archers Skill Level of archer in position #1  ", *a1);
    if (*a4 > *a1) *a4 = *a1;
    *a4   = requestDouble("Archers Skill Level of archer in position #4  ", *a4);
    if (*a8 > *a4) *a8 = *a4;
    *a8   = requestDouble("Archers Skill Level of archer in position #8  ", *a8);
    if (*a16 > *a8) *a16 = *a8;
    *a16  = requestDouble("Archers Skill Level of archer in position #16 ", *a16);
    if (*a32 > *a16) *a32 = *a16;
    *a32  = requestDouble("Archers Skill Level of archer in position #32 ", *a32);
    if (*a56 > *a32) *a56 = *a32;
    *a56  = requestDouble("Archers Skill Level of archer in position #56 ", *a56);
    if (*a104 > *a56) *a104 = *a56;
    *a104 = requestDouble("Archers Skill Level of archer in position #104", *a104);
} /*}}}2*/

static void interactiveFormatName(Format *format) /*{{{2*/
{
    printf("\nName of format/round [%s]: ", format->name); fflush(stdout);
    char buf[FORMAT_NAME_LEN];
    fgets(buf, FORMAT_NAME_LEN-1, stdin);
    buf[FORMAT_NAME_LEN-1] = '\0';
    int len = strlen(buf);
    if (len > 1) {
        /* Replace '\n' with '\0' */
        buf[len-1] = '\0';
        strcpy(format->name, buf);
    }
} /*}}}2*/

static void interactiveTargetFace(Format *fmt) /*{{{2*/
{
    int i;
    while (1) {
        printf("\nTarget face\n");
        for (i = 0; i < N_FACES; i++) {
            Face *face = getFace(i);
            printf("  %d = %s\n", i, face->name);
        }
        int ft = requestInt("Select target face", fmt->facetype);
        if (ft >= 0 && ft < N_FACES) {
            fmt->facetype = ft;
            break;
        }
    }
    Face *face = getFace(fmt->facetype);
    printf("Selected target face: %s\n", face->name);
    for (i = 0; i < face->n_rings; i++) {
        printf("Ring %d : %.1f mm -> %.1f points\n", (i+1), face->radius[i], face->value[i]);
    }
    fmt->distance = requestDouble("Distance to shoot at in meters", fmt->distance);
} /*}}}2*/

static void interactiveMatchFormat(Format *fmt) /*{{{2*/
{
    int again;
    do {
        again = 0;
        printf("\nMatch format\n");
        printf("  %d = Cumulative score\n", CUMULATIVE);
        printf("  %d = Set system\n", SETSYSTEM);
        printf("  %d = Shoot-off only\n", SHOOTOFF);
        printf("  %d = Completely random\n", RANDOM);
        int mt = requestInt("Select match system", fmt->type);
        switch (mt) {
        case CUMULATIVE:
        case SETSYSTEM:
        case SHOOTOFF:
        case RANDOM:
            fmt->type = mt;
            break;
        default:
            again = 1;
            break;
        }
    } while (again);

    switch (fmt->type) {
    case CUMULATIVE:
        fmt->narrows = requestInt("Cumulative scoring for how many arrows (per archer)", fmt->narrows);
        break;
    case SETSYSTEM:
        fmt->narrows = requestInt("Set system, how many arrows per set (per archer)", fmt->narrows);
        fmt->best_of = requestInt("Set system, best of how many sets", fmt->best_of);
        if (fmt->best_of > MAX_SETS) {
            fprintf(stderr, "Maximum number of sets is %d\n", MAX_SETS);
            fmt->best_of = MAX_SETS;
        }
        break;
    }
} /*}}}2*/

static double requestDouble(const char *str, double default_val) /*{{{2*/
{
    double retval = default_val;
    int BUFSIZE = 256;
    char buf[BUFSIZE];

    D("requestDouble(%s, %lf)\n", str, default_val);

    buf[BUFSIZE-1] = '\0';
    printf("%s [%lf]: ", str, default_val);
    fflush(stdout);
    fgets(buf, BUFSIZE-1, stdin);

    D("buf = %s\n", buf);

    if (strlen(buf) > 1) {
        retval = atof(buf);
    }

    printf("-> %lf\n", retval);

    return retval;
} /*}}}2*/

static int requestInt(const char *str, int default_val) /*{{{2*/
{
    int retval = default_val;
    int BUFSIZE = 256;
    char buf[BUFSIZE];
    buf[BUFSIZE-1] = '\0';
    printf("%s [%d]: ", str, default_val);
    fflush(stdout);
    fgets(buf, BUFSIZE-1, stdin);

    if (strlen(buf) > 1) {
        retval = atoi(buf);
    }

    printf("-> %d\n", retval);

    return retval;
} /*}}}2*/


