#ifndef ABSTRACTPARTITION_H
#define ABSTRACTPARTITION_H

class fragnode
{
	public:
	fragnode()
	{
		startpos =NULL;
		endpos = NULL;
	}
	fragnode(char* _startpos, char* _endpos)
	{
		startpos = _startpos;
		endpos = _endpos;
	}
	~fragnode()
	{
		
	}
	
	fragnode& operator = (const fragnode &other)
	{
		if(this != &other)
		{
			fragnode temp(other);
			char* pstemp=temp.startpos;
			char* petemp=temp.endpos;
			startpos=pstemp;
			endpos=petemp;
		}
		return *this;
	}
	
	
	char* startpos;
	char* endpos;
};


class targetnode
{
	public:
	targetnode()
	{
		startpos =NULL;
		endpos = NULL;
		
	}
	targetnode(char* _startpos, char* _endpos, string& _filename, uint16 i)
	{
		startpos = _startpos;
		endpos = _endpos;
		filename = _filename;
		num = i;
	}
	~targetnode()
	{
		
	}
	
	targetnode& operator = (const targetnode &other)
	{
		if(this != &other)
		{
			targetnode temp(other);
			char* pstemp=temp.startpos;
			char* petemp=temp.endpos;
			startpos=pstemp;
			endpos=petemp;
			filename = temp.filename;
			num = temp.num;
		}
		return *this;
	}
	
	
	char* startpos;
	char* endpos;
	string filename;
	uint16 num;
};


class AbstractPartition
{
	public:
	virtual ~AbstractPartition(){};
	virtual void Partition_Ref(char* &reference, const uint32 &reflength, vector<fragnode> &ref) {};
	virtual void Partition_Tar(char* &target, const uint32 &tarlength, string &filename, vector<targetnode> &tar) {};
};










#endif