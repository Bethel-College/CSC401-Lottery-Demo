#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

// global ticket count
int gtickets = 0;
const int LARGE_VALUE = 10000;

struct node_t
{
  char process;
  int tickets;
  int strideValue;
  int passValue;
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
  tmp->strideValue = LARGE_VALUE / tickets;
  tmp->passValue = 0;
  tmp->winningAmount = 0;
  tmp->next = head;
  head = tmp;
  gtickets += tickets;
}

void print_list()
{
  struct node_t *curr = head;
  int prevTickets = 0;
  printf("Process List: ");
  while (curr)
  {
    double ticketPercentage = (double)curr->tickets / (double)gtickets * (double)100;
    printf("[%c: %d (%.2f%%)] ", curr->process, curr->tickets, ticketPercentage);
    prevTickets += curr->tickets;
    curr = curr->next;
  }
  printf("\n");
}

void print_header() {
  struct node_t *curr = head;
  printf("\n");
  while (curr) {
    printf("%*c", 8, curr->process);
    curr = curr->next;
  }
  printf("%*s", 14, "Who Runs?");
  printf("\n");

  curr = head;
  while (curr) {
    printf("%*d", 8, curr->strideValue);
    curr = curr->next;
  }
  printf("\n");
  for (int i = 0; i < 38; i++) {
    putchar('-');
  }
  printf("\n");
}

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    fprintf(stderr, "usage: stride <loops>\n");
    exit(1);
  }
  int loops = atoi(argv[1]);

  // populate list with some number of jobs, each
  // with some number of tickets
  insert('C', 250);
  insert('B', 50);
  insert('A', 100);

  print_list();
  print_header();

  int i;
  for (i = 0; i < loops; i++)
  {
    struct node_t *current = head;
    struct node_t *lowest = head;

    while (current)
    {
      printf("%*d", 8, current->passValue);
      if (current->passValue < lowest->passValue) {
        // this means this is a lower pass value
        lowest = current;
      }

      current = current->next;
    }

    lowest->passValue += lowest->strideValue;
    lowest->winningAmount += 1;
    printf("%*c\n", 14, lowest->process);
  }

  struct node_t *current = head;
  printf("\n");
  while (current)
  {
    double ticketPercentage = (double)current->tickets / (double)gtickets * (double)100;
    double actualWinningPercentage = (double)current->winningAmount / (double)loops * (double)100;
    printf("%c Expected Run Percentage = %.2f, Actual = %.2f\n", current->process, ticketPercentage, actualWinningPercentage);
    current = current->next;
  }

  return 0;
}
