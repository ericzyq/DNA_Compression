#include "Compressor.h"

compressor::compressor()
{
	initialSize = 0;
	nodeNum = 0;
}

compressor::compressor(char* filename)
{
	initialSize = 0;
	nodeNum = 0;
	CreateRefForest(filename);
}

compressor::~compressor()
{
	for (int i = 0; i<refTree.size(); i++)
	{
		delete refTree[i];
	}
	if (outputFile.is_open())
	{
		outputFile.close();
	}
	
}

int compressor::ForestSize()
{
	return refTree.size();
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
	char output[110];
	while(!myFile.eof()){
		myFile >> output;
		if (!myFile)
			break;
		int occur = 0;
		for(int i = 0; i < (signed)refTree.size(); i++){
			if(refTree[i]->search((uchar*)output,101) != 0){
				occur = 1;
				break;
			}
		}
		if(occur == 0)
			refTree.push_back(CreateRefTree((uchar*)output));
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
		cout << "Output File Set to be"<<*filename<<endl;
	}
}

void compressor::Encode(uchar* pattern){
	stringstream s,result;
	s << pattern;
	string target = s.str();
	ulong length = target.length();

	result.clear();
	int node_num = 0;
	for (int i = 0; i < refTree.size(); i++){
		node_num = refTree[(i+nodeNum)%refTree.size()]->search(pattern,length);
		if (node_num != 0) {
			
			if(i < initialSize)
				result << i;
			else{
				result << 's';
				result << i-initialSize;
			}
			result << " ";
			result << refTree[(i+nodeNum)%refTree.size()]->textpos(node_num);
			result << " ";
			result << length;
			nodeNum = i;
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

void compressor::Compress(char* filename){
	if (!outputFile.is_open())
	{
		cout << "Please set the output file first"<<endl;
		return;
	}
	ifstream inputFile(filename,ios::in);
	if (!inputFile.is_open())
	{
		cout << "Please check the input file's directory"<<endl;
		return;
	}
	char buff[110];
	int line_counter = 0;
	while(!inputFile.eof()){
		inputFile.getline(buff,110);
		if (strlen(buff) == 0)
			continue;
		line_counter ++;
		cout<<"compressing line: "<<line_counter<<endl;
		Encode((uchar*)buff);
	}
	inputFile.close();
	outputFile.close();
}

/***********************
the following part is not finished yet
***************************/
//void compressor::Decode(uchar* code)
//{
//	string line, ref, result;
//	int pos, length;
//	ofstream output;
//	string currLine = "";
//	output.open ("Decoded.txt",ios::app);
//	while(getline(input, line))
//	{
//		stringstream linestream(line);
//		getline(linestream, ref, ' ');
//		if(ref.at(0) == '+'){
//			result = ref.substr(1,ref.size());
//			refTree.push_back(createRefTree((uchar*)result.c_str()));
//		}
//		else if((ref.at(0) >= 'A') & (ref.at(0) <= 'Z'))
//			result = ref;
//		else{
//			linestream >> pos >> length;
//			stringstream ss;
//			if(ref.at(0) == 's')
//				ss << refTree[atoi(ref.substr(1,ref.size()).c_str()) + initialSize]->substring(pos,length);
//			else
//				ss << refTree[atoi(ref.c_str())]->substring(pos,length);
//			result = ss.str();
//		}
//		if(currLine.size() + result.size() <= 101){
//			output << result;
//			currLine += result;
//		}
//		else{
//			output << result.substr(0,101-currLine.size());
//			output << "\n";
//			string nextLine = result.substr(101-currLine.size(),result.size());
//			output << nextLine;
//			currLine = nextLine;
//		}
//	}
//}
//
//
//void compressor::Decompress(char* filename)
//{
//	if (!outputFile.is_open())
//	{
//		cout << "Please set the output file first"<<endl;
//		return;
//	}
//	ifstream inputFile(filename,ios::in);
//	char buff[110];
//	int line_counter = 0;
//	while(!inputFile.eof()){
//		inputFile.getline(buff,110);
//		if (strlen(buff) == 0)
//			continue;
//		line_counter ++;
//		cout<<"Decompressing line: "<<line_counter<<endl;
//		Decode((uchar*)buff);
//	}
//	inputFile.close();
//	outputFile.close();
//}