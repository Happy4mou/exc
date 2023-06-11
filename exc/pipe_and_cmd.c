/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmajdoub <mmajdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 13:27:54 by mmajdoub          #+#    #+#             */
/*   Updated: 2023/06/07 11:19:06 by mmajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	ft_pipes_helper1(t_parc *all, char **env, t_heredoc **idfd,
// 		char **spltcmd)
// {
//     	int		eropin;
// 	int		eropout;
//     char *bufcmd;
// 	if (!all->arg)
// 		return ;
// 	eropin = ft_open_infile(all, *idfd);
// 	eropout = ft_open_outfile(all);
// 	if (eropin != -1)
// 		dup2(eropin, 0);
// 	close(fd[0]);
// 	if (eropout == -1)
// 		dup2(fd[1], 1);
// 	else
// 		dup2(eropout, 1);
// 	bufcmd = ft_get_bufcmd(spltcmd, all->arg[0]);
// 	execve(bufcmd, all->arg, env);
// 	(printf("EXECVE ERROR ! \n"), exit(127));
// }

void	ft_one_pipe(t_parc **all1, char **env, t_heredoc **idfd)
{
	int		eropin;
	int		eropout;
	int		id;
	int		i;
	char	*bufcmd;
	int		fd[2];
	char	**spltcmd;
	int		j;
	int		idpip;
	t_parc	*all;
	int		pid;
	int		a;

	all = *all1;
	eropin = -1;
	eropout = -1;
	i = 0;
	j = 0;
	pipe(fd);
	i = ft_getpath(env);
	while (env[i][j] != '/')
		j++;
	spltcmd = ft_split(&env[i][j], ':');
	id = fork();
	if (id == 0)
	{
		if (!all->arg)
			return ;
		eropin = ft_open_infile(all, *idfd);
		eropout = ft_open_outfile(all);
		if (eropin != -1)
			dup2(eropin, 0);
		close(fd[0]);
		if (eropout == -1)
			dup2(fd[1], 1);
		else
			dup2(eropout, 1);
		bufcmd = ft_get_bufcmd(spltcmd, all->arg[0]);
		execve(bufcmd, all->arg, env);
		(printf("EXECVE ERROR ! \n"), exit(127));
	}
	else
	{
		*idfd = (*idfd)->next;
		all = all->next;
		while (all->next)
		{
			close(fd[1]);
			idpip = fd[0];
			pipe(fd);
			if (fork() == 0)
			{
				if (!all->arg)
					return ;
				eropin = ft_open_infile(all, *idfd);
				eropout = ft_open_outfile(all);
				close(fd[0]);
				if (eropin == -1)
					dup2(idpip, 0);
				else
					dup2(eropin, 0);
				if (eropout != -1)
					dup2(eropout, 1);
				else
					dup2(fd[1], 1);
				bufcmd = ft_get_bufcmd(spltcmd, all->arg[0]);
				execve(bufcmd, all->arg, env);
				(printf("EXECVE ERROR ! \n"), exit(127));
			}
			close(idpip);
			all = all->next;
			*idfd = (*idfd)->next;
		}
		pid = fork();
		if (pid == 0)
		{
			if (!all->arg)
				return ;
			eropin = ft_open_infile(all, *idfd);
			eropout = ft_open_outfile(all);
			close(fd[1]);
			if (eropin == -1)
				dup2(fd[0], 0);
			else
				dup2(eropin, 0);
			if (eropout != -1)
				dup2(eropout, 1);
			bufcmd = ft_get_bufcmd(spltcmd, all->arg[0]);
			execve(bufcmd, all->arg, env);
			(printf("EXECVE ERROR ! \n"), exit(127));
		}
	}
	close(fd[1]);
	close(fd[0]);
	waitpid(pid, &a, 0);
	while (waitpid(0, NULL, 0) != -1)
		;
	g_exitstatus = WEXITSTATUS(a);
}
