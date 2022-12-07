/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 12:25:09 by aestraic          #+#    #+#             */
/*   Updated: 2022/11/22 17:00:36 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	ft_digit_count(int n)
{
	int	digit_count;

	digit_count = 0;
	if (n < 0)
		n = n * (-1);
	while (n / 10 != 0)
	{
		n = n / 10;
		digit_count++;
	}
	return (digit_count + 1);
}

static void	ft_create_string(char *str, int n)
{
	int				digit_count;
	int				i;
	unsigned int	n_buff;

	digit_count = ft_digit_count(n);
	i = 0;
	if (n < 0)
	{
		n_buff = n *(-1);
		str[0] = '-';
		digit_count ++;
	}
	else
		n_buff = n;
	if (n_buff == 0)
	{
		str[0] = '0';
	}
	while (n_buff > 0)
	{
		str[digit_count - i - 1] = (n_buff % 10) + '0';
		n_buff /= 10;
		i++;
	}
	str[digit_count] = '\0';
}

char	*ft_itoa(int n)
{
	char	*str;
	int		digit_count;

	digit_count = ft_digit_count(n);
	if (n < 0)
		digit_count ++;
	str = malloc(digit_count * sizeof(char) + 1);
	if (!str)
		return (NULL);
	ft_create_string(str, n);
	return (str);
}
