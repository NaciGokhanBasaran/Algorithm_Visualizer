#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>


int width = 1200;   
int height = 900;   
bool dropdownMenuOpen = false;    

struct dropDownMenuItem {  
    sf::Text AlgorithmName;
    sf::RectangleShape shape; 
    std::string name;
    int posx, posy, width, height;
    bool isOpen;
    sf::Font font;

    dropDownMenuItem(std::string name, int x, int y, int w, int h, bool isOpen, const sf::Font& font)
        : name(name), posx(x), posy(y), width(w), height(h), isOpen(isOpen), font(font) {
        shape.setSize(sf::Vector2f(width, height));
        shape.setPosition(posx, posy);
        shape.setFillColor(sf::Color(47, 47, 55));

        AlgorithmName.setFont(font);
        AlgorithmName.setString(name);
        AlgorithmName.setCharacterSize(15);
        AlgorithmName.setFillColor(sf::Color::White);
        AlgorithmName.setPosition(posx + 10, posy + 10); 
    }

    void draw(sf::RenderWindow& window) {
        if (isOpen) {
            AlgorithmName.setString(name);  
            window.draw(shape);
            window.draw(AlgorithmName);
        }
    }
};

struct datarect {
    sf::RectangleShape shape;
    float value;
    float w, h, x, y;
    sf::Color color;

    datarect(float value, float w, float h, float x, float y, sf::Color color)
        : value(value), w(w), h(h), x(x), y(y), color(color) {
        shape.setSize(sf::Vector2f(w, h));
        shape.setPosition(x, y);
        shape.setFillColor(color);
        shape.setOutlineThickness(1.0f);
        shape.setOutlineColor(sf::Color::Red);
    }
};

template <typename T>
void swap(T& x, T& y) {
    T temp = x;
    x = y;
    y = temp;
}

void drawComponents(sf::RenderWindow& window, sf::RectangleShape& sidebar,
    std::vector<dropDownMenuItem>& dropDownMenu, sf::RectangleShape& startButton,
    sf::RectangleShape& resetButton, sf::RectangleShape& windowButton, sf::RectangleShape& dropdownbutton,
    sf::Text& titleText, sf::RectangleShape& rect,
    std::vector<datarect>& dataSet) {
    window.clear(sf::Color(34, 34, 46));
    window.draw(sidebar);
    sf::Font font; 
    if (!font.loadFromFile("arial.ttf")) { 
        std::cerr << "Font yüklenemedi!" << std::endl; 
         
    } 
      
    sf::Text ResetButtonText;
    ResetButtonText.setFont(font);  
    ResetButtonText.setString("Restrart");
    ResetButtonText.setPosition(55, 470);

    ResetButtonText.setCharacterSize(16);
    ResetButtonText.setFillColor(sf::Color::White);
    
    sf::Text RunButtonText; 
    RunButtonText.setFont(font); 
    RunButtonText.setString("Run");
    RunButtonText.setPosition(110, 611);

    RunButtonText.setCharacterSize(30); 
    RunButtonText.setFillColor(sf::Color::White);  
    if (dropdownMenuOpen) {
        for (auto& item : dropDownMenu) {
            item.draw(window);
        }
    }
    else {
        dropDownMenu[0].isOpen = true;
        dropDownMenu[0].draw(window);
    }

    window.draw(startButton);
    window.draw(resetButton);
    window.draw(windowButton);
    window.draw(titleText);
    window.draw(dropdownbutton);
    window.draw(rect);
    window.draw(ResetButtonText); 
    window.draw(RunButtonText); 
    for (auto& data : dataSet) {
        window.draw(data.shape);
    }
    window.display();
}

void BubbleSort(std::vector<datarect>& dataSet, sf::RenderWindow& window,
    sf::RectangleShape& sidebar, std::vector<dropDownMenuItem>& dropDownMenu,
    sf::RectangleShape& startButton, sf::RectangleShape& resetButton,
    sf::RectangleShape& windowButton, sf::RectangleShape& dropdownbutton,
    sf::Text& titleText, sf::RectangleShape& rect) {
    for (int i = 0; i < dataSet.size(); i++) {
        for (int j = i + 1; j < dataSet.size(); j++) {
            dataSet[i].color = sf::Color::Red;
            dataSet[j].color = sf::Color::Red;

            dataSet[i].shape.setFillColor(dataSet[i].color);
            dataSet[j].shape.setFillColor(dataSet[j].color);

            drawComponents(window, sidebar, dropDownMenu, startButton, resetButton,
                windowButton, dropdownbutton, titleText, rect, dataSet);
            sf::sleep(sf::milliseconds(100));

            if (dataSet[i].value > dataSet[j].value) {

                swap(dataSet[i].x, dataSet[j].x);  

                dataSet[i].shape.setPosition(dataSet[i].x, dataSet[i].y);
                dataSet[j].shape.setPosition(dataSet[j].x, dataSet[j].y);

                swap(dataSet[i], dataSet[j]);
            }

            dataSet[j].color = sf::Color::Green;
            dataSet[j].shape.setFillColor(dataSet[j].color);
        }
        dataSet[i].color = sf::Color::Green;
        dataSet[i].shape.setFillColor(dataSet[i].color);
    }

    drawComponents(window, sidebar, dropDownMenu, startButton, resetButton,
        windowButton, dropdownbutton, titleText, rect, dataSet);
}
void SelectionSort(std::vector<datarect>& dataSet, sf::RenderWindow& window,
    sf::RectangleShape& sidebar, std::vector<dropDownMenuItem>& dropDownMenu,
    sf::RectangleShape& startButton, sf::RectangleShape& resetButton,
    sf::RectangleShape& windowButton, sf::RectangleShape& dropdownbutton,
    sf::Text& titleText, sf::RectangleShape& rect) {
    for (int i = 0; i < dataSet.size(); i++) {
        int minIndex = i; 

        for (int j = i + 1; j < dataSet.size(); j++) {
            dataSet[i].color = sf::Color::Red;
            dataSet[j].color = sf::Color::Red;

            dataSet[i].shape.setFillColor(dataSet[i].color);
            dataSet[j].shape.setFillColor(dataSet[j].color);
            drawComponents(window, sidebar, dropDownMenu, startButton, resetButton,
                windowButton, dropdownbutton, titleText, rect, dataSet);
            sf::sleep(sf::milliseconds(100));
            
            if (dataSet[minIndex].value > dataSet[j].value) {
                minIndex = j;
            }
            dataSet[i].color = sf::Color::Green;
            dataSet[j].color = sf::Color::Green;

            dataSet[i].shape.setFillColor(dataSet[i].color);
            dataSet[j].shape.setFillColor(dataSet[j].color);
            drawComponents(window, sidebar, dropDownMenu, startButton, resetButton,
                windowButton, dropdownbutton, titleText, rect, dataSet);
        }

        if(minIndex !=i)
        {

            
            swap(dataSet[i].x, dataSet[minIndex].x);
            dataSet[i].shape.setPosition(dataSet[i].x, dataSet[i].y);
            dataSet[minIndex].shape.setPosition(dataSet[minIndex].x, dataSet[minIndex].y);

            swap(dataSet[i], dataSet[minIndex]);  

        }
        drawComponents(window, sidebar, dropDownMenu, startButton, resetButton,
            windowButton, dropdownbutton, titleText, rect, dataSet);
    }
}
void InsertionSort(std::vector<datarect>& dataSet, sf::RenderWindow& window,
    sf::RectangleShape& sidebar, std::vector<dropDownMenuItem>& dropDownMenu,
    sf::RectangleShape& startButton, sf::RectangleShape& resetButton,
    sf::RectangleShape& windowButton, sf::RectangleShape& dropdownbutton,
    sf::Text& titleText, sf::RectangleShape& rect) {

    for (int i = 1; i < dataSet.size(); i++) { 
        int j = i;

        while (j > 0 && dataSet[j - 1].value > dataSet[j].value) {
            
            dataSet[j].color = sf::Color::Red;
            dataSet[j - 1].color = sf::Color::Red;
            dataSet[j].shape.setFillColor(dataSet[j].color);
            dataSet[j - 1].shape.setFillColor(dataSet[j - 1].color);

            drawComponents(window, sidebar, dropDownMenu, startButton, resetButton,
                windowButton, dropdownbutton, titleText, rect, dataSet);
            sf::sleep(sf::milliseconds(100));

           
            swap(dataSet[j].x, dataSet[j - 1].x); 
            dataSet[j].shape.setPosition(dataSet[j].x, dataSet[j].y); 
            dataSet[j - 1].shape.setPosition(dataSet[j - 1].x, dataSet[j - 1].y); 
             
            
            swap(dataSet[j], dataSet[j - 1]);

            j--;  

            
            dataSet[j].color = sf::Color::Green;
            dataSet[j].shape.setFillColor(dataSet[j].color);
        }

        
        dataSet[i].color = sf::Color::Green;
        dataSet[i].shape.setFillColor(dataSet[i].color);

       
        drawComponents(window, sidebar, dropDownMenu, startButton, resetButton,
            windowButton, dropdownbutton, titleText, rect, dataSet);
    }
}

void reset_dataSet(const std::vector<float>& list, std::vector<datarect>& dataSet) {
    int rectWidth = 700; 
    int rectHeight = 500; 
    float RectangleWidth = static_cast<float>(rectWidth) / list.size();
    float factor = (rectHeight - 150) / (*std::max_element(list.begin(), list.end()));

    dataSet.clear();
    for (int i = 0; i < list.size(); i++) {
        float RectangleHeight = factor * list[i];
        float rectTopY = rectHeight - RectangleHeight + 100;
        datarect newData(list[i], RectangleWidth, RectangleHeight, (400 + i * RectangleWidth), rectTopY, sf::Color::Green);
        dataSet.push_back(newData);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(width, height), "Algorithm Visualization");

    std::vector<float> list = { 2,5,8,3,12,1 };
    std::vector<float> copy_list = list;
    std::vector<datarect> dataSet;
    reset_dataSet(list, dataSet);

    // Sidebar
    sf::RectangleShape sidebar(sf::Vector2f(300, height));
    sidebar.setPosition(0, 0);
    sidebar.setFillColor(sf::Color(17, 17, 25));
    sidebar.setOutlineThickness(5.0f);
    sidebar.setOutlineColor(sf::Color(114, 24, 36));

    // Load font
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Font yüklenemedi!" << std::endl;
        return -1;
    }

    // DropDown Menu
    std::vector<std::string> Algorithms = { "Bubble Sort", "Selection Sort", "Insertion Sort" };
    std::vector<dropDownMenuItem> dropDownMenu;
    for (int i = 0; i < Algorithms.size(); i++) {
        dropDownMenu.emplace_back(Algorithms[i], 50, 200 + (i * 40), 200, 40, true, font);
    }

    // Dropdown button
    sf::RectangleShape dropdownbutton(sf::Vector2f(40, 40));
    dropdownbutton.setPosition(210, 200);
    dropdownbutton.setFillColor(sf::Color::White);

    // Start Button
    sf::RectangleShape startButton(sf::Vector2f(200, 50));
    startButton.setPosition(50, 600);
    startButton.setFillColor(sf::Color(34, 177, 76));

    // Reset Button
    sf::RectangleShape resetButton(sf::Vector2f(75, 75));
    resetButton.setPosition(50, 450);
    resetButton.setFillColor(sf::Color(136, 0, 21));

    sf::Text ResetButtonText; 
    ResetButtonText.setFont(font);
    ResetButtonText.setString("Af"); 
    ResetButtonText.setPosition(50, 450); 
    
    ResetButtonText.setCharacterSize(25);
    ResetButtonText.setFillColor(sf::Color::Yellow);
   
   
    // Window Button
    sf::RectangleShape windowButton(sf::Vector2f(0, 0));
    windowButton.setPosition(175, 450);
    //windowButton.setFillColor(sf::Color(136, 0, 21));

    // Visualization 
    sf::RectangleShape rect(sf::Vector2f(700, 500));
    rect.setPosition(400, 200);
    rect.setOutlineThickness(8.0f);
    rect.setOutlineColor(sf::Color(0, 0, 0));

    // Text
    sf::Text titleText;
    titleText.setFont(font);
    titleText.setString("Algorithm Visualizer");
    titleText.setCharacterSize(30);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(25, 75);



    std::string chosenAlgorithm = dropDownMenu[0].name; 
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

                if (startButton.getGlobalBounds().contains(mousePos)) {
                    std::cout << "Sorting started!" << std::endl;
                    if (chosenAlgorithm == "Bubble Sort") {
                       BubbleSort(dataSet, window, sidebar, dropDownMenu, startButton, resetButton, windowButton, dropdownbutton,
                            titleText, rect); 

                    }
                    else if (chosenAlgorithm == "Selection Sort") {
                        SelectionSort(dataSet, window, sidebar, dropDownMenu, startButton, resetButton, windowButton, dropdownbutton,
                            titleText, rect); 
                    }
                    
                    else if (chosenAlgorithm == "Insertion Sort") {
                        InsertionSort(dataSet, window, sidebar, dropDownMenu, startButton, resetButton, windowButton, dropdownbutton,
                            titleText, rect); 
                    }
                } 

                if (dropdownbutton.getGlobalBounds().contains(mousePos)) {
                    dropdownMenuOpen = !dropdownMenuOpen; // Toggle dropdown menu visibility
                }
                if (dropdownMenuOpen) {
                    for (auto& item : dropDownMenu) {
                        if (item.shape.getGlobalBounds().contains(mousePos)) {  

                            swap(dropDownMenu[0].name, item.name); 
                            
                        }
                    }
                }

                if (resetButton.getGlobalBounds().contains(mousePos)) {
                    std::cout << "Restarted!" << std::endl;
                    dataSet.clear();
                    list = copy_list;
                    reset_dataSet(list, dataSet);
                }
            }
        }

        chosenAlgorithm = dropDownMenu[0].name;
        
        drawComponents(window, sidebar, dropDownMenu, startButton, resetButton,
            windowButton, dropdownbutton, titleText, rect, dataSet);
        
         
    }

    return 0;
}
