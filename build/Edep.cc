void Edep(){
    TFile *f1 = new TFile("output_0.root", "READ");

    //TH2F *histCorr = new TH2F("Energy Deposit", "Energy Deposit;E_{dep}(Compton) (MeV);E_{dep}(Photoelectric) (MeV)", 100, 0, 0.6, 100, 0, 0.6);
    TH1F *histEdepCompt = new TH1F("Energy Deposited (Compton)", "Energy Deposited (Compton);E_{dep} (MeV);Counts", 100, 0, 0.6);
    TH1F *histEdepPhotoP = new TH1F("Energy Deposited", "Energy Deposited;E_{dep} (MeV);Counts", 100, 0, 0.6);
    TH1F *histEdepTotal = new TH1F("Energy Deposited (Total)", "Energy Deposited (Total);E_{dep} (MeV);Counts", 100, 0, 0.6);
    
    TTree *t1 = (TTree*)f1->Get("Events"); 
    double Energy_Deposited_Compton, Energy_Deposited_Photoelectric, Energy_Deposited_Total;
    t1->SetBranchAddress("Energy_Deposited_Compton", &Energy_Deposited_Compton);
    t1->SetBranchAddress("Energy_Deposited_Photoelectric", &Energy_Deposited_Photoelectric);
    t1->SetBranchAddress("Energy_Deposited_Total", &Energy_Deposited_Total);



    int entries1;

    entries1 = t1->GetEntries();
    
    cout << entries1 << endl;
    for(int i = 0; i<entries1; i++){
        t1->GetEntry(i);
        
        histEdepCompt->Fill(Energy_Deposited_Compton);
        histEdepPhotoP->Fill(Energy_Deposited_Photoelectric);
        histEdepTotal->Fill(Energy_Deposited_Total);
        //histCorr->Fill(Energy_Deposited_Compton, Energy_Deposited_Photoelectric);


    }

    histEdepCompt->SetLineColor(kBlue);
    histEdepPhotoP->SetLineColor(kRed);
    histEdepTotal->SetLineColor(kBlack);

    TCanvas *c1 = new TCanvas();
    histEdepPhotoP->Draw();
    histEdepCompt->Draw("same");
    histEdepTotal->Draw("same");

    TLegend *leg1 = new TLegend(0.7, 0.7, 0.8, 0.8);
    leg1->AddEntry(histEdepCompt, "Compton", "LF2");
    leg1->AddEntry(histEdepPhotoP, "Photoelectric", "LF2");
    leg1->AddEntry(histEdepTotal, "Total", "LF2");
    leg1->SetBorderSize(0);
    leg1->SetFillColor(0);
    leg1->SetTextFont(42);
    leg1->Draw();

    //TCanvas *c2 = new TCanvas();
    //histEdepPhotoP->Draw();
    //TCanvas *c3 = new TCanvas();
    //histEdepTotal->Draw();

    //TCanvas *c2 = new TCanvas();
    //histCorr->Draw("colz");
}