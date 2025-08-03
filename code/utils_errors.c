/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 22:16:42 by leberton          #+#    #+#             */
/*   Updated: 2025/08/03 21:05:51 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	exit_error(char *message, t_data *data)
{
	ft_printf("%s\n", message);
	free_all(data);
	exit(EXIT_FAILURE);
}

int	exit_success(char *message, t_data *data)
{
	ft_printf("%s\n", message);
	free_all(data);
	exit(EXIT_SUCCESS);
}
