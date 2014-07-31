#include "Compressor.h"

int main()
{
	clock_t t1,t2;
	compressor c;
	
	t1 = clock();
	cout << "Creating reference forest ...\n";
	c.CreateRefForest("NA12880.txt");
	cout << "Finished creating!\n";
	t2 = clock();
	float diff0 = (((float)t2-(float)t1)/CLOCKS_PER_SEC)/60;

	t1 = clock();
	c.Compress("NA12882.txt","compressed.txt");
	cout<<"Forest size: "<<c.ForestSize()<<endl;
	t2 = clock();
	float diff1 = (((float)t2-(float)t1)/CLOCKS_PER_SEC)/60;
		
	cout<<endl;
	c.clear();

	
	cout << "Creating reference forest ...\n";
	c.CreateRefForest("NA12880.txt");
	cout << "Finished creating!\n";
	t1 = clock();
	c.Decompress("compressed.txt","decompressed.txt");
	t2 = clock();
	float diff2 = (((float)t2-(float)t1)/CLOCKS_PER_SEC)/60;

	cout<<endl;
	cout<<"Forest size: "<<c.ForestSize()<<endl;
	cout << "Building References time total: " << diff0 << " minutes\n";
	cout << "Compression time total: " << diff1 << " minutes\n";
	cout << "Decompression time total: " << diff2 << " minutes\n";	
	
	
	return 0;
}
