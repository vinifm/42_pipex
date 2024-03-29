/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:23:54 by viferrei          #+#    #+#             */
/*   Updated: 2022/04/26 22:00:24 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	perror_exit(char *error_msg, int exit_code)
{
	perror(error_msg);
	exit(exit_code);
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

t_split	*init_split(void)
{
	t_split	*split;

	split = malloc(sizeof(t_split));
	if (!split)
		perror("split init");
	split->arr = NULL;
	split->index = 0;
	split->i = 0;
	split->start = 0;
	return (split);
}

void	free_cmds(t_split *split, char **path_dirs)
{
	int	i;

	i = 0;
	while (path_dirs[i])
		free(path_dirs[i++]);
	free(path_dirs);
	i = 0;
	while (split->arr[i])
		free(split->arr[i++]);
	free(split->arr);
	free(split);
}
