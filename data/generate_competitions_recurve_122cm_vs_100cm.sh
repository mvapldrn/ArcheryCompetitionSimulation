#!/usr/bin/bash

# ==================================== SIMULATE QUALIFICATIONS IN DIFFERENT FORMATS AND DIFFERENT FACES ========================================
NSIMS=100000

echo "RM Outdoor qualification statistics"
# 72 arrows
../bin/archerystats --competitions --pretty-print \
          --level-1=117.0 --level-4=115.0 --level-8=110.6 --level-16=107.2 --level-32=105.0 --level-56=101.2 --level-104=94.5 --level-name="RM Outdoor WorldChampionship 2019" \
          --n-runs-qualification=1 --n-runs=$NSIMS \
          --distance=70 --target-face=0 --n-arrows-qualification=72 --n-arrows-elimination=3 --best-of-sets=5 \
          --format-name-qualification="q_rm_72a_70m_122cm10ring" --format-name-elimination="e_rm_3abo5_70m_122cm10ring" \
          --format-qualification=0 --format-elimination=1
../bin/archerystats --competitions --pretty-print \
          --level-1=117.0 --level-4=115.0 --level-8=110.6 --level-16=107.2 --level-32=105.0 --level-56=101.2 --level-104=94.5 --level-name="RM Outdoor WorldChampionship 2019" \
          --n-runs-qualification=1 --n-runs=$NSIMS \
          --distance=70 --target-face=16 --n-arrows-qualification=72 --n-arrows-elimination=3 --best-of-sets=5 \
          --format-name-qualification="q_rm_72a_70m_100cm10ring" --format-name-elimination="e_rm_3abo5_70m_100cm10ring" \
          --format-qualification=0 --format-elimination=1
echo "RW Outdoor qualification statistics"
../bin/archerystats --competitions --pretty-print \
          --level-1=114.5 --level-4=107.2 --level-8=104.1 --level-16=101.0 --level-32=98.0 --level-56=94.0 --level-104=85.2 --level-name="RW Outdoor WorldChampionship 2019" \
          --n-runs-qualification=1 --n-runs=$NSIMS \
          --distance=70 --target-face=0 --n-arrows-qualification=72 --n-arrows-elimination=3 --best-of-sets=5 \
          --format-name-qualification="q_rm_72a_70m_122cm10ring" --format-name-elimination="e_rm_3abo5_70m_122cm10ring" \
          --format-qualification=0 --format-elimination=1
../bin/archerystats --competitions --pretty-print \
          --level-1=114.5 --level-4=107.2 --level-8=104.1 --level-16=101.0 --level-32=98.0 --level-56=94.0 --level-104=85.2 --level-name="RW Outdoor WorldChampionship 2019" \
          --n-runs-qualification=1 --n-runs=$NSIMS \
          --distance=70 --target-face=16 --n-arrows-qualification=72 --n-arrows-elimination=3 --best-of-sets=5 \
          --format-name-qualification="q_rw_72a_70m_100cm10ring" --format-name-elimination="e_rw_3abo5_70m_100cm10ring" \
          --format-qualification=0 --format-elimination=1





