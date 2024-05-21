#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <iterator>
#include <cmath>

void anal(int p)
{
    std::ifstream ifile{"../data/finite_analysis/finite_N" + std::to_string(p)+".txt"};
    std::ofstream ofile;
    ofile.open("../data/finite_analysis/finite_mean_N"+ std::to_string(p)+".txt", std::ios::trunc);

    std::map<std::string, double> mean;
    std::map<std::string, int> occ;
    while (ifile.good())
    {
        std::string x;
        double y;
        ifile >> x >> y;
        auto it = mean.find(x);
        if (it == mean.end())
        {
            mean[x] = y;
            occ[x]++;
        }
        else
        {
            mean[x] += y;
            occ[x]++;
        }
    }

    ifile.close();

    // now evaluates standard deviation
    std::ifstream ifilesd{"../data/finite_analysis/finite_N" + std::to_string(p)+".txt"};

    std::map<std::string, double> variance;
    while (ifilesd.good())
    {
        std::string x;
        double y;
        ifilesd >> x >> y;
        auto it = variance.find(x);
        if (it == variance.end())
        {
            variance[x] = (y - (mean[x] / occ[x])) * (y - (mean[x] / occ[x]));
        }
        else
        {
            variance[x] += (y - (mean[x] / occ[x])) * (y - (mean[x] / occ[x]));
        }
    }

    for (auto it = mean.begin(); it != mean.end(); ++it)
    {
        std::cout << "Prob: " << it->first << ", mean: " << (it->second) / (occ[it->first]) << std::endl;
        std::cout << "Occur: " << occ[it->first] << std::endl;
        std::cout << "SDOM: " << (std::sqrt((variance[it->first]) / (occ[it->first] - 1))) / (std::sqrt(occ[it->first])) << std::endl;
        ofile << it->first << " " << (it->second) / (occ[it->first]) << " 0 " << (std::sqrt((variance[it->first]) / (occ[it->first] - 1))) / (std::sqrt(occ[it->first])) << std::endl;
        
    }
    ofile.close();
}


void graph()
{

    // anal();
    TGraphErrors *graph = new TGraphErrors("../data/finite_analysis/finite_mean_N100.txt", "%lg %lg %lg %lg");
    graph->SetTitle("Finite size analysis");
    graph->GetXaxis()->SetTitle("Probability p");
    graph->GetYaxis()->SetTitle("S_1 / S_2");
    graph->SetMinimum(3);
    graph->SetMaximum(10);
    graph->SetMarkerSize(.5);
    graph->SetMarkerStyle(21);
    graph->SetLineWidth(2);
    graph->SetLineColor(kBlue);
    graph->Draw("ALP");

    TGraphErrors *graph2 = new TGraphErrors("../data/finite_analysis/finite_mean_N200.txt", "%lg %lg %lg %lg");
    graph2->SetTitle("Finite size analysis");
    graph2->GetXaxis()->SetTitle("Probability p");
    graph2->GetYaxis()->SetTitle("S_1 / S_2");
    graph2->SetMinimum(0);
    graph2->SetMaximum(80);
    graph2->SetMarkerSize(.5);
    graph2->SetMarkerStyle(21);
    graph2->SetLineWidth(2);

    graph2->SetLineColor(kRed);
    graph2->Draw("Same");

    TGraphErrors *graph3 = new TGraphErrors("../data/finite_analysis/finite_mean_N300.txt", "%lg %lg %lg %lg");
    graph3->SetTitle("Finite size analysis");
    graph3->GetXaxis()->SetTitle("Probability p");
    graph3->GetYaxis()->SetTitle("S_1 / S_2");
    graph3->SetMinimum(0);
    graph3->SetMaximum(80);
    graph3->SetMarkerSize(.5);
    graph3->SetMarkerStyle(21);
    graph3->SetLineWidth(2);

    graph3->SetLineColor(kCyan);
    graph3->Draw("Same");

    /* TF1 *f = new TF1("l", "[0]*std::pow(std::abs(x-[2]),-[1])", 0.4, 0.593);
    f->SetParameter(0, 0.01);
    f->SetParameter(1, 2.388);
    f->SetParameter(2, 0.593);
    //f->Draw("Same");
    graph->Fit(f,"R"); */

    TLegend* leg = new TLegend(0.1,0.6,0.48,0.8);
    leg->AddEntry(graph,"N=100x100");
    leg->AddEntry(graph2,"N=200x200");
    leg->AddEntry(graph3,"N=300x300");
    //leg->AddEntry(graph5, "p=p_c");
    /* leg->AddEntry(graph5, "p=0.59");
    leg->AddEntry(graph6, "p=0.594");
    leg->AddEntry(graph7, "p=0.6"); */
    leg->Draw();
}