/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:04:13 by viferrei          #+#    #+#             */
/*   Updated: 2022/03/30 18:09:41 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static int	open_file(char *path, int mode);

/* dup2 redirects stdin (fd == 1) and stdout (fd == 2) to fdin and fddout */
int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	fdin;
	int	fdout;

	if (argc != 5)
	{
		perror("Error: invalid number of arguments");
		exit(1);
	}
	else
	{
		open_file(argv[1], READ);
		dup2(fdin, 1);
		dup2(fdout, 2);
	}
	return (0);
}

static int	open_file(char *path, int mode)
{
	if (mode == READ)
	{
		if(access(path, F_OK))
		{
			perror("Invalid file");
			exit(1);
		}
		return (open(path, O_RDONLY));
	}
	else if (mode == WRITE)
	{

	}
}
