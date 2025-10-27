/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotadashirui <kotadashirui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:32:14 by rufurush          #+#    #+#             */
/*   Updated: 2025/10/26 13:53:50 by kotadashiru      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_metachar(char c)
{
    if(c == '|' || c == '<' || c == '>' || c == '&')
        return(1);
    else
        return(0);
}

int is_quote(char c)
{
    if(c == '\'' || c == '"')
        return(1);
    else    
        return(0);
}

int is_space(char c)
{
    if(c == ' ' || c == '\t')
        return(1);
    else
        return(0);
}

// void	meta_token_end(char *line, size_t *index)
// {
// 	if(is_metachar(line[*index]))
// 	{
// 		if((line[*index] == '<' && line[*index + 1] == '<') || (line[*index] == '>' && line[*index + 1] == '>'))
//         {
//             (*index) += 2;
//             return ;
//         }
//         (*index)++;
//         return ;
// 	}
// 	else
// 		return;
// }

void    token_end(char *line,size_t *index)
{
    int s_quote;
    int d_quote;
    size_t start;

    s_quote = 0;
    d_quote = 0;
    start = *index;

    if(line[start] == '\'')
        s_quote = 1;
    if(line[start] == '"')
        d_quote = 1;
    if(d_quote || s_quote)
        (*index)++;
    while(line[*index] != '\0')
    {
        if(line[*index] == '\'' && d_quote != 1)
        {
            if(s_quote == 0)
                s_quote = 1;
			else if(is_space(line[*index + 1]) && (s_quote != 1) && (line[*index] != '\0'))
				s_quote = 0;
            else
				s_quote = 0;
        }
        else if(line[*index] == '"' && s_quote != 1)
        {
            if(d_quote == 0)
                d_quote = 1;
			else if(is_space(line[*index + 1]) && (d_quote == 0))
				d_quote = 0;
            else
				d_quote = 0;
        }
        if(s_quote == 0 && d_quote == 0)
        {
            if(is_space(line[*index]) || is_metachar(line[*index]))
                return ;
        }
        (*index) += 1;
    }
}

t_token_type classify_tokens()
{
	return(WORD);
}

t_token_type classify_meta_tokens(char *line,size_t *index)
{
	if((line[*index] == '<' && line[*index + 1] == '<'))
	{
		(*index) += 2;
		return (HEREDOC);
	}
	else if((line[*index] == '>' && line[*index + 1] == '>'))
	{
		(*index) += 2;
		return (APPEND);
	}
	else if(line[*index] == '<')
	{
		(*index)++;
		return(INPUT);
	}
	else if(line[*index] == '>')
	{
		(*index)++;
		return(OUTPUT);
	}
	else if(line[*index] == '|')
	{
		(*index)++;
		return(PIPE);
	}
	return(WORD);
}

t_token_list	*create_token_node(t_token_type type, char *content)
{
	t_token_list	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (!new_node)
	{
		perror("create_token_node");
		return (NULL);
	}
	new_node->type = type;
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

t_token_list	*create_new_token(char *line,size_t *index)
{
	t_token_type type;
	char *token;
	size_t start;

	start = *index;
	if(is_metachar(line[*index]))
	{
		//meta_token_end(line,index);
		type = classify_meta_tokens(line,index);//listの使い方がまだはっきりしない。第二引数にこれをぶちこんでいいのか。型はあっているが。
		token = ft_substr(line,start,*index - start);
		if(!token)
			return(NULL);
		return(create_token_node(type,token));
	}
	else
	{
    	token_end(line,index);
		token = ft_substr(line,start,*index - start);
		if(!token)
			return(NULL);
		return(create_token_node(WORD,token));
	}
}

static void	append_token_node(t_token_list **list_head, t_token_list *new_node)
{
	t_token_list	*last;

	if (!list_head || !new_node)
		return ;
	if (!*list_head)
		*list_head = new_node;
	else
	{
		last = *list_head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
}

// t_token_list *token_new(t_token_type type, char *content)
// {
// 	t_token_list *node;

// 	node = malloc(sizeof(*node));
// 	if(!node)
// 		return(NULL);
// 	node->type = type;
// 	node->content = content;
// 	node->next = NULL;
// 	return(node);
// }

t_token_list    *create_token_list(char *line)
{
    t_token_list    *token_list;
	t_token_list	*new_node;
    size_t          index;

    token_list = NULL;
    index = 0;
    while(line[index] != '\0')
    {
        while(line[index] && is_space(line[index]))
            index++;
        if(line[index] == '\0')
        {
            free(line);
            break;
        }
		new_node = create_new_token(line,&index);
		if(!new_node)
		{
			break;
		}
		append_token_node(&token_list,new_node);
    }
	return(token_list);
}
