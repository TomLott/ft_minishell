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

int 	check_nodes(t_pipi *pipi)
{
	t_pipi	*temp;
	int 	res;

	temp = pipi;
	res = 0;
	if (!temp)
	    res = 1;
	while (temp)
	{
		if (!temp->cmd || !(*temp->cmd))
			return ((res = 1));
		temp = temp->next;
	}
	return (res);
}

int		fill_pipes(t_all *all, t_pipi *pipi)
{
	int	i;
	int	pp[2];
	int res;

	i = 0;
	res = check_nodes(pipi);
	while (i++ < all->pipe && !res)
	{
		pipi->exists = 0;
		pipe(pp);
		if (pipi->fd1 == 1)
			pipi->fd1 = dup(pp[1]);
		if (pipi->next->fd0 == 0)
			pipi->next->fd0 = dup(pp[0]);
		close(pp[0]);
		close(pp[1]);
		pipi = pipi->next;
	}
	return (res);
}

int		manage_execve_p(t_all *all, char *bin, char **args, t_pipi *pipi)
{
	size_t  pid;

	if (file_exists(bin))
	{
		pipi->exists = 1;
    	pid = fork();
    	if (pid != 0)
    	{
			wait(&ex_code);
			return (1);
		}
		else
		{
			if (0 > execve(bin, args, all->env))
			{
				ft_putstrn_fd(strerror(errno), STDERR_FILENO);
				exit(ex_code);
			}
			exit(ex_code);
		}
	}
	return (0);
}

int     pipe_no_path(t_all *all, char **args, char *ex_name, t_pipi *pipe)
{
    if (manage_execve_p(all, ex_name, args, pipe))
        return (1);
    if (ft_strcmp("cat", ex_name) || ft_strcmp("grep", ex_name))
        g_f[2] = 1;
    return (0);
}

int		pipe_path(t_all *all, char *path, char *ex_name, t_pipi *pipe)
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
	ex_code = 127;
	free_double_char(&dirs);
	free(path);
	return (0);
}

int		do_pipe(t_all *all, t_pipi *pipi)
{
	int		i;
	int		f;
	t_pipi	*temp;

	i = 0;
	if (fill_pipes(all, pipi))
		return ((all->err = E_PIPE));
	temp = pipi;
	while (i++ <= all->pipe)
	{
		f = fork();
		if (!f)
		{
			dup2(pipi->fd1, 1);
			dup2(pipi->fd0, 0);
			pipi->args = arr_append(pipi->args, pipi->cmd);
			if (!(pipe_path(all, extract_env(all->env, "PATH"), pipi->cmd, pipi)))
			{
				if (ft_strcmp(pipi->cmd, "exit") && errno == 2)
					ex_code = 0;
				else
					if (!pipi->exists)
						ft_putstrn_fd(ft_strjoin(pipi->cmd, ": command not found"), 2);
			}
			if (ex_code == 256)
				ex_code = 1;
			exit(ex_code);
		}
		else
		{
			close(pipi->fd1);
			wait(&ex_code);
		}
		close(pipi->fd0);
		//close(pipi->fd1);
		pipi = pipi->next;
		dup2(all->fd1_def, 1);
		dup2(all->fd0_def, 0);
	}
	ex_code /= 256;
	pipi = temp;
	return (0);
}
