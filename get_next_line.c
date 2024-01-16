/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboujama <mboujama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 22:46:47 by mboujama          #+#    #+#             */
/*   Updated: 2024/01/16 16:19:47 by mboujama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Get everything exist after '\n' character => "new_remaider"
char	*get_new_remainder(char *str)
{
	char	*remainder;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\n' && str[i])
		i++;
	remainder = ft_strdup(str + i + 1);
	if (!remainder)
		return (free(str), str = NULL, NULL);
	free(str);
	str = NULL;
	return (remainder);
}

// Return from the beginning until found '\n' => "line"
char	*get_until_newline(char *remainder)
{
	char	*str;
	int		i;

	i = 0;
	if (!remainder)
		return (NULL);
	while (remainder[i] && remainder[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
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

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

// Main function
char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*tmp;
	char		*line;
	int			read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0 || !fd)
		return (NULL);
	line = NULL;
	tmp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (NULL);
	read_bytes = 1;
	if (!remainder)
		remainder = ft_strdup("");
	while (!is_has_newline(remainder) && read_bytes > 0)
	{
		read_bytes = read(fd, tmp, BUFFER_SIZE);
		if (read_bytes <= 0)
			return (free(tmp), tmp = NULL, NULL);
		tmp[read_bytes] = '\0';
		remainder = ft_strjoin(remainder, tmp);
	}
	if (read_bytes != 0 || ft_strlen(remainder) > 0)
	{
		line = get_until_newline(remainder);
		remainder = get_new_remainder(remainder);
	}
	else
		return (free(remainder), remainder = NULL, NULL);
	return (free(tmp), tmp = NULL, line);
}

int	main(void)
{
	int		fd;
	char	*ptr;
	int		i;

	i = 1;
	fd = open("test.txt", O_RDONLY);
	ptr = get_next_line(fd);
	while (ptr)
	{
		printf("[%d] line = {%s}\n", i, ptr);
		ptr = get_next_line(fd);
		i++;
	}
	return (0);
}
