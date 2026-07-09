/*******************************************************************************************************************************************************************
*Title			: Subtraction
*Description		: This function performs subtraction of two given large numbers and store the result in the resultant list.
*Prototype		: int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "apc.h"
#include <stddef.h>
#include <stdlib.h> 

int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR)
{
    Dlist *temp1 = *tail1;
    Dlist *temp2 = *tail2;
    Dlist *result_tail = NULL;
    int borrow = 0;

    while (temp1 != NULL || temp2 != NULL)
    {
        int val1 = (temp1 != NULL) ? temp1->data : 0;
        int val2 = (temp2 != NULL) ? temp2->data : 0;

        val1 = val1 -  borrow;

        if (val1 < val2)
        {
            val1 = val1 + 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        int data = val1 - val2;

        if (insert_at_first(headR, &result_tail, data) == FAILURE)
            return FAILURE;

        if (temp1 != NULL)
		{
			 temp1 = temp1->prev;
		}
        if (temp2 != NULL) 
		{
			temp2 = temp2->prev;
		}
    }

    while (*headR && (*headR)->data == 0 && (*headR)->next != NULL)
    {
        Dlist *temp = *headR;
        *headR = (*headR)->next;
        (*headR)->prev = NULL;
        free(temp);
    }

    return SUCCESS;
}
