#!/bin/sh

export INPUTDIR=/eos/cms/store/caf/user/ceballos/Nero/merging_jsalfeld_80x;
export OUTPUTDIR=/eos/cms/store/caf/user/ceballos/Nero/output_jsalfeld_80x;

#ls $INPUTDIR|grep -e ChargedHiggs|awk '{printf("root -l -q -b MitAnalysisRunII/skimming/80x/makeOneSkimSample.C+\\(\\\"$INPUTDIR/%s\\\",\\\"$OUTPUTDIR/${PREFIX}%s\\\",\\\"dm\\\",$1\\)\n",$1,$1)}'

export PREFIX="";
if [ $1 == 1 ]
then
  export PREFIX="qcd_";
elif [ $1 == 2 ]
then
  export PREFIX="met_";
elif [ $1 == 3 ]
then
  export PREFIX="zmet_";
elif [ $1 == 4 ]
then
  export PREFIX="pho_";
fi

root -l -q -b MitAnalysisRunII/skimming/80x/makeOneSkimSample.C+\(\"$INPUTDIR/ChargedHiggsToWZTo3LNu_M300_13TeV-madgraph-pythia8_0000.root\",\"$OUTPUTDIR/${PREFIX}ChargedHiggsToWZTo3LNu_M300_13TeV-madgraph-pythia8.root\",\"dm\",$1\)
root -l -q -b MitAnalysisRunII/skimming/80x/makeOneSkimSample.C+\(\"$INPUTDIR/ChargedHiggsToWZTo3LNu_M400_13TeV-madgraph-pythia8_0000.root\",\"$OUTPUTDIR/${PREFIX}ChargedHiggsToWZTo3LNu_M400_13TeV-madgraph-pythia8.root\",\"dm\",$1\)
root -l -q -b MitAnalysisRunII/skimming/80x/makeOneSkimSample.C+\(\"$INPUTDIR/ChargedHiggsToWZTo3LNu_M500_13TeV-madgraph-pythia8_0000.root\",\"$OUTPUTDIR/${PREFIX}ChargedHiggsToWZTo3LNu_M500_13TeV-madgraph-pythia8.root\",\"dm\",$1\)
root -l -q -b MitAnalysisRunII/skimming/80x/makeOneSkimSample.C+\(\"$INPUTDIR/ChargedHiggsToWZTo3LNu_M600_13TeV-madgraph-pythia8_0000.root\",\"$OUTPUTDIR/${PREFIX}ChargedHiggsToWZTo3LNu_M600_13TeV-madgraph-pythia8.root\",\"dm\",$1\)
root -l -q -b MitAnalysisRunII/skimming/80x/makeOneSkimSample.C+\(\"$INPUTDIR/ChargedHiggsToWZTo3LNu_M700_13TeV-madgraph-pythia8_0000.root\",\"$OUTPUTDIR/${PREFIX}ChargedHiggsToWZTo3LNu_M700_13TeV-madgraph-pythia8.root\",\"dm\",$1\)
root -l -q -b MitAnalysisRunII/skimming/80x/makeOneSkimSample.C+\(\"$INPUTDIR/ChargedHiggsToWZTo3LNu_M800_13TeV-madgraph-pythia8_0000.root\",\"$OUTPUTDIR/${PREFIX}ChargedHiggsToWZTo3LNu_M800_13TeV-madgraph-pythia8.root\",\"dm\",$1\)
root -l -q -b MitAnalysisRunII/skimming/80x/makeOneSkimSample.C+\(\"$INPUTDIR/ChargedHiggsToWZTo3LNu_M900_13TeV-madgraph-pythia8_0000.root\",\"$OUTPUTDIR/${PREFIX}ChargedHiggsToWZTo3LNu_M900_13TeV-madgraph-pythia8.root\",\"dm\",$1\)
root -l -q -b MitAnalysisRunII/skimming/80x/makeOneSkimSample.C+\(\"$INPUTDIR/ChargedHiggsToWZTo3LNu_M1000_13TeV-madgraph-pythia8_0000.root\",\"$OUTPUTDIR/${PREFIX}ChargedHiggsToWZTo3LNu_M1000_13TeV-madgraph-pythia8.root\",\"dm\",$1\)
root -l -q -b MitAnalysisRunII/skimming/80x/makeOneSkimSample.C+\(\"$INPUTDIR/ChargedHiggsToWZTo3LNu_M1500_13TeV-madgraph-pythia8_0000.root\",\"$OUTPUTDIR/${PREFIX}ChargedHiggsToWZTo3LNu_M1500_13TeV-madgraph-pythia8.root\",\"dm\",$1\)
root -l -q -b MitAnalysisRunII/skimming/80x/makeOneSkimSample.C+\(\"$INPUTDIR/ChargedHiggsToWZTo3LNu_M2000_13TeV-madgraph-pythia8_0000.root\",\"$OUTPUTDIR/${PREFIX}ChargedHiggsToWZTo3LNu_M2000_13TeV-madgraph-pythia8.root\",\"dm\",$1\)


