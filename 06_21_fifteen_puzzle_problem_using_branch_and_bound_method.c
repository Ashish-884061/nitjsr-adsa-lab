#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4
#define SIZE 16

typedef struct Node {
    int mat[SIZE];
    int x, y;       
    int level;      
    int cost;       
    struct Node* parent;
} Node;

typedef struct Heap {
    Node** arr;
    int size;
} Heap;

int row[] = {0,0,-1,1};
int col[] = {-1,1,0,0};

int heuristic(int mat[]) {
    int dist=0;
    for(int i=0;i<SIZE;i++){
        if(mat[i]){
            int tx=(mat[i]-1)/N, ty=(mat[i]-1)%N;
            int cx=i/N, cy=i%N;
            dist += abs(tx-cx)+abs(ty-cy);
        }
    }
    return dist;
}

int isGoal(int mat[]){
    for(int i=0;i<SIZE-1;i++) if(mat[i]!=i+1) return 0;
    return mat[SIZE-1]==0;
}

void swap(int *a,int *b){ int t=*a; *a=*b; *b=t; }

Heap* createHeap(int capacity){
    Heap* h=(Heap*)malloc(sizeof(Heap));
    h->arr=(Node**)malloc(capacity*sizeof(Node*));
    h->size=0;
    return h;
}

void heapifyUp(Heap* h,int i){
    if(i && h->arr[(i-1)/2]->cost > h->arr[i]->cost){
        Node* t=h->arr[i]; h->arr[i]=h->arr[(i-1)/2]; h->arr[(i-1)/2]=t;
        heapifyUp(h,(i-1)/2);
    }
}

void insertHeap(Heap* h, Node* node){
    h->arr[h->size]=node;
    heapifyUp(h,h->size);
    h->size++;
}

Node* extractMin(Heap* h){
    Node* root=h->arr[0];
    h->size--;
    h->arr[0]=h->arr[h->size];
    int i=0;
    while(1){
        int smallest=i;
        int l=2*i+1, r=2*i+2;
        if(l<h->size && h->arr[l]->cost < h->arr[smallest]->cost) smallest=l;
        if(r<h->size && h->arr[r]->cost < h->arr[smallest]->cost) smallest=r;
        if(smallest==i) break;
        Node* t=h->arr[i]; h->arr[i]=h->arr[smallest]; h->arr[smallest]=t;
        i=smallest;
    }
    return root;
}

void printMat(int mat[]){
    for(int i=0;i<SIZE;i++){
        if(i%N==0) printf("\n");
        printf("%2d ", mat[i]);
    }
    printf("\n");
}

int equalMat(int a[], int b[]){
    for(int i=0;i<SIZE;i++) if(a[i]!=b[i]) return 0;
    return 1;
}

void solve(int mat[]){
    int x,y;
    for(int i=0;i<SIZE;i++){ if(mat[i]==0){ x=i/N; y=i%N; break; } }
    
    Heap* h=createHeap(1000000);
    Node* root=(Node*)malloc(sizeof(Node));
    memcpy(root->mat,mat,sizeof(int)*SIZE);
    root->x=x; root->y=y; root->level=0; root->cost=heuristic(mat); root->parent=NULL;
    insertHeap(h,root);

    while(h->size){
        Node* minNode = extractMin(h);
        if(isGoal(minNode->mat)){
            printf("Solution (reverse order):\n");
            Node* tmp=minNode;
            while(tmp){
                printMat(tmp->mat);
                printf("\n");
                tmp=tmp->parent;
            }
            return;
        }
        for(int i=0;i<4;i++){
            int newX=minNode->x+row[i], newY=minNode->y+col[i];
            if(newX>=0 && newX<N && newY>=0 && newY<N){
                Node* child=(Node*)malloc(sizeof(Node));
                memcpy(child->mat,minNode->mat,sizeof(int)*SIZE);
                swap(&child->mat[minNode->x*N+minNode->y], &child->mat[newX*N+newY]);
                child->x=newX; child->y=newY;
                child->level=minNode->level+1;
                child->cost=child->level + heuristic(child->mat);
                child->parent=minNode;
                insertHeap(h,child);
            }
        }
    }
}

int main(){
    int mat[SIZE]={
        1,2,3,4,
        5,6,7,8,
        9,10,11,12,
        13,15,14,0
    };
    solve(mat);
    return 0;
}
