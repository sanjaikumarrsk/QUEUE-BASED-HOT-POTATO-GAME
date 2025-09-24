#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a player
typedef struct Node {
    char name[50];
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(const char* name) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    strcpy(newNode->name, name);
    newNode->next = NULL;
    return newNode;
}

// Function to enqueue a player (add to the queue)
void enqueue(Node** rear, const char* name) {
    Node* newNode = createNode(name);
    if (*rear == NULL) {
        *rear = newNode;
        newNode->next = newNode; // Circular link
    } else {
        newNode->next = (*rear)->next;
        (*rear)->next = newNode;
        *rear = newNode;
    }
    printf("%s has joined the game.\n", name);
}

// Function to dequeue a player (remove from the queue)
char* dequeue(Node** rear) {
    if (*rear == NULL) {
        return NULL; // Empty queue
    }
    Node* front = (*rear)->next;
    char* name = (char*)malloc(50 * sizeof(char));
    strcpy(name, front->name);

    if (front == *rear) { 
        // Only one node
        *rear = NULL;
    } else {
        (*rear)->next = front->next;
    }
    free(front);
    return name;
}

// Function to display players in the queue
void display(Node* rear) {
    if (rear == NULL) {
        printf("No players in the game.\n");
        return;
    }
    Node* temp = rear->next;
    printf("Players in game: ");
    do {
        printf("%s ", temp->name);
        temp = temp->next;
    } while (temp != rear->next);
    printf("\n");
}

// Function to play Hot Potato
void hotPotato(Node** rear, int passes) {
    if (*rear == NULL || (*rear)->next == *rear) {
        printf("Not enough players to play!\n");
        return;
    }
    while ((*rear)->next != *rear) { // Until one remains
        for (int i = 0; i < passes; i++) {
            *rear = (*rear)->next; // Move potato
        }
        char* eliminated = dequeue(rear);
        printf("%s is eliminated!\n", eliminated);
        free(eliminated);
        display(*rear);
    }
    printf("\nWinner is: %s 🎉\n", (*rear)->name);
}

int main() {
    Node* rear = NULL;
    int choice, passes;
    char name[50];

    do {
        printf("\n--- Queue Based Hot Potato Game ---\n");
        printf("1. Add Player\n");
        printf("2. Display Players\n");
        printf("3. Start Game\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter player name: ");
                scanf("%s", name);
                enqueue(&rear, name);
                break;
            case 2:
                display(rear);
                break;
            case 3:
                printf("Enter number of passes before elimination: ");
                scanf("%d", &passes);
                hotPotato(&rear, passes);
                break;
            case 4:
                printf("Exiting game...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 4);

    return 0;
}
