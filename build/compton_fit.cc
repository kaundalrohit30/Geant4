double fit1(double *x, double *par){
    double fcn =  par[0]*(1-par[1]*cos(2*(x[0]*M_PI/180)));
    return fcn;
}

void compton_fit(){
    TFile *f1 = new TFile("Dphi_Correlation_60_theta_80_check.root", "READ");

    TH1F *h1 = (TH1F*)f1->Get("Corrected_dphi_dist(4)");
    TH1F *h2 = (TH1F*)f1->Get("Corrected_dphi_dist(7)");
    TH1F *h3 = (TH1F*)f1->Get("Corrected_dphi_dist(10)");


    TF1 *Fit1 = new TF1("Fit1", fit1, -160, 160, 2);

    //Fit1->SetParameter(0, 1);
    Fit1->SetParLimits(1, 0, 0.2);
    h1->Fit(Fit1, "R+");
    h2->Fit(Fit1, "R+");
    h3->Fit(Fit1, "R+");


    TCanvas *c1 = new TCanvas("", "", 800, 300);
    c1->Divide(3);
    c1->cd(1);
    h1->Draw();
    TPaveText *txt1 = new TPaveText(0.3, 0.4, 0.5, 0.7, "brNDC");
    txt1->AddText("60^{o} < #theta  < 80^{o}");
    txt1->AddText("d > 4 mm" );
    txt1->SetBorderSize(0);
    txt1->SetFillColor(0);
    txt1->SetTextFont(42);
    txt1->Draw();

    c1->cd(2);
    h2->Draw();
    TPaveText *txt2 = new TPaveText(0.3, 0.4, 0.5, 0.7, "brNDC");
    txt2->AddText("60^{o} < #theta  < 80^{o}");
    txt2->AddText("d > 7 mm" );
    txt2->SetBorderSize(0);
    txt2->SetFillColor(0);
    txt2->SetTextFont(42);
    txt2->Draw();

    c1->cd(3);
    h3->Draw();
    TPaveText *txt3 = new TPaveText(0.3, 0.4, 0.5, 0.7, "brNDC");
    txt3->AddText("60^{o} < #theta  < 80^{o}");
    txt3->AddText("d > 10 mm" );
    txt3->SetBorderSize(0);
    txt3->SetFillColor(0);
    txt3->SetTextFont(42);
    txt3->Draw();


}
