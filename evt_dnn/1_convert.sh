#!/bin/sh

export MAINDIR=/home/ceballos/cms/cmssw/051/CMSSW_10_3_2/src/MitVHBBAnalysis/mva;
export MODE=$1;
export SEL=$2;
export PREFIX=$3;
export YEAR=$4;

rm -rf /data/t3home000/ceballos/hbb/train_${YEAR}/${PREFIX};

if [ ${MODE} == 1 ]; then
echo VH VV_forZH_${YEAR} TW_forZH_${YEAR} TT_forZH_${YEAR} ZJets_forZH_${YEAR}                     | xargs -n1 -P5 python ./convert.py --out /data/t3home000/ceballos/hbb/train_${YEAR} --basedir ${MAINDIR}/zhbb/testcondor${YEAR}/split/ --json root_zh.json --sel ${SEL} --prefix ${PREFIX} --name

elif [ ${MODE} == 2 ]; then
echo VH VV_forWH_${YEAR} TW_forWH_${YEAR} TT_forWH_${YEAR} ZJets_forWH_${YEAR} WJets_forWH_${YEAR} | xargs -n1 -P5 python ./convert.py --out /data/t3home000/ceballos/hbb/train_${YEAR} --basedir ${MAINDIR}/whbb/testcondor${YEAR}/split/ --json root_wh.json --sel ${SEL} --prefix ${PREFIX} --name

fi
