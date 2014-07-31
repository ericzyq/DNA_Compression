#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <unordered_map>
#include "SSTree.h"
using namespace std;
#define THRESH 10

class compressor
{
private:
	vector<SSTree*> refTree;

	unordered_map<string, unsigned char> occurrence;

	int initialSize;

	ofstream outputFile;

	SSTree* CreateRefTree(uchar* text);

	void Encode(uchar* pattern);

	void Decode(uchar* code);

	int nodeNum;

public:
	compressor();

	compressor(char* filename);

	~compressor();

	void CreateRefForest(char* filename);

	void OutputSet(char* filename);
	
	void Compress(char* filename);

	void Decompress(char* filename);

	int ForestSize();
	
};