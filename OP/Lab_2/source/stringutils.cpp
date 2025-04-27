#include "stringutils.h"
#include <string.h>

int splitLine(const char* line,char d,char** tok,size_t cnt,size_t buf)
{
    char tmp[1024]; strncpy(tmp,line,sizeof(tmp)-1); tmp[sizeof(tmp)-1]='\0';
    size_t n=0; char* p=strtok(tmp,&d);
    while(p && n<cnt){ strncpy(tok[n],p,buf-1); tok[n][buf-1]='\0'; n++; p=strtok(NULL,&d);}
    return n==cnt?0:1;
}
