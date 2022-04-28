/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:05:35 by viferrei          #+#    #+#             */
/*   Updated: 2022/04/28 18:15:42 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft/libft.h"

# define READ	0
# define WRITE	1

typedef struct s_split {
	char	**arr;
	size_t	index;
	size_t	i;
	size_t	start;
}				t_split;

// pipex.c
int		open_file(char *file, int mode);
void	pipe_and_fork(char argv[], char **envp, int fd[2]);
void	exec_cmd(char *command, char **envp);
char	*get_cmd_path(t_split *split, char *command, char **envp);

// utils.c
void	perror_exit(char *error_msg, int exit_code);
char	*ft_strjoin3(char const *s1, char const *s2, char const *s3);
t_split	*init_split(void);
void	free_cmds(t_split *split, char **path_dirs);
void	ft_infile(int infile, int fd[2], char argv[], char **envp);

// split.c
char	**ft_split_cmd(t_split *split, char const *s, char c);
size_t	ft_split_cmdcount(char const *s, char c);
void	split_quotes(t_split *split, char const *s, char c);
size_t	jump_quotes(char const *s, size_t i);
void	jump_space(t_split *split, char const *s, char c);

#endif
