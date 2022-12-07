/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 11:11:12 by aestraic          #+#    #+#             */
/*   Updated: 2022/07/08 12:20:33 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <libft.h>

static int	ft_signs(char c, va_list arg_list)
{
	unsigned int	i;

	i = 0;
	if (c == 'c')
		i = ft_conv_character(arg_list);
	else if (c == 'd' || c == 'i')
		i = ft_conv_int(arg_list);
	else if (c == 's')
		i = ft_conv_str(arg_list);
	else if (c == 'X')
		i = ft_conv_hex1(arg_list, 0);
	else if (c == 'x')
		i = ft_conv_hex1(arg_list, 1);
	else if (c == 'p')
		i = ft_conv_pointer(arg_list);
	else if (c == 'u')
		i = ft_conv_unsigned(arg_list);
	else if (c == '%')
	{
		ft_putchar_fd('%', 1);
		return (-1);
	}
	return (i - 2);
}

int	ft_printf(const char *s, ...)
{
	size_t		len;
	size_t		i;
	va_list		arg_list;
	size_t		count;

	count = 0;
	i = 0;
	len = 0;
	va_start(arg_list, s);
	len = ft_strlen(s);
	while (i < len)
	{
		if (s[i] != '%')
			ft_putchar_fd(s[i], 1);
		else
		{
			count = count + ft_signs(s[i + 1], arg_list);
		i++;
		}
		i++;
	}
	va_end(arg_list);
	return (i + count);
}
