#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <iterator>
#include <cmath>

void anal(int N)
{
    std::string name = std::to_string(N);
    std::ifstream ifile{"../data/mean_cluster_size/mcs_N"+ name +"_new.txt"};
    std::ofstream ofile;
    ofile.open("../data/mean_cluster_size/mcs_mean_N"+ name +"_new.txt", std::ios::trunc);

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
    std::ifstream ifilesd{"../data/mean_cluster_size/mcs_N"+name+"_new.txt"};

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
        ofile << it->first << " " << ((it->second) / (occ[it->first])) << " 0 " << (std::sqrt((variance[it->first]) / (occ[it->first] - 1))) / (std::sqrt(occ[it->first])) << std::endl;

        
    }
    ofile.close();
}

void graph()
{
    // anal();
    TGraphErrors *graph = new TGraphErrors("../data/mean_cluster_size/mcs_mean_N200_new.txt", "%lg %lg %lg %lg");
    graph->SetTitle("Mean cluster size");
    graph->GetXaxis()->SetTitle("Probability p");
    graph->GetYaxis()->SetTitle("MCS #chi");
    graph->SetMinimum(-1);
    graph->SetMaximum(30);
    graph->SetMarkerSize(.5);
    graph->SetMarkerStyle(21);
    graph->SetLineWidth(2);

    graph->SetLineColor(kBlue);
    graph->Draw();

    TGraphErrors *graph2 = new TGraphErrors("../data/mean_cluster_size/mcs_mean_N1000_new.txt", "%lg %lg %lg %lg");
    graph2->SetTitle("Mean cluster size");
    graph2->GetXaxis()->SetTitle("Probability p");
    graph2->GetYaxis()->SetTitle("MCS #chi");
    graph2->SetMinimum(-1);
    graph2->SetMaximum(30);
    graph2->SetMarkerSize(.5);
    graph2->SetMarkerStyle(21);
    graph2->SetLineWidth(2);

    graph2->SetLineColor(kRed);
    graph2->Draw("Same");
    TGraphErrors *graph3 = new TGraphErrors("../data/mean_cluster_size/mcs_mean_N500_new.txt", "%lg %lg %lg %lg");
    graph3->SetTitle("Mean cluster size");
    graph3->GetXaxis()->SetTitle("Probability p");
    graph3->GetYaxis()->SetTitle("MCS #chi");
    graph3->SetMinimum(-1);
    graph3->SetMaximum(30);
    graph3->SetMarkerSize(.5);
    graph3->SetMarkerStyle(21);
    graph3->SetLineWidth(2);

    graph3->SetLineColor(kGreen);
    graph3->Draw("Same");

    TLine* line = new TLine(0.5927,0,0.5927,28);
    line->SetLineColor(kBlack);
    line->SetLineWidth(2);
    line->Draw("Same");

    TF1 *f = new TF1("l", "[0]*std::pow(std::abs(x-[2]),-[1])", 0.50, 0.58);
    f->SetParameter(0, 0.4);
    f->SetParameter(1, 2.388);
    f->SetParameter(2, 0.593);
    //f->Draw("Same");
    //graph->Fit(f,"R");

    TLegend* leg = new TLegend(0.1,0.6,0.48,0.8);
    leg->AddEntry(graph,"N=200x200");
    leg->AddEntry(graph2, "N=1000x1000");
    //leg->AddEntry(graph2,"N=500");
    //leg->AddEntry(graph5, "p=p_c");
    /* leg->AddEntry(graph5, "p=0.59");
    leg->AddEntry(graph6, "p=0.594");
    leg->AddEntry(graph7, "p=0.6"); */
    leg->Draw();
}
