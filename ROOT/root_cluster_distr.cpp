#include<fstream>
#include<string>
#include<iostream>
#include<numeric>
#include<cmath>

void histo(){
    double max =500000.5;
    int bin = int(max-0.5);
    const int n = 8;

    TH1F* hist[n];
    std::string p[n] = {"52","53","54","55","56","57","58","59"};
    for (int i = 0; i < n; i++)
    {
        hist[i] = new TH1F("","",bin,0.5,max);
        std::ifstream file;
        std::string n = "clusterdistribution_N1000_p" + p[i] + ".txt";
        file.open(n);
    
        while(file.good()){
            double x=0;
            file >> x;
            hist[i]->Fill(x);
        }
        hist[i]->SetLineColor(i+1);
        hist[i]->Draw("Same");
        file.close();
    }
    for (int i = 0; i < n; i++){
        //int tot = 0;
        std::ofstream ofile;
        ofile.open("clustergraph_N1000_p" + p[i] + ".txt");
        /* for (int k = 0; k < bin; k++)
        {
            tot += hist[i]->GetBinContent(k+1);
        } */
        
        for (int j = 1; j < bin; j++)
        {
            if ((hist[i]->GetBinContent(j))!=0){
                    ofile << j*(max/bin) << " " << (hist[i]->GetBinContent(j)) << " 0 " <<  std::sqrt((hist[i]->GetBinContent(j))) << std::endl;
            }
            
        }
        ofile.close(); 
    }     
}

void graph(){
    TGraph* graph0 = new TGraph("clustergraph_N1000_p20.txt", "%lg %lg");
    graph0->SetTitle("Cluster distribution p = 0.2");
    graph0->SetMarkerStyle(4);
    graph0->SetMarkerSize(1);
    graph0->SetLineColor(1);
    graph0->SetMarkerColor(1);
    graph0->Draw("AP");
    TF1* fit1 = new TF1("lin","[0]*std::pow(x,-[1])",1,20);
    fit1->SetParameter(0,1E5);
    fit1->SetParameter(1,10);
    fit1->SetLineColor(1);
    //graph0->Fit(fit1,"R");
    
    TGraph* graph1 = new TGraph("clustergraph_N1000_p30.txt", "%lg %lg");
    graph1->SetTitle("Cluster distribution p = 0.3");
    graph1->SetMarkerStyle(4);
    graph1->SetMarkerSize(1);
    graph1->SetLineColor(2);
    graph1->SetMarkerColor(2);
    graph1->Draw("Same,P");
    TF1* fit2 = new TF1("lin2","[0]*std::pow(x,-[1])",1,100);
    fit2->SetParameter(0,1E5);
    fit2->SetParameter(1,10);
    fit2->SetLineColor(2);
    //graph1->Fit(fit2,"R");

    TGraph* graph2 = new TGraph("clustergraph_N1000_p40.txt", "%lg %lg");
    graph2->SetTitle("Cluster distribution p = 0.4");
    graph2->SetMarkerStyle(4);
    graph2->SetMarkerSize(1);
    graph2->SetMarkerColor(3);
    graph2->SetLineColor(3);
    graph2->Draw("Same,P");
    TF1* fit3 = new TF1("lin3","[0]*std::pow(x,-[1])",1,100);
    fit3->SetParameter(0,1E5);
    fit3->SetParameter(1,10);
    fit3->SetLineColor(3);
    //graph2->Fit(fit3,"R");



    TGraph* graph3 = new TGraph("clustergraph_N1000_p50.txt", "%lg %lg");
    graph3->SetTitle("Cluster distribution p = 0.5");
    graph3->SetMarkerStyle(4);
    graph3->SetMarkerSize(1);
    graph3->SetMarkerColor(4);
    graph3->SetLineColor(4);
    graph3->Draw("Same,P");
    TF1* fit4 = new TF1("lin4","[0]*std::pow(x,-[1])",1,200);
    fit4->SetParameter(0,1E5);
    fit4->SetParameter(1,10);
    fit4->SetLineColor(4);
    //graph3->Fit(fit4,"R");



    TGraph* graph4 = new TGraph("clustergraph_N1000_p60.txt", "%lg %lg");
    graph4->SetTitle("Cluster distribution p = 0.6");
    graph4->SetMarkerStyle(4);
    graph4->SetMarkerSize(1);
    graph4->SetLineColor(5);
    graph4->SetMarkerColor(5);
    graph4->Draw("Same,P");
    TF1* fit5 = new TF1("lin5","[0]*std::pow(x,-[1])",1,200);
    fit5->SetParameter(0,1E5);
    fit5->SetParameter(1,10);
    fit5->SetLineColor(5);
    //graph4->Fit(fit5,"R");

    /* TGraph* graph5 = new TGraph("clustergraph_N1000_pc.txt", "%lg %lg");
    graph5->SetTitle("Cluster distribution p = $p_c$");
    graph5->SetMarkerStyle(4);
    graph5->SetMarkerSize(1);
    graph5->SetLineColor(6);
    graph5->SetMarkerColor(6);
    graph5->Draw("Same,L");
    TF1* fit6 = new TF1("lin6","[0]*std::pow(x,-[1])",1,80);
    fit6->SetParameter(0,1E5);
    fit6->SetParameter(1,10);
    fit6->SetLineColor(6);
    graph5->Fit(fit6,"RL"); */

    graph4->GetYaxis()->SetRange(0,100000);
    graph4->GetXaxis()->SetRange(1,100000);
    gPad->SetLogy();
    gPad->SetLogx();
    /* TGraph* graph5 = new TGraph("cluster_graph59.txt", "%lg %lg");
    graph5->SetMarkerStyle(4);
    graph5->SetLineColor(6);
    graph5->SetMarkerColor(6);
    graph5->Draw("Same,LP");
    TGraph* graph6 = new TGraph("cluster_graph594.txt", "%lg %lg");
    graph6->SetMarkerStyle(4);
    graph6->SetLineColor(7);
    graph6->SetMarkerColor(7);
    graph6->Draw("Same,LP");
    TGraph* graph7 = new TGraph("cluster_graph60.txt", "%lg %lg");
    graph7->SetMarkerStyle(4);
    graph7->SetLineColor(8);
    graph7->SetMarkerColor(8);
    graph7->Draw("Same,LP"); */


    TLegend* leg = new TLegend(0.1,0.6,0.48,0.8);
    leg->AddEntry(graph0,"p=0.2");
    leg->AddEntry(graph1,"p=0.3");
    leg->AddEntry(graph2, "p=0.4");
    leg->AddEntry(graph3, "p=0.5");
    leg->AddEntry(graph4, "p=0.6");
    //leg->AddEntry(graph5, "p=p_c");
    /* leg->AddEntry(graph5, "p=0.59");
    leg->AddEntry(graph6, "p=0.594");
    leg->AddEntry(graph7, "p=0.6"); */
    leg->Draw();
    
}



void singleGraph(int p){
    std::string s = "../data/cluster_distribution/clustergraph_N1000_p" + std::to_string(p) +".txt";
    //std::string s = "clustergraph_N1000_pc.txt";
    const char *cstr = s.c_str();
    TGraphErrors* graph = new TGraphErrors(cstr, "%lg %lg %lg %lg");

    std::string title = "Cluster distribution p = 0." + std::to_string(p);
    //std::string title = "Cluster distribution p = p_c";
    graph->SetTitle(title.c_str());
    graph->SetMarkerStyle(4);
    graph->SetMarkerSize(1);
    graph->SetMarkerColor(kBlue);
    graph->Draw("AP");

    TF1* fit = new TF1("lin","[0]*exp(-x/[1])*std::pow(x,-[2])",10,200);
    fit->SetParameter(0,10000);
    fit->SetParameter(1,10); 
    fit->SetParameter(2,2.033);
    fit->SetLineColor(kRed);
    graph->Fit(fit,"R");

    graph->GetYaxis()->SetRange(0,50000);
    graph->GetXaxis()->SetRange(-1,500);

    gPad->SetLogy();
}


void createSingleHisto(int p){
    double max =500.5;
    int bin = int(max-0.5);
    std::string name_s = "Cluster distribution for p = 0." + std::to_string(p);
    const char* name = name_s.c_str();
    TH1F* totHisto = new TH1F(name,name,bin,0.5,max);
    totHisto->Sumw2(true);
    const int NUM = 100;
    for (int j = 0; j < NUM; j++)
    {
        std::ifstream file;
        std::string n = "../data/cluster_distribution/clusterdistribution_N1000_p" + std::to_string(p) + "_"+std::to_string(j)+ ".txt";
        file.open(n);
    
        while(file.good()){
            double x=0;
            file >> x;
            totHisto->Fill(x);
        }
        file.close();
    }
    TF1* plat = new TF1("plat", "1",0,max);
    totHisto->Divide(plat, NUM);
    totHisto->Draw();

    TF1* fit = new TF1("lin","[0]*exp(-x/[1])*std::pow(x,-[2])",150,max);
    fit->SetParameter(0,10000);
    fit->SetParameter(1,100000); 
    fit->SetParameter(2,2.033);
    fit->SetLineColor(kRed);

    gPad->SetLogy();
    totHisto->Fit(fit,"R");
}
