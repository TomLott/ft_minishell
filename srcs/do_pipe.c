/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 17:59:19 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/27 20:41:51 by itollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			manage_execve_p(t_all *all, char *bin, char **args, t_pipi *pipi)
{
	size_t	pid;

	if (file_exists(bin))
	{
		pipi->exists = 1;
		pid = fork();
		if (pid != 0)
		{
			wait(&g_ex_code);
			return (1);
		}
		else
		{
			if (0 > execve(bin, args, all->env))
			{
				ft_putstrn_fd(strerror(errno), STDERR_FILENO);
				exit(g_ex_code);
			}
			exit(g_ex_code);
		}
	}
	return (0);
}

int			pipe_no_path(t_all *all, char **args, char *ex_name, t_pipi *pipe)
{
	if (manage_execve_p(all, ex_name, args, pipe))
		return (1);
	if (ft_strcmp("cat", ex_name) || ft_strcmp("grep", ex_name))
		g_f[2] = 1;
	return (0);
}

int			pipe_path(t_all *all, char *path, char *ex_name, t_pipi *pipe)
{
	char	**dirs;
	char	*tmp;
	int		i;

	if (!ex_name || !(*ex_name))
		return (1);
	dirs = ft_split(path, ':');
	if (pipe_no_path(all, pipe->args, ex_name, pipe))
		return (1);
	i = 0;
	while (dirs && dirs[i++])
	{
		tmp = concat_path_exec(dirs[i - 1], ex_name);
		if (manage_execve_p(all, tmp, pipe->args, pipe))
			return (1);
	}
	g_ex_code = 127;
	free_double_char(&dirs);
	free(path);
	return (0);
}

void		ft_purge(t_all *all, t_pipi *pipi)
{
	dup2(pipi->fd1, 1);
	dup2(pipi->fd0, 0);
	pipi->args = arr_append(pipi->args, pipi->cmd);
	if (!(pipe_path(all, extract_env(all->env, "PATH"), pipi->cmd, pipi)))
	{
		if (ft_strcmp(pipi->cmd, "exit") && errno == 2)
			g_ex_code = 0;
		else
		{
			if (!pipi->exists)
				ft_putstrn_fd(ft_strjoin(pipi->cmd,
				": command not found"), 2);
		}
	}
	if (g_ex_code == 256)
		g_ex_code = 1;
	exit(g_ex_code);
}

int			do_pipe(t_all *all, t_pipi *pipi)
{
	int		i[2];
	t_pipi	*temp;

	i[0] = 0;
	if (fill_pipes(all, pipi))
		return ((all->err = E_PIPE));
	temp = pipi;
	while (i[0]++ <= all->pipe)
	{
		i[1] = fork();
		if (!i[1])
			ft_purge(all, temp);
		else
		{
			close(temp->fd1);
			wait(&g_ex_code);
		}
		close(temp->fd0);
		temp = temp->next;
		dup2(all->fd1_def, 1);
		dup2(all->fd0_def, 0);
	}
	g_ex_code /= 256;
	return (0);
}
