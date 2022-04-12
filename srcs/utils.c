/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:23:54 by viferrei          #+#    #+#             */
/*   Updated: 2022/04/12 18:07:42 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	perror_exit(char *error_msg)
{
	perror(error_msg);
	exit(1);
}

char	*ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	char	*aux;
	char	*str;

	aux = ft_strjoin(s1, s2);
	str = ft_strjoin(aux, s3);
	free(aux);
	return (str);
}

size_t	ft_split_cmd_count(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (1)
	{
		if (s[i] == 0)
			break;
		if (*s != c)
		{
			count++;
			while (*s != '\0' && *s != c)
				s++;
		}
		else
			s++;
	}
	return (count);
}

char	**ft_split_cmd(char const *s, char c)
{
	size_t		len;
	size_t		index;
	const char	*start;
	char		**split;

	split = (char **) malloc(((ft_split_count(s, c)) + 1) * sizeof(*split));
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
