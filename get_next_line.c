/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azer <sioudazer8@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 04:32:02 by azer              #+#    #+#             */
/*   Updated: 2022/04/10 04:32:02 by azer             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

// Write a function that returns a line read from a file descriptor
// Read line: correct behavior
// NULL: there is nothing else to read, or an error
// occurred

// int main()
// {    
//     int fd;
// 	char *line;

// 	fd = open("f.txt", O_RDONLY);
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (line == NULL)
// 			break;
// 		printf("LINE: %s\n", line);
// 		free(line);
// 	}
//     return 0;
// }

char *get_next_line(int fd)
{
	static list	*stash;
	char		*line;
	char 		*buff;
	size_t		cnt;

	// if there's an error with open, , file is not readable
	if (fd < 0 || BUFF_SIZE < 1 || read(fd, &line, 0) < 0)
		return (NULL);

	// allocate the BUFF
	buff = (char *)malloc(BUFF_SIZE);
	if (!buff)
		return (NULL);

	// Fill the BUFF
	cnt = read(fd, buff, BUFF_SIZE);

	while (cnt)
	{
		buff[cnt] = '\0'; // null terminate the BUFF
		// printf("///////////// CNT: %lld ////////////////\n", cnt);
		// printf("BUFF: ");
		// write(1, buff, BUFF_SIZE);
		// printf("\n");
		add_buff_to_stash(&stash, buff);

		// lst_display(stash);

		if(!stash) // file is empty
			return (NULL);
		if (stash_has_new_line(&stash, &line))
		{
			free(buff);
			return (line);
		}
		cnt = read(fd, buff, BUFF_SIZE);
		if (stash_has_null_char(&stash, &line) && cnt == 0)
		{
			free(buff);
			return (line);
		}
	}

	return (NULL);
}
