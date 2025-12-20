void thetaCorr(){

    TFile *f1 = new TFile("output_0.root", "READ");

    TH2F *histCorr = new TH2F("Angle Corr", "Angle Corr;#theta_{sim};#theta_{reco}", 100, 0, 180, 100, 0, 180);

    
    TTree *t1 = (TTree*)f1->Get("Angle1"); 
    double recoTheta_1, simTheta_1;
    t1->SetBranchAddress("recoTheta_1", &recoTheta_1);
    t1->SetBranchAddress("simTheta_1", &simTheta_1);

    double recoTheta_2, simTheta_2;
    TTree *t2 = (TTree*)f1->Get("Angle2"); ;
    t2->SetBranchAddress("recoTheta_2", &recoTheta_2);
    t2->SetBranchAddress("simTheta_2", &simTheta_2);

    int entries1, entries2;

    entries1 = t1->GetEntries();
    entries2 = t2->GetEntries();
    cout << entries1 << endl;
    for(int i = 0; i<entries1; i++){
        t1->GetEntry(i);
        t2->GetEntry(i);
        
        histCorr->Fill(simTheta_1, recoTheta_1-90);


    }

    TCanvas *c1 = new TCanvas();
    histCorr->Draw("colz");

    //f1->Close();
}