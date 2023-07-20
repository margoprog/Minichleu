/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:00:59 by maheraul          #+#    #+#             */
/*   Updated: 2023/07/20 19:00:26 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_is_num(char *str)
{
	int i;

	i = 0;
	if(str[0] == '-')
			i++;
	if(!str[i])
		return(0);
	while(str[i])
	{
		if(!ft_isdigit(str[i]))
			return(0);
		i++;
	}
	return(1);
}

int	ft_exit_error(char **arg)
{
	if( arg[2] && ft_is_num(arg[1]))
	{
		ft_printf("%s", "bash: exit: too many arguments\n");
		return(0);
	}
	else if(arg[1] && !ft_is_num(arg[1])   )
	{
		ft_printf("bash: exit: %s: numeric argument required\n", arg[1]);
	}
	printf("exit\n");
	exit(0);
}

int	ft_exit(char **arg, char **env)
{
	(void)arg;
	(void)env;
	if(arg[1]  && !ft_strcmp(arg[1], "--"))
	{
		if(!arg[2])
		{
			printf("exit\n");
			exit(0);
		}
		else
		{
			if(!ft_exit_error(arg + 1))
				return(0);
		}
	}
	ft_exit_error(arg);
	return (0);
}