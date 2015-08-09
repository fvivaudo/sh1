/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvivaudo <fvivaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/12 17:05:11 by fvivaudo          #+#    #+#             */
/*   Updated: 2015/03/12 17:05:12 by fvivaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh1.h>

void	ft_env2(char ***envp, char **av, int *loop, int i)
{
	int	y;

	y = 0;
	while (av[i] && ft_ishere(av[i], '=') > -1)
	{
		while (av[i][y] != '=')
			++y;
		av[i][y] = 0;
		ft_setvar(envp, av[i], av[i] + y + 1);
		++i;
	}
	if (av[i])
	{
		*loop = 1;
		y = 0;
		while (av[i - 1])
			av[y++] = av[i++];
	}
	else
	{
		i = 0;
		while ((*envp)[i])
			ft_putendl((*envp)[i++]);
		*loop = 0;
	}
}

void	ft_env(char ***envp, char **av, int *loop)
{
	int		i;
	int		y;

	i = 1;
	y = 0;
	if (av[i] && ft_strcmp(av[i], "-i") == 0)
	{
		i = 0;
		while ((*envp)[i])
			((*envp)[i++] = NULL);
		i = 2;
	}
	if (av[i] == 0 && i != 2)
	{
		i = 0;
		*loop = 0;
		while ((*envp)[i])
			ft_putendl((*envp)[i++]);
		return ;
	}
	ft_env2(envp, av, loop, i);
}

void	ft_setenv(char ***envp, char **av)
{
	int		ac;
	int		i;

	ac = 0;
	i = 0;
	while (av[ac])
		++ac;
	if (ac == 1)
	{
		while ((*envp)[i])
			ft_putendl((*envp)[i++]);
	}
	else if ((ft_ishere(av[1], '=')) > -1)
		ft_putendl("setenv: Syntax error");
	else if (ac == 2)
		ft_setvar(envp, av[1], NULL);
	else if (ac == 3)
		ft_setvar(envp, av[1], av[2]);
	else
		ft_putendl("setenv: Too many arguments");
	return ;
}

int		ft_unsetenv_error(char **av)
{
	int		ac;

	ac = 0;
	while (av[ac])
		++ac;
	if (ac == 2)
		return (1);
	else if (ac == 1)
		ft_putendl("unsetenv: Too few arguments");
	return (0);
}

void	ft_unsetenv(char ***e, char **av)
{
	int		i;
	int		y;
	int		s;

	if (ft_unsetenv_error(av) == 1)
	{
		y = 1;
		while (av[y])
		{
			s = ft_strlen(av[i]);
			i = 0;
			while ((*e)[i])
			{
				if (ft_strncmp((*e)[i], av[y], s) == 0 && (*e)[i][s] == '=')
				{
					ft_strclr((*e)[i]);
					while ((*e)[i])
					{
						(*e)[i] = (*e)[i + 1];
						++i;
					}
					return ;
				}
				++i;
			}
			++y;
		}
	}
}
