/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:04:13 by viferrei          #+#    #+#             */
/*   Updated: 2022/04/05 18:32:44 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static int	open_file(char *file, int mode);

/* dup2 redirects stdin (fd == 0) and stdout (fd == 1) to infile and outfile */
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
		//dup2(infile, STDIN_FILENO);
		//dup2(outfile, STDOUT_FILENO);
		pipe_and_fork(argv[i]);
	}
	return (0);
}

/*	open_file opens the input and output file (or creates it if need be).
	The input file is opened with reading permission. The output file is
	opened with writing permission or created with 0777 permissions if
	nonexistent (O_CREAT).
*/
static int	open_file(char *file, int mode)
{
	if (mode == READ)
	{
		if(access(file, F_OK))
			perror_exit("input file");
		return (open(file, O_RDONLY));
	}
	else if (mode == WRITE)
		return (open(file, O_WRONLY | O_CREAT, 0777));
	return(-1);
}

/*	pipe_and_fork: Create a pipe and fork the process. On the parent process,
	close the read end of the pipe and redirect STDOUT to the writing end. On
	the child process, close the writing end and redirect STDIN to the reading
	end.
*/
void	pipe_and_fork(char *command)
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
		//dup2(fd[1], STDOUT_FILENO);
		parse_command(command);
	}
	else
	{
		close(fd[1]);
		//dup2(fd[0], STDIN_FILENO);
		waitpid(-1, NULL, WNOHANG);
	}
}

/*	parse_command:
*/

void	parse_command(char *command)
{
	printf("command: %s\n", command);
}

void	perror_exit(char *error_msg)
{
	perror(error_msg);
	exit(1);
}
