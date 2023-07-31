#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defining a structure for the Song
struct Song 
{
    char title[100];
    char artist[100];
    struct Song* next;
};

// Function to add a new song to the playlist
void addSong(struct Song** head, char title[], char artist[]) 
{
    struct Song* newSong = (struct Song*)malloc(sizeof(struct Song));
    strcpy(newSong->title, title);
    strcpy(newSong->artist, artist);
    newSong->next = NULL;
    if (*head == NULL) 
    {
        *head = newSong;
        return;
    }
    struct Song* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newSong;
}

// Function to delete a song with the given title from the playlist
void deleteSong(struct Song** head, char title[]) {
    if (*head == NULL) {
        printf("The playlist is empty.\n");
        return;
    }

    if (strcmp((*head)->title, title) == 0) {
        struct Song* temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }

    struct Song* current = *head;
    struct Song* prev = NULL;
    while (current != NULL && strcmp(current->title, title) != 0) {
        prev = current;
        current = current->next;
    }

    if (current != NULL) {
        prev->next = current->next;
        free(current);
    } else {
        printf("Song with title \"%s\" not found in the playlist.\n", title);
    }
}

// Function to display the details of all songs in the playlist
void displayPlaylist(struct Song* head) {
    if (head == NULL) {
        printf("The playlist is empty.\n");
        return;
    }

    struct Song* current = head;
    printf("Playlist:\n");
    while (current != NULL) {
        printf("Title: %s | Artist: %s\n", current->title, current->artist);
        current = current->next;
    }
}

// Function to simulate playing the songs in the playlist sequentially
void playPlaylist(struct Song* head) {
    if (head == NULL) {
        printf("The playlist is empty.\n");
        return;
    }

    struct Song* current = head;
    printf("Playing Playlist:\n");
    while (current != NULL) {
        printf("Playing \"%s\" by %s\n", current->title, current->artist);
        current = current->next;
    }
}

// Function to search for a song with the given title in the playlist and return its position (index)
int searchSong(struct Song* head, char title[]) {
    if (head == NULL) {
        return -1;
    }

    struct Song* current = head;
    int index = 0;
    while (current != NULL) {
        if (strcmp(current->title, title) == 0) {
            return index;
        }
        current = current->next;
        index++;
    }

    return -1;
}

int main() {
    int choice;
    char title[100], artist[100];

    struct Song* head = NULL;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add a song to the playlist\n");
        printf("2. Delete a song from the playlist\n");
        printf("3. Display the playlist\n");
        printf("4. Play the playlist\n");
        printf("5. Search for a song\n");
        printf("6. Exit the program\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the title of the song: ");
                getchar(); // Consume the newline character left in the input buffer
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = '\0'; // Remove the trailing newline from fgets
                printf("Enter the artist name: ");
                fgets(artist, sizeof(artist), stdin);
                artist[strcspn(artist, "\n")] = '\0'; // Remove the trailing newline from fgets
                addSong(&head, title, artist);
                break;
            case 2:
                printf("Enter the title of the song to delete: ");
                getchar();
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = '\0';
                deleteSong(&head, title);
                break;
            case 3:
                displayPlaylist(head);
                break;
            case 4:
                playPlaylist(head);
                break;
            case 5:
                printf("Enter the title of the song to search: ");
                getchar();
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = '\0';
                int position = searchSong(head, title);
                if (position != -1) {
                    printf("Song \"%s\" found at position %d in the playlist.\n", title, position);
                } else {
                    printf("Song \"%s\" not found in the playlist.\n", title);
                }
                break;
            case 6:
                printf("Exiting the program.\n");
                // Free memory for the entire linked list before exiting
                struct Song* current = head;
                struct Song* next;
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
