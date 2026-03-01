/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:36:24 by mbatty            #+#    #+#             */
/*   Updated: 2026/03/01 19:13:57 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "base64.h"
#include "libft.h"
#include "ft_printf.h"
#include "input.h"

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void	base64_encode(int fd, uint8_t *input, uint64_t len);
void	base64_decode(int fd, uint8_t *input, uint64_t len);

typedef void(*t_base64_func)(int, uint8_t*, uint64_t);

int	base64_exec(t_ctx *ctx, t_base64_func fn)
{
	t_input	in;
	int		fd;

	if (ctx->input._str)
		input_get(&in, INPUT_FILE, ctx->input._str, 0);
	else
		input_get(&in, INPUT_STDIN, NULL, 0);

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

int	base64_dispatch(void *ctx_ptr)
{
	t_ctx	*ctx = ctx_ptr;

	if (ctx->encode._bool && !ctx->decode._bool)
		return (base64_exec(ctx, base64_encode));
	else if (ctx->decode._bool)
		return (base64_exec(ctx, base64_decode));
	return (0);
}
