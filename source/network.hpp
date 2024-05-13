#include "matrix.hpp"

class Network {
private:
    Matrix network_;
    Matrix weights_;
    Matrix clusters_;
    void search(double, double, int);
    void resetClustersMatrix();
public:
    Network(int n) : network_{ Matrix(n, 0) }, weights_{ Matrix(n,0) }, clusters_{ Matrix(n,0) } {};
    double get(const int, const int) const;
    double& set(const double, const double);
    void fillRandomWeights();
    void buildNetwork(double const);
    void formCluster();
    void print();
    int getColorCode(int, int) const;
    std::vector<int> writeClusters();
    int computeLargestCluster();
    int computeSecondLargestCluster();
    double computeRatio();
    double computeSvalue();
    void highlightGiantCluster();
    double get_MCS();
};