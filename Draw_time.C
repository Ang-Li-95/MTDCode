void Draw_time()
{
    gStyle->SetOptStat(0);
    TString input_singlemu="singlemu_D35_relVal_MTD_0431_6GeV_pT_match_2.root";
    TString input_singlepi="singlemu_D35_relVal_MTD_0431_6GeV_pT_match_2.root";
    //TString input_minimumbias="nuGun200PU_v1_test.root";


    TFile *f_singlemu = new TFile(input_singlemu);
    TFile *f_singlepi = new TFile(input_singlepi);
    //TFile *f_minimumbias = new TFile(input_minimumbias);


    TH1F *h_singlemu_BTL = (TH1F*) f_singlemu->Get("BTLrecHits_length_1");
    TH1F *h_singlepi_BTL = (TH1F*) f_singlepi->Get("BTLrecHits_length_1");
    //TH1F *h_minimumbias_BTL = (TH1F*) f_minimumbias->Get("BTLrecHit_energy_h");
    TH1F *h_singlemu_ETL = (TH1F*) f_singlemu->Get("BTLrecHits_length_2");
    TH1F *h_singlepi_ETL = (TH1F*) f_singlepi->Get("BTLrecHits_length_2");
    //TH1F *h_minimumbias_ETL = (TH1F*) f_minimumbias->Get("ETLrecHit_energy_h");
    TH1F *h_singlemu_eff_ETL = (TH1F*) f_singlemu->Get("BTLrecHits_total_length");
    TH1F *h_singlepi_eff_ETL = (TH1F*) f_singlepi->Get("BTLrecHits_total_length");
    //TH1F *h_minbias_eff_ETL = (TH1F*) f_singlemu->Get("divide_ETLtrack_eta_sel_by_ETLtrack_eta_1");
    TH1F *h_singlemu_eff_BTL = (TH1F*) f_singlemu->Get("BTLrecHits_length1_minus_length2");
    TH1F *h_singlepi_eff_BTL = (TH1F*) f_singlepi->Get("BTLrecHits_length1_minus_length2");
    //TH1F *h_minbias_eff_BTL = (TH1F*) f_singlemu->Get("divide_BTLtrack_eta_sel_by_BTLtrack_eta_1");
    TH2F *h1 = (TH2F*)f_singlemu->Get("BTLrecHits_x1_vs_x2");
    TH2F *h2 = (TH2F*)f_singlepi->Get("BTLrecHits_x1_vs_x2");



    TCanvas *c1 = new TCanvas("c1","c1");
    c1->cd();
    h_singlemu_BTL->SetLineColor(kBlue);
    h_singlepi_BTL->SetLineColor(kRed);
    h_singlemu_BTL->Scale(1./h_singlemu_BTL->GetEntries());
    h_singlepi_BTL->Scale(1./h_singlepi_BTL->GetEntries());
    h_singlemu_BTL->SetTitle("distance to left;distance[m];fraction of events");
    //h_singlemu_ETL->SetLineWidth(3);
    //h_singlepi_ETL->SetLineWidth(3);   
    h_singlemu_BTL->Draw("hist");
    //h_singlepi_BTL->Draw("hist same");
   


    TLegend* leg = new TLegend(0.55,0.8,0.9,0.9);
    gStyle->SetLegendBorderSize(0);
    leg->AddEntry(h_singlemu_BTL,"track_pT>6GeV");
    leg->AddEntry(h_singlepi_BTL,"all good tracks");
    //leg->AddEntry(h_minimumbias_ETL,"minbias,   #LTE#GT = MeV");

    //leg->Draw();


    TCanvas *c2 = new TCanvas("c2","c2");
    c2->cd();
    h_singlemu_ETL->SetLineColor(kBlue);
    h_singlepi_ETL->SetLineColor(kRed);
    h_singlemu_ETL->Scale(1./h_singlemu_ETL->GetEntries());
    h_singlepi_ETL->Scale(1./h_singlepi_ETL->GetEntries());
    h_singlemu_ETL->SetTitle("distance to right;distance[m];fraction of events");
    //h_singlemu_ETL->SetLineWidth(3);
    //h_singlepi_ETL->SetLineWidth(3);   
    h_singlemu_ETL->Draw("hist");
    //h_singlepi_ETL->Draw("hist same");
   


    TLegend* leg2 = new TLegend(0.55,0.8,0.9,0.9);
    gStyle->SetLegendBorderSize(0);
    leg2->AddEntry(h_singlemu_ETL,"track_pT>6GeV");
    leg2->AddEntry(h_singlepi_ETL,"all good tracks");
    //leg->AddEntry(h_minimumbias_ETL,"minbias,   #LTE#GT = MeV");

    //leg2->Draw();


    TCanvas *c3 = new TCanvas("c3","c3");
    c3->cd();
    h_singlemu_eff_ETL->SetLineColor(kBlue);
    h_singlepi_eff_ETL->SetLineColor(kRed);
    h_singlemu_eff_ETL->Scale(1./h_singlemu_eff_ETL->GetEntries());
    h_singlepi_eff_ETL->Scale(1./h_singlepi_eff_ETL->GetEntries());
    h_singlemu_eff_ETL->SetTitle("total distance;distance[m];fraction of events");
    //h_singlemu_ETL->SetLineWidth(3);
    //h_singlepi_ETL->SetLineWidth(3);   
    h_singlemu_eff_ETL->Draw("hist");
    //h_singlepi_eff_ETL->Draw("hist same");
   


    TLegend* leg3 = new TLegend(0.55,0.8,0.9,0.9);
    gStyle->SetLegendBorderSize(0);
    leg3->AddEntry(h_singlemu_eff_ETL,"track_pT>6GeV");
    leg3->AddEntry(h_singlepi_eff_ETL,"all good tracks");
    //leg->AddEntry(h_minimumbias_ETL,"minbias,   #LTE#GT = MeV");

    //leg3->Draw();

    TCanvas *c4 = new TCanvas("c4","c4");
    c4->cd();
    h_singlemu_eff_BTL->SetLineColor(kBlue);
    h_singlepi_eff_BTL->SetLineColor(kRed);
    h_singlemu_eff_BTL->Scale(1./h_singlemu_eff_BTL->GetEntries());
    h_singlepi_eff_BTL->Scale(1./h_singlepi_eff_BTL->GetEntries());
    h_singlemu_eff_BTL->SetTitle("distance difference;distance[m];fraction of events");
    //h_singlemu_ETL->SetLineWidth(3);
    //h_singlepi_ETL->SetLineWidth(3);   
    h_singlemu_eff_BTL->Draw("hist");
    //h_singlepi_eff_BTL->Draw("hist same");
   


    TLegend* leg4 = new TLegend(0.55,0.8,0.9,0.9);
    gStyle->SetLegendBorderSize(0);
    leg4->AddEntry(h_singlemu_ETL,"track_pT>6GeV");
    leg4->AddEntry(h_singlepi_ETL,"all good tracks");
    //leg->AddEntry(h_minimumbias_ETL,"minbias,   #LTE#GT = MeV");

    //leg4->Draw();


    TCanvas *c5 = new TCanvas("c5","c5");
    c5->cd();
    h1->SetTitle("BTL recHits D35(track_pT>6GeV);x2[m];x1[m]");
    h1->GetXaxis()->SetRangeUser(-0.2,0.2);
    h1->GetYaxis()->SetRangeUser(-0.2,0.2);

    //h1->Draw("colz");

    TCanvas *c6 = new TCanvas("c6","c6");
    c6->cd();
    h2->SetTitle("BTL recHits D35(all good tracks);x2[m];x1[m]");
    h2->GetXaxis()->SetRangeUser(-0.2,0.2);
    h2->GetYaxis()->SetRangeUser(-0.2,0.2);
    h2->Draw("colz");

}
