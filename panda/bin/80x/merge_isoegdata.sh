#!/bin/sh

nohup root -q -l -b MitAnalysisRunII/panda/macros/9x/makeGoodRunSample.C+'("${PANDA_FLATDIR}/data.root","${PANDA_FLATDIR}/data_IsoEG22_EG30_14p40ifb.root","MitAnalysisRunII/json/80x/IsoEG22_EG30_14p40ifb.json")' >& log_IsoEG22_EG30_14p40ifb &
nohup root -q -l -b MitAnalysisRunII/panda/macros/9x/makeGoodRunSample.C+'("${PANDA_FLATDIR}/data.root","${PANDA_FLATDIR}/data_IsoEG22_EG40_05p86ifb.root","MitAnalysisRunII/json/80x/IsoEG22_EG40_05p86ifb.json")' >& log_IsoEG22_EG40_05p86ifb &
nohup root -q -l -b MitAnalysisRunII/panda/macros/9x/makeGoodRunSample.C+'("${PANDA_FLATDIR}/data.root","${PANDA_FLATDIR}/data_IsoEG24_EG30_05p88ifb.root","MitAnalysisRunII/json/80x/IsoEG24_EG30_05p88ifb.json")' >& log_IsoEG24_EG30_05p88ifb &
nohup root -q -l -b MitAnalysisRunII/panda/macros/9x/makeGoodRunSample.C+'("${PANDA_FLATDIR}/data.root","${PANDA_FLATDIR}/data_IsoEG26_EG30_05p22ifb.root","MitAnalysisRunII/json/80x/IsoEG26_EG30_05p22ifb.json")' >& log_IsoEG26_EG30_05p22ifb &
nohup root -q -l -b MitAnalysisRunII/panda/macros/9x/makeGoodRunSample.C+'("${PANDA_FLATDIR}/data.root","${PANDA_FLATDIR}/data_IsoEG28_EG32_02p48ifb.root","MitAnalysisRunII/json/80x/IsoEG28_EG32_02p48ifb.json")' >& log_IsoEG28_EG32_02p48ifb &
nohup root -q -l -b MitAnalysisRunII/panda/macros/9x/makeGoodRunSample.C+'("${PANDA_FLATDIR}/data.root","${PANDA_FLATDIR}/data_IsoEG30_EG34_01p89ifb.root","MitAnalysisRunII/json/80x/IsoEG30_EG34_01p89ifb.json")' >& log_IsoEG30_EG34_01p89ifb &
nohup root -q -l -b MitAnalysisRunII/panda/macros/9x/makeGoodRunSample.C+'("${PANDA_FLATDIR}/data.root","${PANDA_FLATDIR}/data_IsoEG32_EG36_00p19ifb.root","MitAnalysisRunII/json/80x/IsoEG32_EG36_00p19ifb.json")' >& log_IsoEG32_EG36_00p19ifb &
nohup root -q -l -b MitAnalysisRunII/panda/macros/9x/makeGoodRunSample.C+'("${PANDA_FLATDIR}/data.root","${PANDA_FLATDIR}/data_IsoEG34_EG38_00p00ifb.root","MitAnalysisRunII/json/80x/IsoEG34_EG38_00p00ifb.json")' >& log_IsoEG34_EG38_00p00ifb &
