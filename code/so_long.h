#ifndef SO_LONG_H
#define SO_LONG_H

#include "minilibx-linux/mlx.h"
#include "get_next_line/get_next_line.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h>

typedef struct s_position
{
	int x;
	int y;
}	t_position;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

char	*ft_strdup(const char *s);
void	ft_lstadd_back(t_list **lst, t_list *n);
void	ft_lstadd_front(t_list **lst, t_list *n);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void	*content);
int     ft_lstsize(t_list *lst);

#endif
