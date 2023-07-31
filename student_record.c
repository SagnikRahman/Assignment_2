#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defining a structure for the Student record
struct Student {
    char name[100];
    int rollNumber;
    float marks;
    struct Student* next;
};

// Global pointer variable to keep track of the head of the linked list
struct Student* head = NULL;

// Function to add a new student record to the linked list
void addStudent(char name[], int rollNumber, float marks) {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    strcpy(newStudent->name, name);
    newStudent->rollNumber = rollNumber;
    newStudent->marks = marks;
    newStudent->next = NULL;

    if (head == NULL) {
        head = newStudent;
        return;
    }
    struct Student* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newStudent;
}

// Function to delete a student record with the given roll number from the linked list
void deleteStudent(int rollNumber) {
    if (head == NULL) {
        printf("The student record list is empty.\n");
        return;
    }
    if (head->rollNumber == rollNumber) {
        struct Student* temp = head;
        head = head->next;
        free(temp);
        return;
    }
    struct Student* current = head;
    struct Student* prev = NULL;
    while (current != NULL && current->rollNumber != rollNumber) {
        prev = current;
        current = current->next;
    }
    if (current != NULL) {
        prev->next = current->next;
        free(current);
    } else {
        printf("Student record with roll number %d not found.\n", rollNumber);
    }
}

// Function to display the details of all students in the linked list
void displayStudents() {
    if (head == NULL) {
        printf("The student record list is empty.\n");
        return;
    }
    struct Student* current = head;
    printf("Student Record List:\n");
    while (current != NULL) {
        printf("Name: %s | Roll Number: %d | Marks: %.2f\n", current->name, current->rollNumber, current->marks);
        current = current->next;
    }
}

// Function to search for a student record with the given roll number in the linked list and return its position (index)
int searchStudent(int rollNumber) {
    if (head == NULL) {
        return -1;
    }
    struct Student* current = head;
    int index = 0;
    while (current != NULL) {
        if (current->rollNumber == rollNumber) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

int main() {
    int choice, rollNumber;
    char name[100];
    float marks;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Add a student record\n");
        printf("2. Delete a student record\n");
        printf("3. Display all student records\n");
        printf("4. Search for a student record\n");
        printf("5. Exit the program\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter the name of the student: ");
                getchar(); // Consume the newline character left in the input buffer
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0'; // Remove the trailing newline from fgets
                printf("Enter the roll number of the student: ");
                scanf("%d", &rollNumber);
                printf("Enter the marks of the student: ");
                scanf("%f", &marks);
                addStudent(name, rollNumber, marks);
                break;
            case 2:
                printf("Enter the roll number of the student to delete: ");
                scanf("%d", &rollNumber);
                deleteStudent(rollNumber);
                break;
            case 3:
                displayStudents();
                break;
            case 4:
                printf("Enter the roll number of the student to search: ");
                scanf("%d", &rollNumber);
                int position = searchStudent(rollNumber);
                if (position != -1) {
                    printf("Student record with roll number %d found at position %d in the list.\n", rollNumber, position);
                } else {
                    printf("Student record with roll number %d not found in the list.\n", rollNumber);
                }
                break;
            case 5:
                printf("Exiting the program.\n");
                // Freeing memory for the entire linked list
                struct Student* current = head;
                struct Student* next;
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
