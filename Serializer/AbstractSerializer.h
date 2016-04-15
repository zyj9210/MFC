#ifndef ABSTRACTSERIALIZER_H
#define ABSTRACTSERIALIZER_H

class AbstractSerializer
{
	public:
	
	virtual ~AbstractSerializer(){};
	virtual void serializer(vector<CompressNode> &mfc, string& outPath){};
	virtual void unserializer(string& inPath, const fragnode &reference){};
	
	
};




#endif