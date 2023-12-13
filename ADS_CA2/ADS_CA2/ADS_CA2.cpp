#include <SFML/Graphics.hpp>
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



void guiDisplay() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    sf::Event event;
    //sf::Text("text");
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
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

    guiDisplay();
    return 0; 


}