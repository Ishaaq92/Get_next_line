/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaaq <ishaaq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:47:42 by ishaaq            #+#    #+#             */
/*   Updated: 2024/12/10 17:28:29 by ishaaq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_isascii(int c)
{
	if (c < 128 && c >= 0)
		return (1);
	return (0);
}

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i] != 0)
// 		i ++;
// 	return (i);
// }

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
char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	*ptr;

	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == c)
		{
			ptr = (char *)&str[i];
			return (ptr);
		}
		i ++;
	}
	return (0);
}