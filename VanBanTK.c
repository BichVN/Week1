#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000

typedef struct wordPosL{
    int value;
    struct wordPosL *next;
}wordPosL_t;

typedef char AWord[MAX];

AWord stopList[MAX];
int   stopCount=0;
int headLine = 1;
int find(AWord word,AWord *stopList,int stopCount);// tim tu trong mang char co trong danh sach stop khong
int isExist(char *word,AWord* wordList, int wordListNum);
void wordProcess(char *word, int line,AWord* wordList,wordPosL_t *wordPos, int *wordListNum);
void sort(AWord* wordList,wordPosL_t *wordPos, int wordListNum);
void addLine(wordPosL_t *aNode,int line);
void addWord(wordPosL_t *aNode,int line);
void printList(wordPosL_t *root);

int main(){
  FILE *f1,*f2,*f3;
    char word[MAX];
    char letter;

    AWord stopWord;

    AWord  wordList[MAX];
    wordPosL_t wordPos[MAX];
    int wordListNum=0;
    int line=1;
    int temp,n;


    strcpy(word,"");
    f1 = fopen("vanban.txt","r+");
    f2 = fopen("stopw.txt","r+");
    f3 = fopen("result_1.txt","w");
    //Read stopWord list roi luu vao mang char stopWord
    while (fscanf(f2,"%s",stopWord)!=-1)
        strcpy(stopList[stopCount++], stopWord);

    //Read vanban
    while (fscanf(f1,"%c",&letter)!=-1){

        if (((letter!='\n')&&(letter!=' '))&&(letter!='\r')&&(letter!='.')){ 
	    n         = strlen(word);
            word[n]   = letter;
            word[n+1] = '\0';
        }
        else{
            if (!find(word,stopList,stopCount))
                wordProcess(word,line,wordList,wordPos,&wordListNum);
            strcpy(word,"");
        }
        if (letter=='\n')
            line++;
        if (letter=='\n')
            headLine = 1;
        if (letter==' ')
            headLine = 0;
    }
    if (!find(word,stopList,stopCount))
        wordProcess(word,line,wordList,wordPos,&wordListNum);

    int i;
    sort(wordList,wordPos,wordListNum);
    for (i=0;i<wordListNum;i++){
      printf("%s ",wordList[i]);
      printList(&wordPos[i]);
      printf("\n");
       
    }
    fclose(f1);
    fclose(f2);
    fclose(f3);
    return 0;
}

void wordProcess(char *word, int line,AWord* wordList,wordPosL_t *wordPos, int *wordListNum){
    if (strcmp(word,"")==0) return;
    if (!headLine)
        if ((word[0]>=65)&&(word[0]<=90)) return;
    if ((word[0]<65)||(word[0]>122)) return;

    int i,n= strlen(word);
    for (i=0;i<n;i++){
        if ((word[i]<65)||(word[i]>122)) return;
        if ((word[i]>=65)&&(word[i]<=90))
            word[i] = word[i] +32;
    }

    if (find(word,stopList,stopCount)) return;

    int temp;
    temp = isExist(word,wordList,*wordListNum);
    if (temp!=-1)
        addLine(&wordPos[temp],line);
    else{
        strcpy(wordList[*wordListNum],word);
        addWord(&wordPos[*wordListNum],line);
        (*wordListNum)++;
    }
    strcpy(word,"");
}

int isExist(char *word,AWord* wordList, int wordListNum){
    int i;
    for (i=0;i<wordListNum;i++)
        if (strcmp(word,wordList[i])==0)
            return i;
    return -1;
}

void addLine(wordPosL_t *aNode,int line){
    wordPosL_t *root    = aNode;
    while (root->next!= NULL)
        root =root->next;
    if (root->value == line) return;

    wordPosL_t *newNode = (wordPosL_t*) malloc (sizeof(wordPosL_t));
    newNode->value            = line;
    newNode->next             = NULL;

    root->next               = newNode;
}

void addWord(wordPosL_t *aNode,int line){
    aNode->value            = line;
    aNode->next             = NULL;
}

void printList(wordPosL_t *root){
    wordPosL_t *cur= root;
    int wordCount = 0;

    while (root!=NULL){

        wordCount++;
        root = root->next;
    }

   printf("%d ",wordCount);

    while (cur!=NULL){
      printf("%d ",cur->value);
        cur = cur->next;
    }
}

void swapwordPos(wordPosL_t *a,wordPosL_t *b){
    wordPosL_t c;
    c  =*a;
    *a =*b;
    *b = c;
}

void sort(AWord* wordList,wordPosL_t *wordPos, int wordListNum){
    int i,j;
    AWord tempW;
    for (i=0;i<wordListNum-1;i++)
        for (j=i+1;j<wordListNum;j++)
        if (strcmp(wordList[i],wordList[j])==1){
            strcpy(tempW,wordList[i]);
            strcpy(wordList[i],wordList[j]);
            strcpy(wordList[j],tempW);
            swapwordPos(&wordPos[i],&wordPos[j]);
        }
}

int find(AWord word,AWord *stopList,int stopCount){
    int i;
    for (i=0;i<stopCount;i++)
        if (strcmp(stopList[i],word)==0)
            return 1;
    return 0;
}
