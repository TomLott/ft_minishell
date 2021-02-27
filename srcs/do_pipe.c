/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 17:59:19 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/27 10:42:04 by jmogo            ###   ########.fr       */
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

int		manage_execve_p(t_all *all, char *bin, char **args)
{
	size_t  pid;

	if (file_exists(bin))
	{
    	pid = fork();
    	if (pid != 0)
    	{
			wait(&(ex_code));
			return (1);
		}
		else
		{
			printf("bin is %s\n", bin);
			printf("arg is %s\n", args[1]);

			if (0 > execve(bin, args, all->env))
			{
				ft_putstrn_fd(strerror(errno), STDERR_FILENO);
				exit(errno);
			}
			exit(0);
		}
	}
	return (0);
}

int     pipe_no_path(t_all *all, char **args, char *ex_name)
{
    if (manage_execve_p(all, ex_name, args))
        return (1);
    if (ft_strcmp("cat", ex_name) || ft_strcmp("grep", ex_name))
        g_f[2] = 1;
    return (0);
}

int		pipe_path(t_all *all, char *path, char *ex_name, t_pipi *pipe)
{
	char	**dirs;
	//char	**args;
	char	*tmp;
	int		i;

	if (!ex_name || !(*ex_name))
		return (1);
	dirs = ft_split(path, ':');
	if (pipe_no_path(all, pipe->args, ex_name))
		return (1);
	i = 0;
	while (dirs && dirs[i++])
	{
		tmp = concat_path_exec(dirs[i - 1], ex_name);
		if (manage_execve_p(all, tmp, pipe->args))
			return (1);
	}
	free_double_char(&dirs);
	free(path);
	return (0);
}

int		do_pipe(t_all *all, t_pipi *pipi)
{
	int		i;
	int		f;
	t_pipi	*temp;
	int		temp_fd;

	i = 0;
	if (fill_pipes(all, pipi))
		return ((all->err = E_PIPE));
	temp = pipi;
	temp_fd = -2;
	while (i++ <= all->pipe)
	{
		printf("fd0: %d\tfd1: %d\n", pipi->fd0, pipi->fd1);
		f = fork();
		if (!f)
		{
		//	printf("%s cmd here\n", pipi->cmd);
			dup2(pipi->fd1, 1);
			dup2(pipi->fd0, 0);
			//if (temp_fd != -2)
			//	close(temp_fd);
			pipi->args = arr_append(pipi->args, pipi->cmd);
			if (!pipe_path(all, extract_env(all->env, "PATH"), pipi->cmd, pipi))
				ft_putstrn_fd(strerror(errno), all->fd1);
			exit(errno);
		}
		else
		{
			close(pipi->fd1);
			wait(&ex_code);
		}
		close(pipi->fd0);
		//close(pipi->fd1);
		//temp_fd = pipi->fd1;
		pipi = pipi->next;
		dup2(all->fd1_def, 1);
		dup2(all->fd0_def, 0);
	}
	close(temp_fd);
	i = 0;
	pipi = temp;
	return (0);
	/*while (i++ < all->pipe)
	{
		close(temp->fd1);
		close(temp->fd0);
		temp = temp->next;
	}*/
}
