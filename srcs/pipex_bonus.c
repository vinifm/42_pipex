/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:04:13 by viferrei          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/04/28 18:12:35 by viferrei         ###   ########.fr       */
=======
/*   Updated: 2022/09/14 19:57:19 by viferrei         ###   ########.fr       */
>>>>>>> old-commit
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	int	infile;
	int	outfile;
	int	fd[2];
	int	i;

	i = 2;
	if (argc < 5)
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
		if (infile == -1)
			i++;
		while (i < argc - 2)
			ft_infile(infile, fd, argv[i++], envp);
		exec_cmd(argv[i], envp);
	}
	return (0);
}

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

void	pipe_and_fork(char argv[], char **envp, int fd[2])
{
	pid_t	pid;
<<<<<<< HEAD

=======
	int		fd[2];
ß
	if (pipe(fd) == -1)
		perror_exit("pipe", 1);
>>>>>>> old-commit
	pid = fork();
	if (pid == -1)
		perror_exit("fork", 1);ß
	if (pid == 0)ß
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exec_cmd(argv, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
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
