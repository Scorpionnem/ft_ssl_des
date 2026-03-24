/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:34:23 by mbatty            #+#    #+#             */
/*   Updated: 2026/03/01 19:34:27 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64.h"
#include "ft_printf.h"
#include "libft.h"

#include <stdint.h>
#include <stdlib.h>

#define BASE64 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

void	base64_encode(int fd, uint8_t *input, uint64_t len)
{
	for (uint64_t i = 0; i < len; i += 3)
	{
		uint32_t a = input[i];
		uint32_t b = (i + 1 < len) ? input[i + 1] : 0;
		uint32_t c = (i + 2 < len) ? input[i + 2] : 0;

		uint32_t triple = (a << 16) | (b << 8) | c;

		ft_dprintf(fd, "%c", BASE64[(triple >> 18) & 0b00111111]);
		ft_dprintf(fd, "%c", BASE64[(triple >> 12) & 0b00111111]);

		if (i + 1 < len)
			ft_dprintf(fd, "%c", BASE64[(triple >> 6) & 0b00111111]);
		else
			ft_dprintf(fd, "=");

		if (i + 2 < len)
			ft_dprintf(fd, "%c", BASE64[triple & 0b00111111]);
		else
			ft_dprintf(fd, "=");
	}
	ft_dprintf(fd, "\n");
}

static int	base64_index(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c - 'A');
	if (c >= 'a' && c <= 'z')
		return (c - 'a' + 26);
	if (c >= '0' && c <= '9')
		return (c - '0' + 52);
	if (c == '+')
		return (62);
	if (c == '/')
		return (63);
	if (c == '=')
		return (0);
	return (-1);
}

void	base64_decode(int fd, uint8_t *input, uint64_t len)
{
	uint8_t	block[4];
	int		count = 0;

	for (uint64_t i = 0; i < len; i++)
	{
		char c = input[i];

		if (c == '\n' || c == '\r' || c == ' ' || c == '\t')
			continue ;

		if (!ft_strchr(BASE64, c) && c != '=')
		{
			ft_dprintf(2, "Invalid base64\n");
			return ;
		}

		block[count++] = c;

		if (count == 4)
		{
			int	v0 = base64_index(block[0]);
			int	v1 = base64_index(block[1]);
			int	v2 = base64_index(block[2]);
			int	v3 = base64_index(block[3]);

			uint32_t	triple = (v0 << 18) | (v1 << 12) | (v2 << 6) | v3;

			uint8_t	b1 = (triple >> 16) & 0xFF;
			uint8_t	b2 = (triple >> 8) & 0xFF;
			uint8_t	b3 = triple & 0xFF;

			ft_dprintf(fd, "%c", b1);
			if (block[2] != '=')
				ft_dprintf(fd, "%c", b2);
			if (block[3] != '=')
				ft_dprintf(fd, "%c", b3);

			count = 0;
		}
	}
}
