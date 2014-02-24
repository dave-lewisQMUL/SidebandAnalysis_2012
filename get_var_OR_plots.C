#include "Riostream.h"
#include "TFile.h"
#include "TH1D.h"
#include <iostream>
#include <vector>
#include "TString.h"
#include "TCanvas.h"
#include "TLegend.h"

void get_var_OR_plots(){
  TFile root_file7("Root_files/trigger_count_hists_7.root");
  TFile root_file6("Root_files/trigger_count_hists_6.root");
  TFile root_file5("Root_files/trigger_count_hists_5.root");
  //TFile root_file4("trigger_count_hists_4.root");
  TFile root_file3("Root_files/trigger_count_hists_3.root");
  //TFile root_file2("trigger_count_hists_2.root");
  //TFile root_file1("trigger_count_hists_1.root");
  TCanvas* c1 = new TCanvas("c1","c1",600,600);;
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

  for (int v=0;v<vars.size();v++){
    if(vars.at(v)=="iso7"){
      c1->SetLogy(1);
    }else if(vars.at(v)=="DCA"){
      c1->SetLogy(1);
    }else if(vars.at(v)=="ZCA"){
      c1->SetLogy(1);
    }else if(vars.at(v)=="d0min"){
      c1->SetLogy(1);
    }else if(vars.at(v)=="d0max"){
      c1->SetLogy(1);
    }else{
      c1->SetLogy(0);
    }
    // TH1D* hist_1 = (TH1D*)root_file1.Get(vars.at(v)+"_OR");
    //TH1D* hist_2 = (TH1D*)root_file2.Get(vars.at(v)+"_OR");
    TH1D* hist_3 = (TH1D*)root_file3.Get(vars.at(v)+"_OR");
    //TH1D* hist_4 = (TH1D*)root_file4.Get(vars.at(v)+"_OR");
    TH1D* hist_5 = (TH1D*)root_file5.Get(vars.at(v)+"_OR");
    TH1D* hist_6 = (TH1D*)root_file6.Get(vars.at(v)+"_OR");
    TH1D* hist_7 = (TH1D*)root_file7.Get(vars.at(v)+"_OR");

    //hist_1->SetStats(0);
    //hist_2->SetStats(0);
    hist_3->SetStats(0);
    //hist_4->SetStats(0);
    hist_5->SetStats(0);
    hist_6->SetStats(0);
    hist_7->SetStats(0);

    //hist_1->SetLineColor(1);
    //hist_2->SetLineColor(2);
    hist_3->SetLineColor(1);
    //hist_4->SetLineColor(4);
    hist_5->SetLineColor(38);
    hist_6->SetLineColor(8);
    hist_7->SetLineColor(2);

    //hist_1->Draw("");
    //hist_2->Draw("same");
    hist_3->Draw("");
    //hist_4->Draw("same");
    hist_5->Draw("same");
    hist_6->Draw("same");
    hist_7->Draw("same");

    TLegend* leg1;
    if(vars.at(v)=="iso7"){
      leg1 = new TLegend(0.6,0.5,0.89,0.59);
    }else{
      leg1 = new TLegend(0.6,0.8,0.89,0.89);
    }
    //    leg1->AddEntry(hist_1,"1 trigger","l");
    //    leg1->AddEntry(hist_2,"2 triggers","l");    
    leg1->AddEntry(hist_3,"3 triggers","l");
    //    leg1->AddEntry(hist_4,"4 triggers","l");
    leg1->AddEntry(hist_5,"5 triggers","l");
    leg1->AddEntry(hist_6,"6 triggers","l");
    leg1->AddEntry(hist_7,"7 triggers","l");
    leg1->SetFillColor(0);
    leg1->SetFillStyle(0);
    leg1->Draw();

    c1->SaveAs("OR_"+vars.at(v)+".pdf");
    c1->Clear();
  }

}
