#ifndef KMER_INDEX_H
#define KMER_INDEX_H




uint32 hashforindex(const char *str, uint16 kml, uint32 size=10007)
{
	register uint32 h=0;
	uint16 pcount=0;
	while(*str && pcount<kml)
	{
		h = h*31 + *str++;
		pcount++;
	}
	return (h%size);
}



uint32 ROL(uint32 forekey, uint16 bit = 2)
{
	return ((forekey<<bit) | (forekey>>(32-bit)));
}

uint32 ROL(uchar c, uint16 bit=2)
{
	return ((c<<bit) | (c>>(32-bit)));
}

uint32 hashforkmer(const char *str,uint16 kml,  uint16 bit=2)
{
	register uint32 h=0;
	uint16 pcount=0;
	while(*str && pcount<kml)
	{
		h = ROL(h,bit) ^ (uchar)*str++;
		pcount++;
	}
	return h;
}

uint32 hashforkmer(uint32 fore,const char *str, uint16 kml, uint16 bit=2)
{
		
		return ROL(fore ^ ROL((uchar)*(str-1),(kml-1)*bit),bit) ^ (uchar)*(str+kml-1);
		//return ((((fore^(((uchar)*(str-1)<<((kml-1)*bit)) | (uchar)*(str-1)>>(64-(kml-1)*bit)))<<bit) | ((fore^(((uchar)*(str-1)<<((kml-1)*bit)) | (uchar)*(str-1)>>(64-(kml-1)*bit)))>>(64-bit))) ^ (uchar)*(str+kml-1));
}

//到时候做一个集成所有函数的hash这样测的时间更精准


uint32 gethashindex(const uint32 hashkey, const uint32 size=10007)
{
	return (hashkey%size);
}

void getKmerPara(uchar* p,uint32 length, uint16 &k )    //做一个根据字符串来做kmer的k值大小来做后面的索引
{
	
}




class Kmer_Index
{
	public:
	Kmer_Index(fragnode &partition_ref, uint16 _KmerLength=21,uint32 _IndexSize=10007)
	{
		slice = partition_ref;
		KmerLength=_KmerLength;
		IndexSize=_IndexSize;
		for(uint32 i=0; i<IndexSize; i++)
		{
			vector<uint32>* newv = new vector<uint32>;
			KMERINDEX.push_back(newv);
		}
		
	}

	
	~Kmer_Index()
	{
		
	}
	
	void build_index()
	{
			
	//	uint32 str_len =  ref_length;
		
		uint16 bit=2;
		
		uint32 ref_length=slice.endpos-slice.startpos;
		//cout<<"sequence length "<<ref_length<<" KmerLength "<<KmerLength<<" IndexSize "<<IndexSize<<endl;
		
		//*************index(hash by fore)********************************//
		/*
		cout<<"index(hash by fore) time: ";
		TimeWatch tw1;
		uint32 forekey=hashforkmer(slice.startpos,KmerLength,bit);
		KMERINDEX[gethashindex(forekey,IndexSize)]->push_back(0);
		for(uint32 pos=1; pos<ref_length-KmerLength+1; pos++)
		{
			forekey=hashforkmer(forekey,slice.startpos+pos,KmerLength,bit);
			KMERINDEX[gethashindex(forekey,IndexSize)]->push_back(pos);
			//KMERINDEX[hashforindex(slice.startpos+pos,KmerLength,IndexSize)]->push_back(pos);
		}
		tw1.stop(true);
		*/
		//********************************************************************//
		
		
		//**************************index2(hash by each)***********************//
		//cout<<"index2(hash by each) time: ";
		//TimeWatch tw2;
		for(uint32 pos=0; pos<ref_length-KmerLength+1; pos++)
		{
			KMERINDEX[hashforindex(slice.startpos+pos,KmerLength,IndexSize)]->push_back(pos);
		}
		//tw2.stop(true);
		//**********************************************************************//
		
		
	}
	
	
	void debug_index()
	{
		for(uint32 i=0;i<KMERINDEX.size();i++)
		{
			cout<<KMERINDEX.at(i)->size()<<endl;
		}
	}
	
	
	void findMatch(char* cur_tar, char* end_tar, uint32 &length, uint32 &pos)
	{
		uint32 maxlen=0;
		uint32 maxpos=-1;
		char *end_ref=slice.endpos;
		uint32 h = hashforindex(cur_tar, KmerLength, IndexSize);
		
		for (vector<uint32>::const_iterator iterator = KMERINDEX[h]->begin(), end = KMERINDEX[h]->end(); iterator != end; ++iterator)
		{
			char *temp_ref=slice.startpos+*iterator;
			char *temp_tar=cur_tar;
			uint32 temp_len=0;
			while(temp_tar < end_tar && temp_ref < end_ref)
			{
				if(*temp_tar==*temp_ref)
					temp_len++;
				else
					break;
				temp_tar++;
				temp_ref++;
			}
			if(temp_len>maxlen)
			{
				maxlen = temp_len;
				maxpos=*iterator;
			}
		}
		if(maxlen < KmerLength){
			length = 0;
			pos = -1;
		}
		else{
			length = maxlen;
			pos = maxpos;
		}
	}
	
	void PrintIndex()
	{
		
		for(uint32 i=0; i<IndexSize; i++)
		{
			cout<<i<<": "<<KMERINDEX.at(i)->size()<<endl;
		}
	}
	

	
	
	fragnode slice;
	uint16 KmerLength;
	uint32 IndexSize;
	vector<vector<uint32>*> KMERINDEX;
};


#endif