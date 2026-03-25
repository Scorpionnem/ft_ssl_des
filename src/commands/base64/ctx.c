/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 10:38:39 by mbatty            #+#    #+#             */
/*   Updated: 2026/03/25 21:00:11 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64_ctx.h"
#include "ft_printf.h"
#include <stdlib.h>

int	base64_ctx_init_opts(t_base64_ctx *ctx, char ***av);

#define BASE64_HELP_STRING "\
\n\
Usage:\n  ./ft_ssl base64 [options]\n\
\n\
Options:\n\
  -h --help\t\tshow help message and exit\n\
  -d --decode\t\tdecode mode\n\
  -e --encode\t\tencode mode\n\
  -i --input <string>\tinput file\n\
  -o --output <string>\toutput file\n\
\n\
"

int	base64_ctx_init(t_base64_ctx *ctx, char ***av)
{
	if (base64_ctx_init_opts(ctx, av) == -1)
		return (-1);
	if (ctx->help._bool)
	{
		opt_ctx_delete(&ctx->opt_ctx);
		ft_dprintf(2, BASE64_HELP_STRING);
		return (-1);
	}

	return (0);
}

void	base64_ctx_delete(t_base64_ctx *ctx)
{
	opt_ctx_delete(&ctx->opt_ctx);
}

int	base64_ctx_init_opts(t_base64_ctx *ctx, char ***av)
{
	opt_ctx_init(&ctx->opt_ctx);

	opt_ctx_add_opt(&ctx->opt_ctx, "-h", &ctx->help, OPT_BOOL);
	opt_ctx_add_opt(&ctx->opt_ctx, "--help", &ctx->help, OPT_BOOL);

	opt_ctx_add_opt(&ctx->opt_ctx, "-d", &ctx->decode, OPT_BOOL);
	opt_ctx_add_opt(&ctx->opt_ctx, "--decode", &ctx->decode, OPT_BOOL);

	opt_ctx_add_opt(&ctx->opt_ctx, "-e", &ctx->encode, OPT_BOOL);
	opt_ctx_add_opt(&ctx->opt_ctx, "--encode", &ctx->encode, OPT_BOOL);

	ctx->encode._bool = true;

	opt_ctx_add_opt(&ctx->opt_ctx, "-i", &ctx->input, OPT_STR);
	opt_ctx_add_opt(&ctx->opt_ctx, "--input", &ctx->input, OPT_STR);

	opt_ctx_add_opt(&ctx->opt_ctx, "-o", &ctx->output, OPT_STR);
	opt_ctx_add_opt(&ctx->opt_ctx, "--output", &ctx->output, OPT_STR);

	if (opt_ctx_parse(&ctx->opt_ctx, av) == -1)
	{
		opt_ctx_delete(&ctx->opt_ctx);
		return (-1);
	}
	return (0);
}
