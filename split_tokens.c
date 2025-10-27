/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotadashirui <kotadashirui@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 10:41:03 by rufurush          #+#    #+#             */
/*   Updated: 2025/10/13 21:30:26 by kotadashiru      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	token_count(char *line)
{
	int		state;
	int		count;
	int		i;
	char	ch;

	enum
	{
		WS = 0,
		SQ = 1,
		DQ = 2,
		WORD = 3
	};
	state = WS;
	count = 0;
	i = 0;
	while (line[i] != '\0')
	{
		ch = line[i];
		if ((state != SQ && state != DQ) && (ch == '|' || ch == '<'
				|| ch == '>'))
		{
			if (state == WORD)
				state = WS;
			if (ch == '<' && line[i + 1] && line[i + 1] == '<')
			{
				count++;
				i += 2;
				continue ;
			}
			if (ch == '>' && line[i + 1] && line[i + 1] == '>')
			{
				count++;
				i += 2;
				continue ;
			}
			count++;
			i++;
			continue ;
		}
		if (state == WS || state == WORD)
		{
			if (ch == '\'')
			{
				if (state == WS)
					count++;
				state = SQ;
				i++;
				continue ;
			}
			if (ch == '\"')
			{
				if (state == WS)
					count++;
				state = DQ;
				i++;
				continue ;
			}
		}
		if (state == SQ)
		{
			if (ch == '\'')
				state = WORD;
			i++;
			continue ;
		}
		if (state == DQ)
		{
			if (ch == '\"')
				state = WORD;
			i++;
			continue ;
		}
		if (ch == ' ' || ch == '\t')
		{
			if (state == WORD)
				state = WS;
			i++;
			continue ;
		}
		if (state == WS)
		{
			count++;
			state = WORD;
		}
		i++;
	}
	return (count);
}

char	*ft_strdup_token(char *line, int start, int end)
{
	char	*result;
	int		i;

	i = 0;
	result = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!result)
		return (NULL);
	while (end >= start)
	{
		result[i] = line[start];
		i++;
		start++;
	}
	result[i] = '\0';
	return (result);
}

char	**ft_fill_tokens(char **result, char *line, int tokens)
{
	int		i;
	int		state;
	int		building;
	int		token_start;
	int		index;
	char	ch;

	enum
	{
		WS = 0,
		SQ = 1,
		DQ = 2,
		WORD = 3
	};
	i = 0;
	state = WS;
	building = 0;
	token_start = 0;
	index = 0;
	(void)tokens;
	while (line[i] != '\0')
	{
		ch = line[i];
		if ((state != SQ && state != DQ) && (ch == '|' || ch == '<'
				|| ch == '>'))
		{
			if (building)
			{
				result[index++] = ft_strdup_token(line, token_start, i);
				building = 0;
				state = WS;
			}
			if (ch == '<' && line[i + 1] == '<')
			{
				result[index++] = ft_strdup_token(line, i, i + 2);
				i += 2;
				continue ;
			}
			if (ch == '>' && line[i + 1] == '>')
			{
				result[index++] = ft_strdup_token(line, i, i + 2);
				i += 2;
				continue ;
			}
			result[index++] = ft_strdup_token(line, i, i + 1);
			i++;
			continue ;
		}
		if (state == WS || state == WORD)
		{
			if (ch == '\'')
			{
				if (!building)
				{
					building = 1;
					token_start = i;
				}
				state = SQ;
				i++;
				continue ;
			}
			if (ch == '\"')
			{
				if (!building)
				{
					building = 1;
					token_start = i;
				}
				state = DQ;
				i++;
				continue ;
			}
		}
		if (state == SQ)
		{
			if (ch == '\'')
				state = WORD;
			i++;
			continue ;
		}
		if (state == DQ)
		{
			if (ch == '\"')
				state = WORD;
			i++;
			continue ;
		}
		if (ch == ' ' || ch == '\t')
		{
			if (building)
			{
				result[index++] = ft_strdup_token(line, token_start, i);
				building = 0;
				state = WS;
			}
			i++;
			continue ;
		}
		if (!building)
		{
			building = 1;
			state = WORD;
			token_start = i;
		}
		i++;
	}
	if (state == SQ || state == DQ)
	{
		result[0] = NULL;
		return (NULL);
	}
	if (building)
		result[index++] = ft_strdup_token(line, token_start, i);
	result[index] = NULL;
	return (result);
}

char	**split_token(char *line)
{
	int		tokens;
	char	**result;

	if (!line)
		return (NULL);
	tokens = token_count(line);
	result = (char **)malloc(sizeof(char *) * (tokens + 1));
	if (!result)
		return (NULL);
	if (!ft_fill_tokens(result, line, tokens))
		return (NULL);
	result[tokens] = NULL;
	return (result);
}

// int main()
// {
// 	char *line = "echo 'Hello World' | grep World > output.txt";
// 	char **result = split_token(line);
// 	int i = 0;

// 	while(result[i] != NULL)
// 	{
// 		printf("%s\n",result[i]);
// 		i++;
// 	}
// }

// int	main(void)
// {
// 	char	*line;
// 	int		result;

// 	//line = "echo 'Hello World' | grep World > output.txt";
// 	// line = "a|b";
// 	// line = "cmd>out";
// 	//line = "cat <<EOF | grep foo";
// 	//line = "echo \"x$HOME\"y|wc";
// 	//line = "echo a>>b c<<d | e>f";
// 	//line = "echo \"$HOME\"";
// 	//line = "\"a\"' b '\"c'\"";
// 	//line = "a><<b>>>c|<<d>e||f";
// 	//line = "cat<<EOF<<'X'<<\"Y\"<<Z";
// 	line = "cat <<EOF<<EOF2|<<'E F'";
// 	result = token_count(line);
// 	printf("%d", result);
// }

// int	token_count(char *line)
// {
// 	int	i;
// 	int	token_count;
// 	int	state;
// 	int	first_word;

// 	// SQ = 1;
// 	// WQ = 2;
// 	// WS = 0;
// 	// WORD = 3;
// 	i = 0;
// 	token_count = 0;
// 	first_word = 1;
// 	while (line[i] != '\0')
// 	{
// 		if (line[i] == ' ' || line[i] == '\t')
// 			state = 0;
// 		else if (line[i] == '\'')
// 			state = 1;
// 		else if (line[i] == '\"')
// 			state = 2;
// 		else
// 			state = 3;

// 		if (line[i] != '\0' && (state != 1 && state != 2) && (line[i] == '|'
// 				|| line[i] == '<' || line[i] == '>'))
// 		{
// 			if ((line[i] == '<' && line[i + 1] == '<') || (line[i] == '>'
// 					&& line[i + 1] == '>'))
// 			{
// 				token_count++;
// 				i += 2;
// 				continue ;
// 			}
// 			else
// 			{
// 				token_count++;
// 				i++;
// 				continue ;
// 			}
// 		}
// 		if ((line[i] == ' ' || line[i] == '\t') && line[i] != '\0'
// 			&& (line[i] != '|' && line[i] != '<' && line[i] != '>'))
// 		{
// 			if (line[i] == ' ' || line[i] == '\t')
// 				state = 0;
// 			else if (line[i] == '\'')
// 				state = 1;
// 			else if (line[i] == '\"')
// 				state = 2;
// 			else
// 				state = 3;
// 			if (state == 0 || state == 3)
// 			{
// 				if ((line[i + 1] == '\'') && state == 0)
// 					state = 1;
// 				else if (line[i + 1] == '\"' && state == 0)
// 					state = 2;
// 			}
// 			i++;
// 			continue ;
// 		}
// 		if (state == 1)
// 		{
// 			if (line[i] == '\'')
// 				state = 3;
// 			i++;
// 			continue ;
// 		}
// 		if (state == 2)
// 		{
// 			if (line[i] == '\"')
// 				state = 3;
// 			i++;
// 			continue ;
// 		}
// 		if (state == 0)
// 		{
// 			i++;
// 			continue ;
// 		}
// 		if (state == 3)
// 		{
// 			if (first_word == 1)
// 			{
// 				token_count++;
// 				// printf("i=%d%c\n",token_count,line[i]);
// 				state = 3;
// 			}
// 			first_word = 0;
// 			if (line[i] != '\0' && line[i] != ' ' && line[i] != '\t'
// 				&& line[i] != '|' && line[i] != '<' && line[i] != '>')
// 			{
// 				i++;
// 				continue ;
// 			}
// 		}
// 	}
// 	return (token_count);
// }

// int	main(void)
// {
// 	char	*line;
// 	int		result;

// 	line = "echo 'Hello World' | grep World > output.txt";
// 	result = token_count(line);
// 	printf("%d", result);
// }
