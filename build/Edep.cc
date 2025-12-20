void Edep(){
    TFile *f1 = new TFile("Scint_output_lower_production_cut.root", "READ");

    //TH2F *histCorr = new TH2F("Energy Deposit", "Energy Deposit;E_{dep}(Compton) (MeV);E_{dep}(Photoelectric) (MeV)", 100, 0, 0.6, 100, 0, 0.6);
    TH1F *PhotCountCompt = new TH1F("Scintillation Photon Counts (Compton)", "Scintillation Photon Count (Compton);Photon Counts;Counts", 100, 0, 700);
    TH1F *PhotCountPhote = new TH1F("Scintillation Photon Counts", "Scintillation Photon Counts (Photoelectric);Photon Counts;Counts", 100, 0, 700);
    TH1F *PhotCountComp_Phote = new TH1F("Scintillation Photon Counts (Total)", "Scintillation Photon Counts (Cmpt+phote (e^{-}));Photon Counts;Counts", 100, 0, 700);
    TH1F *PhotCountTotal = new TH1F("Total optical photon count dist", "Scintillation Photon Counts (Total);Photon Counts;Counts", 100, 0, 700);
    TH1F *PhotCountBE = new TH1F("Photoproduced_Photon_Count", "Photoproduced_Photon_Count;Photon Counts;Counts", 80, 0, 80);

    TH1F *histEdepCompt = new TH1F("Energy deposit (Compton)", "Edep (Compton);Edep (MeV);Counts", 100, 0, 0.6);
    TH1F *histEdepPhotoP = new TH1F("Energy deposit (Photoelectric)", "Edep (Photoelectric);Edep (MeV);Counts", 100, 0, 0.6);
    TH1F *histEdepTotal = new TH1F("Energy deposit (Compton+Photoelectric)", "Edep(Compton+Photoelectric);Edep (MeV);Counts", 100, 0, 0.6);
    TH1F *histBE = new TH1F("Energy deposit (BE)", "Edep(BE);Edep (MeV);Counts", 100, 0, 0.1);


    TTree *t1 = (TTree*)f1->Get("Photon_Count"); 
    int Scintillation_Photon_Count_Dist_Compton, Scintillation_Photon_Count_Dist_Photoproduction, Scintillation_Photon_Count_Dist_Total, Total_Photon_Count, Photoproduced_Photon_Count;
    t1->SetBranchAddress("Scintillation_Photon_Count_Dist_Compton", &Scintillation_Photon_Count_Dist_Compton);
    t1->SetBranchAddress("Scintillation_Photon_Count_Dist_Photoproduction", &Scintillation_Photon_Count_Dist_Photoproduction);
    t1->SetBranchAddress("Scintillation_Photon_Count_Dist_Total", &Scintillation_Photon_Count_Dist_Total);
    t1->SetBranchAddress("Total_Photon_Count", &Total_Photon_Count);
    t1->SetBranchAddress("Photoproduced_Photon_Count", &Photoproduced_Photon_Count);

    TTree *t2 = (TTree*)f1->Get("Events"); 
    double Energy_Deposited_Compton, Energy_Deposited_Photoelectric, Energy_Deposited_Total, BE_dist_photoE;
    t2->SetBranchAddress("Energy_Deposited_Compton", &Energy_Deposited_Compton);
    t2->SetBranchAddress("Energy_Deposited_Photoelectric", &Energy_Deposited_Photoelectric);
    t2->SetBranchAddress("Energy_Deposited_Total", &Energy_Deposited_Total);
    t2->SetBranchAddress("BE_dist_photoE", &BE_dist_photoE);
    




    int entries1, entries2;

    entries1 = t1->GetEntries();
    entries2 = t2->GetEntries();
    
    cout << entries1 << endl;
    for(int i = 0; i<entries1; i++){
        t1->GetEntry(i);
        t2->GetEntry(i);
        
        PhotCountCompt->Fill(Scintillation_Photon_Count_Dist_Compton);
        PhotCountPhote->Fill(Scintillation_Photon_Count_Dist_Photoproduction);
        PhotCountComp_Phote->Fill(Scintillation_Photon_Count_Dist_Total);
        PhotCountTotal->Fill(Total_Photon_Count);
        PhotCountBE->Fill(Photoproduced_Photon_Count);
        //histCorr->Fill(Energy_Deposited_Compton, Energy_Deposited_Photoelectric);
        histEdepCompt->Fill(Energy_Deposited_Compton);
        histEdepPhotoP->Fill(Energy_Deposited_Photoelectric);
        histEdepTotal->Fill(Energy_Deposited_Total);
        histBE->Fill(BE_dist_photoE); 



    }

    PhotCountCompt->SetLineWidth(2);
    PhotCountCompt->GetXaxis()->SetLabelSize(0.05);
    PhotCountCompt->GetYaxis()->SetLabelSize(0.05);
    PhotCountCompt->GetXaxis()->SetTitleSize(0.05);
    PhotCountCompt->GetYaxis()->SetTitleSize(0.05);

    PhotCountPhote->SetLineWidth(2);
    PhotCountPhote->GetXaxis()->SetLabelSize(0.05);
    PhotCountPhote->GetYaxis()->SetLabelSize(0.05);
    PhotCountPhote->GetXaxis()->SetTitleSize(0.05);
    PhotCountPhote->GetYaxis()->SetTitleSize(0.05);

    PhotCountComp_Phote->SetLineWidth(2);
    PhotCountComp_Phote->GetXaxis()->SetLabelSize(0.05);
    PhotCountComp_Phote->GetYaxis()->SetLabelSize(0.05);
    PhotCountComp_Phote->GetXaxis()->SetTitleSize(0.05);
    PhotCountComp_Phote->GetYaxis()->SetTitleSize(0.05);

    PhotCountTotal->SetLineWidth(2);
    PhotCountTotal->GetXaxis()->SetLabelSize(0.05);
    PhotCountTotal->GetYaxis()->SetLabelSize(0.05);
    PhotCountTotal->GetXaxis()->SetTitleSize(0.05);
    PhotCountTotal->GetYaxis()->SetTitleSize(0.05);

    PhotCountBE->SetLineWidth(2);
    PhotCountBE->GetXaxis()->SetLabelSize(0.05);
    PhotCountBE->GetYaxis()->SetLabelSize(0.05);
    PhotCountBE->GetXaxis()->SetTitleSize(0.05);
    PhotCountBE->GetYaxis()->SetTitleSize(0.05);

    histEdepCompt->SetLineWidth(2);
    histEdepCompt->GetXaxis()->SetLabelSize(0.05);
    histEdepCompt->GetYaxis()->SetLabelSize(0.05);
    histEdepCompt->GetXaxis()->SetTitleSize(0.05);
    histEdepCompt->GetYaxis()->SetTitleSize(0.05);

    histEdepPhotoP->SetLineWidth(2);
    histEdepPhotoP->GetXaxis()->SetLabelSize(0.05);
    histEdepPhotoP->GetYaxis()->SetLabelSize(0.05);
    histEdepPhotoP->GetXaxis()->SetTitleSize(0.05);
    histEdepPhotoP->GetYaxis()->SetTitleSize(0.05);

    histEdepTotal->SetLineWidth(2);
    histEdepTotal->GetXaxis()->SetLabelSize(0.05);
    histEdepTotal->GetYaxis()->SetLabelSize(0.05);
    histEdepTotal->GetXaxis()->SetTitleSize(0.05);
    histEdepTotal->GetYaxis()->SetTitleSize(0.05);

    histBE->SetLineWidth(2);
    histBE->GetXaxis()->SetLabelSize(0.05);
    histBE->GetYaxis()->SetLabelSize(0.05);
    histBE->GetXaxis()->SetTitleSize(0.05);
    histBE->GetYaxis()->SetTitleSize(0.05);    


    
    
    
    
    TCanvas *c2 = new TCanvas();
    PhotCountPhote->Draw();
    //PhotCountPhote->SetStats(true);
    c2->SetLogy();

    TCanvas *c3 = new TCanvas();
    PhotCountComp_Phote->Draw();
    //PhotCountComp_Phote->SetStats(true);
    c3->SetLogy();

    TCanvas *c4 = new TCanvas();
    PhotCountCompt->Draw();
    //PhotCountCompt->SetStats(true);
    c4->SetLogy();

    TCanvas *c5 = new TCanvas();
    PhotCountTotal->Draw();
    //PhotCountTotal->SetStats(true);
    c5->SetLogy();

    TCanvas *c6 = new TCanvas();
    PhotCountBE->Draw();
    c6->SetLogy();

    PhotCountCompt->SetLineColor(kBlue);
    PhotCountPhote->SetLineColor(kRed);
    PhotCountComp_Phote->SetLineColor(kBlack);
    PhotCountTotal->SetLineColor(kGreen);

    TCanvas *c1 = new TCanvas();
    PhotCountPhote->Draw();
    //PhotCountPhote->SetStats(0);
    PhotCountCompt->Draw("same");
    //PhotCountCompt->SetStats(0);
    PhotCountComp_Phote->Draw("same");
    //PhotCountComp_Phote->SetStats(0);
    PhotCountTotal->Draw("same");
    //PhotCountTotal->SetStats(0);
    c1->SetLogy();

    //PhotCountPhote->SetTitle("Scintillation photons Distribution");
    

    TLegend *leg1 = new TLegend(0.7, 0.7, 0.8, 0.8);
    leg1->AddEntry(PhotCountCompt, "Compton", "LF2");
    leg1->AddEntry(PhotCountPhote, "Photoelectric", "LF2");
    leg1->AddEntry(PhotCountComp_Phote, "Compton+Photoelectric (by e^{-})", "LF2");
    leg1->AddEntry(PhotCountTotal, "All Scintillation photons", "LF2");
    leg1->SetBorderSize(0);
    leg1->SetFillColor(0);
    leg1->SetTextFont(42);
    leg1->Draw();


    TCanvas *c7 = new TCanvas();
    histEdepCompt->Draw();
    c7->SetLogy();

    TCanvas *c8 = new TCanvas();
    histEdepPhotoP->Draw();
    c8->SetLogy();

    TCanvas *c9 = new TCanvas();
    histEdepTotal->Draw();
    c9->SetLogy();

    TCanvas *c10 = new TCanvas();
    histBE->Draw();
    c10->SetLogy();

    histEdepCompt->SetLineColor(kBlue);
    histEdepPhotoP->SetLineColor(kRed);
    histEdepTotal->SetLineColor(kBlack);
    

    TCanvas *c11 = new TCanvas();
    histEdepCompt->Draw();
    histEdepCompt->SetStats(0);
    histEdepPhotoP->Draw("same");
    histEdepPhotoP->SetStats(0);
    histEdepTotal->Draw("same");
    histEdepTotal->SetStats(0);
    c11->SetLogy();


    //histEdepCompt->SetTitle("Energy Deposit");

    

    TLegend *leg2 = new TLegend(0.7, 0.7, 0.8, 0.8);
    leg2->AddEntry(histEdepCompt, "Compton", "LF2");
    leg2->AddEntry(histEdepPhotoP, "Photoelectric", "LF2");
    leg2->AddEntry(histEdepTotal, "Total", "LF2");
    //leg1->AddEntry(histTotal, "All Scintillation photons", "LF2");
    leg2->SetBorderSize(0);
    leg2->SetFillColor(0);
    leg2->SetTextFont(42);
    leg2->Draw();


    
}