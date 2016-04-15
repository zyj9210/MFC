#include "./BasicInclude.h"
#include "./Partition/AbstractPartition.h"
#include "./Partition/PartitionByNum.h"
#include "./Partition/PartitionByLength.h"
#include "./Index/Kmer_Index.h"
#include "./Compress/Compress.h"
#include "./Serializer/AbstractSerializer.h"
#include "./Serializer/SerializerEach.h"
#include "./Recompress/zlibcom.h"
#include "./MainCompress.h"
#include "./MainDecompress.h"
void printUsage()
{
	cout<<"Usage:\n\n";
    cout<<"mfc task inputpath outputpath\n\n";
	cout<<"or mfc task inputpath referencepath outputpath\n\n";
    cout<<"where:\n";
    cout<<"- task is either COMPRESS, DECOMPRESS\n";
    cout<<"- input is \n";
    cout<<"  - a path to the to-be-compressed file (in case of COMPRESS)\n";
    cout<<"  - a path to the referentially compressed files (in case of DECOMPRESS)\n";
	cout<<"- referencepath is \n";
	cout<<"  - a path to a  appointed reference sequence path (in case of COMPRESS and DECOMPRESS)\n";
    cout<<"- output is\n";
    cout<<"  - a path to the referentially compressed output files (in case of COMPRESS)\n";
    cout<<"  - a path to the uncompressed outputfile (in case of DECOMPRESS)\n";
    cout<<"  \n";
    cout<<"Examples:\n\n";
    cout<<"./mfc COMRESS /database/chr1/ /database/compressed/ \n";
    cout<<"./mfc DECOMRESS /database/compressed/ /database/decompressed/ \n";
    cout<<"  \n";
    cout<<"For further information please see README.txt!\n";
    exit(0);
};

int main(int argc, const char* argv[])
{
	if(argc<4 || argc>5)
	{
		printUsage();
		exit(0);
	}
	string inputPath;
	string command;
	string outPath;
	string referencePath;
	bool ASSIGNED = false;
	if(argc == 4)
	{
		command = argv[1];
		inputPath = argv[2];
		outPath = argv[3];
		ASSIGNED=false;
	}
	if(argc == 5)
	{
		command = argv[1];
		inputPath =argv[2];
		referencePath = argv[3];
		outPath = argv[4];
		ASSIGNED=true;
	}

	
	if(command == "COMPRESS")
	{
		MainCompress com;
		if(ASSIGNED)
			com.compress(inputPath, referencePath, outPath);
		else
			com.compress(inputPath, outPath);
	}
	
	else if(command == "DECOMPRESS")
	{
		MainDecompress dec;
		if(ASSIGNED)
			dec.decompress(inputPath, referencePath, outPath);
		else
			dec.decompress(inputPath, outPath);
	}
	else
	{
		cout<<"UNKNOWN COMMAND: "<<command<<endl;
		printUsage();
		exit(0);
	}
	return 0;
}











