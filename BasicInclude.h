#ifndef BASIC_INCLUDE_H
#define BASIC_INCLUDE_H

#include <iostream>
#include <cstdlib>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <sstream>

#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

#include<omp.h>
#include "zlib.h"
using namespace std;


//**************************************//
//
//		DEFAULT SETTING
//
//
//*************************************//
typedef unsigned short int uint16;
typedef unsigned int uint32;
typedef unsigned long ulong;
typedef unsigned long long uint64;
typedef unsigned char uchar;

typedef short int16;
typedef int int32;
typedef long long int64;



//时间观察类
class TimeWatch
{
	public:
	TimeWatch(bool startWatch=true)
	{
		if(startWatch)
			start();
	}
	
	void start()
	{
		gettimeofday(&startTime, NULL);
	}
	
	void stop(bool print=true)
	{
		gettimeofday(&endTime, NULL);
		
		if(print)
			std::cout<<"Total Time Taken: "<<getDiff()<<" ms."<<std::endl;
	}
	
	void stopS(string output)
	{
		gettimeofday(&endTime, NULL);
		
		std::cout<<"Time Taken for "<<output<<": "<<getDiff()<<" ms."<<std::endl;
	}
	
	double getDiff()
	{
		double tS = startTime.tv_sec * 1000000 + (startTime.tv_usec);
		double tE = endTime.tv_sec * 1000000 + (endTime.tv_usec);
		return ((tE-tS)/1000);
	}
	
	
	private:
	
	struct timeval startTime;
	struct timeval endTime;
};


//********************************************//
//
//		LOAD FILES
//
//*******************************************//

int load_file(string filePath, char *&S, char *&H)
{
	
	ifstream t(filePath.c_str());
	if(!t)
	{
		cout<<"OPEN FILE FAILED"<<endl;
		exit(0);
	}
	string line;
	string head;
	string sequence;
	getline(t, line);
	//处理文件头说明信息
	if(line.at(0)=='>' || line.at(0)=='@')
		head=line;
	else
		sequence=line;
	while(!t.eof()){
		getline(t, line);
		sequence+=line;
	}
	
	//转换大写
	std::transform(sequence.begin(),sequence.end(),sequence.begin(),::toupper);
	long s_length=sequence.length();
	S = (char *) malloc(s_length+1);
	H = (char *) malloc(head.length()+1);
	strcpy(S, sequence.c_str());
	strcpy(H, head.c_str());
	//S[s_length+1]='0';
	//S[s_length+1]='\0';
	
	return s_length;
}

int string2int(string &s)
{
    std::stringstream sstr(s);
    long val;
    sstr >> val;
    return val;
}

void getfilename(const string& inputPath, string& filename)
{
	std::size_t found1=inputPath.find_last_of('/');
	std::size_t found2=inputPath.find_last_of(".");
	filename = inputPath.substr(found1+1,found2-found1-1);
}
void create_out(const string &dir)
{
	struct stat buff;
	int cc = lstat(dir.c_str(), &buff);
	
	if(cc || !(buff.st_mode & S_IFDIR)){
		if(mkdir(dir.c_str(),0777))
		{
			cout<<"Creat Failed";
			exit(-1);
		}
	}
}

string compressname(const string &dir, const string& filename,uint32 i)
{
	string temp=dir+filename;
	temp.append(1,'/');
	struct stat buf;
	int cc = lstat(temp.c_str(), &buf);
	if(cc || !(buf.st_mode & S_IFDIR)){
		if(mkdir(temp.c_str(),0777))
		{
			cout<<"Creat Failed"<<temp<<endl;
			exit(-1);
		}
	}
	std::stringstream sstr;
	sstr<<temp<<i<<".mfc";
	string compressname;
	sstr>>compressname;
	return compressname;	
}


void getfilepath(vector<string> &filePath, string &inputPath)
{
	ifstream t(inputPath.c_str());
	if(!t)
	{
		cout<<"OPEN FILE FAILED"<<endl;
		exit(0);
	}
	string line;
	while(!t.eof())
	{
		getline(t, line);
		if(line.length()!=0)
			filePath.push_back(line);
		else
			break;
	}
	
}





#endif