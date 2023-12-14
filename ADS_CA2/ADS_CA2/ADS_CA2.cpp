#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "MyStack.h"
#include <regex>
#include "FileManager.h"
#include "FileStruct.h"
#include "TreeIterator.h"
#include "Tree.h"
using namespace std;

using namespace sf;

void guiDisplay(FileManager<MyItem> & filemanager,TreeIterator<MyItem> iter) {
    RenderWindow window(sf::VideoMode(800, 600), "FileManager Application");

    //if (!font.loadFromFile("arial.ttf")) {
    //    // Handle font loading error
    //    return;
    //}
    //sf::Text text("Hello!", font,20 );

    sf::CircleShape circle(50.f);
    sf::RectangleShape rect(Vector2f(300.f, 50.f));
    rect.setPosition(Vector2f(400.f, 200.f));
    rect.setOutlineColor(Color::Black);
    rect.setOutlineThickness(5.f);
    circle.setPosition(Vector2f(0.f, 0.f));
    circle.setFillColor(Color::Red);
    Font font;

    if (!font.loadFromFile("Font/OpenSans-Regular.ttf"))
    {
        cout << "Error loading font" << endl;
        return;
    }
    
    Text text; 
    

    text.setFont(font); 
    text.setCharacterSize(24); 
    text.setFillColor(Color::Black);
    text.setStyle(Text::Bold);

    Text title = text; 
    title.setString("Directory : ");
    title.setPosition(0.0f, 0.0f);
    title.setCharacterSize(30);
    title.setFillColor(Color::Black);
    title.setStyle(Text::Bold);
    
    Text item = text;
    item.setString("Root");
    item.setPosition(180.0f, 0.0f);
    item.setCharacterSize(30);
    item.setFillColor(Color::Black);
    item.setStyle(Text::Bold);

    

    while (window.isOpen()) {

        Event event; 
        while (window.pollEvent(event)) {

            if (event.type == Event::Closed) {
                window.close();
            }
        }

        window.clear(Color::White);

        window.draw(circle);
        window.draw(rect);
        window.draw(title);
        window.draw(item);
        window.display();
    }
}

int main() {
   
    FileManager<MyItem> fileManager("test.xml");
    
    fileManager.loadToTree();
    fileManager.toDisplayTree();

    Tree<MyItem>* folder = fileManager.getTree(); 
    TreeIterator<MyItem> iter(folder);
    cerr << "============================" << endl;


    fileManager.toCalculateSize(); 
    cerr << "============================" << endl;
    fileManager.countItems(iter);
    
    cerr << "==================================" << endl;
    fileManager.toPruneFolders(); 
    fileManager.toDisplayTree(); 
    cerr << "==================================" << endl;

    fileManager.findFile("config");

    cerr << "==================================" << endl;
    
    fileManager.toPrinTheWholeDirectory("Debug");

    guiDisplay(fileManager,iter);
    return 0; 


}