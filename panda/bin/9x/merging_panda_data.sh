#!/bin/sh

export PARAM="";

if [ $# != 1 ]; then
   echo "TOO FEW PARAMETERS"
   exit
fi

if [ $1 = "2016" ]; then

  hadd -f /data/t3home000/ceballos/panda/zllhbb/v4/data_overlaps_2016.root \
     /mnt/hadoop/scratch/bmaier/dylansVHSkims/2016/v_009_vhbb4/Double*.root \
     /mnt/hadoop/scratch/bmaier/dylansVHSkims/2016/v_009_vhbb4/SingleM*on*.root \
     /mnt/hadoop/scratch/bmaier/dylansVHSkims/2016/v_009_vhbb4/SingleE*on*.root \
     /mnt/hadoop/scratch/bmaier/dylansVHSkims/2016/v_009_vhbb4/MuonEG*.root
  root -q -l -b MitAnalysisRunII/panda/macros/9x/makeGoodRunSample.C+'("/data/t3home000/ceballos/panda/zllhbb/v4/data_overlaps_2016.root","/data/t3home000/ceballos/panda/zllhbb/v4/data_2016.root","PandaAnalysis/data/certs/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt")'

elif [ $1 = "2017" ]; then 

  hadd -f /data/t3home000/ceballos/panda/zllhbb/v4/data_overlaps_2017.root \
     /mnt/hadoop/scratch/bmaier/dylansVHSkims/2017/v_012_vhbb4/Double*.root \
     /mnt/hadoop/scratch/bmaier/dylansVHSkims/2017/v_012_vhbb4/SingleM*on*.root \
     /mnt/hadoop/scratch/bmaier/dylansVHSkims/2017/v_012_vhbb4/SingleE*on*.root \
     /mnt/hadoop/scratch/bmaier/dylansVHSkims/2017/v_012_vhbb4/MuonEG*.root
  root -q -l -b MitAnalysisRunII/panda/macros/9x/makeGoodRunSample.C+'("/data/t3home000/ceballos/panda/zllhbb/v4/data_overlaps_2017.root","/data/t3home000/ceballos/panda/zllhbb/v4/data_2017.root","PandaAnalysis/data/certs/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON_v1.txt")'


elif [ $1 = "2018" ]; then 

  hadd -f /data/t3home000/ceballos/panda/zllhbb/v4/data_overlaps_2018.root \
          /scratch5/bmaier/hbb/2018/v_013_v8/DoubleMuon.root \
          /scratch5/bmaier/hbb/2018/v_013_v8/EGamma.root \
          /scratch5/bmaier/hbb/2018/v_013_v8/MuonEG.root \
          /scratch5/bmaier/hbb/2018/v_013_v8/SingleMuon.root

  root -q -l -b MitAnalysisRunII/panda/macros/9x/makeGoodRunSample.C+'("/data/t3home000/ceballos/panda/zllhbb/v4/data_overlaps_2018.root","/data/t3home000/ceballos/panda/zllhbb/v4/data_2018.root","PandaAnalysis/data/certs/Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt")'

fi
