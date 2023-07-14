/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 21:15:00 by maheraul          #+#    #+#             */
/*   Updated: 2023/07/14 01:56:20 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// << avion ls << bateau -R | cat << terre
// here[0] = {
// 	.delim = "avion"
// 	.fd[2];
// }
// here[1] = {
// 	.delim = "bateau"
// 	.fd[2];
// }
// here[2] = {
// 	.delim = "terre"
// 	.fd[2];
// }
//printf("STR = %s\n", str);

int	count_hd(char *str)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while (str && str[i])
	{
		if (str[i] == '<' && str[i + 1] && str[i + 1] == '<')
			n++;
		i++;
	}
	return (n);
}

char *next_word(char *str)
{
	int i;
	char *del;

	i = 0;
	while(str && str[i] && str[i] != ' ')
		i++;
	del = malloc(sizeof(char) * i + 1);
	i = 0;
	while(str && str[i] && str[i] != ' ')
	{
		del[i] = str[i];
		i++;
	}
	del[i] = '\0';
	return(del);
}
char	*del_is(t_doc *doc, char *str)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while (str && str[i])
	{
		if (str[i] == '<' && str[i + 1] && str[i + 1] == '<')
		{
			doc[n].del = next_word(&str[i+4]);
			pipe(doc[n].fd);
			n++;
		}
		i++;
	}
	return (0);
}

void	child_hd(char *del, int fd1) // ecrire dans le pipe
{
	char	*line;

	while (1)
	{
		line = readline("> "); //stocker la ligne
		if (!line || !*line ||!ft_strncmp(line, del, ft_strlen(line)))// break si entree
			break ;
		ft_putendl_fd(line, fd1); //ecrire dans le pipe 1
		free(line);
	}
	close(fd1); //fermer le pipe ecriture
	// exit(0);
}

void	*here_doc(t_data *data, char *str)
{
	int i;
	t_doc *doc;
	pid_t pid;

	i = 0;
	data->nb_hd = count_hd(str);
	printf("NOMBRE HiRE DOC = %i\n", data->nb_hd);
	if (data->nb_hd == 0)
		return (NULL);
	doc = ft_calloc(sizeof(t_doc), data->nb_hd);
	if (!doc)
		return (NULL);
	while (i < data->nb_hd)
	{
		del_is(doc ,str);
		printf("struct %d del is = %s\n", i, doc[i].del);
		i++;
	}

	i = 0;
	pid = fork();
	if (pid == 0)
	{
		while(i < data->nb_hd)
		{
			close(doc[i].fd[0]);
			child_hd(doc[i].del, doc[i].fd[1]);
			free(doc[i].del);
			i++;
		}
		free_arg(2, 0, 0, str, doc);
		exit(0);
	}
	else if (pid > 0)
	{
		i = 0;
		while(i < data->nb_hd)
			close(doc[i++].fd[1]);
	}
	waitpid(pid, 0, 0);
	data->docs = doc;
	return (NULL);
}