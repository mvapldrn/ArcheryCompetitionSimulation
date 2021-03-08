#!/usr/bin/bash

NSIMS=1000

CMASL1=133.5
CMASL8=127.5
CMASL16=125.0
CMASL32=120.5
CMASL56=117.0
CMASL104=111.5

CWASL1=122.5
CWASL8=116.0
CWASL16=112.5
CWASL32=106.5
CWASL56=99.5
CWASL104=65.5

# Competition levels according to Nimes 2017

# WA 40cm target face (face=3)
echo -n "CM  Indoor: Competitions, 18m60/15arrows, WA 40cm face"
./archerystats --competitions \
          --progress --pretty-print \
          --level-1=$CMASL1 --level-8=$CMASL8 --level-16=$CMASL16 --level-32=$CMASL32 --level-56=$CMASL56 --level-104=$CMASL104 \
          --n-runs=$NSIMS \
          --format=0 --distance=18 --n-arrows-elimination=15 --n-arrows-qualification=60 --arrow-diameter=9.3 \
          --target-face=3 \
          --format-name="indoor" \
          --output=cm_indoor_40cm
echo "OK"

echo -n "CW  Indoor: Competitions, 18m60/15arrows, WA 40cm face"
./archerystats --competitions \
          --progress --pretty-print \
          --level-1=$CWASL1 --level-8=$CWASL8 --level-16=$CWASL16 --level-32=$CWASL32 --level-56=$CWASL56 --level-104=$CWASL104 \
          --n-runs=$NSIMS \
          --format=0 --distance=18 --n-arrows-elimination=15 --n-arrows-qualification=60 --arrow-diameter=9.3 \
          --target-face=3 \
          --format-name="indoor" \
          --output=cw_indoor_40cm
echo "OK"

# WA 40cm target face (face=3)
echo -n "CM  Indoor: Competitions, 18m60/18arrows, WA 40cm face"
./archerystats --competitions \
          --progress --pretty-print \
          --level-1=$CMASL1 --level-8=$CMASL8 --level-16=$CMASL16 --level-32=$CMASL32 --level-56=$CMASL56 --level-104=$CMASL104 \
          --n-runs=$NSIMS \
          --format=0 --distance=18 --n-arrows-elimination=18 --n-arrows-qualification=60 --arrow-diameter=9.3 \
          --target-face=3 \
          --format-name="indoor" \
          --output=cm_indoor_40cm18arrows
echo "OK"

echo -n "CW  Indoor: Competitions, 18m60/18arrows, WA 40cm face"
./archerystats --competitions \
          --progress --pretty-print \
          --level-1=$CWASL1 --level-8=$CWASL8 --level-16=$CWASL16 --level-32=$CWASL32 --level-56=$CWASL56 --level-104=$CWASL104 \
          --n-runs=$NSIMS \
          --format=0 --distance=18 --n-arrows-elimination=18 --n-arrows-qualification=60 --arrow-diameter=9.3 \
          --target-face=3 \
          --format-name="indoor" \
          --output=cw_indoor_40cm18arrows
echo "OK"


# 10,30,50,70,90 target face (face=4)
echo -n "CM  Indoor: Competitions, 18m 60/15arrows, Test 10,30,50,70,90 face"
./archerystats --competitions \
          --progress --pretty-print \
          --level-1=$CMASL1 --level-8=$CMASL8 --level-16=$CMASL16 --level-32=$CMASL32 --level-56=$CMASL56 --level-104=$CMASL104 \
          --n-runs=$NSIMS \
          --format=0 --distance=18 --n-arrows-elimination=15 --n-arrows-qualification=60 --arrow-diameter=9.3 \
          --target-face=4 \
          --format-name="indoor" \
          --output=cm_indoor_10_30_50_70_90
echo "OK"

echo -n "CW  Indoor: Competitions, 18m60/15arrows, Test 10,30,50,70,90 face"
./archerystats --competitions \
          --progress --pretty-print \
          --level-1=$CWASL1 --level-8=$CWASL8 --level-16=$CWASL16 --level-32=$CWASL32 --level-56=$CWASL56 --level-104=$CWASL104 \
          --n-runs=$NSIMS \
          --format=0 --distance=18 --n-arrows-elimination=15 --n-arrows-qualification=60 --arrow-diameter=9.3 \
          --target-face=4 \
          --format-name="indoor" \
          --output=cw_indoor_10_30_50_70_90
echo "OK"


# X=11 face (face=5)
echo -n "CM  Indoor: Competitions, 18m60/15arrows, 40cm X=11"
./archerystats --competitions \
          --progress --pretty-print \
          --level-1=$CMASL1 --level-8=$CMASL8 --level-16=$CMASL16 --level-32=$CMASL32 --level-56=$CMASL56 --level-104=$CMASL104 \
          --n-runs=$NSIMS \
          --format=0 --distance=18 --n-arrows-elimination=15 --n-arrows-qualification=60 --arrow-diameter=9.3 \
          --target-face=5 \
          --format-name="indoor" \
          --output=cm_indoor_x11
echo "OK"

echo -n "CW  Indoor: Competitions, 18m60/15arrows, 40cm X=11"
./archerystats --competitions \
          --progress --pretty-print \
          --level-1=$CWASL1 --level-8=$CWASL8 --level-16=$CWASL16 --level-32=$CWASL32 --level-56=$CWASL56 --level-104=$CWASL104 \
          --n-runs=$NSIMS \
          --format=0 --distance=18 --n-arrows-elimination=15 --n-arrows-qualification=60 --arrow-diameter=9.3 \
          --target-face=5 \
          --format-name="indoor" \
          --output=cw_indoor_x11
echo "OK"

# 20cm 5 rings (face=6)
echo -n "CM  Indoor: Competitions, 18m60/15arrows, 20cm 5rings"
./archerystats --competitions \
          --progress --pretty-print \
          --level-1=$CMASL1 --level-8=$CMASL8 --level-16=$CMASL16 --level-32=$CMASL32 --level-56=$CMASL56 --level-104=$CMASL104 \
          --n-runs=$NSIMS \
          --format=0 --distance=18 --n-arrows-elimination=15 --n-arrows-qualification=60 --arrow-diameter=9.3 \
          --target-face=6 \
          --format-name="indoor" \
          --output=cm_indoor_20cm
echo "OK"

echo -n "CW  Indoor: Competitions, 18m60/15arrows, 20cm 5rings"
./archerystats --competitions \
          --progress --pretty-print \
          --level-1=$CWASL1 --level-8=$CWASL8 --level-16=$CWASL16 --level-32=$CWASL32 --level-56=$CWASL56 --level-104=$CWASL104 \
          --n-runs=$NSIMS \
          --format=0 --distance=18 --n-arrows-elimination=15 --n-arrows-qualification=60 --arrow-diameter=9.3 \
          --target-face=6 \
          --format-name="indoor" \
          --output=cw_indoor_20cm
echo "OK"

# 40cm 5 rings -10% (face=7)
echo -n "CM  Indoor: Competitions, 18m60/15arrows, 40cm 5rings -10%"
./archerystats --competitions \
          --progress --pretty-print \
          --level-1=$CMASL1 --level-8=$CMASL8 --level-16=$CMASL16 --level-32=$CMASL32 --level-56=$CMASL56 --level-104=$CMASL104 \
          --n-runs=$NSIMS \
          --format=0 --distance=18 --n-arrows-elimination=15 --n-arrows-qualification=60 --arrow-diameter=9.3 \
          --target-face=7 \
          --format-name="indoor" \
          --output=cm_indoor_40cmmin10p
echo "OK"

echo -n "CW  Indoor: Competitions, 18m60/15arrows, 40cm 5rings -10%"
./archerystats --competitions \
          --progress --pretty-print \
          --level-1=$CWASL1 --level-8=$CWASL8 --level-16=$CWASL16 --level-32=$CWASL32 --level-56=$CWASL56 --level-104=$CWASL104 \
          --n-runs=$NSIMS \
          --format=0 --distance=18 --n-arrows-elimination=15 --n-arrows-qualification=60 --arrow-diameter=9.3 \
          --target-face=7 \
          --format-name="indoor" \
          --output=cw_indoor_40cmmin10p
echo "OK"


