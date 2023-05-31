#include <stdio.h>
#include <stdlib.h>

struct Node {
    int start;
    int length;
    struct Node* next;
};

void allocateFile(struct Node** head, int start, int length) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->start = start;
    newNode->length = length;
    newNode->next = NULL;
    
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

int isFileAllocated(struct Node* head, int start, int length) {
    struct Node* current = head;
    while (current != NULL) {
        if (current->start == start && current->length == length) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void displayFiles(struct Node* head) {
    if (head == NULL) {
        printf("No files allocated.\n");
    } else {
        printf("Files Allocated are:\n");
        struct Node* current = head;
        while (current != NULL) {
            printf("Start: %d\tLength: %d\n", current->start, current->length);
            current = current->next;
        }
    }
}

int main() {
    struct Node* head = NULL;
    int st, len, c;
    
    do {
        printf("Enter starting block and length of file: ");
        scanf("%d %d", &st, &len);
        
        if (isFileAllocated(head, st, len)) {
            printf("The file is already allocated.\n");
        } else {
            allocateFile(&head, st, len);
            printf("The file is allocated to disk.\n");
        }
        
        printf("Do you want to enter more files? (Yes - 1/No - 0): ");
        scanf("%d", &c);
    } while (c == 1);
    
    displayFiles(head);
    
    return 0;
}
