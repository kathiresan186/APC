/*******************************************************************************************************************************************************************
*Title			: Division
*Description	: This function performs division of two given large numbers and stores the result in the resultant list.
*Prototype		: int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output		: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "apc.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{

    if (*head1 == NULL || *head2 == NULL || is_zero(*head2))
        return FAILURE;

    remove_zeros(head1);
    remove_zeros(head2);

   
    if (cmp_list(*head1, *head2) < 0)
    {
        insert_at_end(headR, tailR, 0);
        return SUCCESS;
    }

    Dlist *temp = *head1;
    Dlist *part_head = NULL, *part_tail = NULL;

    while (temp)
    {
       
        insert_at_end(&part_head, &part_tail, temp->data);
        remove_zeros(&part_head);

        int count = 0;

        while (cmp_list(part_head, *head2) >= 0)
        {
            Dlist *copy1 = NULL, *copy_tail1 = NULL;
            Dlist *copy2 = NULL, *copy_tail2 = NULL;
            Dlist *result = NULL;

            cp_list(part_head, &copy1, &copy_tail1);
            cp_list(*head2, &copy2, &copy_tail2);

            if (subtraction(&copy1, &copy_tail1, &copy2, &copy_tail2, &result) == FAILURE)
                return FAILURE;


            free_list(&part_head, &part_tail);
            part_head = result;
            up_tail(&part_head, &part_tail);

            count++;


            free_list(&copy1, &copy_tail1);
            free_list(&copy2, &copy_tail2);
        }

        insert_at_end(headR, tailR, count);

        temp = temp->next;
    }


    remove_zeros(headR);

    return SUCCESS;
}
int is_zero(Dlist *head)
{
    while (head)
    {
        if (head->data != 0)
            return 0;
        head = head->next;
    }
    return 1;
}
void remove_zeros(Dlist **head)
{
    while (*head && (*head)->data == 0 && (*head)->next)
    {
        Dlist *temp = *head;
        *head = (*head)->next;
        (*head)->prev = NULL;
        free(temp);
    }
}

void cp_list(Dlist* src_head, Dlist** dest_head, Dlist** dest_tail)
{
    *dest_head = NULL;
    *dest_tail = NULL;

    Dlist* current = src_head;
    while (current)
    {
        Dlist* new_node = create_node(current->data);  

        if (*dest_head == NULL)
        {
            *dest_head = *dest_tail = new_node;
        }
        else
        {
            (*dest_tail)->next = new_node;
            new_node->prev = *dest_tail;
            *dest_tail = new_node;
        }
        current = current->next;
    }
}

void up_tail(Dlist** head, Dlist** tail) {
    Dlist* temp = *head;
    if (temp == NULL) {
        *tail = NULL;
        return;
    }
    while (temp->next != NULL)
        temp = temp->next;
    *tail = temp;
}
Dlist* create_node(data_t data)
{
    Dlist* new_node = (Dlist*)malloc(sizeof(Dlist));
    if (new_node == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL; 
    }

    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;

    return new_node;
}
