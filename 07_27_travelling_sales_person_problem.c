#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

int greedyTSP(int n, int dist[n][n]) {
    int visited[n]; for(int i=0;i<n;i++) visited[i]=0;
    int curr=0, total=0; visited[0]=1;

    for(int k=0;k<n-1;k++){
        int next=-1, minD=INT_MAX;
        for(int i=0;i<n;i++){
            if(!visited[i] && dist[curr][i]<minD){ minD=dist[curr][i]; next=i; }
        }
        visited[next]=1; total+=minD; curr=next;
    }
    total += dist[curr][0];
    return total;
}

int main(){
    int sizes[] = {10,20,40,60,100};
    srand(time(0));

    printf("Nodes\tTime(ms)\tTSP cost(approx)\n");
    for(int s=0;s<5;s++){
        int n = sizes[s];
        int dist[n][n];
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                dist[i][j] = (i==j)?0:(rand()%100+1);

        clock_t start = clock();
        int cost = greedyTSP(n, dist);
        clock_t end = clock();
        double time_taken = (double)(end-start)/CLOCKS_PER_SEC*1000; 
        printf("%d\t%.3f\t%d\n", n, time_taken, cost);
    }
}
