#include "tool.h"
void exit_if(int r,const char *info){
	if(r<0){
		printf(info);
		printf("%s %d errno:%d,error msg:%s\n",__FILE__,__LINE__,errno,strerror(errno));
		exit(-1);
	}
}
int get_filesize(const char *path){
	struct stat fstat;
	int r = stat(path,&fstat);
	exit_if(r,"get_filesize(const char *) failed!");
	return fstat.st_size;
}
int get_filesize(FILE *fp){
	fseek(fp,0,SEEK_END);
        int filesize=ftell(fp);
	fseek(fp,0,SEEK_SET);
 	return filesize;
}
/*
int main(){
	FILE *fp=fopen("1.txt","r");
	printf("size %d",get_filesize(fp));
	printf("size %d",get_filesize("1.txt"));
	printf("size %d",get_filesize("2.txt"));
}
*/
