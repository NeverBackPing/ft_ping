#include "../incl/token.h"

t_tokenizer* createt_tokenizer(int token, char *data)
{
    t_tokenizer* Node_tokenizer = (t_tokenizer*)malloc(sizeof(t_tokenizer));
    Node_tokenizer->token = token;
    Node_tokenizer->data = data;
    Node_tokenizer->next = NULL;
    Node_tokenizer->prev = NULL;
    return (Node_tokenizer);
}

void    insertAtBeginning(t_tokenizer **head, int token, char *data)
{
    t_tokenizer* Node_tokenizer = createt_tokenizer(token, data);

    if (head == NULL)
    {
        head = Node_tokenizer;
        return ;
    }
    Node_tokenizer->next = head;
    head->prev = Node_tokenizer;
    head = Node_tokenizer;
}

void	data_delone(t_tokenizer *lst)
{
	if (lst == NULL)
		return ;
	free (lst);
}

void	data_clear(t_tokenizer **lst)
{
	t_tokenizer	*tmp_tokenizer;
	t_tokenizer	*tmp_tokenizer_2;

	tmp_tokenizer = *lst;
	tmp_tokenizer_2 = *lst;
	while (tmp_tokenizer)
	{
		tmp_tokenizer_2 = tmp_tokenizer->next;
		data_delone(tmp_tokenizer);
		tmp_tokenizer = tmp_tokenizer_2;
	}
	*lst = NULL;
}

void printListForward(t_tokenizer* head)
{
	char *token[] = {"OPTION", "VALUE", "ADDRESS"};
    printf("Forward List: ");
    while (head != NULL)
	{
        printf("TOKEN= {%s} | DATA= {%s}\n", token[head->token], head->data);
        head = head->next;
    }
}

void	token_input(t_tokenizer **tokenizer, char **input, int nbr_input)
{
	if (nbr_input == 2)
	{
		t_tokenizer *token = *tokenizer;
		insertAtBeginning(token, ADDRESS, input[1]);
		return ;
	}

}
