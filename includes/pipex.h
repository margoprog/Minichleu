/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 22:25:39 by maheraul          #+#    #+#             */
/*   Updated: 2023/06/27 02:44:23 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "ft_printf.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

// > 1
// >> 2
// < 3
// << 4
typedef struct t_list
{
	char	*file;
	int		type;
	struct t_list	*next;
}				t_list;

typedef	struct t_cmd
{
	t_list	*lst;
	char	*arg[1024];
	char	*cmd;
} t_cmd;

typedef struct t_data
{
	int		nbcmd;
	char	**path;
	char	**tab;
	int		*pid;
	int		previous;
	int		fd[2];
}			t_data;


int	ft_strlen_total(char const *str, char sep);

//utils
void		*ft_free_tab(char **tab);
//pipex
char		*write_path(char *cmd, t_data *data);
void	*execute(t_data *data, t_cmd *cmd, char **env);

void		*free_pipex(t_data *data);
void		*ft_pipex(t_data *data, char **argv, char **env);
//redirection
void		redirect_outfile(t_data *data, int index, char **argv);
int			redirection(t_data *data, int index, t_cmd *cmd);
void		invalid_fd(t_data *data);
void	printtab(char **tab);

#endif