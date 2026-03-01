/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:34:07 by mbatty            #+#    #+#             */
/*   Updated: 2026/03/01 19:31:22 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define UNUSED(x)	_unused_##x __attribute__((unused))

#include "opt.h"
#include "md5.h"
#include "sha256.h"
#include "base64.h"

typedef int (*t_command_func)(void *ctx);

typedef struct	s_ctx
{
	char	***av;

	t_command_func	fn;
	char		*fn_str;

	t_opt_ctx			opt_ctx;

	t_opt				help;

	// MD5 - SHA256
	t_opt				echo;
	t_opt				quiet;
	t_opt				reverse;
	t_opt				string;

	// BASE64 - DES
	t_opt				decode;
	t_opt				encode;
	t_opt				input;
	t_opt				output;
	// DES
	t_opt				base64_io; // decode/encode the input/output in base64, depending on the encrypt mode
	t_opt				key;
	t_opt				password;
	t_opt				salt;
	t_opt				init_vector;
}	t_ctx;

int		ctx_init(t_ctx *ctx, char ***av);
void	ctx_delete(t_ctx *ctx);

int	ft_putnbr_hex_u(unsigned long int n, int level);
