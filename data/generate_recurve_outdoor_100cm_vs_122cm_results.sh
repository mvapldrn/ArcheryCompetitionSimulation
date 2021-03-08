#!/usr/bin/bash
#-------------------------------------------------------------------------------------------
# Name      : generate_recurve_outdoor_100cm_vs_122cm_results.sh
# Purpose   : To evaluate the differences between 122cm and 100cm target face and 72 and
#             60 arrow ranking rounds
# Author    : Marcel van Apeldoorn <mvapldrn@gmail.com>
# Copyright : 2021
# ------------------------------------------------------------------------------------------


# ==================================== SIMULATE QUALIFICATIONS IN DIFFERENT FORMATS AND DIFFERENT FACES ========================================
NSIMS=1000000

DATAFILE=data_100cm_vs_122cm.csv

# Uncomment line below to do pretty-printing.
PRETTYPRINT=--pretty-print

RM_SKILL="--level-1=117.0 --level-4=115.0 --level-8=110.6 --level-16=107.2 --level-32=105.0 --level-56=101.2 --level-104=94.5 --level-name=\"RM Outdoor WorldChampionship 2019\" "
RW_SKILL="--level-1=114.5 --level-4=107.2 --level-8=104.1 --level-16=101.0 --level-32=98.0 --level-56=94.0 --level-104=85.2 --level-name=\"RW Outdoor WorldChampionship 2019\" "

rm -f $DATAFILE

echo "RM Outdoor qualification statistics"
for NARROWS in 72 60; do
  for f in "122cm 0" "100cm 16"; do
    FACE=( $f )

    QFMT_NAME="q_rm_${NARROWS}a_70m_${FACE[0]}10rings"
    echo ${QFMT_NAME}
    ../bin/archerystats --qualification \
        ${RM_SKILL} \
        --n-runs=$NSIMS \
        --distance=70 --target-face=${FACE[1]} --n-arrows=${NARROWS} \
        --format-name=${QFMT_NAME} \
        --format=0 \
        ${PRETTYPRINT} \
        --output-append=$DATAFILE
  done
done
echo "RM Outdoor competitions statistics"
for NARROWS in 72 60; do
  for f in "122cm 0" "100cm 16"; do
    FACE=( $f )

    QFMT_NAME="q_rm_${NARROWS}a_70m_${FACE[0]}10rings"
    EFMT_NAME="e_rm_3abo5_70m_${FACE[0]}10rings"
    echo "${QFMT_NAME} -> ${EFMT_NAME}"

    ../bin/archerystats --competitions \
        ${RM_SKILL} \
        --n-runs-qualification=1 --n-runs=$NSIMS \
        --distance=70 --target-face=${FACE[1]} --n-arrows-qualification=${NARROWS} --n-arrows-elimination=3 --best-of-sets=5 \
        --format-name-qualification=${QFMT_NAME} --format-name-elimination=${EFMT_NAME} \
        --format-qualification=0 --format-elimination=1 \
        ${PRETTYPRINT} \
        --output-append=$DATAFILE
  done
done

echo "RW Outdoor qualification statistics"
for NARROWS in 72 60; do
  for f in "122cm 0" "100cm 16"; do
    FACE=( $f )

    QFMT_NAME="q_rw_${NARROWS}a_70m_${FACE[0]}10rings"
    echo ${QFMT_NAME}
    ../bin/archerystats --qualification \
        ${RW_SKILL} \
        --n-runs=$NSIMS \
        --distance=70 --target-face=${FACE[1]} --n-arrows=${NARROWS} \
        --format-name=${QFMT_NAME} \
        --format=0 \
        ${PRETTYPRINT} \
        --output-append=$DATAFILE
  done
done
echo "RW Outdoor competitions statistics"
for NARROWS in 72 60; do
  for f in "122cm 0" "100cm 16"; do
    FACE=( $f )

    QFMT_NAME="q_rw_${NARROWS}a_70m_${FACE[0]}10rings"
    EFMT_NAME="e_rw_3abo5_70m_${FACE[0]}10rings"
    echo "${QFMT_NAME} -> ${EFMT_NAME}"

    ../bin/archerystats --competitions \
        ${RM_SKILL} \
        --n-runs-qualification=1 --n-runs=$NSIMS \
        --distance=70 --target-face=${FACE[1]} --n-arrows-qualification=${NARROWS} --n-arrows-elimination=3 --best-of-sets=5 \
        --format-name-qualification=${QFMT_NAME} --format-name-elimination=${EFMT_NAME} \
        --format-qualification=0 --format-elimination=1 \
        ${PRETTYPRINT} \
        --output-append=$DATAFILE
  done
done

