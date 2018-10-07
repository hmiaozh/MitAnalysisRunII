void testYields(int year=2017, TString selectName="HeavyFlavorCR_ZptBin2"){
  TString inputDirAll;
  TString type1="plots_ZmmH" + selectName;
  TString type2="plots_ZeeH" + selectName;
  vector<TString> samples;
  if(year==2016){
    inputDirAll = "MitVHBBAnalysis/datacards/zhbb_frozen/testcondor2016";
    samples.push_back("LeptonPDSalad2016"        );
    samples.push_back("WZTo2L2Q"                 );	  
    samples.push_back("ZZTo2L2Q"                 );	  
    samples.push_back("WWTo2L2Nu"                );
    samples.push_back("SingleTop_tW"             );	  
    samples.push_back("SingleTop_tbarW"          );	  
    samples.push_back("TTTo2L2Nu"                );	  
    samples.push_back("ZJets_ht100to200"         );
    samples.push_back("ZJets_ht200to400"         );	  
    samples.push_back("ZJets_ht400to600"         );	  
    samples.push_back("ZJets_ht600to800"         );	  
    samples.push_back("ZJets_ht800to1200"        );	  
    samples.push_back("ZJets_ht1200to2500"       );	  
    samples.push_back("ZJets_ht2500toinf"        );	  
    samples.push_back("ZJets_pt50to100"          );	  
    samples.push_back("ZJets_pt100to250"         );	  
    samples.push_back("ZJets_pt250to400"         );	  
    samples.push_back("ZJets_pt400to650"         );	  
    samples.push_back("ZJets_pt650toinf"         );	  
    samples.push_back("ZJets_bHadrons_incl"      );	  
    samples.push_back("ZJets_bHadrons_pt100to200");	  
    samples.push_back("ZJets_bHadrons_pt200toinf");	  
    samples.push_back("ZJets_bQuarks_incl"       );	  
    samples.push_back("ZJets_bQuarks_pt100to200" );	  
    samples.push_back("ZJets_bQuarks_pt200toinf" );	  
    samples.push_back("ZJets_m10"                );
    samples.push_back("ZllHbb_mH125"             );	  
    samples.push_back("ggZllHbb_mH125"           );	  
  } 
  else if(year==2017){
    inputDirAll = "MitVHBBAnalysis/datacards/zhbb/testcondor2017";
    samples.push_back("LeptonPDSalad2017"	 );
    samples.push_back("WZTo2L2Q"		 );
    samples.push_back("ZZTo2L2Q"		 );
    samples.push_back("WWTo2L2Nu_CP5"	         );
    samples.push_back("TTTo2L2Nu_CP5"	         );
    samples.push_back("SingleTop_tW_CP5"         );
    samples.push_back("SingleTop_tbarW_CP5"      ); 
    samples.push_back("ZJets_bQuarks_incl"       );
    samples.push_back("ZJets_bHadrons_pt100to200");
    samples.push_back("ZJets_bHadrons_pt200toinf");
    samples.push_back("ZJets_ht100to200_CP5"     );
    samples.push_back("ZJets_ht200to400_CP5"     );
    samples.push_back("ZJets_ht400to600_CP5"     );
    samples.push_back("ZJets_ht600to800_CP5"     );
    samples.push_back("ZJets_ht800to1200_CP5"    );
    samples.push_back("ZJets_ht1200to2500_CP5"   );
    samples.push_back("ZJets_ht2500toinf_CP5"    );
    samples.push_back("ZJets_m4_ht70to100_CP5"   );
    samples.push_back("ZJets_m4_ht100to200_CP5"  );
    samples.push_back("ZJets_m4_ht200to400_CP5"  );
    samples.push_back("ZJets_m4_ht400to600_CP5"  );
    samples.push_back("ZJets_m4_ht600toinf_CP5"  );
    samples.push_back("ZllHbb_mH125"	         );
    samples.push_back("ggZllHbb_mH125"	         );
  }
  else {
    return;
  }
  TString inputDir = inputDirAll + "/split";

  double sum1[14],sum2[14];
  for(int i=i; i<14; i++) {sum1[i]=0;sum2[i]=0;}
  for(unsigned n=0; n<samples.size(); n++) {
    TH1F *histos1[14],*histos2[14];    
    TString inputFileName1 = Form("%s/%s_%s.root",inputDir.Data(),type1.Data(),samples[n].Data());
    TString inputFileName2 = Form("%s/%s_%s.root",inputDir.Data(),type2.Data(),samples[n].Data());
    printf("*****%s*****\n",samples[n].Data());
    TFile *inputFile1 = TFile::Open(inputFileName1,"READ"); assert(inputFile1);
    TFile *inputFile2 = TFile::Open(inputFileName2,"READ"); assert(inputFile2);
    for(int i=0; i<14; i++){
       histos1[i]=(TH1F*)inputFile1->Get(Form("%s/histo%d","bjet2btag",i));
       histos2[i]=(TH1F*)inputFile2->Get(Form("%s/histo%d","bjet2btag",i));
       sum1[i] = sum1[i] + histos1[i]->GetSumOfWeights();
       sum2[i] = sum2[i] + histos2[i]->GetSumOfWeights();
       if(histos1[i]->GetSumOfWeights() > 0 && histos2[i]->GetSumOfWeights() > 0){
         printf("%2d: %7.2f /%7.2f = %5.3f\n",i,histos1[i]->GetSumOfWeights(),histos2[i]->GetSumOfWeights(),
	 histos1[i]->GetSumOfWeights()/histos2[i]->GetSumOfWeights());
       }
       else if(histos1[i]->GetSumOfWeights() > 0  && histos2[i]->GetSumOfWeights() == 0){
         printf("warning1 %2d: %7.2f\n",i,histos1[i]->GetSumOfWeights());
       }
       else if(histos1[i]->GetSumOfWeights() == 0 && histos2[i]->GetSumOfWeights()  > 0){
         printf("warning2 %2d: %7.2f\n",i,histos2[i]->GetSumOfWeights());
       }
    }
  }
  {
    TH1F *histos1[14],*histos2[14];    
    TString inputFileName1 = Form("%s/%s.root",inputDirAll.Data(),type1.Data());
    TString inputFileName2 = Form("%s/%s.root",inputDirAll.Data(),type2.Data());
    printf("*****All*****\n");
    TFile *inputFile1 = TFile::Open(inputFileName1,"READ"); assert(inputFile1);
    TFile *inputFile2 = TFile::Open(inputFileName2,"READ"); assert(inputFile2);
    for(int i=0; i<14; i++){
       histos1[i]=(TH1F*)inputFile1->Get(Form("%s/histo%d","bjet2btag",i));
       histos2[i]=(TH1F*)inputFile2->Get(Form("%s/histo%d","bjet2btag",i));
       if(histos1[i]->GetSumOfWeights() > 0 && histos2[i]->GetSumOfWeights() > 0){
         printf("%2d: %7.2f /%7.2f = %5.3f | %7.2f /%7.2f\n",i,histos1[i]->GetSumOfWeights(),histos2[i]->GetSumOfWeights(),
	 histos1[i]->GetSumOfWeights()/histos2[i]->GetSumOfWeights(),sum1[i],sum2[i]);
       }
       else if(histos1[i]->GetSumOfWeights() > 0  && histos2[i]->GetSumOfWeights() == 0){
         printf("warning1 %2d: %7.2f\n",i,histos1[i]->GetSumOfWeights());
       }
       else if(histos1[i]->GetSumOfWeights() == 0 && histos2[i]->GetSumOfWeights()  > 0){
         printf("warning2 %2d: %7.2f\n",i,histos2[i]->GetSumOfWeights());
       }
    }
  }
}
