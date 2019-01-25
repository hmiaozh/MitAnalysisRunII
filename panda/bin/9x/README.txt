
--> setup
source MitAnalysisRunII/panda/bin/9x/setup_leptonic_2016.sh
source MitAnalysisRunII/panda/bin/9x/setup_leptonic_fake_2016.sh
source MitAnalysisRunII/panda/bin/9x/setup_leptonic_2017.sh
source MitAnalysisRunII/panda/bin/9x/setup_leptonic_fake_2017.sh
source MitAnalysisRunII/panda/bin/9x/setup_leptonic_2018.sh
source MitAnalysisRunII/panda/bin/9x/setup_leptonic_fake_2018.sh

--> run macro make sure skim_lep_tmpl* correspond to 2016 or 2017 or 2018!!!
PandaAnalysis/T3/inputs/skim_lep_tmpl.py

PandaAnalysis/Flat/python/analysis.py
# useDeepCSV = True, remove or set to False for 2016

--> Datasets to be included
PandaAnalysis/T3/bin/catalogT2Prod.py --cfg leptonic --outfile ~/public_html/$USER/catalog/test.cfg --catalog ~cmsprod/catalog/t2mit/pandaf/012 --include SingleElectron SingleMuon DoubleEG DoubleMuon MuonEG EGamma ZJets_nlo ZJets_lo --exclude EWK

# standard 2016
PandaAnalysis/T3/bin/catalogT2Prod.py --cfg leptonic --outfile ~/public_html/$USER/catalog/test.cfg --catalog ~cmsprod/catalog/t2mit/pandaf/009 \
--include SingleElectron SingleMuon DoubleEG DoubleMuon MuonEG ZZ WZ WW WLLJJ DYJetsToLL_M-50_Tune DYJetsToLL_M-10to50_Tune tZq GluGluH VBFH VBF_H ttHToNonbb VHToNonbb \
TTG TTZ TTW ST_tW TTTo2L2Nu WGstarTo WGToLNuG ZGTo2LG JetsToLL DYJetsToTauTau MET WJetsToLNu TT_TuneCUETP8M2T4 WpWpJJ HToInvisible HToInv_ZToLL \
--exclude ZpWW_med JetsToLL_M-50_HT DYJetsToLL_Zpt-100to200_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 DYJetsToLL_Zpt-200toInf_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8

# fakes 2016
PandaAnalysis/T3/bin/catalogT2Prod.py --cfg leptonic --outfile ~/public_html/$USER/catalog/test3.cfg --catalog ~cmsprod/catalog/t2mit/pandaf/009 \
--include SingleElectron SingleMuon DoubleEG DoubleMuon MuonEG ZZ WZ WW DYJetsToLL_M-50_Tune DYJetsToLL_M-10to50_Tune tZq \
GluGluH VBFH VBF_H ttHToNonbb VHToNonbb TTG TTZ TTW ST_tW  WGstarTo WGToLNuG ZGTo2LG  WJetsToLNu TT_TuneCUETP8M2T4 \
--exclude ZpWW_med JetsToLL_M-50_HT DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM \
DYJetsToLL_Zpt-100to200_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 DYJetsToLL_Zpt-200toInf_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8 \
DoubleScattering WZTo3LNu_0Jets WZTo3LNu_1Jets WZTo3LNu_2Jets WZTo3LNu_3Jets

# standard 2017
PandaAnalysis/T3/bin/catalogT2Prod.py --cfg leptonic --outfile ~/public_html/$USER/catalog/test.cfg --catalog ~cmsprod/catalog/t2mit/pandaf/012 \
--include SingleElectron SingleMuon DoubleEG DoubleMuon MuonEG EGamma ZZ WZ WW JetsToLL_M-50 DYJetsToLL_M-10to50_Tune tZq GluGluH VBFH VBF_H ttHToNonbb VHToNonbb \
TTG TTZ TTW ST_tW TT WGstarTo WGToLNuG ZGTo2LG ZGToLLG JetsToLL DYJetsToTauTau NNPDF30_13TeV-powheg MET WJetsToLNu WpWpJJ WLLJJ JJ_EWK_M HToInvisible HToInv_ZToLL \
--exclude ZpWW_med JetsToLL_M-50_HT NNPDF30_13TeV-powheg DYJetsToLL_Zpt-100to200 DYJetsToLL_Zpt-200toInf ZZ_TuneCP5_13TeV-pythia8 WZ_TuneCP5_13TeV-pythia8 TTToSemiLeptonic TTTo2L2Nu_TuneCP5_13TeV

# fakes 2017
PandaAnalysis/T3/bin/catalogT2Prod.py --cfg leptonic --outfile ~/public_html/$USER/catalog/test3.cfg --catalog ~cmsprod/catalog/t2mit/pandaf/012 \
--include SingleElectron SingleMuon DoubleEG DoubleMuon MuonEG EGamma ZZ WZ WW DYJetsToLL_M-50_Tune DYJetsToLL_M-10to50_Tune tZq GluGluH VBFH VBF_H ttHToNonbb VHToNonbb \
TTG TTZ TTW ST_tW TT WGstarTo WGToLNuG ZGTo2LG ZGToLLG JetsToLL  WJetsToLNu \
--exclude ZpWW_med JetsToLL_M-50_HT NNPDF30_13TeV-powheg DYJetsToLL_Zpt-100to200 DYJetsToLL_Zpt-200toInf \
ZZ_TuneCP5_13TeV-pythia8 WZ_TuneCP5_13TeV-pythia8 DoubleScattering WZTo3LNu_mllmin01 Jets_MLL DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8 \
DY1JetsToLL DY2JetsToLL DY3JetsToLL DY4JetsToLL TTTo2L2Nu_TuneCP5_13TeV TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8

# standard 2018
PandaAnalysis/T3/bin/catalogT2Prod.py --cfg leptonic --outfile ~/public_html/$USER/catalog/test.cfg --catalog ~cmsprod/catalog/t2mit/pandaf/013 \
--include SingleElectron SingleMuon DoubleEG DoubleMuon MuonEG EGamma ZZ WZ WW JetsToLL_M-50 DYJetsToLL_M-10to50_Tune tZq GluGluH VBFH VBF_H ttHToNonbb VHToNonbb \
TTG TTZ TTW ST_tW TT WGstarTo WGToLNuG ZGTo2LG ZGToLLG JetsToLL DYJetsToTauTau NNPDF30_13TeV-powheg MET WJetsToLNu WpWpJJ WLLJJ JJ_EWK_M HToInvisible HToInv_ZToLL \
--exclude ZpWW_med JetsToLL_M-50_HT NNPDF30_13TeV-powheg DYJetsToLL_Zpt-100to200 DYJetsToLL_Zpt-200toInf ZZ_TuneCP5_13TeV-pythia8 WZ_TuneCP5_13TeV-pythia8 TTToSemiLeptonic

grep -vE '(Run2018A-PromptReco|Run2018B-PromptReco|Run2018C-PromptReco)' ~/public_html/$USER/catalog/test.cfg > lll;wc lll;mv lll ~/public_html/$USER/catalog/test.cfg;

# fakes 2018
PandaAnalysis/T3/bin/catalogT2Prod.py --cfg leptonic --outfile ~/public_html/$USER/catalog/test3.cfg --catalog ~cmsprod/catalog/t2mit/pandaf/013 \
--include SingleElectron SingleMuon DoubleEG DoubleMuon MuonEG EGamma ZZ WZ WW DYJetsToLL_M-50_Tune DYJetsToLL_M-10to50_Tune tZq GluGluH VBFH VBF_H ttHToNonbb VHToNonbb \
TTG TTZ TTW ST_tW TT WGstarTo WGToLNuG ZGTo2LG ZGToLLG JetsToLL  WJetsToLNu \
--exclude ZpWW_med JetsToLL_M-50_HT NNPDF30_13TeV-powheg DYJetsToLL_Zpt-100to200 DYJetsToLL_Zpt-200toInf \
ZZ_TuneCP5_13TeV-pythia8 WZ_TuneCP5_13TeV-pythia8 DoubleScattering WZTo3LNu_mllmin01 Jets_MLL DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8 \
DY1JetsToLL DY2JetsToLL DY3JetsToLL DY4JetsToLL

grep -vE '(Run2018A-PromptReco|Run2018B-PromptReco|Run2018C-PromptReco)' ~/public_html/$USER/catalog/test3.cfg > lll;wc lll;mv lll ~/public_html/$USER/catalog/test3.cfg;

#        dtype = 'MC' if 'MINIAODSIM' in dirname else 'Data'
#	 if 'Run2017' in dirname: continue

--> Processes must be included in 
PandaCore/Tools/python/processes/*.py

--> Define how many files to be ran per job
PandaAnalysis/T3/bin/task.py --build_only  --nfiles=25

--> Clean and submit
PandaAnalysis/T3/bin/task.py --clean
PandaAnalysis/T3/bin/task.py --submit --nfiles=25

--> Check status
PandaAnalysis/T3/bin/task.py --check

--> resubmit
PandaAnalysis/T3/bin/task.py --submit

--> Merge files once all jobs are done
PandaAnalysis/T3/merging/merge.py --cfg leptonic qqZZ                  

--> Git commands:
export PATH=/home/ceballos/bin:$PATH
git lfs clone -b master https://github.com/GuillelmoGomezCeballos/PandaAnalysis
cd PandaAnalysis
git remote add sid https://github.com/sidnarayanan/PandaAnalysis.git 
git fetch sid
git merge sid/master
git push -u origin master
rm .git/hooks/pre-push

--> Adding new variables in the Panda ntuple
./Flat/bin/generateTreeClass.py --cfg Flat/config/GeneralTree.cfg
