#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_RESERVATIONS 100

typedef struct {
    char name[50];
    int partySize;
    char time[10];
} Reservation;

Reservation queue[MAX_RESERVATIONS];
int front = 0;
int rear = -1;
int itemCount = 0;

bool isQueueEmpty() {
    return itemCount == 0;
}

bool isQueueFull() {
    return itemCount == MAX_RESERVATIONS;
}

void enqueue(Reservation reservation) {
    if (!isQueueFull()) {
        if (rear == MAX_RESERVATIONS - 1) {
            rear = -1;
        }
        queue[++rear] = reservation;
        itemCount++;
        printf("Reservation for %s (Party Size: %d, Time: %s) added successfully.\n", reservation.name, reservation.partySize, reservation.time);
    } else {
        printf("Reservation queue is full. Cannot add more reservations.\n");
    }
}

void dequeue() {
    if (!isQueueEmpty()) {
        Reservation servedReservation = queue[front++];
        if (front == MAX_RESERVATIONS) {
            front = 0;
        }
        itemCount--;
        printf("Reservation for %s (Party Size: %d, Time: %s) has been served and removed.\n", servedReservation.name, servedReservation.partySize, servedReservation.time);
    } else {
        printf("Reservation queue is empty. No reservations to serve.\n");
    }
}

void displayReservations() {
    if (isQueueEmpty()) {
        printf("No reservations in the queue.\n");
    } else {
        int i = front;
        int count = 0;
        printf("Reservations:\n");
        while (count < itemCount) {
            printf("Index %d - Name: %s, Party Size: %d, Time: %s\n", count, queue[i].name, queue[i].partySize, queue[i].time);
            i = (i + 1) % MAX_RESERVATIONS;
            count++;
        }
    }
}

void cancelReservation(char *name) {
    if (isQueueEmpty()) {
        printf("Reservation queue is empty. No reservations to cancel.\n");
    } else {
        int i = front;
        int count = 0;
        int found = 0;

        while (count < itemCount) {
            if (strcmp(queue[i].name, name) == 0) {
                // Reservation found; remove it
                printf("Reservation for %s (Party Size: %d, Time: %s) has been canceled and removed.\n", queue[i].name, queue[i].partySize, queue[i].time);

                // Shift elements to cover the gap
                for (int j = i; j < rear; j++) {
                    queue[j] = queue[(j + 1) % MAX_RESERVATIONS];
                }

                if (rear == 0) {
                    // If the last reservation was removed, update rear
                    rear = MAX_RESERVATIONS - 1;
                } else {
                    rear = (rear - 1 + MAX_RESERVATIONS) % MAX_RESERVATIONS;
                }

                itemCount--;
                found = 1;
                break;
            }

            i = (i + 1) % MAX_RESERVATIONS;
            count++;
        }

        if (!found) {
            printf("Reservation for %s not found in the queue.\n", name);
        }
    }
}

int main() {
    int choice;

    printf("Welcome to the Restaurant Reservation System (Queue-based)\n");

    do {
        printf("\nMain Menu:\n");
        printf("1. Make a reservation\n");
        printf("2. Serve the next reservation\n");
        printf("3. Display reservations\n");
        printf("4. Cancel a reservation\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char name[50];
                int partySize;
                char time[10];

                printf("\nMake a Reservation:\n");
                printf("Enter customer name: ");
                scanf("%s", name);
                printf("Enter party size: ");
                scanf("%d", &partySize);
                printf("Enter reservation time (HH:MM AM/PM): ");
                scanf("%s", time);

                Reservation reservation;
                strcpy(reservation.name, name);
                reservation.partySize = partySize;
                strcpy(reservation.time, time);
                enqueue(reservation);
                break;
            }
            case 2: {
                dequeue();
                break;
            }
            case 3: {
                printf("\nDisplay Reservations:\n");
                displayReservations();
                break;
            }
            case 4: {
                char nameToCancel[50];
                printf("\nCancel a Reservation:\n");
                printf("Enter customer name to cancel: ");
                scanf("%s", nameToCancel);
                cancelReservation(nameToCancel);
                break;
            }
            case 5: {
                printf("Thank you for using the reservation system. Exiting.\n");
                break;
            }
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
