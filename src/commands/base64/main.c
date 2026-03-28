/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 10:38:37 by mbatty            #+#    #+#             */
/*   Updated: 2026/03/28 10:32:33 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64_ctx.h"
#include "input.h"
#include "ft_printf.h"
#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdint.h>

void	base64_encode(int fd, uint8_t *input, uint64_t len);
void	base64_decode(int fd, uint8_t *input, uint64_t len);

typedef void(*t_base64_func)(int, uint8_t*, uint64_t);

int	base64_exec(t_base64_ctx *ctx, t_base64_func fn)
{
	t_input	in;
	int		fd;

	if (ctx->input._str)
	{
		if (input_get(&in, INPUT_FILE, ctx->input._str, 0) == -1)
			return (-1);
	}
	else
	{
		if (input_get(&in, INPUT_STDIN, NULL, 0) == -1)
			return (-1);
	}

	if (ctx->output._str)
	{
		fd = open(ctx->output._str, O_WRONLY | O_CREAT, 0644);
		if (fd == -1)
		{
			input_free(&in);
			return (ft_dprintf(2, "ft_ssl: %s: %s\n", ctx->output._str, strerror(errno)), -1);
		}
	}
	else
		fd = 1;

	fn(fd, in.bytes, in.size);

	input_free(&in);
	if (fd != 1)
		close(fd);
	return (0);
}

int	base64_main(char **av)
{
	t_base64_ctx	ctx;

	if (base64_ctx_init(&ctx, &av) == -1)
		return (1);

	if (ctx.string._str)
	{
		if (ctx.encode._bool && !ctx.decode._bool)
			base64_encode(1, (uint8_t*)ctx.string._str, ft_strlen(ctx.string._str));
		else if (ctx.decode._bool)
			base64_decode(1, (uint8_t*)ctx.string._str, ft_strlen(ctx.string._str));
	}
	else
	{
		if (ctx.encode._bool && !ctx.decode._bool)
			base64_exec(&ctx, base64_encode);
		else if (ctx.decode._bool)
			base64_exec(&ctx, base64_decode);
	}

	base64_ctx_delete(&ctx);
	return (1);
}
