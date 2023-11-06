#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_RESERVATIONS 100

typedef struct {
    char name[50];
    int partySize;
    char time[10];
} Reservation;

Reservation stack[MAX_RESERVATIONS];
int top = -1;

bool isStackEmpty() {
    return top == -1;
}

bool isStackFull() {
    return top == MAX_RESERVATIONS - 1;
}

void push(Reservation reservation) {
    if (!isStackFull()) {
        stack[++top] = reservation;
        printf("Reservation for %s (Party Size: %d, Time: %s) added successfully.\n", reservation.name, reservation.partySize, reservation.time);
    } else {
        printf("Reservation stack is full. Cannot add more reservations.\n");
    }
}

void cancelReservation() {
    if (!isStackEmpty()) {
        Reservation canceledReservation = stack[top--];
        printf("Reservation for %s (Party Size: %d, Time: %s) has been canceled.\n", canceledReservation.name, canceledReservation.partySize, canceledReservation.time);
    } else {
        printf("Reservation stack is empty. No reservations to cancel.\n");
    }
}

void modifyReservation(int index) {
    if (index >= 0 && index <= top) {
        char name[50];
        int partySize;
        char time[10];

        printf("\nModify Reservation at Index %d:\n", index);
        printf("Enter new customer name: ");
        scanf("%s", name);
        printf("Enter new party size: ");
        scanf("%d", &partySize);
        printf("Enter new reservation time (HH:MM AM/PM): ");
        scanf("%s", time);

        Reservation modifiedReservation;
        strcpy(modifiedReservation.name, name);
        modifiedReservation.partySize = partySize;
        strcpy(modifiedReservation.time, time);

        stack[index] = modifiedReservation;
        printf("Reservation at index %d has been modified.\n", index);
    } else {
        printf("Invalid index. No reservation was modified.\n");
    }
}

void displayReservations() {
    printf("Reservations:\n");
    for (int i = 0; i <= top; i++) {
        printf("Index %d - Name: %s, Party Size: %d, Time: %s\n", i, stack[i].name, stack[i].partySize, stack[i].time);
    }
}

int main() {
    int choice;

    printf("Welcome to the Restaurant Reservation System\n");

    do {
        printf("Main Menu:\n");
        printf("1. Make a reservation\n");
        printf("2. Cancel a reservation\n");
        printf("3. Modify a reservation\n");
        printf("4. Display reservations\n");
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
                push(reservation);
                break;
            }
            case 2: {
                cancelReservation();
                break;
            }
            case 3: {
                int index;

                printf("\nEnter the index of the reservation to modify: ");
                scanf("%d", &index);
                modifyReservation(index);
                break;
            }
            case 4: {
                printf("\nDisplay Reservations:\n");
                displayReservations();
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
