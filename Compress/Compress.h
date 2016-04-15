#ifndef COMPRESS_H
#define COMPRESS_H

class CompressNode
{
	public:
	CompressNode(uint32 s_pos, uint32 e_pos, char _mis='0')
	{
		startpos = s_pos;
		endpos = e_pos;
		mischar = _mis;		
	}
	
	
	
	
	uint32 startpos;
	uint32 endpos;
	char mischar;
	
};




class Compress{
	public:
	Compress()
	{
		
	}
	~Compress(){}
	void CompressbyKindex(Kmer_Index* index,const targetnode &tar)
	{
		//mfc.reserve(1000);
		char* start_tar = tar.startpos;
		char* end_tar = tar.endpos;
		char* cur_tar = start_tar;
		mfc.clear();
		//cout<<"tar_len:"<<(end_tar - start_tar)<<endl;
		while(cur_tar < end_tar)
		{
			uint32 s_len=0;
			uint32 s_pos=-1;
			if(*cur_tar=='N')
			{	
				char* temp=cur_tar;		
				while(*temp=='N'&&temp!=end_tar)
					temp++;
				
				mfc.push_back(CompressNode(0,temp-cur_tar,'N'));
				cur_tar=temp;
				
			}
			else{
				index->findMatch(cur_tar, end_tar, s_len, s_pos);
				if(s_pos != -1)
				{
					mfc.push_back(CompressNode(s_pos, s_pos+s_len-1));
					cur_tar +=s_len;				
				}
				else
				{
					mfc.push_back(CompressNode(0,0,*cur_tar));
					cur_tar++;
				}
			}
		}
		/*
		for(int i=0; i<mfc.size();i++)
		{
			cout<<mfc[i].startpos<<","<<mfc[i].endpos<<","<<mfc[i].mischar<<endl;
		}
	*/
			
		
	}
	
	
	vector<CompressNode> mfc;
	
};




#endif