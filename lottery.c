// Adapted from https://github.com/remzi-arpacidusseau/ostep-code/tree/master/cpu-sched-lottery
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

// global ticket count
int gtickets = 0;

struct node_t
{
  char process;
  int tickets;
  int winningAmount;
  struct node_t *next;
};

struct node_t *head = NULL;

void insert(char process, int tickets)
{
  struct node_t *tmp = malloc(sizeof(struct node_t));
  assert(tmp != NULL);
  tmp->process = process;
  tmp->tickets = tickets;
  tmp->winningAmount = 0;
  tmp->next = head;
  head = tmp;
  gtickets += tickets;
}

void print_list()
{
  struct node_t *curr = head;
  int prevTickets = 0;
  printf("List: head->");
  while (curr)
  {
    long ticketPercentage = lround((double)curr->tickets / (double)gtickets * 100);
    printf("[%c: %d (%ld%%), %d-%d]->", curr->process, curr->tickets, ticketPercentage, prevTickets, curr->tickets + prevTickets - 1);
    prevTickets += curr->tickets;
    curr = curr->next;
  }
  printf("NULL\n");
}

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    fprintf(stderr, "usage: lottery <seed> <loops>\n");
    exit(1);
  }
  int seed = atoi(argv[1]);
  int loops = atoi(argv[2]);
  srandom(seed);

  // populate list with some number of jobs, each
  // with some number of tickets
  insert('C', 250);
  insert('B', 50);
  insert('A', 100);

  printf("Total Tickets = %d\n", gtickets);
  print_list();

  int i;
  for (i = 0; i < loops; i++)
  {
    int counter = 0;
    int winner = random() % gtickets; // get winner
    struct node_t *current = head;

    // loop until the sum of ticket values is > the winner
    while (current)
    {
      counter = counter + current->tickets;
      if (counter > winner)
      {
        current->winningAmount += 1;
        break; // found the winner
      }
      current = current->next;
    }
    // current is the winner: schedule it...
    printf("Winning Ticket: %d, Winner: %c\n", winner, current->process);
  }

  struct node_t *current = head;
  printf("\n");
  while (current)
  {
    double ticketPercentage = (double)current->tickets / (double)gtickets * (double)100;
    double actualWinningPercentage = (double)current->winningAmount / (double)loops * (double)100;
    printf("%c Expected Winning Percentage = %.2f, Actual = %.2f\n", current->process, ticketPercentage, actualWinningPercentage);
    current = current->next;
  }

  return 0;
}
