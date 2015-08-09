/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvivaudo <fvivaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/12 17:05:23 by fvivaudo          #+#    #+#             */
/*   Updated: 2015/03/12 17:05:24 by fvivaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh1.h>

int		check_builtin(char ***envp, char **tab)
{
	int		loop;

	loop = 1;
	if (*tab == 0)
		--loop;
	else if (ft_strcmp(*tab, "setenv") == 0)
		ft_setenv(envp, tab), --loop;
	else if (ft_strcmp(*tab, "unsetenv") == 0)
		ft_unsetenv(envp, tab), --loop;
	else if (ft_strcmp(*tab, "env") == 0)
		ft_env(envp, tab, &loop);
	else if (ft_strcmp(*tab, "cd") == 0)
		ft_cd(envp, tab), --loop;
	else if (ft_strcmp(*tab, "exit") == 0)
	{
		if (tab[1] && tab[2])
			ft_putendl("exit: too many arguments"), loop--;
		else if (!tab[1])
			exit (0);
		else if (tab[1][0] > '9' || tab[1][0] < '0')
			ft_putendl("exit: wrong argument"), loop--;
		else
			exit (ft_atoi(tab[1]));
	}
	return (loop);
}
