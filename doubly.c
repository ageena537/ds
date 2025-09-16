#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char url[100];
    struct node* next;
    struct node* previous;
};

struct node* current = NULL;

void visitpage(const char* newurl) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    if (newnode == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    strcpy(newnode->url, newurl);
    newnode->next = NULL;
    newnode->previous = current;

    if (current != NULL) {
        current->next = newnode;
    }
    current = newnode;

    printf("Visited URL is: %s\n", current->url);
}

void goback() {
    if (current == NULL || current->previous == NULL) {
        printf("Cannot go back\n");
    } else {
        current = current->previous;
        printf("Moved back to URL: %s\n", current->url);
    }
}

void goforward() {
    if (current == NULL || current->next == NULL) {
        printf("Cannot go forward\n");
    } else {
        current = current->next;
        printf("Moved forward to URL: %s\n", current->url);
    }
}

void showcurrentpage() {
    if (current == NULL) {
        printf("No page visited\n");
    } else {
        printf("Current page is: %s\n", current->url);
    }
}

int main() {
    char url[100];
    int choice = 0;

    while (choice != 5) {
        printf("\n Menu\n");
        printf("1. Visit new page\n");
        printf("2. Go back\n");
        printf("3. Go forward\n");
        printf("4. Display current page\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter URL: ");
                scanf("%s", url);
                visitpage(url);
                break;
            case 2:
                goback();
                break;
            case 3:
                goforward();
                break;
            case 4:
                showcurrentpage();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
 
