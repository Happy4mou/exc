/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajdoub <mmajdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 13:29:20 by mmajdoub          #+#    #+#             */
/*   Updated: 2023/06/10 08:49:44 by mmajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_openinfile_helper(char *ptr, int eropin)
{
    			eropin = open(ptr, O_RDONLY, 0644);
			if (eropin == -1)
				(write(2, "OPEN INFILE ERROR ! \n", 22), exit(1));
}

int	ft_open_infile(t_parc *all, t_heredoc *idfd)
{
	int	eropin;
	int	i;

	eropin = -1;
	i = 0;
	while (all->name[i])
	{
		if (all->tab[i] == 1)
            ft_openinfile_helper(all->name[i], eropin);
		else if (all->tab[i] == 4)
		{
			eropin = idfd->data;
		}
		else if (all->tab[i] == 3)
		{
			eropin = open(all->name[i], O_RDONLY | O_APPEND, 0644);
			if (eropin == -1)
				(write(2, "OPEN APPEND ERROR ! \n", 22), exit(1));
		}
		i++;
	}
	return (eropin);
}

int	ft_open_outfile(t_parc *all)
{
	int	eropout;
	int	i;

	eropout = -1;
	i = 0;
	while (all->name[i])
	{
		if (all->tab[i] == 2)
		{
			eropout = open(all->name[i], O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (eropout == -1)
				(write(2, "OPEN OUTFILE ERROR ! \n", 23), exit(1));
		}
		i++;
	}
	return (eropout);
}
