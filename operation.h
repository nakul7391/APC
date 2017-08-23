#ifndef OPERATION_H
#define OPERATION_H

extern Dlist *head_real1, *tail_real1,*head_real2, *tail_real2, *head_real_out, *tail_real_out,
 *head_float1, *tail_float1, *head_float2, *tail_float2, *head_float_out, *tail_float_out;

extern int minus;

int summation(int float_ops);

int subtraction(int float_ops);

int multiplication(int float_ops);

int division(int float_ops);

#endif
