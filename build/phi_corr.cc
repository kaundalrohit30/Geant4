void phi_corr(){

    TFile *f = new TFile("Dphi_Correlation_70_theta_90.root", "RECREATE");
    TFile *f1 = new TFile("output_Correlated_gamma_20M_nw00.root ", "READ");
    TFile *f2 = new TFile("output_UnCorrelated_gamma_20M_nw00.root", "READ");
    //TFile *f3 = new TFile("output_BothGamma_selected_20M_0.root", "READ");

    TH1F *histTotal1 = new TH1F("Correlated_dphi_distribution(4)", "Correlated dphi distribution (d>4);#phi_{1}-#phi_{2};N(#phi_{1}-#phi_{2})", 20, -200, 200);
    TH1F *histUnCorr1 = new TH1F("Uncorrelated_dphi_dist(4)", "Uncorrelated dphi dist (d>4);#phi_{1}-#phi_{2};N(#phi_{1}-#phi_{2})", 20, -200, 200);
    TH1F *histCorr1 = new TH1F("Corrected_dphi_dist(4)", "Corrected dphi dist (d>4);#phi_{1}-#phi_{2};N_{corr}(#phi_{1}-#phi_{2})", 20, -200, 200);
    histCorr1->Sumw2();

    TH1F *histTotal2 = new TH1F("Correlated_dphi_distribution(7)", "Correlated dphi distribution (d>7);#phi_{1}-#phi_{2};N(#phi_{1}-#phi_{2})", 20, -200, 200);
    TH1F *histUnCorr2 = new TH1F("Uncorrelated_dphi_dist(7)", "Uncorrelated dphi dist (d>7);#phi_{1}-#phi_{2};N(#phi_{1}-#phi_{2})", 20, -200, 200);
    TH1F *histCorr2 = new TH1F("Corrected_dphi_dist(7)", "Corrected dphi dist (d>7);#phi_{1}-#phi_{2};N_{corr}(#phi_{1}-#phi_{2})", 20, -200, 200);
    histCorr2->Sumw2();

    TH1F *histTotal3 = new TH1F("Correlated_dphi_distribution(10)", "Correlated dphi distribution (d>10);#phi_{1}-#phi_{2};N(#phi_{1}-#phi_{2})", 20, -200, 200);
    TH1F *histUnCorr3 = new TH1F("Uncorrelated_dphi_dist(10)", "Uncorrelated dphi dist (d>10);#phi_{1}-#phi_{2};N(#phi_{1}-#phi_{2})", 20, -200, 200);
    TH1F *histCorr3 = new TH1F("Corrected_dphi_dist(10)", "Corrected dphi dist (d>10);#phi_{1}-#phi_{2};N_{corr}(#phi_{1}-#phi_{2})", 20, -200, 200);
    histCorr3->Sumw2();

    
    TTree *t1 = (TTree*)f1->Get("Detector1");

    double phi1, Theta1, PixelDistance1;
    t1->SetBranchAddress("phi1", &phi1);
    t1->SetBranchAddress("Theta1", &Theta1);
    t1->SetBranchAddress("PixelDistance1", &PixelDistance1);

    TTree *t2 = (TTree*)f1->Get("Detector2");

    double phi2, Theta2, PixelDistance2;
    t2->SetBranchAddress("phi2", &phi2);
    t2->SetBranchAddress("Theta2", &Theta2);
    t2->SetBranchAddress("PixelDistance2", &PixelDistance2);


    TTree *t3 = (TTree*)f2->Get("Detector1");

    double phi3, Theta3, PixelDistance3;
    t3->SetBranchAddress("phi1", &phi3);
    t3->SetBranchAddress("Theta1", &Theta3);
    t3->SetBranchAddress("PixelDistance1", &PixelDistance3);

    TTree *t4 = (TTree*)f2->Get("Detector2");

    double phi4, Theta4, PixelDistance4;
    t4->SetBranchAddress("phi2", &phi4);
    t4->SetBranchAddress("Theta2", &Theta4);
    t4->SetBranchAddress("PixelDistance2", &PixelDistance4);


    //double dphi;
    //TTree *t = (TTree*)f3->Get("Dphi");
    //t->SetBranchAddress("dPhi_dist", &dphi);

    int num = 1;
    int entries1 = t1->GetEntries()/num;
    int entries2 = t2->GetEntries()/num;
    int entries3 = t3->GetEntries()/num;
    int entries4 = t4->GetEntries()/num;
    
    //int entries = t->GetEntries();

    //vector<double> *Phi1 = new vector<double>();
    //vector<double> *Phi2 = new vector<double>();

    double thetaMin = 70;
    double thetaMax = 90;
    double PD = 3.2;
    double PD1 = 4;
    double PD2 = 7;
    double PD3 = 10;

    //for(int i = 0; i < entries; i++){
    //    t->GetEntry(i);
    //    histTotal->Fill(dphi);
    //}

    double dPhiAll;
    for(int i = 0; i<entries1; i++){
        t1->GetEntry(i);
        if(Theta1 < thetaMax and Theta1 > thetaMin){
            for(int j = 0; j < entries2; j++){
                t2->GetEntry(j);
                if(Theta2 < thetaMax and Theta2 > thetaMin){
                    
                    dPhiAll = phi1 - phi2;
                    if(dPhiAll > 180) dPhiAll -= 2*180;
                        
                    else if(dPhiAll < -180) dPhiAll += 2*180;

                    if(PixelDistance1 > PD1 and PixelDistance2 > PD1){
                        histTotal1->Fill(dPhiAll);
                    }
                    if(PixelDistance1 > PD2 and PixelDistance2 > PD2){
                        histTotal2->Fill(dPhiAll);
                    }
                    if(PixelDistance1 > PD3 and PixelDistance2 > PD3){
                        histTotal3->Fill(dPhiAll);
                    }
                    
                }    
            }
        }
    }

    //vector<double> *Phi3 = new vector<double>();
    //vector<double> *Phi4 = new vector<double>();
    double dPhiUncorr;
    for(int i = 0; i<entries3; i++){
        t3->GetEntry(i);
        if(Theta3 < thetaMax and Theta3 > thetaMin and PixelDistance3 > PD){
            
            for(int j = 0; j < entries4; j++){
                t4->GetEntry(j);
                if(Theta4 < thetaMax and Theta4 > thetaMin and PixelDistance4 > PD){
                    
                    dPhiUncorr = phi3 - phi4;

                    if(dPhiUncorr > 180) dPhiUncorr -= 2*180;
                  
                    else if(dPhiUncorr < -180) dPhiUncorr += 2*180;

                    if(PixelDistance3 > PD1 and PixelDistance4 > PD1 and histUnCorr1->GetEntries()<= histTotal1->GetEntries()){
                        histUnCorr1->Fill(dPhiUncorr);
                    }
                    if(PixelDistance3 > PD2 and PixelDistance4 > PD2 and histUnCorr2->GetEntries()<= histTotal2->GetEntries()){
                        histUnCorr2->Fill(dPhiUncorr);
                    }
                    if(PixelDistance3 > PD3 and PixelDistance4 > PD3 and histUnCorr3->GetEntries()<= histTotal3->GetEntries()){
                        histUnCorr3->Fill(dPhiUncorr);
                    }
                }  
                  if(histUnCorr1->GetEntries()>= histTotal1->GetEntries() and histUnCorr2->GetEntries()>= histTotal2->GetEntries() and histUnCorr3->GetEntries()>= histTotal3->GetEntries()) break;
            }
        }
        if(histUnCorr1->GetEntries()>= histTotal1->GetEntries() and histUnCorr2->GetEntries()>= histTotal2->GetEntries() and histUnCorr3->GetEntries()>= histTotal3->GetEntries()) break;
    }
    


    /*double dPhiUncorr;
    for(int i = 0; i < Phi1->size(); i++){
        for(int j = i+1; j < Phi1->size(); j++){
            dPhiUncorr = (*Phi1)[i] - (*Phi1)[j];
            
            if(dPhiUncorr > 180) dPhiUncorr -= 2*180;
                        
            else if(dPhiUncorr < -180) dPhiUncorr += 2*180;
            
            histUnCorr->Fill(dPhiUncorr);
            if(histUnCorr->GetEntries()>= histTotal->GetEntries()) break;
        }
        if(histUnCorr->GetEntries()>= histTotal->GetEntries()) break;
    }
    for(int i = 0; i < Phi2->size(); i++){
        for(int j = i+1; j < Phi2->size(); j++){
            dPhiUncorr = (*Phi2)[i] - (*Phi2)[j];
            
            if(dPhiUncorr > 180) dPhiUncorr -= 2*180;
                        
            else if(dPhiUncorr < -180) dPhiUncorr += 2*180;
            
            histUnCorr->Fill(dPhiUncorr);
            if(histUnCorr->GetEntries()>= histTotal->GetEntries()) break;
        }
        if(histUnCorr->GetEntries()>= histTotal->GetEntries()) break;
    }*/

    //histTotal->Scale(1/histTotal->GetEntries());
    //histUnCorr->Scale(1/histUnCorr->GetEntries());
    
    histCorr1->Divide(histTotal1, histUnCorr1, 1, 1, "");
    histCorr2->Divide(histTotal2, histUnCorr2, 1, 1, "");
    histCorr3->Divide(histTotal3, histUnCorr3, 1, 1, "");
    //histCorr->Scale(1/histCorr->GetEntries());

    //histTotal->SetLineColor(kRed);
    //TCanvas *c1 = new TCanvas();
    //histUnCorr->Draw();
    ////histUnCorr->SetStats(0);
    //histTotal->Draw("same");
    //histTotal->SetStats(0);

    /*TLegend *leg1 = new TLegend(0.7, 0.7, 0.8, 0.8);
    leg1->AddEntry(histUnCorr, "non correlated polarizations", "LF2");
    leg1->AddEntry(histTotal, "correlated polarizations", "LF2");
    leg1->SetBorderSize(0);
    leg1->SetFillColor(0);
    leg1->SetTextFont(42);
    leg1->Draw();*/

    /*TCanvas *c2 = new TCanvas();
    histTotal->Draw();

    TCanvas *c3 = new TCanvas();
    histUnCorr->Draw();

    TCanvas *c4 = new TCanvas();
    histCorr->Draw();*/

    
    f->cd();
    histTotal1->Write();
    histUnCorr1->Write();
    histCorr1->Write();
    histTotal2->Write();
    histUnCorr2->Write();
    histCorr2->Write();
    histTotal3->Write();
    histUnCorr3->Write();
    histCorr3->Write();
    f->Write();
    f->Close();
    f1->Close();
    f2->Close();
}