/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvivaudo <fvivaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/05 15:07:02 by fvivaudo          #+#    #+#             */
/*   Updated: 2015/03/05 15:07:03 by fvivaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh1.h>

t_path	deal_path(char ***envp)
{
	int		i;
	t_path	p;

	p.cwd = 0;
	i = 0;
	while ((*envp)[i])
	{
		if (ft_strstr((*envp)[i], "PATH") != NULL)
			break ;
		++i;
	}
	if ((*envp)[i])
		p.path = ft_strsplit((*envp)[i] + 5, ':');
	p.cwd = getcwd(p.cwd, 0);
	return (p);
}

int		bastard(t_path p, char *tmp, char **tab, char ***envp)
{
	char	*right_path;
	int		i;
	int		a;

	i = 0;
	a = 0;
	right_path = 0;
	if (ft_ishere(tmp + 1, '/') > 0)
	{
		right_path = ft_strjoin(p.cwd, tmp);
		execve(right_path, tab, *envp);
	}
	else
	{
		while (p.path[i])
		{
			right_path = ft_strjoin(p.path[i], tmp);
			if (access(right_path, F_OK) == 0 && access(right_path, X_OK) == -1)
				++a;
			execve(right_path, tab, *envp);
			++i;
		}
	}
	if (a > 0)
		return (-1);
	return (0);
}

int		child(char **tab, t_path p, char ***envp)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strjoin("/", *tab);
	if ((tab)[0][0] == '/')
		execve(*tab, tab, *envp);
	else
		i = bastard(p, tmp, tab, envp);
	if (i == -1)
		ft_putstr("sh1: Permission denied: ");
	else if ((tab)[0][0] == '.' && (tab)[0][1] == '/')
		ft_putstr("cd : Command not found : ");
	else
		ft_putstr("sh1: No such file or directory: ");
	ft_putendl(tmp + 1);
	ft_strdel(&tmp);
	exit(1);
	return (0);
}

int		recursive(char ***envp)
{
	char	**tab;
	char	*tmp;
	pid_t	father;
	t_path	p;

	p = deal_path(envp);
	while (2048)
	{
		ft_strdel(&p.cwd);
		ft_doubletabfree(&p.path);
		p = deal_path(envp);
		ft_putstr("\x1b[36m$>\x1b[0m");
		if (signal(SIGINT, sig_handler) == SIG_ERR)
			ft_putendl("SIG_ERROR");
		get_next_line(0, &tmp);
		tab = ft_strsplitspace(tmp);
		ft_strdel(&tmp);
		if (check_builtin(envp, tab))
		{
			father = fork();
			if (father > 0)
				wait(&father);
			else if (father == 0)
				child(tab, p, envp);
		}
		ft_doubletabfree(&tab);
	}
	return (0);
}

int		main(int ac, char **av, char **envp)
{
	int		i;
	char	**cpy;

	i = 0;
	if (ac)
		if (av)
			ac = 1;
	cpy = ft_doubletabcpy(envp);
	return (recursive(&cpy));
}