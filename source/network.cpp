#include"network.hpp"

/////////////////////////////////////////////////////////////////
//////////////////    FREE FUNCTIONS   //////////////////////////
/////////////////////////////////////////////////////////////////


double get_mean(std::vector<int> const& v) {
    int i = std::accumulate(v.begin(), v.end(), 0);
    int tot = v.size();
    return (double(i) / double(tot));
}

/////////////////////////////////////////////////////////////////
//////////////////  PRIVATE FUNCTIONS  //////////////////////////
/////////////////////////////////////////////////////////////////

//iterative method to identify the clusters. Nodes belonging to the same cluster have the same value in clusters_ matrix
void Network::search(double i, double j, int c) {
    //even if the node is not occupied or has already been classified in a cluster, the function search is called
    if ((clusters_.get(i, j) == 0) && (network_.get(i, j) == 1)) {
        clusters_.set(i, j) = c;
        //looking for the neighbouring nodes
        if (i == 0) {
            if (j == 0) {
                if (this->get(i + 1, j) == 1) {
                    this->search(i + 1, j, c);
                }
                if (this->get(i, j + 1) == 1) {
                    this->search(i, j + 1, c);
                }
            }
            else if (j == clusters_.size() - 1) {
                if (this->get(i + 1, j) == 1) {
                    this->search(i + 1, j, c);
                }
                if (this->get(i, j - 1) == 1) {
                    this->search(i, j - 1, c);
                }
            }
            else {
                if (this->get(i, j - 1) == 1) {
                    this->search(i, j - 1, c);
                }
                if (this->get(i + 1, j) == 1) {
                    this->search(i + 1, j, c);
                }
                if (this->get(i, j + 1) == 1) {
                    this->search(i, j + 1, c);
                }
            }
        }
        else if (i == clusters_.size() - 1) {
            if (j == 0) {
                if (this->get(i - 1, j) == 1) {
                    this->search(i - 1, j, c);
                }
                if (this->get(i, j + 1) == 1) {
                    this->search(i, j + 1, c);
                }
            }
            else if (j == clusters_.size() - 1) {
                if (this->get(i - 1, j) == 1) {
                    this->search(i - 1, j, c);
                }
                if (this->get(i, j - 1) == 1) {
                    this->search(i, j - 1, c);
                }
            }
            else {
                if (this->get(i, j - 1) == 1) {
                    this->search(i, j - 1, c);
                }
                if (this->get(i - 1, j) == 1) {
                    this->search(i - 1, j, c);
                }
                if (this->get(i, j + 1) == 1) {
                    this->search(i, j + 1, c);
                }
            }
        }
        else {
            if (this->get(i + 1, j) == 1) {
                this->search(i + 1, j, c);
            }
            if (this->get(i - 1, j) == 1) {
                this->search(i - 1, j, c);
            }
            if (this->get(i, j + 1) == 1) {
                this->search(i, j + 1, c);
            }
            if (this->get(i, j - 1) == 1) {
                this->search(i, j - 1, c);
            }
        }
    }
}

void Network::resetClustersMatrix() {
    for (int i = 0; i < weights_.size(); i++)
    {
        for (int j = 0; j < weights_.size(); j++) {
            clusters_.set(i, j) = (network_.get(i, j) == 0) ? -1 : 0;
        }
    }
}



/////////////////////////////////////////////////////////////////
//////////////////  PUBLIC FUNCTIONS  ///////////////////////////
/////////////////////////////////////////////////////////////////


//getter (row, column)
double Network::get(const int i, const int j) const
{
    return network_.get(i, j);
}

//setter (row,column)
double& Network::set(const double i, const double j)
{
    return network_.set(i, j);
}

void Network::fillRandomWeights() {
    int n = weights_.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            double a = double(rand()) / RAND_MAX;
            weights_.set(i, j) = a;
        }
    }
}

//builds the network once a probabilty p is specified 
void Network::buildNetwork(double const p) {
    int n = network_.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            network_.set(i, j) = (weights_.get(i, j) < p) ? 1 : 0;
        }
    }
}

//search for the clusters in the network and create clusters_ matrix 
void Network::formCluster() {
    this->resetClustersMatrix();
    int c = 1;
    for (int i = 0; i < network_.size(); i++)
    {
        for (int j = 0; j < network_.size(); j++)
        {
            if ((clusters_.get(i, j) == 0) && (network_.get(i, j) == 1)) {
                this->search(i, j, c);
                c++;
            }
        }
    }
}

//getter for the color code
int Network::getColorCode(int i, int j) const {
    return clusters_.get(i, j);
}
//print clusters matrix
void Network::print() { clusters_.print(); }

//returns distribution of clusters
std::vector<int> Network::writeClusters() {
    auto matrix = clusters_.getVector();
    std::vector<int> cl;
    for (int i = 0; i < matrix.size(); i++) {
        cl.insert(cl.end(), matrix[i].begin(), matrix[i].end());
    }
    std::vector<int> v;
    for (int c = 1; c < *std::max_element(cl.begin(),cl.end()); c++) {
        int count = 0;
        auto it = std::find(cl.begin(), cl.end(), c);
        while (it != std::end(cl)) {
            count++;
            it = std::find(it + 1, cl.end(), c);
        };
        if (count != 0) { v.push_back(count); };
    }
    return v;
}

int Network::computeLargestCluster() {
    auto v = this->writeClusters();
    auto res = std::max_element(v.begin(), v.end());
    return *res;
}


int Network::computeSecondLargestCluster() {
    int MAX_SIZE = this->computeLargestCluster();
    auto v = this->writeClusters();
    while (std::find(v.begin(), v.end(), MAX_SIZE) != v.end()) {
        v.erase(std::find(v.begin(), v.end(), MAX_SIZE));
    }
    auto res = std::max_element(v.begin(), v.end());
    return *res;
}

double Network::computeRatio() {
    int S_1 = this->computeLargestCluster();
    int S_2 = this->computeSecondLargestCluster();
    double ratio = double(S_1) / double(S_2);
    return ratio;
}

double Network::computeSvalue() {
    return double(this->computeLargestCluster()) / double((network_.size() * network_.size()));
}

void Network::highlightGiantCluster() {
    int maxValue = this->computeLargestCluster();
    auto matrix = clusters_.getVector();
    std::vector<int> cl;
    int cRight = 0;
    for (int i = 0; i < matrix.size(); i++) {
        cl.insert(cl.end(), matrix[i].begin(), matrix[i].end());
    }
    int cMax = *(std::max_element(cl.begin(), cl.end()));
    for (int c = 0; c < cMax; c++) {
        auto occ = std::count(cl.begin(), cl.end(), c);
        if (occ == maxValue) {
            cRight = c;
            break;
        }
    }
    for (int i = 0; i < clusters_.size(); i++) {
        for (int j = 0; j < clusters_.size(); j++) {
            if (clusters_.get(i, j) == cRight) {
                clusters_.set(i, j) = 1;
            }
            else {
                clusters_.set(i, j) = 0;
            }
        }
    }
}

double Network::get_MCS() {
    return get_mean(this->writeClusters());
}

