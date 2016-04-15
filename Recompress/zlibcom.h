#ifndef ZLIBCOM_H
#define ZLIBCOM_H

#define MAXBUFFERSIZE 102400



class zlibcom
{
	public:
	zlibcom(){};
	~zlibcom(){};
	
	bool Compress(const char* originalBuf, string &outPath)  //源文件，压缩后写出
	{
		
		if(originalBuf == NULL)
			return false;
		if(strlen(originalBuf) == 0)
			return false;
		
		ulong oristr_len = strlen(originalBuf)+1;
		ulong complen = compressBound(oristr_len);
		Byte compr[complen];
		memset(compr, 0, complen);
		int err;
		err=compress2(compr, &complen, (const Bytef *) originalBuf, oristr_len, 6);
		if(err != Z_OK)
		{
			cout<<"Zlib Compress Error"<<err;
			return false;
		}
		//cout<<outPath<<endl;
		int fd = open(outPath.c_str(), O_WRONLY|O_CREAT|O_TRUNC,0777);
		if(fd == -1)
		{
			cout<<"WRITE FAILED 1"<<endl;
			exit(-1);
		}
		if(write(fd, compr, complen) == -1)
		{
			cout<<"WRITE FAILED 2"<<endl;
			exit(-1);
		}			
		close(fd);
		return true;
	}
	
	
	
	bool deCompress(string &inPath, char* result)
	{
		int fd = open(inPath.c_str(), O_RDONLY);
		if(fd == -1)
		{
			cout<<"WRITE FAILED 1"<<endl;
			exit(-1);
		}
		char *com_buf = new char[MAXBUFFERSIZE];
		ulong Ucomplen=read(fd, com_buf, MAXBUFFERSIZE);
		Byte decompr[MAXBUFFERSIZE];
		memset(decompr, 0, MAXBUFFERSIZE);
		ulong decomlen = MAXBUFFERSIZE;
		int err;
		err = uncompress(decompr, &decomlen, (const Bytef *)com_buf, Ucomplen);
		if(err != Z_OK)
		{
			cout<<"decompress error"<<err;
			return false;
		}
		
		memcpy(result, decompr, decomlen);
		
		
		return true;
	}
	
	
    
	
	
};




#endif