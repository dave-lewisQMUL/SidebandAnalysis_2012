#include "Riostream.h"
#include "TString.h"
#include "TFile.h"
#include <iostream>
#include <fstream>
#include "TH1D.h"
#include "TCanvas.h"
#include "TAxis.h"

void plot_trig_counts(){

  TCanvas* c1 = new TCanvas("c1","c1",600,600);
  TFile root_file("trigger_count_hists.root");
  TH1D* trig_OR = (TH1D*)root_file.Get("trigg_OR");
  trig_OR->GetYaxis()->SetTitleOffset(1.5);
  trig_OR->GetYaxis()->SetTitle("Num. events");
  trig_OR->GetXaxis()->SetTitle("Period");
  trig_OR->GetXaxis()->SetBinLabel(1,"A");
  trig_OR->GetXaxis()->SetBinLabel(3,"B");
  trig_OR->GetXaxis()->SetBinLabel(5,"C");
  trig_OR->GetXaxis()->SetBinLabel(7,"D");
  trig_OR->GetXaxis()->SetBinLabel(9,"E");
  trig_OR->GetXaxis()->SetBinLabel(11,"G");
  trig_OR->GetXaxis()->SetBinLabel(13,"H");
  trig_OR->GetXaxis()->SetBinLabel(15,"I");
  trig_OR->GetXaxis()->SetBinLabel(17,"J");
  trig_OR->GetXaxis()->SetBinLabel(19,"L");
  trig_OR->Draw();
  c1->SaveAs("trigg_or.pdf");
  c1->Clear();

  TH1D* hist_A = (TH1D*)root_file.Get("hist_A");
  hist_A->GetYaxis()->SetTitleOffset(1.5);
  hist_A->GetYaxis()->SetTitle("Num. events");
  hist_A->GetXaxis()->SetLabelSize(0.02);
  hist_A->Draw();
  c1->SaveAs("hist_A.pdf");
  c1->Clear();
  TH1D* hist_B = (TH1D*)root_file.Get("hist_B");
  hist_B->GetYaxis()->SetTitleOffset(1.5);
  hist_B->GetYaxis()->SetTitle("Num. events");
  hist_B->GetXaxis()->SetLabelSize(0.02);
  hist_B->Draw();
  c1->SaveAs("hist_B.pdf");
  c1->Clear();
  TH1D* hist_C = (TH1D*)root_file.Get("hist_C");
  hist_C->GetYaxis()->SetTitleOffset(1.5);
  hist_C->GetYaxis()->SetTitle("Num. events");
  hist_C->GetXaxis()->SetLabelSize(0.02);
  hist_C->Draw();
  c1->SaveAs("hist_C.pdf");
  c1->Clear();
  TH1D* hist_D = (TH1D*)root_file.Get("hist_D");
  hist_D->GetYaxis()->SetTitleOffset(1.5);
  hist_D->GetYaxis()->SetTitle("Num. events");
  hist_D->GetXaxis()->SetLabelSize(0.02);
  hist_D->Draw();
  c1->SaveAs("hist_D.pdf");
  c1->Clear();
  TH1D* hist_E = (TH1D*)root_file.Get("hist_E");
  hist_E->GetYaxis()->SetTitleOffset(1.5);
  hist_E->GetYaxis()->SetTitle("Num. events");
  hist_E->GetXaxis()->SetLabelSize(0.02);
  hist_E->Draw();
  c1->SaveAs("hist_E.pdf");
  c1->Clear();
  TH1D* hist_G = (TH1D*)root_file.Get("hist_G");
  hist_G->GetYaxis()->SetTitleOffset(1.5);
  hist_G->GetYaxis()->SetTitle("Num. events");
  hist_G->GetXaxis()->SetLabelSize(0.02);
  hist_G->Draw();
  c1->SaveAs("hist_G.pdf");
  c1->Clear();
  TH1D* hist_H = (TH1D*)root_file.Get("hist_H");
  hist_H->GetYaxis()->SetTitleOffset(1.5);
  hist_H->GetYaxis()->SetTitle("Num. events");
  hist_H->GetXaxis()->SetLabelSize(0.02);
  hist_H->Draw();
  c1->SaveAs("hist_H.pdf");
  c1->Clear();
  TH1D* hist_I = (TH1D*)root_file.Get("hist_I");
  hist_I->GetYaxis()->SetTitleOffset(1.5);
  hist_I->GetYaxis()->SetTitle("Num. events");
  hist_I->GetXaxis()->SetLabelSize(0.02);
  hist_I->Draw();
  c1->SaveAs("hist_I.pdf");
  c1->Clear();
  TH1D* hist_J = (TH1D*)root_file.Get("hist_J");
  hist_J->GetYaxis()->SetTitleOffset(1.5);
  hist_J->GetYaxis()->SetTitle("Num. events");
  hist_J->GetXaxis()->SetLabelSize(0.02);
  hist_J->Draw();
  c1->SaveAs("hist_J.pdf");
  c1->Clear();
  TH1D* hist_L = (TH1D*)root_file.Get("hist_L");
  hist_L->GetYaxis()->SetTitleOffset(1.5);
  hist_L->GetYaxis()->SetTitle("Num. events");
  hist_L->GetXaxis()->SetLabelSize(0.02);
  hist_L->Draw();
  c1->SaveAs("hist_L.pdf");
  c1->Clear();


}
