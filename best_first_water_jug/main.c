#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 3

// Data structure to represent a puzzle state
struct State {
    int puzzle[N][N];
    struct State* parent;
    int move;
    int cost; // Total cost (g + h)
};

// Function to compare two puzzle states for equality
bool isEqual(int puzzle1[N][N], int puzzle2[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (puzzle1[i][j] != puzzle2[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// Function to check if a state is the goal state (solved)
bool isGoalState(struct State* state, int goal[N][N]) {
    return isEqual(state->puzzle, goal);
}

// Function to print the puzzle state
void printPuzzle(int puzzle[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", puzzle[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Function to create a new puzzle state
struct State* newState(int puzzle[N][N], int move, struct State* parent, int goal[N][N]) {
    struct State* state = (struct State*)malloc(sizeof(struct State));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            state->puzzle[i][j] = puzzle[i][j];
        }
    }
    state->move = move;
    state->parent = parent;
    // Calculate the Manhattan distance heuristic
    state->cost = move + calculateManhattanDistance(state->puzzle, goal);
    return state;
}

// Function to swap two puzzle elements
void swap(int* x1, int* x2) {
    int temp = *x1;
    *x1 = *x2;
    *x2 = temp;
}

// Function to calculate the Manhattan distance heuristic
int calculateManhattanDistance(int puzzle[N][N], int goal[N][N]) {
    int distance = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (puzzle[i][j] != 0) {
                int goalX, goalY;
                findTile(goal, puzzle[i][j], &goalX, &goalY);
                distance += abs(i - goalX) + abs(j - goalY);
            }
        }
    }
    return distance;
}

// Function to find the position of a tile in the puzzle
void findTile(int puzzle[N][N], int tile, int* x, int* y) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (puzzle[i][j] == tile) {
                *x = i;
                *y = j;
                return;
            }
        }
    }
}

// Function to generate successor states
void getSuccessors(struct State* parent, struct State* successors[], int goal[N][N]) {
    int x, y;
    findTile(parent->puzzle, 0, &x, &y);

    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    for (int i = 0; i < 4; i++) {
        int newX = x + dx[i];
        int newY = y + dy[i];
        if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
            struct State* child = newState(parent->puzzle, parent->move + 1, parent, goal);
            swap(&child->puzzle[x][y], &child->puzzle[newX][newY]);
            successors[i] = child;
        } else {
            successors[i] = NULL;
        }
    }
}

// Function to apply Best-First Search to solve the puzzle
void solvePuzzle(int puzzle[N][N], int goal[N][N]) {
    struct State* initialState = newState(puzzle, 0, NULL, goal);

    struct State* priorityQueue[1000];
    int front = 0, rear = 0;

    priorityQueue[rear++] = initialState;

    while (front < rear) {
        struct State* currentState = priorityQueue[front++];

        // Add print statement to check the puzzle state being explored
        printf("Exploring state:\n");
        printPuzzle(currentState->puzzle);

        if (isGoalState(currentState, goal)) {
            // Print the solution path
            printSolutionPath(currentState);
            printf("Puzzle Solved in %d moves\n", currentState->move);
            return;
        }

        struct State* successors[4];
        getSuccessors(currentState, successors, goal);

        for (int i = 0; i < 4; i++) {
            if (successors[i] != NULL) {
                // Insert successors into the priority queue based on their cost
                int j;
                for (j = rear - 1; j >= 0; j--) {
                    if (successors[i]->cost >= priorityQueue[j]->cost) {
                        break;
                    }
                    priorityQueue[j + 1] = priorityQueue[j];
                }
                priorityQueue[j + 1] = successors[i];
                rear++;
            }
        }
    }

    printf("Puzzle cannot be solved\n");
}

// Function to print the solution path
void printSolutionPath(struct State* state) {
    if (state == NULL) {
        return;
    }

    printSolutionPath(state->parent);
    printf("Move %d:\n", state->move);
    printPuzzle(state->puzzle);
}

int main() {
    int initial[N][N] = {{1, 3, 2}, {8, 0, 4}, {7, 6, 5}};
    int goal[N][N] = {{1, 3, 2}, {0, 8, 4}, {7, 6, 5}};  // Change the goal state here

    solvePuzzle(initial, goal);

    return 0;
}
