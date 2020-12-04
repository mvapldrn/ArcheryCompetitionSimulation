#!/usr/bin/bash
#-------------------------------------------------------------------------------------------
# Name      : generate.sh
# Purpose   : To call the archerystats tool with different settings in an automated way
# Author    : Marcel van Apeldoorn <mvapldrn@gmail.com>
# Copyright : 2020
# ------------------------------------------------------------------------------------------

DATANAME=test

OUTPUT=../data/${DATANAME}
rm -f ${OUTPUT}

NRUNS=100

# Setup performance levels
ALL_PERF_LEVELS=()
ALL_PERF_NAMES=()
ALL_PERF_LEVELS+=( '--level-1=131.2 --level-4=125.2 --level-8=123.6 --level-16=122.0 --level-32=120.0 --level-56=116.8 --level-104=109.0' )
ALL_PERF_NAMES+=( 'CM Level Outdoor WorldChampionship 2019' )
ALL_PERF_LEVELS+=( '--level-1=120.0 --level-4=120.0 --level-8=120.0 --level-16=120.0 --level-32=120.0 --level-56=120.0 --level-104=120.0' )
ALL_PERF_NAMES+=( 'CW Level Outdoor WorldChampionships 2019' )


#ALL_PERF_LEVELS+=( '--level-1=118.0 --level-4=111.9 --level-8=105.8 --level-16=101.9 --level-32=99.3 --level-56=95.0 --level-104=82.0' )
#ALL_PERF_NAMES+=( 'Recurve Men' )

# Setup distances
ALL_DISTANCES=( 50 60 65 )

# Setup targets
ALL_TARGET_FACES=( 2 12 4 )

# Setup arrows
ALL_N_ARROWS=( 144 72 60 48 36 )


FORMAT=0

EXE=../bin/archerystats

for i in ${!ALL_PERF_LEVELS[@]};
do
PERF_LEVELS=${ALL_PERF_LEVELS[$i]}
PERF_NAME=${ALL_PERF_NAMES[$i]}

for DISTANCE in ${ALL_DISTANCES[@]}; do
for TARGET_FACE in ${ALL_TARGET_FACES[@]}; do
for N_ARROWS in ${ALL_N_ARROWS[@]}; do

    ${EXE} --qualification ${PERF_LEVELS} --level-name="${PERF_NAME}" \
            --n-runs=${NRUNS} --distance=${DISTANCE} --target-face=${TARGET_FACE} --n-arrows=${N_ARROWS} --format==${FORMAT} \
            --output-append=${OUTPUT}
done
done
done
done

exit




./archerystats --elimination \
          --start-level=75 --end-level=120 --level-step=1 \
          --n-runs=$NSIMS \
          --distance=70 --target-face=0 --best-of-sets=5 --n-arrows=3 \
          --format-name="5set3a" \
          --format=1 \
          --output=h2h_wa122cm_70m_set_3a_bo5
echo "OK"

echo -n "Elimination statistics on 70m at 122cm World archery face normal scoring, cumulative scoring 12 arrows..."
./archerystats --elimination \
          --start-level=75 --end-level=120 --level-step=1 \
          --n-runs=$NSIMS \
          --distance=70 --target-face=0 --n-arrows=12 \
          --format-name="cum12a" \
          --format=0 \
          --output=h2h_wa122cm_70m_cum_12a
echo "OK"

echo -n "Elimination statistics on 70m at 122cm World archery face normal scoring, cumulative scoring 15 arrows..."
./archerystats --elimination \
          --start-level=75 --end-level=120 --level-step=1 \
          --n-runs=$NSIMS \
          --distance=70 --target-face=0 --n-arrows=15 \
          --format-name="cum15a" \
          --format=0 \
          --output=h2h_wa122cm_70m_cum_15a
echo "OK"

echo -n "Elimination statistics on 70m at 122cm World archery face normal scoring, set system best of 7 3 arrow sets..."
./archerystats --elimination \
          --start-level=75 --end-level=120 --level-step=1 \
          --n-runs=$NSIMS \
          --distance=70 --target-face=0 --best-of-sets=7 --n-arrows=3 \
          --format-name="7set3a" \
          --format=1 \
          --output=h2h_wa122cm_70m_set_3a_bo7
echo "OK"

echo -n "Elimination statistics on 70m at 122cm World archery face normal scoring, set system best of 5 4 arrow sets..."
./archerystats --elimination \
          --start-level=75 --end-level=120 --level-step=1 \
          --n-runs=$NSIMS \
          --distance=70 --target-face=0 --best-of-sets=5 --n-arrows=4 \
          --format-name="5set4a" \
          --format=1 \
          --output=h2h_wa122cm_70m_set_4a_bo5
echo "OK"

echo -n "Elimination statistics on 70m at 122cm World archery face normal scoring, set system best of 5 5 arrow sets..."
./archerystats --elimination \
          --start-level=75 --end-level=120 --level-step=1 \
          --n-runs=$NSIMS \
          --distance=70 --target-face=0 --best-of-sets=5 --n-arrows=5 \
          --format-name="5set5a" \
          --format=1 \
          --output=h2h_wa122cm_70m_set_5a_bo5
echo "OK"

echo -n "Elimination statistics on 70m at 122cm World archery face normal scoring, set system best of 5 6 arrow sets..."
./archerystats --elimination \
          --start-level=75 --end-level=120 --level-step=1 \
          --n-runs=$NSIMS \
          --distance=70 --target-face=0 --best-of-sets=5 --n-arrows=6 \
          --format-name="5set6a" \
          --format=1 \
          --output=h2h_wa122cm_70m_set_6a_bo5
echo "OK"

echo -n "Elimination statistics on 70m at 122cm World archery face normal scoring, single arrow shootoff..."
./archerystats --elimination \
          --start-level=75 --end-level=120 --level-step=1 \
          --n-runs=$NSIMS \
          --distance=70 --target-face=0 \
          --format-name="so1a" \
          --format=2 \
          --output=h2h_wa122cm_70m_1a_so
echo "OK"

echo -n "Elimination statistics on 70m at 80cm 6 ring face normal scoring, set system best of 5 3 arrow sets..."
./archerystats --elimination \
          --start-level=75 --end-level=120 --level-step=1 \
          --n-runs=$NSIMS \
          --distance=70 --target-face=1 --best-of-sets=5 --n-arrows=3 \
          --format-name="5set3a" \
          --format=1 \
          --output=h2h_80cm6rings_70m_set_3a_bo5
echo "OK"

echo -n "Elimination statistics on 70m at 122cm Extreme (Pinhole scores 100), set system best of 5 3 arrow sets..."
./archerystats --elimination \
          --start-level=75 --end-level=120 --level-step=1 \
          --n-runs=$NSIMS \
          --distance=70 --target-face=8 --best-of-sets=5 --n-arrows=3 \
          --format-name="5set3a" \
          --format=1 \
          --output=h2h_122cmextremepinholescore_70m_set_3a_bo5
echo "OK"

echo -n "Elimination statistics on 70m at 122cm Extreme (Pinhole scores 100), cumulative 15 arrows..."
./archerystats --elimination \
          --start-level=75 --end-level=120 --level-step=1 \
          --n-runs=$NSIMS \
          --distance=70 --target-face=8 --n-arrows=15 \
          --format-name="cum12a" \
          --format=0 \
          --output=h2h_122cmextremepinholescore_70m_cum_15a
echo "OK"





