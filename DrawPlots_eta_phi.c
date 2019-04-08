

#include <math.h>



void DrawPlots_eta_phi()
{
    gStyle->SetOptStat(0);
    TString input_singlemu="singlemu_eff_0222.root";
    TString input_singlepi="singlepi_eff_0222.root";
    TString input_minimumbias="nuGun200PU_v1_test.root";
    TString input_singlemu108="singlemu_eff_0223_108bin.root";
    TString input_singlemu144="singlemu_eff_0223_144bin.root";
    TString input_singlemu216="singlemu_eff_0223_216bin.root";
    TString input_singlemu288="singlemu_eff_0223_288bin.root";



    TFile *f_singlemu = new TFile(input_singlemu);
    TFile *f_singlepi = new TFile(input_singlepi);
    TFile *f_minimumbias = new TFile(input_minimumbias);
    TFile *f_singlemu108 = new TFile(input_singlemu108);
    TFile *f_singlemu144 = new TFile(input_singlemu144);
    TFile *f_singlemu216 = new TFile(input_singlemu216);
    TFile *f_singlemu288 = new TFile(input_singlemu288);



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

    TH2F *h_singlemu_eff2_ETL_denominator = (TH2F*) f_singlemu->Get("ETLtrack_eta_vs_phi_denominator_recHits");
    TH2F *h_singlemu_eff2_ETL_numerator = (TH2F*) f_singlemu->Get("ETLtrack_eta_vs_phi_numerator_recHits");
    TH2F *h_singlemu_eff2_BTL_denominator = (TH2F*) f_singlemu->Get("BTLtrack_eta_vs_phi_denominator_recHits");
    TH2F *h_singlemu_eff2_BTL_numerator = (TH2F*) f_singlemu->Get("BTLtrack_eta_vs_phi_numerator_recHits");

    TH2F *h_singlepi_eff2_ETL_denominator = (TH2F*) f_singlepi->Get("ETLtrack_eta_vs_phi_denominator");
    TH2F *h_singlepi_eff2_ETL_numerator = (TH2F*) f_singlepi->Get("ETLtrack_eta_vs_phi_numerator");
    TH2F *h_singlepi_eff2_BTL_denominator = (TH2F*) f_singlepi->Get("BTLtrack_eta_vs_phi_denominator");
    TH2F *h_singlepi_eff2_BTL_numerator = (TH2F*) f_singlepi->Get("BTLtrack_eta_vs_phi_numerator");

    TH1F *h_singlemu_eff_108 = (TH1F*) f_singlemu108->Get("divide_BTLrecHits_eff_phi_numerator_by_BTLrecHits_eff_phi_denominator");
    TH1F *h_singlemu_eff_144 = (TH1F*) f_singlemu144->Get("divide_BTLrecHits_eff_phi_numerator_by_BTLrecHits_eff_phi_denominator");
    TH1F *h_singlemu_eff_216 = (TH1F*) f_singlemu216->Get("divide_BTLrecHits_eff_phi_numerator_by_BTLrecHits_eff_phi_denominator");
    TH1F *h_singlemu_eff_288 = (TH1F*) f_singlemu288->Get("divide_BTLrecHits_eff_phi_numerator_by_BTLrecHits_eff_phi_denominator");



    TCanvas *c1 = new TCanvas("c1","c1");
    c1->cd();
    h_singlemu_eff_108->SetTitle(";phi;eff");
    //h_singlemu_eff_108->SetAxisRange(-0.2,1.2,"X");
    h_singlemu_eff_108->SetMaximum(1.1);
    h_singlemu_eff_108->Draw("AP");
    TLatex l;
    l.SetTextSize(0.04);
    l.SetTextFont(61);
    l.DrawLatex(-3.2,1.15,"BTL Bin Number: 108 (36*3)"); 

    TCanvas *c2 = new TCanvas("c2","c2");
    c2->cd();
    h_singlemu_eff_144->SetTitle(";phi;eff");
    h_singlemu_eff_144->SetMaximum(1.1);
    h_singlemu_eff_144->Draw("AP");
    //TLatex l;
    l.SetTextSize(0.04);
    l.SetTextFont(61);
    l.DrawLatex(-3.2,1.15,"BTL Bin Number: 144 (36*4)"); 

    TCanvas *c3 = new TCanvas("c3","c3");
    c3->cd();
    h_singlemu_eff_216->SetTitle(";phi;eff");
    h_singlemu_eff_216->SetMaximum(1.1);
    h_singlemu_eff_216->Draw("AP");
    l.SetTextSize(0.04);
    l.SetTextFont(61);
    l.DrawLatex(-3.2,1.15,"BTL Bin Number: 216 (36*6)"); 

    TCanvas *c4 = new TCanvas("c4","c4");
    c4->cd();
    h_singlemu_eff_288->SetTitle(";phi;eff");
    h_singlemu_eff_288->SetMaximum(1.1);
    h_singlemu_eff_288->Draw("AP");
    l.SetTextSize(0.04);
    l.SetTextFont(61);
    l.DrawLatex(-3.2,1.15,"BTL Bin Number: 288 (36*8)"); 







    
    TCanvas *c5 = new TCanvas("c5","c5");
    c5->cd();
    h_singlemu_eff2_ETL_numerator->Divide(h_singlemu_eff2_ETL_denominator);
    h_singlemu_eff2_ETL_numerator->GetYaxis()->SetRangeUser(1.5,3.1);
    h_singlemu_eff2_ETL_numerator->GetXaxis()->SetRangeUser(-M_PI,M_PI);
    h_singlemu_eff2_ETL_numerator->GetZaxis()->SetRangeUser(0,1);

    h_singlemu_eff2_ETL_numerator->SetTitle(";phi;|eta|");
    h_singlemu_eff2_ETL_numerator->Draw("colz");
    TLatex latex5;
    latex5.SetTextSize(0.04);
    latex5.SetTextFont(61);
    latex5.DrawLatex(-3.2,3.15,"CMS");  

    latex5.SetTextSize(0.025);
    latex5.SetTextFont(52);
    latex5.DrawLatex(-2.5,3.15,"Phase-2 Simulation");

    latex5.SetTextSize(0.025);
    latex5.SetTextFont(61);
    latex5.DrawLatex(2,3.15,"singleMuon ETL eff");  


    TCanvas *c6 = new TCanvas("c6","c6");
    c6->cd();
    h_singlemu_eff2_BTL_numerator->Divide(h_singlemu_eff2_BTL_denominator);
    h_singlemu_eff2_BTL_numerator->GetYaxis()->SetRangeUser(0,1.5);
    h_singlemu_eff2_BTL_numerator->GetXaxis()->SetRangeUser(-M_PI,M_PI);
    h_singlemu_eff2_BTL_numerator->GetZaxis()->SetRangeUser(0,1);

    h_singlemu_eff2_BTL_numerator->SetTitle(";phi;|eta|");
    h_singlemu_eff2_BTL_numerator->Draw("colz");

    TLatex latex6;
    latex6.SetTextSize(0.04);
    latex6.SetTextFont(61);
    latex6.DrawLatex(-3.2,1.55,"CMS");  

    latex6.SetTextSize(0.025);
    latex6.SetTextFont(52);
    latex6.DrawLatex(-2.5,1.55,"Phase-2 Simulation");


    latex6.SetTextSize(0.025);
    latex6.SetTextFont(61);
    latex6.DrawLatex(2,1.55,"singleMuon BTL eff");  


    TCanvas *c7 = new TCanvas("c7","c7");
    c7->cd();
    h_singlepi_eff2_ETL_numerator->Divide(h_singlepi_eff2_ETL_denominator);
    h_singlepi_eff2_ETL_numerator->GetYaxis()->SetRangeUser(1.5,3.1);
    h_singlepi_eff2_ETL_numerator->GetXaxis()->SetRangeUser(-M_PI,M_PI);
    h_singlepi_eff2_ETL_numerator->GetZaxis()->SetRangeUser(0,1);

    h_singlepi_eff2_ETL_numerator->SetTitle(";phi;|eta|");
    h_singlepi_eff2_ETL_numerator->Draw("colz");
    TLatex latex7;
    latex7.SetTextSize(0.04);
    latex7.SetTextFont(61);
    latex7.DrawLatex(-3.2,3.15,"CMS");  

    latex7.SetTextSize(0.025);
    latex7.SetTextFont(52);
    latex7.DrawLatex(-2.5,3.15,"Phase-2 Simulation");

    latex7.SetTextSize(0.025);
    latex7.SetTextFont(61);
    latex7.DrawLatex(2,3.15,"singlePion ETL eff");  


    TCanvas *c8 = new TCanvas("c8","c8");
    c8->cd();
    h_singlepi_eff2_BTL_numerator->Divide(h_singlepi_eff2_BTL_denominator);
    h_singlepi_eff2_BTL_numerator->GetYaxis()->SetRangeUser(0,1.5);
    h_singlepi_eff2_BTL_numerator->GetXaxis()->SetRangeUser(-M_PI,M_PI);
    h_singlepi_eff2_BTL_numerator->GetZaxis()->SetRangeUser(0,1);

    h_singlepi_eff2_BTL_numerator->SetTitle(";phi;|eta|");
    h_singlepi_eff2_BTL_numerator->Draw("colz");

    TLatex latex8;
    latex8.SetTextSize(0.04);
    latex8.SetTextFont(61);
    latex8.DrawLatex(-3.2,1.55,"CMS");  

    latex8.SetTextSize(0.025);
    latex8.SetTextFont(52);
    latex8.DrawLatex(-2.5,1.55,"Phase-2 Simulation");


    latex8.SetTextSize(0.025);
    latex8.SetTextFont(61);
    latex8.DrawLatex(2,1.55,"singlePion BTL eff");  

    

    

}