#ifndef SERIALIZEREACH_H
#define SERIALIZEREACH_H

#include"../Recompress/zlibcom.h"

#define MAXBUFFERSIZE 102400

class SerializerEach : public AbstractSerializer
{
	public:
	SerializerEach(){};
	~SerializerEach(){};
	
	void serializer(vector<CompressNode> &mfc, string& outPath)
	{
		uint32 oldpos=0;
		std::stringstream str_buf;
		vector<CompressNode>::const_iterator iter=mfc.begin();
		while(iter!=mfc.end())
		{
			
			if((*iter).mischar!='0')
			{
				if(iter!=mfc.end()&&(*iter).mischar=='N'&&(*iter).endpos!=0)
				{
					str_buf<<(*iter).endpos<<'^'<<"\n";
					iter++;					
				}
				else
				{
					string misstr;
					while(iter!=mfc.end()&&(*iter).endpos==0)
					{
						misstr.append(1,(*iter).mischar);
						iter++;
					}
					misstr.append("\n");
					str_buf<<misstr;
				}
			}
			else
			{
				int32 curlen=(*iter).endpos-(*iter).startpos;
				int32 curpos=(*iter).startpos-oldpos;
				oldpos = (*iter).endpos;				
				str_buf<<curpos<<","<<curlen<<"\n";
				iter++;				
			}
		}
		string zlib_com=str_buf.str();
		
		zlibcom *zlib=new zlibcom();
		zlib->Compress(zlib_com.c_str(), outPath);
		delete zlib;
	}
	
	void unserializer(string &inPath,const fragnode &reference)
	{
		cout<<inPath<<endl;
		stringstream str_buf1;
		
		char *result = new char[MAXBUFFERSIZE];
		zlibcom *zlib=new zlibcom();
		zlib->deCompress(inPath, result);
		char *currpos=result;
		int prev_end=0;
		cout<<"start......."<<endl;
		while(*currpos != '\0')
		{
			string line;
			//char *start=currpos;
			while(*currpos!='\n'){
				line.push_back(*currpos);			
				currpos++;
				
			}
			std::size_t found = std::string::npos;
			if((found=line.find(','))!=std::string::npos){
				string s1=line.substr(0,found);
				string s2=line.substr(found+1);
				
				int s_pos=string2int(s1);
				int length=string2int(s2);
				s_pos+=prev_end;
				prev_end = s_pos+length;
//				cout<<s_pos<<","<<prev_end<<endl;
				str_buf1<<string(reference.startpos+s_pos,length+1);
//				cout<<string(reference.startpos+s_pos,length)<<endl;
				
			}
			else if((found=line.find('^'))!=std::string::npos)  //可以改成^16，这样更快
			{
				string s1=line.substr(0,found);
				int length=string2int(s1);
//				cout<<s1<<","<<"N"<<endl;
				str_buf1<<string(length,'N');	
//				cout<<string(length,'N')<<endl;	
			}
			else{
				str_buf1<<line;
//				cout<<line<<endl;
			}
			currpos++;
							
		}
		string my_result = str_buf1.str();
		string temp_result;
		temp_result.append(1,my_result.at(0));
		for(int i=1; i<my_result.length();i++)
		{
			if(i%60 == 0)
				temp_result.append(1,'\n');
			temp_result.append(1,my_result.at(i));
		}
		cout<<temp_result<<endl;
		
			
		delete []result;
		
		
		delete zlib;
	}
	
	
};


#endif