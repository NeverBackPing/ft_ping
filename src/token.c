#include "../incl/token.h"

/*
	Create the node for link list
*/
t_tokenizer* createt_tokenizer(int token, char *data)
{
    t_tokenizer* Node_tokenizer = (t_tokenizer*)malloc(sizeof(t_tokenizer));

    Node_tokenizer->token = token;
    Node_tokenizer->data = data;
    Node_tokenizer->next = NULL;
    Node_tokenizer->prev = NULL;
    return (Node_tokenizer);
}

/*
	delate one node
*/
void	data_delone(t_tokenizer *tokenizer)
{
	if (tokenizer == NULL)
		return ;
	free (tokenizer);
}

/*
	delate the link list
*/
void	data_clear(t_tokenizer **tokenizer)
{
	t_tokenizer	*tmp_tokenizer;
	t_tokenizer	*tmp_tokenizer_2;

	if (!tokenizer || !*tokenizer)
		return ;
	tmp_tokenizer = *tokenizer;
	tmp_tokenizer_2 = *tokenizer;
	while (tmp_tokenizer)
	{
		tmp_tokenizer_2 = tmp_tokenizer->next;
		data_delone(tmp_tokenizer);
		tmp_tokenizer = tmp_tokenizer_2;
	}
	*tokenizer = NULL;
}

/*
	print data of the link list
*/
void printListForward(t_tokenizer* head)
{
	int count = 1;
	char *token[] = {"OPTION", "VALUE", "ADDRESS"};
    printf("Forward List: ");
    while (head != NULL)
	{
        printf("%d | TOKEN= {%s} | DATA= {%s}\n", count++, token[head->token], head->data);
        head = head->next;
    }
}

/*
	Get the last node in the link list
*/
t_tokenizer	*last(t_tokenizer *lst)
{
	t_tokenizer	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp)
	{
		if (tmp->next == NULL)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

/*
	keep the head of nodes in the first in link list
	and put the last in the end.

	- A pointer to the next node (next)
	- A pointer to the previous node (prev)
*/
void	insertAtBeginning(t_tokenizer **tokenizer, t_tokenizer *new_node)
{
	t_tokenizer	*end_node;

	end_node = NULL;
	if (*tokenizer)
	{
		end_node = last(*tokenizer);
		end_node->next = new_node;
		new_node->prev = end_node;
	}
	else
	{
		*tokenizer = new_node;
		new_node->prev = end_node;
	}
}

/*
	Lexer
*/
void	token_input(t_tokenizer **tokenizer, char **input, int nbr_input)
{
	t_tokenizer *tmp_token;

	tmp_token = NULL;
	if (nbr_input == 2)
	{
		if (IsFlag(input[1]))
			tmp_token = createt_tokenizer(OPTION, input[1]);
		else
			tmp_token = createt_tokenizer(ADDRESS, input[1]);
		insertAtBeginning(tokenizer, tmp_token);
		return ;
	}

	int tmp_nbr = nbr_input;

	while (tmp_nbr--)
	{

	}

}
