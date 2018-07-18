--> setup
source MitAnalysisRunII/panda/bin/80x/setup_leptonic.sh

--> run macro 
PandaAnalysis/T3/inputs/skim_lep_tmpl.py

--> Datasets to be included
PandaAnalysis/T3/bin/catalogT2Prod.py --outfile ~/public_html/$USER/catalog/test.cfg --catalog ~cmsprod/catalog/t2mit/pandaf/009 --include SingleElectron SingleMuon DoubleEG DoubleMuon MuonEG ZJets_nlo ZJets_lo --exclude EWK

# standard
PandaAnalysis/T3/bin/catalogT2Prod.py --outfile ~/public_html/$USER/catalog/test.cfg --catalog ~cmsprod/catalog/t2mit/pandaf/009 \
--include SingleElectron SingleMuon DoubleEG DoubleMuon MuonEG ZZ WZ WW DYJetsToLL_M-50_Tune DYJetsToLL_M-10to50_Tune tZq GluGluH VBFH VBF_H ttHToNonbb VHToNonbb \
TTG TTZ TTW ST_tW TTTo2L2Nu WGstarTo WGToLNuG ZGTo2LG JetsToLL DYJetsToTauTau NNPDF30_13TeV-powheg MET WJetsToLNu TT_TuneCUETP8M2T4 WpWpJJ ZJToEEJ --exclude ZpWW_med JetsToLL_M-50_HT

# fakes
PandaAnalysis/T3/bin/catalogT2Prod.py --outfile ~/public_html/$USER/catalog/test.cfg --catalog ~cmsprod/catalog/t2mit/pandaf/009 \
--include SingleElectron SingleMuon DoubleEG DoubleMuon MuonEG ZZ WZ WW DYJetsToLL_M-50_Tune DYJetsToLL_M-10to50_Tune tZq \
GluGluH VBFH VBF_H ttHToNonbb VHToNonbb TTG TTZ TTW ST_tW  WGstarTo WGToLNuG ZGTo2LG  WJetsToLNu TT_TuneCUETP8M2T4 \
--exclude ZpWW_med JetsToLL_M-50_HT DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM

--> Processes must be included in 
PandaCore/Tools/python/processes/*.py

--> Define how many files to be ran per job
PandaAnalysis/T3/bin/buildMergedInputs.sh -t -n 30

--> Submit
PandaAnalysis/T3/bin/submit.py

--> Check status
PandaAnalysis/T3/bin/checkMissingFiles.py


--> Merge files once all jobs are done
PandaAnalysis/T3/merging/merge_Leptonic.py WZ                   
