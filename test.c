/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:36:03 by aestraic          #+#    #+#             */
/*   Updated: 2022/12/13 15:15:31 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

/**
 * main function without mlx for testing simple functions
*/
// int32_t	main(int argc, char **argv)
// {
// 	t_readmap		*map_data;
// 	t_trans	*transform;

// 	ft_printf("ARGC: %d\n",argc);
// 	map_data = ft_calloc(sizeof(t_readmap), 1);
// 	transform = ft_calloc(sizeof(t_trans), 1);
// 	transform->b_x = ft_calloc(sizeof(int), map_data->total_count);
// 	transform->b_y = ft_calloc(sizeof(int), map_data->total_count);
// 	get_map_information(argv[1], map_data);

// 	transformation(map_data, transform);

// 	//system("leaks test");
// 	return (EXIT_SUCCESS);
// }
/**
 * main function with mlx
*/
int32_t	main(int argc, char **argv)
{
	mlx_t		*mlx;
	mlx_image_t	*g_img;
	t_readmap	*map_data;
	t_trans		*transform;

	ft_printf("ARGC: %d\n", argc);
	ft_printf("\n----------Controls----------\n");
	transform = ft_calloc(sizeof(t_trans), 1);
	map_data = ft_calloc(sizeof(t_readmap), 1);
	init_map(argv[1], map_data, transform);
	mlx = transform->mlx;
	g_img = transform->img;
	mlx_image_to_window(mlx, g_img, 0, 0);
	transformation(transform);
	draw_image(g_img, transform);
	mlx_loop_hook(mlx, &hook, transform);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	fr_dblsgl_p((void **)map_data->values_matrix, NULL, map_data->total_count);
	fr_dblsgl_p((void **)map_data->rgb_values, NULL, map_data->total_count);
	free(map_data);
	// system("leaks test"); 
	return (EXIT_SUCCESS);
}
