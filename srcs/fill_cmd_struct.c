/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 22:40:06 by maheraul          #+#    #+#             */
/*   Updated: 2023/06/30 22:46:39 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	chevron_comp(char *str)
{
	if (!ft_strcmp(str, ">"))
		return (1);
	if (!ft_strcmp(str, ">>"))
		return (2);
	if (!ft_strcmp(str, "<"))
		return (3);
	if (!ft_strcmp(str, "<<"))
		return (4);
	return (0);
}

int	countarg(char **tab)
{
	int	size;
	int	i;

	size = 0;
	i = 0;
	while (tab[i])
	{
		if (chevron_comp(tab[i]))
			i++;
		else
			size++;
		i++;
	}
	return (size);
}

t_cmd	parse(char *str)
{
	t_cmd	cmds;
	t_list	*lst;
	char	**input;
	int		j;
	int		i;

	j = 0;
	i = 0;
	lst = 0;
	input = ft_split(str, ' ');
	cmds.arg = ft_calloc(sizeof(char *), countarg(input) + 1);
	while (input[i])
	{
		if (chevron_comp(input[i]))
		{
			ft_rediradd_back(&lst, ft_redirnew(ft_strdup(input[i + 1]),
						chevron_comp(input[i])));
			i++;
		}
		else
			cmds.arg[j++] = ft_strdup(input[i]);
		i++;
	}
	ft_freetab(input);
	cmds.cmd = cmds.arg[0];
	cmds.lst = lst;
	printstruct(&cmds);
	return (cmds);
}