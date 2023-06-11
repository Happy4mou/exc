/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajdoub <mmajdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:00:26 by mmajdoub          #+#    #+#             */
/*   Updated: 2023/06/07 13:23:59 by mmajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_env(char **arg, t_env *env)
{
	if (arg[1] == NULL)
	{
		while (env)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(env->var, 1);
			if (env->val)
			{
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(env->val, 1);
				ft_putchar_fd('\"', 1);
			}
			ft_putchar_fd('\n', 1);
			env = env->next;
		}
		return (1);
	}
	return (0);
}

int	check_dub(int end, char *str, t_env *env)
{
	while (env)
	{
		if (strncmp(env->var, str, end + 1) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

void	ft_export(char **arg, t_env *env)
{
	int		i;
	t_env	*tmp;
	char	*var;

	i = -1;
	if (arg[1] && ft_isalpha(arg[1][0]) == 0)
    {
        g_exitstatus = 1;
        printf(" not a valid identifier\n");
        return ;
    }
		
	if (print_env(arg, env) == 1)
		return ;
	while (arg[1][++i])
	{
		if (ft_isalpha(arg[1][i]) == 0 && ft_isdigit(arg[1][i]) == 0)
			break ;
	}
	var = ft_substr(arg[1], 0, i);
	if ((arg[1][i] != '+' && arg[1][i] != '=' && arg[1][i]) || (arg[1][i]
			&& arg[1][i] == '+' && arg[1][i + 1] != '='))
	{
        g_exitstatus = 1;
		ft_putstr_fd(arg[1], 1);
		ft_putstr_fd(": not a valid identifier\n", 1);
		return ;
	}
	if (check_dub(i, var, env) == 0)
	{
		tmp = malloc(sizeof(t_env));
		tmp->var = var;
		tmp->val = NULL;
		tmp->next = NULL;
		ft_lst_add_back2(env, tmp);
		if (arg[1][i] == '+' && arg[1][i + 1] == '=')
			tmp->val = ft_strjoin(tmp->val, &arg[1][i + 2]);
		else if (arg[1][i] == '=')
		{
			if (tmp->val != NULL)
				free(tmp->val);
			tmp->val = ft_strdup(&arg[1][i + 1]);
		}
	}
	else
	{
		while (env)
		{
			if (strncmp(env->var, var, i + 1) == 0)
				break ;
			env = env->next;
		}
		if (arg[1][i] == '+' && arg[1][i + 1] == '=')
			env->val = ft_strjoin(env->val, &arg[1][i + 2]);
		else if (arg[1][i] == '=')
		{
			if (env->val != NULL)
				free(env->val);
			env->val = ft_strdup(&arg[1][i + 1]);
		}
	}
    g_exitstatus = 0;
}

void	ft_env(t_env **env)
{
	t_env	*tmp;

	g_exitstatus = 0;
	tmp = *env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->var, tmp->val);
		tmp = tmp->next;
	}
}
void	ft_checkcmd(t_parc *head, t_env **env_list, char **env,
		t_heredoc **idfd)
{
	if (head->arg[0] != NULL)
	{
		if (ft_strncmp(head->arg[0], "echo", 5) == 0)
			ft_echo(head);
		else if (ft_strncmp(head->arg[0], "export", 7) == 0)
			ft_export(head->arg, *env_list);
		else if (ft_strncmp(head->arg[0], "unset", 6) == 0)
			ft_remove_node(env_list, head->arg[1]);
		else if (ft_strncmp(head->arg[0], "env", 4) == 0)
			ft_env(env_list);
		else if (ft_strncmp(head->arg[0], "cd", 3) == 0)
			cdfunction(env_list, head->arg[1]);
		else if (ft_strncmp(head->arg[0], "pwd", 4) == 0)
			pwdfunction(0);
		else if (ft_strncmp(head->arg[0], "exit", 5) == 0)
			ft_exit(head);
		else
			ft_one_cmd(head, env, idfd);
	}
	else
		return ;
}
