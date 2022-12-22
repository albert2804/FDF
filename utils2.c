/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 18:12:20 by aestraic          #+#    #+#             */
/*   Updated: 2022/12/22 18:24:52 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int	**cal_matrix(t_readmap *map_data)
{
	int	**matrix;

	matrix = ft_calloc(sizeof(int *), map_data->total_count);
	if (!matrix)
		free_matrix(map_data);
	return (matrix);
}

int	*cal_values(t_readmap *map_data, int **matrix, size_t row)
{
	int	*values;

	values = ft_calloc(sizeof(int), 3);
	if (!values)
		free_values(map_data, matrix, row);
	return (values);
}

size_t	*cal_vertices(t_readmap *map_data)
{
	size_t	*vertices;

	vertices = ft_calloc(sizeof(size_t), 2);
	if (!vertices)
		free_vertices(map_data);
	return (vertices);
}
