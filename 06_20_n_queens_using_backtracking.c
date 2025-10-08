#include <stdio.h>
#define N 8

int board[N][N];

int isSafe(int row, int col) {
    for(int i=0;i<col;i++) if(board[row][i]) return 0;     
    for(int i=row,j=col;i>=0 && j>=0;i--,j--) if(board[i][j]) return 0;
    for(int i=row,j=col;i<N && j>=0;i++,j--) if(board[i][j]) return 0;
    return 1;
}

int solve(int col) {
    if(col >= N) return 1;
    for(int i=0;i<N;i++) {
        if(isSafe(i,col)) {
            board[i][col] = 1;
            if(solve(col+1)) return 1;
            board[i][col] = 0;
        }
    }
    return 0;
}

void printBoard() {
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++) printf("%d ", board[i][j]);
        printf("\n");
    }
}

int main() {
    if(solve(0)) printBoard();
    else printf("No solution exists\n");
    return 0;
}
