/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajdoub <mmajdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 06:04:42 by mmajdoub          #+#    #+#             */
/*   Updated: 2023/06/11 14:17:31 by mmajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	 ft_exc(t_parc **all, t_env *env_list, char **env, t_heredoc **idfd)
{
    
	ft_heredoc_list(all, idfd, env_list);
	if ((*all)->next)
		ft_one_pipe(all, env, idfd);
	else
		ft_checkcmd(*all, &env_list, env, idfd);
}
