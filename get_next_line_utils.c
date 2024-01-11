/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboujama <mboujama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 22:46:50 by mboujama          #+#    #+#             */
/*   Updated: 2024/01/11 10:16:05 by mboujama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*ptr;

	ptr = (char *) malloc(ft_strlen(s1) + 1);
	if (!ptr)
		return (0);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	ptr = (char *) malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ptr)
		return (0);
	i = 0;
	j = 0;
	while (i < ft_strlen(s1))
		ptr[i++] = s1[j++];
	j = 0;
	while (j < ft_strlen(s2))
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	return (ptr);
}
