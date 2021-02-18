/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmogo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 11:44:34 by jmogo             #+#    #+#             */
/*   Updated: 2021/02/18 19:56:45 by itollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*concat_path_exec(char *dir, char *exec)
{
	char	*str[2];

	str[0] = ft_strjoin(dir, "/");
	str[1] = ft_strjoin(str[0], exec);
	free(str[0]);
	return (str[1]);
}

int		manage_execve(t_all *all, char *bin, char **args)
{
	size_t	pid;

	dup2(all->fd1, 1);
	dup2(all->fd0, 0);
	if (file_exists(bin))
	{
		pid = fork();
		if (pid != 0)
		{
			wait(&(all->last_rv));
			return (1);
		}
		else
		{
			if (0 > execve(bin, args, all->env))
				ft_putstrn_fd(strerror(errno), STDERR_FILENO);
			return (errno);
		}
	}
	return (0);
}

int		check_no_path(t_all *all, char **args)
{
	if (manage_execve(all, all->def_cmd, args))
		return (1);
	return (0);
}

int		get_path(t_all *all, char *path, char *ex_name)
{
	char	**dirs;
	char	**args;
	char	*tmp;
	int		i;

	if (!ex_name)
		return (0);
	if (all->arg)
		args = copy_env(all->args.args);
	else
		args = 0x0;
	args = arr_append(args, ex_name);
	dirs = ft_split(path, ':');
	if (check_no_path(all, args))
		return (1);
	i = 0;
	while (dirs && dirs[i++])
	{
		tmp = concat_path_exec(dirs[i - 1], ex_name);
		if (manage_execve(all, tmp, args))
			return (1);
	}
	free_double_char(dirs);
	free(path);
	return (0);
}
