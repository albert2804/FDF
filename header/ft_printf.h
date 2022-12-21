/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:26:10 by aestraic          #+#    #+#             */
/*   Updated: 2022/12/21 15:49:39 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <libft.h>

int		ft_printf(const char *s, ...);
int		ft_conv_character(va_list arg_list);
int		ft_conv_int(va_list arg_list);
int		ft_conv_str(va_list arg_list);
int		ft_conv_hex1(va_list arg_list, int k);
int		ft_conv_pointer(va_list arg_list);
int		ft_conv_unsigned(va_list arg_list);
char	*ft_itoa_u(unsigned int n);
int		ft_digit_count_u(unsigned int n);
void	ft_create_string_u(char *str, unsigned int n);

#endif