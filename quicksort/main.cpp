//
//  main.cpp
//  quicksort
//
//  Created by Joyce Chin on 2018/6/2.
//  Copyright © 2018年 Joyce Chin. All rights reserved.
//


#include <cstdio>
#include <cassert>
#include <cstring>
#define NUM 100
#define N 10000
#define LEN 20
using namespace std;


int numcmp(void *point1, void *point2){
    return *((int *)point1)-*((int *)point2);
}  //sort number的compare function

typedef struct{
    int num1;
    int num2;
}PAIR;   //（num,num)

int paircmp(void *point1,void *point2){
    PAIR first=*(PAIR *)point1, second=*(PAIR *)point2;
    if(first.num1-second.num1==0) return first.num2-second.num2;
    return first.num1-second.num1;
} //sort pair的compare function

typedef struct{
    char char1;
    char char2;
}CHAR;   //（char,char)

int charcmp(void *point1,void *point2){
    CHAR first=*(CHAR *)point1, second=*(CHAR *)point2;
    if(first.char1-second.char1==0) return first.char2-second.char2;
    return first.char1-second.char1;
}   //sort char char的compare function

typedef struct{
    char str;
    int num;
}MIX;  //(char,num)

int mixcmp(void *point1, void *point2){
    MIX first=*(MIX *)point1, second=*(MIX *)point2;
    if(first.str-second.str==0) return first.num-second.num;
    return first.str-second.str;
}  //sort char num的compare function

//做位置交換的function
void swap(char *point1,char *point2,size_t size){
    if(point1==point2) return;
    char *tempMem=(char*)malloc(size);  //交換時的暫存空間
    memcpy(tempMem,point1,size);
    memcpy(point1,point2,size);
    memcpy(point2,tempMem,size);
    return;
}

//做quicksort的function
// *start:sequence起始位置, *number:整個sequence的個數, *size:傳上來的型態單個的size
//(*cmp): 不同型態搭配的compare function
void quicksort(void *start, long long int number, int size, int (*cmp) (void*,void*)){
    //partition到個數剩1的時候結束
    if(number<=1) return;
    // *pivot:基準值, *base:sequence起始位置
    char *pivot,*base=(char*)start;
    pivot=base+(number-1)*size;  //初始pivot是最後一個元素
    // *randomPivot: 用random選出來的新的pivot
    char *randomPivot=base+(rand()%number)*size;
    swap(pivot,randomPivot,size);
    char *ptr,*i;
    ptr=base;
    //做pivot和其他元素的比較，藉此確認pivot應該在的位置
    for(i=base;i<pivot;i+=size){
        if(cmp(i,pivot)<=0){
            swap(i,ptr,size);
            ptr+=size;
        }
    }
    swap(pivot,ptr,size);
    //splitPoint:從base到現在pivot正確位置的前一個元素的元素個數
    //因為pivot已經確定，所以就分別繼續quicksort pivot前和pivot後的元素
    long long int splitPoint=(ptr-base)/size;
    quicksort(base,splitPoint,size,cmp);
    quicksort(ptr+size,number-splitPoint-1,size,cmp);
    return;
}


int main()
{
    FILE *inputFile,*outputFile;
    int i,count;
    char line[N],option[LEN],input[N];
    char choice[][LEN]={"number","pair","char char","char num","no"};
    inputFile=fopen("/Users/joycechin/Desktop/EX5/quicksort/sampleInputFile.in","r");
    assert(inputFile!=NULL);
    outputFile=fopen("/Users/joycechin/Desktop/EX5/quicksort/outputFile.out","w");
    assert(outputFile!=NULL);
    while(1){
        fgets(line,N,inputFile);
        strncpy(option,line,strlen(line)-1);
        option[strlen(line)-1]='\0';
        printf("option=%s\n",option);
        if(strncmp(option,choice[4],2)==0){
            break;
        }
        fgets(input,N,inputFile);
        printf("%s",input);
        char *token;
        //sort number情況
        int sequence[NUM];  //number序列
        if(strncmp(option,choice[0],6)==0){
            count=0;
            token = strtok(input, " \0");
            while (token != NULL){
                sequence[count] = atoi(token);
                count++;
                token = strtok(NULL, " \0");
            }
            //for(i=0;i<count;i++) printf("%d ",sequence[i]);
            //printf("\n");
            quicksort(sequence,count,sizeof(int),numcmp);
            fprintf(outputFile,"This is a number sequence\n");
            for(i=0;i<count;i++) fprintf(outputFile,"%d ",sequence[i]);
            fprintf(outputFile,"\n\n");
        }
        //sort pair情況
        PAIR pair[NUM];  //struct (num,num)
        if(strncmp(option,choice[1],4)==0){
            count=0;
            token = strtok(input, " \n"); //告訴strtok()在哪些地方切開
            while (token != NULL){
                sscanf(token,"(%d,%d)",&pair[count].num1,&pair[count].num2);
                count++;
                token = strtok(NULL, " \n");
            }
            //for(i=0;i<count;i++) printf("(%d %d) ",pair[i].num1,pair[i].num2);
            quicksort(pair, count, sizeof(PAIR), paircmp);
            fprintf(outputFile,"This is a number pair sequence\n");
            for(i=0;i<count;i++) fprintf(outputFile,"(%d,%d) ",pair[i].num1,pair[i].num2);
            fprintf(outputFile,"\n\n");
        }
        //sort char char pair
        CHAR character[NUM];  //struct (char,char)
        if(strncmp(option,choice[2],9)==0){
            count=0;
            token = strtok(input, " \n");
            while (token != NULL){
                sscanf(token,"(%c,%c)",&character[count].char1,&character[count].char2);
                count++;
                token = strtok(NULL, " \n");
            }
            //for(i=0;i<count;i++) printf("(%c,%c) ",character[i].char1,character[i].char2);
            quicksort(character, count, sizeof(CHAR), charcmp);
            fprintf(outputFile,"This is a character pair sequence\n");
            for(i=0;i<count;i++) fprintf(outputFile,"(%c,%c) ",character[i].char1,character[i].char2);
            fprintf(outputFile,"\n\n");
        }
        //sort char num情況
        MIX mix[NUM];
        if(strncmp(option,choice[3],8)==0){
            count=0;
            token = strtok(input, " \n");
            while (token != NULL){
                sscanf(token,"(%c,%d)",&mix[count].str,&mix[count].num);
                count++;
                token = strtok(NULL, " \n");
            }
            //for(i=0;i<count;i++) printf("(%c,%d) ",mix[i].str,mix[i].num);
            quicksort(mix, count, sizeof(MIX), mixcmp);
            fprintf(outputFile,"This is a character and number pair sequence\n");
            for(i=0;i<count;i++) fprintf(outputFile,"(%c,%d) ",mix[i].str,mix[i].num);
            fprintf(outputFile,"\n\n");
        }
    }
   /* while(1){
        //開始將輸入寫入inputFile中
        inputFile=fopen("/Users/joycechin/Desktop/EX5/quicksort/inputFile","w");
        assert(inputFile!=NULL);
        //指定要輸入的type：number,(num,num),(char,char),(char,num)
        printf("please enter the type of input: ");
        char inputString[N]; //輸入的字串
        fgets(inputString,N,stdin);
        fprintf(inputFile,"%s",inputString);
        fclose(inputFile);
        //輸入完type之後就輸入要sort的sequence
        inputFile=fopen("/Users/joycechin/Desktop/EX5/quicksort/inputFile","a+");
        assert(inputFile!=NULL);
        fgets(inputString,N,stdin);
        fprintf(inputFile,"%s",inputString);
        fclose(inputFile);
        inputFile=fopen("/Users/joycechin/Desktop/EX5/quicksort/inputFile","r");
        //一行一行地將剛才的輸入從inputFile中讀出來處理
        //line[]是我從inputFile中讀出來的
        //option[]是存我的input type字串
        //input[]是要sorting的序列
        char line[N],input[N];
        i=0;
        while(fgets(line,sizeof(line),inputFile)){
            if(i==0) strncpy(option,line,strlen(line)-1);
            //printf("%s",option);
            else strcpy(input,line);
            i++;
        }
        int count;
        //choice是所有可輸入的input type
        char choice[][LEN]={"number","pair","char char","char num","no"};
        char *token;
        //終止條件是當option是 no的時候
        if(strncmp(option,choice[4],2)==0){
            break;
        }
        //sort number情況
        int sequence[NUM];  //number序列
        if(strncmp(option,choice[0],6)==0){
            count=0;
            token = strtok(input, " \0");
            while (token != NULL){
                sequence[count] = atoi(token);
                count++;
                token = strtok(NULL, " \0");
            }
            //for(i=0;i<count;i++) printf("%d ",sequence[i]);
            //printf("\n");
            quicksort(sequence,count,sizeof(int),numcmp);
            outputFile=fopen("/Users/joycechin/Desktop/EX5/quicksort/outputFile","w");
            assert(outputFile!=NULL);
            for(i=0;i<count;i++) fprintf(outputFile,"%d ",sequence[i]);
            fclose(outputFile);
        }
        //sort pair情況
        PAIR pair[NUM];  //struct (num,num)
        if(strncmp(option,choice[1],4)==0){
            count=0;
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
        //sort char char pair
        CHAR character[NUM];  //struct (char,char)
        if(strncmp(option,choice[2],9)==0){
            count=0;
            token = strtok(input, " \0");
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
        //sort char num情況
        MIX mix[NUM];
        if(strncmp(option,choice[3],8)==0){
            count=0;
            token = strtok(input, " \0");
            while (token != NULL){
                sscanf(token,"(%c,%d)",&mix[count].str,&mix[count].num);
                count++;
                token = strtok(NULL, " \0");
            }
            for(i=0;i<count;i++) printf("(%c,%d) ",mix[i].str,mix[i].num);
            quicksort(mix, count, sizeof(MIX), mixcmp);
            outputFile=fopen("/Users/joycechin/Desktop/EX5/quicksort/outputFile","w");
            assert(outputFile!=NULL);
            for(i=0;i<count;i++) fprintf(outputFile,"(%c,%d) ",mix[i].str,mix[i].num);
            fclose(outputFile);
        }
        printf("please check inputFile and outFile,and press 0 after it\n");
        char enter[10];
        fgets(enter,10,stdin);
    }*/
    return 0;
}
