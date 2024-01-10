/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboujama <mboujama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 22:46:47 by mboujama          #+#    #+#             */
/*   Updated: 2024/01/09 15:01:54 by mboujama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_remainder(char *str)
{
	char	*remainder;
	int		i;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	remainder = ft_strdup(str + i + 1);
	return (remainder);
}

char	*get_until_newline(char *remainder)
{
	char	*str;
	int		i;

	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (remainder[i] && remainder[i] != '\n')
	{
		str[i] = remainder[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	is_has_newline(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	remainder[BUFFER_SIZE * 5];
	char		*str;
	char		*line;
	char		*tmp;
	int			i;

	line = NULL;
	tmp = NULL;
	str = (char *) malloc(BUFFER_SIZE + 1);
	if (!str)
		return (NULL);
	if (remainder[0] == '\0')
		read(fd, remainder, BUFFER_SIZE);
	if (remainder[0] != '\0')
	{
		if (!is_has_newline(remainder))
		{
			read(fd, str, BUFFER_SIZE);
			tmp = ft_strjoin(remainder, str);
			printf("TMP = %s\n", tmp);
			i = 0;
			while (tmp[i])
			{
				remainder[i] = tmp[i];
				i++;
			}
			line = get_until_newline(remainder);
		}
		if (is_has_newline(remainder))
		{
			line = get_until_newline(remainder);
		}
	}
	return (line);
}

int	main(void)
{
	int		fd;

	fd = open("test.txt", O_RDWR);
	printf("------> LINES <------\n");
	printf("[1] %s\n", get_next_line(fd));
	printf("[2] %s\n", get_next_line(fd));
	return (0);
}
