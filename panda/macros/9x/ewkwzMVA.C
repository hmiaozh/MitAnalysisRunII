#include <TROOT.h>
#include <TMVA/DataLoader.h>
#include <TMVA/Factory.h>
#include <TMVA/Types.h>
#include <TFile.h>
#include <TCut.h>
#include <TTree.h>
#include <TString.h>
#include <TStyle.h>

#include "MitAnalysisRunII/panda/macros/9x/common.h"

void ewkwzMVA(
  TString inputFileName, 
  TString extraString="v0",
  bool useGaussDeco=false,
  TString variableSet = "orthodox" // orthodox | fullResolved | everything
) {
  gROOT->ProcessLine("TMVA::gConfig().GetVariablePlotting().fMaxNumOfAllowedVariablesForScatterPlots = 50");
  TFile *output_file;
  TMVA::Factory *factory;
  TString trainTreeEventSplitStr="(eventNum % 10)<3";
  TString testTreeEventSplitStr="(eventNum % 10)>=3";

  // Determine the input trees
  TFile *inputFile = TFile::Open(inputFileName,"READ");
  TTree *mvaTree = (TTree*)inputFile->Get("mvatree");
  
  // Initialize the factory
  output_file=TFile::Open(Form("MVA_%s.root",extraString.Data()), "RECREATE");
  //factory = new TMVA::Factory("bdt", output_file, "!V:!Silent:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Multiclass");
  TString factoryOptions="!V:!Silent:DrawProgressBar";
  //TString factoryOptions="!V:!Silent:!DrawProgressBar";
  factoryOptions+=":AnalysisType=Classification";
  if(useGaussDeco)  factoryOptions += ":Transformations=G,D";
  //else              factoryOptions += ":Transformations=I";
  factory = new TMVA::Factory("bdt", output_file, factoryOptions);
  TMVA::DataLoader *dataloader=new TMVA::DataLoader("MitEWKWZAnalysis");

  TCut cutTrainSignal = Form("%s && category==%d",trainTreeEventSplitStr.Data(),kPlotEWKWZ);
  TCut cutTrainBkg    = Form("%s && category==%d",trainTreeEventSplitStr.Data(),kPlotWZ);
  TCut cutTestSignal  = Form("%s && category==%d",testTreeEventSplitStr.Data(), kPlotEWKWZ);
  TCut cutTestBkg     = Form("%s && category==%d",testTreeEventSplitStr.Data(), kPlotWZ);
  dataloader->AddTree(mvaTree, "Background", 1.0, cutTrainBkg	, "train");
  dataloader->AddTree(mvaTree, "Signal"    , 1.0, cutTrainSignal, "train");
  dataloader->AddTree(mvaTree, "Background", 1.0, cutTestBkg   , "test");
  dataloader->AddTree(mvaTree, "Signal"    , 1.0, cutTestSignal, "test");
  dataloader->SetWeightExpression("abs(weight)", "Signal");
  dataloader->SetWeightExpression("abs(weight)", "Background");
  
  TCut preselectionCut;
  dataloader->AddVariable("mvamjj"    , "mvamjj"    , "", 'F');
  dataloader->AddVariable("mvadeta"   , "mvadeta"   , "", 'F');
  dataloader->AddVariable("mvadphi"   , "mvadphi"   , "", 'F');
  dataloader->AddVariable("mvajetpt1" , "mvajetpt1" , "", 'F');
  dataloader->AddVariable("mvajetpt2" , "mvajetpt2" , "", 'F');
  dataloader->AddVariable("mvajeteta1", "mvajeteta1", "", 'F');
  //dataloader->AddVariable("mvajeteta2", "mvajeteta2", "", 'F');
  //dataloader->AddVariable("mvanjets"  , "mvanjets"  , "", 'F');
  //dataloader->AddVariable("mvaWpt"    , "mvaWpt"    , "", 'F');
  //dataloader->AddVariable("mvaZpt"    , "mvaZpt"    , "", 'F');
  //dataloader->AddVariable("mvaWZmt"   , "mvaWZmt"   , "", 'F');
  dataloader->AddVariable("mvaWlZdeta", "mvaWlZdeta", "", 'F');
  dataloader->AddVariable("mvazstar"  , "mvazstar"  , "", 'F');
  dataloader->AddVariable("mvazep1"   , "mvazep1"   , "", 'F');
  dataloader->AddVariable("mvazep2"   , "mvazep2"   , "", 'F');
  dataloader->AddVariable("mvazep3"   , "mvazep3"   , "", 'F');
  //dataloader->AddVariable("mvamaxzep" , "mvamaxzep" , "", 'F');
  dataloader->AddVariable("mvaj1Zdr"  , "mvaj1Zdr"  , "", 'F');
  //dataloader->AddVariable("mvaj2Zdr"  , "mvaj2Zdr"  , "", 'F');
  dataloader->AddVariable("mvapttotN" , "mvapttotN" , "", 'F');
  //dataloader->AddVariable("mvapttot"  , "mvapttot"  , "", 'F');

  TString prepareOptions="NormMode=None";
    prepareOptions+=":SplitMode=Block"; // use e.g. all events selected by trainTreeEventSplitStr for training
    prepareOptions+=":MixMode=Random";
  dataloader->PrepareTrainingAndTestTree("", prepareOptions);

  TString hyperparameters;

  hyperparameters=
  "!H:!V:NTrees=800:BoostType=Grad:MinNodeSize=5%:NegWeightTreatment=IgnoreNegWeightsInTraining:Shrinkage=0.10:UseBaggedBoost:GradBaggingFraction=0.5:nCuts=10000:MaxDepth=2";
  factory->BookMethod(dataloader, TMVA::Types::kBDT, Form("BDTG_%s",extraString.Data()), hyperparameters);

  bool moreMVAs = false;
  if(moreMVAs){
  hyperparameters=
  "!H:!V:BoostType=AdaBoost:MinNodeSize=5%:NegWeightTreatment=IgnoreNegWeightsInTraining:SeparationType=MisClassificationError:NTrees=500:MaxDepth=3:AdaBoostBeta=0.12:nCuts=10000";
  factory->BookMethod(dataloader, TMVA::Types::kBDT, Form("BDTA_%s",extraString.Data()), hyperparameters);

  hyperparameters=
  "!H:!V:NTrees=500:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=1000:PruneMethod=CostComplexity:PruneStrength=50:VarTransform=Decorrelate";
  factory->BookMethod(dataloader, TMVA::Types::kBDT, Form("BDTD_%s",extraString.Data()), hyperparameters);

  hyperparameters=
  "!H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:NAvEvtPerBin=40:VarTransform=Decorrelate";
  factory->BookMethod(dataloader, TMVA::Types::kLikelihood, Form("LikelihoodD_%s",extraString.Data()), hyperparameters);

  hyperparameters=
  "H:nkNN=31:ScaleFrac=0.8:SigmaFact=1.0:Kernel=Gaus:UseKernel=F:UseWeight=T:!Trim";
  factory->BookMethod(dataloader, TMVA::Types::kKNN, Form("KNN_%s",extraString.Data()), hyperparameters);

  hyperparameters=
  "H:!V:Fisher:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=40:NsmoothMVAPdf=10";
  factory->BookMethod(dataloader, TMVA::Types::kFisher, Form("Fisher_%s",extraString.Data()), hyperparameters);

  hyperparameters=
  "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:!UseRegulator";
  factory->BookMethod(dataloader, TMVA::Types::kMLP, Form("MLP_%s",extraString.Data()), hyperparameters);
  }

  factory->TrainAllMethods();
  factory->TestAllMethods();
  factory->EvaluateAllMethods();
  output_file->Close();
}
