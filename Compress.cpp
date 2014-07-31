#include "Compressor.h"

int main()
{
	clock_t t1,t2;
	compressor c;
	
	t1 = clock();
	cout << "Creating reference forest ...\n";
	c.CreateRefForest("NA12880.txt");
	cout << "Finished creating!\n";
	cout << "Compressing ...\n";
	c.Compress("NA12882.txt","compressed.txt");
	cout<<"Done!\n";
	cout<<"Forest size: "<<c.ForestSize()<<endl;
	t2 = clock();
	float diff1 = (((float)t2-(float)t1)/CLOCKS_PER_SEC)/60;
		
	cout<<endl;
	c.clear();

	t1 = clock();
	cout << "Creating reference forest ...\n";
	c.CreateRefForest("NA12880.txt");
	cout << "Finished creating!\n";
	cout << "Decompressing ...\n";
	c.Decompress("compressed.txt","decompressed.txt");
	cout<<"Done!\n";
	t2 = clock();
	float diff2 = (((float)t2-(float)t1)/CLOCKS_PER_SEC)/60;
	
	cout<<"Forest size: "<<c.ForestSize()<<endl;
	cout << "Total: " << diff1 << " minutes\n";
	cout << "Total: " << diff2 << " minutes\n";	
	
	
	return 0;
}
