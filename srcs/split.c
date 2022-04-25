/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:14:47 by viferrei          #+#    #+#             */
/*   Updated: 2022/04/25 14:58:40 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_split	*init_split(char const *s, char c)
{
	t_split	*split;

	split = malloc(sizeof(t_split));
	split->arr = (char **) malloc(((ft_split_cmdcount(s, c)) + 1) \
		* sizeof(*split));;
	if (!split || !split->arr)
		perror("split allocation");
	split->index = 0;
	split->i = 0;
	split->start = 0;

	return(split);
}

static size_t	jump_delimiter(char const *s, size_t i)
{
	if (s[i] == 34 || s[i] == 39)
	{
		i++;
		while (s[i] != 34 && s[i] != 39)
			i++;
	}
	return (i);
}

static void	jump_space(t_split *split, char const *s, char c)
{
	while (s[split->i] && s[split->i] == c)
			split->i++;
	split->start = split->i;
}

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


char	**ft_split_cmd(char const *s, char c)
{
	t_split		*split;

	split = init_split(s, c);
	while (s[split->i])
	{
		jump_space(split, s, c);
		while (s[split->i] && s[split->i] != c)
		{
			if (s[split->i] && (s[split->i] == 34 || s[split->i] == 39))
			{
				split->i = (jump_delimiter(s, split->i) + 1);
				split->arr[split->index++] = ft_substr(&s[split->start], 0, \
				split->i - split->start);
				jump_space(split, s, c);
				split->i--;
			}
			split->i++;
		}
		if ((s[split->i - 1] != c))
			split->arr[split->index++] = ft_substr(&s[split->start], 0, \
				split->i - split->start);
	}
	split->arr[split->index] = 0;
	return (split->arr);
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
