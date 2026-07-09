#ifndef APC_H
#define APC_H
#define SUCCESS 0
#define FAILURE -1

typedef int data_t;
typedef struct node
{
	struct node *prev;
	data_t data;
	struct node *next;
}Dlist;
int insert_at_end(Dlist **head, Dlist **tail, data_t data);
int string_to_dlist(char *str, Dlist **head, Dlist **tail);
void print_dlist(Dlist *head);
int insert_at_first(Dlist **head, Dlist **tail, int data);
void free_list(Dlist **head, Dlist **tail);
int is_zero(Dlist *head);
void remove_zeros(Dlist **head);
int cmp_list(Dlist *head1, Dlist *head2);
void up_tail(Dlist** head, Dlist** tail);
void cp_list(Dlist* src_head, Dlist** dest_head, Dlist** dest_tail);
Dlist* create_node(data_t data);
/* Include the prototypes here */
int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR,Dlist **tailR);
int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR,Dlist **tailR);
int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);
#endif
