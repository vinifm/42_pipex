/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:14:47 by viferrei          #+#    #+#             */
/*   Updated: 2022/04/26 14:13:15 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	**ft_split_cmd(t_split *split, char const *s, char c)
{
	split->arr = (char **) malloc(((ft_split_cmdcount(s, c)) + 1) \
		* sizeof(*split));
	if (!split->arr)
		perror("split array");
	while (s[split->i])
	{
		jump_space(split, s, c);
		while (s[split->i] && s[split->i] != c)
		{
			split_quotes(split, s, c);
			split->i++;
		}
		if (s[split->i - 1] != c && s[split->i - 1] != 34
			&& s[split->i - 1] != 39)
			split->arr[split->index++] = ft_substr(&s[split->start], 0, \
				split->i - split->start);
	}
	split->arr[split->index] = 0;
	return (split->arr);
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
				i = jump_quotes(s, i);
				i++;
			}
		}
		else
			i++;
	}
	return (count);
}

void	split_quotes(t_split *split, char const *s, char c)
{
	if (s[split->i] && (s[split->i] == 34 || s[split->i] == 39))
	{
		split->i = (jump_quotes(s, split->i) + 1);
		split->arr[split->index++] = ft_substr(&s[split->start], 1, \
		split->i - split->start - 2);
		jump_space(split, s, c);
		split->i--;
	}
}

size_t	jump_quotes(char const *s, size_t i)
{
	if (s[i] == 34 || s[i] == 39)
	{
		i++;
		while (s[i] != 34 && s[i] != 39)
			i++;
	}
	return (i);
}

void	jump_space(t_split *split, char const *s, char c)
{
	while (s[split->i] && s[split->i] == c)
			split->i++;
	split->start = split->i;
}
