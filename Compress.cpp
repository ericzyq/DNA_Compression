#include "Compressor.h"

int main()
{
	clock_t t1,t2;
	compressor c;
	
	t1 = clock();
	cout << "Creating reference forest ...\n";
	c.CreateRefForest("NA12880.txt");
	cout << "Finished creating!\n";
	c.OutputSet("compressed.txt");
	cout << "Compressing ...\n";
	c.Compress("NA12882.txt");
	cout<<"Done!\n";
	cout<<"Forest size: "<<c.ForestSize()<<endl;
	t2 = clock();
	float diff = (((float)t2-(float)t1)/CLOCKS_PER_SEC)/60;
	cout << "Total: " << diff << " minutes\n";
	
	cout<<endl;
	c.clear();

	t1 = clock();
	cout << "Creating reference forest ...\n";
	c.CreateRefForest("NA12880.txt");
	cout << "Finished creating!\n";
	c.OutputSet("decompressed.txt");
	cout << "Decompressing ...\n";
	c.Decompress("compressed.txt");
	cout<<"Done!\n";
	cout<<"Forest size: "<<c.ForestSize()<<endl;
	t2 = clock();
	diff = (((float)t2-(float)t1)/CLOCKS_PER_SEC)/60;
	cout << "Total: " << diff << " minutes\n";	
	
	
	return 0;
}
