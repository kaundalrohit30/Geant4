void crossSection(){

    TFile *f1 = new TFile("output_ScatAndPol_Angle_50M_0.root", "READ");

    TH2F *hist_ThetaEta = new TH2F("Theta_vs_Eta", "Theta_vs_Eta;#eta;#theta", 100, -200, 200, 100, 0, 180);

    TTree *t1 = (TTree*)f1->Get("Angle");
    double theta, eta;
    t1->SetBranchAddress("RecoTheta", &theta);
    t1->SetBranchAddress("RecoEta", &eta);

    int entries1 = t1->GetEntries();
    double scatFact, rdSigma;
    //int incE = 511;

    for(int i = 0; i<entries1; i++){
        
        t1->GetEntry(i);
        
        scatFact =  2 + cos(theta*M_PI/180);
        rdSigma = (1/(2-cos(theta*M_PI/180)) + 2 - cos(theta*M_PI/180) - (2*pow(sin(theta*M_PI/180),2)*pow(cos(eta*M_PI/180),2)))/(pow(2-cos(theta*M_PI/180),2));
        hist_ThetaEta->Fill(eta, theta, rdSigma);


    }

    hist_ThetaEta->Scale(1/hist_ThetaEta->GetEntries());

    TH2D *hist_ThetaEta_clone = (TH2D*)hist_ThetaEta->Clone("hist_ThetaEta_clone");

    TH1D *histTheta = hist_ThetaEta->ProjectionY("histTheta");
    //TH2D *histNorm;

    int nX = hist_ThetaEta->GetNbinsX();
    int nY = hist_ThetaEta->GetNbinsY();
    double normFact, binContent;
    for(int i = 1; i <= nY; i++){
        normFact = 1/histTheta->GetBinContent(i);
        for(int j = 1; j <= nX; j++){
            binContent = hist_ThetaEta->GetBinContent(j,i);
            //cout << binContent << "    " << binContent*normFact << endl;
            hist_ThetaEta->SetBinContent(j, i, binContent*normFact);
        }
//
    }

    TH1D *histNorm1 = hist_ThetaEta->ProjectionX("histNorm1", hist_ThetaEta->GetYaxis()->FindBin(80), hist_ThetaEta->GetYaxis()->FindBin(85));
    TH1D *histNorm2 = hist_ThetaEta->ProjectionX("histNorm2", hist_ThetaEta->GetYaxis()->FindBin(95), hist_ThetaEta->GetYaxis()->FindBin(100));
    TH1D *histNorm3 = hist_ThetaEta->ProjectionX("histNorm3", hist_ThetaEta->GetYaxis()->FindBin(50), hist_ThetaEta->GetYaxis()->FindBin(55));
    TH1D *histNorm4 = hist_ThetaEta->ProjectionX("histNorm4", hist_ThetaEta->GetYaxis()->FindBin(20), hist_ThetaEta->GetYaxis()->FindBin(25));
    TH1D *histNorm5 = hist_ThetaEta->ProjectionX("histNorm5", hist_ThetaEta->GetYaxis()->FindBin(140), hist_ThetaEta->GetYaxis()->FindBin(145));


    TH1D *histNormTheta = hist_ThetaEta->ProjectionY("histNormTheta", hist_ThetaEta->GetXaxis()->FindBin(-90), hist_ThetaEta->GetXaxis()->FindBin(90));

    TCanvas *c1 = new TCanvas();
    hist_ThetaEta->Draw("COLZ0");
    hist_ThetaEta->SetStats(0);
    TCanvas *c2 = new TCanvas();
    histNormTheta->Draw();

    histNorm1->SetLineColor(kBlue);
    histNorm2->SetLineColor(kRed);
    histNorm3->SetLineColor(kMagenta);
    histNorm4->SetLineColor(kGreen);
    histNorm5->SetLineColor(kOrange);

    histNorm1->SetLineWidth(2);
    histNorm2->SetLineWidth(2);
    histNorm3->SetLineWidth(2);
    histNorm4->SetLineWidth(2);
    histNorm5->SetLineWidth(2);


    TCanvas *c3 = new TCanvas();
    histNorm1->Draw();
    histNorm2->Draw("same");
    histNorm3->Draw("same");
    histNorm4->Draw("same");
    histNorm5->Draw("same");
    histNorm1->SetStats(0);
    histNorm2->SetStats(0);
    histNorm3->SetStats(0);
    histNorm4->SetStats(0);
    histNorm5->SetStats(0);

    TLegend *leg1 = new TLegend(0.7, 0.7, 0.8, 0.8);
    leg1->AddEntry(histNorm1, "80 < #theta < 85", "LF2");
    leg1->AddEntry(histNorm2, "95 < #theta < 100", "LF2");
    leg1->AddEntry(histNorm3, "50 < #theta < 55", "LF2");
    leg1->AddEntry(histNorm4, "20 < #theta < 25", "LF2");
    leg1->AddEntry(histNorm5, "145 < #theta < 150", "LF2");
    leg1->SetBorderSize(0);
    leg1->SetFillColor(0);
    leg1->SetTextFont(42);
    leg1->Draw();
    
    TCanvas *c4 = new TCanvas();
    hist_ThetaEta_clone->Draw("colz");
}