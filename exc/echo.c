/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajdoub <mmajdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:16:10 by mmajdoub          #+#    #+#             */
/*   Updated: 2023/06/07 10:26:34 by mmajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_write_in_fd(char **str, int fd)
{
	int	i;

	i = 1;
	if (str == NULL)
		return ;
	while (str[i])
	{
		ft_putstr_fd(str[i], fd);
		i++;
	}
}

void	ft_echo(t_parc *head)
{
	int	fd;

	fd = -1;
	g_exitstatus = 0;
	fd = ft_open_outfile(head);
	if (fd == -1)
	{
		ft_write_in_fd(head->arg, 1);
		printf("\n");
	}
	else
		ft_write_in_fd(head->arg, fd);
}
