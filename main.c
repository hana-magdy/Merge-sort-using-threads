#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int* InputArray;
int n;


struct position{
int left;
int right;
};

void ReadInputFile(){
 FILE* fptr;
 fptr=fopen("input.txt","r");
 fscanf(fptr,"%d",&n);
 InputArray=malloc(sizeof(int)*n);
 for(int i=0;i<n;i++){
   fscanf(fptr,"%d",&InputArray[i]);
 }
fclose(fptr);
}

void Merge(int l,int r,int m){



    int n1 = m-l+1;
    int n2 = r-m;
    int TempLeft[n1], TempRight[n2];

    for (int i=0;i<n1;i++)
       TempLeft[i] = InputArray[l+i];

    for (int i=0;i<n1;i++)
       TempRight[i] = InputArray[m+1+i];

    int LeftArrIndex=0, RightArrIndex=0 ,OriginalIndex=l;

    while(LeftArrIndex<n1 && RightArrIndex<n2){
         if (TempLeft[LeftArrIndex] <= TempRight[RightArrIndex]) {
            InputArray[OriginalIndex] = TempLeft[LeftArrIndex];
            LeftArrIndex++;
        }
        else {
            InputArray[OriginalIndex] = TempRight[RightArrIndex];
            RightArrIndex++;
        }
        OriginalIndex++;
    }

    while (LeftArrIndex < n1) {
        InputArray[OriginalIndex] = TempLeft[LeftArrIndex];
        LeftArrIndex++;
        OriginalIndex++;
    }

    while (RightArrIndex < n2) {
        InputArray[OriginalIndex] = TempRight[RightArrIndex];
        RightArrIndex++;
        OriginalIndex++;
    }



}


void *MergeSort(void * data){


    struct position *pos;
    pos=(struct position *)data;
    int l=pos->left;
    int r=pos->right;

    if(l>=r){
        return;
    }

    int m = (l+r)/2;
    pthread_t LeftThread, RightThread;
    struct position *LeftPos, *RightPos;

    LeftPos= malloc(sizeof(struct position));
    LeftPos->left=l;
    LeftPos->right=m;
    pthread_create(&LeftThread, NULL, MergeSort, (void *)LeftPos);

    RightPos= malloc(sizeof(struct position));
    RightPos->left=m+1;
    RightPos->right=r;
    pthread_create(&RightThread, NULL, MergeSort, (void *)RightPos);

    pthread_join(LeftThread, NULL);
    pthread_join(RightThread, NULL);

    Merge(l,r,m);


}


int main()
{



    ReadInputFile();

    pthread_t firstThread;
    struct position *pos;
    pos = malloc(sizeof(struct position));
    pos->left = 0;
    pos->right = n-1;
    pthread_create(&firstThread, NULL, MergeSort, (void *)pos);
    pthread_join(firstThread,NULL);

    for(int i=0;i<n;i++){
      printf("%d ",(InputArray[i]));
    }
    printf("\n");


    return 0;
}
