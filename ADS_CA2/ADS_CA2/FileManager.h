#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "MyStack.h"
#include "Tree.h"
#include "TreeIterator.h"
#include "FileStruct.h"
#include <queue>

using namespace std;
template <class T>
class FileManager
{
	string filename;
    Tree<T>* tree;
public:
    FileManager();
	FileManager(const string fileName);
	bool loadAndValidateXML();
    void loadToTree();
	void setFileName(const string fileName);
    int getCountTree();
    void displayTree(TreeIterator<T> iter, string indent);
    void toDisplayTree();
    pair<int,int> countItems(TreeIterator<T>);
    void pruneEmptyFolders(TreeIterator<T> iter);
    void toPruneFolders();
    void toCalculateSize();
    int calculateSize(Tree<T>* folders);
    vector<string> findFile(const string& filename);
    bool findPathFile(Tree<T>* folder, const string& file, vector<string>& path);
    Tree<T>* getTree();

    vector<T> toPrinTheWholeDirectory(const string& dir);

    void printMatchingDirectories(Tree<T>* folders, const string& dirToMatch, vector<T>& foundItems);

    //void printDirectoryContent(Tree<T>* folders);
    
};



template <class T>
bool FileManager<T>::loadAndValidateXML() {
    using namespace std; // Import std namespace into function scope

    ifstream file(this->filename);

    if (!file.is_open()) {
        cerr << "Error opening file " << this->filename << endl;
        return false;
    }

    MyStack<string> tags;
    string line;

    while (getline(file, line)) {
        size_t openTagStart = line.find("<");
        size_t openTagEnd = line.find(">", openTagStart);

        size_t closeTagStart = line.find("</");
        size_t closeTagEnd = line.find(">", closeTagStart);
        cout<< "before :"<<line << endl;
        while (openTagStart != string::npos && openTagEnd != string::npos) {
            string tag = line.substr(openTagStart + 1, openTagEnd - openTagStart - 1);
            cout << "tag: " << tag << endl;
            if (tag[0] == '/') {
                break;
            }
            else {
                cout<< "push: " << tag << endl;
                tags.push(tag);
            }

            openTagStart = line.find("<", openTagEnd);
            openTagEnd = line.find(">", openTagStart);

        }
        cout << "checkpoint1" << endl;
        cout <<"after: "<< line << endl;
        // Process closing tags separately
        while (closeTagStart != string::npos && closeTagEnd != string::npos) {
            string tag = line.substr(closeTagStart + 2, closeTagEnd - closeTagStart - 2);

            if (tags.isEmpty()) {
                cerr << "Error part 2: Closing tag without opening tag" << endl;
                return false;
            }
            else {
                string top = tags.top();
                if (top == tag) {
                    tags.pop();
                }
                else {
                    cout << "top 2: " << top << endl;
                    cout << "tag 2: " << tag << endl;
                    cerr << "Error part 2: Closing tag does not match opening tag" << endl;
                    return false;
                }
            }

            closeTagStart = line.find("</", closeTagEnd);
            closeTagEnd = line.find(">", closeTagStart);
        }
    }
    file.close();
    if (tags.isEmpty()) {
        cerr << "Complete" << endl;
        return true;
    }
    else {
        cerr << "Error: Opening tag without closing tag" << endl;
        return false;
    }
}

template <class T>
void FileManager<T>::loadToTree() {
    using namespace std; // Import std namespace into function scope

    ifstream file(this->filename);

    if (!file.is_open()) {
        cerr << "Error opening file " << this->filename << endl;
        return;
    }
    string line;
    string prevtag;
    string tag;
    MyItem item;
    string content;
    TreeIterator<MyItem> it(tree);
    while (getline(file, line)) {
        size_t openTagStart = line.find("<");
        size_t openTagEnd = line.find(">", openTagStart);
        size_t closeTagStart = line.find("</");
        size_t closeTagEnd = line.find(">", closeTagStart);
        cout << line << endl;
        tag = line.substr(openTagStart + 1, openTagEnd - openTagStart - 1);
        if (tag == "dir") {
               prevtag = tag;
               item.type = "dir";
               item.length = "";
               cout << "Current folder: " << it.node->getData().name << endl;
               it.childEnd();
               it.down();
               
        }
        if (tag == "file") {
            prevtag = tag;
            item.length = "";
            item.type = "";
            item.name = "";
            it.childEnd();
            it.down();
        }

        if (tag == "name") {
                content = line.substr(openTagEnd + 1, closeTagStart - openTagEnd - 1);
                item.name = content;
            if (prevtag == "dir") {
                it.appendChild(item);
                
            }
        }

        if (tag == "type" && prevtag == "file") {
            content = line.substr(openTagEnd + 1, closeTagStart - openTagEnd - 1);
            item.type = content;
        }

        if (tag == "length" && prevtag == "file") {
            size_t numberEnd = line.find("b<", openTagEnd);
            content = line.substr(openTagEnd + 1, numberEnd - openTagEnd - 2);
            item.length = content;
        }

        if(tag == "/file") {
			it.appendChild(item);
            it.up();
		}

        if (tag == "/dir") {
			it.up();
		}


    }

    file.close();
}

template <class T>
pair<int,int> FileManager<T>::countItems(TreeIterator<T> iter) {
    iter.childStart();
    int folderCount = 0;
    int fileCount = 0;
    cerr << "Counting items: "<< iter.node->getData() << endl;

    while (iter.childValid()) {
        TreeIterator<MyItem> iter2(iter.childIter.currentNode->data);
        MyItem item = iter2.node->data;
        cerr << item << endl;
        if (item.type == "dir") {
            folderCount++;
        }
        else {
            fileCount++;
        }
        iter.childForth();
    }
    cerr << "folderCount: " << folderCount << endl;
    cerr << "fileCount: " << fileCount << endl;
    return make_pair(folderCount, fileCount);
}

template<class T>
int FileManager<T>::getCountTree() {
    return this->tree->count();
}


template<class T>
void FileManager<T>::setFileName(const string fileName) {
	this->filename = fileName;
}

template<class T>
FileManager<T>::FileManager() {
    this->filename = "";
    MyItem item;
    item.name = "Root";
    item.type = "Root";
    tree = new Tree<MyItem>(item);
}

template<class T>
FileManager<T>::FileManager(const string fileName) {
    this->filename = fileName;
    MyItem item;
    item.name = "Root";
    item.type = "Root";
    tree = new Tree<MyItem>(item);
}


template<class T>
void FileManager<T>::toDisplayTree() {
	TreeIterator<T> iter(tree);
	displayTree(iter, "=");
}

template<class T>
void FileManager<T>::displayTree(TreeIterator<T> iter,string indent)
{
    cout << indent << iter.node->data;
    if (iter.childValid())
    {
        cout << "(" << endl;

        while (iter.childValid())
        {
            TreeIterator<T> iter2(iter.childIter.currentNode->data);
            displayTree(iter2, "\t" + indent);
            iter.childForth();
        }
        cout << indent << ")";
    }
    cout << endl;
}

template<class T>
void FileManager<T>::toCalculateSize() {
    calculateSize(tree); 
}

template <class T>
int FileManager<T>::calculateSize(Tree<T> * folders) {
    queue<Tree<T>*> queue;
    queue.push(folders);
    int size = 0;
    while (!queue.empty())
    {
        DListIterator<Tree<T>*> iter = queue.front()->children->getIterator();
        while (iter.isValid())
        {
            queue.push(iter.item());
            iter.advance();
        }
        string temp = queue.front()->getData().length;
        if(temp == "") {
			temp = "0";
		}
        size += stoi(temp);
        queue.pop();

    }
    cerr << "Size: " << size << "b" << endl;
    return size;
}

template<class T>
void FileManager<T>::toPruneFolders() {
    TreeIterator<T> iter(tree);
	pruneEmptyFolders(iter);
}

template <class T>
void FileManager<T>::pruneEmptyFolders(TreeIterator<T> iter) {
    iter.down();
    cerr << "pruneEmptyFolders: " << iter.node->data << endl;
    iter.childStart();

    while (iter.childValid()) {
        
        Tree<MyItem>* childNode = iter.childIter.currentNode->data;
        cerr << "childNode: " << childNode->getData() << endl;
        pruneEmptyFolders(childNode);
        if (childNode->getData().type == "dir") {
            pair<int, int> counts = countItems(childNode);

            if (counts.first == 0 && counts.second == 0 && childNode->getData().type == "dir") {
                cout << "===== " << endl;
                cerr << "Removing: " << childNode->getData() << endl;
                iter.removeChild();
                
            }else {
            iter.childForth();
        }
        }
        else {
            iter.childForth();
        }
    }
    
}

template<class T>
vector<string> FileManager<T>::findFile(const string& filename) {
    vector<string> path;
    findPathFile(tree, filename, path);
    string temp;
    for (string item : path) { 
        temp += (item + "/");
	}
    cerr << temp << endl;
    
    return path;
}

template <class T>
bool FileManager<T>::findPathFile(Tree<T>* folder, const string& file, vector<string>& path) {
    if (!folder) {
        cerr << "Invalid folder" << endl;
        return false;
    }

    path.push_back(folder->getData().name);

    // Check if the current node matches the target file
    if (folder->getData().name == file) {
        // Do something with the path 
        cout << "Path for file '" << file << "': ";
        for (const auto& folderName : path) {
            cout << folderName << "/";
        }
        cout << endl;
        return true;
    }

    DListIterator<Tree<T>*> iter = folder->children->getIterator();
    while (iter.isValid()) {
        if (findPathFile(iter.item(), file, path)) {
            return true;  
        }
        iter.advance();
    }

    path.pop_back();
    return false;
}


template<class T>
Tree<T>* FileManager<T>::getTree() {
	return this->tree;
}

template <class T> 
vector<T> FileManager<T>::toPrinTheWholeDirectory(const string& dir) {
    vector<MyItem> items;
    printMatchingDirectories(tree, dir,items);
    cerr << "Directory: " << dir << endl;
    if (items.size() > 0) {
        cerr << "Items found: " << endl;
        for (MyItem i : items) {
            cout << "Item: " << i.name << " || Type : " << i.type;  
            if (i.length != "") {  
                cout << " || Length: " << i.length; 
            }
            cout << endl; 
        }
    }
    cerr << "start here" << endl;
    
    return items;
}


template<class T>
void FileManager<T>::printMatchingDirectories(Tree<T>* folders, const string& dirToMatch, vector<T>& foundItems) {

    queue<Tree<T>*> folderQueue;
    folderQueue.push(folders);

    while (!folderQueue.empty())
    {
        Tree<T>* currentFolder = folderQueue.front();
        folderQueue.pop();
        
        DListIterator<Tree<T>*> iter = currentFolder->children->getIterator();
        while (iter.isValid())
        {
            folderQueue.push(iter.item());
            iter.advance();
        }
        string currentDir = currentFolder->getData().name;  
        if (currentDir == dirToMatch) {
            TreeIterator<T> iter2(currentFolder);
            //while
            cout << "Directory : " << iter2.node->getData().name << endl;
            while (iter2.childValid())
            {
                TreeIterator<T> iter3(iter2.childIter.currentNode->data);
                MyItem item = iter3.node->getData();
                
                foundItems.push_back(item);
                iter2.childForth(); 
            } 

            
            // You can add more logic here based on your requirements
        }
    }

    cout << "Search done" << endl;
}
