/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alidy <alidy@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/23 14:51:53 by alidy        #+#   ##    ##    #+#       */
/*   Updated: 2019/11/23 16:11:13 by alidy       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

/*				TEST-GNL				*/
/*
int main(int argc, char **argv)
{  
    int		fd;
	char	*line;
	int 	res;

	(void)argc;
	res = 1;
	if ((fd = open(argv[1], 'r')) == -1)
		return (-1);
	while (res > 0)
	{
		res = get_next_line(fd, &line);
		printf("%s",line);
        if (res != 0)
            printf("\n");
		free(line);
		line = 0;
	}
	close(fd);
    return (0);
}
*/
/* 				TEST MULTI-FD				*/

int main(int argc, char **argv)
{  
    int		fd;
	int		fd2;
	char	*line;
	int 	res;

	(void)argc;
	res = 10;
	if((fd = open(argv[1], 'r')) == -1)
		return (-1);
	if((fd2 = open(argv[2],'r')) == -1)
		return (-1);
	while (res > 0)
	{
		get_next_line(fd, &line);
		printf("%s\n", line);
		free(line);
		line = 0;
		get_next_line(fd2, &line);
		printf("%s\n", line);
		free(line);
		line = 0;
		res--;
	}
	res = 1;
	/*while (res > 0)
	{
		res = get_next_line(fd, &line); // Passer en fd2 pour le deuxieme test
		printf("%s", line);
        if (res != 0)
            printf("\n");
		free(line);
		line = 0;
	}*/
	close(fd);
	close(fd2);
    return (0);
}
