#ifndef DOUBLELINK_H
#define DOUBLELINK_H

typedef int data_t;
/*structure for double link list*/
typedef struct Doublelink
{
    data_t data;
    struct Doublelink *prev;
    struct Doublelink *next;
} Dlist;

typedef enum
{
Failure,
Success
} Status;

typedef enum
{
LIST1,
LIST2,
EQUAL
} Compare;

Status insert_at_first(Dlist **head, Dlist **tail, data_t data);

Status print_list(Dlist **head);

Status get_last(Dlist **head, Dlist **tail, data_t *data);

int show_output(Dlist **head, Dlist **head_float, int float_ops, int minus);

Status get_last_data_without_deletion(Dlist **head, Dlist **tail,data_t *data);

Status shift_get(Dlist **head, Dlist **tail,int i, data_t *data);

Status shift_add(Dlist **head, Dlist **tail,int i, data_t data);

Compare compare_list(Dlist **head_real1, Dlist **head_real2);

Status delete_list(Dlist ** head, Dlist **tail);
#endif
