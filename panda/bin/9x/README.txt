--> setup
source MitAnalysisRunII/panda/bin/9x/setup_leptonic.sh

--> run macro 
PandaAnalysis/T3/inputs/skim_lep_tmpl.py

--> Datasets to be included
PandaAnalysis/T3/bin/catalogT2Prod.py --cfg leptonic --outfile ~/public_html/$USER/catalog/test.cfg --catalog ~cmsprod/catalog/t2mit/pandaf/010 --include SingleElectron SingleMuon DoubleEG DoubleMuon MuonEG EGamma ZJets_nlo ZJets_lo --exclude EWK

# standard
PandaAnalysis/T3/bin/catalogT2Prod.py --cfg leptonic --outfile ~/public_html/$USER/catalog/test.cfg --catalog ~cmsprod/catalog/t2mit/pandaf/010 \
--include SingleElectron SingleMuon DoubleEG DoubleMuon MuonEG EGamma ZZ WZ WW DYJetsToLL_M-50_Tune DYJetsToLL_M-10to50_Tune tZq GluGluH VBFH VBF_H ttHToNonbb VHToNonbb \
TTG TTZ TTW ST_tW TT WGstarTo WGToLNuG ZGTo2LG JetsToLL DYJetsToTauTau NNPDF30_13TeV-powheg MET WJetsToLNu WpWpJJ HToBB \
--exclude ZpWW_med JetsToLL_M-50_HT NNPDF30_13TeV-powheg DYJetsToLL_Zpt-100to200 DYJetsToLL_Zpt-200toInf

# fakes
PandaAnalysis/T3/bin/catalogT2Prod.py --cfg leptonic --outfile ~/public_html/$USER/catalog/test3.cfg --catalog ~cmsprod/catalog/t2mit/pandaf/010 \
--include SingleElectron SingleMuon DoubleEG DoubleMuon MuonEG EGamma ZZ WZ WW DYJetsToLL_M-50_Tune DYJetsToLL_M-10to50_Tune tZq \
GluGluH VBFH VBF_H ttHToNonbb VHToNonbb TTG TTZ TTW ST_tW  WGstarTo WGToLNuG ZGTo2LG  WJetsToLNu TT \
--exclude ZpWW_med JetsToLL_M-50_HT DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM NNPDF30_13TeV-powheg DYJetsToLL_Zpt-100to200 DYJetsToLL_Zpt-200toInf WW_DoubleScattering 

#        dtype = 'MC' if 'MINIAODSIM' in dirname else 'Data'
#	 if 'Run2017' in dirname: continue

--> Processes must be included in 
PandaCore/Tools/python/processes/*.py

--> Define how many files to be ran per job
PandaAnalysis/T3/bin/task.py --build_only  --nfiles=25

--> Submit
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
