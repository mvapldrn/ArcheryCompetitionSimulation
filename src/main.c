/*****************************************************************************
*** Name      : main                                                       ***
*** Purpose   : Archery competition simulation                             ***
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
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "random.h"
#include "asl_distribution.h"
#include "dump.h"
#include "face.h"
#include "score.h"
#include "modes.h"
#include "format.h"
#include "archer.h"
#include "team.h"
#include "skilllevelscores.h"
#include "qualification.h"
#include "elimination.h"
#include "interactive.h"

/* --- Global data {{{1*/

char *name_of_population = POPULATION_FROM;

/* Default pretty-print */
int pretty_print = 0;

/* Default with progress */
int with_progress = 0;

/* Default single match values */
double start_asl =  75.0;
double end_asl   = 120.0;
double step_asl  =   1.0;

double arrow_diameter = ARROW_DIAMETER;

long seed = 0L;

/* --- Local prototypes {{{1*/

static void help();

/* --- Implementation {{{1*/

int main(int argc, char *argv[]) /*{{{2*/
{
    int i = 0;
    int j = 0;
    int tcnt = 0;
    int cnt = 0;
    int opt = 0;

    int mode = 0; /* No mode */

    int option_index = 0;
    static struct option long_options[] = {

        { "score",                     no_argument,       NULL, MODE_SCORE },
        { "qualification",             no_argument,       NULL, MODE_QUALIFICATION },
        { "elimination",               no_argument,       NULL, MODE_ELIMINATION },
        { "team-elimination",          no_argument,       NULL, MODE_TEAM_ELIMINATION },
        { "mixed-team-elimination",    no_argument,       NULL, MODE_MIXED_TEAM_ELIMINATION },
        { "competition",               no_argument,       NULL, MODE_COMPETITION },
        { "competitions",              no_argument,       NULL, MODE_COMPETITIONS },

        { "interactive",               no_argument,       NULL, 906 },
        { "output",                    required_argument, NULL, 907 },
        { "output-append",             required_argument, NULL, 917 },
        { "help",                      no_argument,       NULL, 908 },

        { "level-1",                   required_argument, NULL, 1000 },
        { "level-4",                   required_argument, NULL, 1001 },
        { "level-8",                   required_argument, NULL, 1002 },
        { "level-16",                  required_argument, NULL, 1003 },
        { "level-32",                  required_argument, NULL, 1004 },
        { "level-56",                  required_argument, NULL, 1005 },
        { "level-104",                 required_argument, NULL, 1006 },
        { "level-name",                required_argument, NULL, 1007 },

        { "team1-level-1",             required_argument, NULL, 1011 },
        { "team1-level-2",             required_argument, NULL, 1012 },
        { "team1-level-3",             required_argument, NULL, 1013 },
        { "team2-level-1",             required_argument, NULL, 1021 },
        { "team2-level-2",             required_argument, NULL, 1022 },
        { "team2-level-3",             required_argument, NULL, 1023 },

        { "start-level",               required_argument, NULL, 1100 },
        { "end-level",                 required_argument, NULL, 1101 },
        { "level-step",                required_argument, NULL, 1102 },

        { "distance",                  required_argument, NULL, 1103 },

        { "target-face",               required_argument, NULL, 1104 },

        { "arrow-diameter",            required_argument, NULL, 1126 },

        { "n-arrows",                  required_argument, NULL, 1105 },
        { "n-arrows-qualification",    required_argument, NULL, 1115 },
        { "n-arrows-elimination",      required_argument, NULL, 1125 },

        { "best-of-sets",              required_argument, NULL, 1106 },

        { "format-name",               required_argument, NULL, 1107 },
        { "format-name-qualification", required_argument, NULL, 1117 },
        { "format-name-elimination",   required_argument, NULL, 1127 },

        { "format",                    required_argument, NULL, 1108 },
        { "format-qualification",      required_argument, NULL, 1118 },
        { "format-elimination",        required_argument, NULL, 1128 },

        { "n-runs",                    required_argument, NULL, 1200 },
        { "n-runs-qualification",      required_argument, NULL, 1210 },
        { "n-runs-elimination",        required_argument, NULL, 1220 },

        { "cut-high-loser",            required_argument, NULL, 1301 },
        { "high-loser",                required_argument, NULL, 1302 },

        { "pretty-print",              no_argument,       NULL, 1400 },
        { "seed",                      required_argument, NULL, 1401 },
        { "progress",                  no_argument,       NULL, 1402 },


        { "arrow-diameter",            required_argument, NULL, 999 },

        {0,0,0,0}
    };

    while ( (opt = getopt_long(argc, argv, "", long_options, &option_index)) != -1) {

        switch (opt) {
        case 1000: asl1   = atof(optarg); break;
        case 1001: asl4   = atof(optarg); break;
        case 1002: asl8   = atof(optarg); break;
        case 1003: asl16  = atof(optarg); break;
        case 1004: asl32  = atof(optarg); break;
        case 1005: asl56  = atof(optarg); break;
        case 1006: asl104 = atof(optarg); break;
        case 1007: name_of_population = strdup(optarg); break;

        case 1011: xt1asl1 = t1asl1  = atof(optarg); break;
        case 1012: xt1asl2 = t1asl2  = atof(optarg); break;
        case 1013:           t1asl3  = atof(optarg); break;
        case 1021: xt2asl1 = t2asl1  = atof(optarg); break;
        case 1022: xt2asl2 = t2asl2  = atof(optarg); break;
        case 1023:           t2asl3  = atof(optarg); break;

        case 1100: start_asl = atof(optarg); break;
        case 1101: end_asl   = atof(optarg); break;
        case 1102: step_asl  = atof(optarg); break;

        case 1103: q_format.distance = e_format.distance = atof(optarg); break;

        case 1104: q_format.facetype = e_format.facetype = atoi(optarg); break;

        case 1105: q_format.narrows = e_format.narrows = atoi(optarg); break;
        case 1115: q_format.narrows = atoi(optarg); break;
        case 1125: e_format.narrows = atoi(optarg); break;
        case 1126: arrow_diameter = (double)atof(optarg); break;

        case 1106: q_format.best_of = e_format.best_of = atoi(optarg); break;

        case 1107:
            strcpy(q_format.name, optarg);
            strcpy(e_format.name, optarg);
            break;
        case 1117:
            strcpy(q_format.name, optarg);
            break;
        case 1127:
            strcpy(e_format.name, optarg);
            break;

        case 1108: q_format.type = e_format.type = atoi(optarg); break;
        case 1118: q_format.type = atoi(optarg); break;
        case 1128: e_format.type = atoi(optarg); break;

        case 1200: q_nruns = e_nruns = atoi(optarg); break;
        case 1210: q_nruns = atoi(optarg); break;
        case 1220: e_nruns = atoi(optarg); break;

        case 1301: cut_high_loser = atoi(optarg); break;
        case 1302: high_loser = atoi(optarg); break;

        case 1400: pretty_print = 1; break;
        case 1401: seed = (long)atoi(optarg); break;
        case 1402: with_progress = 1; break;

        case MODE_SCORE:
        case MODE_QUALIFICATION:
        case MODE_ELIMINATION:
        case MODE_TEAM_ELIMINATION:
        case MODE_MIXED_TEAM_ELIMINATION:
        case MODE_COMPETITION:
        case MODE_COMPETITIONS:
            mode = opt;
            break;

        case 906:
            interactive = 1;
            break;

        case 907:
            getOutput(optarg, "w");
            break;

        case 917:
            getOutput(optarg, "a");
            break;

        case 908:
            help();
            return 0;

        case 999: arrow_diameter = atof(optarg); break;
        }
    }

    initRandomGenerator();

    switch (mode) {
    case MODE_SCORE:
        modeScore();
        break;

    case MODE_QUALIFICATION:
        modeQualification();
        break;

    case MODE_ELIMINATION:
        modeElimination();
        break;

    case MODE_TEAM_ELIMINATION:
        modeTeamElimination();
        break;

    case MODE_MIXED_TEAM_ELIMINATION:
        modeMixedTeamElimination();
        break;

    case MODE_COMPETITION:
        modeCompetition();
        break;

    case MODE_COMPETITIONS:
        modeCompetitions();
        break;

    default:
        fprintf(stderr, "Mode option is required!\n");
    }

    return 0;
} /*}}}2*/

static void help() /*{{{2*/
{
    int i;

    printf("Archery statistical simulator from Marcel van Apeldoorn (mvapldrn@gmail.com)\n");

    printf("\nUsage: archerystats [option (<value>)]\n");

    printf("\nModes: SCORE | QUALIFICATION | ELIMINATION | COMPETITION | COMPETITIONS\n");

    printf("\nMode: SCORE\n");
    printf("--score                            Perform simulations of a score (ASL -> score)\n");
    printf("--start-level=<level>              Start (lowest) Archers Skill Level\n");
    printf("--end-level=<level>                End (highest) Archers Skill Level\n");
    printf("--level-step=<step>                Steps in Archers Skill Level\n");
    printf("--distance=<distance>              Shooting distance in [m]\n");
    printf("--target-face=<face-code>          Target face code\n");
    printf("--n-arrows=<n>                     Number of arrows to shoot\n");
    printf("--format-name=<name>               Name of all formats (for logging)\n");
    printf("--n-runs=<n>                       Number of times the score is simulated\n");

    printf("\nMode: QUALIFICATION\n");
    printf("--qualification                    Perform simulations of a qualification round\n");
    printf("--level-1=<level>                  Archers Skill Level of the #1 ranked archer\n");
    printf("--level-4=<level>                  Archers Skill Level of the #4 ranked archer\n");
    printf("--level-8=<level>                  Archers Skill Level of the #8 ranked archer\n");
    printf("--level-16=<level>                 Archers Skill Level of the #16 ranked archer\n");
    printf("--level-32=<level>                 Archers Skill Level of the #32 ranked archer\n");
    printf("--level-56=<level>                 Archers Skill Level of the #56 ranked archer\n");
    printf("--level-104=<level>                Archers Skill Level of the #104 ranked archer\n");
    printf("--distance=<distance>              Shooting distance in [m]\n");
    printf("--target-face=<face-code>          Target face code\n");
    printf("--n-arrows=<n>                     Number of arrows to shoot\n");
    printf("--format-name=<name>               Name of all formats (for logging)\n");
    printf("--n-runs=<n>                       Number of times a score is generated per archer (for averaging skill level)\n");

    printf("\nMode: ELIMINATION\n");
    printf("--elimination                      Perform simulations of eliminations between two archers\n");
    printf("--start-level=<level>              Start (lowest) Archers Skill Level\n");
    printf("--end-level=<level>                End (highest) Archers Skill Level\n");
    printf("--level-step=<step>                Steps in Archers Skill Level\n");
    printf("--distance=<distance>              Shooting distance in [m]\n");
    printf("--target-face=<face-code>          Target face code\n");
    printf("--n-arrows=<n>                     Number of arrows to shoot\n");
    printf("--best-of-sets=<n-sets>            Best of <n-sets> sets\n");
    printf("--format-name=<name>               Name of all formats (for logging)\n");
    printf("--format=<format>                  Format code\n");
    printf("--n-runs=<n>                       Number op times an elimination is run between two archers\n");

    printf("\nMode: TEAM ELIMINATION\n");
    printf("--team-elimination                 Perform simulation of team elimination between two teams\n");
    printf("--team1-level-1=<level>            Archers Skill Level archer #1\n");
    printf("--team1-level-2=<level>            Archers Skill Level archer #2\n");
    printf("--team1-level-3=<level>            Archers Skill Level archer #3\n");
    printf("--team2-level-1=<level>            Archers Skill Level archer #1\n");
    printf("--team2-level-2=<level>            Archers Skill Level archer #2\n");
    printf("--team2-level-3=<level>            Archers Skill Level archer #3\n");
    printf("--start-level=<level>              Start (lowest) Archers Skill Level of best archer\n");
    printf("--end-level=<level>                End (highest) Archers Skill Level of best archer in team\n");
    printf("--level-step=<step>                Steps in Archers Skill Level\n");
    printf("--distance=<distance>              Shooting distance in [m]\n");
    printf("--target-face=<face-code>          Target face code\n");
    printf("--n-arrows=<n>                     Number of arrows to shoot per archer\n");
    printf("--best-of-sets=<n-sets>            Best of <n-sets> sets\n");
    printf("--format-name=<name>               Name of all formats (for logging)\n");
    printf("--format=<format>                  Format code\n");
    printf("--n-runs=<n>                       Number op times an elimination is run between two archers\n");

    printf("\nMode: MIXED-TEAM ELIMINATION\n");
    printf("--mixed-team-elimination           Perform simulation of mixed-team elimination between two teams\n");
    printf("--team1-level-1=<level>            Archers Skill Level archer #1\n");
    printf("--team1-level-2=<level>            Archers Skill Level archer #2\n");
    printf("--team2-level-1=<level>            Archers Skill Level archer #1\n");
    printf("--team2-level-2=<level>            Archers Skill Level archer #2\n");
    printf("--start-level=<level>              Start (lowest) Archers Skill Level of best archer\n");
    printf("--end-level=<level>                End (highest) Archers Skill Level of best archer in team\n");
    printf("--level-step=<step>                Steps in Archers Skill Level\n");
    printf("--distance=<distance>              Shooting distance in [m]\n");
    printf("--target-face=<face-code>          Target face code\n");
    printf("--n-arrows=<n>                     Number of arrows to shoot per archer\n");
    printf("--best-of-sets=<n-sets>            Best of <n-sets> sets\n");
    printf("--format-name=<name>               Name of all formats (for logging)\n");
    printf("--format=<format>                  Format code\n");
    printf("--n-runs=<n>                       Number op times an elimination is run between two archers\n");

    printf("\nMode: COMPETITION\n");
    printf("--competition                      Perform simulations of a full competition (i.e. qualification followed by eliminations)\n");
    printf("--level-1=<level>                  Archers Skill Level of the #1 ranked archer\n");
    printf("--level-4=<level>                  Archers Skill Level of the #4 ranked archer\n");
    printf("--level-8=<level>                  Archers Skill Level of the #8 ranked archer\n");
    printf("--level-16=<level>                 Archers Skill Level of the #16 ranked archer\n");
    printf("--level-32=<level>                 Archers Skill Level of the #32 ranked archer\n");
    printf("--level-56=<level>                 Archers Skill Level of the #56 ranked archer\n");
    printf("--level-104=<level>                Archers Skill Level of the #104 ranked archer\n");
    printf("--distance=<distance>              Shooting distance in [m]\n");
    printf("--target-face=<face-code>          Target face code\n");
    printf("--n-arrows-qualification=<n>       Number fo arrows to shoot in qualification\n");
    printf("--n-arrows-elimination=<n>        Number fo arrows to shoot in elimination\n");
    printf("--best-of-sets=<n-sets>            Best of <n-sets> sets\n");
    printf("--format-name-qualification=<name> Name of qualification format (for logging)\n");
    printf("--format-name-elimination=<name>   Name of elimination format (for logging)\n");
    printf("--format-qualification=<format>    Format code of qualification\n");
    printf("--format-elimination=<format>      Format code of elimination\n\n");
    printf("--n-runs=<n>                       Number of times a score is generated per archer (for averaging skill level) in qualification only\n");

    printf("\nMode: COMPETITIONS\n");
    printf("--competitions                     Perform simulations of a full competition (i.e. qualification followed by eliminations)\n");
    printf("--level-1=<level>                  Archers Skill Level of the #1 ranked archer\n");
    printf("--level-4=<level>                  Archers Skill Level of the #4 ranked archer\n");
    printf("--level-8=<level>                  Archers Skill Level of the #8 ranked archer\n");
    printf("--level-16=<level>                 Archers Skill Level of the #16 ranked archer\n");
    printf("--level-32=<level>                 Archers Skill Level of the #32 ranked archer\n");
    printf("--level-56=<level>                 Archers Skill Level of the #56 ranked archer\n");
    printf("--level-104=<level>                Archers Skill Level of the #104 ranked archer\n");
    printf("--distance=<distance>              Shooting distance in [m]\n");
    printf("--target-face=<face-code>          Target face code\n");
    printf("--n-arrows-qualification=<n>       Number fo arrows to shoot in qualification\n");
    printf("--n-arrows-eliminations=<n>        Number fo arrows to shoot in elimination\n");
    printf("--best-of-sets=<n-sets>            Best of <n-sets> sets\n");
    printf("--format-name-qualification=<name> Name of qualification format (for logging)\n");
    printf("--format-name-elimination=<name>   Name of elimination format (for logging)\n");
    printf("--format-qualification=<format>    Format code of qualification\n");
    printf("--format-elimination=<format>      Format code of elimination\n\n");
    printf("--n-runs-qualification=<n>         Number of times a score is generated per archer (for averaging skill level) in qualification only\n");
    printf("--n-runs=<n>                       Number of times the entire competition is run\n");
    printf("--high-loser=<n>                   How much positions lower is an archer called a high-loser\n");
    printf("--cut-high-loser=<n>               To be a high-loser the q-rank needs to be at least n\n");

    printf("\n<face-code>\n");
    for (i = 0; i < N_FACES; i++) {
        Face *face = getFace(i);
        printf(" %2d = %s\n", i, face->name);
    }

    printf("\n<format>\n");
    printf("0 = Cumulative scoring\n");
    printf("1 = Set system\n");
    printf("2 = Single arrow shootoff closest to center\n");
    printf("3 = Pure random (flip a coin)\n");

    printf("\nGeneric options\n");
    printf("--interactive                      Start in interactive mode\n");
    printf("--output=<file>                    Write output to file <file>\n");
    printf("--output-append=<file>             Append output to file <file>\n");
    printf("--pretty-print                     Pretty print the results (default is CSV print of results)\n\n");
    printf("--help                             This help file\n");

} /*}}}2*/

