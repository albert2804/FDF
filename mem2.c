/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 17:50:02 by aestraic          #+#    #+#             */
/*   Updated: 2022/12/22 18:21:06 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	free_vertices(t_readmap *map_data)
{
	free(map_data);
	exit(EXIT_FAILURE);
}

void	free_values(t_readmap *map_data, int **matrix, int row)
{
	free(map_data);
	fr_dblsgl_p((void **)matrix, NULL, row);
	exit(EXIT_FAILURE);
}

void	free_rgbv(t_readmap *map_data)
{
	fr_dblsgl_p((void **)map_data->values_matrix, NULL, map_data->total_count);
	free(map_data);
	exit(EXIT_FAILURE);
}

void	free_rgbc(t_readmap *map_data, int **rgb_values, int count)
{
	fr_dblsgl_p((void **)map_data->values_matrix, NULL, map_data->total_count);
	fr_dblsgl_p((void **)rgb_values, NULL, count);
	free(map_data);
	exit(EXIT_FAILURE);
}

void	free_digits(t_readmap *map_data, int **rgb_values, int count, int *rgb)
{
	free_rgbc(map_data, rgb_values, count);
	free(rgb);
	free(map_data);
	exit(EXIT_FAILURE);
}
