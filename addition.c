/*******************************************************************************************************************************************************************
*Title			: Addition
*Description		: This function performs addition of two given large numbers and store the result in the resultant list.
*Prototype		: int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "apc.h"
#include <stddef.h>


int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR,Dlist **tailR)
{

	Dlist *temp1=*tail1;
	Dlist *temp2=*tail2;
	int data;
	int digit=0;
	data_t carry=0;

	while(temp1!=NULL || temp2!=NULL){


		int val1 = (temp1 !=NULL) ? temp1->data:0;
		int val2 = (temp2 !=NULL) ? temp2->data:0;
		
		data = val1+val2+carry;
		carry = data/10; 
		digit = data % 10;
	if (insert_at_first(headR, tailR, digit) == FAILURE)
	{
        return FAILURE;
	}

    if (temp1)
	{
		temp1 = temp1->prev;
	}
    if (temp2)
	{
		 temp2 = temp2->prev;
    }
}
	

	 if (carry)
    {
        if (insert_at_first(headR, tailR, carry) == FAILURE)
            return FAILURE;
    }
	return SUCCESS;
}
