
#include <math.h>

using namespace std;

void Draweff()
{
    gStyle->SetOptStat(0);
    TString input_singlemu_barz="singlemu_100k_D35_0409_1.root";
    TString input_singlemu_barphi="singlemu_D39_100k_0409_1.root";
    TFile *f_z = new TFile(input_singlemu_barz);
    TFile *f_phi = new TFile(input_singlemu_barphi);


    TH1F *h_eff_z = (TH1F*)f_z->Get("divide_BTLtrack_phi_sel_by_BTLtrack_phi_1");           //eff vs. phi
    TH1F *h_eff_phi = (TH1F*)f_phi->Get("divide_BTLtrack_phi_sel_by_BTLtrack_phi_1");       //eff vs. phi
    TH1F *h_eff_eta_phi = (TH1F*)f_phi->Get("divide_BTLtrack_eta_sel_by_BTLtrack_eta_1");   //eff vs. eta
    TH1F *h_eff_eta_z = (TH1F*)f_z->Get("divide_BTLtrack_eta_sel_by_BTLtrack_eta_1");       //eff vs. eta
    TH1F *h_eff_pt_z = (TH1F*)f_z->Get("divide_BTLtrack_pt_numerator_by_BTLtrack_pt_denominator");
    TH1F *h_eff_pt_phi = (TH1F*)f_phi->Get("divide_BTLtrack_pt_numerator_by_BTLtrack_pt_denominator");
    TH1F *h_pt_z = (TH1F*)f_z->Get("BTLtrack_pt_denominator");
    TH1F *h_pt_phi = (TH1F*)f_phi->Get("BTLtrack_pt_denominator");
    TH1F *h_phi_z = (TH1F*)f_z->Get("BTLtrack_phi_1");
    TH1F *h_phi_phi = (TH1F*)f_phi->Get("BTLtrack_phi_1");
    TH1F *h_eta_z = (TH1F*)f_z->Get("BTLtrack_eta_1");
    TH1F *h_eta_phi = (TH1F*)f_phi->Get("BTLtrack_eta_1");
    TH1F *h_pt_z_sel = (TH1F*)f_z->Get("BTLtrack_pt_numerator");
    TH1F *h_pt_phi_sel = (TH1F*)f_phi->Get("BTLtrack_pt_numerator");
    TH1F *h_phi_z_sel = (TH1F*)f_z->Get("BTLtrack_phi_sel");
    TH1F *h_phi_phi_sel = (TH1F*)f_phi->Get("BTLtrack_phi_sel");
    TH1F *h_eta_z_sel = (TH1F*)f_z->Get("BTLtrack_eta_sel");
    TH1F *h_eta_phi_sel = (TH1F*)f_phi->Get("BTLtrack_eta_sel");
    TH1F *h1 = new TH1F("h1","h1",100,-M_PI,M_PI);
    TH1F *h2 = new TH1F("h2","h2",100,-M_PI,M_PI);
    TH1F *h3 = new TH1F("h3","h3",100,-M_PI,M_PI);
    TH1F *h4 = new TH1F("h4","h4",100,-M_PI,M_PI);
    TH1F *h5 = new TH1F("h5","h5",100,0,1.5);
    TH1F *h6 = new TH1F("h6","h6",100,-M_PI,M_PI);

    double eff = 0;
    double err = 0;


    TCanvas *c1 = new TCanvas("c1","c1");
    c1->cd();
    h_eff_z->SetLineColor(kBlue);
    h_eff_phi->SetLineColor(kRed);
    h1->SetTitle("BTL efficiency;phi;efficiency");
    //h_eff_z->Draw();
    //h->GetXaxis()->SetLimits(5.,11.);
    h1->Draw();
    h_eff_z->Draw("Psame");
    //h_eff_phi->Draw("same");
    TLegend* leg = new TLegend(0.1,0.1,0.25,0.2);
    gStyle->SetLegendBorderSize(0);
    leg->AddEntry(h_eff_z,"bars in z");
    leg->AddEntry(h_eff_phi,"bars in phi");
    //leg->Draw();

    c1->Update();
    eff = (h_pt_z_sel->GetEntries())/(h_pt_z->GetEntries());
    err = eff*sqrt(1/(h_pt_z_sel->GetEntries())+1/(h_pt_z->GetEntries()));
    cout << "for eff_pt: (barinz) eff= " << eff << " +- " << err << endl;
    eff = (h_pt_phi_sel->GetEntries())/(h_pt_phi->GetEntries());
    err = eff*sqrt(1/(h_pt_phi_sel->GetEntries())+1/(h_pt_phi->GetEntries()));
    cout << "for eff_pt: (barinphi) eff= " << eff << " +- " << err << endl;

    


    TCanvas *c2 = new TCanvas("c2","c2");
    c2->cd();
    h_eff_eta_z->SetLineColor(kBlue);
    h_eff_eta_phi->SetLineColor(kRed);
    h2->SetTitle("BTL efficiency;|eta|;efficiency");
    //h_eff_z->Draw();
    //h->GetXaxis()->SetLimits(0.,3.);
    h2->Draw();
    h2->GetXaxis()->SetRangeUser(0,1.5);
    h_eff_eta_z->Draw("P SAME");
    //h_eff_eta_phi->Draw("same");
    TLegend* leg2 = new TLegend(0.1,0.1,0.25,0.2);
    gStyle->SetLegendBorderSize(0);
    leg2->AddEntry(h_eff_eta_z,"bars in z");
    leg2->AddEntry(h_eff_eta_phi,"bars in phi");
    //leg2->Draw();

    c2->Update();

    eff = (h_eta_z_sel->GetEntries())/(h_eta_z->GetEntries());
    err = eff*sqrt(1/(h_eta_z_sel->GetEntries())+1/(h_eta_z->GetEntries()));
    cout << "for eff_eta: (barinz) eff= " << eff << " +- " << err << endl;
    eff = (h_eta_phi_sel->GetEntries())/(h_eta_phi->GetEntries());
    err = eff*sqrt(1/(h_eta_phi_sel->GetEntries())+1/(h_eta_phi->GetEntries()));
    cout << "for eff_eta: (barinphi) eff= " << eff << " +- " << err << endl;



    TCanvas *c3 = new TCanvas("c3","c3");
    c3->cd();
    h_eff_pt_z->SetLineColor(kBlue);
    h_eff_pt_phi->SetLineColor(kRed);
    h3->SetTitle("BTL efficiency;pT;efficiency");
    //h_eff_z->Draw();
    h3->GetXaxis()->SetLimits(0.,11.);
    h3->Draw();
    h_eff_pt_z->Draw("Psame");
    //h_eff_pt_phi->Draw("APsame");
    TLegend* leg3 = new TLegend(0.1,0.1,0.25,0.2);
    gStyle->SetLegendBorderSize(0);
    leg3->AddEntry(h_eff_pt_z,"bars in z");
    leg3->AddEntry(h_eff_pt_phi,"bars in phi");
    //leg3->Draw();

    c3->Update();

    eff = (h_phi_z_sel->GetEntries())/(h_phi_z->GetEntries());
    err = eff*sqrt(1/(h_phi_z_sel->GetEntries())+1/(h_phi_z->GetEntries()));
    cout << "for eff_phi: (barinz) eff= " << eff << " +- " << err << endl;
    eff = (h_phi_phi_sel->GetEntries())/(h_phi_phi->GetEntries());
    err = eff*sqrt(1/(h_phi_phi_sel->GetEntries())+1/(h_phi_phi->GetEntries()));
    cout << "for eff_phi: (barinphi) eff= " << eff << " +- " << err << endl;



    TCanvas *c4 = new TCanvas("c4","c4");
    c4->cd();
    h_pt_z->SetLineColor(kBlue);
    h_pt_phi->SetLineColor(kRed);
    h_pt_phi->SetTitle("BTL pT distribution;pT;scaled units");
    //h_eff_z->Draw();
    h4->GetXaxis()->SetLimits(0.,11.);
    //h4->Draw();
    h_pt_z->Scale(1./(h_pt_z->GetEntries()));
    h_pt_phi->Scale(1./(h_pt_phi->GetEntries()));

    //h_pt_phi->Scale(100./(h_pt_phi->GetEntries()));
    h_pt_phi->Draw("hist");
    h_pt_z->Draw("same hist");
    TLegend* leg4 = new TLegend(0.1,0.1,0.25,0.2);
    gStyle->SetLegendBorderSize(0);
    leg4->AddEntry(h_pt_z,"bars in z");
    leg4->AddEntry(h_pt_phi,"bars in phi");
    leg4->Draw();

    c4->Update();


    TCanvas *c5 = new TCanvas("c5","c5");
    c5->cd();
    h_eta_z->SetLineColor(kBlue);
    h_eta_phi->SetLineColor(kRed);
    h_eta_z->SetTitle("BTL eta distribution;|eta|;scaled units");
    //h_eff_z->Draw();
    h5->GetXaxis()->SetLimits(0.,1.5);
    h5->Draw();
    h_eta_z->Scale(1./(h_eta_z->GetEntries()));
    h_eta_phi->Scale(1./(h_eta_phi->GetEntries()));

    //h_eta_phi->Scale(100./(h_eta_phi->GetEntries()));
    h_eta_z->Draw("hist");
    h_eta_phi->Draw("same hist");
    TLegend* leg5 = new TLegend(0.1,0.1,0.25,0.2);
    gStyle->SetLegendBorderSize(0);
    leg5->AddEntry(h_eta_z,"bars in z");
    leg5->AddEntry(h_eta_phi,"bars in phi");
    leg5->Draw();

    c5->Update();



    TCanvas *c6 = new TCanvas("c6","c6");
    c6->cd();
    h_phi_z->SetLineColor(kBlue);
    h_phi_phi->SetLineColor(kRed);
    h_phi_z->SetTitle("BTL phi distribution;phi;scaled units");
    //h_eff_z->Draw();
    h6->GetXaxis()->SetLimits(-M_PI,M_PI);
    h6->Draw();
    h_phi_z->Scale(1./(h_phi_z->GetEntries()));
    h_phi_phi->Scale(1./(h_phi_phi->GetEntries()));
    //h_phi_phi->Scale(2./(h_phi_phi->GetEntries()));
    h_phi_z->Draw("hist");
    h_phi_phi->Draw("same hist");
    TLegend* leg6 = new TLegend(0.1,0.1,0.25,0.2);
    gStyle->SetLegendBorderSize(0);
    leg6->AddEntry(h_phi_z,"bars in z");
    leg6->AddEntry(h_phi_phi,"bars in phi");
    leg6->Draw();

    c6->Update();



    


    

}