/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:04:13 by viferrei          #+#    #+#             */
/*   Updated: 2022/04/28 16:55:45 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/* dup2 redirects stdin (fd == 0) and stdout (fd == 1) to infile and outfile */
int	main(int argc, char **argv, char **envp)
{
	int	infile;
	int	outfile;
	int	fd[2];

	if (argc != 5)
		perror_exit("Invalid number of arguments", 1);
	else
	{
		if (pipe(fd) == -1)
			perror_exit("pipe in read_command", 1);
		infile = open_file(argv[1], READ);
		outfile = open_file(argv[argc - 1], WRITE);
		if (outfile == -1)
			perror_exit("outfile", 1);
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
		ft_infile(infile, fd, argv, envp);
		exec_cmd(argv[3], envp);
	}
	return (0);
}

/*	open_file opens the input and output file (or creates it if need be).
	The input file is opened with reading permission. The output file is
	opened with writing permission or created with 0777 permissions if
	nonexistent (O_CREAT).
*/

int	open_file(char *file, int mode)
{
	if (mode == READ)
	{
		if (access(file, F_OK))
		{
			write(2, file, ft_strlen(file));
			write(2, ": No such file or directory\n", 29);
		}
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

void	pipe_and_fork(char argv[], char **envp, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror_exit("fork in read_command", 1);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		exec_cmd(argv, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(-1, NULL, 0);
	}
}

void	exec_cmd(char *command, char **envp)
{
	char	**cmd_args;
	char	*cmd_path;
	t_split	*split;

	split = init_split();
	cmd_args = ft_split_cmd(split, command, ' ');
	cmd_path = get_cmd_path(split, cmd_args[0], envp);
	execve(cmd_path, cmd_args, envp);
}

/* 	get_cmd_path: gets PATH from envp and iterate through searchable directories
	returning the appropriate one.
*/

char	*get_cmd_path(t_split *split, char *command, char **envp)
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
			return (full_cmd);
		free(full_cmd);
		i++;
	}
	write(2, command, ft_strlen(command));
	write(2, ": command not found\n", 21);
	free_cmds(split, path_dirs);
	exit(127);
}
