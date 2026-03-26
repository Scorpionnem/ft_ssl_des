/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:57:01 by mbatty            #+#    #+#             */
/*   Updated: 2026/03/26 14:08:00 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des_ecb_ctx.h"
#include "libft.h"
#include "ft_printf.h"
#include "input.h"
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

char	*get_password(void)
{
	char	*password = ft_strdup(getpass("enter des-ecb encryption password: "));
	if (!password)
		return (NULL);

	char	*password_verif = ft_strdup(getpass("Verifying - enter des-ecb encryption password: "));
	if (!password_verif)
		return (NULL);

	if (ft_strcmp(password, password_verif))
	{
		ft_dprintf(2, "ft_ssl: bad password: invalid match\n");
		free(password);
		free(password_verif);
		return (NULL);
	}
	free(password_verif);
	return (password);
}

int	parse_hex(const char *hex, uint8_t buf[8])
{
	for (int i = 0; i < 8; i++)
	{
		char	byte_str[3] = {hex[i * 2], hex[i * 2 + 1], 0};
		buf[i] = (uint8_t)ft_atoi_hex(byte_str);
	}
	return (0);
}

int	get_salt(uint8_t salt[8])
{
	int fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		return (-1);
	if (read(fd, salt, 8) != 8)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

char	*get_key(t_des_ecb_ctx *ctx)
{
	ctx->password = ctx->password_opt._str ? ft_strdup(ctx->password_opt._str) : get_password();
	if (!ctx->password)
		return (NULL);
	if ((ctx->salt_opt._str ? parse_hex(ctx->salt_opt._str, ctx->salt) : get_salt(ctx->salt)) == -1)
		return (NULL);

	return (NULL);
}

int	des_ecb_main(char **av)
{
	t_des_ecb_ctx	ctx;

	if (des_ecb_ctx_init(&ctx, &av) == -1)
		return (1);

	if (!ctx.key_opt._str)
		get_key(&ctx);

	des_ecb_ctx_delete(&ctx);
	return (0);
}
