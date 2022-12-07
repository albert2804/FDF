/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 17:17:37 by aestraic          #+#    #+#             */
/*   Updated: 2022/11/22 11:58:29 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>

char	*ft_strdup_gnl(char *s)
{
	int		n;
	int		i;
	char	*s_cpy;

	i = 0;
	n = ft_strlen_gnl(s);
	s_cpy = malloc(n * sizeof(char) + 1);
	if (!s_cpy)
	{
		free(s);
		return (NULL);
	}
	if (s == NULL)
	{
		free (s);
		return (NULL);
	}
	while (i <= n)
	{
		s_cpy[i] = s[i];
		i++;
	}
	return (s_cpy);
}

void	read_into_buffer(int fd, char **buffer, int *a)
{
	char	*read_str;

	read_str = malloc(BUFFER_SIZE * sizeof(char) + 1);
	*a = read(fd, read_str, BUFFER_SIZE);
	read_str[*a] = '\0';
	if (*a > 0)
		*buffer = ft_strjoin_gnl(*buffer, read_str, -1, -1);
	free(read_str);
}

char	*make_new_buffer(char *read, int *a)
{
	char	*buffer;

	buffer = NULL;
	if (*a > 0)
	{
		buffer = ft_strdup_gnl(ft_strchr_gnl(read, '\n'));
		free(read);
	}
	else if (*a == 0 && ft_strlen_gnl(read) > 0)
	{
		buffer = NULL;
		free(read);
	}
	return (buffer);
}

char	*make_line(char *buffer)
{
	char	*line;
	int		i;
	int		pos;

	line = NULL;
	pos = ft_check_for_newline_in_buffer(buffer);
	if (pos == -1 && buffer != NULL)
	{
		line = ft_strdup_gnl(buffer);
		return (line);
	}
	line = malloc(sizeof(char) * pos + 1);
	i = 0;
	while (i < pos)
	{
		line[i] = buffer[i];
		i ++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer = NULL;
	int			a;

	line = NULL;
	a = 1;
	if (BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	while (a > 0)
	{
		if (ft_check_for_newline_in_buffer(buffer) != -1)
			break ;
		read_into_buffer(fd, &buffer, &a);
		if (buffer && ft_strlen_gnl(buffer) == 0)
			return (free (buffer), buffer = NULL, NULL);
	}
	if (a == 0 && ft_strlen_gnl(buffer) == 0)
		return (line);
	line = make_line(buffer);
	buffer = make_new_buffer(buffer, &a);
	return (line);
}

// int main()
// {
// 	int fd;
// 	int i;
// 	static int j;
// 	// fd = open("text.txt",O_RDONLY);
// 	fd = open("./Tripouoille/files/42_with_nl",O_RDONLY);
// 	i = 0;
// 	j = 0;
// 	char *string;

// 	while (i < 2)
// 	{
// 		string = get_next_line(fd);
// 		printf("%s", string);
// 		free(string);
// 		i++;
// 	}
// }