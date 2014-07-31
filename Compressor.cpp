#include "Compressor.h"

compressor::compressor()
{
	initialSize = 0;
	searchRec = 0;
}

compressor::compressor(char* filename)
{
	initialSize = 0;
	searchRec = 0;
	CreateRefForest(filename);
}

compressor::~compressor()
{
	this->clear();	
}

int compressor::ForestSize()
{
	return refTree.size();
}

void compressor::clear()
{
	for (int i = 0; i<refTree.size(); i++)
	{
		delete refTree[i];
	}
	refTree.clear();
	if (outputFile.is_open())
	{
		outputFile.close();
	}
	occurrence.clear();
	searchRec = 0;
}

SSTree* compressor::CreateRefTree(uchar* text){
	ulong n = strlen((char*)text);
	n++;
	SSTree *sst = new SSTree(text, n);
	return sst;
}

void compressor::CreateRefForest(char* filename){
	ifstream myFile(filename);
	if (!myFile.is_open())
	{
		cout << "Please check the reference file's directory"<<endl;
		return;
	}
	this->clear();
	char output[segLength + 5];
	unordered_map<string,bool> forest;
	while(!myFile.eof()){
		myFile >> output;
		if (!myFile)
			break;
		if (forest.count((char*)output) == 0)
		{
			forest[(char*)output] = true;
			refTree.push_back(CreateRefTree((uchar*)output));
		} 
	}
	myFile.close();
	initialSize = refTree.size();
}

void compressor::OutputSet(char* filename){
	if (outputFile.is_open())
	{
		cout<<"Output File has been set before, changing..."<<endl;
		outputFile.close();
	} 
	outputFile.open(filename, ios::out);
	if (outputFile.is_open())
	{
		cout << "Output File Set to be "<<filename<<endl;
	}
	else
	{
		cout<< "Output File Set Fail, exiting!!!"<<endl;
		exit(1);
	}
}

void compressor::Encode(uchar* pattern){
	stringstream result;
	string target((char*)pattern);
	ulong length = target.length();

	result.clear();
	int node_num = 0;
	for (int i = 0; i < refTree.size(); i++){
		int treeNum = (i + searchRec)%refTree.size();
		node_num = refTree[treeNum]->search(pattern,length);
		if (node_num != 0) {
			if(treeNum < initialSize)
			{
				result << 's';
				result << treeNum;
			}
			else{
				result << 'd';
				result << treeNum-initialSize;
			}
			result << " ";
			result << refTree[treeNum]->textpos(node_num);
			result << " ";
			result << length;
			searchRec = i;
			break;
		}
	}
	if (node_num == 0){
		occurrence[target]++;
		if(occurrence[target] >= length) {
			refTree.push_back(CreateRefTree(pattern));
			occurrence.erase(target);
			result << "+" << target;
		}
		else if (length/2 < THRESH)
			result << target;
		else{
			string a = target.substr(0,length/2);
			string b = target.substr(length/2,length);
			Encode((uchar*) a.c_str());
			Encode((uchar*) b.c_str());
			return;
		}
	}
	if(!result.str().empty())
		outputFile << result.str() << endl;
	return;
}

void compressor::Compress(char* oriFile, char* reFile){
	this->OutputSet(reFile);
	ifstream inputFile(oriFile,ios::in);
	if (!inputFile.is_open())
	{
		cout << "Please check the input file's directory"<<endl;
		return;
	}
	char buff[segLength + 5];
	int line_counter = 0;
	while(!inputFile.eof()){
		inputFile.getline(buff,segLength + 5);
		if (strlen(buff) == 0)
			continue;
		line_counter ++;
		printf("Decompressing line: %d\r",line_counter);
		Encode((uchar*)buff);
	}
	cout<<endl;
	inputFile.close();
	outputFile.close();
}


void compressor::Decode(char* info)
{
	string code((char*)info);

	switch (code[0])
	{
		case '+' : // For dynamically added references
		{
			code = code.substr(1,string::npos);
			refTree.push_back(CreateRefTree((uchar*)code.c_str()));
			deBuff.append(code);
			break;
		}
		case 'd' : // For alignments to dynamic references
		{
			int p1 = code.find(' ');
			int p2 = code.find(' ', p1+1);
			int treeNum = atoi(code.substr(1,p1-1).c_str());
			int pos = atoi(code.substr(p1+1,p2-1).c_str());
			int length = atoi(code.substr(p2+1).c_str());
			deBuff.append((char*)refTree[treeNum + initialSize]->substring(pos,length));
			break;
		}
		case ('s') : // For alignments to static references
		{
			int p1 = code.find(' ');
			int p2 = code.find(' ', p1+1);
			int treeNum = atoi(code.substr(1,p1-1).c_str());
			int pos = atoi(code.substr(p1+1,p2-1).c_str());
			int length = atoi(code.substr(p2+1).c_str());
			deBuff.append((char*)refTree[treeNum]->substring(pos,length));
			break;
		}
		default: // For non-matched segments
		{
			deBuff.append(code);
			break;
		}			
	}
	if(deBuff.size() >= segLength)
	{
		outputFile << deBuff << endl;
		deBuff.clear();
	}
}


void compressor::Decompress(char* oriFile, char* reFile)
{
	this->OutputSet(reFile);
	ifstream inputFile(oriFile,ios::in);
	char buff[segLength + 5];
	int line_counter = 0;
	this->deBuff.clear();
	while(!inputFile.eof()){
		inputFile.getline(buff,segLength + 5);
		if (strlen(buff) == 0)
			continue;
		line_counter ++;
		printf("Decompressing line: %d\r",line_counter);
		Decode((char*)buff);
	}
	cout<<endl;
	inputFile.close();
	outputFile.close();
}