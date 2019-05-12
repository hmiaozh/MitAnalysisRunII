#!/bin/sh

rm -rf /data/t3serv014/ceballos/submit/whbb/*
#rm -rf MitVHBBAnalysis/datacards/whbb/*

MitVHBBAnalysis/bash/buildJobArgsWh.sh whbb/testcondor2016 3 2016 true
grep -v Presel MitVHBBAnalysis/datacards/whbb/testcondor2016/jobArgs.txt | grep -v WHTT1bFJCR > lll
#grep -v Presel MitVHBBAnalysis/datacards/whbb/testcondor2016/jobArgs.txt | grep -v WHTT1bFJCR | grep SR > lll
#grep -v Presel MitVHBBAnalysis/datacards/whbb/testcondor2016/jobArgs.txt | grep -v WHTT1bFJCR | grep SR | grep mH125 > lll
mv lll MitVHBBAnalysis/datacards/whbb/testcondor2016/jobArgs.txt
PandaCore/bin/submit --exec MitVHBBAnalysis/bash/runWhAnalysis.sh --njobs 1000 --arglist MitVHBBAnalysis/datacards/whbb/testcondor2016/jobArgs.txt --cache /data/t3serv014/ceballos/submit/whbb/testcondor2016

#PandaCore/bin/check --cache /data/t3serv014/ceballos/submit/whbb/testcondor2016
#MitVHBBAnalysis/bash/mergeOutputWh.sh whbb/testcondor2016

MitVHBBAnalysis/bash/buildJobArgsWh.sh whbb/testcondor2017 3 2017 true
grep -v Presel MitVHBBAnalysis/datacards/whbb/testcondor2017/jobArgs.txt | grep -v WHTT1bFJCR > lll
#grep -v Presel MitVHBBAnalysis/datacards/whbb/testcondor2017/jobArgs.txt | grep -v WHTT1bFJCR | grep SR > lll
#grep -v Presel MitVHBBAnalysis/datacards/whbb/testcondor2017/jobArgs.txt | grep -v WHTT1bFJCR | grep SR | grep mH125 > lll
mv lll MitVHBBAnalysis/datacards/whbb/testcondor2017/jobArgs.txt
PandaCore/bin/submit --exec MitVHBBAnalysis/bash/runWhAnalysis.sh --njobs 1000 --arglist MitVHBBAnalysis/datacards/whbb/testcondor2017/jobArgs.txt --cache /data/t3serv014/ceballos/submit/whbb/testcondor2017

#PandaCore/bin/check --cache /data/t3serv014/ceballos/submit/whbb/testcondor2017
#MitVHBBAnalysis/bash/mergeOutputWh.sh whbb/testcondor2017

MitVHBBAnalysis/bash/buildJobArgsWh.sh whbb/testcondor2018 3 2018 true
grep -v Presel MitVHBBAnalysis/datacards/whbb/testcondor2018/jobArgs.txt | grep -v WHTT1bFJCR > lll
#grep -v Presel MitVHBBAnalysis/datacards/whbb/testcondor2018/jobArgs.txt | grep -v WHTT1bFJCR | grep SR > lll
#grep -v Presel MitVHBBAnalysis/datacards/whbb/testcondor2018/jobArgs.txt | grep -v WHTT1bFJCR | grep SR | grep mH125 > lll
mv lll MitVHBBAnalysis/datacards/whbb/testcondor2018/jobArgs.txt
PandaCore/bin/submit --exec MitVHBBAnalysis/bash/runWhAnalysis.sh --njobs 1000 --arglist MitVHBBAnalysis/datacards/whbb/testcondor2018/jobArgs.txt --cache /data/t3serv014/ceballos/submit/whbb/testcondor2018

#PandaCore/bin/check --cache /data/t3serv014/ceballos/submit/whbb/testcondor2018
#MitVHBBAnalysis/bash/mergeOutputWh.sh whbb/testcondor2018

exit;
MitVHBBAnalysis/bash/runWhAnalysis.sh whbb/testcondor2018 kWHLightFlavorFJCR true 3 2018 false SingleTop_tbarW_noHad vhbbPlot::kTop
ls -l MitVHBBAnalysis/datacards/whbb/testcondor2016/split/|grep HSR|wc
ls -l MitVHBBAnalysis/datacards/whbb/testcondor2016/split/|grep H2TopCR|wc
ls -l MitVHBBAnalysis/datacards/whbb/testcondor2016/split/|grep HHeavyFlavorCR|wc
ls -l MitVHBBAnalysis/datacards/whbb/testcondor2016/split/|grep HLightFlavorCR|wc
ls -l MitVHBBAnalysis/datacards/whbb/testcondor2016/split/|grep HFJSR|wc
ls -l MitVHBBAnalysis/datacards/whbb/testcondor2016/split/|grep TT2bFJCR|wc
ls -l MitVHBBAnalysis/datacards/whbb/testcondor2016/split/|grep HHeavyFlavorFJCR|wc
ls -l MitVHBBAnalysis/datacards/whbb/testcondor2016/split/|grep HLightFlavorFJCR|wc

ls -l MitVHBBAnalysis/datacards/whbb/testcondor2017/split/|grep HSR|wc
ls -l MitVHBBAnalysis/datacards/whbb/testcondor2017/split/|grep H2TopCR|wc
ls -l MitVHBBAnalysis/datacards/whbb/testcondor2017/split/|grep HHeavyFlavorCR|wc
ls -l MitVHBBAnalysis/datacards/whbb/testcondor2017/split/|grep HLightFlavorCR|wc
ls -l MitVHBBAnalysis/datacards/whbb/testcondor2017/split/|grep HFJSR|wc
ls -l MitVHBBAnalysis/datacards/whbb/testcondor2017/split/|grep TT2bFJCR|wc
ls -l MitVHBBAnalysis/datacards/whbb/testcondor2017/split/|grep HHeavyFlavorFJCR|wc
ls -l MitVHBBAnalysis/datacards/whbb/testcondor2017/split/|grep HLightFlavorFJCR|wc

ls -l MitVHBBAnalysis/datacards/whbb/testcondor2018/split/|grep HSR|wc
ls -l MitVHBBAnalysis/datacards/whbb/testcondor2018/split/|grep H2TopCR|wc
ls -l MitVHBBAnalysis/datacards/whbb/testcondor2018/split/|grep HHeavyFlavorCR|wc
ls -l MitVHBBAnalysis/datacards/whbb/testcondor2018/split/|grep HLightFlavorCR|wc
ls -l MitVHBBAnalysis/datacards/whbb/testcondor2018/split/|grep HFJSR|wc
ls -l MitVHBBAnalysis/datacards/whbb/testcondor2018/split/|grep TT2bFJCR|wc
ls -l MitVHBBAnalysis/datacards/whbb/testcondor2018/split/|grep HHeavyFlavorFJCR|wc
ls -l MitVHBBAnalysis/datacards/whbb/testcondor2018/split/|grep HLightFlavorFJCR|wc
