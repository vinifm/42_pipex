/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:28:28 by viferrei          #+#    #+#             */
/*   Updated: 2022/03/21 16:24:48 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(void)
{
	int	fd[2];
	pid_t	pid;

	if (pipe(fd) < 0)
	{
		perror("pipe");
		exit(1);
	}
	if ((pid = fork()) < 0)
	{
		perror("fork");
		exit(1);
	}
	if (pid > 0)
	{
		close(fd[0]);
		char	str[BUFFER] = "Aprendi a usar pipes em c?";
		ft_printf("string enviada pelo pai: %s\n", str);

		write(fd[1], str, BUFFER);
		exit(0);
	}
	else
	{
		close(fd[1]);
		char	str_son[BUFFER];
		read(fd[0], str_son, BUFFER);
		ft_printf("str_son: %s\n", str_son);
	}
	return (0);
}
