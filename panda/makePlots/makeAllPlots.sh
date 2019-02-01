#!/bin/sh

./MitAnalysisRunII/panda/makePlots/mergeHistograms.sh;

./MitAnalysisRunII/panda/makePlots/makePlots.sh wz 1 2016;
./MitAnalysisRunII/panda/makePlots/makePlots.sh wz 1 2017;
./MitAnalysisRunII/panda/makePlots/makePlots.sh wz 1 2018;
./MitAnalysisRunII/panda/makePlots/makePlots.sh wz 1 2019;

./MitAnalysisRunII/panda/makePlots/makePlots.sh zz 1 2016;
./MitAnalysisRunII/panda/makePlots/makePlots.sh zz 1 2017;
./MitAnalysisRunII/panda/makePlots/makePlots.sh zz 1 2018;
./MitAnalysisRunII/panda/makePlots/makePlots.sh zz 1 2019;

./MitAnalysisRunII/panda/makePlots/makePlots.sh zh 0 2016;
./MitAnalysisRunII/panda/makePlots/makePlots.sh zh 0 2017;
./MitAnalysisRunII/panda/makePlots/makePlots.sh zh 0 2018;
./MitAnalysisRunII/panda/makePlots/makePlots.sh zh 0 2019;

./MitAnalysisRunII/panda/makePlots/makePlots.sh z 1 2016;
./MitAnalysisRunII/panda/makePlots/makePlots.sh z 1 2017;
./MitAnalysisRunII/panda/makePlots/makePlots.sh z 1 2018;

./MitAnalysisRunII/panda/makePlots/makePlots.sh zhg 0 2016;
./MitAnalysisRunII/panda/makePlots/makePlots.sh zhg 0 2017;
./MitAnalysisRunII/panda/makePlots/makePlots.sh zhg 0 2018;
./MitAnalysisRunII/panda/makePlots/makePlots.sh zhg 0 2019;

./MitAnalysisRunII/panda/makePlots/makePlots.sh ssww 0 2016;
./MitAnalysisRunII/panda/makePlots/makePlots.sh ssww 0 2017;
./MitAnalysisRunII/panda/makePlots/makePlots.sh ssww 0 2018;
./MitAnalysisRunII/panda/makePlots/makePlots.sh ssww 0 2019;
