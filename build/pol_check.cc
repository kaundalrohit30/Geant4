void pol_check(){

    TFile *f1 = new TFile("output_CorrPrimaryGamma_features_check0.root ", "READ");
    TFile *f2 = new TFile("output_UnCorrPrimaryGamma_features_check0.root", "READ");


    TH1F *histCorPhi1 = new TH1F("CorrPolarization1_Phi", "Polarization Orientation1 (#phi dist corr);#phi;Counts", 100, -200, 200);
    TH1F *histCorPhi2 = new TH1F("CorrPolarization2_Phi", "Polarization Orientation2 (#phi dist corr);#phi;Counts", 100, -200, 200);
    TH1F *histUnCorPhi1 = new TH1F("UnCorrPolarization1_Phi", "Polarization Orientation1 (#phi dist uncorr);#phi;Counts", 100, -200, 200);
    TH1F *histUnCorPhi2 = new TH1F("UnCorrPolarization2_Phi", "Polarization Orientation2 (#phi dist uncorr);#phi;Counts", 100, -200, 200);
    TH2F *histCorr = new TH2F("Pol1_vs_pol2_(corr)", "Pol1_vs_pol2 (corr)", 100, -200, 200, 100, -200, 200);
    TH2F *histUnCorr = new TH2F("Pol1_vs_pol2_(uncorr)", "Pol1_vs_pol2 (uncorr)", 100, -200, 200, 100, -200, 200);
    TH1F *histCorPhi1__Phi2 = new TH1F("Phi1_Phi2_Corr", "#phi_{1} - #phi_{2} dist (Correlated);#phi_{1} - #phi_{2};Counts", 100, -360, 360);
    TH1F *histUnCorPhi1__Phi2 = new TH1F("Phi1_Phi2_UnCorr", "#phi_{1} - #phi_{2} dist (Uncorrelated);#phi_{1} - #phi_{2};Counts", 100, -180, 300);

    TTree *t1 = (TTree*)f1->Get("Polarization");
    TTree *t2 = (TTree*)f2->Get("Polarization");

    double CorPol1X, CorPol2X, CorPol1Y, CorPol2Y;
    t1->SetBranchAddress("Pol1X", &CorPol1X);
    t1->SetBranchAddress("Pol1Y", &CorPol1Y);
    t1->SetBranchAddress("Pol2X", &CorPol2X);
    t1->SetBranchAddress("Pol2Y", &CorPol2Y);

    double UnCorPol1X, UnCorPol2X, UnCorPol1Y, UnCorPol2Y;
    t2->SetBranchAddress("Pol1X", &UnCorPol1X);
    t2->SetBranchAddress("Pol1Y", &UnCorPol1Y);
    t2->SetBranchAddress("Pol2X", &UnCorPol2X);
    t2->SetBranchAddress("Pol2Y", &UnCorPol2Y);

    int entries1 = t1->GetEntries();
    int entries2 = t2->GetEntries();

    double CorPhi1, CorPhi2, UnCorPhi1, UnCorPhi2;
    for(int i = 0; i< entries1; i++){
        t1->GetEntry(i);
        t2->GetEntry(i);
        
        CorPhi1 = atan2(CorPol1Y, CorPol1X)*180/M_PI;
        CorPhi2 = atan2(CorPol2Y, CorPol2X)*180/M_PI;
        UnCorPhi1 = atan2(UnCorPol1Y, UnCorPol1X)*180/M_PI;
        UnCorPhi2 = atan2(UnCorPol2Y, UnCorPol2X)*180/M_PI;
        //cout << UnCorPol2Y << "   " << UnCorPol2X << "   " << UnCorPhi2 <<  endl;
        histCorPhi1->Fill(CorPhi1);
        histCorPhi2->Fill(CorPhi2);
        histUnCorPhi1->Fill(UnCorPhi1);
        histUnCorPhi2->Fill(UnCorPhi2);
        histCorr->Fill(CorPhi1, CorPhi2);
        histUnCorr->Fill(UnCorPhi1, UnCorPhi2); 
        histCorPhi1__Phi2->Fill(CorPhi1-CorPhi2);
        histUnCorPhi1__Phi2->Fill(UnCorPhi1-UnCorPhi2);
    }

    TCanvas *c1 = new TCanvas();
    histCorPhi1->Draw();
    TCanvas *c2 = new TCanvas();
    histCorPhi2->Draw();
    TCanvas *c3 = new TCanvas();
    histUnCorPhi1->Draw();
    TCanvas *c4 = new TCanvas();
    histUnCorPhi2->Draw();
    TCanvas *c5 = new TCanvas();
    histCorr->Draw("colz");
    TCanvas *c6 = new TCanvas();
    histUnCorr->Draw("colz");
    TCanvas *c7 = new TCanvas();
    histCorPhi1__Phi2->Draw();
    TCanvas *c8 = new TCanvas();
    histUnCorPhi1__Phi2->Draw();

}