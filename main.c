/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:36:03 by aestraic          #+#    #+#             */
/*   Updated: 2022/12/22 17:56:47 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int32_t	main(int argc, char **argv)
{
	t_readmap	*map_data;
	t_trans		*transform;

	if (input_handling(argc, argv) == false)
		return (EXIT_FAILURE);
	controls();
	transform = ft_calloc(sizeof(t_trans), 1);
	if (!transform)
		exit (EXIT_FAILURE);
	map_data = ft_calloc(sizeof(t_readmap), 1);
	if (!map_data)
		free_map_data(transform);
	init_map(argv[1], map_data, transform);
	mlx_image_to_window(transform->mlx, transform->img, 0, 0);
	transformation(transform);
	draw_image(transform->img, transform);
	mlx_loop_hook(transform->mlx, &hook, transform);
	mlx_loop(transform->mlx);
	mlx_terminate(transform->mlx);
	fr_dblsgl_p((void **)map_data->values_matrix, NULL, map_data->total_count);
	fr_dblsgl_p((void **)map_data->rgb_values, NULL, map_data->total_count);
	free(map_data);
	system("leaks fdf");
	return (EXIT_SUCCESS);
}
