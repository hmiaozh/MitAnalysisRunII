#!/bin/sh

#root -q -b -l MitAnalysisRunII/panda/makePlots/make2DPlots.C+'(2016,"pdf")';
#root -q -b -l MitAnalysisRunII/panda/makePlots/make2DPlots.C+'(2017,"pdf")';
#root -q -b -l MitAnalysisRunII/panda/makePlots/make2DPlots.C+'(2018,"pdf")';

#./MitAnalysisRunII/panda/makePlots/mergeHistograms.sh;

./MitAnalysisRunII/panda/makePlots/makePlots.sh wz 1 2016;
./MitAnalysisRunII/panda/makePlots/makePlots.sh wz 1 2017;
./MitAnalysisRunII/panda/makePlots/makePlots.sh wz 1 2018;
./MitAnalysisRunII/panda/makePlots/makePlots.sh wz 1 2019;

./MitAnalysisRunII/panda/makePlots/makePlots.sh zz 1 2016;
./MitAnalysisRunII/panda/makePlots/makePlots.sh zz 1 2017;
./MitAnalysisRunII/panda/makePlots/makePlots.sh zz 1 2018;
./MitAnalysisRunII/panda/makePlots/makePlots.sh zz 1 2019;

./MitAnalysisRunII/panda/makePlots/makePlots.sh zh 1 2016;
./MitAnalysisRunII/panda/makePlots/makePlots.sh zh 1 2017;
./MitAnalysisRunII/panda/makePlots/makePlots.sh zh 1 2018;
./MitAnalysisRunII/panda/makePlots/makePlots.sh zh 1 2019;

./MitAnalysisRunII/panda/makePlots/makePlots.sh zhg 0 2016;
./MitAnalysisRunII/panda/makePlots/makePlots.sh zhg 0 2017;
./MitAnalysisRunII/panda/makePlots/makePlots.sh zhg 0 2018;
./MitAnalysisRunII/panda/makePlots/makePlots.sh zhg 0 2019;
./MitAnalysisRunII/panda/makePlots/makePlots.sh zhgpaper 0 2019;

./MitAnalysisRunII/panda/makePlots/makePlots.sh ssww 0 2016;
./MitAnalysisRunII/panda/makePlots/makePlots.sh ssww 0 2017;
./MitAnalysisRunII/panda/makePlots/makePlots.sh ssww 0 2018;
./MitAnalysisRunII/panda/makePlots/makePlots.sh ssww 0 2019;

./MitAnalysisRunII/panda/makePlots/makePlots.sh z 1 2016;
./MitAnalysisRunII/panda/makePlots/makePlots.sh z 1 2017;
./MitAnalysisRunII/panda/makePlots/makePlots.sh z 1 2018;

./MitAnalysisRunII/panda/makePlots/makePlots.sh ww 0 2016;
./MitAnalysisRunII/panda/makePlots/makePlots.sh ww 0 2017;
./MitAnalysisRunII/panda/makePlots/makePlots.sh ww 0 2018;
