#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <unordered_map>
#include "SSTree.h"
using namespace std;
#define THRESH 10
#define segLength 101

class compressor
{
private:
	vector<SSTree*> refTree;

	unordered_map<string, unsigned char> occurrence;

	int initialSize;

	int searchRec;

	string deBuff;

	ofstream outputFile;

	SSTree* CreateRefTree(uchar* text);

	void Encode(uchar* pattern);

	void Decode(char* info);

	void OutputSet(char* filename);
	
public:
	compressor();

	compressor(char* filename);

	~compressor();

	void clear();

	void CreateRefForest(char* filename);

	void Compress(char* oriFile, char* reFile);

	void Decompress(char* oriFile, char* reFile);

	int ForestSize();
	
};