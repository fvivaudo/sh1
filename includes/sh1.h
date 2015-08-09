/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh1.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvivaudo <fvivaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/08 12:55:17 by fvivaudo          #+#    #+#             */
/*   Updated: 2015/03/08 12:55:19 by fvivaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH1_H
# define SH1_H

# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <libft.h>
# include <get_next_line.h>
# include <signal.h>

typedef struct		s_path
{
	char			**path;
	char			*cwd;
}					t_path;

int					bastard(t_path p, char *tmp, char **tab, char ***envp);
int					check_builtin(char ***envp, char **tab);
int					child(char **tab, t_path p, char ***envp);
t_path				deal_path(char ***envp);
void				ft_cd(char ***envp, char **av);
int					ft_cd2(char ***envp, char **av, int *a);
int					ft_cd3(char **av, char ***envp, char **path, int *a);
void				ft_cd4(char **av, char ***envp, char **path);
void				ft_env(char ***envp, char **av, int *loop);
void				ft_env2(char ***envp, char **av, int *loop, int i);
char				*ft_getvar(char ***envp, char *name);
void				ft_setenv(char ***envp, char **av);
void				ft_setvar(char ***envp, char *name, char *value);
int					ft_unsetenv_error(char **av);
void				ft_unsetenv(char ***e, char **av);
void				sig_handler(int sig);
#endif
