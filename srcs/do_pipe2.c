#include "minishell.h"

int			check_nodes(t_pipi *pipi)
{
	t_pipi	*temp;
	int		res;

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

int			fill_pipes(t_all *all, t_pipi *pipi)
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
