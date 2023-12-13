#pragma once

#include <vector>
#include <string>
using namespace std;

//enum item_enum {
//	FILE_TYPE = 0,
//	FOLDER_TYPE = 1
//};
//
//
//class MyFile {
//	string name;
//	string length;
//	string type;
//};
//
//class MyDirectory {
//	
//	string name; 
//	vector<MyFile> files;
//public:
//	MyDirectory(const string name) {
//		this->name = name;
//	}
//};

struct MyItem {
public:
	string name="";
	string type="";
	string length="";
	MyItem() {};
	MyItem(const string name, const string type, const string length) {
		this->name = name;
		this->type = type;
		this->length = length;
	};

	MyItem(const MyItem& other)
		: name(other.name), type(other.type), length(other.length) {}


	friend ostream& operator<<(ostream& os, const MyItem& item) {
		os <<"(" << item.name << "," << item.type << "," << item.length << ")";
		return os;
	}

	bool operator==(const MyItem& other) const {
		return name == other.name && type == other.type && length == other.length;
	}
	
	
};