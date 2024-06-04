#include <stdio.h>
#include <stdbool.h>

typedef struct State {
    int jugA;
    int jugB;
} State;

bool isGoalState(State state, int target) {
    return state.jugA == target || state.jugB == target;
}

bool isVisited(State state, State visited[], int visitedSize) {
    for (int i = 0; i < visitedSize; i++) {
        if (visited[i].jugA == state.jugA && visited[i].jugB == state.jugB) {
            return true;
        }
    }
    return false;
}

void printPath(State visited[], int visitedSize) {
    printf("Path to goal:\n");
    for (int i = 0; i < visitedSize; i++) {
        printf("(%d, %d)\n", visited[i].jugA, visited[i].jugB);
    }
}

void dfs(State currentState, int jugACapacity, int jugBCapacity, int target, State visited[], int *visitedSize) {
    if (isVisited(currentState, visited, *visitedSize) || *visitedSize > 50) {
        return;
    }

    visited[*visitedSize] = currentState;
    (*visitedSize)++;

    if (isGoalState(currentState, target)) {
        printPath(visited, *visitedSize);
        return;
    }

    // Fill jug A
    if (currentState.jugA < jugACapacity) {
        State newState = {jugACapacity, currentState.jugB};
        dfs(newState, jugACapacity, jugBCapacity, target, visited, visitedSize);
    }

    // Fill jug B
    if (currentState.jugB < jugBCapacity) {
        State newState = {currentState.jugA, jugBCapacity};
        dfs(newState, jugACapacity, jugBCapacity, target, visited, visitedSize);
    }

    // Empty jug A
    if (currentState.jugA > 0) {
        State newState = {0, currentState.jugB};
        dfs(newState, jugACapacity, jugBCapacity, target, visited, visitedSize);
    }

    // Empty jug B
    if (currentState.jugB > 0) {
        State newState = {currentState.jugA, 0};
        dfs(newState, jugACapacity, jugBCapacity, target, visited, visitedSize);
    }

    // Pour water from jug A to jug B
    if (currentState.jugA > 0 && currentState.jugB < jugBCapacity) {
        int pourAmount = (currentState.jugA < jugBCapacity - currentState.jugB) ? currentState.jugA : (jugBCapacity - currentState.jugB);
        State newState = {currentState.jugA - pourAmount, currentState.jugB + pourAmount};
        dfs(newState, jugACapacity, jugBCapacity, target, visited, visitedSize);
    }

    // Pour water from jug B to jug A
    if (currentState.jugB > 0 && currentState.jugA < jugACapacity) {
        int pourAmount = (currentState.jugB < jugACapacity - currentState.jugA) ? currentState.jugB : (jugACapacity - currentState.jugA);
        State newState = {currentState.jugA + pourAmount, currentState.jugB - pourAmount};
        dfs(newState, jugACapacity, jugBCapacity, target, visited, visitedSize);
    }

    (*visitedSize)--;
}

int main() {
    int jugACapacity, jugBCapacity, target;
    printf("Enter the capacity of jug A: ");
    scanf("%d", &jugACapacity);
    printf("Enter the capacity of jug B: ");
    scanf("%d", &jugBCapacity);
    printf("Enter the target volume: ");
    scanf("%d", &target);

    State initialState = {0, 0}; // Initial state of both jugs
    State visited[100]; // Array to store visited states
    int visitedSize = 0;

    printf("DFS steps:\n");
    dfs(initialState, jugACapacity, jugBCapacity, target, visited, &visitedSize);

    return 0;
}
