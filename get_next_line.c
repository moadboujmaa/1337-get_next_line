/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboujama <mboujama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 22:46:47 by mboujama          #+#    #+#             */
/*   Updated: 2024/01/10 15:40:41 by mboujama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Get everything exist after '\n' character => "new_remaider"
char	*get_new_remainder(char *str)
{
	char	*remainder;
	int		i;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	remainder = ft_strdup(str + i + 1);
	return (remainder);
}

// Retrun from the beginning until found '\n' => "line"
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

// check if the string has a '\n' 
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

// 
int	init_remainder(char **remainder, int fd)
{
	ssize_t		bytes_read;

	*remainder = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!*remainder)
		return (0);
	bytes_read = read(fd, *remainder, BUFFER_SIZE);
	if (bytes_read == -1)
	{
		free(*remainder);
		return (0);
	}
	(*remainder)[bytes_read] = '\0';
	return (1);
}

// Main function
char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*tmp;
	char		*line;
	int			read_bytes;

	line = NULL;
	tmp = (char *)malloc(sizeof(char) * (BUFFER_SIZE));
	if (!tmp)
		return (NULL);
	if (!remainder)
		if (!init_remainder(&remainder, fd))
			return (NULL);
	if (remainder)
	{
		while (remainder && !is_has_newline(remainder) && read_bytes > 0)
		{
			read_bytes = read(fd, tmp, BUFFER_SIZE);
			remainder = ft_strjoin(remainder, tmp);
		}
		if (is_has_newline(remainder))
		{
			line = get_until_newline(remainder);
			remainder = get_new_remainder(remainder);
		}
	}
	return (line);
}

// int	main(void)
// {
// 	int	fd;
// 	int	i;

// 	i = 1;
// 	fd = open("test.txt", O_RDWR);
// 	printf("FD = %d\n", fd);
// 	printf("------> LINES <------\n");
// 	while (i <= 26)
// 	{
// 		printf("[%d] = {%s}\n", i, get_next_line(fd));
// 		i++;
// 	}
// 	return (0);
// }
