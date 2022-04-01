/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:04:13 by viferrei          #+#    #+#             */
/*   Updated: 2022/04/01 18:09:40 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static int	open_file(char *path, int mode);

/* dup2 redirects stdin (fd == 1) and stdout (fd == 2) to infile and outfile */
int	main(int argc, char **argv)
{
	int	infile;
	int	outfile;
	int	i;

	i = 1;
	if (argc != 5)
		perror_exit("Invalid number of arguments");
	else
	{
		infile = open_file(argv[1], READ);
		outfile = open_file(argv[argc - 1], WRITE);
		if (infile == -1 || outfile == -1)
			perror_exit("open_file:");
		dup2(infile, 1);
		dup2(outfile, 2);
		read_command(argv[i++]);
	}
	return (0);
}

/*	open_file opens the input and output file (or creates it if need be).
	The input file is opened with reading permission. The output file is
	opened with writing permission or created with 0777 permissions if
	nonexistent (O_CREAT).
*/
static int	open_file(char *path, int mode)
{
	if (mode == READ)
	{
		if(access(path, F_OK))
			perror_exit("input file");
		return (open(path, O_RDONLY));
	}
	else if (mode == WRITE)
		return (open(path, O_WRONLY | O_CREAT, 0777));
	return(-1);
}

/* read_command:
*/
void	read_command(char *command)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		perror_exit("pipe in read_command");
	pid = fork();
	if (pid == -1)
		perror_exit("fork in read_command");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		waitpid(-1, NULL, WNOHANG); // why?
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);

	}


}

void	perror_exit(char *error_msg)
{
	perror(error_msg);
	exit(1);
}
