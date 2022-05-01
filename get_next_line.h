#ifndef GET_NEXT_LINE_H

# ifndef BUFF_SIZE
# 	define BUFF_SIZE 32
# endif

# include <stdlib.h>
# include <stddef.h>
# include <stdio.h>
# include <string.h>

typedef struct node
{
	char		*content;
	struct node *next;
}	list;

list	*ft_lst_get_last(list	*stash);
list	*lst_new(void	*content);
list	*lst_last(list	*lst);

void    add_buff_to_stash(list	**stash, char	*content);
void 	get_line_from_stash(list *stash, char **line);
void	generate_line(char	**line, list	*stash);
void	lst_add_back(list	**lst, list	*new);
void	remove_line_from_stash(list **stash);
void 	free_stash(list **stash);

char 	*get_next_line(int	fd);

int 	stash_has_new_line(list	**stash, char	**line);
int 	stash_has_null_char(list **stash, char	**line);
int		lst_display(list	*lst);

#endif