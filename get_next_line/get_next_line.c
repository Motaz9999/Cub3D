/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 19:10:45 by motaz             #+#    #+#             */
/*   Updated: 2025/09/16 17:57:36 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char **stash);
static void	trim_stash(char **stash, size_t take);
static char	*join_and_free(char *s1, const char *s2);

// you cant free null soo i used 2 cases
static void	*free_stash(char **stash, char *buff, int cas)
{
	if (cas == 1)
	{
		free(buff);
		free(*stash);
		*stash = NULL;
	}
	if (cas == 2)
		free(buff);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	ssize_t		bytes_readed;
	char		*buff;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = malloc(BUFFER_SIZE + 1);
	if (buff == NULL)
		return (free_stash(&stash, NULL, 1));
	while (1)
	{
		if (stash && ft_strchr(stash, '\n'))
			break ;
		bytes_readed = read(fd, buff, BUFFER_SIZE);
		if (bytes_readed < 0)
			return (free_stash(&stash, buff, 1));
		if (bytes_readed == 0)
			break ;
		buff[bytes_readed] = '\0';
		stash = join_and_free(stash, buff);
		if (!stash)
			return (free_stash(NULL, buff, 2));
	}
	free(buff);
	return (extract_line(&stash));
}

static char	*extract_line(char **stash)
{
	char	*line;
	size_t	len;

	if (!*stash || (*stash)[0] == '\0')
		return (free_stash(stash, NULL, 1));
	len = 0;
	while ((*stash)[len] != '\n' && (*stash)[len] != '\0')
		len++;
	if ((*stash)[len] == '\n')
		len++;
	line = (char *)malloc(len + 1);
	if (line == NULL)
		return (free_stash(stash, NULL, 1));
	ft_strlcpy(line, *stash, len + 1);
	trim_stash(stash, len);
	return (line);
}

static void	trim_stash(char **stash, size_t take)
{
	char	*new_stash;
	size_t	remaining_len;
	size_t	len;

	if (*stash == NULL)
		len = 0;
	else
		len = ft_strlen(*stash);
	remaining_len = len - take;
	if (remaining_len <= 0)
	{
		free(*stash);
		*stash = NULL;
		return ;
	}
	new_stash = malloc(remaining_len + 1);
	if (!new_stash)
	{
		free(*stash);
		*stash = NULL;
		return ;
	}
	ft_strlcpy(new_stash, *stash + take, (remaining_len + 1));
	free(*stash);
	*stash = new_stash;
}

static char	*join_and_free(char *s1, const char *s2)
{
	char	*join;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s2)
		return (free_stash(NULL, s1, 2));
	if (s1 == NULL)
		s1 = ft_strdup("");
	if (!s1)
		return (NULL);
	join = malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (join == NULL)
		return (free_stash(NULL, s1, 2));
	while (s1[i] != '\0')
		join[j++] = s1[i++];
	free(s1);
	i = 0;
	while (s2[i] != '\0')
		join[j++] = s2[i++];
	join[j] = '\0';
	return (join);
}
