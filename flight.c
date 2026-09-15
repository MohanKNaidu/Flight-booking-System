#include <stdio.h>
#include <string.h>

#define MAX_TICKETS 100
#define TICKET_PRICE_DOMESTIC 5000
#define TICKET_PRICE_INTERNATIONAL 15000

typedef struct
{
    char passengerName[50];
    char passportID[20];
    char source[50];
    char destination[50];
    char phoneNumber[20];
    char travelDate[20];
    char airline[50];
    char timing[50];

    float ticketPrice;
    int isBooked;

} Ticket;

Ticket tickets[MAX_TICKETS];
int ticketCount = 0;


/* Function to display ticket details */
void displayTicketDetails(Ticket ticket)
{
    printf("\n----------- TICKET DETAILS -----------\n");

    printf("Passenger Name : %s\n", ticket.passengerName);
    printf("Passport ID    : %s\n", ticket.passportID);
    printf("Source         : %s\n", ticket.source);
    printf("Destination    : %s\n", ticket.destination);
    printf("Phone Number   : %s\n", ticket.phoneNumber);
    printf("Travel Date    : %s\n", ticket.travelDate);
    printf("Airline        : %s\n", ticket.airline);
    printf("Timing         : %s\n", ticket.timing);
    printf("Ticket Price   : %.2f\n", ticket.ticketPrice);

    if (ticket.isBooked)
        printf("Status         : Booked\n");
    else
        printf("Status         : Cancelled\n");

    printf("--------------------------------------\n");
}


/* Check whether Passport ID is already booked */
int isPassportIDBooked(char passportID[])
{
    for (int i = 0; i < ticketCount; i++)
    {
        if (strcmp(tickets[i].passportID, passportID) == 0 &&
            tickets[i].isBooked == 1)
        {
            return 1;
        }
    }

    return 0;
}


/* Find ticket by passenger name and destination */
int findTicketByPassengerAndDestination(char name[], char destination[])
{
    for (int i = 0; i < ticketCount; i++)
    {
        if (strcmp(tickets[i].passengerName, name) == 0 &&
            strcmp(tickets[i].destination, destination) == 0 &&
            tickets[i].isBooked == 1)
        {
            return i;
        }
    }

    return -1;
}


/* Book Ticket */
void bookTicket()
{
    if (ticketCount >= MAX_TICKETS)
    {
        printf("Ticket booking limit reached!\n");
        return;
    }

    Ticket newTicket;
    int ticketType;

    printf("\nSelect Ticket Type:\n");
    printf("1. Domestic Ticket\n");
    printf("2. International Ticket\n");
    printf("Enter your choice: ");
    scanf("%d", &ticketType);

    if (ticketType == 1)
        newTicket.ticketPrice = TICKET_PRICE_DOMESTIC;
    else
        newTicket.ticketPrice = TICKET_PRICE_INTERNATIONAL;

    strcpy(newTicket.airline, "Bharath Airlines");
    strcpy(newTicket.timing,
           "7:00 PM(Departure)- 10:00 PM(Arrival)");

    printf("Enter Passenger Name: ");
    scanf("%s", newTicket.passengerName);

    printf("Enter Passport ID: ");
    scanf("%s", newTicket.passportID);

    if (isPassportIDBooked(newTicket.passportID))
    {
        printf("Ticket is already booked for this Passport ID!\n");

        int ticketIndex =
            findTicketByPassengerAndDestination(
                newTicket.passengerName,
                newTicket.destination);

        if (ticketIndex != -1)
        {
            displayTicketDetails(tickets[ticketIndex]);
        }

        return;
    }

    printf("Enter Source: ");
    scanf("%s", newTicket.source);

    printf("Enter Destination: ");
    scanf("%s", newTicket.destination);

    printf("Enter Phone Number: ");
    scanf("%s", newTicket.phoneNumber);

    printf("Enter Travel Date (dd-mm-yyyy): ");
    scanf("%s", newTicket.travelDate);

    newTicket.isBooked = 1;

    tickets[ticketCount++] = newTicket;

    printf("\nTicket booked successfully!\n");

    displayTicketDetails(newTicket);
}


/* Cancel Ticket */
void cancelTicket()
{
    char passportID[20];

    printf("\nEnter Passport ID to cancel the ticket: ");
    scanf("%s", passportID);

    for (int i = 0; i < ticketCount; i++)
    {
        if (strcmp(tickets[i].passportID, passportID) == 0)
        {
            tickets[i].isBooked = 0;

            printf("Ticket cancelled successfully!\n");
            return;
        }
    }

    printf("No ticket found with Passport ID: %s\n", passportID);
}


/* Search Ticket */
void searchTicket()
{
    char name[50];
    char destination[50];

    printf("\nEnter Passenger Name: ");
    scanf("%s", name);

    printf("Enter Destination: ");
    scanf("%s", destination);

    int ticketIndex =
        findTicketByPassengerAndDestination(name, destination);

    if (ticketIndex != -1)
    {
        printf("Ticket is booked!\n");

        displayTicketDetails(tickets[ticketIndex]);
    }
    else
    {
        printf("No ticket found for this passenger and destination.\n");
    }
}


/* Check Availability */
void checkAvailability()
{
    char destination[50];
    char travelDate[20];

    printf("\nEnter Destination: ");
    scanf("%s", destination);

    printf("Enter Travel Date (dd-mm-yyyy): ");
    scanf("%s", travelDate);

    int availableTickets = MAX_TICKETS - ticketCount;

    printf("Available tickets for %s on %s: %d\n",
           destination,
           travelDate,
           availableTickets);
}


/* Main Function */
int main()
{
    int choice;

    do
    {
        printf("\n--- Flight Ticket Booking System ---\n");
        printf("1. Book Ticket\n");
        printf("2. Cancel Ticket\n");
        printf("3. Search Ticket\n");
        printf("4. Check Availability\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                bookTicket();
                break;

            case 2:
                cancelTicket();
                break;

            case 3:
                searchTicket();
                break;

            case 4:
                checkAvailability();
                break;

            case 5:
                printf("Exiting the system. Thank you!\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }

    } while (choice != 5);

    return 0;
}
