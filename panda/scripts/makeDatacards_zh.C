
//bool isVZbbAna = true, applyBtagPtEta = false;
bool isVZbbAna = false, applyBtagPtEta = false;

gSystem->Load("libPandaAnalysisFlat.so");
.L MitVHBBAnalysis/macros/zllhAnalysis.C+g
datacardsFromHistograms("zhbb/testcondor2016", kZllHSR,             true, 3, 0, 2016, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2016", kZllHLightFlavorCR,  true, 3, 0, 2016, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2016", kZllHHeavyFlavorCR , true, 3, 0, 2016, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2016", kZllH2TopCR,         true, 3, 0, 2016, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2016", kZllHVZbbCR,         true, 3, 0, 2016, isVZbbAna, applyBtagPtEta);

datacardsFromHistograms("zhbb/testcondor2016", kZllHSR,             true, 3, 1, 2016, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2016", kZllHLightFlavorCR,  true, 3, 1, 2016, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2016", kZllHHeavyFlavorCR , true, 3, 1, 2016, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2016", kZllH2TopCR,         true, 3, 1, 2016, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2016", kZllHVZbbCR,         true, 3, 1, 2016, isVZbbAna, applyBtagPtEta);

datacardsFromHistograms("zhbb/testcondor2016", kZllHSR,             true, 3, 2, 2016, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2016", kZllHLightFlavorCR,  true, 3, 2, 2016, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2016", kZllHHeavyFlavorCR , true, 3, 2, 2016, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2016", kZllH2TopCR,         true, 3, 2, 2016, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2016", kZllHVZbbCR,         true, 3, 2, 2016, isVZbbAna, applyBtagPtEta);

datacardsFromHistograms("zhbb/testcondor2016", kZllHFJSR,           true, 3, 0, 2016, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2016", kZllHLightFlavorFJCR,true, 3, 0, 2016, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2016", kZllHHeavyFlavorFJCR,true, 3, 0, 2016, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2016", kZllHVZbbFJCR,       true, 3, 0, 2016, isVZbbAna, applyBtagPtEta);

datacardsFromHistograms("zhbb/testcondor2017", kZllHSR,             true, 3, 0, 2017, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2017", kZllHLightFlavorCR,  true, 3, 0, 2017, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2017", kZllHHeavyFlavorCR , true, 3, 0, 2017, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2017", kZllH2TopCR,         true, 3, 0, 2017, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2017", kZllHVZbbCR,         true, 3, 0, 2017, isVZbbAna, applyBtagPtEta);

datacardsFromHistograms("zhbb/testcondor2017", kZllHSR,             true, 3, 1, 2017, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2017", kZllHLightFlavorCR,  true, 3, 1, 2017, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2017", kZllHHeavyFlavorCR , true, 3, 1, 2017, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2017", kZllH2TopCR,         true, 3, 1, 2017, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2017", kZllHVZbbCR,         true, 3, 1, 2017, isVZbbAna, applyBtagPtEta);

datacardsFromHistograms("zhbb/testcondor2017", kZllHSR,             true, 3, 2, 2017, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2017", kZllHLightFlavorCR,  true, 3, 2, 2017, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2017", kZllHHeavyFlavorCR , true, 3, 2, 2017, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2017", kZllH2TopCR,         true, 3, 2, 2017, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2017", kZllHVZbbCR,         true, 3, 2, 2017, isVZbbAna, applyBtagPtEta);

datacardsFromHistograms("zhbb/testcondor2017", kZllHFJSR,           true, 3, 0, 2017, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2017", kZllHLightFlavorFJCR,true, 3, 0, 2017, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2017", kZllHHeavyFlavorFJCR,true, 3, 0, 2017, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2017", kZllHVZbbFJCR,       true, 3, 0, 2017, isVZbbAna, applyBtagPtEta);

datacardsFromHistograms("zhbb/testcondor2018", kZllHSR,             true, 3, 0, 2018, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2018", kZllHLightFlavorCR,  true, 3, 0, 2018, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2018", kZllHHeavyFlavorCR , true, 3, 0, 2018, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2018", kZllH2TopCR,         true, 3, 0, 2018, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2018", kZllHVZbbCR,         true, 3, 0, 2018, isVZbbAna, applyBtagPtEta);

datacardsFromHistograms("zhbb/testcondor2018", kZllHSR,             true, 3, 1, 2018, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2018", kZllHLightFlavorCR,  true, 3, 1, 2018, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2018", kZllHHeavyFlavorCR , true, 3, 1, 2018, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2018", kZllH2TopCR,         true, 3, 1, 2018, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2018", kZllHVZbbCR,         true, 3, 1, 2018, isVZbbAna, applyBtagPtEta);

datacardsFromHistograms("zhbb/testcondor2018", kZllHSR,             true, 3, 2, 2018, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2018", kZllHLightFlavorCR,  true, 3, 2, 2018, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2018", kZllHHeavyFlavorCR , true, 3, 2, 2018, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2018", kZllH2TopCR,         true, 3, 2, 2018, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2018", kZllHVZbbCR,         true, 3, 2, 2018, isVZbbAna, applyBtagPtEta);

datacardsFromHistograms("zhbb/testcondor2018", kZllHFJSR,           true, 3, 0, 2018, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2018", kZllHLightFlavorFJCR,true, 3, 0, 2018, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2018", kZllHHeavyFlavorFJCR,true, 3, 0, 2018, isVZbbAna, applyBtagPtEta);
datacardsFromHistograms("zhbb/testcondor2018", kZllHVZbbFJCR,       true, 3, 0, 2018, isVZbbAna, applyBtagPtEta);
