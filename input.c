/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 11:29:39 by aestraic          #+#    #+#             */
/*   Updated: 2022/12/21 13:25:21 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

bool	input_handling(int argc, char **argv)
{
	char	*path;
	int		fd;

	if (argc != 2)
	{
		ft_printf("Wrong Input\n");
		return (false);
	}
	path = ft_strjoin("./test_maps/", argv[1]);
	fd = open(path, O_RDONLY);
	free(path);
	if (fd == -1)
	{
		ft_printf("Wrong Input\n");
		return (false);
	}
	return (true);
}

void	controls(void)
{
	ft_printf("\n----------Controls----------\n");
	ft_printf("*Translate with Arrows\n");
	ft_printf("*Change angles with LShift + (Arrows || Lctrl || Num0)\n");
	ft_printf("*Zoom with LShift + (+ || -)\n");
	ft_printf("*Press P fast to switch between perspective and\
 isometric projection\n");
	ft_printf("*Press 1 to switch to top-view\n");
	ft_printf("*In perspective projection:\n\
	Use TAB + (Arrows || Lctrl || Num0) to translate projection in\
 directions\n\tof the relative coordinate system");
}

bool	equal(int a, int b, int c, int d)
{
	if (a == b && c == d)
		return (true);
	return (false);
}
