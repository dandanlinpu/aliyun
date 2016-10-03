#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "rio.h"
void form_response_header(int fd,int content_len,const char *content_type);
void show_index(int fd,const char *filename);
void process_http_request(char *buf, int len);
void calc(int fd,char *);
