#include "Riostream.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TFile.h"
#include "TLegend.h"
#include <vector>

void combine_plots()
{

  TFile trigg_hists("TriggPlots/Trigg_hists_2.root");
  TFile L2StarB_hists("L2StarBPlots/L2StarB_hists_2.root");

  TCanvas* c1 = new TCanvas("c1","c1",600,600);

  std::vector<TString> vars;
  vars.clear();

  //  vars.push_back("iso7");
  vars.push_back("Lxy");
  vars.push_back("DR");
  vars.push_back("a_2d");
  vars.push_back("pTime");
  vars.push_back("logChi2z");
  vars.push_back("logChi2xy");
  vars.push_back("pT");
  //  vars.push_back("DCA");
  //  vars.push_back("ZCA");
  //  vars.push_back("d0min");
  //  vars.push_back("d0max");
  vars.push_back("Plng_min");
  vars.push_back("Plng_max");

  for (int v=0; v<vars.size(); ++v)
    {
      TH1D* h_trigg = (TH1D*)trigg_hists.Get(vars.at(v)+"_hist");
      TH1D* h_L2StarB = (TH1D*)L2StarB_hists.Get(vars.at(v)+"_hist");
      
      h_L2StarB->SetStats(0);
      h_trigg->SetStats(0);
      h_L2StarB->GetYaxis()->SetTitleOffset(1.5);
      h_L2StarB->GetYaxis()->SetTitle("Arbitrary Units");
      
      Double_t n_trigg = h_trigg->GetEntries();
      Double_t n_L2StarB = h_L2StarB->GetEntries();
      if (n_trigg) h_trigg->Scale(1/n_trigg);
      if (n_L2StarB) h_L2StarB->Scale(1/n_L2StarB);
      if (h_L2StarB->GetMaximum() < h_trigg->GetMaximum()){
	h_L2StarB->SetMaximum(h_trigg->GetMaximum()*1.2);
      }else{
	h_L2StarB->SetMaximum(h_L2StarB->GetMaximum()*1.2);
      }
      
      h_L2StarB->Draw("");
      h_trigg->Draw("same");
      h_L2StarB->SetMarkerColor(2);
      h_L2StarB->SetLineColor(2);

      TLegend* leg = new TLegend(0.6,0.8,0.89,0.89);
      leg->AddEntry(h_trigg, "Trigg","l");
      leg->AddEntry(h_L2StarB, "L2StarB","l");
      leg->SetFillColor(0);
      leg->SetFillStyle(0);
      leg->Draw();
      /*
      if (vars.at(v).CompareTo("iso7") || vars.at(v).CompareTo("DCA") || 
	  vars.at(v).CompareTo("ZCA") || vars.at(v).CompareTo("d0min") ||
	  vars.at(v).CompareTo("d0max"))
	{
	  c1->SetLogy(1);
	  }
      */
      c1->SaveAs("Combined_"+vars.at(v)+"_plot_norm.eps");
    }
}
