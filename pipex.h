/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:05:35 by viferrei          #+#    #+#             */
/*   Updated: 2022/04/06 18:24:12 by viferrei         ###   ########.fr       */
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

// STRUCTS

typedef struct	s_pipe
{

}				t_pipe;

// pipex.c
void	pipe_and_fork(char *command, char **envp);
void	perror_exit(char *error_msg);
void	exec_cmd(char *command, char **envp);
char	*get_cmd_path(char *command, char **envp);

#endif
