#!/bin/sh

root -q -b -l MitVHBBAnalysis/macros/zllhAnalysis.C+

nohup root -q -b -l MitVHBBAnalysis/macros/zllhAnalysis.C+'("test2016",kZllHSR,true,3,0,2016,0,1)' >& logzhbin0_kZllHSR2016 &
nohup root -q -b -l MitVHBBAnalysis/macros/zllhAnalysis.C+'("test2016",kZllHLightFlavorCR,true,3,0,2016,0,1)' >& logzhbin0_kZllHLightFlavorCR2016 &
nohup root -q -b -l MitVHBBAnalysis/macros/zllhAnalysis.C+'("test2016",kZllHHeavyFlavorCR,true,3,0,2016,0,1)' >& logzhbin0_kZllHHeavyFlavorCR2016 &
nohup root -q -b -l MitVHBBAnalysis/macros/zllhAnalysis.C+'("test2016",kZllH2TopCR,true,3,0,2016,0,1)' >& logzhbin0_kZllH2TopCR2016 &
#nohup root -q -b -l MitVHBBAnalysis/macros/zllhAnalysis.C+'("test2016",kZllHVZbbCR,true,3,0,2016,0,1)' >& logzhbin0_kZllHVZbbCR2016 &

nohup root -q -b -l MitVHBBAnalysis/macros/zllhAnalysis.C+'("test2016",kZllHSR,true,3,1,2016,0,1)' >& logzhbin1_kZllHSR2016 &
nohup root -q -b -l MitVHBBAnalysis/macros/zllhAnalysis.C+'("test2016",kZllHLightFlavorCR,true,3,1,2016,0,1)' >& logzhbin1_kZllHLightFlavorCR2016 &
nohup root -q -b -l MitVHBBAnalysis/macros/zllhAnalysis.C+'("test2016",kZllHHeavyFlavorCR,true,3,1,2016,0,1)' >& logzhbin1_kZllHHeavyFlavorCR2016 &
nohup root -q -b -l MitVHBBAnalysis/macros/zllhAnalysis.C+'("test2016",kZllH2TopCR,true,3,1,2016,0,1)' >& logzhbin1_kZllH2TopCR2016 &
#nohup root -q -b -l MitVHBBAnalysis/macros/zllhAnalysis.C+'("test2016",kZllHVZbbCR,true,3,1,2016,0,1)' >& logzhbin1_kZllHVZbbCR2016 &

nohup root -q -b -l MitVHBBAnalysis/macros/zllhAnalysis.C+'("test2016",kZllHFJSR,true,3,0,2016,0,1)' >& logzhbin0_kZllHFJSR2016 &
nohup root -q -b -l MitVHBBAnalysis/macros/zllhAnalysis.C+'("test2016",kZllHLightFlavorFJCR,true,3,0,2016,0,1)' >& logzhbin0_kZllHLightFlavorFJCR2016 &
nohup root -q -b -l MitVHBBAnalysis/macros/zllhAnalysis.C+'("test2016",kZllHHeavyFlavorFJCR,true,3,0,2016,0,1)' >& logzhbin0_kZllHHeavyFlavorFJCR2016 &
#nohup root -q -b -l MitVHBBAnalysis/macros/zllhAnalysis.C+'("test2016",kZllHTT1bFJCR,true,3,0,2016,0,1)' >& logzhbin0_kZllHTT1bFJCR2016 &
#nohup root -q -b -l MitVHBBAnalysis/macros/zllhAnalysis.C+'("test2016",kZllHTT2bFJCR,true,3,0,2016,0,1)' >& logzhbin0_kZllHTT2bFJCR2016 &
#nohup root -q -b -l MitVHBBAnalysis/macros/zllhAnalysis.C+'("test2016",kZllHVZbbFJCR,true,3,0,2016,0,1)' >& logzhbin0_kZllHVZbbFJCR2016 &

nohup root -q -b -l MitVHBBAnalysis/macros/zllhAnalysis.C+'("test2017",kZllHSR,true,3,0,2017,0,1)' >& logzhbin0_kZllHSR2017 &
nohup root -q -b -l MitVHBBAnalysis/macros/zllhAnalysis.C+'("test2017",kZllHLightFlavorCR,true,3,0,2017,0,1)' >& logzhbin0_kZllHLightFlavorCR2017 &
nohup root -q -b -l MitVHBBAnalysis/macros/zllhAnalysis.C+'("test2017",kZllHHeavyFlavorCR,true,3,0,2017,0,1)' >& logzhbin0_kZllHHeavyFlavorCR2017 &
nohup root -q -b -l MitVHBBAnalysis/macros/zllhAnalysis.C+'("test2017",kZllH2TopCR,true,3,0,2017,0,1)' >& logzhbin0_kZllH2TopCR2017 &
#nohup root -q -b -l MitVHBBAnalysis/macros/zllhAnalysis.C+'("test2017",kZllHVZbbCR,true,3,0,2017,0,1)' >& logzhbin0_kZllHVZbbCR2017 &

nohup root -q -b -l MitVHBBAnalysis/macros/zllhAnalysis.C+'("test2017",kZllHSR,true,3,1,2017,0,1)' >& logzhbin1_kZllHSR2017 &
nohup root -q -b -l MitVHBBAnalysis/macros/zllhAnalysis.C+'("test2017",kZllHLightFlavorCR,true,3,1,2017,0,1)' >& logzhbin1_kZllHLightFlavorCR2017 &
nohup root -q -b -l MitVHBBAnalysis/macros/zllhAnalysis.C+'("test2017",kZllHHeavyFlavorCR,true,3,1,2017,0,1)' >& logzhbin1_kZllHHeavyFlavorCR2017 &
nohup root -q -b -l MitVHBBAnalysis/macros/zllhAnalysis.C+'("test2017",kZllH2TopCR,true,3,1,2017,0,1)' >& logzhbin1_kZllH2TopCR2017 &
#nohup root -q -b -l MitVHBBAnalysis/macros/zllhAnalysis.C+'("test2017",kZllHVZbbCR,true,3,1,2017,0,1)' >& logzhbin1_kZllHVZbbCR2017 &

nohup root -q -b -l MitVHBBAnalysis/macros/zllhAnalysis.C+'("test2017",kZllHFJSR,true,3,0,2017,0,1)' >& logzhbin0_kZllHFJSR2017 &
nohup root -q -b -l MitVHBBAnalysis/macros/zllhAnalysis.C+'("test2017",kZllHLightFlavorFJCR,true,3,0,2017,0,1)' >& logzhbin0_kZllHLightFlavorFJCR2017 &
nohup root -q -b -l MitVHBBAnalysis/macros/zllhAnalysis.C+'("test2017",kZllHHeavyFlavorFJCR,true,3,0,2017,0,1)' >& logzhbin0_kZllHHeavyFlavorFJCR2017 &
#nohup root -q -b -l MitVHBBAnalysis/macros/zllhAnalysis.C+'("test2017",kZllHTT1bFJCR,true,3,0,2017,0,1)' >& logzhbin0_kZllHTT1bFJCR2017 &
#nohup root -q -b -l MitVHBBAnalysis/macros/zllhAnalysis.C+'("test2017",kZllHTT2bFJCR,true,3,0,2017,0,1)' >& logzhbin0_kZllHTT2bFJCR2017 &
#nohup root -q -b -l MitVHBBAnalysis/macros/zllhAnalysis.C+'("test2017",kZllHVZbbFJCR,true,3,0,2017,0,1)' >& logzhbin0_kZllHVZbbFJCR2017 &
