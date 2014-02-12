#include "TFile.h"
#include "TH1D.h"
#include <stdio>

void draw_plots(){

  TFile f("iso7-hist.root");
  TH1D *h = (TH1D*)f.Get("iso7_hist");
  std::cout << "Hello" << std::endl;
  h.Draw();

}
