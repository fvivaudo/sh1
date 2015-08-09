/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sig.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvivaudo <fvivaudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/12 17:09:01 by fvivaudo          #+#    #+#             */
/*   Updated: 2015/03/12 17:09:02 by fvivaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh1.h>

void sig_handler(int sig)
{
	if (sig == SIGINT)
		sig = SIGINT;
	if (sig == SIGSEGV)
	{
		ft_putendl("sh1: Segmentation fault");
	}
	if (sig == SIGQUIT)
	{
		exit(10);
	}
}
