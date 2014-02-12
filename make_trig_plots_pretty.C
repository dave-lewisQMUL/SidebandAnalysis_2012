#include "Riostream.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TFile.h"
#include "TLegend.h"
#include <vector>

void make_trig_plots_pretty(){
  
  TFile root_file("trigger_count_hists.root");
  TCanvas* c1 = new TCanvas("c1","c1",600,600);
  TCanvas* c2 = new TCanvas("c2","c2",600,600);
  TString trigg_names[7]={"EF_2mu4T_Bmumu",
			 "EF_2mu4T_Bmumu_Barrel",
			 "EF_mu4Tmu6_Bmumu",
			 "EF_2mu4T_Bmumu_BarrelOnly",
			 "EF_3mu4T",
			 "EF_mu4Tmu6_Bmumu_Barrel",
			 "EF_2mu6_Bmumu"};
  std::vector<TString> vars;
  vars.clear();
  vars.push_back("iso7");
  vars.push_back("Lxy");
  vars.push_back("a_2d");
  vars.push_back("DR");
  vars.push_back("pTime");
  vars.push_back("logChi2z");
  vars.push_back("logChi2xy");
  vars.push_back("pT");
  vars.push_back("DCA");
  vars.push_back("ZCA");
  vars.push_back("d0min");
  vars.push_back("d0max");
  vars.push_back("Plng_min");
  vars.push_back("Plng_max");

  for(int i=0;i<vars.size();i++){
    if(vars.at(i)=="iso7"){
      c1->SetLogy(1);
      c2->SetLogy(1);
    }else if(vars.at(i)=="DCA"){
      c1->SetLogy(1);
      c2->SetLogy(1);
    }else if(vars.at(i)=="ZCA"){
      c1->SetLogy(1);
      c2->SetLogy(1);
    }else if(vars.at(i)=="d0min"){
      c1->SetLogy(1);
      c2->SetLogy(1);
    }else if(vars.at(i)=="d0max"){
      c1->SetLogy(1);
      c2->SetLogy(1);
    }else{
      c1->SetLogy(0);
      c2->SetLogy(0);
    }

    TH1D* h_trigg_1 = (TH1D*)root_file.Get(vars.at(i)+"_EF_2mu4T_Bmumu");
    TH1D* h_l2starb_1 = (TH1D*)root_file.Get(vars.at(i)+"_EF_2mu4T_Bmumu_l2starb");
    TH1D* h_trigg_2 = (TH1D*)root_file.Get(vars.at(i)+"_EF_2mu4T_Bmumu_Barrel");
    TH1D* h_l2starb_2 = (TH1D*)root_file.Get(vars.at(i)+"_EF_2mu4T_Bmumu_Barrel_l2starb");
    TH1D* h_trigg_3 = (TH1D*)root_file.Get(vars.at(i)+"_EF_mu4Tmu6_Bmumu");
    TH1D* h_l2starb_3 = (TH1D*)root_file.Get(vars.at(i)+"_EF_mu4Tmu6_Bmumu_l2starb");
    TH1D* h_trigg_4 = (TH1D*)root_file.Get(vars.at(i)+"_EF_2mu4T_Bmumu_BarrelOnly");
    TH1D* h_l2starb_4 = (TH1D*)root_file.Get(vars.at(i)+"_EF_2mu4T_Bmumu_BarrelOnly_l2starb");
    TH1D* h_trigg_5 = (TH1D*)root_file.Get(vars.at(i)+"_EF_3mu4T");
    TH1D* h_trigg_6 = (TH1D*)root_file.Get(vars.at(i)+"_EF_mu4Tmu6_Bmumu_Barrel");
    TH1D* h_l2starb_6 = (TH1D*)root_file.Get(vars.at(i)+"_EF_mu4Tmu6_Bmumu_Barrel_l2starb");
    TH1D* h_trigg_7 = (TH1D*)root_file.Get(vars.at(i)+"_EF_2mu6_Bmumu");
    TH1D* h_l2starb_7 = (TH1D*)root_file.Get(vars.at(i)+"_EF_2mu6_Bmumu_l2starb");
    h_trigg_1->SetStats(0);
    h_l2starb_1->SetStats(0);
    h_trigg_2->SetStats(0);
    h_l2starb_2->SetStats(0);
    h_trigg_3->SetStats(0);
    h_l2starb_3->SetStats(0);
    h_trigg_4->SetStats(0);
    h_l2starb_4->SetStats(0);
    h_trigg_5->SetStats(0);
    h_trigg_6->SetStats(0);
    h_l2starb_6->SetStats(0);
    h_trigg_7->SetStats(0);
    h_l2starb_7->SetStats(0);

    h_trigg_1->GetYaxis()->SetTitleOffset(1.5);
    h_trigg_1->SetLineColor(1);
    h_trigg_2->SetLineColor(2);
    h_trigg_3->SetLineColor(3);
    h_trigg_4->SetLineColor(4);
    h_trigg_5->SetLineColor(5);
    h_trigg_6->SetLineColor(6);
    h_trigg_7->SetLineColor(7);
    h_l2starb_1->SetLineColor(8);
    h_l2starb_2->SetLineColor(9);
    h_l2starb_3->SetLineColor(10);
    h_l2starb_4->SetLineColor(11);
    h_l2starb_6->SetLineColor(12);
    h_l2starb_7->SetLineColor(13);

    c1->cd();

    h_trigg_1->Draw("");
    h_l2starb_1->Draw("same");
    h_trigg_2->Draw("same");
    h_l2starb_2->Draw("same");
    h_trigg_3->Draw("same");
    h_l2starb_3->Draw("same");
    h_trigg_4->Draw("same");
    h_l2starb_4->Draw("same");
    h_trigg_5->Draw("same");
    h_trigg_6->Draw("same");
    h_l2starb_6->Draw("same");
    h_trigg_7->Draw("same");
    h_l2starb_7->Draw("same");

    TLegend* leg1;
    if(vars.at(i)=="iso7"){
      leg1 = new TLegend(0.6,0.5,0.89,0.59);
    }else{
      leg1 = new TLegend(0.6,0.8,0.89,0.89);
    }
    leg1->AddEntry(h_trigg_1,trigg_names[0],"l");
    leg1->AddEntry(h_l2starb_1,trigg_names[0]+"_L2StarB","l");
    leg1->AddEntry(h_trigg_2,trigg_names[1],"l");
    leg1->AddEntry(h_l2starb_2,trigg_names[1]+"_L2StarB","l");
    leg1->AddEntry(h_trigg_3,trigg_names[2],"l");
    leg1->AddEntry(h_l2starb_3,trigg_names[2]+"_L2StarB","l");
    leg1->AddEntry(h_trigg_4,trigg_names[3],"l");
    leg1->AddEntry(h_l2starb_4,trigg_names[3]+"_L2StarB","l");
    leg1->AddEntry(h_trigg_5,trigg_names[4],"l");
    leg1->AddEntry(h_trigg_6,trigg_names[5],"l");
    leg1->AddEntry(h_l2starb_6,trigg_names[5]+"_L2StarB","l");
    leg1->AddEntry(h_trigg_7,trigg_names[6],"l");
    leg1->AddEntry(h_l2starb_7,trigg_names[6]+"_L2StarB","l");
    leg1->SetFillColor(0);
    leg1->SetFillStyle(0);
    leg1->Draw();

    c1->SaveAs("all_triggs/"+vars.at(i)+"_plot.pdf");
    c1->Clear();
    /*
    //just trigg hists
    h_trigg_1->Draw("");
    h_trigg_2->Draw("same");
    h_trigg_3->Draw("same");
    h_trigg_4->Draw("same");
    h_trigg_5->Draw("same");
    h_trigg_6->Draw("same");
    h_trigg_7->Draw("same");

    leg1->Clear();
    leg1->AddEntry(h_trigg_1,trigg_names[0],"l");
    leg1->AddEntry(h_trigg_2,trigg_names[1],"l");
    leg1->AddEntry(h_trigg_3,trigg_names[2],"l");
    leg1->AddEntry(h_trigg_4,trigg_names[3],"l");
    leg1->AddEntry(h_trigg_5,trigg_names[4],"l");
    leg1->AddEntry(h_trigg_6,trigg_names[5],"l");
    leg1->AddEntry(h_trigg_7,trigg_names[6],"l");
    leg1->Draw();

    c1->SaveAs("all_triggs/"+vars.at(i)+"_trigg.eps");
    c1->Clear();
    //just l2starb hists
    h_l2starb_1->Draw("");
    h_l2starb_2->Draw("same");
    h_l2starb_3->Draw("same");
    h_l2starb_4->Draw("same");
    h_l2starb_6->Draw("same");
    h_l2starb_7->Draw("same");

    leg1->Clear();
    leg1->AddEntry(h_l2starb_1,trigg_names[0]+"_L2StarB","l");
    leg1->AddEntry(h_l2starb_2,trigg_names[1]+"_L2StarB","l");
    leg1->AddEntry(h_l2starb_3,trigg_names[2]+"_L2StarB","l");
    leg1->AddEntry(h_l2starb_4,trigg_names[3]+"_L2StarB","l");
    leg1->AddEntry(h_l2starb_6,trigg_names[5]+"_L2StarB","l");
    leg1->AddEntry(h_l2starb_7,trigg_names[6]+"_L2StarB","l");
    leg1->Draw();

    c1->SaveAs("all_triggs/"+vars.at(i)+"_l2starb.eps");
    c1->Clear();

    //add trigg+l2starb hists and plot totals
    h_trigg_1->Add(h_l2starb_1,1);
    h_trigg_2->Add(h_l2starb_2,1);
    h_trigg_3->Add(h_l2starb_3,1);
    h_trigg_4->Add(h_l2starb_4,1);
    h_trigg_6->Add(h_l2starb_6,1);
    h_trigg_7->Add(h_l2starb_7,1);

    h_trigg_1->Draw("");
    h_trigg_2->Draw("same");
    h_trigg_3->Draw("same");
    h_trigg_4->Draw("same");
    h_trigg_5->Draw("same");
    h_trigg_6->Draw("same");
    h_trigg_7->Draw("same");

    leg1->Clear();
    leg1->AddEntry(h_trigg_1,trigg_names[0]+"_total","l");
    leg1->AddEntry(h_trigg_2,trigg_names[1]+"_total","l");
    leg1->AddEntry(h_trigg_3,trigg_names[2]+"_total","l");
    leg1->AddEntry(h_trigg_4,trigg_names[3]+"_total","l");
    leg1->AddEntry(h_trigg_5,trigg_names[4]+"_total","l");
    leg1->AddEntry(h_trigg_6,trigg_names[5]+"_total","l");
    leg1->AddEntry(h_trigg_7,trigg_names[6]+"_total","l");
    leg1->Draw();

    c1->SaveAs("all_triggs/"+vars.at(i)+"_total.eps");
    c1->Clear();

    //subtract l2starb hists from trigg hists, by adding with weight -1
    h_trigg_1->Add(h_l2starb_1,-1);
    h_trigg_2->Add(h_l2starb_2,-1);
    h_trigg_3->Add(h_l2starb_3,-1);
    h_trigg_4->Add(h_l2starb_4,-1);
    h_trigg_6->Add(h_l2starb_6,-1);
    h_trigg_7->Add(h_l2starb_7,-1);
    */
    //normalised histograms
    c2->cd(); 
    //need to subtract 2* l2starb entries from trigg hists, due to adding them
    //above to get the total hists.
    h_trigg_1->Scale(1/(h_trigg_1->GetEntries()));  
    h_l2starb_1->Scale(1/h_l2starb_1->GetEntries());
    h_trigg_2->Scale(1/(h_trigg_2->GetEntries()));
    h_l2starb_2->Scale(1/h_l2starb_2->GetEntries());
    h_trigg_3->Scale(1/(h_trigg_3->GetEntries()));
    h_l2starb_3->Scale(1/h_l2starb_3->GetEntries());
    h_trigg_4->Scale(1/(h_trigg_4->GetEntries()));
    h_l2starb_4->Scale(1/h_l2starb_4->GetEntries());
    h_trigg_5->Scale(1/h_trigg_5->GetEntries());
    h_trigg_6->Scale(1/(h_trigg_6->GetEntries()));
    h_l2starb_6->Scale(1/h_l2starb_6->GetEntries());
    h_trigg_7->Scale(1/(h_trigg_7->GetEntries()));
    h_l2starb_7->Scale(1/h_l2starb_7->GetEntries());
 
    if (h_l2starb_1->GetMaximum() < h_trigg_1->GetMaximum()){
      h_trigg_1->SetMaximum(h_trigg_1->GetMaximum()*1.3);
    }else{
      h_trigg_1->SetMaximum(h_l2starb_1->GetMaximum()*1.3);
    }
    h_trigg_1->GetYaxis()->SetTitle("Arbitrary Units");
    h_trigg_1->GetYaxis()->SetTitleOffset(1.5);
    
    h_trigg_1->Draw("");
    h_l2starb_1->Draw("same");
    h_trigg_2->Draw("same");
    h_l2starb_2->Draw("same");
    h_trigg_3->Draw("same");
    h_l2starb_3->Draw("same");
    h_trigg_4->Draw("same");
    h_l2starb_4->Draw("same");
    h_trigg_5->Draw("same");
    h_trigg_6->Draw("same");
    h_l2starb_6->Draw("same");
    h_trigg_7->Draw("same");
    h_l2starb_7->Draw("same");

    TLegend* leg2;
    if(vars.at(i)=="iso7"){
      leg2 = new TLegend(0.6,0.5,0.89,0.69);
    }else{
      leg2 = new TLegend(0.6,0.7,0.89,0.89);
    }   
    leg2->AddEntry(h_trigg_1,trigg_names[0],"l");
    leg2->AddEntry(h_l2starb_1,trigg_names[0]+"_L2StarB","l");
    leg2->AddEntry(h_trigg_2,trigg_names[1],"l");
    leg2->AddEntry(h_l2starb_2,trigg_names[1]+"_L2StarB","l");
    leg2->AddEntry(h_trigg_3,trigg_names[2],"l");
    leg2->AddEntry(h_l2starb_3,trigg_names[2]+"_L2StarB","l");
    leg2->AddEntry(h_trigg_4,trigg_names[3],"l");
    leg2->AddEntry(h_l2starb_4,trigg_names[3]+"_L2StarB","l");
    leg2->AddEntry(h_trigg_5,trigg_names[4],"l");
    leg2->AddEntry(h_trigg_6,trigg_names[5],"l");
    leg2->AddEntry(h_l2starb_6,trigg_names[5]+"_L2StarB","l");
    leg2->AddEntry(h_trigg_7,trigg_names[6],"l");
    leg2->AddEntry(h_l2starb_7,trigg_names[6]+"_L2StarB","l");    
    leg2->SetFillColor(0);
    leg2->SetFillStyle(0);
    leg2->Draw();

    c2->SaveAs("all_triggs/"+vars.at(i)+"_norm.pdf");
    c2->Clear();
    
  }
}
