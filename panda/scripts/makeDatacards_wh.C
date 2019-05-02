{
bool applyBtagPtEta = false;

gSystem->Load("libPandaAnalysisFlat.so");
.L MitVHBBAnalysis/macros/whAnalysis.C+g

datacardsFromHistograms("whbb/testcondor2016", kWHSR,             true, 3, 2016, applyBtagPtEta);
datacardsFromHistograms("whbb/testcondor2016", kWHLightFlavorCR,  true, 3, 2016, applyBtagPtEta);
datacardsFromHistograms("whbb/testcondor2016", kWHHeavyFlavorCR,  true, 3, 2016, applyBtagPtEta);
datacardsFromHistograms("whbb/testcondor2016", kWH2TopCR,         true, 3, 2016, applyBtagPtEta);

datacardsFromHistograms("whbb/testcondor2016", kWHFJSR,           true, 3, 2016, applyBtagPtEta);
datacardsFromHistograms("whbb/testcondor2016", kWHLightFlavorFJCR,true, 3, 2016, applyBtagPtEta);
datacardsFromHistograms("whbb/testcondor2016", kWHHeavyFlavorFJCR,true, 3, 2016, applyBtagPtEta);
datacardsFromHistograms("whbb/testcondor2016", kWHTT2bFJCR,       true, 3, 2016, applyBtagPtEta);

datacardsFromHistograms("whbb/testcondor2017", kWHSR,             true, 3, 2017, applyBtagPtEta);
datacardsFromHistograms("whbb/testcondor2017", kWHLightFlavorCR,  true, 3, 2017, applyBtagPtEta);
datacardsFromHistograms("whbb/testcondor2017", kWHHeavyFlavorCR,  true, 3, 2017, applyBtagPtEta);
datacardsFromHistograms("whbb/testcondor2017", kWH2TopCR,         true, 3, 2017, applyBtagPtEta);

datacardsFromHistograms("whbb/testcondor2017", kWHFJSR,           true, 3, 2017, applyBtagPtEta);
datacardsFromHistograms("whbb/testcondor2017", kWHLightFlavorFJCR,true, 3, 2017, applyBtagPtEta);
datacardsFromHistograms("whbb/testcondor2017", kWHHeavyFlavorFJCR,true, 3, 2017, applyBtagPtEta);
datacardsFromHistograms("whbb/testcondor2017", kWHTT2bFJCR,       true, 3, 2017, applyBtagPtEta);

datacardsFromHistograms("whbb/testcondor2018", kWHSR,             true, 3, 2018, applyBtagPtEta);
datacardsFromHistograms("whbb/testcondor2018", kWHLightFlavorCR,  true, 3, 2018, applyBtagPtEta);
datacardsFromHistograms("whbb/testcondor2018", kWHHeavyFlavorCR,  true, 3, 2018, applyBtagPtEta);
datacardsFromHistograms("whbb/testcondor2018", kWH2TopCR,         true, 3, 2018, applyBtagPtEta);

datacardsFromHistograms("whbb/testcondor2018", kWHFJSR,           true, 3, 2018, applyBtagPtEta);
datacardsFromHistograms("whbb/testcondor2018", kWHLightFlavorFJCR,true, 3, 2018, applyBtagPtEta);
datacardsFromHistograms("whbb/testcondor2018", kWHHeavyFlavorFJCR,true, 3, 2018, applyBtagPtEta);
datacardsFromHistograms("whbb/testcondor2018", kWHTT2bFJCR,       true, 3, 2018, applyBtagPtEta);
}
