/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvivaudo <fvivaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/13 11:17:38 by fvivaudo          #+#    #+#             */
/*   Updated: 2015/03/13 11:17:40 by fvivaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh1.h>

extern	char **environ;

void	ft_cd(char ***envp, char **av)
{
	char	*cwd;
	int		i;
	int		a;

	cwd = getcwd(NULL, 0);
	i = 0;
	while (av[i])
		++i;
	if (i >= 3)
	{
		ft_putendl("cd: too many arguments");
		return ;
	}
	i = ft_cd2(envp, av, &a);
	if (i < -1)
	{
		if (a == 0)
			ft_putstr("cd : permission denied : ");
		else
			ft_putstr("cd : no such file or directory : ");
		ft_putendl(av[1]);
	}
	ft_setvar(envp, "OLDPWD", cwd);
	ft_strdel(&cwd);
}

int		ft_cd2(char ***envp, char **av, int *a)
{
	int		i;
	char	*path;

	path = 0;
	i = 0;
	if (!(path = ft_getvar(envp, "HOME")))
		return (-1);
	i = 1;
	if (av[i] == 0 || (av[i][0] == '~' && av[i][1] == 0))
	{
		i = chdir(path);
		*a = access(path, F_OK);
	}
	else
		i = ft_cd3(av, envp, &path, a);
	return (i);
}

int		ft_cd3(char **av, char ***envp, char **path, int *a)
{
	int		i;

	if (av[1][0] == '/')
	{
		*path = ft_strdup(av[1]);
		i = chdir(*path);
	}
	else if (av[1][0] == '~' && av[1][1] == '/')
	{
		*path = ft_strjoin(*path, "/");
		*path = ft_strext(*path, (av)[1] + 2, 0);
	}
	else
		ft_cd4(av, envp, path);
	i = chdir(*path);
	*a = access(*path, F_OK);
	ft_setvar(envp, "PWD", *path);
	ft_strdel(path);
	return (i);
}

void	ft_cd4(char **av, char ***envp, char **path)
{
	if (av[1][0] == '-' && av[1][1] == 0
		&& (*path = ft_getvar(envp, "OLDPWD")))
	{
		*path = ft_strdup(*path);
		chdir(*path);
	}
	else
	{
		*path = getcwd(NULL, 0);
		*path = ft_strext(*path, "/", 0);
		*path = ft_strext(*path, av[1], 0);
	}
}
