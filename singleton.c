#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// It is so ugly....
// But I am not sure how to fix that without
// violating the design pattern itself.

void*
sburger()
{
  typedef struct {
    char* name;
  } burger;

  static burger* s_burger;
  if (s_burger == NULL)
  {
    printf("New Singleton burger created!\n");
    s_burger = (burger*)malloc(sizeof(burger));

    char name[] = "Singleton Burger";
    
    size_t name_length = strlen(name);

    s_burger->name = (char*)malloc(name_length + 1);
    strncpy(s_burger->name, name, name_length + 1);
  }
  else
    printf("Static singleton burger returned\n");

  return s_burger;
}

char*
get_sburger_name (void* burger)
{
  if (burger == NULL)
  {
    fprintf(stderr, "get_name: burger pointer is NULL\n");
    return NULL;
  }

  char* name = *(void**)burger;
  return name;
}

int
set_sburger_name (void* burger, char* new_name)
{
  if (burger == NULL)
  {
    fprintf(stderr, "set_name: burger pointer is NULL\n");
    return 1;
  }

  if (new_name == NULL)
  {
    fprintf(stderr, "set_name: new_name pointer is NULL\n");
    return 1;
  }

  char* name = *(void**)burger;

  size_t new_name_len = strlen(new_name);

  name = (char*)realloc(name, new_name_len + 1);

  strncpy(name, new_name, new_name_len);

  return 0;
}

void
printf_sburger_name(void* burger)
{
  if (burger == NULL)
  {
    fprintf(stderr, "printf: burger pointer is NULL\n");
    return;
  }

  char* name = *(void**)burger;

  if (name == NULL)
  {
    fprintf(stderr, "printf: burger name pointer is NULL\n");
    return;
  }

  printf("%s\n", name);
}

void
free_sburger(void* burger)
{
  char* name = *(void**)burger;
  free(name);

  free(burger);
}

int
main(int argc, char* argv[])
{
  get_sburger_name(NULL);

  void* burger = sburger();
  printf_sburger_name(burger);
  
  printf("The name is: %s\n", get_sburger_name(burger));

  set_sburger_name(burger, "Singleton Burger 2");
  printf("New name is: %s\n", get_sburger_name(burger));


  void* burger2 = sburger();
  printf_sburger_name(burger2);
  printf("The name from burger2 pointer: %s\n", get_sburger_name(burger2));

  free_sburger(burger);

  return 0;
}
