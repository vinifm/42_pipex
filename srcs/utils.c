/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:23:54 by viferrei          #+#    #+#             */
/*   Updated: 2022/04/07 13:43:00 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	perror_exit(char *error_msg)
{
	perror(error_msg);
	exit(1);
}

char	*ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	char	*aux;
	char	*str;

	aux = ft_strjoin(s1, s2);
	str = ft_strjoin(aux, s3);
	free(aux);
	return (str);
}
