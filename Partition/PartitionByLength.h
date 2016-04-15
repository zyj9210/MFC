#ifndef PARTITIONBYLENGTH_H
#define PARTITIONBYLENGTH_H

class PartitionByLength : public AbstractPartition
{
	public:
	PartitionByLength()
	{
		splitlength=1000000;
		sigma = 24;
	}
	
	PartitionByLength(uint32 _sliplength, uint16 _sigma)
	{
		splitlength = _sliplength;
		sigma = _sigma;
	}
	
	~PartitionByLength()
	{
		
	}
	
	//********************************************//
	//
	//		划分reference和target
	//
	//********************************************//
	
	void Partition_Ref(char* &reference, const uint32 &reflength, vector<fragnode> &ref)
	{
		uint32 sliptnum = (reflength+splitlength/2)/splitlength;
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
	

	void Partition_Tar(char* &target, const uint32 &tarlength, string &filename, vector<targetnode> &tar)
	{
		uint16 sliptnum = (tarlength+splitlength/2)/splitlength;
		
		for(uint16 i=0; i<sliptnum-1; i++)
		{
			char *s=target+i*splitlength;
			tar.push_back(targetnode(s, s+splitlength, filename, i));
		}
		tar.push_back(targetnode(target+(sliptnum-1)*splitlength, target + tarlength, filename, sliptnum-1)); 
	
	}
	
	
	
	private:
	uint32 splitlength;
	uint16 sigma;
};


#endif