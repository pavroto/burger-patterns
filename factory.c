#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *name;
  char **ingridients; // NULL terminated list.
  int n_ingridients;  // Number of ingridients excluding NULL terminator.
} burger;

void destroy_burger(burger *brg) {
  free(brg->name);

  if (brg->ingridients != NULL) {
    for (int i = brg->n_ingridients - 1; i >= 0; i--)
      free(brg->ingridients[i]);

    free(brg->ingridients);
  }

  free(brg);
}

void printf_burger(const burger *brg) {
  printf("Name: %s\n", brg->name);
  printf("Ingridients:\n");

  for (int counter = 1; counter <= brg->n_ingridients; counter++)
    printf("  %d: %s\n", counter, brg->ingridients[counter - 1]);
}

burger *create_custom_burger(const char *name, const char **ingridients,
                             int n_ingridients) {

  burger *brg = (burger *)malloc(sizeof(burger));

  if (brg == NULL) {
    perror("malloc");
    return NULL;
  }

  size_t name_size = strlen(name);
  brg->name = (char *)malloc(name_size + 1);

  if (brg->name == NULL) {
    perror("malloc");
    free(brg);
    return NULL;
  }

  strncpy(brg->name, name, name_size + 1);

  brg->n_ingridients = n_ingridients;
  brg->ingridients = (char **)malloc(sizeof(char *) * n_ingridients + 1);

  if (brg->ingridients == NULL) {
    perror("malloc");
    free(brg->name);
    free(brg);
    return NULL;
  }

  int i;
  for (i = 0; i < n_ingridients; i++) {
    brg->ingridients[i] = (char *)malloc(strlen(ingridients[i]) + 1);
    if (brg->ingridients[i] == NULL) {
      perror("malloc");
      destroy_burger(brg);
      return NULL;
    }
    strncpy(brg->ingridients[i], ingridients[i], strlen(ingridients[i]) + 1);
  }

  ingridients[i] = NULL;

  return brg;
}

burger *create_cheeseburger(void) {
  char *name = "Cheeseburger";

  const char *ingridients[] = {"bottom-bun", "mayonnaise", "patty",
                               "onion",      "cheese",     "lettuse",
                               "mayonnaise", "top-bun",    NULL};

  int n_ingridients;
  for (n_ingridients = 0; ingridients[n_ingridients]; n_ingridients++)
    ;

  return create_custom_burger(name, ingridients, n_ingridients);
}

burger *create_doublecheeseburger(void) {
  char *name = "Double Cheeseburger";

  const char *ingridients[] = {"bottom-bun", "mayonnaise", "patty",   "onion",
                               "cheese",     "patty",      "onion",   "cheese",
                               "lettuse",    "mayonnaise", "top-bun", NULL};

  int n_ingridients;
  for (n_ingridients = 0; ingridients[n_ingridients]; n_ingridients++)
    ;

  return create_custom_burger(name, ingridients, n_ingridients);
}

int main(int argc, char *argv[]) {
  // Cheeseburger
  burger *cheeseburger = create_cheeseburger();
  printf_burger(cheeseburger);
  destroy_burger(cheeseburger);

  printf("\n");

  // Double Cheeseburger
  burger *doublecheeseburger = create_doublecheeseburger();
  printf_burger(doublecheeseburger);
  destroy_burger(doublecheeseburger);

  return 0;
}
