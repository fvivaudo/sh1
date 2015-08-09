/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvivaudo <fvivaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/12 17:07:49 by fvivaudo          #+#    #+#             */
/*   Updated: 2015/03/12 17:07:50 by fvivaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh1.h>

void	ft_setvar(char ***envp, char *name, char *value)
{
	int		i;
	int		size;
	char	**newenv;

	i = 0;
	size = ft_strlen(name);
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], name, size) == 0 && (*envp)[i][size] == '=')
		{
			(*envp)[i][size + 1] = 0;
			(*envp)[i] = value ? ft_strjoin((*envp)[i], value) : (*envp)[i];
			return ;
		}
		++i;
	}
	newenv = (char**)malloc((i + 2) * sizeof(char*));
	newenv[i + 1] = NULL;
	newenv[i] = value == 0 ? ft_strdup("=") : ft_strjoin("=", value);
	newenv[i] = ft_strext(name, newenv[i], 1);
	while (--i > -1)
		newenv[i] = ft_strdup((*envp)[i]);
	ft_doubletabfree(envp);
	*envp = newenv;
}

char	*ft_getvar(char ***envp, char *name)
{
	int		i;
	int		size;

	size = ft_strlen(name);
	i = 0;
	while ((*envp)[i])
	{
		if (ft_strstr((*envp)[i], name) != NULL && (*envp)[i][size] == '=')
			return ((*envp)[i] + size + 1);
		++i;
	}
	return (NULL);
}
