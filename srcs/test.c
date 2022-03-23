/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 17:19:57 by viferrei          #+#    #+#             */
/*   Updated: 2022/03/23 16:59:57 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int main(void)
{
	pid_t pid;
	pid = fork();

	if (pid == -1)
		return (1);

// child process
	if (pid == 0)
		ft_printf("hello from child\n");
		//execlp("ping", "ping", "-c", "3", "google.com", NULL);
// parent process
	else
	{
		ft_printf("hello from parent\n");
		//wait(NULL);
		//ft_printf("child has terminated\n");
	}
	return (0);
}
