#!/bin/sh

./1_convert.sh 1 ZH_boosted ZllHFJSR_mvaTree 2016
./1_convert.sh 1 ZH_boosted ZllHFJSR_mvaTree 2017

./1_convert.sh 1 ZH_resolved ZllHSR_mvaTree_ZptBin0 2016
./1_convert.sh 1 ZH_resolved ZllHSR_mvaTree_ZptBin0 2017

./1_convert.sh 1 ZH_resolved ZllHSR_mvaTree_ZptBin1 2016
./1_convert.sh 1 ZH_resolved ZllHSR_mvaTree_ZptBin1 2017

./1_convert.sh 1 ZH_resolved ZllHSR_mvaTree_ZptBin2 2016
./1_convert.sh 1 ZH_resolved ZllHSR_mvaTree_ZptBin2 2017

./1_convert.sh 2 WH_boosted WHFJSR_mvaTree 2016
./1_convert.sh 2 WH_boosted WHFJSR_mvaTree 2017

./1_convert.sh 2 WH_resolved WHSR_mvaTree 2016
./1_convert.sh 2 WH_resolved WHSR_mvaTree 2017
