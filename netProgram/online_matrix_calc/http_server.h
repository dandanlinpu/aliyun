#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "rio.h"
void form_response_header(char *buf,int maxline,int filesize);
void show_index(int fd,const char *filename);

