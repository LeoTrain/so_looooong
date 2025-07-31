/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 22:16:42 by leberton          #+#    #+#             */
/*   Updated: 2025/07/31 11:23:11 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>

int	ft_puterror(char *message, t_data *data)
{
	printf("%s\n", message);
	free_all(data);
	exit(EXIT_FAILURE);
}

