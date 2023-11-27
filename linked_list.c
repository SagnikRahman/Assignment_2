#include <stdio.h>
#include <stdlib.h>
// Defining a structure named Node
struct Node 
{
    int data;
    struct Node* next;
};
//to insert at beginning
void insertAtBeginning(int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = head;
    head = newNode;
}
// Declaring the global pointer variable head
struct Node* head = NULL;

// Function to insert a new node at the end of the linked list
void insertNode(int val) 
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->next = NULL;

    if (head == NULL) 
    {
        head = newNode;
        return;
    }

    // Traversing to the last node and inserting the new node at the end
    struct Node* current = head;
    while (current->next != NULL) 
    {
        current = current->next;
    }
    current->next = newNode;
}

// Function to delete a node with the given value from the linked list
void deleteNode(int val) 
{
    // If the list is empty, nothing to delete
    if (head == NULL) 
    {
        printf("The list is empty.\n");
        return;
    }

    // If the head node itself contains the value to be deleted
    if (head->data == val) 
    {
        struct Node* temp = head;
        head = head->next;
        free(temp);
        return;
    }

    // Traversing the list to find the node to be deleted and its previous node
    struct Node* current = head;
    struct Node* prev = NULL;
    while (current != NULL && current->data != val) 
    {
        prev = current;
        current = current->next;
    }

    // If the node with the given value is found, deletion is done
    if (current != NULL) 
    {
        prev->next = current->next;
        free(current);
    } else {
        printf("Node with value %d not found in the list.\n", val);
    }
}

// Function to display the elements of the linked list
void displayList() {
    // If the list is empty, nothing to display
    if (head == NULL) 
    {
        printf("List is empty.\n");
        return;
    }

    // Traversing the list and printing each element
    struct Node* current = head;
    printf("Linked List: ");
    while (current != NULL) 
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Function to reverse the order of the nodes in the linked list
void reverseList() {
    struct Node* prev = NULL;
    struct Node* current = head;
    struct Node* next = NULL;

    while (current != NULL) 
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    head = prev;
}

// Function to search for a node with the given value in the linked list and return its position
int searchNode(int value) {
    // If the list is empty, return -1
    if (head == NULL) {
        return -1;
    }

    // Traversing the list to find the node with the given value
    struct Node* current = head;
    int index = 0;
    while (current != NULL) {
        if (current->data == value) {
            return index;
        }
        current = current->next;
        index++;
    }

    // Node with the given value not found
    return -1;
}

int main() {
    int choice, val;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert a node at the end of the list\n");
        printf("2. Delete a node by value\n");
        printf("3. Display the list\n");
        printf("4. Reverse the list\n");
        printf("5. Search for a node\n");
        printf("6. Exit the program\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) 
        {
            case 1:
                printf("Enter the value to insert: ");
                scanf("%d", &val);
                insertNode(val);
                break;
            case 2:
                printf("Enter the value to delete: ");
                scanf("%d", &val);
                deleteNode(val);
                break;
            case 3:
                displayList();
                break;
            case 4:
                reverseList();
                printf("List reversed.\n");
                break;
            case 5:
                printf("Enter the value to search: ");
                scanf("%d", &val);
                int pos = searchNode(val);
                if (pos != -1) {
                    printf("Node with value %d found at position %d.\n", val, pos);
                } else {
                    printf("Node with value %d not found in the list.\n", val);
                }
                break;
            case 6:
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
