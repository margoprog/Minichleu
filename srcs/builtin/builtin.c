/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 23:24:23 by maheraul          #+#    #+#             */
/*   Updated: 2023/07/13 21:00:43 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_is_builtin(t_cmd *cmd, char **env)
{
	int						i;
	static const char		*str[4] = {"pwd", "cd", "echo", NULL};
	static const t_builtin	func[3] = {ft_pwd, ft_cd, ft_echo};

	i = 0;
	if (!cmd)
		return (0);
	while (str[i])
	{
		if (!ft_strncmp(cmd->cmd, str[i], ft_strlen(cmd->cmd)))
		{
			func[i](cmd->arg, env);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_is_builtin_vrmnt(char *str)
{
	int					i;
	static const char	*tab[4] = {"pwd", "cd", "echo", NULL};

	i = 0;
	while (str && tab[i])
	{
		if (!ft_strncmp(str, tab[i], ft_strlen(str)))
			return (1);
		i++;
	}
	return (0);
}
