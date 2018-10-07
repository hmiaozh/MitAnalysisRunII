#!/bin/sh

voms-proxy-init --valid 168:00 -voms cms;

for datasetName in `cat list_of_datasets.txt`; do
  export theFiles=list_of_files_$RANDOM.txt;
  dasgoclient --query "file dataset=${datasetName}" | grep "store/mc" | head -10 > ${theFiles};
  for fileName in `cat ${theFiles}`; do
    cmsRun ana.py inputFiles=${fileName} maxEvents=-1;
  done
  rm -f ${theFiles};
done
