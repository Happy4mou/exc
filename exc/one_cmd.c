/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajdoub <mmajdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:39:29 by mmajdoub          #+#    #+#             */
/*   Updated: 2023/06/11 18:22:28 by mmajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_one_cmd_helper(t_parc *all, char **env, t_heredoc **idfd,
		char **spltcmd)
{
	int		eropin;
	int		eropout;
	char	*bufcmd;

	if (!all->arg)
		return ;
	eropin = ft_open_infile(all, *idfd);
	eropout = ft_open_outfile(all);
	bufcmd = ft_get_bufcmd(spltcmd, all->arg[0]);
	if (eropin != -1)
	{
		dup2(eropin, 0);
	}
	if (eropout != -1)
		dup2(eropout, 1);
	execve(bufcmd, all->arg, env);
	(printf("EXECVE ERROR ! \n"), exit(127));
}

void	ft_one_cmd(t_parc *all, char **env, t_heredoc **idfd)
{
	int		id;
	int		i;
	char	**spltcmd;
	int		j;
	int		a;

	j = 0;
	i = ft_getpath(env);
	while (env[i][j] != '/')
		j++;
	spltcmd = ft_split(&env[i][j], ':');
	i = 0;
	id = fork();
	if (id == 0)
	{
		ft_one_cmd_helper(all, env, idfd, spltcmd);
	}
	waitpid(id, &a, 0);
	g_exitstatus = WEXITSTATUS(a);
}
