/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:14:47 by viferrei          #+#    #+#             */
/*   Updated: 2022/04/22 19:09:36 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

size_t	ft_split_cmdcount(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (1)
	{
		if (s[i] == 0)
			break ;
		if (s[i] != c)
		{
			count++;
			while (s[i] != 0 && s[i] != c)
			{
				i = jump_delimiter(s, i);
				i++;
			}
		}
		else
			i++;
	}
	return (count);
}

/*	find_delimiter: if there's a ' or " in the string, continue to read until
	the end of the string and return the index of the end of it.
*/
size_t	jump_delimiter(char const *s, size_t i)
{
	if (s[i] == 34 || s[i] == 39)
	{
		i++;
		while (s[i] != 34 && s[i] != 39)
			i++;
	}
	return (i);
}


// SPLIT COM ASPAS PRIMEIRO DEPOIS ESPAÇO
char	**ft_split_cmd(char const *s, char c)
{
	size_t		index;
	size_t		i;
	size_t		start;
	char		**split;

	split = (char **) malloc(((ft_split_cmdcount(s, c)) + 1) * sizeof(*split));
	if (!split)
		return (0);
	index = 0;
	i = 0;
	while (s[i] != 0)
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
		{
			// i = split_delimiter(s, i, split);
			i++;
		}
		if (s[i - 1] != c)
			split[index++] = ft_substr(&s[start], 0, i - start);
	}
	split[index] = 0;
	return (split);
}

/*	find_delimiter: reads the string and returns 34 if " is found or 39 if ' is
	found; or 0 if none is found.
*/
int	find_delimiter(char *command)
{
	size_t	i;
	i = 0;
	while (command[i] && command[i] != 34 && command[i] != 39)
		i++;
	if (command[i] == 34)
		return(34);
	if (command[i] == 39)
		return(39);
	return(0);
}

// // SPLIT PERCORRENDO ATE ACHAR ASPAS
// char	**ft_split_cmd(char const *s, char c)
// {
// 	size_t		index;
// 	size_t		i;
// 	size_t		start;
// 	char		**split;

// 	split = (char **) malloc(((ft_split_cmdcount(s, c)) + 1) * sizeof(*split));
// 	if (!split)
// 		return (0);
// 	index = 0;
// 	i = 0;
// 	while (s[i] != 0)
// 	{
// 		while (s[i] && s[i] == c)
// 			i++;
// 		start = i;
// 		while (s[i] && s[i] != c)
// 		{
// 			// i = split_delimiter(s, i, split);
// 			i++;
// 		}
// 		if (s[i - 1] != c)
// 			split[index++] = ft_substr(&s[start], 0, i - start);
// 	}
// 	split[index] = 0;
// 	return (split);
// }

// size_t	split_delimiter(char const *s, size_t i, char **split)
// {
// 	size_t	start;

// 	if (s[i] == 34 || s[i] == 39)
// 	{
// 		i++;
// 		while (s[i] != 34 && s[i] != 39)
// 			i++;
// 	}
// 	split[index++] = ft_substr(start + 1, 0, i - start - 1);
// 	return (i);
// }
