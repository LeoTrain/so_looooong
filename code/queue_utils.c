/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:16:40 by leberton          #+#    #+#             */
/*   Updated: 2025/05/30 15:19:23 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

typedef struct s_queue_node
{
	t_position             pos;
	struct s_queue_node   *next;
}	t_queue_node;

struct s_queue
{
	t_queue_node *front;
	t_queue_node *rear;
};

t_queue	*queue_new(void)
{
	t_queue *q = malloc(sizeof(t_queue));
	if (!q)
		return (NULL);
	q->front = NULL;
	q->rear = NULL;
	return (q);
}

void	queue_push(t_queue *q, t_position pos)
{
	t_queue_node *new_node = malloc(sizeof(t_queue_node));
	if (!new_node)
		return;
	new_node->pos = pos;
	new_node->next = NULL;
	if (!q->rear)
	{
		q->front = new_node;
		q->rear = new_node;
	}
	else
	{
		q->rear->next = new_node;
		q->rear = new_node;
	}
}

t_position	queue_pop(t_queue *q)
{
	t_position null_pos = {-1, -1};
	if (!q->front)
		return null_pos;
	t_queue_node *tmp = q->front;
	t_position ret = tmp->pos;
	q->front = q->front->next;
	if (!q->front)
		q->rear = NULL;
	free(tmp);
	return ret;
}

int	queue_empty(t_queue *q)
{
	return (q->front == NULL);
}

void	queue_free(t_queue *q)
{
	while (!queue_empty(q))
		queue_pop(q);
	free(q);
}

