/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 09:46:19 by mbatty            #+#    #+#             */
/*   Updated: 2026/03/02 10:43:34 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "md5.h"
#include "libft.h"
#include "ft_printf.h"
#include "input.h"
#include "itoa.h"

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

int	des_get_key(t_ctx *ctx, uint64_t *key)
{
	char	*pass;
	if (!ctx->password->_str)
	{
		char	*p = getpass("enter des-ecb encryption password:");
		pass = ft_strdup(p);
		p = getpass("Verifying - enter des-ecb encryption password:");
		char	*pass_verif = ft_strdup(p);

		if (ft_strcmp(pass, pass_verif))
		{
			ft_dprintf(2, "Invalid password: Verify failure\n");
			return (-1);
		}
	}
	else
		pass = ft_strdup(ctx->password->_str);

	uint64_t	salt = 0;
	if (!ctx->salt->_str)
	{
		int	fd = open("/dev/urandom", O_RDONLY);
		read(fd, &salt, sizeof(uint64_t));
		close(fd);
	}
	else
		salt = ft_atoi_hex(ctx->salt->_str);

	uint64_t	pass_size = ft_strlen(pass) * sizeof(char);
	uint64_t	size = pass_size + sizeof(uint64_t);

	uint8_t	*md_key = malloc(size);
	ft_memcpy(md_key, pass, pass_size);
	ft_memcpy(md_key + pass_size, &salt, sizeof(uint64_t));
	*key = md5_uint64(md_key, size);

	free(pass);
	free(md_key);
	return (0);
}

int	des_ecb_dispatch(void *ctx_ptr)
{
	t_ctx	*ctx = ctx_ptr;

	uint64_t	key = 0;
	if (!ctx->key._str)
	{
		if (des_get_key(ctx, &key) == -1)
			return (-1);
	}
	else
		key = ft_atoi_hex(ctx->key._str);

	printf("key =\t%lx\n", key);

	return (0);
}
