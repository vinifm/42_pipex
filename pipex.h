/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:05:35 by viferrei          #+#    #+#             */
/*   Updated: 2022/04/26 14:14:53 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/types.h>
# include <fcntl.h>
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
void	pipe_and_fork(char **argv, char **envp);
void	exec_cmd(char *command, char **envp);
char	*get_cmd_path(char *command, char **envp);

// utils.c
void	perror_exit(char *error_msg, int exit_code);
char	*ft_strjoin3(char const *s1, char const *s2, char const *s3);
t_split	*init_split(void);

// split.c
char	**ft_split_cmd(t_split *split, char const *s, char c);
size_t	ft_split_cmdcount(char const *s, char c);
void	split_quotes(t_split *split, char const *s, char c);
size_t	jump_quotes(char const *s, size_t i);
void	jump_space(t_split *split, char const *s, char c);

#endif
