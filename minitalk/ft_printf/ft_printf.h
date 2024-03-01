/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:52:21 by vsarana           #+#    #+#             */
/*   Updated: 2023/05/16 18:13:18 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

int		ft_printf(const char *format, ...);
int		ft_putchar(int c);
int		ft_putstr(char *s);
int		ft_putptr(uintptr_t ptr, const char format);
int		ft_putnbr(int n);
int		ft_unsign_nbr(unsigned int n);
int		ft_puthex(uintptr_t ptr, const char format);
char	*ft_itoa(int n);
char	*ft_unsign_itoa(unsigned int n);

#endif
