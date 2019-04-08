





void CombineTwoPlotsFromTwoFile(TFile* h1,TFile* h2,TString h1name,TString h2name,TString graphtitle,Double_t* limits)
{
    TH1F *h1 = (TH1F*) f1->Get(h1name);
    TH1F *h2 = (TH1F*) f2->Get(h2name);
    TCanvas *c1 = new TCanvas("c1","c1");
    c1->cd();

    c1->SetGrid();
    c1->SetLogy();
    c1->SetTicks();
    h1->SetLineColor(kBlue);
    h2->SetLineColor(kRed);
    //h_minimumbias_ETL->SetLineColor(kBlack);
    h1->Scale(1./h_singlemu_ETL->GetEntries());
    h2->Scale(1./h_singlepi_ETL->GetEntries());
    //h_minimumbias_ETL->Scale(1./h_minimumbias_ETL->GetEntries());
    h1->SetTitle(graphtitle);
    //h_minimumbias_BTL->SetLineColor(kBlack);
    h1->SetLineWidth(3);
    h2->SetLineWidth(3);
    //h_minimumbias_ETL->SetLineWidth(3);
    h1->GetXaxis()->SetRangeUser(limits[0],limits[1]);
    h1->GetYaxis()->SetRangeUser(limits[2],limits[3]);
    h1->Draw("hist");
    h2->Draw("hist same");
    //h_minimumbias_ETL->Draw("hist same");
    //h_minimumbias_BTL->Draw("same");


    TLegend* leg = new TLegend(0.55,0.8,0.9,0.9);
    gStyle->SetLegendBorderSize(0);
    leg->AddEntry(h1,"single muons,  #LTE#GT = 0.9MeV");
    leg->AddEntry(h1,"single pions,  #LTE#GT = 4.4MeV");
    //leg->AddEntry(h_minimumbias_ETL,"minbias,   #LTE#GT = MeV");

    leg->Draw();

    TLatex latex;
    latex.SetTextSize(0.04);
    latex.SetTextFont(61);
    latex.DrawLatex(limits[4],limits[5],"CMS");  

    latex.SetTextSize(0.025);
    latex.SetTextFont(52);
    latex.DrawLatex(limits[6],limits[7],"Phase-2 Simulation");
}




void DrawPlots()
{
    gStyle->SetOptStat(0);
    TString input_singlemu="singlemu_eff_test_l.root";
    TString input_singlepi="singlepi_eff_test_l.root";
    TString input_minimumbias="nuGun200PU_v1_test.root";


    TFile *f_singlemu = new TFile(input_singlemu);
    TFile *f_singlepi = new TFile(input_singlepi);
    TFile *f_minimumbias = new TFile(input_minimumbias);


    TH1F *h_singlemu_BTL = (TH1F*) f_singlemu->Get("BTLrecHit_energy_h");
    TH1F *h_singlepi_BTL = (TH1F*) f_singlepi->Get("BTLrecHit_energy_h");
    //TH1F *h_minimumbias_BTL = (TH1F*) f_minimumbias->Get("BTLrecHit_energy_h");
    TH1F *h_singlemu_ETL = (TH1F*) f_singlemu->Get("ETLrecHit_energy_h");
    TH1F *h_singlepi_ETL = (TH1F*) f_singlepi->Get("ETLrecHit_energy_h");
    //TH1F *h_minimumbias_ETL = (TH1F*) f_minimumbias->Get("ETLrecHit_energy_h");
    TH1F *h_singlemu_eff_ETL = (TH1F*) f_singlemu->Get("divide_ETLtrack_phi_sel_by_ETLtrack_phi_1");
    TH1F *h_singlepi_eff_ETL = (TH1F*) f_singlepi->Get("divide_ETLtrack_phi_sel_by_ETLtrack_phi_1");
    //TH1F *h_minbias_eff_ETL = (TH1F*) f_singlemu->Get("divide_ETLtrack_eta_sel_by_ETLtrack_eta_1");
    TH1F *h_singlemu_eff_BTL = (TH1F*) f_singlemu->Get("divide_BTLtrack_phi_sel_by_BTLtrack_phi_1");
    TH1F *h_singlepi_eff_BTL = (TH1F*) f_singlepi->Get("divide_BTLtrack_phi_sel_by_BTLtrack_phi_1");
    //TH1F *h_minbias_eff_BTL = (TH1F*) f_singlemu->Get("divide_BTLtrack_eta_sel_by_BTLtrack_eta_1");

    TH2F *h_singlemu_eff2_ETL_denominator = (TH2F*) f_singlepi->Get("ETLtrack_eta_vs_pt_denominator");
    TH2F *h_singlemu_eff2_ETL_numerator = (TH2F*) f_singlepi->Get("ETLtrack_eta_vs_pt_numerator");
    TH2F *h_singlemu_eff2_BTL_denominator = (TH2F*) f_singlepi->Get("BTLtrack_eta_vs_pt_denominator");
    TH2F *h_singlemu_eff2_BTL_numerator = (TH2F*) f_singlepi->Get("BTLtrack_eta_vs_pt_numerator");

    TH2F *h_singlepi_eff2_ETL_denominator = (TH2F*) f_singlepi->Get("ETLtrack_eta_vs_pt_denominator");
    TH2F *h_singlepi_eff2_ETL_numerator = (TH2F*) f_singlepi->Get("ETLtrack_eta_vs_pt_numerator");
    TH2F *h_singlepi_eff2_BTL_denominator = (TH2F*) f_singlepi->Get("BTLtrack_eta_vs_pt_denominator");
    TH2F *h_singlepi_eff2_BTL_numerator = (TH2F*) f_singlepi->Get("BTLtrack_eta_vs_pt_numerator");



    TCanvas *c1 = new TCanvas("c1","c1");
    c1->cd();
    /*h_singlemu_BTL->SetLineColor(kBlue);
    h_singlepi_BTL->SetLineColor(kRed);
    h_minimumbias_BTL->SetLineColor(kBlack);
    h_singlemu_BTL->Draw();
    h_singlepi_BTL->Draw("same");
    h_minimumbias_BTL->Draw("same");*/

    c1->SetGrid();
    c1->SetLogy();
    c1->SetTicks();
    h_singlemu_ETL->SetLineColor(kBlue);
    h_singlepi_ETL->SetLineColor(kRed);
    //h_minimumbias_ETL->SetLineColor(kBlack);
    h_singlemu_ETL->Scale(1./h_singlemu_ETL->GetEntries());
    h_singlepi_ETL->Scale(1./h_singlepi_ETL->GetEntries());
    //h_minimumbias_ETL->Scale(1./h_minimumbias_ETL->GetEntries());
    h_singlemu_ETL->SetTitle("");
    h_singlemu_ETL->GetXaxis()->SetTitle("ETL   #scale[0.8]{#sum} E_{recHit}^{#DeltaR<0.05}[MeV]");
    h_singlemu_ETL->GetYaxis()->SetTitle("Event Fraction / 0.5MeV");
    //h_minimumbias_BTL->SetLineColor(kBlack);
    h_singlemu_ETL->SetLineWidth(3);
    h_singlepi_ETL->SetLineWidth(3);
    //h_minimumbias_ETL->SetLineWidth(3);
    h_singlemu_ETL->GetXaxis()->SetRangeUser(0,0.6);
    h_singlemu_ETL->GetYaxis()->SetRangeUser(1e-05,10);
    h_singlemu_ETL->Draw("hist");
    h_singlepi_ETL->Draw("hist same");
    //h_minimumbias_ETL->Draw("hist same");
    //h_minimumbias_BTL->Draw("same");


    TLegend* leg = new TLegend(0.55,0.8,0.9,0.9);
    gStyle->SetLegendBorderSize(0);
    leg->AddEntry(h_singlemu_ETL,"single muons,  #LTE#GT = 0.9MeV");
    leg->AddEntry(h_singlepi_ETL,"single pions,  #LTE#GT = 4.4MeV");
    //leg->AddEntry(h_minimumbias_ETL,"minbias,   #LTE#GT = MeV");

    leg->Draw();

    TLatex latex;
    latex.SetTextSize(0.04);
    latex.SetTextFont(61);
    latex.DrawLatex(0,11,"CMS");  

    latex.SetTextSize(0.025);
    latex.SetTextFont(52);
    latex.DrawLatex(0.1,11,"Phase-2 Simulation");


    TCanvas *c2 = new TCanvas("c2","c2");
    c2->cd();
    c2->SetGrid();
    //h_singlemu_eff_BTL->SetTitle("");
    h_singlemu_eff_BTL->SetTitle(";phi;efficiency");
    //h_singlemu_eff_BTL->GetYaxis()->SetTitle("efficiency");
    h_singlemu_eff_BTL->SetLineColor(kBlue);
    //h_singlemu_eff_BTL->SetLineWidth(5);
    h_singlepi_eff_BTL->SetLineColor(kRed);
    h_singlemu_eff_BTL->Draw("AP");
    h_singlepi_eff_BTL->Draw("sameP");
    TLegend* leg2 = new TLegend(0.55,0.8,0.9,0.9);
    gStyle->SetLegendBorderSize(0);
    leg2->AddEntry(h_singlemu_eff_BTL,"single muons");
    leg2->AddEntry(h_singlepi_eff_BTL,"single pions");
    //leg->AddEntry(h_minimumbias_ETL,"minbias,   #LTE#GT = MeV");

    leg2->Draw();

    TLatex latex2;
    latex2.SetTextSize(0.04);
    latex2.SetTextFont(61);
    latex2.DrawLatex(-3.75,1.15,"CMS");  

    latex2.SetTextSize(0.025);
    latex2.SetTextFont(52);
    latex2.DrawLatex(-3.2,1.15,"Phase-2 Simulation");



    /*TCanvas *c3 = new TCanvas("c3","c3");
    c3->cd();
    h_singlemu_eff2_ETL_numerator->Divide(h_singlemu_eff2_ETL_denominator);
    h_singlemu_eff2_ETL_numerator->GetYaxis()->SetRangeUser(1.5,3.1);
    h_singlemu_eff2_ETL_numerator->GetZaxis()->SetRangeUser(0.98,1);

    h_singlemu_eff2_ETL_numerator->SetTitle(";pT;eta");
    h_singlemu_eff2_ETL_numerator->Draw("colz");
    TLatex latex3;
    latex3.SetTextSize(0.04);
    latex3.SetTextFont(61);
    latex3.DrawLatex(0,3.15,"CMS");  

    latex3.SetTextSize(0.025);
    latex3.SetTextFont(52);
    latex3.DrawLatex(1,3.15,"Phase-2 Simulation");

    latex3.SetTextSize(0.04);
    latex3.SetTextFont(61);
    latex3.DrawLatex(3,3.15,"ETL eff");  


    TCanvas *c4 = new TCanvas("c4","c4");
    c4->cd();
    h_singlemu_eff2_BTL_numerator->Divide(h_singlemu_eff2_BTL_denominator);
    h_singlemu_eff2_BTL_numerator->GetYaxis()->SetRangeUser(0,1.5);
    h_singlemu_eff2_BTL_numerator->GetZaxis()->SetRangeUser(0.5,1);

    h_singlemu_eff2_BTL_numerator->SetTitle(";pT;eta");
    h_singlemu_eff2_BTL_numerator->Draw("colz");

    TLatex latex4;
    latex4.SetTextSize(0.04);
    latex4.SetTextFont(61);
    latex4.DrawLatex(0,1.55,"CMS");  

    latex4.SetTextSize(0.025);
    latex4.SetTextFont(52);
    latex4.DrawLatex(1,1.55,"Phase-2 Simulation");


    latex4.SetTextSize(0.04);
    latex4.SetTextFont(61);
    latex4.DrawLatex(3,1.55,"BTL eff");  */

    
    TCanvas *c5 = new TCanvas("c5","c5");
    c5->cd();
    h_singlepi_eff2_ETL_numerator->Divide(h_singlepi_eff2_ETL_denominator);
    h_singlepi_eff2_ETL_numerator->GetYaxis()->SetRangeUser(1.5,3.1);
    h_singlepi_eff2_ETL_numerator->GetXaxis()->SetRangeUser(0,10);
    h_singlepi_eff2_ETL_numerator->GetZaxis()->SetRangeUser(0.5,1);

    h_singlepi_eff2_ETL_numerator->SetTitle(";pT;eta");
    h_singlepi_eff2_ETL_numerator->Draw("colz");
    TLatex latex5;
    latex5.SetTextSize(0.04);
    latex5.SetTextFont(61);
    latex5.DrawLatex(0,3.15,"CMS");  

    latex5.SetTextSize(0.025);
    latex5.SetTextFont(52);
    latex5.DrawLatex(1,3.15,"Phase-2 Simulation");

    latex5.SetTextSize(0.04);
    latex5.SetTextFont(61);
    latex5.DrawLatex(3,3.15,"ETL eff");  


    TCanvas *c6 = new TCanvas("c6","c6");
    c6->cd();
    h_singlepi_eff2_BTL_numerator->Divide(h_singlepi_eff2_BTL_denominator);
    h_singlepi_eff2_BTL_numerator->GetYaxis()->SetRangeUser(0,1.5);
    h_singlepi_eff2_BTL_numerator->GetXaxis()->SetRangeUser(0,10);
    h_singlepi_eff2_BTL_numerator->GetZaxis()->SetRangeUser(0.5,1);

    h_singlepi_eff2_BTL_numerator->SetTitle(";pT;eta");
    h_singlepi_eff2_BTL_numerator->Draw("colz");

    TLatex latex6;
    latex6.SetTextSize(0.04);
    latex6.SetTextFont(61);
    latex6.DrawLatex(0,1.55,"CMS");  

    latex6.SetTextSize(0.025);
    latex6.SetTextFont(52);
    latex6.DrawLatex(1,1.55,"Phase-2 Simulation");


    latex6.SetTextSize(0.04);
    latex6.SetTextFont(61);
    latex6.DrawLatex(3,1.55,"BTL eff");  

    

}