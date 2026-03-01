/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:34:33 by mbatty            #+#    #+#             */
/*   Updated: 2026/03/01 15:02:13 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "ft_printf.h"
#include "libft.h"
#include "input.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#define BASE64 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

void	base64(char *str)
{
	int	seq = 0;

	uint8_t	prev = 0;
	uint8_t	cur = *str;
	uint8_t	b = 0;
	size_t	i = 0;
	(void)str;
	while (i <= ft_strlen(str))
	{
		prev = cur;
		cur = str[i];

		if (seq == 0)
			b = (cur >> 2) & 0b00111111;
		if (seq == 1)
			b = ((prev & 0b00000011) << 4) | ((cur & 0b11110000) >> 4);
		if (seq == 2)
			b = ((prev & 0b00001111) << 2) | ((cur & 0b11000000) >> 6);
		if (seq == 3)
			b = prev & 0b00111111;

		printf("%c", BASE64[b]);

		i++;
		seq++;
		if (seq >= 4)
			seq = 0;
	}
	printf("\n");
}

int	main(int UNUSED(ac), char **av)
{
	t_ctx	ctx;

	if (ctx_init(&ctx, &av) == -1)
		return (1);

	ctx.av = &av;

	int	res = ctx.fn(&ctx);

	ctx_delete(&ctx);
	return (res);
}
