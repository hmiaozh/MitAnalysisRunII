!/bin/sh

hadd /data/t3home000/ceballos/panda/v_vbfg_2017_0/data_overlaps.root \
   /data/t3home000/bmaier/darkg/2017/vbfg_v_012_v3/MET.root \
   /data/t3home000/bmaier/darkg/2017/vbfg_v_012_v3/SinglePhoton.root

root -q -l -b MitAnalysisRunII/panda/macros/9x/makeGoodRunSample.C+'("/data/t3home000/ceballos/panda/v_vbfg_2017_0/data_overlaps.root","/data/t3home000/ceballos/panda/v_vbfg_2017_0/data.root","PandaAnalysis/data/certs/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON_v1.txt")';
