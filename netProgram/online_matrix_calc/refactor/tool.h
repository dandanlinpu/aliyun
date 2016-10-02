#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<sys/unistd.h>
#include<errno.h>
void exit_if(int r,const char *info);
int get_filesize(const char *path);
int get_filesize(FILE *fp);
