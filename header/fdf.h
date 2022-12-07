/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 15:58:50 by aestraic          #+#    #+#             */
/*   Updated: 2022/12/07 13:24:02 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# ifndef WIDTH
#  define WIDTH 1200
# endif

# ifndef HEIGHT
#  define HEIGHT 1200
# endif

# include <fcntl.h>
# include <limits.h>
# include <memory.h>
# include <math.h>

# include <libft.h>
# include "../mlx/include/MLX42/MLX42.h"

//STRUCTS
/**
 * Stores initial information about the map, 
 * which are read in from test_maps.
 * 
 * @param count_x Counts the nodes in x-direction
 * @param count_y Counts the nodes in y-direction
 * @param total_count Represents total count of nodes (=count_x * count_y)
 * @param max_xy Represents the max-value between count_x and count_y 
 * @param values_matrix Stores the xyz-positions of all nodes in the form
 * 						 [[x1,y1,z1], [x2, y2, z2], ...] + color_code
 * @param delta Represents the distance between nodes in xy-direction
 * @param offset_x Represents the x-offset from Imageeckpunkt x (0,0)
 * @param offset_y Represents the y-offset from Imageeckpunkt y (0,0)
 * @param center Represents the center coordiantes in x-y direction.
 */
typedef struct s_readmap
{
	size_t		count_x;
	size_t		count_y;
	size_t		max_xy;
	int			delta;
	int			offset_x;
	int			offset_y;
	int			center_x;
	int			center_y;
	int			center_z;
	size_t		total_count;
	int			**values_matrix;
}			t_readmap;
/**
 * Used for storing calculation values, dependng on the viewing angle.
 * @param angle Represents the viewing angle
 * @param matrix Stores the newly calculated values for of each node in 
 * 						3D representation in the form  [[x1,y1,z1],[x2,y2,z1],...]
 * 						, depending on the viewing angles and distance of the "camera(view point)"
 * @param b_x Represents the x-coordiante of the 2D-depiction of all nodes.
 * @param b_y Represents the y-coordiante of the 2D-depiction of all nodes.
*/
typedef struct s_trans
{
	size_t	alpha;
	size_t	beta;
	size_t	gamma;
	int		**matrix;
	int		*b_x;
	int		*b_y;
}			t_trans;

/**
 * main struct for connecting all structs
*/
typedef struct s_map
{
	t_readmap	*readmap;
	t_trans		*trans;
	mlx_t		*mlx;
	mlx_image_t	*g_img;
}			t_map;
//Initialize Map
size_t			ft_count_spaces(char *c);
void			read_map_vertices(int fd, t_readmap *map_data);
void			get_map_information(char *map_name, t_readmap *map_data);
void			store_positions(char *line, t_readmap *map_data);
void			xyz_pos(int fd, size_t row, size_t col, t_readmap *map_data);

//Transform from 2D into 3D
void			transformation(t_readmap *map_data, t_trans *transform);
//Utils
void			find_max_nbr(size_t *array, t_readmap *map_data);
void			fr_dblsgl_p(void **dbl, void *sgl, size_t c);
int				get_rgba(int r, int g, int b, int a);
void			determine_delta(t_readmap *map_data);
void			determine_center(t_readmap *map_data);

//Draw-Utils
void			draw_image(mlx_image_t *g_img, t_readmap *map_data, t_trans *calc);
void			hor_line(size_t node, t_readmap *map_data, mlx_image_t *g_img, t_trans *trans);
void			ver_line(size_t node, t_readmap *map_data, mlx_image_t *g_img, t_trans *trans);
void			bresenham(mlx_image_t *g_img, int x0, int x1, int y0, int y1);
void 			draw_grid(t_readmap *map_data, t_trans *transform, mlx_image_t *g_img);
void			ft_putpixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color);

#endif