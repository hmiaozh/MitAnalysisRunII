#!/bin/sh

rm -rf /data/t3serv014/ceballos/submit/zhbb/*
#rm -rf MitVHBBAnalysis/datacards/zhbb/*

MitVHBBAnalysis/bash/buildJobArgsZllh.sh zhbb/testcondor2016 3 2016 true
grep -v Presel MitVHBBAnalysis/datacards/zhbb/testcondor2016/jobArgs.txt | grep -v ZllHTT2bFJCR > lll
mv lll MitVHBBAnalysis/datacards/zhbb/testcondor2016/jobArgs.txt
PandaCore/bin/submit --exec MitVHBBAnalysis/bash/runZllhAnalysis.sh --njobs 1000 --arglist MitVHBBAnalysis/datacards/zhbb/testcondor2016/jobArgs.txt --cache /data/t3serv014/ceballos/submit/zhbb/testcondor2016

#PandaCore/bin/check --cache /data/t3serv014/ceballos/submit/zhbb/testcondor2016
#MitVHBBAnalysis/bash/mergeOutputZllh.sh zhbb/testcondor2016

MitVHBBAnalysis/bash/buildJobArgsZllh.sh zhbb/testcondor2017 3 2017 true
grep -v Presel MitVHBBAnalysis/datacards/zhbb/testcondor2017/jobArgs.txt | grep -v ZllHTT2bFJCR > lll
mv lll MitVHBBAnalysis/datacards/zhbb/testcondor2017/jobArgs.txt
PandaCore/bin/submit --exec MitVHBBAnalysis/bash/runZllhAnalysis.sh --njobs 1000 --arglist MitVHBBAnalysis/datacards/zhbb/testcondor2017/jobArgs.txt --cache /data/t3serv014/ceballos/submit/zhbb/testcondor2017

#PandaCore/bin/check --cache /data/t3serv014/ceballos/submit/zhbb/testcondor2017
#MitVHBBAnalysis/bash/mergeOutputZllh.sh zhbb/testcondor2017
