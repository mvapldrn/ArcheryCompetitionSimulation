#!/usr/bin/bash

# ==================================== SIMULATE QUALIFICATIONS IN DIFFERENT FORMATS AND DIFFERENT FACES ========================================
NSIMS=100

DATAFILE=../data/q_data

rm -f $DATAFILE

echo -n "CM Outdoor qualification statistics"
# 72 arrows
../bin/archerystats --qualification \
          --level-1=131.2 --level-4=125.2 --level-8=123.6 --level-16=122.0 --level-32=120.0 --level-56=116.8 --level-104=109.0 --level-name="CM Level Outdoor WorldChampionship 2019" \
          --n-runs=$NSIMS \
          --distance=50 --target-face=2 --n-arrows=72 \
          --format-name="q_cm_72a_50m_80cm6ring" \
          --format=0 \
          --pretty-print \
          --output-append=$DATAFILE
../bin/archerystats --qualification \
          --level-1=131.2 --level-4=125.2 --level-8=123.6 --level-16=122.0 --level-32=120.0 --level-56=116.8 --level-104=109.0 \
          --n-runs=$NSIMS \
          --distance=50 --target-face=12 --n-arrows=72 \
          --format-name="q_cm_72a_50m_80cm6ringX11" \
          --format=0 \
          --pretty-print \
          --output-append=$DATAFILE
../bin/archerystats --qualification \
          --level-1=131.2 --level-4=125.2 --level-8=123.6 --level-16=122.0 --level-32=120.0 --level-56=116.8 --level-104=109.0 \
          --n-runs=$NSIMS \
          --distance=60 --target-face=2 --n-arrows=72 \
          --format-name="q_cm_72a_60m_80cm6ring" \
          --format=0 \
          --pretty-print \
          --output-append=$DATAFILE
# 60 arrows
../bin/archerystats --qualification \
          --level-1=131.2 --level-4=125.2 --level-8=123.6 --level-16=122.0 --level-32=120.0 --level-56=116.8 --level-104=109.0 \
          --n-runs=$NSIMS \
          --distance=50 --target-face=2 --n-arrows=60 \
          --format-name="q_cm_60a_50m_80cm6ring" \
          --format=0 \
          --pretty-print \
          --output-append=$DATAFILE
../bin/archerystats --qualification \
          --level-1=131.2 --level-4=125.2 --level-8=123.6 --level-16=122.0 --level-32=120.0 --level-56=116.8 --level-104=109.0 \
          --n-runs=$NSIMS \
          --distance=50 --target-face=12 --n-arrows=60 \
          --format-name="q_cm_60a_50m_80cm6ringX11" \
          --format=0 \
          --pretty-print \
          --output-append=$DATAFILE
../bin/archerystats --qualification \
          --level-1=131.2 --level-4=125.2 --level-8=123.6 --level-16=122.0 --level-32=120.0 --level-56=116.8 --level-104=109.0 \
          --n-runs=$NSIMS \
          --distance=60 --target-face=2 --n-arrows=60 \
          --format-name="q_cm_60a_60m_80cm6ring" \
          --format=0 \
          --pretty-print \
          --output-append=$DATAFILE
# 48 arrows
../bin/archerystats --qualification \
          --level-1=131.2 --level-4=125.2 --level-8=123.6 --level-16=122.0 --level-32=120.0 --level-56=116.8 --level-104=109.0 \
          --n-runs=$NSIMS \
          --distance=50 --target-face=2 --n-arrows=48 \
          --format-name="q_cm_48a_50m_80cm6ring" \
          --format=0 \
          --pretty-print \
          --output-append=$DATAFILE
../bin/archerystats --qualification \
          --level-1=131.2 --level-4=125.2 --level-8=123.6 --level-16=122.0 --level-32=120.0 --level-56=116.8 --level-104=109.0 \
          --n-runs=$NSIMS \
          --distance=50 --target-face=12 --n-arrows=48 \
          --format-name="q_cm_48a_50m_80cm6ringX11" \
          --format=0 \
          --pretty-print \
          --output-append=$DATAFILE
../bin/archerystats --qualification \
          --level-1=131.2 --level-4=125.2 --level-8=123.6 --level-16=122.0 --level-32=120.0 --level-56=116.8 --level-104=109.0 \
          --n-runs=$NSIMS \
          --distance=60 --target-face=2 --n-arrows=48 \
          --format-name="q_cm_48a_60m_80cm6ring" \
          --pretty-print \
          --format=0 \
          --output-append=$DATAFILE
# 144 arrows
../bin/archerystats --qualification \
          --level-1=131.2 --level-4=125.2 --level-8=123.6 --level-16=122.0 --level-32=120.0 --level-56=116.8 --level-104=109.0 \
          --n-runs=$NSIMS \
          --distance=50 --target-face=2 --n-arrows=144 \
          --format-name="q_cm_144a_50m_80cm6ring_REFERENCE" \
          --format=0 \
          --pretty-print \
          --output-append=$DATAFILE





