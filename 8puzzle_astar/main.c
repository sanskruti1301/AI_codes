#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 3

void findZero(int board[N][N], int *x, int *y) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 0) {
                *x = i;
                *y = j;
                return;
            }
        }
    }
}

void printBoard(int board[N][N], int g, int h, int cost) {
    printf("Cost: %d (g: %d, h: %d)\n", cost, g, h);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

bool isGoalState(int board[N][N], int goal[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] != goal[i][j]) {
                return false;
            }
        }
    }
    return true;
}

int findMisplacedTiles(int board[N][N], int goal[N][N]) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] != goal[i][j]) {
                count++;
            }
        }
    }
    return count;
}

void aStar(int board[N][N], int goal[N][N], int depth, int x, int y) {
    // Priority Queue using a simple array (min-heap)
    int pq[1000][N][N];
    int front = 0, rear = 0;

    int g = depth;
    int h = findMisplacedTiles(board, goal);
    int cost = g + h;

    // Push the initial state into the priority queue
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            pq[rear][i][j] = board[i][j];
        }
    }
    rear++;

    while (front < rear) {
        int curr[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                curr[i][j] = pq[front][i][j];
            }
        }
        front++;

        findZero(curr, &x, &y);

        if (isGoalState(curr, goal)) {
            printf("Goal State Reached\n");
            return;
        }

        printBoard(curr, g, h, cost);

        int dx[] = {0, 0, -1, 1};
        int dy[] = {1, -1, 0, 0};

        for (int i = 0; i < 4; i++) {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
                // Swap elements and calculate new g, h, and cost
                int temp = curr[x][y];
                curr[x][y] = curr[newX][newY];
                curr[newX][newY] = temp;

                g = depth + 1;
                h = findMisplacedTiles(curr, goal);
                cost = g + h;

                // Push the new state into the priority queue
                for (int i = 0; i < N; i++) {
                    for (int j = 0; j < N; j++) {
                        pq[rear][i][j] = curr[i][j];
                    }
                }
                rear++;

                // Swap back to revert the changes
                temp = curr[x][y];
                curr[x][y] = curr[newX][newY];
                curr[newX][newY] = temp;
            }
        }
    }
}

int main() {
    int initial[N][N] = {{1,2,3,}, {0,5,4}, {6,7,8}};
    int goal[N][N] = {{1, 2, 3}, {5, 0, 4}, {6,7,8}};
    int x, y;
    findZero(initial, &x, &y);
    aStar(initial, goal, 0, x, y);
    return 0;
}
