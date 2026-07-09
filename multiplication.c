/*******************************************************************************************************************************************************************
*Title			: Multiplication
*Description		: This function performs multiplication of two given large numbers and store the result in the resultant list.
*Prototype		: int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "apc.h"
#include <stddef.h>
int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    if (*head1 == NULL || *head2 == NULL)
        return FAILURE;

    Dlist *temp1 = *tail1;
    int position = 0;
    int data =0;

    *headR = NULL;
    *tailR = NULL;

    while (temp1)
    {
        Dlist *temp2 = *tail2;
        Dlist *temp_result = NULL;
        Dlist *tail_result = NULL;
        int carry = 0;

        for (int i = 0; i < position; i++)
        {
            insert_at_first(&temp_result, &tail_result, 0);
        }

        while (temp2)
        {
            int product = temp1->data * temp2->data + carry;
            carry = product / 10;
            data = product % 10;
            insert_at_first(&temp_result, &tail_result, data);
            temp2 = temp2->prev;
        }

        if (carry)
        {
            insert_at_first(&temp_result, &tail_result, carry);
        }

        Dlist *new_headR = NULL, *new_tailR = NULL;
        addition(&temp_result, &tail_result, headR, tailR, &new_headR, &new_tailR);

        *headR = new_headR;
        *tailR = new_tailR;
 
        temp1 = temp1->prev;
        position++;
    }

    return SUCCESS;
}
