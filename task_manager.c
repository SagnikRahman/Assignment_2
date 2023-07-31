#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for the Task
struct Task {
    int taskId;
    char description[100];
    int priority;
    struct Task* next;
};

// Function to add a new task to the task manager
void addTask(struct Task** head, int taskId, char description[], int priority) {
    struct Task* newTask = (struct Task*)malloc(sizeof(struct Task));
    newTask->taskId = taskId;
    strcpy(newTask->description, description);
    newTask->priority = priority;
    newTask->next = NULL;
    if (*head == NULL) {
        *head = newTask;
        return;
    }

    struct Task* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newTask;
}

// Function to delete a task with the given task ID from the task manager
void deleteTask(struct Task** head, int taskId) {
    if (*head == NULL) {
        printf("The task manager is empty.\n");
        return;
    }

    if ((*head)->taskId == taskId) {
        struct Task* temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }

    struct Task* current = *head;
    struct Task* prev = NULL;
    while (current != NULL && current->taskId != taskId) {
        prev = current;
        current = current->next;
    }
    if (current != NULL) {
        prev->next = current->next;
        free(current);
    } else {
        printf("Task with ID %d not found in the task manager.\n", taskId);
    }
}

// Function to display the details of all tasks in the task manager
void displayTasks(struct Task* head) {
    if (head == NULL) {
        printf("The task manager is empty.\n");
        return;
    }
    struct Task* current = head;
    printf("Task Manager:\n");
    while (current != NULL) {
        printf("Task ID: %d | Description: %s | Priority: %d\n", current->taskId, current->description, current->priority);
        current = current->next;
    }
}

// Function to swap the positions of two tasks
void swapTasks(struct Task* a, struct Task* b) {
    int tempId = a->taskId;
    char tempDesc[100];
    int tempPriority = a->priority;
    strcpy(tempDesc, a->description);

    a->taskId = b->taskId;
    a->priority = b->priority;
    strcpy(a->description, b->description);

    b->taskId = tempId;
    b->priority = tempPriority;
    strcpy(b->description, tempDesc);
}

// Function to prioritize the tasks based on their priority using Bubble Sort
void prioritizeTasks(struct Task* head) {
    if (head == NULL) {
        printf("The task manager is empty.\n");
        return;
    }
    int swapped;
    struct Task* current;
    struct Task* last = NULL;
    do {
        swapped = 0;
        current = head;

        while (current->next != last) {
            if (current->priority < current->next->priority) {
                swapTasks(current, current->next);
                swapped = 1;
            }
            current = current->next;
        }
        last = current;
    } while (swapped);
}

// Function to search for a task with the given task ID in the task manager and return its position (index)
int searchTask(struct Task* head, int taskId) {
    if (head == NULL) {
        return -1;
    }
    struct Task* current = head;
    int index = 0;
    while (current != NULL) {
        if (current->taskId == taskId) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

int main() {
    int choice, taskId, priority;
    char description[100];
    struct Task* head = NULL;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Add a task\n");
        printf("2. Delete a task\n");
        printf("3. Display all tasks\n");
        printf("4. Prioritize tasks\n");
        printf("5. Search for a task\n");
        printf("6. Exit the program\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the task ID: ");
                scanf("%d", &taskId);
                printf("Enter the task description: ");
                getchar(); // Consume the newline character left in the input buffer
                fgets(description, sizeof(description), stdin);
                description[strcspn(description, "\n")] = '\0'; // Remove the trailing newline from fgets
                printf("Enter the priority of the task: ");
                scanf("%d", &priority);
                addTask(&head, taskId, description, priority);
                break;
            case 2:
                printf("Enter the task ID to delete: ");
                scanf("%d", &taskId);
                deleteTask(&head, taskId);
                break;
            case 3:
                displayTasks(head);
                break;
            case 4:
                prioritizeTasks(head);
                printf("Tasks prioritized based on their priority.\n");
                break;
            case 5:
                printf("Enter the task ID to search: ");
                scanf("%d", &taskId);
                int position = searchTask(head, taskId);
                if (position != -1) {
                    printf("Task with ID %d found at position %d in the task manager.\n", taskId, position);
                } else {
                    printf("Task with ID %d not found in the task manager.\n", taskId);
                }
                break;
            case 6:
                printf("Exiting the program.\n");
                // Freeing memory for the entire linked list
                struct Task* current = head;
                struct Task* next;
                while (current != NULL) {
                    next = current->next;
                    free(current);
                    current = next;
                }
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
