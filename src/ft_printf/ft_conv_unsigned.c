/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_unsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 11:07:47 by aestraic          #+#    #+#             */
/*   Updated: 2022/07/08 12:20:30 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_digit_count_u(unsigned int n)
{
	unsigned int	digit_count;

	digit_count = 0;
	while (n / 10 != 0)
	{
		n = n / 10;
		digit_count++;
	}
	return (digit_count + 1);
}

void	ft_create_string_u(char *str, unsigned int n)
{
	unsigned int	digit_count;
	unsigned int	i;
	unsigned int	n_buff;

	digit_count = ft_digit_count_u(n);
	i = 0;
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

char	*ft_itoa_u(unsigned int n)
{
	char			*str;
	unsigned int	digit_count;

	digit_count = ft_digit_count_u(n);
	str = malloc(digit_count * sizeof(char) + 1);
	if (!str)
		return (NULL);
	ft_create_string_u(str, n);
	return (str);
}

int	ft_conv_unsigned(va_list arg_list)
{
	char			*str;
	unsigned int	ret;

	str = ft_itoa_u(va_arg(arg_list, unsigned int));
	ret = ft_strlen(str);
	ft_putstr_fd(str, 1);
	free(str);
	return (ret);
}
