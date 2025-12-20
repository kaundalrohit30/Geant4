void comp_plt(){
    TFile *f1 = new TFile("Scint_output_lower_production_cut.root", "READ");
    TFile *f2 = new TFile("Scnt_output.root", "READ");

    TH1F *PhotCountDefault = new TH1F("Scintillation Photon Counts (Default)", "Scintillation Photon Count (Default);Photon Counts;Counts", 100, 0, 700);
    TH1F *PhotCount_LP_cut = new TH1F("Scintillation Photon Counts (LP cut)", "Scintillation Photon Counts (LP cut);Photon Counts;Counts", 100, 0, 700);

    TH1F *PhotCountOnlyEle_Default = new TH1F("Scintillation Photon(from electron) Counts (Default)", "Scintillation Photon(from electron) Count (Default);Photon Counts;Counts", 100, 0, 700);
    TH1F *PhotCountOnlyEle_LP_cut = new TH1F("Scintillation Photon(from electron) Counts (LP cut)", "Scintillation Photon(from electron) Counts (LP cut);Photon Counts;Counts", 100, 0, 700);

    int PhotonCountDefault, PhotonCountOnlyEle_Default, PhotonCountLP_cut, PhotonCountOnlyEle_LP_cut;
    TTree *t1 = (TTree*)f2->Get("Photon_Count"); 
    t1->SetBranchAddress("Total_Photon_Count", &PhotonCountDefault);
    t1->SetBranchAddress("Scintillation_Photon_Count_Dist_Total", &PhotonCountOnlyEle_Default);

    TTree *t2 = (TTree*)f1->Get("Photon_Count"); 
    t2->SetBranchAddress("Total_Photon_Count", &PhotonCountLP_cut);
    t2->SetBranchAddress("Scintillation_Photon_Count_Dist_Total", &PhotonCountOnlyEle_LP_cut);

    int entries1 = t1->GetEntries();
    int entries2 = t2->GetEntries();

    for(int i = 0; i<entries1; i++){
        t1->GetEntry(i);
        t2->GetEntry(i);

        PhotCountDefault->Fill(PhotonCountDefault);
        PhotCount_LP_cut->Fill(PhotonCountLP_cut);
        PhotCountOnlyEle_Default->Fill(PhotonCountOnlyEle_Default);
        PhotCountOnlyEle_LP_cut->Fill(PhotonCountOnlyEle_LP_cut);
    }


    PhotCountDefault->SetLineColor(kBlue);
    PhotCount_LP_cut->SetLineColor(kBlack);
    PhotCountOnlyEle_Default->SetLineColor(kBlue);
    PhotCountOnlyEle_LP_cut->SetLineColor(kBlack);

    TCanvas *c1 = new TCanvas();
    PhotCountDefault->Draw();
    PhotCountDefault->SetStats(0);
    PhotCount_LP_cut->Draw("same");

    TLegend *leg1 = new TLegend(0.7, 0.7, 0.8, 0.8);
    leg1->AddEntry(PhotCountDefault, "All Scintillation Photons (default cut)", "LF2");
    leg1->AddEntry(PhotCount_LP_cut, "All Scintillation Photons (LP cut)", "LF2");
    leg1->SetBorderSize(0);
    leg1->SetFillColor(0);
    leg1->SetTextFont(42);
    leg1->Draw();

    TCanvas *c2 = new TCanvas();
    PhotCountOnlyEle_Default->Draw();
    PhotCountOnlyEle_Default->SetStats(0);
    PhotCountOnlyEle_LP_cut->Draw("same");

    TLegend *leg2 = new TLegend(0.7, 0.7, 0.8, 0.8);
    leg2->AddEntry(PhotCountOnlyEle_Default, "Scintillation Photons from e^{-} (default cut)", "LF2");
    leg2->AddEntry(PhotCountOnlyEle_LP_cut, "Scintillation Photons from e^{-} (LP cut)", "LF2");
    leg2->SetBorderSize(0);
    leg2->SetFillColor(0);
    leg2->SetTextFont(42);
    leg2->Draw();

    
}