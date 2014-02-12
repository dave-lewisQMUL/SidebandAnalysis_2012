#include "Riostream.h"
#include "TString.h"
#include "TChain.h"
#include "TH1D.h"
#include "TFile.h"
#include "TCanvas.h"

#include <stdio.h>
#include <vector>
#include <cmath>

void macro_sidebands(){

  TString mu_algo="";
  // ** NOTE: "mu_algo" variable allows to select root files processed with a certain muon algorithm.
  //                    -- select "muons" for Muons algorithm files
  //                    -- select "staco" for Staco algorithm files
  //
  mu_algo = "muons";
  //mu_algo = "staco";
  
  TString period= "";
  // ** NOTE: "period" variable allows to select the root file containing data belonging to a certain 
  //                   data taking period, A, B, ...
  //                   if period = "*" --> the macro runs on all periods.
  //
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

  TFile* f = new TFile("L2StarB_hists_2.root","new");
  TCanvas* c1 = new TCanvas("c1","c1",600,600);

  TChain *t_even = new TChain("T_mv_even");
  TChain *t_odd  = new TChain("T_mv_odd");

  TString dir = "/afs/cern.ch/work/c/calpigia/public/Bsmumu_NTP_2012/data_Bs/";
  t_even->Add(dir+"tmva_Bs_data12_"+period+"_"+mu_algo+".root");
  t_odd ->Add(dir+"tmva_Bs_data12_"+period+"_"+mu_algo+".root");

  // Declare variables
  Double_t mass=-999;
  Int_t RunNum=-999;
  Double_t a_2D=-999;
  //
  bool evPassedMCP=false;
  bool evPassedKinMuons=false;
  bool evPassedKinBs=false;
  bool evPassedChi2Bs=false;
  //Additional cuts
  Double_t DR = -999;
  Double_t Lxy = -999;
  Double_t properTime_sig = -999;
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
  //
  vector<string> *trigg=0;

  int nTotEv=0;
  int nEvPassed_trigg=0;
  int nEvPassed_trigg_L2StarB=0;
 
  //histograms for plots
  TH1D* iso7_hist = new TH1D("iso7_hist", ";I_0.7;Num. events", 100,0.0,1.0);
  TH1D* Lxy_hist = new TH1D("Lxy_hist",";Lxy [mm];Num. events",100,-0.5,3.0);
  TH1D* a_2d_hist = new TH1D("a_2d_hist",";a_2D [rad];num. events",100,0.0,3.0);
  TH1D* DR_hist = new TH1D("DR_hist",";DR [rad];num. events",100,0.0,6.0);
  TH1D* pTime_hist = new TH1D("pTime_hist",";Proper time significance;num. events",100,-5.0,35.0);
  TH1D* logChi2z_hist = new TH1D("logChi2z_hist",";log[chi-squared(PV-SV)] z-axis;num. events",
				 100,-20.0,10.0);
  TH1D* logChi2xy_hist = new TH1D("logChi2xy_hist",";log[chi-squared(PV-SV)] x-y plane;num. events",
				  100,-20.0,10.0);
  TH1D* pT_hist = new TH1D("pT_hist",";B meson pT [GeV/c];num. events",100,5.0,70.0);
  TH1D* DCA_hist = new TH1D("DCA_hist",";DCA [mm];num. events",100,-0.5,0.5);
  TH1D* ZCA_hist = new TH1D("ZCA_hist",";ZCA [mm];num. events",200,-200,200);
  TH1D* d0min_hist = new TH1D("d0min_hist",";d0 min [mm];num. events",100,-0.4,0.4);
  TH1D* d0max_hist = new TH1D("d0max_hist",";d0 max [mm];num. events",100,-2,2);
  TH1D* Plng_min_hist = new TH1D("Plng_min_hist",";P_L_min (2D) [GeV/c];num. events",100,0,20000);
  TH1D* Plng_max_hist = new TH1D("Plng_max_hist",";P_L_max (2D) [GeV/c];num. events",100,0,40000);

  iso7_hist->SetMinimum(1);
  Lxy_hist->SetMinimum(0);
  a_2d_hist->SetMinimum(0);
  DR_hist->SetMinimum(0);
  pTime_hist->SetMinimum(0);
  logChi2z_hist->SetMinimum(0);
  logChi2xy_hist->SetMinimum(0);
  pT_hist->SetMinimum(0);
  DCA_hist->SetMinimum(1);
  ZCA_hist->SetMinimum(1);
  d0min_hist->SetMinimum(1);
  d0max_hist->SetMinimum(1);
  Plng_min_hist->SetMinimum(0);
  Plng_max_hist->SetMinimum(0);

  // ** EVEN **
  // Declare branches
  t_even->SetBranchAddress("mass",&mass);
  t_even->SetBranchAddress("run_number",&RunNum);
  t_even->SetBranchAddress("a_2D",&a_2D);
  //
  t_even->SetBranchAddress("EF_trigger_name",&trigg);
  t_even->SetBranchAddress("evPassedMCP",&evPassedMCP);
  t_even->SetBranchAddress("evPassedKinMuons",&evPassedKinMuons);
  t_even->SetBranchAddress("evPassedKinBs",&evPassedKinBs);
  t_even->SetBranchAddress("evPassedChi2Bs",&evPassedChi2Bs);
  //
  t_even->SetBranchAddress("DR",&DR);
  t_even->SetBranchAddress("Lxy",&Lxy);
  t_even->SetBranchAddress("properTime_sig",&properTime_sig);
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

  // Loop on EVEN events
  for (int l=0;l<t_even->GetEntries();l++)
    {
      t_even->GetEntry(l);
      // Select events in the Bs_mumu invariant mass search region [4766,5966] MeV
      if (mass>4766 && mass<5966)
	{
	  nTotEv++;
	  //
	  // Look for the trigger
	  bool hasPassedTrigg         = false;
	  bool hasPassedTrigg_L2StarB = false;
	  for (vector<string>::iterator iter= (*trigg).begin(); iter != (*trigg).end(); iter++)
	    {
	      if (iter->compare("EF_2mu4T_Bmumu")         == 0) hasPassedTrigg         = true;
	      if (iter->compare("EF_2mu4T_Bmumu_L2StarB") == 0) hasPassedTrigg_L2StarB = true;
	    }	
	  // Apply the baseline selection cuts
	  if ( evPassedMCP && evPassedKinBs && evPassedKinMuons && evPassedChi2Bs )
	    {
	      //do this if just doing cut for background reduction
	      //Apply additional cut
       	      //if (DR<1.5 && fabs(a_2D)<1.0 && Lxy>0.0 && properTime_sig>0.0 && iso7>0.25)
	      //{
		  
		  // Count the events that have passed the trigger selection
		  //if (hasPassedTrigg         && RunNum < 206955 ) nEvPassed_trigg++;
		  //if (hasPassedTrigg_L2StarB && RunNum >=  206955 ) nEvPassed_trigg_L2StarB++;
		  
	      //}

	      //do this when replicating plots
       	      if (hasPassedTrigg_L2StarB && RunNum >= 206955){
		  iso7_hist->Fill(iso7);
		  Lxy_hist->Fill(Lxy);
		  DR_hist->Fill(DR);
		  a_2d_hist->Fill(fabs(a_2D));
		  pTime_hist->Fill(properTime_sig);
		  logChi2z_hist->Fill(logChi2z);
		  logChi2xy_hist->Fill(logChi2xy);
		  pT_hist->Fill(pT/1000);
		  DCA_hist->Fill(DCA);
		  ZCA_hist->Fill(ZCA);
		  d0min_hist->Fill(d0min);
		  d0max_hist->Fill(d0max);
		  Plng_min_hist->Fill(Plng_min);
		  Plng_max_hist->Fill(Plng_max);
       	      }
	    }
	}
    } // end loop on EVEN events
  
  
  // ** ODD **
  // Declare branches
  t_odd->SetBranchAddress("mass",&mass);
  t_odd->SetBranchAddress("run_number",&RunNum);
  t_odd->SetBranchAddress("a_2D",&a_2D);
  //
  t_odd->SetBranchAddress("EF_trigger_name",&trigg);
  t_odd->SetBranchAddress("evPassedMCP",&evPassedMCP);
  t_odd->SetBranchAddress("evPassedKinMuons",&evPassedKinMuons);
  t_odd->SetBranchAddress("evPassedKinBs",&evPassedKinBs);
  t_odd->SetBranchAddress("evPassedChi2Bs",&evPassedChi2Bs);
  //
  t_odd->SetBranchAddress("DR",&DR);
  t_odd->SetBranchAddress("Lxy",&Lxy);
  t_odd->SetBranchAddress("properTime_sig",&properTime_sig);
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

  // Loop on ODD events
  cout << "Now doing ODD events!" << endl;
  for (int l=0;l<t_odd->GetEntries();l++)
    {
      t_odd->GetEntry(l);
      
      // Select events in the Bs_mumu invariant mass search region [4766,5966] MeV
      if (mass>4766 && mass<5966)
	{
	  nTotEv++;
	  //
	  // Look for the trigger
	  bool hasPassedTrigg         = false;
	  bool hasPassedTrigg_L2StarB = false;
	  for (vector<string>::iterator iter= (*trigg).begin(); iter != (*trigg).end(); iter++)
	    {
	      if (iter->compare("EF_2mu4T_Bmumu")         == 0) hasPassedTrigg         = true;
	      if (iter->compare("EF_2mu4T_Bmumu_L2StarB") == 0) hasPassedTrigg_L2StarB = true;
	    }	
	  // Apply the baseline selection cuts
	  if ( evPassedMCP && evPassedKinBs && evPassedKinMuons && evPassedChi2Bs )
	    {
	      //do this when cutting for background reduction
	      //Additional cuts
     	      //if (DR<1.5 && fabs(a_2D)<1.0 && Lxy>0.0 && properTime_sig>0.0 && iso7>0.25)
	      //{
		  // Count the events that have passed the trigger selection
		  //if (hasPassedTrigg         && RunNum < 206955 ) nEvPassed_trigg++;
		  //if (hasPassedTrigg_L2StarB && RunNum >=  206955 ) nEvPassed_trigg_L2StarB++;
	      //}

	      //do this when replicating plots
      	      if (hasPassedTrigg_L2StarB && RunNum >= 206955){
		  iso7_hist->Fill(iso7);
		  Lxy_hist->Fill(Lxy);
		  DR_hist->Fill(DR);
		  a_2d_hist->Fill(a_2D);
		  pTime_hist->Fill(properTime_sig);
		  logChi2z_hist->Fill(logChi2z);
		  logChi2xy_hist->Fill(logChi2xy);
		  pT_hist->Fill(pT/1000);
		  DCA_hist->Fill(DCA);
		  ZCA_hist->Fill(ZCA);
		  d0min_hist->Fill(d0min);
		  d0max_hist->Fill(d0max);
		  Plng_min_hist->Fill(Plng_min);
		  Plng_max_hist->Fill(Plng_max);
       	      }
	    }
	}
    } // end loop on ODD events

  /*
  cout << "" << endl;
  cout << " Tot number of B candidates = " << nTotEv << endl;
  cout << "" << endl;
  cout << " -- Events passed trigger EF_2mu4T_Bmumu         = " <<  nEvPassed_trigg << endl; 
  cout << " -- Events passed trigger EF_2mu4T_Bmumu_l2StarB = " <<  nEvPassed_trigg_L2StarB << endl; 
  cout << "" <<endl;
  */
  cout << "finished" << endl;
  /*
  iso7_hist->Draw("e");
  iso7_hist->SetMarkerStyle(7);
  c1->SetLogy(1);
  c1->SaveAs("iso7_plot3.eps");
  Lxy_hist->Draw("e");
  Lxy_hist->SetMarkerStyle(7);
  c1->SetLogy(0);
  c1->SaveAs("Lxy_plot3.eps");
  DR_hist->Draw("e");
  DR_hist->SetMarkerStyle(7);
  c1->SaveAs("DR_plot3.eps");
  a_2d_hist->Draw("e");
  a_2d_hist->SetMarkerStyle(7);
  c1->SaveAs("a_2d_plot3.eps");
  pTime_hist->Draw("e");
  pTime_hist->SetMarkerStyle(7);
  c1->SaveAs("pTime_plot3.eps");
  logChi2z_hist->Draw("e");
  logChi2z_hist->SetMarkerStyle(7);
  c1->SaveAs("logChi2z_plot3.eps");*/
  logChi2xy_hist->Draw("e");
  logChi2xy_hist->SetMarkerStyle(7);
  c1->SaveAs("logChi2xy_plot_L2StarB_2.eps");         
  pT_hist->Draw("e");
  pT_hist->SetMarkerStyle(7);
  c1->SaveAs("pT_plot_L2StarB_2.eps");
  /*  DCA_hist->Draw("e");
  DCA_hist->SetMarkerStyle(7);
  c1->SetLogy(1);
  c1->SaveAs("DCA_plot3.eps");
  ZCA_hist->Draw("e");
  ZCA_hist->SetMarkerStyle(7);
  c1->SetLogy(1);
  c1->SaveAs("ZCA_plot3.eps");
  d0min_hist->Draw("e");
  d0min_hist->SetMarkerStyle(7);
  c1->SetLogy(1);
  c1->SaveAs("d0min_plot3.eps");
  d0max_hist->Draw("e");
  d0max_hist->SetMarkerStyle(7);
  c1->SetLogy(1);
  c1->SaveAs("d0max_plot3.eps");
  Plng_min_hist->Draw("e");
  Plng_min_hist->SetMarkerStyle(7);
  c1->SetLogy(0);
  c1->SaveAs("Plng_min_plot3.eps");
  Plng_max_hist->Draw("e");
  Plng_max_hist->SetMarkerStyle(7);
  c1->SaveAs("Plng_max_plot3.eps");   */  
  
  f->Write();

}
