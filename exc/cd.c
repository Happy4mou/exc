/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajdoub <mmajdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:29:14 by mmajdoub          #+#    #+#             */
/*   Updated: 2023/06/07 10:31:38 by mmajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*pwdfunction(int c)
{
	char	buffer[300];

	g_exitstatus = 0;
	if (getcwd(buffer, 300) == NULL)
	{
		perror("getcwd() error");
	}
	if (c == 0)
	{
		printf("%s\n", buffer);
	}
	return (ft_strdup(buffer));
}

char	*gethompath(t_env **head)
{
	t_env	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (ft_strnstr(tmp->var, "HOME", 4))
			return (tmp->val);
		tmp = tmp->next;
	}
	return (0);
}

char	*getpwdpath(t_env **head)
{
	t_env	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (ft_strnstr(tmp->var, "PWD", 4))
			return (tmp->val);
		tmp = tmp->next;
	}
	return (0);
}

void	ft_change_pwd(t_env **head, char *ptr)
{
	t_env	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (ft_strnstr(tmp->var, "PWD", 4))
		{
			tmp->val = ft_strdup(ptr);
		}
		tmp = tmp->next;
	}
}

void	ft_change_oldpwd(t_env **head, char *ptr)
{
	t_env	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (ft_strnstr(tmp->var, "OLDPWD", 7))
		{
			tmp->val = ft_strdup(ptr);
		}
		tmp = tmp->next;
	}
}

void	cdfunction(t_env **head, char *ptr)
{
	char	*svptr;

	svptr = NULL;
	if (ptr == NULL || ft_strcmp(ptr, "~") == 0)
	{
		svptr = gethompath(head);
		if (chdir(svptr) != 0)
		{
			g_exitstatus = 1;
			write(2, "No such file or directory\n", 16);
			return ;
		}
		svptr = pwdfunction(1);
	}
	else
	{
		if (chdir(ptr) != 0)
		{
			g_exitstatus = 1;
			write(2, "No such file or directory\n", 12);
			return ;
		}
		svptr = pwdfunction(1);
	}
	ft_change_oldpwd(head, getpwdpath(head));
	ft_change_pwd(head, svptr);
	g_exitstatus = 0;
	//pwdendoldpwd(head);
}
