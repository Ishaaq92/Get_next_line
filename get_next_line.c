/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaaq <ishaaq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:43:18 by ishaaq            #+#    #+#             */
/*   Updated: 2024/12/11 11:16:30 by ishaaq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "get_next_line.h"
# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h> 

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != 0)
		i ++;
	return (i);
}
int	ft_strrchri(const char *s, int c, int start)
{
	int		i;
	int		pos;

	pos = -1;
	i = start;
	while (s[i] != 0)
	{
		if (s[i] == c)
			pos = i;
		i ++;
	}
	return (pos);
}
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ptr;

	if (ft_strlen(s) <= start)
		len = 0;
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	i = 0;
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	while (i < len && s[start + i] != '\0')
	{
		ptr[i] = s[start + i];
		i ++;
	}
	ptr[i] = '\0';
	return (ptr);
}
int	countsubstr(char *str, int start, int c)
{
	int	i;

	i = 0;
	while (str[start + i] != c && str[start + i] != '\0')
		i ++;
	return (i);
}

char	*extend(char *str, char *buffer, ssize_t num_read)
{
	char	*new_str;
	int		i;
	int		j;
	new_str = malloc(sizeof(char) * (ft_strlen(str) + num_read + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		new_str[i] = str[i];
		i ++;
	}
	j = 0;
	while (j < num_read)
	{
		new_str[i + j] = buffer[j];
		j ++;
	}
	new_str[i + j] = '\0';
	free(str);
	return (new_str);
}

char	*get_next_line(int fd)
{
	ssize_t	num_read;
	static char	*text = NULL;
	static int	start = 0;
	char	buffer[BUFFER_SIZE];
	char	*line;
	int		newline_pos;

	if (!text)
	{
		text = malloc(sizeof(char));
		if (!text)
			return (NULL);
		text[0] = '\0';
	}
	while ((num_read = read(fd, buffer, BUFFER_SIZE - 1)) > 0)
	{
		buffer[num_read] = '\0';
		text = extend(text, buffer, num_read);
		if (!text)
		{
			free(text);
			return (NULL);
		}
		if ((newline_pos = ft_strrchri(text, '\n', start)) >= 0)
		{
			line = ft_substr(text, start, countsubstr(text, start, '\n') + 1);
			start = newline_pos + 1;
			return (line);
		}
	}
	if (text[start] != '\0') // Remaining content after EOF
	{
		line = ft_substr(text, start, ft_strlen(text) - start);
		free(text);
		text = NULL;
		return line;
	}
	free(text);
	text = NULL;
	return NULL; // No more content to read
}

int main(int ac, char *av[])
{
	if (ac < 2)
	{
		printf("Usage: %s <filename>\n", av[0]);
		return (1);
	}

	int fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}

	char *line;
	// while ((line = get_next_line(fd)) != NULL)
	// {
	// 	printf("%s", line); // Print the line (newlines are preserved)
	// 	free(line);         // Free each line after use
	// }
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	close(fd);
	return (0);
}