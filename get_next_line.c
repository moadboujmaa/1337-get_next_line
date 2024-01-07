/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboujama <mboujama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 22:46:47 by mboujama          #+#    #+#             */
/*   Updated: 2024/01/07 19:33:06 by mboujama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*ptr;
	int		len;

	len = 0;
	while (s1[len])
		len++;
	ptr = (char *) malloc(len + 1);
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

char	*get_remainder(char *str)
{
	char	*remainder;
	int 	i;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	remainder = ft_strdup(str + i + 1);
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*str;
	int			i;

	str = (char *) malloc(BUFFER_SIZE + 1);
	if (!str)
		return (NULL);
	read(fd, str, BUFFER_SIZE);
	remainder = get_remainder(str);
	printf("Remainder is: %s\n", remainder);
	return (str);
}

// int	main(void)
// {
// 	int	fd;

// 	fd = open("test.txt", O_RDWR);
// 	get_next_line(fd);
// 	return (0);
// }
