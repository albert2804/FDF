/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 12:25:09 by aestraic          #+#    #+#             */
/*   Updated: 2022/11/22 17:00:36 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	n_buff;

	n_buff = n;
	if (n < 0)
	{
		n_buff = -n;
		ft_putchar_fd('-', fd);
	}
	if (n_buff > 9)
	{
		ft_putnbr_fd(n_buff / 10, fd);
		ft_putchar_fd((n_buff % 10) + '0', fd);
	}
	else if (n_buff / 10 == 0)
		ft_putchar_fd((n_buff % 10) + '0', fd);
}
