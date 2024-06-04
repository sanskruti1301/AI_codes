#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 3

typedef struct Node {
    int puzzle[N][N];
    struct Node* parent;
    int x, y; // Blank tile coordinates
    int cost; // Total cost from the start node
    int level; // Depth of the current node in the search tree
} Node;

// Function declarations
void printPuzzle(int puzzle[N][N]);
bool isGoal(int puzzle[N][N], int goal[N][N]);
Node* newNode(int puzzle[N][N], int x, int y, int newX, int newY, int level, Node* parent, int goal[N][N]);
int calculateCost(int puzzle[N][N], int goal[N][N]);
void bestFirstSearch(int puzzle[N][N], int goal[N][N]);
void swap(int* x, int* y);

int main() {
    int puzzle[N][N] = {
        {1, 2, 3},
        {5, 6, 0},
        {7, 8, 4}
    };

    int goal[N][N] = {
        {1, 2, 3},
        {5, 8, 6},
        {0, 7, 4}
    };

    bestFirstSearch(puzzle, goal);

    return 0;
}

// Function to print the puzzle
void printPuzzle(int puzzle[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", puzzle[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Function to check if the current state is the goal state
bool isGoal(int puzzle[N][N], int goal[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (puzzle[i][j] != goal[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// Function to create a new node with a given state
Node* newNode(int puzzle[N][N], int x, int y, int newX, int newY, int level, Node* parent, int goal[N][N]) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->parent = parent;

    // Copy the current puzzle state to the new node
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            node->puzzle[i][j] = puzzle[i][j];
        }
    }

    // Swap the blank tile with the given tile
    swap(&node->puzzle[x][y], &node->puzzle[newX][newY]);

    // Update the blank tile coordinates
    node->x = newX;
    node->y = newY;

    // Update the cost and level of the new node
    node->cost = calculateCost(node->puzzle, goal);
    node->level = level;

    return node;
}

// Function to calculate the cost of a given state
int calculateCost(int puzzle[N][N], int goal[N][N]) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (puzzle[i][j] && puzzle[i][j] != goal[i][j]) {
                count++;
            }
        }
    }
    return count;
}

// Function to perform Best-First Search
void bestFirstSearch(int puzzle[N][N], int goal[N][N]) {
    // Create the initial node and set its cost
    Node* root = newNode(puzzle, 1, 2, 1, 2, 0, NULL, goal);
    root->cost = calculateCost(root->puzzle, goal);

    // Create a priority queue and enqueue the root node
    // The priority queue is implemented as an array, where the first element has the lowest cost
    Node* priorityQueue[1000];
    int front = 0, rear = 0;
    priorityQueue[rear++] = root;

    // Perform Best-First Search
    while (front < rear) {
        Node* min = priorityQueue[front++];

        // If the current state is the goal state, print the solution
        if (isGoal(min->puzzle, goal)) {
            printf("Solution Found:\n");
            while (min != NULL) {
                printPuzzle(min->puzzle);
                min = min->parent;
            }
            return;
        }

        // Generate all possible child nodes from the current node
        // and enqueue them in the priority queue based on their costs
        if (min->x - 1 >= 0) {
            priorityQueue[rear++] = newNode(min->puzzle, min->x, min->y, min->x - 1, min->y, min->level + 1, min, goal);
        }
        if (min->x + 1 < N) {
            priorityQueue[rear++] = newNode(min->puzzle, min->x, min->y, min->x + 1, min->y, min->level + 1, min, goal);
        }
        if (min->y - 1 >= 0) {
            priorityQueue[rear++] = newNode(min->puzzle, min->x, min->y, min->x, min->y - 1, min->level + 1, min, goal);
        }
        if (min->y + 1 < N) {
            priorityQueue[rear++] = newNode(min->puzzle, min->x, min->y, min->x, min->y + 1, min->level + 1, min, goal);
        }
    }

    printf("Solution not found.\n");
}

// Function to swap two integers
void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}
