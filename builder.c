#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

enum INGRIDIENT_CATEGORIES {
  NONE,
  BUN,
  PATTY,
  CHEESE,
  SOUCE,
  TOPPING
};

enum INGRIDIENT_FLAGS {
  VEGAN = 1,
  VEGETARIAN = 2,
  LOW_FAT = 4,
  LOW_CALORIE = 8,
  NUT_ALLERGY = 16,
  FISH_ALLERGY = 32,
  EGG_ALLERGY = 64,
};

typedef struct {
  char* name;
  uint32_t amount;
  uint32_t category;
  uint32_t flags;
} ingridient;

typedef struct {
  char *name;
  
  ingridient bun;
  ingridient patty;
  ingridient cheese;
  ingridient souce;
  ingridient topping;
   
} burger;

ingridient*
set_ingridient (ingridient* target, char* name, uint32_t amount, uint32_t category, uint32_t flags) 
{
  if (target == NULL)
    return NULL;

  if (name)
  {
    target->name = (char*)malloc(strlen(name) + 1);
    strcpy(target->name, name);
  }

  target->amount = amount;
  target->category = category;
  target->flags = flags;

  return target;
}

burger*
set_bun(burger* brg, char* name, uint32_t amount, uint32_t category, uint32_t flags)
{
  if (set_ingridient(&brg->bun, name, amount, category, flags) == NULL)
    return NULL;
  return brg;
}

burger*
set_patty(burger* brg, char* name, uint32_t amount, uint32_t category, uint32_t flags)
{
  if (set_ingridient(&brg->patty, name, amount, category, flags) == NULL)
    return NULL;
  return brg;
}

burger*
set_cheese(burger* brg, char* name, uint32_t amount, uint32_t category, uint32_t flags)
{
  if (set_ingridient(&brg->cheese, name, amount, category, flags) == NULL)
    return NULL;
  return brg;
}

burger*
set_souce(burger* brg, char* name, uint32_t amount, uint32_t category, uint32_t flags)
{
  if (set_ingridient(&brg->souce, name, amount, category, flags) == NULL)
    return NULL;
  return brg;
}

burger*
set_topping(burger* brg, char* name, uint32_t amount, uint32_t category, uint32_t flags)
{
  if (set_ingridient(&brg->topping, name, amount, category, flags) == NULL)
    return NULL;
  return brg;
}

burger*
create_burger (char* name)
{
  burger* brg = (burger*)malloc(sizeof(burger)); 

  brg->name = (char*)malloc(strlen(name) + 1);

  strcpy(brg->name, name);
  set_ingridient(&brg->bun, NULL, 0, 0, 0); 
  set_ingridient(&brg->patty, NULL, 0, 0, 0); 
  set_ingridient(&brg->cheese, NULL, 0, 0, 0); 
  set_ingridient(&brg->souce, NULL, 0, 0, 0); 
  set_ingridient(&brg->topping, NULL, 0, 0, 0); 

  return brg;
}

void
free_burger(burger* brg)
{
  free(brg->name);
  free(brg);
}

int main (int argc, char* argv[])
{
  burger* cheeseburger = create_burger("Cheeseburger");
  if (
  !set_bun(cheeseburger, "Seasame", 2, 1, VEGAN | VEGETARIAN | NUT_ALLERGY) |
  !set_patty(cheeseburger, "Beef", 1, 2, 0) |
  !set_cheese(cheeseburger, "Cheddar", 1, 3, 0) |
  !set_souce(cheeseburger, "Mayonaise", 2, 4, VEGETARIAN | EGG_ALLERGY) |
  !set_topping(cheeseburger, "Yellow Onion", 1, 5, VEGAN | VEGETARIAN | LOW_FAT | LOW_CALORIE) )
  {
    free_burger(cheeseburger);
    return 1;
  }

  free_burger(cheeseburger);

  return 0;
}
