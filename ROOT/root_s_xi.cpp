void graph(){
    TGraphErrors* graph = new TGraphErrors("../data/s_xi/s_xi_withpow.txt", "%lg %lg %lg %lg");
    graph->SetTitle("#s_#xi values");
    graph->SetLineColor(kBlue);
    graph->GetXaxis()->SetTitle("Probability p");
    graph->GetYaxis()->SetTitle("#s_#xi");
    graph->SetMarkerSize(.5);
    graph->SetMarkerStyle(21);
    graph->SetLineWidth(2);
    graph->Draw();


    /* TF1* f = new TF1("l","[2]*TMath::Power(x-[0],[1])",0.595,0.63);
    f->SetParameter(0,0.59);
    f->SetParameter(1,0.14);
    f->SetParameter(2,1);
    graph->Fit(f,"R"); */

    //leg->AddEntry(graph5, "p=p_c");
    /* leg->AddEntry(graph5, "p=0.59");
    leg->AddEntry(graph6, "p=0.594");
    leg->AddEntry(graph7, "p=0.6"); */

}