
#include"network.hpp"
#include<vector>
#include<algorithm>
#include<SFML/Graphics.hpp>

std::ostream& operator<<(std::ostream& stream, std::vector<int> v) {
    stream << "(";
    for (auto it = v.begin(); it != v.end() - 1; it++) {
        stream << *it << ", ";
    }
    stream << *(v.end() - 1) << ")\n";
    return stream;
}


int main() {
    //setting random seed
    srand((unsigned)time(NULL));

    //graphic constants and parameters
    const int N = 250 * 250;     //n. of cells (perfect square)
    const int n = std::sqrt(N);
    double p = 0.2;
    unsigned const display_height = 0.9 * sf::VideoMode::getDesktopMode().height; //=768
    int const fps = 60;
    double const R = (double)display_height / n;


    //Creating the network
    Network network = Network(n);
    //filling the network with random weights
    network.fillRandomWeights();
    //now builds it based on assigne p
    network.buildNetwork(p);
    //runs the algorithm to recognize clusters
    network.formCluster();

    //graphic sfml
    sf::RenderWindow window(sf::VideoMode(display_height, display_height), "Forest fire percolation", sf::Style::Default);
    //window.setFramerateLimit(fps);
    //graphic loop
    while (window.isOpen())
    {
        //handling the events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {

                }
            }
            window.clear(sf::Color::White);



            //for every p, builds again the network
            network.buildNetwork(p);
            network.formCluster();

            //uncomment this line to selectively colour the largest cluster 
            //network.highlightGiantCluster();
            

            //drawing the grid
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    sf::RectangleShape unity(sf::Vector2f(R, R));
                    unity.setPosition(i * R, R * j);
                    /*if (network.get(i, j) != 0) {
                        int cNumber = network.getColorCode(i, j);
                        if (cNumber == 0) { unity.setFillColor(sf::Color::White); }
                        else { unity.setFillColor(sf::Color::Black); }
                        window.draw(unity);
                    }*/
                    if (network.get(i, j) != 0) {
                         int color_code = network.getColorCode(i, j);
                         std::seed_seq seed{ color_code };
                         std::mt19937 generator(seed);
                         std::uniform_int_distribution<int> distribution(1, 254);
                         sf::Color color{ sf::Uint8(distribution(generator)),sf::Uint8(distribution(generator)),sf::Uint8(distribution(generator)) };
                         unity.setFillColor(color);
                         window.draw(unity);
                     }
                }
            }

            //set this to true to save an image of the grid at every iteration of p
            if (false) {
                sf::Texture texture;
                texture.create(window.getSize().x, window.getSize().y);
                texture.update(window);
                sf::Image screenshot = texture.copyToImage();
                std::string name = "screenshot_N"  + std::to_string(N)+ "_GiantCluster_" + std::to_string(p) + ".png";
                auto var = screenshot.saveToFile(name);
                std::cerr << p << '\n';
                p += 0.005;
            }

            //update the graphical buffer
            window.display();
        }

    }
}
