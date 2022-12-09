/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:36:03 by aestraic          #+#    #+#             */
/*   Updated: 2022/12/09 11:56:13 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	hook(void *param)
{
	t_trans		*transform;
	mlx_t		*mlx;
	mlx_image_t	*g_img;
	
	transform = param;
	mlx = transform->mlx;
	g_img = transform->img;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		g_img->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		g_img->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		g_img->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		g_img->instances[0].x += 5;
}

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
	
	ft_printf("ARGC: %d\n",argc);
	map_data = ft_calloc(sizeof(t_readmap), 1);
	transform = ft_calloc(sizeof(t_trans), 1);
	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	g_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	// init_mlx(g_img, mlx, transform);
	transform->img = g_img;
	transform->mlx = mlx;
	mlx_image_to_window(mlx, g_img, 0, 0);
	
	init_map(argv[1], map_data, transform);
	transformation(map_data, transform);
	draw_image(g_img, map_data, transform);
	
	mlx_loop_hook(mlx, &hook, transform);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	fr_dblsgl_p((void **)map_data->values_matrix, NULL, map_data->total_count);
	free(map_data);
	
	
	// system("leaks test");
	return (EXIT_SUCCESS);
}
