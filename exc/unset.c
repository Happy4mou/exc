/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajdoub <mmajdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:14:19 by mmajdoub          #+#    #+#             */
/*   Updated: 2023/06/11 13:42:25 by mmajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_remove_node(t_env **env, char *ptr)
{
	t_env	*tmp;
	t_env	*prv;

	tmp = *env;
	prv = *env;
	g_exitstatus = 0;
	if (ptr == NULL)
		return ;
	if (ft_strcmp((*env)->var, ptr) == 0)
	{
		tmp = *env;
		*env = (*env)->next;
		return ;
	}
	while (prv->next != NULL)
	{
		if (ft_strcmp(prv->var, ptr) == 0)
		{
			tmp->next = prv->next;
			break ;
		}
		tmp = prv;
		prv = prv->next;
	}
	if (prv->next == NULL && ft_strcmp(prv->var, ptr) == 0)
	{
		tmp->next = NULL;
		free(prv);
		return ;
	}
	if (tmp == NULL)
		return ;
}
