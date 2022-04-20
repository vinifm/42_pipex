/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:05:35 by viferrei          #+#    #+#             */
/*   Updated: 2022/04/20 15:44:32 by viferrei         ###   ########.fr       */
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

// pipex.c
void	pipe_and_fork(char **argv, char **envp);
void	exec_cmd(char *command, char **envp);
char	*get_cmd_path(char *command, char **envp);

// utils.c
void	perror_exit(char *error_msg);
char	*ft_strjoin3(char const *s1, char const *s2, char const *s3);
char	**ft_double_split(char const *s, char c, char b);

// pipex.h
size_t	ft_split_cmdcount(char const *s, char c);
size_t	find_delimiter(char const *s, size_t i);
char	**ft_split_cmd(char const *s, char c);

#endif
