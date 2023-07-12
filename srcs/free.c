/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:09:30 by maheraul          #+#    #+#             */
/*   Updated: 2023/07/13 00:08:56 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void	*free_arg(int str, int tab, int lst, ...)
{
	va_list arg;

	va_start(arg, lst);
	while(str > 0)
	{
		free((char *)va_arg(arg, char *));
		str--;
	}
	while(tab > 0)
	{
		ft_free_tab((char **)va_arg(arg, char **));
		tab--;
	}
	while(lst > 0)
	{
		ft_lst_clear((t_list **)va_arg(arg, t_list **));
		lst--;
	}
	// ft_printf("%s", "error malloc"); // a changer
	return(va_end(arg),NULL);
}