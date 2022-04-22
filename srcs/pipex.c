/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:04:13 by viferrei          #+#    #+#             */
/*   Updated: 2022/04/22 19:09:10 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static int	open_file(char *file, int mode);

/* dup2 redirects stdin (fd == 0) and stdout (fd == 1) to infile and outfile */
int	main(int argc, char **argv, char **envp)
{
	int	infile;
	int	outfile;

	size_t n = ft_split_cmdcount("tr 'hey ' x", ' ');
	printf("%zu\n", n);

/*
	int i = 0;
	while (argv[i])
	{
		ft_printf("argv[%d]: %s\n", i, argv[i]);
		i++;
	}
*/

	if (argc != 5)
		perror_exit("Invalid number of arguments");
	else
	{
		infile = open_file(argv[1], READ);
		outfile = open_file(argv[argc - 1], WRITE);
		if (infile == -1 || outfile == -1)
			perror_exit("open_file:");
		dup2(infile, STDIN_FILENO);
		//dup2(outfile, STDOUT_FILENO);
		pipe_and_fork(argv, envp);
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
		if (access(file, F_OK))
			perror_exit("input file");
		return (open(file, O_RDONLY));
	}
	else if (mode == WRITE)
		return (open(file, O_CREAT | O_WRONLY | O_TRUNC, 0777));
	return (-1);
}

/*	pipe_and_fork: Create a pipe and fork the process. On the child process,
	close the read end of the pipe and redirect STDOUT to the writing end; STDIN
	remains infile. On the parent process, close the writing end and redirect
	STDIN to the pipe fd; since it's piped, STDOUT remains outfile.
*/

void	pipe_and_fork(char **argv, char **envp)
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
		exec_cmd(argv[2], envp);
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(-1, NULL, WNOHANG);
		exec_cmd(argv[3], envp);
	}
}

/*	exec_cmd:
*/

void	exec_cmd(char *command, char **envp)
{
	char	**cmd_args;
	char	**delim_args;
	char	*cmd_path;
	size_t	i;
	int		delim;

	i = 0;
	delim = find_delimiter(command);
	if (delim)
	{
		delim_args = ft_split(command, delim);
		while(delim_args[i])
		{
			cmd_args = ft_split(delim_args[i], ' ');
			i++;
		}
	}
	else
		cmd_args = ft_split(command, ' ');

	int j = 0;
	while (cmd_args[j])
	{
		ft_printf("cmd_args[%d]: %s\n", j, cmd_args[j]);
		j++;
	}
	ft_printf("\n");

	cmd_path = get_cmd_path(cmd_args[0], envp);
	//execve(cmd_path, cmd_args, envp);
}

/* 	get_cmd_path: gets PATH from envp and iterate through searchable directories
	returning the appropriate one.
*/

char	*get_cmd_path(char *command, char **envp)
{
	int		i;
	char	**path_dirs;
	char	*full_cmd;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	path_dirs = ft_split(ft_strchr(envp[i], envp[i][5]), ':');
	i = 0;
	while (path_dirs[i])
	{
		full_cmd = ft_strjoin3(path_dirs[i], "/", command);
		if (!(access(full_cmd, F_OK | X_OK)))
			return(full_cmd);
		free(full_cmd);
		i++;
	}
	write(2, "Invalid command\n", 16);
	exit(1);
}
