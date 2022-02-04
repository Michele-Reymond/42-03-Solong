#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

# include "libft/libft.h"
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char*s1, char*s2);
char	*clean_start_of_line(char *str);
char	*clean_end_of_line(char *str);
char    *read_lines(char *str, int fd, char *buffer);

#endif
