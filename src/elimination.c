/*****************************************************************************
*** Name      : elimination.c                                              ***
*** Purpose   : Defines the elimination phase routines                     ***
*** Author    : Marcel van Apeldoorn <mvapldrn@gmail.com>                  ***
*** Copyright : 2013                                                       ***
*****************************************************************************/

/* --- Includes {{{1 */

#include <math.h>
#include <stdlib.h>

#include "archer.h"
#include "dump.h"
#include "mixedteam.h"
#include "team.h"
#include "score.h"
#include "elimination.h"
#include "qualification.h"
#include "format.h"

#include "debug.h"

extern int pretty_print;
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

EliminationStatistics elimstats;

int e_nruns = 1000;

typedef struct {
    long n_win_with_lower_score[MAX_STAGES];
    long n_win_with_equal_score_no_so[MAX_STAGES];
    long n_win_after_sets[MAX_SETS][MAX_STAGES];
    long n_expected_wins[MAX_STAGES];
    long n_win_after_shootoff[MAX_STAGES];
    long n_second_shootoff_required[MAX_STAGES];
    long n_top_q16_e16;
    long n_top_q8_e8;
    long n_top_q4_e4;
} Counters;

/* --- Local function prototypes {{{1 */

static Result doMatch(const Face*, Archer*, Archer*, int, Counters*);
static Result doTeamMatch(Team*, Team*, int, Counters*);
static Result doMixedTeamMatch(MixedTeam*, MixedTeam*, int, Counters*);
static Result doSetMatch(Archer*, Archer*, int, Counters*);
static Result doCumulativeMatch(Archer*, Archer*, int, Counters*);
static Result doShootOff(const Face*, Archer*, Archer*, int, Counters*);
static Result doRandomMatch(Archer*, Archer*, int, Counters*);
static Result doSetTeamMatch(Team*, Team*, int, Counters*);
static Result doCumulativeTeamMatch(Team*, Team*, int, Counters*);
static Result doTeamShootOff(Team*, Team*, int, Counters*);
static Result doTeamRandomMatch(Team*, Team*, int, Counters*);
static Result doSetMixedTeamMatch(MixedTeam*, MixedTeam*, int, Counters*);
static Result doCumulativeMixedTeamMatch(MixedTeam*, MixedTeam*, int, Counters*);
static Result doMixedTeamShootOff(MixedTeam*, MixedTeam*, int, Counters*);
static Result doMixedTeamRandomMatch(MixedTeam*, MixedTeam*, int, Counters*);
static double getFinalRankingCorrectness(void);

/* --- Global functions {{{1 */

void initEliminationStats() /*{{{2*/
{
    int i;
    int s;

    elimstats.n_competitions = 0;
    for (s = 0; s < MAX_STAGES; s++) {
        elimstats.n_matches[s] = 0L;
        for (i = 0; i < MAX_SETS; i++) {
            resetStat(&(elimstats.n_win_after_sets[i][s]));
        }
        resetStat(&(elimstats.n_win_after_shootoff[s]));
        resetStat(&(elimstats.n_win_with_lower_score[s]));
        resetStat(&(elimstats.n_win_with_equal_score_no_so[s]));
    }
} /*}}}2*/

void doEliminationRound(void) /*{{{2*/
/*
 * Performs a simulation of an elimination round from 1/48th to gold for the
 * current set of archers with top 8 rules and shootoff rules, etc.
 */
{
    int i;
    int me_rank;
    int opponent_rank;
    int me_idx;
    int opponent_idx;
    Archer *me;
    Archer *opponent;
    const Face *face = getFace(e_format.facetype);
    Counters counters = {0};

    /* 1/48
     * In 1/48 elimination round pairs are created without top 8
     *  9 vs 104
     * 10 vs 103
     * 11 vs 102
     * Opponent-rank = 113 - me-rank
     */
    for (me_rank = 9; me_rank <= 56; me_rank++) {
        opponent_rank = 113-me_rank;

        /* Indices into arrays */
        me_idx = me_rank-1;
        opponent_idx = opponent_rank-1;

        me = archerrank[me_idx];
        opponent = archerrank[opponent_idx];

        switch (doMatch(face, me, opponent, F48TH, &counters)) {
        case LEFT_WINS:
        case LEFT_WINS_SHOOTOFF:

            /* If 'me' ranked higher than 'opponent' (which it should!) then this
             * counts for an expected win
             */
            if (me->q_rank < opponent->q_rank) counters.n_expected_wins[F48TH]++;

            /* Do nothing */
            break;

        case RIGHT_WINS:
        case RIGHT_WINS_SHOOTOFF:

            /* If 'opponent' ranked higher than 'opponent' (which it cannot!) then this
             * counts for an expected win
             */
            if (opponent->q_rank < me->q_rank) counters.n_expected_wins[F48TH]++;

            /* Switch places in array */
            archerrank[me_idx] = opponent;
            archerrank[opponent_idx] = me;
            break;

        default:
            fatal("doMatch() unknown result in 1/48");
        }
    }
    /* Sort everyone from rank 57 onwards on Q score */
    rankArchersOnQualifyingRank(57, 104);

    /* 1/24
     * In 1/24 elimination round pairs are created without top 8
     *  9 vs 56
     * 10 vs 55
     * 11 vs 54
     * Opponent-rank = 65 - me-rank
     */
    for (me_rank = 9; me_rank <= 32; me_rank++) {
        opponent_rank = 65-me_rank;

        /* Indices into arrays */
        me_idx = me_rank-1;
        opponent_idx = opponent_rank-1;

        me = archerrank[me_idx];
        opponent = archerrank[opponent_idx];

        switch (doMatch(face, me, opponent, F24TH, &counters)) {
        case LEFT_WINS:
        case LEFT_WINS_SHOOTOFF:

            /* If 'me' ranked higher than 'opponent' then this
             * counts for an expected win
             */
            if (me->q_rank < opponent->q_rank) counters.n_expected_wins[F24TH]++;

            /* Do nothing */
            break;

        case RIGHT_WINS:
        case RIGHT_WINS_SHOOTOFF:

            /* If 'opponent' ranked higher than 'opponent' then this
             * counts for an expected win
             */
            if (opponent->q_rank < me->q_rank) counters.n_expected_wins[F24TH]++;

            /* Switch places in array */
            archerrank[me_idx] = opponent;
            archerrank[opponent_idx] = me;
            break;

        default:
            fatal("doMatch() unknown result in 1/24");
        }
    }
    /* Sort everyone from rank 33 to 56 on Q score */
    rankArchersOnQualifyingRank(33, 56);

    /* 1/16
     * In 1/16 elimination round pairs are created including top 8
     *  1 vs 32
     *  2 vs 31
     *  3 vs 30
     * Opponent-rank = 33 - me-rank
     */
    for (me_rank = 1; me_rank <= 16; me_rank++) {
        opponent_rank = 33-me_rank;

        /* Indices into arrays */
        me_idx = me_rank-1;
        opponent_idx = opponent_rank-1;

        me = archerrank[me_idx];
        opponent = archerrank[opponent_idx];

        switch (doMatch(face, me, opponent, F16TH, &counters)) {
        case LEFT_WINS:
        case LEFT_WINS_SHOOTOFF:

            /* If 'me' ranked higher than 'opponent' then this
             * counts for an expected win
             */
            if (me->q_rank < opponent->q_rank) counters.n_expected_wins[F16TH]++;

            /* Do nothing */
            break;

        case RIGHT_WINS:
        case RIGHT_WINS_SHOOTOFF:

            /* If 'opponent' ranked higher than 'opponent' then this
             * counts for an expected win
             */
            if (opponent->q_rank < me->q_rank) counters.n_expected_wins[F16TH]++;

            /* Switch places in array */
            archerrank[me_idx] = opponent;
            archerrank[opponent_idx] = me;
            break;

        default:
            fatal("doMatch() unknown result in 1/16");
        }
    }
    /* Sort everyone from rank 17 to 32 on Q score */
    rankArchersOnQualifyingRank(17, 32);

    /* Count archers that qualified top 16 and are now in last 16 */
    for (me_rank = 1; me_rank <= 16; me_rank++) {
        me_idx = me_rank-1;
        me = archerrank[me_idx];
        if (me->q_rank <= 16) counters.n_top_q16_e16++;
    }

    /* 1/8
     * In 1/8 elimination round pairs are created including top 8
     *  1 vs 16
     *  2 vs 15
     *  3 vs 14
     * Opponent-rank = 17 - me-rank
     */
    for (me_rank = 1; me_rank <= 8; me_rank++) {
        opponent_rank = 17-me_rank;

        /* Indices into arrays */
        me_idx = me_rank-1;
        opponent_idx = opponent_rank-1;

        me = archerrank[me_idx];
        opponent = archerrank[opponent_idx];

        switch (doMatch(face, me, opponent, F8TH, &counters)) {
        case LEFT_WINS:
        case LEFT_WINS_SHOOTOFF:

            /* If 'me' ranked higher than 'opponent' then this
             * counts for an expected win
             */
            if (me->q_rank < opponent->q_rank) counters.n_expected_wins[F8TH]++;

            /* Do nothing */
            break;

        case RIGHT_WINS:
        case RIGHT_WINS_SHOOTOFF:

            /* If 'opponent' ranked higher than 'opponent' then this
             * counts for an expected win
             */
            if (opponent->q_rank < me->q_rank) counters.n_expected_wins[F8TH]++;

            /* Switch places in array */
            archerrank[me_idx] = opponent;
            archerrank[opponent_idx] = me;
            break;

        default:
            fatal("doMatch() unknown result in 1/8");
        }
    }
    /* Sort everyone from rank 9 to 16 on Q score */
    rankArchersOnQualifyingRank(9, 16);

    /* Count archers that qualified in top 8 and are now in last 8 */
    for (me_rank = 1; me_rank <= 8; me_rank++) {
        me_idx = me_rank-1;
        me = archerrank[me_idx];
        if (me->q_rank <= 8) counters.n_top_q8_e8++;
    }

    /* 1/4
     * In 1/4 elimination round pairs are created including top 8
     *  1 vs 8
     *  2 vs 7
     *  3 vs 6
     * Opponent-rank = 9 - me-rank
     */
    for (me_rank = 1; me_rank <= 4; me_rank++) {
        opponent_rank = 9-me_rank;

        /* Indices into arrays */
        me_idx = me_rank-1;
        opponent_idx = opponent_rank-1;

        me = archerrank[me_idx];
        opponent = archerrank[opponent_idx];

        switch (doMatch(face, me, opponent, F4TH, &counters)) {
        case LEFT_WINS:
        case LEFT_WINS_SHOOTOFF:

            /* If 'me' ranked higher than 'opponent' then this
             * counts for an expected win
             */
            if (me->q_rank < opponent->q_rank) counters.n_expected_wins[F4TH]++;

            /* Do nothing */
            break;

        case RIGHT_WINS:
        case RIGHT_WINS_SHOOTOFF:

            /* If 'opponent' ranked higher than 'opponent' then this
             * counts for an expected win
             */
            if (opponent->q_rank < me->q_rank) counters.n_expected_wins[F4TH]++;

            /* Switch places in array */
            archerrank[me_idx] = opponent;
            archerrank[opponent_idx] = me;
            break;

        default:
            fatal("doMatch() unknown result in 1/4");
        }
    }
    /* Sort everyone from rank 5 to 8 on Q score */
    rankArchersOnQualifyingRank(5, 8);

    /* Count archers that qualified top 4 and are now in last 4 */
    for (me_rank = 1; me_rank <= 4; me_rank++) {
        me_idx = me_rank-1;
        me = archerrank[me_idx];
        if (me->q_rank <= 4) counters.n_top_q4_e4++;
    }

    /* 1/2
     * In 1/2 elimination round pairs are created including top 8
     *  1 vs 4
     *  2 vs 3
     * Opponent-rank = 5 - me-rank
     */
    for (me_rank = 1; me_rank <= 2; me_rank++) {
        opponent_rank = 5-me_rank;

        me_idx = me_rank-1;
        opponent_idx = opponent_rank-1;

        /* Indices into arrays */
        me = archerrank[me_idx];
        opponent = archerrank[opponent_idx];

        switch (doMatch(face, me, opponent, FSEMI, &counters)) {
        case LEFT_WINS:
        case LEFT_WINS_SHOOTOFF:

            /* If 'me' ranked higher than 'opponent' then this
             * counts for an expected win
             */
            if (me->q_rank < opponent->q_rank) counters.n_expected_wins[FSEMI]++;

            /* Do nothing */
            break;

        case RIGHT_WINS:
        case RIGHT_WINS_SHOOTOFF:

            /* If 'opponent' ranked higher than 'opponent' then this
             * counts for an expected win
             */
            if (opponent->q_rank < me->q_rank) counters.n_expected_wins[FSEMI]++;

            /* Switch places in arrays */
            archerrank[me_idx] = opponent;
            archerrank[opponent_idx] = me;
            break;

        default:
            fatal("doMatch() unknown result in 1/2");
        }
    }

    /* Bronze */
    me_rank = 3;
    opponent_rank = 4;

    me_idx = me_rank-1;
    opponent_idx = opponent_rank-1;

    me = archerrank[me_idx];
    opponent = archerrank[opponent_idx];

    switch (doMatch(face, me, opponent, FBRONZE, &counters)) {
    case LEFT_WINS:
    case LEFT_WINS_SHOOTOFF:

        /* If 'me' ranked higher than 'opponent' then this
         * counts for an expected win
         */
        if (me->q_rank < opponent->q_rank) counters.n_expected_wins[FBRONZE]++;

        /* Do nothing */
        break;

    case RIGHT_WINS:
    case RIGHT_WINS_SHOOTOFF:

        /* If 'opponent' ranked higher than 'opponent' then this
         * counts for an expected win
         */
        if (opponent->q_rank < me->q_rank) counters.n_expected_wins[FBRONZE]++;

        /* Switch places */
        archerrank[me_idx] = opponent;
        archerrank[opponent_idx] = me;
        break;

    default:
        fatal("doMatch() unknown result in Bronze");
    }

    /* Gold */
    me_rank = 1;
    opponent_rank = 2;

    me_idx = me_rank-1;
    opponent_idx = opponent_rank-1;

    me = archerrank[me_idx];
    opponent = archerrank[opponent_idx];

    switch (doMatch(face, me, opponent, FGOLD, &counters)) {
    case LEFT_WINS:
    case LEFT_WINS_SHOOTOFF:

        /* If 'me' ranked higher than 'opponent' then this
         * counts for an expected win
         */
        if (me->q_rank < opponent->q_rank) counters.n_expected_wins[FGOLD]++;

        /* Do nothing */
        break;

    case RIGHT_WINS:
    case RIGHT_WINS_SHOOTOFF:

        /* If 'opponent' ranked higher than 'opponent' then this
         * counts for an expected win
         */
        if (opponent->q_rank < me->q_rank) counters.n_expected_wins[FGOLD]++;

        /* Switch places */
        archerrank[me_idx] = opponent;
        archerrank[opponent_idx] = me;
        break;

    default:
        fatal("doMatch() unknown result in Gold");
    }

    /*
     * Now that the final ranking is known, set the elimination rank
     */
    for (i = 0; i < 104; i++) {
        archerrank[i]->e_rank = (i+1);
    }

    /* Add all counters to the overall statistics */
    for (int stage = 0; stage < MAX_STAGES; stage++) {
        addStat(&(elimstats.n_expected_wins[stage]), counters.n_expected_wins[stage]);
        addStat(&(elimstats.n_win_with_lower_score[stage]), counters.n_win_with_lower_score[stage]);
        addStat(&(elimstats.n_win_with_equal_score_no_so[stage]), counters.n_win_with_equal_score_no_so[stage]);
        addStat(&(elimstats.n_win_after_shootoff[stage]), counters.n_win_after_shootoff[stage]);
        addStat(&(elimstats.n_second_shootoff_required[stage]), counters.n_second_shootoff_required[stage]);
        for (int set = 0; set < MAX_SETS; set++) {
            addStat(&(elimstats.n_win_after_sets[set][stage]), counters.n_win_after_sets[set][stage]);
        }
    }

    addStat(&(elimstats.n_top_q16_e16), counters.n_top_q16_e16);
    addStat(&(elimstats.n_top_q8_e8), counters.n_top_q8_e8);
    addStat(&(elimstats.n_top_q4_e4), counters.n_top_q4_e4);

    addStat(&(elimstats.fc), getFinalRankingCorrectness());

    elimstats.n_competitions += 1;
} /*}}}2*/

void doTeamEliminationRound(void) /*{{{2*/
/*
 * Performs a simulation of a team elimination round from 1/8th to gold for the
 * current set of teams with team shootoff rules, etc.
 */
{
    int i;
    int me_rank;
    int opponent_rank;
    int me_idx;
    int opponent_idx;
    Team *me;
    Team *opponent;
    Counters counters = {0};

    /* 1/8 */
    for (me_rank = 1; me_rank <= 8; me_rank++) {
        opponent_rank = 17-me_rank;

        me_idx = me_rank-1;
        opponent_idx = opponent_rank-1;

        me = teamrank[me_idx];
        opponent = teamrank[opponent_idx];

        switch (doTeamMatch(me, opponent, F8TH, &counters)) {

        case LEFT_WINS:
        case LEFT_WINS_SHOOTOFF:
            /* Do nothing */
            break;

        case RIGHT_WINS:
        case RIGHT_WINS_SHOOTOFF:
            /* Switch places */
            teamrank[me_idx] = opponent;
            teamrank[opponent_idx] = me;
            break;

        default:
            fatal("doTeamMatch() unknown result in 1/8");
        }
    }
    /* Sort everyone from rank 9 to 16 on Q score */
    rankTeams(9, 16);

    /* 1/4 */
    for (me_rank = 1; me_rank <= 4; me_rank++) {
        opponent_rank = 9-me_rank;

        me_idx = me_rank-1;
        opponent_idx = opponent_rank-1;

        me = teamrank[me_idx];
        opponent = teamrank[opponent_idx];

        switch (doTeamMatch(me, opponent, F4TH, &counters)) {

        case LEFT_WINS:
        case LEFT_WINS_SHOOTOFF:
            /* Do nothing */
            break;

        case RIGHT_WINS:
        case RIGHT_WINS_SHOOTOFF:
            /* Switch places */
            teamrank[me_idx] = opponent;
            teamrank[opponent_idx] = me;
            break;

        default:
            fatal("doTeamMatch() unknown result in 1/4");
        }
    }
    /* Sort everyone from rank 5 to 8 on Q score */
    rankTeams(5, 8);

    /* 1/2 */
    for (me_rank = 1; me_rank <= 2; me_rank++) {
        opponent_rank = 5-me_rank;

        me_idx = me_rank-1;
        opponent_idx = opponent_rank-1;

        me = teamrank[me_idx];
        opponent = teamrank[opponent_idx];

        switch (doTeamMatch(me, opponent, FSEMI, &counters)) {

        case LEFT_WINS:
        case LEFT_WINS_SHOOTOFF:
            /* Do nothing */
            break;

        case RIGHT_WINS:
        case RIGHT_WINS_SHOOTOFF:
            /* Switch places */
            teamrank[me_idx] = opponent;
            teamrank[opponent_idx] = me;
            break;

        default:
            fatal("doTeamMatch() unknown result in 1/2");
        }
    }

    /* Bronze */
    me_rank = 3;
    opponent_rank = 4;

    me_idx = me_rank-1;
    opponent_idx = opponent_rank-1;

    me = teamrank[me_idx];
    opponent = teamrank[opponent_idx];

    switch (doTeamMatch(me, opponent, FBRONZE, &counters)) {

    case LEFT_WINS:
    case LEFT_WINS_SHOOTOFF:
        /* Do nothing */
        break;

    case RIGHT_WINS:
    case RIGHT_WINS_SHOOTOFF:
        /* Switch places */
        teamrank[me_idx] = opponent;
        teamrank[opponent_idx] = me;
        break;

    default:
        fatal("doTeamMatch() unknown result in Bronze");
    }

    /* Gold */
    me_rank = 1;
    opponent_rank = 2;

    me_idx = me_rank-1;
    opponent_idx = opponent_rank-1;

    me = teamrank[me_idx];
    opponent = teamrank[opponent_idx];

    switch (doTeamMatch(me, opponent, FGOLD, &counters)) {

    case LEFT_WINS:
    case LEFT_WINS_SHOOTOFF:
        /* Do nothing */
        break;

    case RIGHT_WINS:
    case RIGHT_WINS_SHOOTOFF:
        /* Switch places */
        teamrank[me_idx] = opponent;
        teamrank[opponent_idx] = me;
        break;

    default:
        fatal("doTeamMatch() unknown result in Gold");
    }

    for (i = 0; i < 16; i++) {
        teamrank[i]->e_rank = (i+1);
    }
} /*}}}2*/

void doMixedTeamEliminationRound(void) /*{{{2*/
/*
 * Performs a simulation of a mixed-team elimination round from 1/24 to gold for the
 * current set of mixed-teams with team shootoff rules, etc.
 */
{
    int i;
    int me_rank;
    int opponent_rank;
    int me_idx;
    int opponent_idx;
    MixedTeam *me;
    MixedTeam *opponent;
    Counters counters = {0};


    /* 1/12
     * In 1/12 elimination round pairs are created without top 8
     *  9 vs 24
     * 10 vs 23
     * 11 vs 22
     * Opponent-rank = 33 - me-rank
     */
    for (me_rank = 9; me_rank <= 16; me_rank++) {
        opponent_rank = 33-me_rank;

        /* Indices into arrays */
        me_idx = me_rank-1;
        opponent_idx = opponent_rank-1;

        me = mixedteamrank[me_idx];
        opponent = mixedteamrank[opponent_idx];

        switch (doMixedTeamMatch(me, opponent, F24TH, &counters)) {
        case LEFT_WINS:
        case LEFT_WINS_SHOOTOFF:

            /* If 'me' ranked higher than 'opponent' then this
             * counts for an expected win
             */
            if (me->q_rank < opponent->q_rank) counters.n_expected_wins[F24TH]++;

            /* Do nothing */
            break;

        case RIGHT_WINS:
        case RIGHT_WINS_SHOOTOFF:

            /* If 'opponent' ranked higher than 'opponent' then this
             * counts for an expected win
             */
            if (opponent->q_rank < me->q_rank) counters.n_expected_wins[F24TH]++;

            /* Switch places in array */
            mixedteamrank[me_idx] = opponent;
            mixedteamrank[opponent_idx] = me;
            break;

        default:
            fatal("doMixedTeamMatch() unknown result in 1/24");
        }
    }
    /* Sort everyone from rank 17 to 24 on Q score */
    rankMixedTeams(17, 24);

    /* 1/8
     * In 1/8 elimination round pairs are created
     *  1 vs 16
     *  2 vs 15
     *  3 vs 14
     * Opponent-rank = 17 - me-rank
     */
    for (me_rank = 1; me_rank <= 8; me_rank++) {
        opponent_rank = 17-me_rank;

        me_idx = me_rank-1;
        opponent_idx = opponent_rank-1;

        me = mixedteamrank[me_idx];
        opponent = mixedteamrank[opponent_idx];

        switch (doMixedTeamMatch(me, opponent, F8TH, &counters)) {

        case LEFT_WINS:
        case LEFT_WINS_SHOOTOFF:
            /* Do nothing */
            break;

        case RIGHT_WINS:
        case RIGHT_WINS_SHOOTOFF:
            /* Switch places */
            mixedteamrank[me_idx] = opponent;
            mixedteamrank[opponent_idx] = me;
            break;

        default:
            fatal("doMixedTeamMatch() unknown result in 1/8");
        }
    }
    /* Sort everyone from rank 9 to 16 on Q score */
    rankMixedTeams(9, 16);

    /* 1/4
     * In 1/4 elimination round pairs are created
     *  1 vs 8
     *  2 vs 7
     *  3 vs 6
     * Opponent-rank = 9 - me-rank
     */
    for (me_rank = 1; me_rank <= 4; me_rank++) {
        opponent_rank = 9-me_rank;

        me_idx = me_rank-1;
        opponent_idx = opponent_rank-1;

        me = mixedteamrank[me_idx];
        opponent = mixedteamrank[opponent_idx];

        switch (doMixedTeamMatch(me, opponent, F4TH, &counters)) {

        case LEFT_WINS:
        case LEFT_WINS_SHOOTOFF:
            /* Do nothing */
            break;

        case RIGHT_WINS:
        case RIGHT_WINS_SHOOTOFF:
            /* Switch places */
            mixedteamrank[me_idx] = opponent;
            mixedteamrank[opponent_idx] = me;
            break;

        default:
            fatal("doMixedTeamMatch() unknown result in 1/4");
        }
    }
    /* Sort everyone from rank 5 to 8 on Q score */
    rankTeams(5, 8);

    /* 1/2
     * In 1/2 elimination round pairs are created
     *  1 vs 4
     *  2 vs 3
     * Opponent-rank = 5 - me-rank
     */
    for (me_rank = 1; me_rank <= 2; me_rank++) {
        opponent_rank = 5-me_rank;

        me_idx = me_rank-1;
        opponent_idx = opponent_rank-1;

        me = mixedteamrank[me_idx];
        opponent = mixedteamrank[opponent_idx];

        switch (doMixedTeamMatch(me, opponent, FSEMI, &counters)) {

        case LEFT_WINS:
        case LEFT_WINS_SHOOTOFF:
            /* Do nothing */
            break;

        case RIGHT_WINS:
        case RIGHT_WINS_SHOOTOFF:
            /* Switch places */
            mixedteamrank[me_idx] = opponent;
            mixedteamrank[opponent_idx] = me;
            break;

        default:
            fatal("doMixedTeamMatch() unknown result in 1/2");
        }
    }

    /* Bronze */
    me_rank = 3;
    opponent_rank = 4;

    me_idx = me_rank-1;
    opponent_idx = opponent_rank-1;

    me = mixedteamrank[me_idx];
    opponent = mixedteamrank[opponent_idx];

    switch (doMixedTeamMatch(me, opponent, FBRONZE, &counters)) {

    case LEFT_WINS:
    case LEFT_WINS_SHOOTOFF:
        /* Do nothing */
        break;

    case RIGHT_WINS:
    case RIGHT_WINS_SHOOTOFF:
        /* Switch places */
        mixedteamrank[me_idx] = opponent;
        mixedteamrank[opponent_idx] = me;
        break;

    default:
        fatal("doMixedTeamMatch() unknown result in Bronze");
    }

    /* Gold */
    me_rank = 1;
    opponent_rank = 2;

    me_idx = me_rank-1;
    opponent_idx = opponent_rank-1;

    me = mixedteamrank[me_idx];
    opponent = mixedteamrank[opponent_idx];

    switch (doMixedTeamMatch(me, opponent, FGOLD, &counters)) {

    case LEFT_WINS:
    case LEFT_WINS_SHOOTOFF:
        /* Do nothing */
        break;

    case RIGHT_WINS:
    case RIGHT_WINS_SHOOTOFF:
        /* Switch places */
        mixedteamrank[me_idx] = opponent;
        mixedteamrank[opponent_idx] = me;
        break;

    default:
        fatal("doTeamMatch() unknown result in Gold");
    }

    for (i = 0; i < 24; i++) {
        mixedteamrank[i]->e_rank = (i+1);
    }
} /*}}}2*/

void computeEliminationStats(void) /*{{{2*/
{
    const Face *face = getFace(e_format.facetype);
    Archer left;
    Archer right;

    double lasl;
    double rasl;
    Counters counters = {0};

    initEliminationStats();

    if (pretty_print) {
        outp("Format: %s\n", getFormatName(&e_format));
        outp("N     : %d\n", e_nruns);
        /* Header */
        outp("Archers Skill Level\n");
        outp("       ");
        for (rasl = start_asl; rasl <= end_asl; rasl += step_asl) {
            outp("|  %5.1lf  ", rasl);
        }
        outp("|\n-------");
        for (rasl = start_asl; rasl <= end_asl; rasl += step_asl) {
            outp("+---------");
        }
        outp("+\n");
    }
    else {
        outp("\"%s\"\n%d\n", getFormatName(&e_format), e_nruns);
        /* Header */
        for (rasl = start_asl; rasl <= end_asl; rasl += step_asl) {
            outp(";%lf", rasl);
        }
        outp("\n");
    }
    for (lasl = start_asl; lasl <= end_asl; lasl += step_asl) {
        setArcher(&left, 0, lasl);
        if (pretty_print) {
            outp(" %5.1lf ", left.lvl);
        }
        else {
            outp("%lf", left.lvl);
        }
        for (rasl = start_asl; rasl <= end_asl; rasl += step_asl) {
            int i;
            int left_wins = 0;

            setArcher(&right, 0, rasl);

            /* Perform n times an elimination round */
            initEliminationStats();
            for (i = 0; i < e_nruns; i++) {
                Result result = doMatch(face, &left, &right, FGOLD, &counters);
                if (result == LEFT_WINS || result == LEFT_WINS_SHOOTOFF) {
                    left_wins++;
                }
            }

            if (pretty_print) {
                outp("| %6.2lf%% ", 100.0*left_wins/e_nruns);
            }
            else {
                outp(";%lf", 1.0*left_wins/e_nruns);
            }
        }
        if (pretty_print) {
            outp("|\n");
        }
        else {
            outp("\n");
        }
    }

    outp_close();
} /*}}}2*/

void computeTeamEliminationStats(void) /*{{{2*/
{
    const Face *face = getFace(e_format.facetype);
    const double dist = e_format.distance;
    const int narrows = e_format.narrows;

    int i;
    Team left;
    Team right;
    double lvl[3];
    double lasl, rasl;
    double lw, lwso, rw, rwso;
    Counters counters = {0};

    initEliminationStats();

    if (pretty_print) {
        outp("Format              : %s\n", getFormatName(&e_format));
        outp("N                   : %d\n", e_nruns);
    }
    else {
        outp("\"%s\"\n%d\n", getFormatName(&e_format), e_nruns);
    }

    /* === Loop over team skills */
    for (lasl = start_asl; lasl <= end_asl; lasl += step_asl) {

        lvl[0] = lasl;
        lvl[1] = lasl - (t1asl1 - t1asl2); /* Second archer is bit worse */
        lvl[2] = lasl - (t1asl1 - t1asl3); /* Third archer is more worse */
        setTeam(&left, lvl);

        for (rasl = start_asl; rasl <= end_asl; rasl += step_asl) {

            lvl[0] = rasl;
            lvl[1] = rasl - (t2asl1 - t2asl2); /* Second archer is bit worse */
            lvl[2] = rasl - (t2asl1 - t2asl3); /* Third archer is more worse */
            setTeam(&right, lvl);

            if (pretty_print) {
                outp("Archers Skill Levels: ");
                outp("Left team %5.1lf,%5.1lf,%5.1lf vs right team %5.1lf,%5.1lf,%5.1lf\n",
                       left.archer[0].lvl, left.archer[1].lvl, left.archer[2].lvl,
                       right.archer[0].lvl, right.archer[1].lvl, right.archer[2].lvl);
            }
            else {
                outp("%5.1lf;%5.1lf;%5.1lf;%5.1lf;%5.1lf;%5.1lf",
                       left.archer[0].lvl, left.archer[1].lvl, left.archer[2].lvl,
                       right.archer[0].lvl, right.archer[1].lvl, right.archer[2].lvl);
            }

            int left_wins = 0;
            int right_wins = 0;
            int left_wins_shootoff = 0;
            int right_wins_shootoff = 0;
            for (i = 0; i < e_nruns; i++) {
                switch (doTeamMatch(&left, &right, FGOLD, &counters)) {
                case LEFT_WINS:           left_wins++;           break;
                case LEFT_WINS_SHOOTOFF:  left_wins_shootoff++;  break;
                case RIGHT_WINS:          right_wins++;          break;
                case RIGHT_WINS_SHOOTOFF: right_wins_shootoff++; break;
                }
            }

            lw   = 1.0*(left_wins+left_wins_shootoff)/e_nruns;
            if (left_wins+left_wins_shootoff == 0) {
                lwso = 0.0;
            }
            else {
                lwso = 1.0*left_wins_shootoff/(left_wins+left_wins_shootoff);
            }
            rw   = 1.0*(right_wins+right_wins_shootoff)/e_nruns;
            if (right_wins + right_wins_shootoff == 0) {
                rwso = 0.0;
            }
            else {
                rwso = 1.0*right_wins_shootoff/(right_wins+right_wins_shootoff);
            }

            if (pretty_print) {
                outp("Results             :%.2lf%%(Shootoff %.2lf%%) - %.2lf%%(Shootoff %.2lf%%)\n", 100.0*lw, 100.0*lwso, 100.0*rw, 100.0*rwso);
            }
            else {
                outp(";%lf;%lf;%lf;%lf\n", lw, lwso, rw, rwso);
            }
        }
    }

    /* === END loop over team skills */

    outp_close();
} /*}}}2*/

void computeMixedTeamEliminationStats(void) /*{{{2*/
{
    const Face *face = getFace(e_format.facetype);
    const double dist = e_format.distance;
    const int narrows = e_format.narrows;

    int i;
    MixedTeam left;
    MixedTeam right;
    double lvl[2];
    double lasl, rasl;
    double lw, lwso, rw, rwso;
    Counters counters = {0};

    initEliminationStats();

    if (pretty_print) {
        outp("Format              : %s\n", getFormatName(&e_format));
        outp("N                   : %d\n", e_nruns);
    }
    else {
        outp("\"%s\"\n%d\n", getFormatName(&e_format), e_nruns);
    }

    /* === Loop over team skills */
    for (lasl = start_asl; lasl <= end_asl; lasl += step_asl) {

        lvl[0] = lasl;
        lvl[1] = lasl - (xt1asl1 - xt1asl2);
        setMixedTeam(&left, lvl);

        for (rasl = start_asl; rasl <= end_asl; rasl += step_asl) {

            lvl[0] = rasl;
            lvl[1] = rasl - (xt2asl1 - xt2asl2);
            setMixedTeam(&right, lvl);

            if (pretty_print) {
                outp("Archers Skill Levels: ");
                outp("Left mixed-team %5.1lf,%5.1lf vs right mixed=-team %5.1lf,%5.1lf\n",
                       left.archer[0].lvl, left.archer[1].lvl,
                       right.archer[0].lvl, right.archer[1].lvl);
            }
            else {
                outp("%5.1lf;%5.1lf;%5.1lf;%5.1lf",
                       left.archer[0].lvl, left.archer[1].lvl,
                       right.archer[0].lvl, right.archer[1].lvl);
            }

            int left_wins = 0;
            int right_wins = 0;
            int left_wins_shootoff = 0;
            int right_wins_shootoff = 0;
            for (i = 0; i < e_nruns; i++) {
                switch(doMixedTeamMatch(&left, &right, FGOLD, &counters)) {
                case LEFT_WINS:           left_wins++;           break;
                case LEFT_WINS_SHOOTOFF:  left_wins_shootoff++;  break;
                case RIGHT_WINS:          right_wins++;          break;
                case RIGHT_WINS_SHOOTOFF: right_wins_shootoff++; break;
                }
            }

            lw   = 1.0*(left_wins+left_wins_shootoff)/e_nruns;
            if (left_wins+left_wins_shootoff == 0) {
                lwso = 0.0;
            }
            else {
                lwso = 1.0*left_wins_shootoff/(left_wins+left_wins_shootoff);
            }
            rw   = 1.0*(right_wins+right_wins_shootoff)/e_nruns;
            if (right_wins + right_wins_shootoff == 0) {
                rwso = 0.0;
            }
            else {
                rwso = 1.0*right_wins_shootoff/(right_wins+right_wins_shootoff);
            }

            if (pretty_print) {
                outp("Results             :%.2lf%%(Shootoff %.2lf%%) - %.2lf%%(Shootoff %.2lf%%)\n", 100.0*lw, 100.0*lwso, 100.0*rw, 100.0*rwso);
            }
            else {
                outp(";%lf;%lf;%lf;%lf\n", lw, lwso, rw, rwso);
            }
        }
    }

    outp_close();
} /*}}}2*/

Result doMatch(const Face *face, Archer *left, Archer *right, int stage, Counters *counters) /*{{{2*/
/*
 * Perform a single match between two given archers with the given format
 * left : left archer
 * right : right archer
 * format : elimination match format
 * stage : for metrics;
 *         0 -> GoldFinal or BronzeFinal
 *         1 -> 1/2
 *         2 -> 1/4
 *         3 -> 1/8
 *         4 -> 1/16
 *         5 -> 1/24
 *         6 -> 1/48
 * Return: result, i.e. LEFT_WINS, LEFT_WINS_SHOOTOFF, RIGHT_WINS or RIGHT_WINS_SHOOTOFF
 */
{
    Result result;

    elimstats.n_matches[stage]++;

    switch (e_format.type) {
    case CUMULATIVE:
        result = doCumulativeMatch(left, right, stage, counters);
        break;
    case SETSYSTEM:
        result = doSetMatch(left, right, stage, counters);
        break;
    case SHOOTOFF:
        result = doShootOff(face, left, right, stage, counters);
        break;
    case RANDOM:
        result = doRandomMatch(left, right, stage, counters);
        break;
    default:
        outp("ERROR: doMatch()?\n");
        break;
    }

    return result;
} /*}}}2*/

Result doTeamMatch(Team *left, Team *right, int stage, Counters *counters) /*{{{2*/
/*
 * Perform a single match between two given teams with the given format
 * left : left team
 * right : right team
 * format : elimination match format
 * stage : for metrics;
 *         0 -> GoldFinal or BronzeFinal
 *         1 -> 1/2
 *         2 -> 1/4
 *         3 -> 1/8
 *         4 -> 1/16
 * Return: result, i.e. LEFT_WINS, LEFT_WINS_SHOOTOFF, RIGHT_WINS or RIGHT_WINS_SHOOTOFF
 */
{
    Result result;

    elimstats.n_matches[stage]++;

    switch (e_format.type) {
    case CUMULATIVE:
        result = doCumulativeTeamMatch(left, right, stage, counters);
        break;
    case SETSYSTEM:
        result = doSetTeamMatch(left, right, stage, counters);
        break;
    case SHOOTOFF:
        result = doTeamShootOff(left, right, stage, counters);
        break;
    case RANDOM:
        result = doTeamRandomMatch(left, right, stage, counters);
        break;
    default:
        outp("ERROR: doTeamMatch()?\n");
        break;
    }

    return result;
} /*}}}2*/

Result doMixedTeamMatch(MixedTeam *left, MixedTeam *right, int stage, Counters *counters) /*{{{2*/
/*
 * Perform a single match between two given mixed teams with the given format
 * left : left mixed team
 * right : right mixed team
 * format : elimination match format
 * stage : for metrics;
 *         0 -> GoldFinal or BronzeFinal
 *         1 -> 1/2
 *         2 -> 1/4
 *         3 -> 1/8
 *         4 -> 1/16
 * Return: result, i.e. LEFT_WINS, LEFT_WINS_SHOOTOFF, RIGHT_WINS or RIGHT_WINS_SHOOTOFF
 */
{
    Result result;

    elimstats.n_matches[stage]++;

    switch (e_format.type) {
    case CUMULATIVE:
        result = doCumulativeMixedTeamMatch(left, right, stage, counters);
        break;
    case SETSYSTEM:
        result = doSetMixedTeamMatch(left, right, stage, counters);
        break;
    case SHOOTOFF:
        result = doMixedTeamShootOff(left, right, stage, counters);
        break;
    case RANDOM:
        result = doMixedTeamRandomMatch(left, right, stage, counters);
        break;
    default:
        outp("ERROR: doMixedTeamMatch()?\n");
        break;
    }

    return result;
} /*}}}2*/

void dumpEliminationStats() /*{{{2*/
{
    Face *f;
    int i;

    outp("Qualification: %s\n", getFormatName(&q_format));
    outp("Elimination  : %s\n", getFormatName(&e_format));
    outp("Skill level distribution: %5.1lf %5.1lf %5.1lf %5.1lf %5.1lf %5.1lf (%s)\n",
            asl1, asl4, asl8, asl16, asl32, asl56, asl104, name_of_population);

    outp("\n           Elimination round statistics\n");
    outp("=============================================================================================\n");
    outp("|                            |  1/48  |  1/24  |  1/16  |   1/8  |   1/4  |   1/2  |  FG+FB |\n");
    outp("+----------------------------+--------+--------+--------+--------+--------+--------+--------+\n");

    outp("| # total simulated matches  | %6ld | %6ld | %6ld | %6ld | %6ld | %6ld | %6ld |\n",
               elimstats.n_matches[F48TH],
               elimstats.n_matches[F24TH],
               elimstats.n_matches[F16TH],
               elimstats.n_matches[F8TH],
               elimstats.n_matches[F4TH],
               elimstats.n_matches[FSEMI],
               elimstats.n_matches[FGOLD]);
    if (e_format.best_of > 0) {
        for (i = 0; i < e_format.best_of; i++) {
            outp("| # avg wins after %2d sets   | %5.1lf%% | %5.1lf%% | %5.1lf%% | %5.1lf%% | %5.1lf%% | %5.1lf%% | %5.1lf%% |\n",
                   i+1,
                   100.0*elimstats.n_win_after_sets[i][F48TH].avg/48.0,
                   100.0*elimstats.n_win_after_sets[i][F24TH].avg/24.0,
                   100.0*elimstats.n_win_after_sets[i][F16TH].avg/16.0,
                   100.0*elimstats.n_win_after_sets[i][F8TH].avg/8.0,
                   100.0*elimstats.n_win_after_sets[i][F4TH].avg/4.0,
                   100.0*elimstats.n_win_after_sets[i][FSEMI].avg/2.0,
                   100.0*elimstats.n_win_after_sets[i][FGOLD].avg/2.0);
        }
    }
    outp("| # avg wins after S/O       |  %5.1lf |  %5.1lf |  %5.1lf |  %5.1lf |  %5.1lf |  %5.1lf |  %5.1lf |\n",
               elimstats.n_win_after_shootoff[F48TH].avg,
               elimstats.n_win_after_shootoff[F24TH].avg,
               elimstats.n_win_after_shootoff[F16TH].avg,
               elimstats.n_win_after_shootoff[F8TH].avg,
               elimstats.n_win_after_shootoff[F4TH].avg,
               elimstats.n_win_after_shootoff[FSEMI].avg,
               elimstats.n_win_after_shootoff[FGOLD].avg);
    outp("| # avg wins after D-S/O     |  %5.1lf |  %5.1lf |  %5.1lf |  %5.1lf |  %5.1lf |  %5.1lf |  %5.1lf |\n",
               elimstats.n_second_shootoff_required[F48TH].avg,
               elimstats.n_second_shootoff_required[F24TH].avg,
               elimstats.n_second_shootoff_required[F16TH].avg,
               elimstats.n_second_shootoff_required[F8TH].avg,
               elimstats.n_second_shootoff_required[F4TH].avg,
               elimstats.n_second_shootoff_required[FSEMI].avg,
               elimstats.n_second_shootoff_required[FGOLD].avg);
    if (e_format.best_of > 0) {
        outp("| # avg wins equal score !S/O|  %5.1lf |  %5.1lf |  %5.1lf |  %5.1lf |  %5.1lf |  %5.1lf |  %5.1lf |\n",
                   elimstats.n_win_with_equal_score_no_so[F48TH].avg,
                   elimstats.n_win_with_equal_score_no_so[F24TH].avg,
                   elimstats.n_win_with_equal_score_no_so[F16TH].avg,
                   elimstats.n_win_with_equal_score_no_so[F8TH].avg,
                   elimstats.n_win_with_equal_score_no_so[F4TH].avg,
                   elimstats.n_win_with_equal_score_no_so[FSEMI].avg,
                   elimstats.n_win_with_equal_score_no_so[FGOLD].avg);
        outp("| # avg wins with lower score|  %5.1lf |  %5.1lf |  %5.1lf |  %5.1lf |  %5.1lf |  %5.1lf |  %5.1lf |\n",
                   elimstats.n_win_with_lower_score[F48TH].avg,
                   elimstats.n_win_with_lower_score[F24TH].avg,
                   elimstats.n_win_with_lower_score[F16TH].avg,
                   elimstats.n_win_with_lower_score[F8TH].avg,
                   elimstats.n_win_with_lower_score[F4TH].avg,
                   elimstats.n_win_with_lower_score[FSEMI].avg,
                   elimstats.n_win_with_lower_score[FGOLD].avg);
    }
    outp("| # avg expected wins        | %5.1lf%% | %5.1lf%% | %5.1lf%% | %5.1lf%% | %5.1lf%% | %5.1lf%% | %5.1lf%% |\n",
               100.0*elimstats.n_expected_wins[F48TH].avg/48.0,
               100.0*elimstats.n_expected_wins[F24TH].avg/24.0,
               100.0*elimstats.n_expected_wins[F16TH].avg/16.0,
               100.0*elimstats.n_expected_wins[F8TH].avg/8.0,
               100.0*elimstats.n_expected_wins[F4TH].avg/4.0,
               100.0*elimstats.n_expected_wins[FSEMI].avg/2.0,
               100.0*elimstats.n_expected_wins[FGOLD].avg/2.0);
    outp("=============================================================================================\n");

    outp("\nNumber of archers that qualified top  4, also ends in top  4 = %5.1lf\n", elimstats.n_top_q4_e4.avg);
    outp("Number of archers that qualified top  8, also ends in top  8 = %5.1lf\n", elimstats.n_top_q8_e8.avg);
    outp("Number of archers that qualified top 16, also ends in top 16 = %5.1lf\n", elimstats.n_top_q16_e16.avg);

    outp("\nAverage final ranking fit to theoretical ranking: %lf\n", elimstats.fc.avg);
    outp("                                        StdDev  : %lf\n\n", elimstats.fc.stdev);
} /*}}}2*/

/* --- Local functions {{{1 */

static Result doSetMatch(Archer *me, Archer *opponent, int stage, Counters *counters) /*{{{2*/
/*
 * Performs a simulation of a match between two archers based on the set principle, best of <best_of> sets
 * each set consists of <n_arrows> arrows (with possible shootoff) for given competition format
 * Returns 1 for my win!
 * me       = Me
 * opponent = My opponent
 * format   = The competition format (face, distance, n_arrows, best_of)
 */
{
    const Face *face = getFace(e_format.facetype);
    const double dist = e_format.distance;
    const int narrows = e_format.narrows;

    int nsets = 0;
    int my_setpoints = 0;
    int opponent_setpoints = 0;
    int target_points = e_format.best_of+1;
    double my_cumulative_score = 0.0;
    double opponent_cumulative_score = 0.0;

    while (1) {
        /* Set */
        nsets++;

        double my_score       = getScore(me->lvl, face, dist, narrows);
        double opponent_score = getScore(opponent->lvl, face, dist, narrows);

        my_cumulative_score += my_score;
        opponent_cumulative_score += opponent_score;

        switch (scoreCompare(my_score, opponent_score)) {
        case LEFT_WINS:
            my_setpoints += 2;
            break;
        case RIGHT_WINS:
            opponent_setpoints += 2;
            break;
        case DRAW:
            my_setpoints++;
            opponent_setpoints++;
            break;
        }

        if (my_setpoints >= target_points) {
            /* I win! */
            if (my_cumulative_score < opponent_cumulative_score) {
                /* With lower cumulative score */
                counters->n_win_with_lower_score[stage]++;
            }
            if (my_cumulative_score == opponent_cumulative_score) {
                /* With equal cumulative score but NO shootoff */
                counters->n_win_with_equal_score_no_so[stage]++;
            }
            counters->n_win_after_sets[nsets-1][stage]++;
            return LEFT_WINS;
        }

        if (opponent_setpoints >= target_points) {
            /* Opponent wins! */
            if (opponent_cumulative_score < my_cumulative_score) {
                /* With lower cumulative score */
                counters->n_win_with_lower_score[stage]++;
            }
            if (opponent_cumulative_score == my_cumulative_score) {
                /* With equal cumulative score but NO shootoff */
                counters->n_win_with_equal_score_no_so[stage]++;
            }
            counters->n_win_after_sets[nsets-1][stage]++;
            return RIGHT_WINS;
        }

        if ( (my_setpoints == (target_points-1))      &&
             (opponent_setpoints == (target_points-1))   )
        {
            /* We draw -> shootoff */
            counters->n_win_after_sets[nsets-1][stage]++;
            return doShootOff(face, me, opponent, stage, counters);
        }

        /* Nope.. continue */
    }
} /*}}}2*/

static Result doSetTeamMatch(Team *left, Team *right, int stage, Counters *counters) /*{{{2*/
/*
 * Performs a simulation of a match between two teams based on the set principle, best of <best_of> sets
 * each set consists of <n_arrows> arrows per archer (with possible shootoff) for given competition format
 * Returns 1 for left win!
 * left   = Left team
 * right  = Right team
 * format = The competition format (face, distance, n_arrows, best_of)
 */
{
    int nsets = 0;
    int left_setpoints = 0;
    int right_setpoints = 0;
    int target_points = e_format.best_of+1;
    double left_cumulative_score = 0.0;
    double right_cumulative_score = 0.0;
    int narrows = e_format.narrows;

    const Face *face = getFace(e_format.facetype);
    const double dist = e_format.distance;

    D("Team set-match\n");

    while (1) {
        /* Set */
        nsets++;

        double left_score   = getScore(left->archer[0].lvl,  face, dist, narrows) +
                              getScore(left->archer[1].lvl,  face, dist, narrows) +
                              getScore(left->archer[2].lvl,  face, dist, narrows);
        double right_score  = getScore(right->archer[0].lvl, face, dist, narrows) +
                              getScore(right->archer[1].lvl, face, dist, narrows) +
                              getScore(right->archer[2].lvl, face, dist, narrows);

        D("Set %d: %4.1lf - %4.1lf -> ", nsets, left_score, right_score);

        left_cumulative_score += left_score;
        right_cumulative_score += right_score;

        switch (scoreCompare(left_score, right_score)) {
        case LEFT_WINS:
            left_setpoints += 2;
            break;
        case RIGHT_WINS:
            right_setpoints += 2;
            break;
        case DRAW:
            left_setpoints++;
            right_setpoints++;
            break;
        }

        D("%d - %d\n", left_setpoints, right_setpoints);

        if (left_setpoints >= target_points) {
            /* I win! */
            if (left_cumulative_score < right_cumulative_score) {
                /* With lower cumulative score */
                counters->n_win_with_lower_score[stage]++;
            }
            if (left_cumulative_score == right_cumulative_score) {
                /* With equal cumulative score but NO shootoff */
                counters->n_win_with_equal_score_no_so[stage]++;
            }
            counters->n_win_after_sets[nsets-1][stage]++;
            return LEFT_WINS;
        }

        if (right_setpoints >= target_points) {
            /* Opponent wins! */
            if (right_cumulative_score < left_cumulative_score) {
                /* With lower cumulative score */
                counters->n_win_with_lower_score[stage]++;
            }
            if (right_cumulative_score == left_cumulative_score) {
                /* With equal cumulative score but NO shootoff */
                counters->n_win_with_equal_score_no_so[stage]++;
            }
            counters->n_win_after_sets[nsets-1][stage]++;
            return RIGHT_WINS;
        }

        if ( (left_setpoints == (target_points-1))      &&
             (right_setpoints == (target_points-1))   )
        {
            /* We draw -> shootoff */
            counters->n_win_after_sets[nsets-1][stage]++;
            return doTeamShootOff(left, right, stage, counters);
        }

        /* Nope.. continue */
    }
} /*}}}2*/

static Result doSetMixedTeamMatch(MixedTeam *left, MixedTeam *right, int stage, Counters *counters) /*{{{2*/
/*
 * Performs a simulation of a match between two mixed-teams based on the set principle, best of <best_of> sets
 * each set consists of <n_arrows> arrows per archer (with possible shootoff) for given competition format
 * Returns 1 for left win!
 * left   = Left mixed-team
 * right  = Right mixed-team
 * format = The competition format (face, distance, n_arrows, best_of)
 */
{
    int nsets = 0;
    int left_setpoints = 0;
    int right_setpoints = 0;
    int target_points = e_format.best_of+1;
    double left_cumulative_score = 0.0;
    double right_cumulative_score = 0.0;
    int narrows = e_format.narrows;

    const Face *face = getFace(e_format.facetype);
    const double dist = e_format.distance;

    D("Mixed-team set-match\n");

    while (1) {
        /* Set */
        nsets++;

        double left_score   = getScore(left->archer[0].lvl,  face, dist, narrows) +
                              getScore(left->archer[1].lvl,  face, dist, narrows);
        double right_score  = getScore(right->archer[0].lvl, face, dist, narrows) +
                              getScore(right->archer[1].lvl, face, dist, narrows);

        D("Set %d: %4.1lf - %4.1lf -> ", nsets, left_score, right_score);

        left_cumulative_score += left_score;
        right_cumulative_score += right_score;

        switch (scoreCompare(left_score, right_score)) {
        case LEFT_WINS:
            left_setpoints += 2;
            break;
        case RIGHT_WINS:
            right_setpoints += 2;
            break;
        case DRAW:
            left_setpoints++;
            right_setpoints++;
            break;
        }

        D("%d - %d\n", left_setpoints, right_setpoints);

        if (left_setpoints >= target_points) {
            /* I win! */
            if (left_cumulative_score < right_cumulative_score) {
                /* With lower cumulative score */
                counters->n_win_with_lower_score[stage]++;
            }
            if (left_cumulative_score == right_cumulative_score) {
                /* With equal cumulative score but NO shootoff */
                counters->n_win_with_equal_score_no_so[stage]++;
            }
            counters->n_win_after_sets[nsets-1][stage]++;
            return LEFT_WINS;
        }

        if (right_setpoints >= target_points) {
            /* Opponent wins! */
            if (right_cumulative_score < left_cumulative_score) {
                /* With lower cumulative score */
                counters->n_win_with_lower_score[stage]++;
            }
            if (right_cumulative_score == left_cumulative_score) {
                /* With equal cumulative score but NO shootoff */
                counters->n_win_with_equal_score_no_so[stage]++;
            }
            counters->n_win_after_sets[nsets-1][stage]++;
            return RIGHT_WINS;
        }

        if ( (left_setpoints == (target_points-1))      &&
             (right_setpoints == (target_points-1))   )
        {
            /* We draw -> shootoff */
            counters->n_win_after_sets[nsets-1][stage]++;
            return doMixedTeamShootOff(left, right, stage, counters);
        }

        /* Nope.. continue */
    }
} /*}}}2*/

static Result doCumulativeMatch(Archer *me, Archer *opponent, int stage, Counters *counters) /*{{{2*/
/*
 * Performs a simulation of a cummulative scoring match (with possible shootoff) between two
 * archers in some competition format
 * Returns 1 for my win!
 * me       = Me
 * opponent = My opponent
 * format   = Competition format
 */
{
    const Face *face = getFace(e_format.facetype);
    const double dist = e_format.distance;
    const int narrows = e_format.narrows;

    double my_score       = getScore(me->lvl, face, dist, narrows);
    double opponent_score = getScore(opponent->lvl, face, dist, narrows);

    switch (scoreCompare(my_score, opponent_score)) {

        case LEFT_WINS:
            counters->n_win_after_sets[0][stage]++;
            return LEFT_WINS;

        case RIGHT_WINS:
            counters->n_win_after_sets[0][stage]++;
            return RIGHT_WINS;

        case DRAW:
            counters->n_win_after_sets[0][stage]++;
            return doShootOff(face, me, opponent, stage, counters);
    }

    outp("ERROR: doCumulativeMatch()?\n");
} /*}}}2*/

static Result doCumulativeTeamMatch(Team *left, Team *right, int stage, Counters *counters) /*{{{2*/
/*
 * Performs a simulation of a cummulative scoring match (with possible shootoff) between two
 * teams in some competition format
 * Returns 1 for left win!
 * left    = Left
 * right   = Right
 * format  = Competition format
 */
{
    const Face *face = getFace(e_format.facetype);
    const double dist = e_format.distance;
    const int narrows = e_format.narrows;

    double left_score  = getScore(left->archer[0].lvl, face, dist, narrows) +
                         getScore(left->archer[1].lvl, face, dist, narrows) +
                         getScore(left->archer[2].lvl, face, dist, narrows);
    double right_score  = getScore(right->archer[0].lvl, face, dist, narrows) +
                          getScore(right->archer[1].lvl, face, dist, narrows) +
                          getScore(right->archer[2].lvl, face, dist, narrows);

    D("Match: %5.1lf - %5.1lf\n", left_score, right_score);

    switch (scoreCompare(left_score, right_score)) {

        case LEFT_WINS:
            counters->n_win_after_sets[0][stage]++;
            return LEFT_WINS;

        case RIGHT_WINS:
            counters->n_win_after_sets[0][stage]++;
            return RIGHT_WINS;

        case DRAW:
            counters->n_win_after_sets[0][stage]++;
            return doTeamShootOff(left, right, stage, counters);
    }

    outp("ERROR: doCumulativeTeamMatch()?");
} /*}}}2*/

static Result doCumulativeMixedTeamMatch(MixedTeam *left, MixedTeam *right, int stage, Counters *counters) /*{{{2*/
/*
 * Performs a simulation of a cummulative scoring match (with possible shootoff) between two
 * mixed-teams in some competition format
 * Returns 1 for left win!
 * left    = Left
 * right   = Right
 * format  = Competition format
 */
{
    const Face *face = getFace(e_format.facetype);
    const double dist = e_format.distance;
    const int narrows = e_format.narrows;

    double left_score  = getScore(left->archer[0].lvl, face, dist, narrows) +
                         getScore(left->archer[1].lvl, face, dist, narrows);
    double right_score  = getScore(right->archer[0].lvl, face, dist, narrows) +
                          getScore(right->archer[1].lvl, face, dist, narrows);

    D("Match: %5.1lf - %5.1lf\n", left_score, right_score);

    switch (scoreCompare(left_score, right_score)) {

        case LEFT_WINS:
            counters->n_win_after_sets[0][stage]++;
            return LEFT_WINS;

        case RIGHT_WINS:
            counters->n_win_after_sets[0][stage]++;
            return RIGHT_WINS;

        case DRAW:
            counters->n_win_after_sets[0][stage]++;
            return doMixedTeamShootOff(left, right, stage, counters);
    }

    outp("ERROR: doCumulativeMixedTeamMatch()?");
} /*}}}2*/

static Result doShootOff(const Face *face, Archer *me, Archer *opponent, int stage, Counters *counters) /*{{{2*/
/*
 * Performs a simulation of a single arrow shoot-off between two archers in a
 * competition format (actually, only distance)
 * archers in some competition format
 * Returns 1 for my win!
 * me       = Me
 * opponent = My opponent
 * format   = Competition format
 */
{
    const double dist = e_format.distance;

    /* Shootoff */
    counters->n_win_after_shootoff[stage]++;
    int attempt = 0;
    while (1) {
        attempt++;
        double my_d       = getArrowPosition(me->lvl, dist);
        double opponent_d = getArrowPosition(opponent->lvl, dist);
        /* This targetface has special 2nd shootoff rule enabled and this is the first attempt */
        if ( (face->ring_for_2nd_so >= 0)  &&
             (attempt == 1)                   )
        {
            if ( (my_d <= face->radius[face->ring_for_2nd_so]) &&
                 (opponent_d <= face->radius[face->ring_for_2nd_so]) )
            {
                /* Both in same ring, retry shootoff */
                counters->n_second_shootoff_required[stage]++;
                continue;
            }
        }
        switch (shootoffCompare(my_d, opponent_d)) {
        case LEFT_WINS_SHOOTOFF: return LEFT_WINS_SHOOTOFF;
        case RIGHT_WINS_SHOOTOFF: return RIGHT_WINS_SHOOTOFF;
        }
        /* All other cases, do it again */
    }
} /*}}}2*/

static Result doTeamShootOff(Team *left, Team *right, int stage, Counters *counters) /*{{{2*/
/*
 * Performs a simulation of a team shoot-off between two teams in a
 * competition format (actually, only distance)
 * Teams in some competition format
 * Returns 1 for left teams wins!
 * format = Competition format
 * stage = stage in elimination
 */
{
    const Face *face = getFace(e_format.facetype);
    const double dist = e_format.distance;

    D("TEAM SHOOTOFF\n");

    /* Shootoff */
    counters->n_win_after_shootoff[stage]++;
    while (1) {

        /* First shoot three arrows each team */
        double left_d[3];
        double right_d[3];

        left_d[0] = getArrowPosition(left->archer[0].lvl, dist);
        left_d[1] = getArrowPosition(left->archer[1].lvl, dist);
        left_d[2] = getArrowPosition(left->archer[2].lvl, dist);

        right_d[0] = getArrowPosition(right->archer[0].lvl, dist);
        right_d[1] = getArrowPosition(right->archer[1].lvl, dist);
        right_d[2] = getArrowPosition(right->archer[2].lvl, dist);

        switch (teamShootoffCompare(left, left_d, right, right_d, face)) {
        case LEFT_WINS_SHOOTOFF: return LEFT_WINS_SHOOTOFF;
        case RIGHT_WINS_SHOOTOFF: return RIGHT_WINS_SHOOTOFF;
        }
        /* In all other cases, do it again */
    }
} /*}}}2*/

static Result doMixedTeamShootOff(MixedTeam *left, MixedTeam *right, int stage, Counters *counters) /*{{{2*/
/*
 * Performs a simulation of a mixed team shoot-off between two mixed teams in a
 * competition format (actually, only distance)
 * Teams in some competition format
 * Returns 1 for left teams wins!
 * format = Competition format
 * stage = stage in elimination
 */
{
    const Face *face = getFace(e_format.facetype);
    const double dist = e_format.distance;

    D("MIXED-TEAM SHOOTOFF\n");

    /* Shootoff */
    counters->n_win_after_shootoff[stage]++;
    while (1) {

        /* First shoot one arrows each archer in the team */
        double left_d[2];
        double right_d[2];

        left_d[0] = getArrowPosition(left->archer[0].lvl, dist);
        left_d[1] = getArrowPosition(left->archer[1].lvl, dist);

        right_d[0] = getArrowPosition(right->archer[0].lvl, dist);
        right_d[1] = getArrowPosition(right->archer[1].lvl, dist);

        switch (mixedTeamShootoffCompare(left, left_d, right, right_d, face)) {
        case LEFT_WINS_SHOOTOFF: return LEFT_WINS_SHOOTOFF;
        case RIGHT_WINS_SHOOTOFF: return RIGHT_WINS_SHOOTOFF;
        }
        /* In all other cases, do it again */
    }
} /*}}}2*/

static Result doRandomMatch(Archer *me, Archer *opponent, int stage, Counters *counters) /*{{{2*/
/*
 * Performs a simulation of a random match between two skill levels
 * Returns 1 for my win!
 */
{
    return rand()>RAND_MAX/2?LEFT_WINS:RIGHT_WINS;
} /*}}}2*/

static Result doTeamRandomMatch(Team *left, Team *right, int stage, Counters *counters) /*{{{2*/
/*
 * Performs a simulation of a random match between two teams
 * Returns 1 for left team wins!
 */
{
    return rand()>RAND_MAX/2?LEFT_WINS:RIGHT_WINS;
} /*}}}2*/

static Result doMixedTeamRandomMatch(MixedTeam *left, MixedTeam *right, int stage, Counters *counters) /*{{{2*/
/*
 * Performs a simulation of a random match between two mixed teams
 * Returns 1 for left mixed team wins!
 */
{
    return rand()>RAND_MAX/2?LEFT_WINS:RIGHT_WINS;
} /*}}}2*/

static double getFinalRankingCorrectness(void) /*{{{2*/
/*
 * Compute the correctness factor for the final ranking
 *
 * Correctness is defined as:
 *
 *                     N(104)
 * correctness = sqrt ( SUM ( archer[i].lvl_rank - archer[i].e_rank )^2   ) / N
 *                      i=1
 *
 * This indicates how well the final ranking fits the perfect ranking. The smaller
 * this number, the better the fit
 */
{
    double f = 0.0;
    int i;

    for (i = 0; i < 104; i++) {
        f += (archer[i].lvl_rank - archer[i].e_rank) * (archer[i].lvl_rank - archer[i].e_rank);
    }
    return sqrt(f)/104.0;
} /*}}}2*/


