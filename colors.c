/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:49:03 by aestraic          #+#    #+#             */
/*   Updated: 2022/12/13 15:52:03 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
/**
 * reads the color code from the testmaps 
 * in hexa and transforms it into RGB. The values will be stored in 
 * the map_data struct inside map_data->colors_matrix.
*/
void	read_color(int fd, size_t row, size_t i, t_readmap *map_data)
{
	char	*line;
	int		**rgb_values;
	char	**split;
	int		node;

	node = 0;
	rgb_values = ft_calloc(sizeof(int *), map_data->total_count);
	while (row < map_data->count_y)
	{
		i = 0;
		line = get_next_line(fd);
		split = ft_split(line, ' ');
		while (split[i] != NULL)
			rgb_values[node ++] = rgb_converter(split[i ++]);
		row ++;
		fr_dblsgl_p((void **)split, (void *)line, map_data->count_x);
	}
	map_data->rgb_values = rgb_values;
}

int	*rgb_converter(char *str)
{
	int	*digits;
	int	*rgb;
	int	i;
	int	j;

	if (str[ft_strlen(str) - 1] == '\n')
		str[ft_strlen(str) - 1] = '\0';
	rgb = ft_calloc(sizeof(int), 3);
	if (ft_strchr(str, 'x') == 0)
		return (rgb[0] = 255, rgb[1] = 255, rgb[2] = 255, rgb);
	digits = ft_calloc(sizeof(int), 6);
	i = ft_strlen(str) - 6;
	j = 0;
	while (str[i] != '\0')
	{
		if ((int)str[i] >= 65)
			digits[j ++] = (int)str[i ++] - 55;
		else if ((int)str[i] >= 48 && (int)str[i] <= 57)
			digits[j ++] = str[i ++] - '0';
	}
	rgb[0] = (digits[0] * 16 + digits[1]);
	rgb[1] = (digits[2] * 16 + digits[3]);
	rgb[2] = (digits[4] * 16 + digits[5]);
	free(digits);
	return (rgb);
}
