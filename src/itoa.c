/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 14:51:56 by mbatty            #+#    #+#             */
/*   Updated: 2026/03/01 14:52:12 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#define LOWER_HEX		"0123456789abcdef"

static void	ft_itoa_hex_rec(char *buf, uint32_t n, uint32_t level, uint32_t *i)
{
	if (n <= 15)
	{
		if (level == 0)
		{
			buf[*i] = '0';
			(*i)++;
		}
		buf[*i] = LOWER_HEX[n % 16];
		(*i)++;
		return ;
	}
	ft_itoa_hex_rec(buf, n / 16, level + 1, i);
	ft_itoa_hex_rec(buf, n % 16, level + 1, i);
}

void	ft_itoa_hex(char *buf, uint32_t n)
{
	uint32_t	i = 0;

	ft_itoa_hex_rec(buf, n, 0, &i);
}
