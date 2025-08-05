#include <stdio.h>
#include <stdlib.h>
#define SIZE 5

typedef struct {
    int arr[SIZE];
    int front, rear, count;
} Deque;

void init(Deque* d) {
    d->front = -1;
    d->rear = 0;
    d->count = 0;
}

int isFull(Deque* d) {
    return d->count == SIZE;
}

int isEmpty(Deque* d) {
    return d->count == 0;
}

void insertFront(Deque* d, int val) {
    if (isFull(d)) {
        printf("Deque is full\n");
        return;
    }
    if (d->front == -1) {
        d->front = d->rear = 0;
    } else {
        d->front = (d->front - 1 + SIZE) % SIZE;
    }
    d->arr[d->front] = val;
    d->count++;
    printf("Inserted %d at front\n", val);
}

void insertRear(Deque* d, int val) {
    if (isFull(d)) {
        printf("Deque is full\n");
        return;
    }
    if (d->front == -1) {
        d->front = d->rear = 0;
    } else {
        d->rear = (d->rear + 1) % SIZE;
    }
    d->arr[d->rear] = val;
    d->count++;
    printf("Inserted %d at rear\n", val);
}

void deleteFront(Deque* d) {
    if (isEmpty(d)) {
        printf("Deque is empty\n");
        return;
    }
    printf("Deleted %d from front\n", d->arr[d->front]);
    if (d->front == d->rear) {
        d->front = -1;
        d->rear = 0;
    } else {
        d->front = (d->front + 1) % SIZE;
    }
    d->count--;
}

void deleteRear(Deque* d) {
    if (isEmpty(d)) {
        printf("Deque is empty\n");
        return;
    }
    printf("Deleted %d from rear\n", d->arr[d->rear]);
    if (d->front == d->rear) {
        d->front = -1;
        d->rear = 0;
    } else {
        d->rear = (d->rear - 1 + SIZE) % SIZE;
    }
    d->count--;
}

void display(Deque* d) {
    if (isEmpty(d)) {
        printf("Deque is empty\n");
        return;
    }
    int i = d->front;
    printf("Deque: ");
    for (int c = 0; c < d->count; c++) {
        printf("%d ", d->arr[i]);
        i = (i + 1) % SIZE;
    }
    printf("\n");
}

int main() {
    Deque d;
    init(&d);

    int choice, val;
    while (1) {
        printf("\n1.Insert Front 2.Insert Rear 3.Delete Front 4.Delete Rear 5.Display 6.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Value: "); scanf("%d", &val);
                insertFront(&d, val); break;
            case 2:
                printf("Value: "); scanf("%d", &val);
                insertRear(&d, val); break;
            case 3:
                deleteFront(&d); break;
            case 4:
                deleteRear(&d); break;
            case 5:
                display(&d); break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}
