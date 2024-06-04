#include <stdio.h>
#include <stdbool.h>

typedef struct State {
    int jugA;
    int jugB;
} State;

typedef struct Node {
    State state;
    struct Node* parent;
} Node;

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

void printPath(Node* node) {
    if (node == NULL) {
        return;
    }
    printPath(node->parent);
    printf("(%d, %d)\n", node->state.jugA, node->state.jugB);
}

void bfs(State initialState, int jugACapacity, int jugBCapacity, int target) {
    Node* queue[1000];
    int front = 0, rear = 0;

    State visited[100];
    int visitedSize = 0;

    Node* root = (Node*)malloc(sizeof(Node));
    root->state = initialState;
    root->parent = NULL;

    queue[rear++] = root;

    while (front < rear) {
        Node* currentNode = queue[front++];
        State currentState = currentNode->state;

        if (isGoalState(currentState, target)) {
            printf("Solution Found:\n");
            printPath(currentNode);
            return;
        }

        visited[visitedSize++] = currentState;

        // Fill jug A
        if (currentState.jugA < jugACapacity) {
            State newState = {jugACapacity, currentState.jugB};
            if (!isVisited(newState, visited, visitedSize)) {
                Node* newNode = (Node*)malloc(sizeof(Node));
                newNode->state = newState;
                newNode->parent = currentNode;
                queue[rear++] = newNode;
            }
        }

        // Fill jug B
        if (currentState.jugB < jugBCapacity) {
            State newState = {currentState.jugA, jugBCapacity};
            if (!isVisited(newState, visited, visitedSize)) {
                Node* newNode = (Node*)malloc(sizeof(Node));
                newNode->state = newState;
                newNode->parent = currentNode;
                queue[rear++] = newNode;
            }
        }

        // Empty jug A
        if (currentState.jugA > 0) {
            State newState = {0, currentState.jugB};
            if (!isVisited(newState, visited, visitedSize)) {
                Node* newNode = (Node*)malloc(sizeof(Node));
                newNode->state = newState;
                newNode->parent = currentNode;
                queue[rear++] = newNode;
            }
        }

        // Empty jug B
        if (currentState.jugB > 0) {
            State newState = {currentState.jugA, 0};
            if (!isVisited(newState, visited, visitedSize)) {
                Node* newNode = (Node*)malloc(sizeof(Node));
                newNode->state = newState;
                newNode->parent = currentNode;
                queue[rear++] = newNode;
            }
        }

        // Pour water from jug A to jug B
        if (currentState.jugA > 0 && currentState.jugB < jugBCapacity) {
            int pourAmount = (currentState.jugA < jugBCapacity - currentState.jugB) ? currentState.jugA : (jugBCapacity - currentState.jugB);
            State newState = {currentState.jugA - pourAmount, currentState.jugB + pourAmount};
            if (!isVisited(newState, visited, visitedSize)) {
                Node* newNode = (Node*)malloc(sizeof(Node));
                newNode->state = newState;
                newNode->parent = currentNode;
                queue[rear++] = newNode;
            }
        }

        // Pour water from jug B to jug A
        if (currentState.jugB > 0 && currentState.jugA < jugACapacity) {
            int pourAmount = (currentState.jugB < jugACapacity - currentState.jugA) ? currentState.jugB : (jugACapacity - currentState.jugA);
            State newState = {currentState.jugA + pourAmount, currentState.jugB - pourAmount};
            if (!isVisited(newState, visited, visitedSize)) {
                Node* newNode = (Node*)malloc(sizeof(Node));
                newNode->state = newState;
                newNode->parent = currentNode;
                queue[rear++] = newNode;
            }
        }
    }

    printf("Solution not found.\n");
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

    printf("BFS steps:\n");
    bfs(initialState, jugACapacity, jugBCapacity, target);

    return 0;
}
