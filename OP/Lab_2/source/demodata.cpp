#include "demodata.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringutils.h"

int initDemographicArray(DemographicArray* a)
{
    a->records=NULL; a->size=0; a->capacity=0;
    a->records=(DemographicRecord*)malloc(10*sizeof(DemographicRecord));
    if(!a->records) return ERR_MEM;
    a->capacity=10; return OK;
}
static int ensureCap(DemographicArray* a)
{
    if(a->size<a->capacity) return OK;
    size_t nc=a->capacity*2;
    void* p=realloc(a->records,nc*sizeof(DemographicRecord));
    if(!p) return ERR_MEM;
    a->records=(DemographicRecord*)p; a->capacity=nc; return OK;
}
int pushDemographicRecord(DemographicArray* a,const DemographicRecord* r)
{
    int st=ensureCap(a); if(st!=OK) return st;
    a->records[a->size++]=*r; return OK;
}
void freeDemographicArray(DemographicArray* a)
{
    free(a->records); a->records=NULL;a->size=a->capacity=0;
}

static int parseLine(const char* line,DemographicRecord* rec)
{
    char t[CSV_FIELDS][FIELD_SIZE]; char* p[CSV_FIELDS];
    for(int i=0;i<CSV_FIELDS;i++){p[i]=t[i];t[i][0]='\0';}
    if(splitLine(line,',',p,CSV_FIELDS,FIELD_SIZE)) return 1;
    strncpy(rec->year  ,p[0],FIELD_SIZE-1); rec->year  [FIELD_SIZE-1]='\0';
    strncpy(rec->region,p[1],FIELD_SIZE-1); rec->region[FIELD_SIZE-1]='\0';
    rec->npg         = atof(p[2]);
    rec->birthRate   = atof(p[3]);
    rec->deathRate   = atof(p[4]);
    rec->gdw         = atof(p[5]);
    rec->urbanization= atof(p[6]);
    return 0;
}

int parseCSVFile(const char* fn,DemographicArray* a,size_t* tot,size_t* bad)
{
    FILE* f=fopen(fn,"r"); if(!f) return ERR_FILE;
    char buf[1024]; *tot=*bad=0;
    fgets(buf,sizeof(buf),f);                         /* заголовок */
    while(fgets(buf,sizeof(buf),f)){
        (*tot)++; size_t len=strlen(buf);
        if(len&&buf[len-1]=='\n') buf[len-1]='\0';
        DemographicRecord r;
        if(parseLine(buf,&r)) {(*bad)++; continue;}
        if(pushDemographicRecord(a,&r)!=OK){fclose(f);return ERR_MEM;}
    }
    fclose(f); return OK;
}

static void qsortD(double* v,size_t l,size_t r)
{
    if(l>=r) return;
    double p=v[(l+r)/2]; size_t i=l,j=r;
    while(i<=j){
        while(v[i]<p)i++; while(v[j]>p)j--;
        if(i<=j){double tmp=v[i];v[i]=v[j];v[j]=tmp;i++; if(j)j--;}
    }
    if(j>l) qsortD(v,l,j); if(i<r) qsortD(v,i,r);
}
static double getVal(const DemographicRecord* r,int c)
{
    switch(c){
    case COL_NPG:          return r->npg;
    case COL_BIRTH_RATE:   return r->birthRate;
    case COL_DEATH_RATE:   return r->deathRate;
    case COL_GDW:          return r->gdw;
    case COL_URBANIZATION: return r->urbanization;
    default:               return 0.0;
    }
}

int calculateMinMaxMedian(const DemographicArray* a,const char* region,
                          int col,double* mn,double* mx,double* med)
{
    if(!a||a->size==0||col<3||col>7) return ERR_USER_INPUT;
    double* vals=NULL; size_t n=0,cap=0;
    for(size_t i=0;i<a->size;i++){
        const DemographicRecord* r=&a->records[i];
        if(region&&*region&&strcmp(r->region,region)!=0) continue;
        if(n==cap){size_t nc=cap?cap*2:16;double* p=(double*)realloc(vals,nc*sizeof(double));
            if(!p){free(vals);return ERR_MEM;} vals=p; cap=nc;}
        vals[n++]=getVal(r,col);
    }
    if(n==0){free(vals);return ERR_NOT_FOUND;}
    *mn=*mx=vals[0];
    for(size_t i=1;i<n;i++){ if(vals[i]<*mn)*mn=vals[i]; if(vals[i]>*mx)*mx=vals[i];}
    qsortD(vals,0,n-1);
    *med = (n%2)? vals[n/2] : (vals[n/2-1]+vals[n/2])/2.0;
    free(vals); return OK;
}
