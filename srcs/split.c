/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:14:47 by viferrei          #+#    #+#             */
/*   Updated: 2022/04/22 15:09:40 by viferrei         ###   ########.fr       */
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
			break;
		if (s[i] != c)
		{
			count++;
			while (s[i] != 0 && s[i] != c)
			{
				i = find_delimiter(s, i);
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
size_t	find_delimiter(char const *s, size_t i)
{
	if (s[i] == 34 || s[i] == 39)
	{
		i++;
		while (s[i] != 34 && s[i] != 39)
			i++;
	}
	return (i);
}

char	**ft_split_cmd(char const *s, char c)
{
	size_t		len;
	size_t		index;
	const char	*start;
	char		**split;

	split = (char **) malloc(((ft_split_cmdcount(s, c)) + 1) * sizeof(*split));
	if (!split)
		return (0);
	index = 0;
	while (*s != '\0')
	{
		while (*s && *s == c)
			s++;
		start = s;
		len = 0;
		while (*s && *s != c)
		{
			s++;
			len++;
		}
		if (*(s - 1) != c)
			split[index++] = ft_substr(start, 0, len);
	}
	split[index] = 0;
	return (split);
}
