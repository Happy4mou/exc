/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajdoub <mmajdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:16:26 by mmajdoub          #+#    #+#             */
/*   Updated: 2023/06/10 16:28:33 by mmajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_addback(t_heredoc **head, int ptr)
{
	t_heredoc	*new;
	t_heredoc	*last;

	new = malloc(sizeof(t_heredoc));
	new->data = ptr;
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
}
void	ft_heredoc_list(t_parc **head, t_heredoc **idfd, t_env *env)
{
	t_parc	*tmp;
	int		i;

	i = 0;
	tmp = *head;
	while (tmp)
	{
        i = 0;
		while (tmp->name[i])
		{
			if (tmp->tab[i] == 4)
				ft_addback(idfd, ft_heredoc(tmp, env));
            i++;
		}
		tmp = tmp->next;
	}
}

int	ft_heredoc(t_parc *head, t_env *env)
{
	int		perout;
	int		fd[2];
	int		i;
	char	*buffer;

	perout = -1;
	i = 0;
	(void)(env);
	while (head->name[i])
	{
		if (head->tab[i] == 4)
		{
			pipe(fd);
			while (1)
			{
				buffer = get_next_line(0);
				if (ft_strncmp(buffer, head->name[i],
						ft_strlen(head->name[i])) == 0)
					break ;
				buffer = ft_expand(buffer, env, 0);
				perout = ft_open_outfile(head);
				ft_putstr_fd(buffer, fd[1]);
			}
		}
		i++;
	}
	close(fd[1]);
	return (fd[0]);
}
