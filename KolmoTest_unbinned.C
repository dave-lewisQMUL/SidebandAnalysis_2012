#include "Riostream.h"
#include "TMath.h"
#include "TString.h"
#include "TFile.h"
#include "TChain.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "TH1D.h"


void KolmoTest_unbinned()
{

  TString mu_algo="";
  mu_algo = "muons";
  //mu_algo = "staco";
  
  TString period= "";

  period = "*";
  //period = "A";
  //period = "B";
  //period = "C";
  //period = "D";
  //period = "E";
  //period = "G";
  //period = "H";
  //period = "I";
  //period = "J";
  //period = "L";

  TChain *t_even = new TChain("T_mv_even");
  TChain *t_odd  = new TChain("T_mv_odd");

  TString dir = "/afs/cern.ch/work/c/calpigia/public/Bsmumu_NTP_2012/data_Bs/";
  t_even->Add(dir+"tmva_Bs_data12_"+period+"_"+mu_algo+".root");
  t_odd ->Add(dir+"tmva_Bs_data12_"+period+"_"+mu_algo+".root");

  TH1D *trigg_hist = new TH1D("trigg_hist","",3000,0.0,6.0);
  TH1D *l2starb_hist = new TH1D("l2starb_hist","",3000,0.0,6.0);

  //variables
  std::vector<string>* trigg = 0;
  Double_t mass = -999;
  Int_t RunNum = -999;
  //baseline selection
  bool evPassedMCP = false;
  bool evPassedKinMuons = false;
  bool evPassedKinBs = false;
  bool evPassedChi2Bs = false;
  //Additional cuts + variables
  Double_t a_2D = -999; 
  Double_t DR = -999;
  Double_t Lxy = -999;
  Double_t pTime = -999;
  Double_t iso7 = -999;
  Double_t logChi2z = -999;
  Double_t logChi2xy = -999;
  Double_t pT = -999; 
  Double_t DCA = -999;
  Double_t ZCA = -999;
  Double_t d0min = -999;
  Double_t d0max = -999;
  Double_t Plng_min = -999;
  Double_t Plng_max = -999;

  vector<Double_t> var_trigg;
  vector<Double_t> var_L2StarB;

  //even events

  cout << "Doing even events" << endl;
  
  t_even->SetBranchAddress("mass",&mass);
  t_even->SetBranchAddress("run_number",&RunNum);
  t_even->SetBranchAddress("EF_trigger_name",&trigg);
  t_even->SetBranchAddress("evPassedMCP",&evPassedMCP);
  t_even->SetBranchAddress("evPassedKinMuons",&evPassedKinMuons);
  t_even->SetBranchAddress("evPassedKinBs",&evPassedKinBs);
  t_even->SetBranchAddress("evPassedChi2Bs",&evPassedChi2Bs);

  t_even->SetBranchAddress("a_2D",&a_2D);
  t_even->SetBranchAddress("DR",&DR);
  t_even->SetBranchAddress("Lxy",&Lxy);
  t_even->SetBranchAddress("properTime_sig",&pTime);
  t_even->SetBranchAddress("iso7Chi26MedPt05",&iso7);
  t_even->SetBranchAddress("chi2PVSVLog1Dz",&logChi2z);
  t_even->SetBranchAddress("chi2PVSVLog2D",&logChi2xy);
  t_even->SetBranchAddress("pT",&pT);
  t_even->SetBranchAddress("closeDCA",&DCA);
  t_even->SetBranchAddress("closeZCA",&ZCA);
  t_even->SetBranchAddress("d0Min",&d0min);
  t_even->SetBranchAddress("d0Max",&d0max);
  t_even->SetBranchAddress("BrefTrPlngMax2D",&Plng_max);
  t_even->SetBranchAddress("BrefTrPlngMin2D",&Plng_min);
  
  for (int i=0; i<t_even->GetEntries(); i++)
    {
      t_even->GetEntry(i);
      if (mass>4766 && mass<5966)
	{
	  bool hasPassedTrigg = false;
	  bool hasPassedTrigg_L2StarB = false;
	  for (vector<string>::iterator iter=(*trigg).begin();iter!=(*trigg).end();iter++)
	    {
	      if (iter->compare("EF_2mu4T_Bmumu")==0)
		{
		  hasPassedTrigg = true;
		}
	      else if(iter->compare("EF_2mu4T_Bmumu_L2StarB")==0)
		{
		  hasPassedTrigg_L2StarB = true;
		}
	      
	      if (evPassedMCP && evPassedKinBs && evPassedKinMuons && evPassedChi2Bs)
		{
		  if (hasPassedTrigg && RunNum < 206955)
		    {
		      var_trigg.push_back(pTime);  //need to change this and below
		      trigg_hist->Fill(pTime);
		    }
		  else if (hasPassedTrigg_L2StarB && RunNum >= 206955)
		    {
		      var_L2StarB.push_back(pTime);  //change this
		      l2starb_hist->Fill(pTime);
		    }
		}
	    }
	}
    }
  	 	 
  cout << "Doing odd events" << endl;

  //odd events
  t_odd->SetBranchAddress("mass",&mass);
  t_odd->SetBranchAddress("run_number",&RunNum);
  t_odd->SetBranchAddress("EF_trigger_name",&trigg);
  t_odd->SetBranchAddress("evPassedMCP",&evPassedMCP);
  t_odd->SetBranchAddress("evPassedKinMuons",&evPassedKinMuons);
  t_odd->SetBranchAddress("evPassedKinBs",&evPassedKinBs);
  t_odd->SetBranchAddress("evPassedChi2Bs",&evPassedChi2Bs);
  //
  t_odd->SetBranchAddress("a_2D",&a_2D);
  t_odd->SetBranchAddress("DR",&DR);
  t_odd->SetBranchAddress("Lxy",&Lxy);
  t_odd->SetBranchAddress("properTime_sig",&pTime);
  t_odd->SetBranchAddress("iso7Chi26MedPt05",&iso7);
  t_odd->SetBranchAddress("chi2PVSVLog1Dz",&logChi2z);
  t_odd->SetBranchAddress("chi2PVSVLog2D",&logChi2xy);
  t_odd->SetBranchAddress("pT",&pT);
  t_odd->SetBranchAddress("closeDCA",&DCA);
  t_odd->SetBranchAddress("closeZCA",&ZCA);
  t_odd->SetBranchAddress("d0Min",&d0min);
  t_odd->SetBranchAddress("d0Max",&d0max);
  t_odd->SetBranchAddress("BrefTrPlngMax2D",&Plng_max);
  t_odd->SetBranchAddress("BrefTrPlngMin2D",&Plng_min);
   
  for (int i=0;i<t_odd->GetEntries();i++)
    {
      t_odd->GetEntry(i);
      if (mass>4766 && mass<5966)
	{
	  bool hasPassedTrigg = false;
	  bool hasPassedTrigg_L2StarB = false;
	  for (vector<string>::iterator iter=(*trigg).begin();iter!=(*trigg).end();iter++)
	    {
	      if (iter->compare("EF_2mu4T_Bmumu")==0)
		{
		  hasPassedTrigg = true;
		}
	      else if(iter->compare("EF_2mu4T_Bmumu_L2StarB")==0)
		{
		  hasPassedTrigg_L2StarB = true;
		}
	      
	      if (evPassedMCP && evPassedKinBs && evPassedKinMuons && evPassedChi2Bs)
		{
		  if (hasPassedTrigg && RunNum < 206955)
		    {
		      var_trigg.push_back(pTime);  //change this
		      trigg_hist->Fill(pTime);
		    }
		  else if (hasPassedTrigg_L2StarB && RunNum >= 206955)
		    {
		      var_L2StarB.push_back(pTime);  //change this. Don't forget to change below!
		      l2starb_hist->Fill(pTime);
		    }
		}
	    }
	}
    }
  
  //

  std::sort(var_trigg.begin(),var_trigg.end());
  std::sort(var_L2StarB.begin(),var_L2StarB.end());
  // check it sorted correctly
  cout << "[0]: " << var_trigg.at(0) << " " << var_L2StarB.at(0) << endl;
  cout << "[100]: " << var_trigg.at(100) << " " << var_L2StarB.at(100) << endl;
  cout << "[end]: " << var_trigg.at(var_trigg.size()-1) << " " << var_L2StarB.at(var_L2StarB.size()-1) << endl;

  Double_t* array_trigg = new Double_t[var_trigg.size()];
  Double_t* array_L2StarB = new Double_t[var_L2StarB.size()];

  for (int i=0;i<var_trigg.size();i++)
    {
      array_trigg[i]=var_trigg.at(i)/var_trigg.size();
    }
  for (int i=0;i<var_L2StarB.size();i++)
    {
      array_L2StarB[i]=var_L2StarB.at(i)/var_L2StarB.size();
    }
  
  Double_t kolmo_result = TMath::KolmogorovTest(var_trigg.size(),array_trigg,
						var_L2StarB.size(),array_L2StarB,"D");
  //
  delete array_trigg;
  delete array_L2StarB;
  //output result to results file
  ofstream results_file;
  results_file.open("kolmo_results.txt",ios::app);
  results_file << "pTime " << kolmo_result << " \n";            //also change here 
  results_file.close();
  cout << "Kolmogorov test result: " << kolmo_result << endl;

  //Binned test
  //  trigg_hist->Scale(1/trigg_hist->GetEntries());
  //  l2starb_hist->Scale(1/l2starb_hist->GetEntries());
  kolmo_result = trigg_hist->KolmogorovTest(l2starb_hist,"D");
  cout << "binned test result: " << kolmo_result << endl;

}
