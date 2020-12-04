# ArcheryCompetitionSimulation
Can be used to simulated archery competitions in existing and non-existing formats to get insight in their statistics, like win/lose statistics, tie-statistics etc.

```
Archery statistical simulator from Marcel van Apeldoorn (mvapldrn@gmail.com)

Usage: archerystats [option (<value>)]

Modes: SCORE | QUALIFICATION | ELIMINATION | COMPETITION | COMPETITIONS

Mode: SCORE
--score                            Perform simulations of a score (ASL -> score)
--start-level=<level>              Start (lowest) Archers Skill Level
--end-level=<level>                End (highest) Archers Skill Level
--level-step=<step>                Steps in Archers Skill Level
--distance=<distance>              Shooting distance in [m]
--target-face=<face-code>          Target face code
--n-arrows=<n>                     Number of arrows to shoot
--format-name=<name>               Name of all formats (for logging)
--n-runs=<n>                       Number of times the score is simulated

Mode: QUALIFICATION
--qualification                    Perform simulations of a qualification round
--level-1=<level>                  Archers Skill Level of the #1 ranked archer
--level-4=<level>                  Archers Skill Level of the #4 ranked archer
--level-8=<level>                  Archers Skill Level of the #8 ranked archer
--level-16=<level>                 Archers Skill Level of the #16 ranked archer
--level-32=<level>                 Archers Skill Level of the #32 ranked archer
--level-56=<level>                 Archers Skill Level of the #56 ranked archer
--level-104=<level>                Archers Skill Level of the #104 ranked archer
--distance=<distance>              Shooting distance in [m]
--target-face=<face-code>          Target face code
--n-arrows=<n>                     Number of arrows to shoot
--format-name=<name>               Name of all formats (for logging)
--n-runs=<n>                       Number of times a score is generated per archer (for averaging skill level)

Mode: ELIMINATION
--elimination                      Perform simulations of eliminations between two archers
--start-level=<level>              Start (lowest) Archers Skill Level
--end-level=<level>                End (highest) Archers Skill Level
--level-step=<step>                Steps in Archers Skill Level
--distance=<distance>              Shooting distance in [m]
--target-face=<face-code>          Target face code
--n-arrows=<n>                     Number of arrows to shoot
--best-of-sets=<n-sets>            Best of <n-sets> sets
--format-name=<name>               Name of all formats (for logging)
--format=<format>                  Format code
--n-runs=<n>                       Number op times an elimination is run between two archers

Mode: TEAM ELIMINATION
--team-elimination                 Perform simulation of team elimination between two teams
--team1-level-1=<level>            Archers Skill Level archer #1
--team1-level-2=<level>            Archers Skill Level archer #2
--team1-level-3=<level>            Archers Skill Level archer #3
--team2-level-1=<level>            Archers Skill Level archer #1
--team2-level-2=<level>            Archers Skill Level archer #2
--team2-level-3=<level>            Archers Skill Level archer #3
--start-level=<level>              Start (lowest) Archers Skill Level of best archer
--end-level=<level>                End (highest) Archers Skill Level of best archer in team
--level-step=<step>                Steps in Archers Skill Level
--distance=<distance>              Shooting distance in [m]
--target-face=<face-code>          Target face code
--n-arrows=<n>                     Number of arrows to shoot per archer
--best-of-sets=<n-sets>            Best of <n-sets> sets
--format-name=<name>               Name of all formats (for logging)
--format=<format>                  Format code
--n-runs=<n>                       Number op times an elimination is run between two archers

Mode: MIXED-TEAM ELIMINATION
--mixed-team-elimination           Perform simulation of mixed-team elimination between two teams
--team1-level-1=<level>            Archers Skill Level archer #1
--team1-level-2=<level>            Archers Skill Level archer #2
--team2-level-1=<level>            Archers Skill Level archer #1
--team2-level-2=<level>            Archers Skill Level archer #2
--start-level=<level>              Start (lowest) Archers Skill Level of best archer
--end-level=<level>                End (highest) Archers Skill Level of best archer in team
--level-step=<step>                Steps in Archers Skill Level
--distance=<distance>              Shooting distance in [m]
--target-face=<face-code>          Target face code
--n-arrows=<n>                     Number of arrows to shoot per archer
--best-of-sets=<n-sets>            Best of <n-sets> sets
--format-name=<name>               Name of all formats (for logging)
--format=<format>                  Format code
--n-runs=<n>                       Number op times an elimination is run between two archers

Mode: COMPETITION
--competition                      Perform simulations of a full competition (i.e. qualification followed by eliminations)
--level-1=<level>                  Archers Skill Level of the #1 ranked archer
--level-4=<level>                  Archers Skill Level of the #4 ranked archer
--level-8=<level>                  Archers Skill Level of the #8 ranked archer
--level-16=<level>                 Archers Skill Level of the #16 ranked archer
--level-32=<level>                 Archers Skill Level of the #32 ranked archer
--level-56=<level>                 Archers Skill Level of the #56 ranked archer
--level-104=<level>                Archers Skill Level of the #104 ranked archer
--distance=<distance>              Shooting distance in [m]
--target-face=<face-code>          Target face code
--n-arrows-qualification=<n>       Number fo arrows to shoot in qualification
--n-arrows-eliminations=<n>        Number fo arrows to shoot in elimination
--best-of-sets=<n-sets>            Best of <n-sets> sets
--format-name-qualification=<name> Name of qualification format (for logging)
--format-name-elimination=<name>   Name of elimination format (for logging)
--format-qualification=<format>    Format code of qualification
--format-elimination=<format>      Format code of elimination

--n-runs=<n>                       Number of times a score is generated per archer (for averaging skill level) in qualification only

Mode: COMPETITIONS
--competitions                     Perform simulations of a full competition (i.e. qualification followed by eliminations)
--level-1=<level>                  Archers Skill Level of the #1 ranked archer
--level-4=<level>                  Archers Skill Level of the #4 ranked archer
--level-8=<level>                  Archers Skill Level of the #8 ranked archer
--level-16=<level>                 Archers Skill Level of the #16 ranked archer
--level-32=<level>                 Archers Skill Level of the #32 ranked archer
--level-56=<level>                 Archers Skill Level of the #56 ranked archer
--level-104=<level>                Archers Skill Level of the #104 ranked archer
--distance=<distance>              Shooting distance in [m]
--target-face=<face-code>          Target face code
--n-arrows-qualification=<n>       Number fo arrows to shoot in qualification
--n-arrows-eliminations=<n>        Number fo arrows to shoot in elimination
--best-of-sets=<n-sets>            Best of <n-sets> sets
--format-name-qualification=<name> Name of qualification format (for logging)
--format-name-elimination=<name>   Name of elimination format (for logging)
--format-qualification=<format>    Format code of qualification
--format-elimination=<format>      Format code of elimination

--n-runs-qualification=<n>         Number of times a score is generated per archer (for averaging skill level) in qualification only
--n-runs=<n>                       Number of times the entire competition is run
--high-loser=<n>                   How much positions lower is an archer called a high-loser
--cut-high-loser=<n>               To be a high-loser the q-rank needs to be at least n

<face-code>
  0 = World Archery 122cm, 10 rings
  1 = World Archery 80cm, 10 rings
  2 = World Archery 80cm, 6 rings
  3 = World Archery 60cm, 10 rings
  4 = World Archery 60cm, 5 rings
  5 = World Archery 40cm, 5 rings, recurve
  6 = World Archery 40cm, 5 rings, compound
  7 = Experimental 38cm, 5 rings, compound (10 30 50 70 90mm)
  8 = Experimental 40cm, 6 rings, compound, (10 20 40 60 80 100mm), X=11, 10=10, etc
  9 = Experimental 20cm, 10 rings, compound
 10 = Experimental 36cm, 5 rings, compound, (9 27 45 63 81mm)
 11 = Experimental 32cm, 5 rings, compound, (8 24 40 56 72mm)
 12 = Experimental 80cm, 7 rings with X scores 11
 13 = Experimental 80cm 6 rings with decimal scoring
 14 = Experimental 122cm, 11 rings, with pinhole scores 100,10,9,8,7,6,5,4,3,2,1
 15 = Experimental 110cm, 10 rings
 16 = Experimental 100cm, 10 rings
 17 = Experimental 200cm, 1 ring with score 10
 18 = Exprimental 80cm 20 rings (only 12 scoring rings)

<format>
0 = Cumulative scoring
1 = Set system
2 = Single arrow shootoff closest to center
3 = Pure random (flip a coin)

Generic options
--interactive                      Start in interactive mode
--output=<file>                    Write output to file <file>
--output-append=<file>             Append output to file <file>
--pretty-print                     Pretty print the results (default is CSV print of results)

--help                             This help file
```
