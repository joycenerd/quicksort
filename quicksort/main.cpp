//
//  main.cpp
//  quicksort
//
//  Created by Joyce Chin on 2018/6/2.
//  Copyright © 2018年 Joyce Chin. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cassert>
#include <vector>
#define NUM 100
#define N 300
using namespace std;

typedef struct{
    int num1;
    int num2;
}PAIR;

typedef struct{
    char char1;
    char char2;
}CHAR;

typedef struct{
    char str;
    int num;
}MIX;

int mixcmp(void *point1, void *point2){
    MIX first=*(MIX *)point1, second=*(MIX *)point2;
    if(first.str-second.str==0) return first.num-second.num;
    return first.str-second.str;
}

int charcmp(void *point1,void *point2){
    CHAR first=*(CHAR *)point1, second=*(CHAR *)point2;
    if(first.char1-second.char1==0) return first.char2-second.char2;
    return first.char1-second.char1;
}

int numcmp(void *point1, void *point2){
    return *((int *)point1)-*((int *)point2);
}

int paircmp(void *point1,void *point2){
    PAIR first=*(PAIR *)point1, second=*(PAIR *)point2;
    if(first.num1-second.num1==0) return first.num2-second.num2;
    return first.num1-second.num1;
}

void swap(char *point1,char *point2,size_t size){
    if(point1==point2) return;
    char *tempMem=(char*)malloc(size);
    memcpy(tempMem,point1,size);
    memcpy(point1,point2,size);
    memcpy(point2,tempMem,size);
    return;
}

void quicksort(void *start, long long int number, int size, int (*cmp) (void*,void*)){
    if(number<=1) return;
    char *pivot,*base=(char*)start;
    pivot=base+(number-1)*size;
    char *randomPivot=base+(rand()%number)*size;
    swap(pivot,randomPivot,size);
    char *ptr,*i;
    ptr=base;
    for(i=base;i<pivot;i+=size){
        if(cmp(i,pivot)<=0){
            swap(i,ptr,size);
            ptr+=size;
        }
    }
    swap(pivot,ptr,size);
    long long int splitPoint=(ptr-base)/size;
    quicksort(base,splitPoint,size,cmp);
    quicksort(ptr+size,number-splitPoint-1,size,cmp);
    return;
}


int main()
{
    FILE *inputFile,*outputFile;
    int sequence[NUM];
    char option[N],inputString[N],input[N];
    char *token;
    inputFile=fopen("/Users/joycechin/Desktop/EX5/quicksort/inputFile","w");
    assert(inputFile!=NULL);
    printf("please enter the type of input: ");
    fgets(inputString,N,stdin);
    fprintf(inputFile,"%s",inputString);
    fclose(inputFile);
    inputFile=fopen("/Users/joycechin/Desktop/EX5/quicksort/inputFile","a+");
    assert(inputFile!=NULL);
    fgets(inputString,N,stdin);
    fprintf(inputFile,"%s",inputString);
    fclose(inputFile);
    inputFile=fopen("/Users/joycechin/Desktop/EX5/quicksort/inputFile","r");
    char line[N];
    int i=0;
    while(fgets(line,sizeof(line),inputFile)){
        if(i==0) strncpy(option,line,strlen(line)-1);
        //printf("%s",option);
        else strcpy(input,line);
        i++;
    }
    int count=0;
    char choice[4][20]={"number","pair","char char","char num"};
    if(strncmp(option,choice[0],6)==0){
        token = strtok(input, " \0"); //告訴strtok()在哪些地方切開
        while (token != NULL){
            sequence[count] = atoi(token); //將字元轉數字
            count++;
            token = strtok(NULL, " \0");
        }
        for(i=0;i<count;i++) printf("%d ",sequence[i]);
        printf("\n");
        quicksort(sequence,count,sizeof(int),numcmp);
        outputFile=fopen("/Users/joycechin/Desktop/EX5/quicksort/outputFile","w");
        assert(outputFile!=NULL);
        for(i=0;i<count;i++) fprintf(outputFile,"%d ",sequence[i]);
        fclose(outputFile);
            /*for(i=0;i<count;i++){
            if(i==0) printf("%d",sequence[i]);
            else printf(" %d",sequence[i]);
        }
        printf("\n");*/
    }
    PAIR pair[NUM];
    if(strncmp(option,choice[1],4)==0){
        token = strtok(input, " \0"); //告訴strtok()在哪些地方切開
        while (token != NULL){
            sscanf(token,"(%d,%d)",&pair[count].num1,&pair[count].num2);
            count++;
            token = strtok(NULL, " \0");
        }
        for(i=0;i<count;i++) printf("(%d %d) ",pair[i].num1,pair[i].num2);
        quicksort(pair, count, sizeof(PAIR), paircmp);
        outputFile=fopen("/Users/joycechin/Desktop/EX5/quicksort/outputFile","w");
        assert(outputFile!=NULL);
        for(i=0;i<count;i++) fprintf(outputFile,"(%d,%d) ",pair[i].num1,pair[i].num2);
        fclose(outputFile);
    }
    CHAR character[NUM];
    if(strncmp(option,choice[2],9)==0){
        token = strtok(input, " \0"); //告訴strtok()在哪些地方切開
        while (token != NULL){
            sscanf(token,"(%c,%c)",&character[count].char1,&character[count].char2);
            count++;
            token = strtok(NULL, " \0");
        }
        for(i=0;i<count;i++) printf("(%c,%c) ",character[i].char1,character[i].char2);
        quicksort(character, count, sizeof(CHAR), charcmp);
        outputFile=fopen("/Users/joycechin/Desktop/EX5/quicksort/outputFile","w");
        assert(outputFile!=NULL);
        for(i=0;i<count;i++)
            fprintf(outputFile,"(%c,%c) ",character[i].char1,character[i].char2);
        fclose(outputFile);
    }
    MIX mix[NUM];
    if(strncmp(option,choice[3],8)==0){
        token = strtok(input, " \0"); //告訴strtok()在哪些地方切開
        while (token != NULL){
            sscanf(token,"(%c,%d)",&mix[count].str,&mix[count].num);
            count++;
            token = strtok(NULL, " \0");
        }
        for(i=0;i<count;i++) printf("(%c,%d) ",mix[i].str,mix[i].num);
        quicksort(mix, count, sizeof(MIX), mixcmp);
        outputFile=fopen("/Users/joycechin/Desktop/EX5/quicksort/outputFile","w");
        assert(outputFile!=NULL);
        for(i=0;i<count;i++)
            fprintf(outputFile,"(%c,%d) ",mix[i].str,mix[i].num);
        fclose(outputFile);
    }
    
    return 0;
}
