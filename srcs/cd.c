/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 02:56:31 by maheraul          #+#    #+#             */
/*   Updated: 2023/06/28 03:34:02 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	ft_cd(char **arg, char **env)
{
	if(arg[2] && chdir(arg[2]) < 0)
	{
		perror("bash");
		return(1);
	}
	return(0);
}

int main(int ac, char **av, char **env)
{
	ft_cd(av, env);
}