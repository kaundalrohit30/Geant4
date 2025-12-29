void PrimaryGamma_dist(){
    TFile *f1 = new TFile("output_UnCorrPrimaryGamma_features_check0.root", "READ");

    TH1F *histPx = new TH1F("MomentumX", "MomentumX;P_{x};Counts", 100, -2, 2);
    TH1F *histPy = new TH1F("MomentumY", "MomentumY;P_{y};Counts", 100, -2, 2);
    TH1F *histPz = new TH1F("MomentumZ", "MomentumZ;P_{z};Counts", 100, -2, 2);
    //TH1F *histP = new TH1F("Momentum", "Momentum;P;Counts", 100, -2, 2);
    TH2F *histPxPy = new TH2F("MomentumX:Y", "Momentum X:Y;P_{x};P_{y}", 100, -2, 2, 100, -2, 2);

    TH1F *histHitX = new TH1F("HitX", "Hit X;Hit X;Counts", 100, -15, 15);
    TH1F *histHitY = new TH1F("HitY", "Hit Y;Hit Y;Counts", 100, -15, 15);
    TH1F *histHitZ = new TH1F("HitZ", "Hit Z;Hit Z;Counts", 100, -30, 30);
    TH2F *histHitXY = new TH2F("HitX:Y", "Hit X:Y;Hit X;Hit Y", 100, -12, 12, 100, -12, 12);

    TTree *t1 = (TTree*)f1->Get("Momentum"); 
    double Px, Py, Pz, magP;
    t1->SetBranchAddress("Px", &Px);
    t1->SetBranchAddress("Py", &Py);
    t1->SetBranchAddress("Pz", &Pz);
    //t1->SetBranchAddress("magP", &magP);

    TTree *t2 = (TTree*)f1->Get("Hit"); 
    double hitX, hitY, hitZ;
    t2->SetBranchAddress("hitX", &hitX);
    t2->SetBranchAddress("hitY", &hitY);
    t2->SetBranchAddress("hitZ", &hitZ);

    if (!t1 || !t2) {
    std::cerr << "Error: Tree not found!" << std::endl;
    return;
    }
    
    int entries1 = t1->GetEntries();
    //cout << entries1 << endl;
    int entries2 = t2->GetEntries();
    
    for(int i = 0; i < entries1; i++){
        t1->GetEntry(i);
        histPx->Fill(Px);
        histPy->Fill(Py);
        histPz->Fill(Pz);
        //histP->Fill(magP);
        histPxPy->Fill(Px,Py);
    }

    for(int i = 0; i < entries2; i++){
        t2->GetEntry(i);
        histHitX->Fill(hitX);
        histHitY->Fill(hitY);
        histHitZ->Fill(hitZ);
        histHitXY->Fill(hitX, hitY);
    }
    
    //histPxPy->SetContour(50);
    //histHitXY->SetContour(50);

    TCanvas *c1 = new TCanvas();
    histPx->Draw();
    TCanvas *c2 = new TCanvas();
    histPy->Draw();
    TCanvas *c3 = new TCanvas();
    histPz->Draw();
    //TCanvas *c4 = new TCanvas();
    //histP->Draw();
    TCanvas *c5 = new TCanvas();
    histPxPy->Draw("colz");
    TCanvas *c6 = new TCanvas();
    histHitX->Draw();
    TCanvas *c7 = new TCanvas();
    histHitY->Draw();
    TCanvas *c8 = new TCanvas();
    histHitZ->Draw();
    TCanvas *c9 = new TCanvas();
    histHitXY->Draw("colz");
    
}