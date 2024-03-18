/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javimar2 <javimar2@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:59:24 by javimar2          #+#    #+#             */
/*   Updated: 2024/03/02 17:59:26 by javimar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(char	*str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*output;
	size_t	i;
	size_t	j;

	i = -1;
	j = -1;
	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		if (!s1)
			return (0);
		s1[0] = '\0';
	}
	output = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!output)
		return (ft_free(&s1));
	while (s1[++i] != '\0')
		output[i] = s1[i];
	while (s2[++j] != '\0')
		output[i + j] = s2[j];
	output[i + j] = '\0';
	free(s1);
	return (output);
}

// char	*ft_strchr(char *s, int c)
// {
// 	while (*s != (char)c && *s != '\0')
// 	{
// 		s++;
// 	}
// 	if (*s == '\0' && (char)c != '\0')
// 		return (NULL);
// 	return ((char *)s);
// }

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (&((char *)s)[i]);
		i++;
	}
	if ((char)c == '\0')
		return (&((char *)s)[i]);
	return (0);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*res;

	i = 0;
	if (!s)
		return (0);
	if (start > ft_strlen(s))
	{
		res = malloc(sizeof(char) * (1));
		if (!res)
			return (NULL);
		res[0] = '\0';
		return (res);
	}
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	while (start < ft_strlen(s) && i < len && s[start])
		res[i++] = s[start++];
	res[i] = '\0';
	return (res);
}

// char	*ft_substr(char *s, unsigned int start, size_t len)
// {
// 	char	*substr;
// 	size_t	i;

// 	if (start >= (unsigned int)ft_strlen(s) || len == 0)
// 	{
// 		substr = (char *)malloc(sizeof(char) * 1);
// 		if (!substr)
// 			return (NULL);
// 		substr[0] = '\0';
// 		return (substr);
// 	}
// 	i = 0;
// 	if (len > ft_strlen(s) - start)
// 		len = ft_strlen(s) - start;
// 	substr = (char *)malloc((sizeof(char)) * (len + 1));
// 	if (!substr)
// 		return (NULL);
// 	while (i < len && s[start + i] != '\0')
// 	{
// 		substr[i] = s[start + i];
// 		i++;
// 	}
// 	substr[i] = '\0';
// 	return (substr);
// }

char	*ft_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (NULL);
}
