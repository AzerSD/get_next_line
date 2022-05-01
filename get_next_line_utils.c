/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azer <sioudazer8@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 22:26:59 by azer              #+#    #+#             */
/*   Updated: 2022/04/10 22:26:59 by azer             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void    add_buff_to_stash(list **stash, char *buff) // tested, don't touch bitch 
{
	int		i;
	list	*last;
	list	*new_node;
	// lst_display(*stash);
	new_node = malloc(sizeof(list));
	if (new_node == NULL)
		return ;
	new_node->next = NULL;
	new_node->content = malloc(sizeof(char) * (BUFF_SIZE));
	if (new_node->content == NULL)
		return ;
	i = 0;
	while (buff[i] && i < BUFF_SIZE)
	{
		new_node->content[i] = buff[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (*stash == NULL)
	{
		*stash = new_node;
		return ;
	}
	last = ft_lst_get_last(*stash);
	last->next = new_node;
	return ;
}

void	generate_line(char **line, list *stash)
{
	int	i;
	int	len;

	len = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		stash = stash->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
}

list	*ft_lst_get_last(list *stash) // tested, don't touch bitch 
{
	list	*current;

	current = stash;
	while (current && current->next)
		current = current->next;
	return (current);
}

void 	free_stash(list **stash) // tested, don't touch bitch 
{
    list *current = *stash;
    list *next;

    while (current != NULL)
    {
       next = current->next;
       free(current);
       current = next;
    }
    *stash = NULL;
}

void 	get_line_from_stash(list *stash, char **line)
{
	int	i;
	int	j;

	if (stash == NULL)
		return ;
	generate_line(line, stash);
	if (*line == NULL)
		return ;
	j = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				(*line)[j++] = stash->content[i];
				break ;
			}
			(*line)[j++] = stash->content[i++];
		}
		stash = stash->next;
	}
	(*line)[j] = '\0';
}

void	remove_line_from_stash(list **stash) // tested, don't touch bitch 
{
	list	*last_node;
	list	*clean_node; // from ato\nmic to mic
	int		i;
	int		j;

	clean_node = malloc(sizeof(list));
	if (!stash || !clean_node)
		return ;

	clean_node->next = NULL;
	last_node = ft_lst_get_last(*stash);
	i = 0;
	while (last_node->content[i] && last_node->content[i] != '\n')
			i++;
	if (last_node->content && last_node->content[i] == '\n')
		i++;

	clean_node->content = malloc(sizeof(char) * ((strlen(last_node->content) - i) + 1));
	if (clean_node->content == NULL)
		return ;
	j = 0;
	while (last_node->content[i])
		clean_node->content[j++] = last_node->content[i++]; 
	clean_node->content[j] = '\0';
	free_stash(stash);
	*stash = clean_node;
}

int 	lst_display(list *lst) // tested, don't touch bitch 
{
	int i;

	i = 0;
	printf("/////////// list /////////////\n");
	while (lst)
	{
		printf("%d: %s\n", i, lst->content);
		lst = lst->next;
		i++;
	}
	printf("///////// end of List //////////\n");
	return (i);
}

int 	stash_has_new_line(list **stash, char **line)
{
	int		i;
	list	*current;

	current = ft_lst_get_last(*stash);
	// check Last Element of the List

	i = 0;
	while (current->content[i])
	{
		if (current->content[i] == '\n')
		{
			get_line_from_stash(*stash, line);
			remove_line_from_stash(&(*stash));
			return (1);
		}
		i++;
	}
	return (0);
}

int 	stash_has_null_char(list **stash, char **line)
{
	int		i;
	list	*current;

	current = ft_lst_get_last(*stash);
	// check Last Element of the List

	i = 0;
	while (i < BUFF_SIZE)
	{
		if (current->content[i] == '\0')
		{
			get_line_from_stash(*stash, line);
			remove_line_from_stash(&(*stash));
			return (1);
		}
		i++;
	}
	return (0);
}