#include "client.h"

int main(int argc, char const *argv[])
{

    struct Tickets* tickets = InitTickets();

    PrintTickets(tickets);

    Push(NewTicket(1, BUY, 0, 10, 10), tickets);

    PrintTickets(tickets);

    Push(NewTicket(2, SELL, 1, 1, 11), tickets);

    PrintTickets(tickets);

    Push(NewTicket(3, SELL, 2, 100, 1), tickets);

    PrintTickets(tickets);

    DeleteTicket(1, tickets);

    PrintTickets(tickets);

    return 0;
}
