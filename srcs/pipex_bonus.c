/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:04:13 by viferrei          #+#    #+#             */
/*   Updated: 2022/04/26 14:15:50 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	int	infile;
	int	outfile;
	int	i;

	i = 2;
	if (argc < 5)
		perror_exit("Invalid number of arguments", 1);
	else
	{
		infile = open_file(argv[1], READ);
		outfile = open_file(argv[argc - 1], WRITE);
		if (infile == -1)
			perror_exit("infile", 0);
		if (outfile == -1)
			perror_exit("outfile", 1);
		dup2(infile, STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		while (i < argc - 2)
			pipe_and_fork(argv[i++], envp);
		exec_cmd(argv[i], envp);
	}
	return (0);
}

int	open_file(char *file, int mode)
{
	if (mode == READ)
	{
		if (access(file, F_OK))
			perror_exit("input file", 1);
		return (open(file, O_RDONLY));
	}
	else if (mode == WRITE)
		return (open(file, O_CREAT | O_WRONLY | O_TRUNC, 0777));
	return (-1);
}

void	pipe_and_fork(char argv[], char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		perror_exit("pipe in read_command", 1);
	pid = fork();
	if (pid == -1)
		perror_exit("fork in read_command", 1);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		exec_cmd(argv, envp);
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(-1, NULL, WNOHANG);
	}
}

void	exec_cmd(char *command, char **envp)
{
	char	**cmd_args;
	char	*cmd_path;
	t_split	*split;

	split = init_split();
	cmd_args = ft_split_cmd(split, command, ' ');
	free(split);
	cmd_path = get_cmd_path(cmd_args[0], envp);
	execve(cmd_path, cmd_args, envp);
}

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
			return (full_cmd);
		free(full_cmd);
		i++;
	}
	write(2, command, ft_strlen(command));
	write(2, ": command not found\n", 21);
	exit(127);
}
