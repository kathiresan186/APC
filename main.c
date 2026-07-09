/* DOCUMENTATION 
NAME : KATHIRESAN 
DATE : 07-08-2025 
DESCRIPTION : APC - Project-1*/
/**************************************************************************************************************************************************************
* Title        : main function (Driver function)
* Description  : This function is used as the driver function for all the arithmetic operations using doubly linked lists
***************************************************************************************************************************************************************/
#include "apc.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Error: Invalid number of arguments.\n");
        printf("Usage: %s <operand1> <operator> <operand2>\n", argv[0]);
        return FAILURE;
    }

    Dlist *head1 = NULL, *tail1 = NULL;
    Dlist *head2 = NULL, *tail2 = NULL;
    Dlist *headR = NULL, *tailR = NULL;

    char *input1 = argv[1];
    char *input2 = argv[3];

    int ind_argv1 = 1, ind_argv2 = 1, res = 1;

    if (input1[0] == '-')
    {
        ind_argv1 = -1;
        input1++;
    }

    if (input2[0] == '-')
    {
        ind_argv2 = -1;
        input2++;
    }

    if (string_to_dlist(input1, &head1, &tail1) == FAILURE ||
        string_to_dlist(input2, &head2, &tail2) == FAILURE)
    {
        printf("Error: Invalid input numbers.\n");
        return FAILURE;
    }

    char operator = argv[2][0];
    char option;

    do
    {
        free_list(&headR, &tailR); 
        switch (operator)
        {
        case '+':
            if (ind_argv1 == ind_argv2)
            {
                if (addition(&head1, &tail1, &head2, &tail2, &headR, &tailR) == SUCCESS)
                    res = ind_argv1;
                else
                {
                    printf("Addition failed\n");
                    return FAILURE;
                }
            }
            else
            {
                int comp = cmp_list(head1, head2);
                if (comp == 0)
                {
                    insert_at_first(&headR, &tailR, 0);
                    res = 1;
                }
                else if (comp > 0)
                {
                    subtraction(&head1, &tail1, &head2, &tail2, &headR);
                    res = ind_argv1;
                }
                else
                {
                    subtraction(&head2, &tail2, &head1, &tail1, &headR);
                    res = ind_argv2;
                }
            }
            break;

        case '-':
            if (ind_argv1 == ind_argv2)
            {
                int comp = cmp_list(head1, head2);
                if (comp == 0)
                {
                    insert_at_first(&headR, &tailR, 0);
                    res = 1;
                }
                else if (comp > 0)
                {
                    subtraction(&head1, &tail1, &head2, &tail2, &headR);
                    res = ind_argv1;
                }
                else
                {
                    subtraction(&head2, &tail2, &head1, &tail1, &headR);
                    res = -ind_argv1;
                }
            }
            else
            {
                if (addition(&head1, &tail1, &head2, &tail2, &headR, &tailR) == SUCCESS)
                    res = ind_argv1;
                else
                {
                    printf("Subtraction failed\n");
                    return FAILURE;
                }
            }
            break;

        case 'x':
        case 'X':
            if (multiplication(&head1, &tail1, &head2, &tail2, &headR, &tailR) == SUCCESS)
                res = ind_argv1 * ind_argv2;
            else
            {
                printf("Multiplication failed\n");
                return FAILURE;
            }
            break;

        case '/':
            if (division(&head1, &tail1, &head2, &tail2, &headR, &tailR) == SUCCESS)
                res = ind_argv1 * ind_argv2;
            else
            {
                printf("Division failed\n");
                return FAILURE;
            }
            break;

        default:
            printf("Unsupported operator: %c\n", operator);
            return FAILURE;
        }

        if (headR && headR->data == 0 && headR->next == NULL)
            printf("Result: 0\n");
        else
        {
            printf("Result: ");
            if (res == -1)
                printf("-");
            print_dlist(headR);
        }

        printf("Want to continue? Press[yY | nN]: ");
        scanf(" %c", &option);

    } while (option == 'y' || option == 'Y');

    free_list(&head1, &tail1);
    free_list(&head2, &tail2);
    free_list(&headR, &tailR);

    return 0;
}


int string_to_dlist(char *str, Dlist **head, Dlist **tail)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            if (insert_at_end(head, tail, str[i] - '0') == FAILURE)
                return FAILURE;
        }
        else
        {   printf("Error: Invalid character '%c' in input string.\n", str[i]);
            printf("Only digits are allowed.\n");                                                                                                         
            return FAILURE; 
        }
        i++;
    }
    return SUCCESS;
}

void print_dlist(Dlist *head)
{
    if (!head)
    {
        printf("0\n");
        return;
    }

    while (head)
    {
        printf("%d", head->data);
        head = head->next;
    }
    printf("\n");
}
int insert_at_end(Dlist **head, Dlist **tail, data_t data)
{
    Dlist *new=malloc(sizeof(Dlist));
    
    if(new==NULL){
        return FAILURE;
    }
    new->next=NULL;
    new->prev=NULL;
    if(*head==NULL && *tail==NULL){
        new->data=data;
        *head=*tail=new;
        return SUCCESS;
    }else
    {
        new->data=data;
        new->prev=*tail;
         (*tail)->next=new;
         *tail=new;
         return SUCCESS;
    }
}
int insert_at_first(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = malloc(sizeof(Dlist));
    
    if(new==NULL){
        return FAILURE;
    }
    new->next=NULL;
    new->prev=NULL;
    if(*head == NULL && *tail==NULL){
        new->data=data;
        *head=*tail=new;
       
        return SUCCESS;
    }else{
          new->data=data;
        new->next=*head;
       (*head)->prev=new;
        *head=new;
        
         return SUCCESS;
    }
    
}

int cmp_list(Dlist *head1, Dlist *head2)
{
    int len1 = 0, len2 = 0;
    Dlist *temp1 = head1, *temp2 = head2;

    while (temp1) 
    { 
        len1++; temp1 = temp1->next; 
    }
    while (temp2) 
    {
         len2++; temp2 = temp2->next;
     }

    if (len1 > len2) return 1;
    if (len1 < len2) return -1;

    temp1 = head1;
    temp2 = head2;

    while (temp1 && temp2)
    {
        if (temp1->data > temp2->data) return 1;
        if (temp1->data < temp2->data) return -1;
        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    return 0;
}
void free_list(Dlist **head, Dlist **tail)
{
    while (*head)
    {
        Dlist *temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    *tail = NULL;
}