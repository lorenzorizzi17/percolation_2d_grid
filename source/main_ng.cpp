#include"network.hpp"
#include<vector>
#include<algorithm>
#include<string>
#include<fstream>
#include<numeric>


int main() {
    //setting random seed
    srand((unsigned)time(NULL));

    //graphic constants and parameters
    const int N = 50*50;     //n. of sites (perfect square)
    const int n = std::sqrt(N);
    //Creating the network
    std::ofstream fout{ "Ratiovalue_N" + std::to_string(n) + ".txt" };
    //std::ofstream fout{ "Chivalue_N" + std::to_string(n) + ".txt" };
    for (double p = 0.591; p < 0.595; p += 0.0001) {
        double ratios[10000];
        //std::ofstream fout("clusterdistribution_N" + std::to_string(n) + "_p" + std::to_string(int(p * 100)) + ".txt");
        for (int j = 0; j < 10000; j++) {
            Network network = Network(n);
            network.fillRandomWeights();
            network.buildNetwork(p);
            network.formCluster();

            double ratio = network.computeRatio();
            ratios[j] = ratio;
            
        }
        std::cout << p << std::endl;
        for (int i = 0; i < 10000; i++) {
            fout << p << " " << ratios[i] << std::endl;
        }
    }
}