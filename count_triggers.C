#include "Riostream.h"
#include <string>
#include "TMath.h"
#include "TString.h"
#include "TFile.h"
#include "TChain.h"
#include <iostream>
#include <fstream>
#include "TH1D.h"
#include <sstream>


void count_triggers(){

  Int_t n_trig = 1;
  TString trigg_name[7]={"EF_2mu4T_Bmumu",
			 "EF_2mu4T_Bmumu_Barrel",
			 "EF_mu4Tmu6_Bmumu",
			 "EF_2mu4T_Bmumu_BarrelOnly",
			 "EF_3mu4T",
			 "EF_mu4Tmu6_Bmumu_Barrel",
			 "EF_2mu6_Bmumu"};

  for(int z=0;z<n_trig;z++){
    Int_t n_triggs = n_trig-z;
  TString mu_algo="";
  mu_algo = "muons";
  //mu_algo = "staco";  
  TString period_list[10]={"A","B","C","D","E","G","H","I","J","L"};
  Int_t counts_per_period[10][n_triggs];
  Int_t counts_per_period_l2starb[10][n_triggs];
  std::ostringstream ss;
  ss << n_triggs;
  TString file_name = "trigger_count_hists_"+ss.str()+".root";
  TFile* f = new TFile(file_name,"recreate");
  TH1D* hists_list[10]; //Array of hist objects, one for each period, to count events per trigger
  TH1D* trigg_OR_hist = new TH1D("trigg_OR","",20,0,20);

  //histograms for plots
  TH1D* vars_hist_list[n_triggs][14];
  TH1D* vars_l2starb_hist_list[n_triggs][14];
  TH1D* vars_OR[14];
  vars_OR[0] = new TH1D("iso7_OR",";I_{0.7};Num. events",100,0.0,1.0);
  vars_OR[1] = new TH1D("Lxy_OR",";Lxy [mm];Num. events",100,-0.5,3.0);
  vars_OR[2] = new TH1D("a_2d_OR",";a_{2D} [rad];num. events",100,0.0,3.0);
  vars_OR[3] = new TH1D("DR_OR",";\\Delta R [rad];num. events",100,0.0,6.0);
  vars_OR[4] = new TH1D("pTime_OR",";Proper time significance;num. events",100,-5.0,35.0);
  vars_OR[5] = new TH1D("logChi2z_OR",";log[\\chi^{2}(PV-SV)] z-axis;num. events",100,-20.0,10.0);
  vars_OR[6] = new TH1D("logChi2xy_OR",";log[\\chi^{2}(PV-SV)] x-y plane;num. events",100,-20.0,10.0);
  vars_OR[7] = new TH1D("pT_OR",";B meson pT [GeV/c];num. events",100,5.0,70.0);
  vars_OR[8] = new TH1D("DCA_OR",";DCA [mm];num. events",100,-0.5,0.5);
  vars_OR[9] = new TH1D("ZCA_OR",";ZCA [mm];num. events",200,-200,200);
  vars_OR[10] = new TH1D("d0min_OR",";d0 min [mm];num. events",100,-0.4,0.4);
  vars_OR[11] = new TH1D("d0max_OR",";d0 max [mm];num. events",100,-2,2);
  vars_OR[12] = new TH1D("Plng_min_OR",";P_{L}^{min} (2D) [GeV/c];num. events",100,0,20);
  vars_OR[13] = new TH1D("Plng_max_OR",";P_{L}^{max} (2D) [GeV/c];num. events",100,0,40);

  for (int j=0;j<n_triggs;j++){
    vars_hist_list[j][0] = new TH1D("iso7_"+trigg_name[j], ";I_{0.7};Num. events", 100,0.0,1.0);
    vars_hist_list[j][1] = new TH1D("Lxy_"+trigg_name[j],";Lxy [mm];Num. events",100,-0.5,3.0);
    vars_hist_list[j][2] = new TH1D("a_2d_"+trigg_name[j],";a_{2D} [rad];num. events",100,0.0,3.0);
    vars_hist_list[j][3] = new TH1D("DR_"+trigg_name[j],";\\Delta R [rad];num. events",100,0.0,6.0);
    vars_hist_list[j][4] = new TH1D("pTime_"+trigg_name[j],";Proper time significance;num. events",100,-5.0,35.0);
    vars_hist_list[j][5] = new TH1D("logChi2z_"+trigg_name[j],";log[\\chi^{2}(PV-SV)] z-axis;num. events",
				    100,-20.0,10.0);
    vars_hist_list[j][6] = new TH1D("logChi2xy_"+trigg_name[j],";log[\\chi^{2}(PV-SV)] x-y plane;num. events",
				    100,-20.0,10.0);
    vars_hist_list[j][7] = new TH1D("pT_"+trigg_name[j],";B meson pT [GeV/c];num. events",100,5.0,70.0);
    vars_hist_list[j][8] = new TH1D("DCA_"+trigg_name[j],";DCA [mm];num. events",100,-0.5,0.5);
    vars_hist_list[j][9] = new TH1D("ZCA_"+trigg_name[j],";ZCA [mm];num. events",200,-200,200);
    vars_hist_list[j][10] = new TH1D("d0min_"+trigg_name[j],";d0 min [mm];num. events",100,-0.4,0.4);
    vars_hist_list[j][11] = new TH1D("d0max_"+trigg_name[j],";d0 max [mm];num. events",100,-2,2);
    vars_hist_list[j][12] = new TH1D("Plng_min_"+trigg_name[j],";P_{L}^{min} (2D) [GeV/c];num. events",100,0,20);
    vars_hist_list[j][13] = new TH1D("Plng_max_"+trigg_name[j],";P_{L}^{max} (2D) [GeV/c];num. events",100,0,40);
    //note to self - when filling, divide Plng by 1000 to get in GeV not MeV
    vars_hist_list[j][0]->SetMinimum(1);
    vars_hist_list[j][1]->SetMinimum(0);
    vars_hist_list[j][2]->SetMinimum(0);
    vars_hist_list[j][3]->SetMinimum(0);
    vars_hist_list[j][4]->SetMinimum(0);
    vars_hist_list[j][5]->SetMinimum(0);
    vars_hist_list[j][6]->SetMinimum(0);
    vars_hist_list[j][7]->SetMinimum(0);
    vars_hist_list[j][8]->SetMinimum(1);
    vars_hist_list[j][9]->SetMinimum(1);
    vars_hist_list[j][10]->SetMinimum(1);
    vars_hist_list[j][11]->SetMinimum(1);
    vars_hist_list[j][12]->SetMinimum(0);
    vars_hist_list[j][13]->SetMinimum(0);
    //L2StarB hists
    vars_l2starb_hist_list[j][0] = new TH1D("iso7_"+trigg_name[j]+"_l2starb", ";I_{0.7};Num. events", 
					    100,0.0,1.0);
    vars_l2starb_hist_list[j][1] = new TH1D("Lxy_"+trigg_name[j]+"_l2starb",";Lxy [mm];Num. events",
					    100,-0.5,3.0);
    vars_l2starb_hist_list[j][2] = new TH1D("a_2d_"+trigg_name[j]+"_l2starb",";a_{2D} [rad];num. events",
					    100,0.0,3.0);
    vars_l2starb_hist_list[j][3] = new TH1D("DR_"+trigg_name[j]+"_l2starb",";\\Delta R [rad];num. events",
					    100,0.0,6.0);
    vars_l2starb_hist_list[j][4] = new TH1D("pTime_"+trigg_name[j]+"_l2starb",
					    ";Proper time significance;num. events",100,-5.0,35.0);
    vars_l2starb_hist_list[j][5] = new TH1D("logChi2z_"+trigg_name[j]+"_l2starb",
					    ";log[\\chi^{2}(PV-SV)] z-axis;num. events",100,-20.0,10.0);
    vars_l2starb_hist_list[j][6] = new TH1D("logChi2xy_"+trigg_name[j]+"_l2starb",
					    ";log[\\chi^{2}(PV-SV)] x-y plane;num. events",100,-20.0,10.0);
    vars_l2starb_hist_list[j][7] = new TH1D("pT_"+trigg_name[j]+"_l2starb",
					    ";B meson pT [GeV/c];num. events",100,5.0,70.0);
    vars_l2starb_hist_list[j][8] = new TH1D("DCA_"+trigg_name[j]+"_l2starb",";DCA [mm];num. events",
					    100,-0.5,0.5);
    vars_l2starb_hist_list[j][9] = new TH1D("ZCA_"+trigg_name[j]+"_l2starb",";ZCA [mm];num. events",
					    200,-200,200);
    vars_l2starb_hist_list[j][10] = new TH1D("d0min_"+trigg_name[j]+"_l2starb",";d0 min [mm];num. events",
					     100,-0.4,0.4);
    vars_l2starb_hist_list[j][11] = new TH1D("d0max_"+trigg_name[j]+"_l2starb",";d0 max [mm];num. events",
					     100,-2,2);
    vars_l2starb_hist_list[j][12] = new TH1D("Plng_min_"+trigg_name[j]+"_l2starb",
					     ";P_{L}^{min} (2D) [GeV/c];num. events",100,0,20);
    vars_l2starb_hist_list[j][13] = new TH1D("Plng_max_"+trigg_name[j]+"_l2starb",
					     ";P_{L}^{max} (2D) [GeV/c];num. events",100,0,40);
    //note to self - when filling, divide Plng by 1000 to get in GeV not MeV
    vars_l2starb_hist_list[j][0]->SetMinimum(1);
    vars_l2starb_hist_list[j][1]->SetMinimum(0);
    vars_l2starb_hist_list[j][2]->SetMinimum(0);
    vars_l2starb_hist_list[j][3]->SetMinimum(0);
    vars_l2starb_hist_list[j][4]->SetMinimum(0);
    vars_l2starb_hist_list[j][5]->SetMinimum(0);
    vars_l2starb_hist_list[j][6]->SetMinimum(0);
    vars_l2starb_hist_list[j][7]->SetMinimum(0);
    vars_l2starb_hist_list[j][8]->SetMinimum(1);
    vars_l2starb_hist_list[j][9]->SetMinimum(1);
    vars_l2starb_hist_list[j][10]->SetMinimum(1);
    vars_l2starb_hist_list[j][11]->SetMinimum(1);
    vars_l2starb_hist_list[j][12]->SetMinimum(0);
    vars_l2starb_hist_list[j][13]->SetMinimum(0);
  }

  for (int a=0;a<10;a++){
    
    TString period= period_list[a];
    //period = "*";
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

    Int_t event_count[n_triggs];
    Int_t event_count_l2starb[n_triggs];
    for (int i=0;i<n_triggs;i++){
      event_count[i]=0;
      event_count_l2starb[i]=0;
    }

    TChain *t_even = new TChain("T_mv_even");
    TChain *t_odd  = new TChain("T_mv_odd");

    TString dir = "/afs/cern.ch/work/c/calpigia/public/Bsmumu_NTP_2012/data_Bs/";
    t_even->Add(dir+"tmva_Bs_data12_"+period+"_"+mu_algo+".root");
    t_odd ->Add(dir+"tmva_Bs_data12_"+period+"_"+mu_algo+".root");

    //variables
    std::vector<string>* trigg_address = 0;
    Double_t mass = -999;
    Int_t RunNum = -999;
    //baseline selection
    bool evPassedMCP = false;
    bool evPassedKinMuons = false;
    bool evPassedKinBs = false;
    bool evPassedChi2Bs = false;
    //Additional cuts + variables
    Double_t iso7 = -999;
    Double_t Lxy = -999;
    Double_t a_2D = -999; 
    Double_t DR = -999;
    Double_t pTime = -999;
    Double_t logChi2z = -999;
    Double_t logChi2xy = -999;
    Double_t pT = -999; 
    Double_t DCA = -999;
    Double_t ZCA = -999;
    Double_t d0min = -999;
    Double_t d0max = -999;
    Double_t Plng_min = -999;
    Double_t Plng_max = -999;
    //Variable list for histogram filling. 
    Double_t* vars_list[14]={&iso7,&Lxy,&a_2D,&DR,&pTime,&logChi2z,&logChi2xy,
			     &pT,&DCA,&ZCA,&d0min,&d0max,&Plng_min,&Plng_max};
    //initialise hist array for this period
    if (period=="C"){
      hists_list[a] = new TH1D("hist_"+period,"",2*n_triggs,0,2*n_triggs); //can get l2starb and trigg in C
    }else{
      hists_list[a] = new TH1D("hist_"+period,"",n_triggs+1,0,n_triggs+1); //+1 just for empty bin at edge
    }
    hists_list[a]->SetBarOffset(0.1);
    hists_list[a]->SetFillColor(30+a);
    hists_list[a]->SetBarWidth(0.45);

    //even events

    std::cout << "Doing even events" << std::endl;
  
    t_even->SetBranchAddress("mass",&mass);
    t_even->SetBranchAddress("run_number",&RunNum);
    t_even->SetBranchAddress("EF_trigger_name",&trigg_address);
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
  
    for (int i=0;i<t_even->GetEntries();i++){
      t_even->GetEntry(i);
      if (mass>4766 && mass<5966){
	bool already_counted = false; //for trigger OR, so don't double count
	for (vector<string>::iterator iter=(*trigg_address).begin();iter!=(*trigg_address).end();iter++){
	  for(int j=0;j<n_triggs;j++){ //loop over triggers
	    bool hasPassedTrigg = false;
	    bool hasPassedTrigg_L2StarB = false;
	    if (iter->compare(trigg_name[j])==0){
	      hasPassedTrigg = true;
	    }else if(iter->compare(trigg_name[j]+"_L2StarB")==0){
	      hasPassedTrigg_L2StarB = true;
	    }
	    if (evPassedMCP && evPassedKinBs && evPassedKinMuons && evPassedChi2Bs){
	      if (hasPassedTrigg && RunNum<206955){
		event_count[j]++;
		hists_list[a]->Fill(trigg_name[j],1);
		if (!already_counted){ //check if not counted, for trigger OR
		  trigg_OR_hist->Fill(a*2);
		  already_counted=true;
		  for (int k=0;k<14;k++){ //fill discrim var OR hists
		    if (k==7 || k==12 || k==13){ //pT or Plng, divide by 1000 to get in GeV
		      vars_OR[k]->Fill(*vars_list[k]/1000.0);
		    }else{
		      vars_OR[k]->Fill(*vars_list[k]);
		    }
		  }
		}
		//Fill discriminating variable histograms
		for (int k=0;k<14;k++){
		  if (k==7 || k==12 || k==13){ //pT or Plng, divide by 1000 to get in GeV
		    vars_hist_list[j][k]->Fill(*vars_list[k]/1000.0);
		  }else{
		    vars_hist_list[j][k]->Fill(*vars_list[k]);
		  }
		}
	      }else if (hasPassedTrigg_L2StarB && RunNum>=206955){
		event_count_l2starb[j]++;
		hists_list[a]->Fill(trigg_name[j]+"_L2StarB",1);
		if (!already_counted){ //check if not counted
		  trigg_OR_hist->Fill(a*2);
		  already_counted=true;
		  for (int k=0;k<14;k++){ //fill discrim var OR hists
		    if (k==7 || k==12 || k==13){ //pT or Plng, divide by 1000 to get in GeV
		      vars_OR[k]->Fill(*vars_list[k]/1000.0);
		    }else{
		      vars_OR[k]->Fill(*vars_list[k]);
		    }
		  }
		}
		//Fill discriminiating variable histograms
		for (int k=0;k<14;k++){
		  if (k==7 || k==12 || k==13){ //pT or Plng, divide by 1000 to get in GeV
		    vars_l2starb_hist_list[j][k]->Fill(*vars_list[k]/1000.0);
		  }else{
		    vars_l2starb_hist_list[j][k]->Fill(*vars_list[k]);
		  }		
		}
	      }else if (hasPassedTrigg && RunNum>=206955 && trigg_name[j]=="EF_3mu4T"){
		//need this bit as 3mu4T has no L2StarB, so would otherwise only be counted
		//between run 1 and run 206955.
		event_count[j]++;
		hists_list[a]->Fill(trigg_name[j],1);
		if (!already_counted){
		  trigg_OR_hist->Fill(a*2);
		  already_counted=true;
		  for (int k=0;k<14;k++){ //fill discrim var OR hists
		    if (k==7 || k==12 || k==13){ //pT or Plng, divide by 1000 to get in GeV
		      vars_OR[k]->Fill(*vars_list[k]/1000.0);
		    }else{
		      vars_OR[k]->Fill(*vars_list[k]);
		    }
		  }
		}
		//Fill discriminating variable histograms
		for (int k=0;k<14;k++){
		  if (k==7 || k==12 || k==13){ //pT or Plng, divide by 1000 to get in GeV
		    vars_hist_list[j][k]->Fill(*vars_list[k]/1000.0);
		  }else{
		    vars_hist_list[j][k]->Fill(*vars_list[k]);
		  }		  
		}
	      }
	    }
	  }
	}
      }
    }
  	 	 
    std::cout << "Doing odd events" << std::endl;

    //odd events
    t_odd->SetBranchAddress("mass",&mass);
    t_odd->SetBranchAddress("run_number",&RunNum);
    t_odd->SetBranchAddress("EF_trigger_name",&trigg_address);
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
   
    for (int i=0;i<t_odd->GetEntries();i++){
      t_odd->GetEntry(i);
      if (mass>4766 && mass<5966){
	bool already_counted=false; //for trigger OR, so don't double count
	for (vector<string>::iterator iter=(*trigg_address).begin();iter!=(*trigg_address).end();iter++){
	  for(int j=0;j<n_triggs;j++){ //loop over triggers
	    bool hasPassedTrigg = false;
	    bool hasPassedTrigg_L2StarB = false;
	    if (iter->compare(trigg_name[j])==0){
	      hasPassedTrigg = true;
	    }else if(iter->compare(trigg_name[j]+"_L2StarB")==0){
	      hasPassedTrigg_L2StarB = true;
	    }
	    if (evPassedMCP && evPassedKinBs && evPassedKinMuons && evPassedChi2Bs){
	      if (hasPassedTrigg && RunNum<206955){
		event_count[j]++;
		hists_list[a]->Fill(trigg_name[j],1);
		if (!already_counted){ //check if counted or not
		  trigg_OR_hist->Fill(a*2);
		  already_counted=true;
		  for (int k=0;k<14;k++){ //fill discrim var OR hists
		    if (k==7 || k==12 || k==13){ //pT or Plng, divide by 1000 to get in GeV
		      vars_OR[k]->Fill(*vars_list[k]/1000.0);
		    }else{
		      vars_OR[k]->Fill(*vars_list[k]);
		    }
		  }
		}
		//Fill discriminating variable histograms
		for (int k=0;k<14;k++){
		  if (k==7 || k==12 || k==13){ //pT or Plng, divide by 1000 to get in GeV
		    vars_hist_list[j][k]->Fill(*vars_list[k]/1000.0);
		  }else{
		    vars_hist_list[j][k]->Fill(*vars_list[k]);
		  }
		}
	      }else if (hasPassedTrigg_L2StarB && RunNum>=206955){
		event_count_l2starb[j]++;
		hists_list[a]->Fill(trigg_name[j]+"_L2StarB",1);
		if (!already_counted){ //check if counted or not
		  trigg_OR_hist->Fill(a*2);
		  already_counted=true;
		  for (int k=0;k<14;k++){ //fill discrim var OR hists
		    if (k==7 || k==12 || k==13){ //pT or Plng, divide by 1000 to get in GeV
		      vars_OR[k]->Fill(*vars_list[k]/1000.0);
		    }else{
		      vars_OR[k]->Fill(*vars_list[k]);
		    }
		  }
		}
		//Fill discriminating variable histograms
		for (int k=0;k<14;k++){
		  if (k==7 || k==12 || k==13){ //pT or Plng, divide by 1000 to get in GeV
		    vars_l2starb_hist_list[j][k]->Fill(*vars_list[k]/1000.0);
		  }else{
		    vars_l2starb_hist_list[j][k]->Fill(*vars_list[k]);
		  }
		}
	      }else if (hasPassedTrigg && RunNum>=206955 && trigg_name[j]=="EF_3mu4T"){
		//need this bit as 3mu4T has no L2StarB, so would otherwise only be counted
		//between run 1 and run 206955. 
		event_count[j]++;
		hists_list[a]->Fill(trigg_name[j],1);
		if (!already_counted){
		  trigg_OR_hist->Fill(a*2);
		  already_counted=true;
		  for (int k=0;k<14;k++){ //fill discrim var OR hists
		    if (k==7 || k==12 || k==13){ //pT or Plng, divide by 1000 to get in GeV
		      vars_OR[k]->Fill(*vars_list[k]/1000.0);
		    }else{
		      vars_OR[k]->Fill(*vars_list[k]);
		    }
		  }
		}
		//Fill discriminating variable histograms
		for (int k=0;k<14;k++){
		  if (k==7 || k==12 || k==13){ //pT or Plng, divide by 1000 to get in GeV
		    vars_hist_list[j][k]->Fill(*vars_list[k]/1000.0);
		  }else{
		    vars_hist_list[j][k]->Fill(*vars_list[k]);
		  }
		}
	      }
	    }
	  }
	}
      }
    } 
    for (int i=0;i<n_triggs;i++){
      counts_per_period[a][i]=event_count[i];
      counts_per_period_l2starb[a][i]=event_count_l2starb[i];
    }
  }
  //clear EF_3mu4T_L2StarB histograms, as that trigger doesn't actually exist
  for (int k=0;k<14;k++){
    delete vars_l2starb_hist_list[4][k];
  }
  f->Write(); //Output histogram arrays to .root file

  ofstream count_file("count_file.txt", ios::app);
  Int_t total_events = 0;
  for (int i=0;i<10;i++){
    count_file << period_list[i] << ": " << std::endl;
    std::cout << period_list[i] << ": " << std::endl;
    for(int j=0; j<n_triggs;j++){
      count_file << trigg_name[j] << ": " << counts_per_period[i][j] << std::endl
 		 << trigg_name[j] << "_L2StarB: " << counts_per_period_l2starb[i][j] << std::endl;
      std::cout << "Events from " << trigg_name[j] << ": " << counts_per_period[i][j] << std::endl
		<< "Events from " << trigg_name[j] << "_L2StarB: " << counts_per_period_l2starb[i][j]
		<< std::endl;
      total_events=total_events+counts_per_period[i][j]+counts_per_period_l2starb[i][j];
    } 
  }
  count_file << std::endl << "Total: " << total_events << std::endl
	     << "-----" << std::endl << "Next run" << std::endl << "-----" << std::endl;
  count_file.close();
  std::cout << std::endl << "Total: " << total_events << std::endl;
  std::cout << "Finished." << std::endl;
  //
}
}
