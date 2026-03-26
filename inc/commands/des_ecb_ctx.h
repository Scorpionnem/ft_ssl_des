/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb_ctx.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 21:04:59 by mbatty            #+#    #+#             */
/*   Updated: 2026/03/26 14:07:38 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "opt.h"
#include <stdint.h>

typedef struct	s_des_ecb_ctx
{
	char	***av;

	t_opt_ctx			opt_ctx;

	t_opt				help;

	t_opt				b64_encode;
	t_opt				encrypt;
	t_opt				decrypt;

	t_opt				input;
	t_opt				output;

	t_opt				key_opt;
	t_opt				password_opt;
	t_opt				salt_opt;
	t_opt				init_vector_opt;

	uint8_t				key[8];
	uint8_t				salt[8];
	char				*password;
}	t_des_ecb_ctx;

int		des_ecb_ctx_init(t_des_ecb_ctx *ctx, char ***av);
void	des_ecb_ctx_delete(t_des_ecb_ctx *ctx);
