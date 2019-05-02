#!/bin/sh

rm -rf /data/t3serv014/ceballos/submit/zhbb/*
#rm -rf MitVHBBAnalysis/datacards/zhbb/*

MitVHBBAnalysis/bash/buildJobArgsZllh.sh zhbb/testcondor2016 3 2016 true
grep -v Presel MitVHBBAnalysis/datacards/zhbb/testcondor2016/jobArgs.txt | grep -v ZllHTT2bFJCR > lll
#grep -v Presel MitVHBBAnalysis/datacards/zhbb/testcondor2016/jobArgs.txt | grep -v ZllHTT2bFJCR | grep SR > lll
#grep -v Presel MitVHBBAnalysis/datacards/zhbb/testcondor2016/jobArgs.txt | grep -v ZllHTT2bFJCR | grep SR | grep mH125 > lll
mv lll MitVHBBAnalysis/datacards/zhbb/testcondor2016/jobArgs.txt
PandaCore/bin/submit --exec MitVHBBAnalysis/bash/runZllhAnalysis.sh --njobs 1000 --arglist MitVHBBAnalysis/datacards/zhbb/testcondor2016/jobArgs.txt --cache /data/t3serv014/ceballos/submit/zhbb/testcondor2016

#PandaCore/bin/check --cache /data/t3serv014/ceballos/submit/zhbb/testcondor2016
#MitVHBBAnalysis/bash/mergeOutputZllh.sh zhbb/testcondor2016

MitVHBBAnalysis/bash/buildJobArgsZllh.sh zhbb/testcondor2017 3 2017 true
grep -v Presel MitVHBBAnalysis/datacards/zhbb/testcondor2017/jobArgs.txt | grep -v ZllHTT2bFJCR > lll
#grep -v Presel MitVHBBAnalysis/datacards/zhbb/testcondor2017/jobArgs.txt | grep -v ZllHTT2bFJCR | grep SR > lll
#grep -v Presel MitVHBBAnalysis/datacards/zhbb/testcondor2017/jobArgs.txt | grep -v ZllHTT2bFJCR | grep SR | grep mH125 > lll
mv lll MitVHBBAnalysis/datacards/zhbb/testcondor2017/jobArgs.txt
PandaCore/bin/submit --exec MitVHBBAnalysis/bash/runZllhAnalysis.sh --njobs 1000 --arglist MitVHBBAnalysis/datacards/zhbb/testcondor2017/jobArgs.txt --cache /data/t3serv014/ceballos/submit/zhbb/testcondor2017

#PandaCore/bin/check --cache /data/t3serv014/ceballos/submit/zhbb/testcondor2017
#MitVHBBAnalysis/bash/mergeOutputZllh.sh zhbb/testcondor2017

MitVHBBAnalysis/bash/buildJobArgsZllh.sh zhbb/testcondor2018 3 2018 true
grep -v Presel MitVHBBAnalysis/datacards/zhbb/testcondor2018/jobArgs.txt | grep -v ZllHTT2bFJCR > lll
#grep -v Presel MitVHBBAnalysis/datacards/zhbb/testcondor2018/jobArgs.txt | grep -v ZllHTT2bFJCR | grep SR > lll
#grep -v Presel MitVHBBAnalysis/datacards/zhbb/testcondor2018/jobArgs.txt | grep -v ZllHTT2bFJCR | grep SR | grep mH125 > lll
mv lll MitVHBBAnalysis/datacards/zhbb/testcondor2018/jobArgs.txt
PandaCore/bin/submit --exec MitVHBBAnalysis/bash/runZllhAnalysis.sh --njobs 1000 --arglist MitVHBBAnalysis/datacards/zhbb/testcondor2018/jobArgs.txt --cache /data/t3serv014/ceballos/submit/zhbb/testcondor2018

#PandaCore/bin/check --cache /data/t3serv014/ceballos/submit/zhbb/testcondor2018
#MitVHBBAnalysis/bash/mergeOutputZllh.sh zhbb/testcondor2018

exit;
MitVHBBAnalysis/bash/runZllhAnalysis.sh zhbb/testcondor2018 kZllHLightFlavorFJCR true 3 1 2018 SingleTop_tbarW_noHad vhbbPlot::kTop
ls -l MitVHBBAnalysis/datacards/zhbb/testcondor2016/split/|grep HSR|grep Zmm|wc
ls -l MitVHBBAnalysis/datacards/zhbb/testcondor2016/split/|grep H2TopCR|grep Zmm|wc
ls -l MitVHBBAnalysis/datacards/zhbb/testcondor2016/split/|grep HHeavyFlavorCR|grep Zmm|wc
ls -l MitVHBBAnalysis/datacards/zhbb/testcondor2016/split/|grep HLightFlavorCR|grep Zmm|wc
ls -l MitVHBBAnalysis/datacards/zhbb/testcondor2016/split/|grep HVZbbCR|grep Zmm|wc
ls -l MitVHBBAnalysis/datacards/zhbb/testcondor2016/split/|grep HFJSR|grep Zmm|wc
ls -l MitVHBBAnalysis/datacards/zhbb/testcondor2016/split/|grep HHeavyFlavorFJCR|grep Zmm|wc
ls -l MitVHBBAnalysis/datacards/zhbb/testcondor2016/split/|grep HLightFlavorFJCR|grep Zmm|wc
ls -l MitVHBBAnalysis/datacards/zhbb/testcondor2016/split/|grep HVZbbFJCR|grep Zmm|wc

ls -l MitVHBBAnalysis/datacards/zhbb/testcondor2017/split/|grep HSR|grep Zmm|wc
ls -l MitVHBBAnalysis/datacards/zhbb/testcondor2017/split/|grep H2TopCR|grep Zmm|wc
ls -l MitVHBBAnalysis/datacards/zhbb/testcondor2017/split/|grep HHeavyFlavorCR|grep Zmm|wc
ls -l MitVHBBAnalysis/datacards/zhbb/testcondor2017/split/|grep HLightFlavorCR|grep Zmm|wc
ls -l MitVHBBAnalysis/datacards/zhbb/testcondor2017/split/|grep HVZbbCR|grep Zmm|wc
ls -l MitVHBBAnalysis/datacards/zhbb/testcondor2017/split/|grep HFJSR|grep Zmm|wc
ls -l MitVHBBAnalysis/datacards/zhbb/testcondor2017/split/|grep HHeavyFlavorFJCR|grep Zmm|wc
ls -l MitVHBBAnalysis/datacards/zhbb/testcondor2017/split/|grep HLightFlavorFJCR|grep Zmm|wc
ls -l MitVHBBAnalysis/datacards/zhbb/testcondor2017/split/|grep HVZbbFJCR|grep Zmm|wc

ls -l MitVHBBAnalysis/datacards/zhbb/testcondor2018/split/|grep HSR|grep Zmm|wc
ls -l MitVHBBAnalysis/datacards/zhbb/testcondor2018/split/|grep H2TopCR|grep Zmm|wc
ls -l MitVHBBAnalysis/datacards/zhbb/testcondor2018/split/|grep HHeavyFlavorCR|grep Zmm|wc
ls -l MitVHBBAnalysis/datacards/zhbb/testcondor2018/split/|grep HLightFlavorCR|grep Zmm|wc
ls -l MitVHBBAnalysis/datacards/zhbb/testcondor2018/split/|grep HVZbbCR|grep Zmm|wc
ls -l MitVHBBAnalysis/datacards/zhbb/testcondor2018/split/|grep HFJSR|grep Zmm|wc
ls -l MitVHBBAnalysis/datacards/zhbb/testcondor2018/split/|grep HHeavyFlavorFJCR|grep Zmm|wc
ls -l MitVHBBAnalysis/datacards/zhbb/testcondor2018/split/|grep HLightFlavorFJCR|grep Zmm|wc
ls -l MitVHBBAnalysis/datacards/zhbb/testcondor2018/split/|grep HVZbbFJCR|grep Zmm|wc
