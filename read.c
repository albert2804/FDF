/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:15:28 by aestraic          #+#    #+#             */
/*   Updated: 2022/12/22 15:36:13 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

size_t	ft_count_spaces(char *c)
{
	size_t	count;
	char	**str;

	count = 0;
	if (c == NULL)
		return (0);
	c = ft_strtrim(c, "\n, ");
	str = ft_split(c, ' ');
	while (str[count])
		count ++;
	fr_dblsgl_p((void **)str, c, count);
	return (count);
}
// size_t	ft_count_spaces(char *c)
// {
// 	size_t	count;
// 	size_t	i;

// 	count = 0;
// 	i = 0;
// 	if (c == NULL)
// 		return (0);
// 	while (c[i] == ' ')
// 		i ++;
// 	while (c[i] != '\0')
// 	{
// 		if (c[i] == ' ' && c[i + 1] != ' ')
// 			count++;
// 		i++;
// 	}
// 	return (count);
// }

/*
reads the amount of lines and columns (eckpunkte) 
provided by the test_maps
*/
void	read_map_vertices(int fd, t_readmap *map_data)
{
	size_t	*i;
	size_t	j;
	char	*line;

	i = ft_calloc(sizeof(size_t), 2);
	j = 1;
	line = get_next_line(fd);
	i[0] = ft_count_spaces(line);
	free(line);
	while (j)
	{
		line = get_next_line(fd);
		line = trim(&line);
		if (ft_strlen_gnl(line) == 0)
		{
			free(line);
			break ;
		}
		free(line);
		i[1] = ++j;
	}
	map_data->count_x = i[0];
	map_data->count_y = i[1];
	map_data->total_count = map_data->count_x * map_data->count_y;
	free (i);
}

/**
 * reads out the xyz values of one line of each node 
 * and stores the matrix in the 
 * m_data struct.
 * @param line is the string of the read line
 * @param row inital value for row (=1)
 * @param col inital value for column (=1)
 * @param returns an integer/size_t matrix in this form
 * [[x1,y1,z1], [x2,y2,z2]], [x3,y3,z3], ....]
 */
void	xyz_pos(int fd, size_t row, size_t col, t_readmap *map_data)
{
	char	*line;
	int		**matrix;
	int		*values;
	char	**split;
	int		node;

	node = 0;
	matrix = ft_calloc(sizeof(int *), map_data->total_count);
	while (row ++ < map_data->count_y)
	{
		line = get_next_line(fd);
		line = trim(&line);
		split = ft_split(line, ' ');
		col = 0;
		while (col < map_data->count_x)
		{
			values = ft_calloc(sizeof(int), 3);
			values[0] = map_data->offset_x + col * map_data->delta;
			values[1] = map_data->offset_y + (row - 1) * map_data->delta;
			values[2] = ft_atoi(split[col++]);
			matrix[node ++] = values;
		}
		fr_dblsgl_p((void **)split, (void *)line, map_data->count_x);
	map_data->values_matrix = matrix;
	}
}

/*
reads the map with gnl and stores the the positions of nodes
and its values in a matrix
*/
void	get_map_information(char *map_name, t_readmap *map_data)
{
	int		fd;
	char	*path;

	path = ft_strjoin("./test_maps/", map_name);
	fd = open(path, O_RDONLY);
	read_map_vertices(fd, map_data);
	close(fd);
	determine_delta(map_data);
	fd = open(path, O_RDONLY);
	xyz_pos(fd, 0, 0, map_data);
	close(fd);
	fd = open(path, O_RDONLY);
	read_color(fd, 0, 0, map_data);
	close(fd);
	free(path);
}
