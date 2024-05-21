#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<map>
#include<cmath>

void anal(){
    //evaluating mean values for every p
    std::ifstream ifile{"data/Svalues700.txt"};
    std::ofstream ofile;
    ofile.open("Svalues700_mean.txt", std::ios::trunc);

    std::map<std::string, double> mean;
    std::map<std::string, int> occ;
    while(ifile.good()){
        std::string x;
        double y;
        ifile >> x >> y;
        auto it = mean.find(x);
        if(it == mean.end()){
            mean[x] = y;
            occ[x]++;
            
        } else {
            mean[x] += y;
            occ[x]++;
        }
    }

    ifile.close();
    

    //now evaluates standard deviation
    std::ifstream ifilesd{"Svalues700.txt"};

    std::map<std::string, double> variance;
    while(ifilesd.good()){
        std::string x;
        double y;
        ifilesd >> x >> y;
        auto it = variance.find(x);
        if(it == variance.end()){
            variance[x] = (y-(mean[x]/occ[x]))*(y-(mean[x]/occ[x]));
            
        } else {
            variance[x] += (y-(mean[x]/occ[x]))*(y-(mean[x]/occ[x]));
        }
    }
    
    for (auto it = mean.begin(); it != mean.end(); ++it) {
        std::cout << "Prob: " << it->first << ", mean: " << (it->second)/(occ[it->first])  << std::endl;
        std::cout << "Occur: " << occ[it->first] << std::endl;
        std::cout << "SDOM: " << (std::sqrt((variance[it->first])/(occ[it->first]-1)))/(std::sqrt(occ[it->first])) << std::endl;
        ofile << it->first << " " << (it->second)/(occ[it->first]) << " 0 " << (std::sqrt((variance[it->first])/(occ[it->first]-1)))/(std::sqrt(occ[it->first])) <<std::endl;
    }

    ofile.close();
}


void graph(){
    anal();
    TGraphErrors* graph = new TGraphErrors("Svalues700_mean.txt", "%lg %lg %lg %lg");
    graph->SetTitle("S values on a 2D grid");
    graph->SetLineColor(kBlue);
    graph->GetXaxis()->SetTitle("Probability p");
    graph->GetYaxis()->SetTitle("S values");
    graph->SetMinimum(-0.1);
    graph->SetMaximum(0.8);
    graph->SetMarkerSize(.5);
    graph->SetMarkerStyle(21);
    graph->SetLineWidth(2);

    TGraphErrors* graph2 = new TGraphErrors("Svalues500_mean.txt","%lg %lg %lg %lg");
    graph2->SetLineColor(kGreen);
    graph2->SetMarkerSize(.5);
    graph2->SetMarkerStyle(21);
    graph2->SetMarkerColor(kBlack);
    graph2->SetLineWidth(2);

    

    graph->Draw();
    graph2->Draw("Same");


    /* TF1* f = new TF1("l","[2]*TMath::Power(x-[0],[1])",0.595,0.63);
    f->SetParameter(0,0.59);
    f->SetParameter(1,0.14);
    f->SetParameter(2,1);
    graph->Fit(f,"R"); */

    TLegend* leg = new TLegend(0.1,0.6,0.48,0.8);
    leg->AddEntry(graph,"N=700");
    leg->AddEntry(graph2,"N=500");
    //leg->AddEntry(graph5, "p=p_c");
    /* leg->AddEntry(graph5, "p=0.59");
    leg->AddEntry(graph6, "p=0.594");
    leg->AddEntry(graph7, "p=0.6"); */
    leg->Draw();

}