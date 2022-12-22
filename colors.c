/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:49:03 by aestraic          #+#    #+#             */
/*   Updated: 2022/12/22 17:52:18 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
/**
 * reads the color code from the testmaps 
 * in hexa and transforms it into RGB. The values will be stored in 
 * the map_data struct inside map_data->colors_matrix.
*/
void	read_color(int fd, size_t row, size_t i, t_readmap *md)
{
	char	*line;
	int		**rgb_values;
	char	**split;
	int		node;

	node = 0;
	rgb_values = ft_calloc(sizeof(int *), md->total_count);
	if (!rgb_values)
		free_rgbv(md);
	while (row < md->count_y)
	{
		i = 0;
		line = get_next_line(fd);
		line = trim(&line);
		split = ft_split(line, ' ');
		while (split[i] != NULL)
		{
			rgb_values[node ++] = rgb_converter(i, split[i], rgb_values, md);
			i ++;
		}
		row ++;
		fr_dblsgl_p((void **)split, (void *)line, md->count_x);
	}
	md->rgb_values = rgb_values;
}

/**
 * calculates the rgb-values of the nodes, which are read in from test-maps
*/
int	*rgb_converter(int i, char *str, int **rgb_values, t_readmap *md)
{
	int	*digits;
	int	*rgb;

	if (str[ft_strlen(str) - 1] == '\n')
		str[ft_strlen(str) - 1] = '\0';
	rgb = ft_calloc(sizeof(int), 3);
	if (!rgb)
		free_rgbc(md, rgb_values, i);
	if (ft_strchr(str, 'x') == 0)
		return (rgb[0] = 255, rgb[1] = 255, rgb[2] = 255, rgb);
	digits = ft_calloc(sizeof(int), 6);
	if (!digits)
		free_digits(md, rgb_values, i, rgb);
	digits = rgb_decider(str, digits);
	rgb[0] = (digits[0] * 16 + digits[1]);
	rgb[1] = (digits[2] * 16 + digits[3]);
	rgb[2] = (digits[4] * 16 + digits[5]);
	free(digits);
	return (rgb);
}

/**
 * logic to parse 3 different color Hexcodes
*/
int	*rgb_decider(char *str, int *digits)
{	
	int	i;
	int	j;

	j = 0;
	i = ft_strlen(str) - 6;
	if (str[ft_strlen(str) - 5] == 'x')
	{
		i = ft_strlen(str) - 4;
		j = 2;
	}
	else if (str[ft_strlen(str) - 3] == 'x')
	{
		i = ft_strlen(str) - 2;
		j = 4;
	}
	while (str[i] != '\0')
	{
		if ((int)str[i] >= 65 && (int)str[i] <= 71)
			digits[j ++] = (int)str[i ++] - 55;
		else if ((int)str[i] >= 97 && (int)str[i] <= 102)
			digits[j ++] = (int)str[i ++] - 55 - 32;
		else if ((int)str[i] >= 48 && (int)str[i] <= 57)
			digits[j ++] = str[i ++] - '0';
	}
	return (digits);
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

char	*trim(char **line)
{
	char	*tmp;

	tmp = ft_strtrim(*line, "\n, ");
	free(*line);
	return (tmp);
}
