#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Linked List structure for Inventory
typedef struct Item {
    char name[30];
    struct Item* next;
} Item;

// Stack Node for Conversation Choices
typedef struct StackNode {
    char choice[100];
    struct StackNode* next;
} StackNode;

// Queue Node for Tasks
typedef struct Task {
    char description[100];
    struct Task* next;
} Task;

// Tree Node for Character Dialogues
typedef struct CharacterNode {
    char name[30];
    char dialogue[100];
    struct CharacterNode* left;  // For Yes choices
    struct CharacterNode* right; // For No choices
} CharacterNode;

// Function Prototypes
void pushChoice(StackNode** top, char* choice);
void popChoice(StackNode** top);
void displayChoices(StackNode* top);
void addTask(Task** front, Task** rear, char* description);
void completeTask(Task** front, Task** rear);
void displayTasks(Task* front);
Item* addItem(Item* head, char* name);
void showInventory(Item* head);
CharacterNode* createCharacterNode(char* name, char* dialogue);
void navigateDialogue(CharacterNode* root);
void freeInventory(Item* head);
void freeTasks(Task* front);
void freeChoices(StackNode* top);
void freeDialogue(CharacterNode* root);

// Main Game Code
int main() {
    // Initialize Data Structures
    Item* inventory = NULL;
    Task* taskFront = NULL;
    Task* taskRear = NULL;
    StackNode* choiceStack = NULL;

    // Add initial tasks
    addTask(&taskFront, &taskRear, "Complete the sales report");
    addTask(&taskFront, &taskRear, "Check with Jim about the prank");
    
    // Set up Character Dialogue Tree
    CharacterNode* michael = createCharacterNode("Michael", "Do you want to join our team meeting?");
    michael->left = createCharacterNode("Michael - Yes", "Great! Let's discuss new ideas.");
    michael->right = createCharacterNode("Michael - No", "Well, you miss 100% of the meetings you don't attend.");
    
    printf("Welcome to The Office Game!\n");

    // Main Menu Loop
    while (1) {
        int choice;
        printf("\nWhat would you like to do?\n");
        printf("1. Navigate Michael's Dialogue\n");
        printf("2. Check Tasks Queue\n");
        printf("3. Check Inventory\n");
        printf("4. View Choices Stack\n");
        printf("5. Add Item to Inventory\n");
        printf("6. Complete a Task\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline

        if (choice == 1) {
            navigateDialogue(michael);
        } else if (choice == 2) {
            displayTasks(taskFront);
        } else if (choice == 3) {
            showInventory(inventory);
        } else if (choice == 4) {
            displayChoices(choiceStack);
        } else if (choice == 5) {
            char itemName[30];
            printf("Enter the item name to add: ");
            fgets(itemName, sizeof(itemName), stdin);
            itemName[strcspn(itemName, "\n")] = 0; // Remove newline
            inventory = addItem(inventory, itemName);
        } else if (choice == 6) {
            completeTask(&taskFront, &taskRear);
        } else if (choice == 7) {
            break;
        } else {
            printf("Invalid choice! Please try again.\n");
        }
    }

    // Free allocated memory
    freeInventory(inventory);
    freeTasks(taskFront);
    freeDialogue(michael);
    freeChoices(choiceStack);

    printf("Thank you for playing The Office Game!\n");
    return 0;
}

// Stack Operations
void pushChoice(StackNode** top, char* choice) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    strcpy(newNode->choice, choice);
    newNode->next = *top;
    *top = newNode;
}

void popChoice(StackNode** top) {
    if (*top == NULL) return;
    StackNode* temp = *top;
    *top = (*top)->next;
    free(temp);
}

void displayChoices(StackNode* top) {
    printf("Choices Stack:\n");
    while (top != NULL) {
        printf("- %s\n", top->choice);
        top = top->next;
    }
}

// Queue Operations
void addTask(Task** front, Task** rear, char* description) {
    Task* newTask = (Task*)malloc(sizeof(Task));
    strcpy(newTask->description, description);
    newTask->next = NULL;
    if (*rear == NULL) {
        *front = *rear = newTask;
    } else {
        (*rear)->next = newTask;
        *rear = newTask;
    }
}

void completeTask(Task** front, Task** rear) {
    if (*front == NULL) {
        printf("No tasks to complete.\n");
        return;
    }
    Task* temp = *front;
    *front = (*front)->next;
    if (*front == NULL) *rear = NULL;
    printf("Completed task: %s\n", temp->description);
    free(temp);
}

void displayTasks(Task* front) {
    printf("Tasks Queue:\n");
    while (front != NULL) {
        printf("- %s\n", front->description);
        front = front->next;
    }
}

// Linked List Operations for Inventory
Item* addItem(Item* head, char* name) {
    Item* newItem = (Item*)malloc(sizeof(Item));
    strcpy(newItem->name, name);
    newItem->next = head;
    return newItem;
}

void showInventory(Item* head) {
    printf("Inventory:\n");
    if (head == NULL) {
        printf("- Empty\n");
        return;
    }
    while (head != NULL) {
        printf("- %s\n", head->name);
        head = head->next;
    }
}

// Tree Operations for Dialogue
CharacterNode* createCharacterNode(char* name, char* dialogue) {
    CharacterNode* newNode = (CharacterNode*)malloc(sizeof(CharacterNode));
    strcpy(newNode->name, name);
    strcpy(newNode->dialogue, dialogue);
    newNode->left = newNode->right = NULL;
    return newNode;
}

void navigateDialogue(CharacterNode* root) {
    CharacterNode* current = root;
    while (current != NULL) {
        printf("%s says: \"%s\"\n", current->name, current->dialogue);
        printf("Choose (1) Yes or (2) No: ");
        int choice;
        scanf("%d", &choice);
        if (choice == 1) current = current->left;
        else if (choice == 2) current = current->right;
        else {
            printf("Invalid choice.\n");
            return;
        }
    }
    printf("Dialogue ended.\n");
}

// Free Functions
void freeInventory(Item* head) {
    while (head != NULL) {
        Item* temp = head;
        head = head->next;
        free(temp);
    }
}

void freeTasks(Task* front) {
    while (front != NULL) {
        Task* temp = front;
        front = front->next;
        free(temp);
    }
}

void freeChoices(StackNode* top) {
    while (top != NULL) {
        StackNode* temp = top;
        top = top->next;
        free(temp);
    }
}

void freeDialogue(CharacterNode* root) {
    if (root == NULL) return;
    freeDialogue(root->left);
    freeDialogue(root->right);
    free(root);
}



