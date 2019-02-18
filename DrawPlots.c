





void DrawPlots()
{
    gStyle->SetOptStat(0);
    TString input_singlemu="singlemu_eff_test_l.root";
    TString input_singlepi="singlepi_eff_test_l.root";
    //TString input_minimumbias="nuGun200PU_v1_test.root";


    TFile *f_singlemu = new TFile(input_singlemu);
    TFile *f_singlepi = new TFile(input_singlepi);
    //TFile *f_minimumbias = new TFile(input_minimumbias);


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



    

}