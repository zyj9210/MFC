#ifndef MAINCOMPRESS_H
#define MAINCOMPRESS_H

class MainCompress
{
	public:
	void compress(string &inputPath, string &referencePath, string &outputPath)
	{
		char *reference = NULL;
		char *ref_head = NULL;
		int32 reflength = -1;
		cout<<"READing..."<<endl;
		TimeWatch tw0;
		reflength = load_file(referencePath, reference, ref_head);
		tw0.stop(true);
		vector<fragnode> partition_reference;
		//划分reference
		AbstractPartition *partition = new PartitionByLength(1000000,21);   //划分 @para1 划分个数， @para2 reference拓展长度
		partition->Partition_Ref(reference, reflength, partition_reference); //划分reference并存入数组slip_reference (起点指针，终点指针)
		int32 partition_num = partition_reference.size();
		//构建索引
		vector<Kmer_Index *> index;
		cout<<"Indexing...";
		TimeWatch tw1;
		for(int i=0; i<partition_num; i++ )
		{
			Kmer_Index *temp=new Kmer_Index(partition_reference.at(i),21,100007);
			temp->build_index();
			index.push_back(temp);
		}
				
		tw1.stop(true);
		vector<string> filePath;
		getfilepath(filePath, inputPath);
		
		vector<targetnode> partition_target;
		for(uint32 i=0;i<filePath.size();i++)
		{
			char *target = NULL;
			char *tar_head = NULL;
			string filename;
			uint32 tarlength = load_file(filePath.at(i), target, tar_head);
			getfilename(filePath.at(i), filename);
			partition->Partition_Tar(target, tarlength, filename, partition_target);
			
			
		}
		
		create_out(outputPath);
		TimeWatch tw3;
		for(uint16 j=0; j<partition_target.size(); j++)
		{	
			//TimeWatch tw2;
			Compress *compress = new Compress();
			AbstractSerializer *serfile=new SerializerEach();
			uint16 index_num = partition_target.at(j).num;
			compress->CompressbyKindex(index.at(index_num), partition_target.at(j));
			string everyname=compressname(outputPath,partition_target.at(j).filename,index_num);	
			serfile->serializer(compress->mfc,everyname);
			//tw2.stop(true);
			delete compress;
			delete serfile;				
		}
		tw3.stop(true);
		delete partition;

		//delete []target;
		//delete []tar_head;
	}
		
	
	void compress(string &inputPath, string &outputPath)
	{
		vector<string> filePath;
		getfilepath(filePath, inputPath);
		compress(inputPath, filePath.at(0), outputPath);
	}
};






#endif
