#include "minishell.h"

int				ft_do_right_r(t_all *all, t_redir *red, int temp)
{
	if (temp != 1)
		close(temp);
	if (red->redir == -1)
	{
		if (!(all->fd1 = open(red->cont, O_CREAT | O_WRONLY, 0755)))
			return (-1);
	}
	else if (red->redir == -3)
	{
		if (!(all->fd1 = open(red->cont, O_CREAT | O_APPEND | O_WRONLY, 0755)))
			return (-1);
	}
	return (all->fd1);
}

int				ft_do_left_r(t_all *all, t_redir *red, int temp)
{
	if (temp != 0)
		close(temp);
	if (!(all->fd0 = open(red->cont, O_RDONLY, 0755)))
		return (-1);
	return (all->fd0);
}

int 			ft_fd_cont(t_all *all)
{
	if (all->fd0 >= 0 && all->fd1 >= 1)
	{
		dup2(all->fd0, 0);
		dup2(all->fd1, 1);
	}
	else
		return ((all->err = E_FD));
	return (0);
}

int				ft_fd(t_all *all)
{
	t_redir	*redir;
	int		temp_in;
	int		temp_out;

	redir = all->l_red;
	temp_in = 0;
	temp_out = 1;
	if (redir)
	{
		while (redir)
		{
			if (redir->redir == -2)
				temp_in = ft_do_left_r(all, redir, temp_in);
			if (redir->redir == -1 || redir->redir == -3)
				temp_out = ft_do_right_r(all, redir, temp_out);
			redir = redir->next;
			if (temp_in == -1 || temp_out == -1)
				all->err = E_FD;
		}
	}
	else
		return (0);
	return (ft_fd_cont(all));
}