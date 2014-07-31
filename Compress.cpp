#include "Compressor.h"

/*
vector<SSTree*> refTree;
map<string, int> occurrence;
int initialSize;

SSTree *createRefTree(uchar* text){
	ulong n = strlen((char*)text);
	n++;
	SSTree *sst = new SSTree(text, n);
	return sst;
}

void createRefForest(string filename){
	ifstream myFile(filename.c_str());
	char output[110];
	while(!myFile.eof()){
		myFile >> output;
		if (!myFile)
			break;
		refTree.push_back(createRefTree((uchar*)output));
	}
	myFile.close();
}

void encode(uchar* pattern){
	stringstream s,s1,s2,s3;
	s << pattern;
	string target = s.str();
	ulong length = target.length();
	string result = "";
	int node_num;
	for (int i = 0; i < (signed)refTree.size(); i++){
		node_num = refTree[i]->search(pattern,length);
		if (node_num != 0){
			s1.clear();
			s2.clear();
			s3.clear();
			if(i < initialSize)
				s1 << i;
			else{
				s1 << 's';
				s1 << i-initialSize;
			}
			result = s1.str() + " ";
			s2 << refTree[i]->textpos(node_num);
			result += s2.str() + " ";
			s3 << length;
			result += s3.str();
			break;
		}
	}
	if (node_num == 0){
		occurrence[target]++;
		if(signed(occurrence[target]/length) >= 1){
			refTree.push_back(createRefTree(pattern));
			result = "+" + target;
		}
		else if (length/2 < THRESH)
			result = target;
		else{
			string a = target.substr(0,length/2);
			string b = target.substr(length/2,length);
			encode((uchar*) a.c_str());
			encode((uchar*) b.c_str());
		}
	}
	ofstream myfile;
	myfile.open ("RPMM.txt",ios::app);
	if(result != "")
		myfile << result << endl;
	myfile.close();
}

void matchAlignments(string filename){
	ifstream myFile(filename.c_str());
	char output[110];
	while(!myFile.eof()){
		myFile >> output;
		if (!myFile)
			break;
		encode((uchar*)output);
	}
	myFile.close();
}

int main() {
	clock_t t1,t2;
	t1 = clock();
	cout << "Creating reference forest ...\n";
	createRefForest("NA12880.txt");
	cout << "Finished creating!\n";
	initialSize = refTree.size();
	ofstream myfile;
	myfile.open ("RPMM.txt");
	cout << "Matching alignments ...\n";
	matchAlignments("NA12882.txt");
	cout << "Finished matching!\n";
	cout << "Forest size: " << refTree.size() << endl;
	t2 = clock();
	float diff = (((float)t2-(float)t1)/CLOCKS_PER_SEC)/60;
	cout << diff << " minutes\n";
	return 0;
}
*/

int main()
{
	clock_t t1,t2;
	t1 = clock();
	cout << "Creating reference forest ...\n";
	
	compressor c("NA12880.txt");
	cout << "Finished creating!\n";
	c.OutputSet("tmp.txt");
	cout << "Comressing ...\n";
	c.Compress("NA12882.txt");
	cout<<"Done!\n";
	cout<<"Forest size: "<<c.ForestSize()<<endl;
	
	t2 = clock();
	float diff = (((float)t2-(float)t1)/CLOCKS_PER_SEC)/60;
	cout << diff << " minutes\n";
	return 0;
}
