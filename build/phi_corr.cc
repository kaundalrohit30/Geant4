void phi_corr(){

    TFile *f1 = new TFile("output_0.root ", "READ");
    TFile *f2 = new TFile("output_Uncorrelated_gamma_0.root", "READ");

    TH1F *histTotal = new TH1F("Dphi Distribution", "Dphi Distribution;#phi_{1}-#phi_{2};Counts", 100, -200, 200);
    TH1F *histUnCorr = new TH1F("Uncorrelated dphi dist", "Uncorrelated dphi dist;#phi_{1}-#phi_{2};Counts", 100, -200, 200);
    TH1F *histCorr = new TH1F("Correlated dphi dist", "Correlated dphi dist;#phi_{1}-#phi_{2};Counts", 100, -200, 200);
    //histCorr->Sumw2();
    
    TTree *t1 = (TTree*)f1->Get("Detector1");

    double phi1, Theta1, PixelDistance1;
    t1->SetBranchAddress("phi1", &phi1);
    t1->SetBranchAddress("Theta1", &Theta1);
    //t1->SetBranchAddress("PixelDistance1", &PixelDistance1);

    TTree *t2 = (TTree*)f1->Get("Detector2");

    double phi2, Theta2, PixelDistance2;
    t2->SetBranchAddress("phi2", &phi2);
    t2->SetBranchAddress("Theta2", &Theta2);
    //t2->SetBranchAddress("PixelDistance2", &PixelDistance2);


    TTree *t3 = (TTree*)f2->Get("Detector1");

    double phi3, Theta3, PixelDistance3;
    t3->SetBranchAddress("phi1", &phi3);
    t3->SetBranchAddress("Theta1", &Theta3);
    //t3->SetBranchAddress("PixelDistance3", &PixelDistance3);

    TTree *t4 = (TTree*)f2->Get("Detector2");

    double phi4, Theta4, PixelDistance4;
    t4->SetBranchAddress("phi2", &phi4);
    t4->SetBranchAddress("Theta2", &Theta4);
    //t4->SetBranchAddress("PixelDistance4", &PixelDistance4);


    int entries1 = t1->GetEntries();
    int entries2 = t2->GetEntries();
    int entries3 = t3->GetEntries();
    int entries4 = t4->GetEntries();

    vector<double> *Phi1 = new vector<double>();
    vector<double> *Phi2 = new vector<double>();
    double dPhiAll;
    for(int i = 0; i<entries1/10; i++){
        t1->GetEntry(i);
        //if(Theta1 < 85 and Theta1 > 80){
            Phi1->push_back(phi1);
            for(int j = 0; j < entries2/10; j++){
                t2->GetEntry(j);
                //if(Theta2 < 85 and Theta2 > 80){
                    if(i == 0){
                        Phi2->push_back(phi2);
                    }
                    dPhiAll = phi1 - phi2;
                    histTotal->Fill(dPhiAll);
                //}    
            }
        //}
    }

    vector<double> *Phi3 = new vector<double>();
    vector<double> *Phi4 = new vector<double>();
    double dPhiUncorr;
    for(int i = 0; i<entries3/10; i++){
        t3->GetEntry(i);
        //if(Theta3 < 85 and Theta3 > 80){
            Phi3->push_back(phi3);
            for(int j = 0; j < entries4/10; j++){
                t4->GetEntry(j);
                //if(Theta4 < 85 and Theta4 > 80){
                    if(i == 0){
                        Phi4->push_back(phi4);
                    }
                    dPhiUncorr = phi3 - phi4;
                    histUnCorr->Fill(dPhiUncorr);
                //}    
            }
        //}
    }
    
    /*double dPhiUncorr;
    for(int i = 0; i < Phi1->size(); i++){
        for(int j = i+1; j < Phi1->size(); j++){
            dPhiUncorr = (*Phi1)[i] - (*Phi1)[j];
            histUnCorr->Fill(dPhiUncorr);
        }
    }
    for(int i = 0; i < Phi2->size(); i++){
        for(int j = i+1; j < Phi2->size(); j++){
            dPhiUncorr = (*Phi2)[i] - (*Phi2)[j];
            histUnCorr->Fill(dPhiUncorr);
        }
    }*/


    
    histCorr->Divide(histTotal, histUnCorr, 1, 1, "");

    histTotal->SetLineColor(kRed);
    TCanvas *c1 = new TCanvas();
    histTotal->Draw();
    //histUnCorr->Draw("same");

    TCanvas *c2 = new TCanvas();
    histUnCorr->Draw();

    TCanvas *c3 = new TCanvas();
    histCorr->Draw();

    
}