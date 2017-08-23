#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doublelink.h"
#include "operation.h"


int summation(int float_ops)
{
    int sum = 0, data = 0, one , two;

    if( float_ops == 1 )
    while( head_float1 != NULL || head_float2 != NULL )
    {
        one = two = 0;
        if( get_last(&head_float1,&tail_float1,&data)!= Failure)
        one = data;

        if( get_last(&head_float2,&tail_float2,&data) != Failure)
        two = data;

        sum = sum + one + two;

        if( sum > 9999 )
        {
            sum = sum % 10000;
            insert_at_first(&head_float_out,&tail_float_out,sum);
            sum = 1;
        }
        else if( sum == 0)
        {
            insert_at_first(&head_float_out,&tail_float_out,sum);
            sum = 0;
        }
        else
        {
            insert_at_first(&head_float_out,&tail_float_out,sum);
            sum = 0;
        }
    }

    while( head_real1 != NULL || head_real2 != NULL )
    {
        one = two = 0;
        if( get_last(&head_real1,&tail_real1,&data)!= Failure)
        one = data;

        if( get_last(&head_real2,&tail_real2,&data) != Failure)
        two = data;

        sum = sum + one + two;

        if( sum > 9999 )
        {
            sum = sum % 10000;
            insert_at_first(&head_real_out,&tail_real_out,sum);
            sum = 1;
        }
        else if( sum == 0)
        {
            insert_at_first(&head_real_out,&tail_real_out,sum);
            sum = 0;
        }
        else
        {
            insert_at_first(&head_real_out,&tail_real_out,sum);
            sum = 0;
        }
    }
    if( sum != 0 )
    insert_at_first(&head_real_out,&tail_real_out,sum);

}

/*subtraction operation*/
int subtraction(int float_ops)
{
      int return_value, data, one, two, diff = 0;

      if( float_ops )
      {
          return_value = compare_list(&head_float1,&head_float2);

          /*if both values are equal*/
          if( return_value == EQUAL )
              insert_at_first(&head_float_out,&tail_float_out,0);
          else
          {
            while( head_float1)
            {
                /*get each data and subtract*/
                get_last(&head_float1,&tail_float1,&data);
                one = data;

                get_last(&head_float2,&tail_float2,&data);
                two = data;

                if( return_value == LIST1 )
                diff = one - two - diff;
                else if( return_value == LIST2 )
                {
                    diff = two - one - diff;
                    minus = 1;
                }


                /*handle borrow*/
                if( diff > 0 ) /*if diff is positive put zero*/
                {
                  insert_at_first(&head_float_out,&tail_float_out,diff);
                  diff = 0;
                }
                else /* take one borrow */
                {
                  diff = 9999 + diff + 1;
                  insert_at_first(&head_float_out,&tail_float_out,diff);
                  diff = 1;
                }

            }
          }
      }

      /*check which value is greter*/
      return_value = compare_list(&head_real1,&head_real2);

      /*if both lists are equal put zero in output list*/
      if( return_value == EQUAL )
      {
          insert_at_first(&head_real_out,&tail_real_out,0);
          return 0;
      }

      while( head_real1)
      {
          /*get each data and subtract*/
          get_last(&head_real1,&tail_real1,&data);
          one = data;

          get_last(&head_real2,&tail_real2,&data);
          two = data;

          if( return_value == LIST1 )
          diff = one - two - diff;
          else if( return_value == LIST2 )
          {
              diff = two - one - diff;
              minus = 1;
          }


          /*handle borrow*/
          if( diff > 0 ) /*if diff is positive put zero*/
          {
            insert_at_first(&head_real_out,&tail_real_out,diff);
            diff = 0;
          }
          else /* take one borrow */
          {
            diff = 9999 + diff + 1;
            insert_at_first(&head_real_out,&tail_real_out,diff);
            diff = 1;
          }

      }
      return 0;
  }


int multiplication(int float_ops)
{
    int one = 0, two = 0, mul = 0, carry = 0, data, i = 0, j = 0;

    /*if the input is float
    modify the function for float */

    if( float_ops == 1 )
    while( head_float2 != NULL )
    {
        /*get second number*/
        if( get_last(&head_float2,&tail_float2,&data)!= Failure)
        two = data;
        printf("two %d\n",two);
        i = j;
        carry = 0;
        Dlist *ptr = tail_float1, *ptr_out = head_float_out;
        while( ptr )
        {
            get_last_data_without_deletion(&head_float1,&ptr,&data);
            one = data;
            printf("one %d\n",one);
            ptr = ptr->prev;
            mul = one * two + carry;
            carry = mul / 10000;
            printf("mul %d\n",mul);
            printf("carry %d\n",carry);
            if( j == 0 )
            insert_at_first(&head_float_out, &tail_float_out,mul % 10000);
            else
            {
                data = 0;
                shift_get(&head_float_out,&tail_float_out,i,&data);
                mul = mul + data;
                shift_add(&head_float_out,&tail_float_out,i,mul % 10000);
                carry = mul / 10000;
            }
            i++;
        }
        if( carry != 0 )
        insert_at_first(&head_float_out, &tail_float_out,carry);
        j++;
    }

    /*delete entire float list*/
    delete_list(&head_float1, &tail_float1);
    delete_list(&head_float2, &tail_float2);

    carry = 0;
    i = j = 0;
    mul = 0;
    data = 0;
    while( head_real2 != NULL )
    {
        /*get second number*/
        if( get_last(&head_real2,&tail_real2,&data)!= Failure)
        two = data;
        i = j;
        //carry = 0;
        Dlist *ptr = tail_real1, *ptr_out = head_real_out;
        while( ptr )
        {
            get_last_data_without_deletion(&head_real1,&ptr,&data);
            one = data;
            ptr = ptr->prev;
            mul = one * two + carry;
            carry = mul / 10000;
            if( j == 0 )
            insert_at_first(&head_real_out, &tail_real_out,mul % 10000);
            else
            {
                data = 0;
                shift_get(&head_real_out,&tail_real_out,i,&data);
                mul = mul + data;
                shift_add(&head_real_out,&tail_real_out,i,mul % 10000);
                carry = mul / 10000;
            }
            i++;
        }
        if( carry != 0 )
        insert_at_first(&head_real_out, &tail_real_out,carry);
        carry = 0;
        j++;
    }

    /*delete entire real list*/
    delete_list(&head_real1, &tail_real1);
    delete_list(&head_real2, &tail_real2);
}

/*handle division right now only for integers*/
int division(int float_ops)
{
   int count = 0;
    /*if first number is less output zero*/
    if( compare_list( &head_real1, &head_real2) == LIST2 )
    {
        printf("0\n");
        return 0;
    }

    /*if both are equal output 1*/
    if( compare_list( &head_real1, &head_real2) == EQUAL )
    {
        printf("1\n");
        return 0;
    }

//    subtraction(float_ops);
  //  count++;
  //  while( compare_list(head))
    //}

    //printf("count %d\n",count);
}
