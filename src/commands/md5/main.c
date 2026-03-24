/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:57:01 by mbatty            #+#    #+#             */
/*   Updated: 2026/03/24 18:23:39 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5_ctx.h"
#include "libft.h"
#include "ft_printf.h"
#include "input.h"
#include <stdint.h>

char	*md5(uint8_t *msg, uint32_t len);

int	process_files(t_md5_ctx *ctx, char **av)
{
	while (*av)
	{
		t_input	in;

		if (input_get(&in, INPUT_FILE, *av, 0) == -1)
		{
			av++;
			continue ;
		}

		char	*h = md5(in.bytes, in.size);

		if (!ctx->reverse._bool && !ctx->quiet._bool)
			ft_printf("MD5 (%s) = %s\n", *av, h);
		if (ctx->reverse._bool && !ctx->quiet._bool)
			ft_printf("%s %s\n", h, *av);

		free(h);
		input_free(&in);
		av++;
	}
	return (0);
}

int	process_string(t_md5_ctx *ctx, char *str)
{
	char	*hash_str = md5((uint8_t*)str, ft_strlen(str));
	if (!hash_str)
		return (-1);

	if (!ctx->reverse._bool && !ctx->quiet._bool)
		ft_printf("MD5 (\"%s\") = %s\n", str, hash_str);
	if (ctx->reverse._bool && !ctx->quiet._bool)
		ft_printf("%s \"%s\"\n", hash_str, str);

	free(hash_str);
	return (0);
}

int	md5_main(char **av)
{
	t_md5_ctx	ctx;

	if (md5_ctx_init(&ctx, &av) == -1)
		return (1);

	if (ctx.string._str)
		process_string(&ctx, ctx.string._str);
	if (*av)
		process_files(&ctx, av);

	md5_ctx_delete(&ctx);
	return (0);
}
