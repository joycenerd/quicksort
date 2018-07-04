#  quicksort

- 原理：在一個未排序的陣列中，先找一個pivot，在把大於這個pivot和小於這個pivot的元素分成兩堆，藉此確定pivot的位置，這兩堆在分別繼續做前面的動作直到整個陣列都已經sort完

> quicksort運作

- 從main呼叫

```cpp
quicksort(sequence,count,sizeof(int),numcmp);
```
- 這個是sort數字陣列的例子,sequence是數字陣列的開頭元素，count是有幾個元素，sizeof(int)是每個元素的大小，numcmp是數字陣列所對應到的compare function

> quicksort副程式

```cpp
void quicksort(void *start, long long int number, int size, int (*cmp) (void*,void*)){
    //partition到個數剩1的時候結束
    if(number<=1) return;
    // *pivot:基準值, *base:sequence起始位置
    char *pivot,*base=(char*)start;
    pivot=base+(number-1)*size;  //初始pivot是最後一個元素
    // *randomPivot: 用random選出來的新的pivot
    char *randomPivot=base+(rand()%number)*size;
    swap(pivot,randomPivot,size);
 ```

- 用字元指標是因為要做partition和swap的時候比較方便，就給他記憶體位置就好了
- `rand()`: 可以製造random數字的函式
- 因為是用指標，所以告訴指標元素的位置時就要自己去算記憶體的空格，像int是4之類的，不能像普通的陣列一樣用index去找元素，所以我們會每個都乘一個size，這個是每個元素所佔的大小
- `swap`是另一個副程式，用來做兩個元素位置互換的動作

```cpp
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
```
- 將比pivot小和比pivot大的分成兩邊
- ptr是確認pivot應該在的位置，然後最後將pivot放在他的正確位置上

```cpp
    //splitPoint:從base到現在pivot正確位置的前一個元素的元素個數
    //因為pivot已經確定，所以就分別繼續quicksort pivot前和pivot後的元素
    long long int splitPoint=(ptr-base)/size;
    quicksort(base,splitPoint,size,cmp);
    quicksort(ptr+size,number-splitPoint-1,size,cmp);
    return;
}
```

- 和quicksort的觀念一樣，pivot位置確定之後將pivot左邊和右邊各自再去呼叫quicksort去做一樣的事情，直到整個陣列排序完畢

> compare function

- 要比較元素才有辦法做排序，所以會依照要sorting元素的類別去寫不一樣的compare function
- 例如sort普通的數字陣列

```cpp
int numcmp(void *point1, void *point2){
    return *((int *)point1)-*((int *)point2);
}  //sort number的compare function
```
- 傳上來兩個元素的記憶體位置，然後會型轉成他們原本的類型，像這個是數字陣列那就型轉成int去做比較，但記得還是要用指標傳回去
- 又例如sort number pair

```cpp
typedef struct{
    int num1;
    int num2;
}PAIR;   //（num,num)

int paircmp(void *point1,void *point2){
    PAIR first=*(PAIR *)point1, second=*(PAIR *)point2;
    if(first.num1-second.num1==0) return first.num2-second.num2;
    return first.num1-second.num1;
} //sort pair的compare function
```

- 用struct宣告的原因是因為它可以整個用指標丟很方便
- 但記得在compare function中要記得把void指標型轉成struct指標才可以做比較

> swap

```cpp
//做位置交換的function
void swap(char *point1,char *point2,size_t size){
    if(point1==point2) return;
    char *tempMem=(char*)malloc(size);  //交換時的暫存空間
    memcpy(tempMem,point1,size);
    memcpy(point1,point2,size);
    memcpy(point2,tempMem,size);
    return;
}
```
- 因為是指標所以我們做記憶體的搬移來互換元素
- malloc可以自行定義要給的暫存記憶體大小
- `memcpy`和`strncpy`的概念是一樣的





