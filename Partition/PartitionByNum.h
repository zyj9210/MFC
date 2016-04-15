#ifndef PARTITIONBYNUM_H
#define PARTITIONBYNUM_H



class PartitionByNum : public AbstractPartition
{
	public:
	PartitionByNum()
	{
		sliptnum=16;
		sigma = 24;
	}
	
	PartitionByNum(uint16 _sliptnum, uint16 _sigma)
	{
		sliptnum = _sliptnum;
		sigma = _sigma;
	}
	
	~PartitionByNum()
	{
		
	}
	
	//********************************************//
	//
	//		划分reference和target
	//
	//********************************************//
	
	void Partition_Ref(char* &reference, const uint32 &reflength, vector<fragnode> &ref)
	{
		uint32 splitlength = reflength/sliptnum;   //根据划分度划分长度		
		for(uint16 i=0; i<sliptnum; i++)	//根据划分度确认最后数组大小
		{
			fragnode temp_frag;
			ref.push_back(temp_frag);
		}
		ref[0] = fragnode(reference,reference+splitlength+sigma);
		for(uint16 i=1; i<sliptnum-1; i++)
		{
			char *s=reference+i*splitlength-sigma;
			ref[i] = fragnode(s,s+splitlength+2*sigma);
		}	
		ref[sliptnum-1]=fragnode(reference+(sliptnum-1)*splitlength-sigma,reference+reflength);
		
	}
	

	void Partition_Tar(char* &target, const uint32 &tarlength, vector<fragnode> &tar)
	{
		uint32 splitlength = tarlength/sliptnum;
		for(uint16 i=0; i<sliptnum; i++)	//根据划分度确认最后数组大小
		{
			fragnode temp_frag;
			tar.push_back(temp_frag);
		}
		for(uint16 i=0; i<sliptnum-1; i++)
		{
			char *s=target+i*splitlength;
			tar[i]=fragnode(s, s+splitlength);
		}
		tar[sliptnum-1] = fragnode(target+(sliptnum-1)*splitlength, target + tarlength); 

	}
	
	
	
	private:
	uint16 sliptnum;
	uint16 sigma;
};


#endif