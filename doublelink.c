/*file for double link list*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "doublelink.h"

Status insert_at_first(Dlist **head, Dlist **tail, data_t data)
{
    /*allocate memory*/
    Dlist *new = malloc(sizeof(Dlist));

    if( new == NULL )
    return Failure;

    /*create node*/
    new->next = new->prev = NULL;
    new->data = data;

    /*check head*/
    if( *head == NULL )
    {
        *head = *tail = new;
        return Success;
     }

     (*head)->prev = new;
     new->next = *head;
     *head = new;

     return Success;
}

/*print list function*/
Status print_list(Dlist **head)
{
    if( *head == NULL )
    return Failure;

    Dlist *ptr = *head;
    while( ptr )
    {
        printf("%04d->",ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}

/*function for multiplication leave last node and retreive data*/
Status shift_get(Dlist **head, Dlist **tail,int i, data_t *data)
{
      Dlist *ptr = *tail;
      while( i-- )
      ptr = ptr->prev;

      if( ptr != NULL )
      {
          *data = ptr->data;
          return Success;
      }

      return Failure;
}

/*delete list function*/
Status delete_list(Dlist ** head, Dlist **tail)
{
    Dlist *ptr = *head, *prev = *head;

    while( ptr )
    {
        prev = ptr;
        ptr = ptr->next;
        free(prev);
    }

    *head = *tail = NULL;

    return Success;
}


Status shift_add(Dlist **head, Dlist **tail,int i, data_t data)
{
      Dlist *ptr = *tail;
      while( i-- )
      ptr = ptr->prev;

      if( ptr == NULL )
      {
      insert_at_first(head,tail,data);
      return Success;
      }

      if( ptr != NULL )
      {
          ptr->data = data;
          return Success;
      }

      return Failure;
}

/*delete node and get last data*/
Status get_last(Dlist **head, Dlist **tail,data_t *data)
{
    /*list doesnot exists*/
    if( *head == NULL )
    return Failure;

    Dlist *ptr = *tail;

    *data = ptr->data;

    /*if it is first node*/
    if( (*tail)->prev == NULL )
    {
        free(ptr);
        *head = *tail = NULL;
        return Success;
    }

    /*else*/
    (*tail) = ptr->prev;
    (*tail)->next = NULL;
    free(ptr);
    return Success;
}

Status get_last_data_without_deletion(Dlist **head, Dlist **tail,data_t *data)
{
    /*list doesnot exists*/
    if( *head == NULL )
    return Failure;

    Dlist *ptr = *tail;

    *data = ptr->data;

    return Success;
}


int show_output(Dlist **head, Dlist **head_float,int float_ops, int minus)
{
    if( *head == NULL )
    return Failure;

    Dlist *ptr = *head;

    /*print minus*/
    if( minus )
    printf("-");

    while( ptr )
    {
        if( ptr->prev == NULL )
        printf("%d",ptr->data);
        else if(ptr->data != 0 )
        printf("%04d",ptr->data);
        ptr = ptr->next;
    }

    if( *head_float == NULL )
    {
        printf("\n");
        return Failure;
    }


    if( float_ops == 1)
    {
      printf(".");
      Dlist *ptr = *head_float;
      while( ptr )
      {
          if(ptr->data != 0 )
          printf("%04d",ptr->data);
          ptr = ptr->next;
      }
    }

    printf("\n");
    return Success;
}

/*return one if list one is greater than list two else zero*/
Compare compare_list(Dlist **head1, Dlist **head2)
{
      Dlist *ptr1 = *head1, *ptr2 = *head2;

      /*both have same length*/
      while( ptr1 )
      {
          if( ptr1->data > ptr2->data)
          return LIST1;
          else if( ptr1->data < ptr2->data )
          return LIST2;
          else
          {
              ptr1 = ptr1->next;
              ptr2 = ptr2->next;
          }
      }

      /*if code comes here means both are equal*/
      return EQUAL;
}
