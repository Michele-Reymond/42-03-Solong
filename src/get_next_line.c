#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

// size_t ft_strlen(char *str)
// {
// 	size_t i;

// 	i = 0;
// 	if (str == NULL)
// 		return (0);
// 	while (str[i] != '\0')
// 		i++;
// 	return (i);
// }

// char *ft_strchr(char *str, int lettre)
// {
// 	char c;

// 	c = lettre;
// 	if (str == NULL)
// 		return (NULL);
// 	while (*str != '\0')
// 	{
// 		if (*str == c)
// 			return (str);
// 		str++;
// 	}
// 	if (*str == c)
// 		return (str);
// 	return (NULL);
// }

char *ft_strjoin_gnl(char *s1, char *s2)
{
	char *joined;
	int i;
	int j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	joined = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (joined == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		joined[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		joined[i] = s2[j];
		j++;
		i++;
	}
	joined[i] = '\0';
	if (s1)
	{
		free(s1);
		s1 = NULL;
	}
	return (joined);
}

char *clean_end_of_line(char *str)
{
	int i;
	char *cleaned;

	i = 0;
	if (str[i] == 0)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	cleaned = malloc(i + 2);
	if (cleaned == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		cleaned[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		cleaned[i] = str[i];
		i++;
	}
	cleaned[i] = '\0';
	return (cleaned);
}

char *clean_start_of_line(char *str)
{
	char *cleaned;
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == 0)
	{
		free(str);
		str = NULL;
		return (NULL);
	}
	cleaned = malloc(ft_strlen(str) - i + 1);
	if (cleaned == NULL)
		return (NULL);
	i++;
	while (str[i] && str[i] != '\0')
	{
		cleaned[j] = str[i];
		i++;
		j++;
	}
	cleaned[j] = '\0';
	if (str)
	{
		free(str);
		str = NULL;
	}
	return (cleaned);
}

char *get_next_line(int fd)
{
	char *buffer;
	char *tmp;
	char *returned_line;
	static char *line;
	int lecture;

	lecture = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	tmp = line;
	while (lecture != 0 && ft_strchr(tmp, '\n') == NULL)
	{
		lecture = read(fd, buffer, BUFFER_SIZE);
		if (lecture == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[lecture] = '\0';
		if (!tmp)
		{
			tmp = malloc(1);
			tmp[0] = '\0';
		}
		tmp = ft_strjoin_gnl(tmp, buffer);
	}
	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}
	returned_line = clean_end_of_line(tmp);
	line = clean_start_of_line(tmp);
	return (returned_line);
}





























// size_t ft_strlen(char *str)
	// ________3 STEPS_________
	// 1. si str est NULL return NULL
	// 2. itérer sur str
	// 3. return i

// char *ft_strchr(char *str, int lettre)
	// ________5 STEPS_________
	// 1. si str est NULL return NULL
	// 2. c = lettre
	// 3. itérer sur str
	// 	3.1 si *str == c return str
	// 4. si *str == c return str
	// 5. return NULL

// char *strjoin(char *s1, char *s2)
	// ________7 STEPS_________
	// 1. si s1 ou s2 est NULL return NULL
	// 2. malloc des 2 longueur + 1
	// 3. itérer sur s1 et mettre s1 dans joined
	// 4. itérer sur s2 et mettre s2 dans joined
	// 5. ajouter \0 à joined
	// 6. si s1 free s1
	// 7. return joined

// char *clean_end_of_line(char *str)
	// ________8 STEPS_________
	// 1. si str[i] vaut 0 return NULL
	// 2. itérer sur str jusqu'au \n
	// 3. malloc de i + 2
	// 4. i = 0
	// 5. itérer sur str et mettre str dans cleaned jusqu'au \n
	// 6. si il y a un \n le mettre dans cleaned
	// 7. mettre un \0 à la fin de cleaned
	// 8. return cleaned

// char *clean_start_of_line(char *str)
	// ________8 STEPS_________
	// 1. itérer sur str jusqu'au \n
	// 2. si str[i] vaut 0 free str et return NULL
	// 3. malloc de longueur de str - i + 1
	// 4. i++
	// 5. itérer sur str jusqu'au \0 et mettre dans cleaned
	// 6. ajouter \0 à cleaned
	// 7. si str existe free str
	// 8. return cleaned

// char *get_next_line(int fd)
	// ________9 STEPS_________
	// 1. lecture vaut 1
	// 2. si fd est negatif et BUFFER_SIZE plus petit ou égal à zéro return NULL
	// 3. malloc de BUFFER_SIZE + 1 sur buffer
	// 4. tmp = line
	// 5. itérer tant que ce n'est pas la fin du fichier et pas de \n dans tmp
		// 5.1 faire un read
		// 5.2 si lecture vaut -1 free buffer et return NULL
		// 5.3 mettre un \0 à la fin du buffer
		// 5.4 si tmp n'existe pas malloc de 1 et mettre un \0
		// 5.5 strjoin de tmp et buffer
	// 6. si buffer free le buffer
	// 7. clean end of line
	// 8. clean start of line
	// 9. return la returned_line

// size_t ft_strlen(char *str)
// {
// 	size_t i;

// 	i = 0;
// 	if (str == NULL)
// 		return (0);
// 	while (str[i] != '\0')
// 		i++;
// 	return (i);
// }

// char *ft_strchr(char *str, int lettre)
// {
// 	char c;

// 	if (str == NULL)
// 		return (NULL);
// 	c = lettre;
// 	while (*str != '\0')
// 	{
// 		if (*str == c)
// 			return (str);
// 		str++;
// 	}
// 	if (*str == c)
// 		return (str);
// 	return (NULL);
// }

// char *strjoin(char *s1, char *s2)
// {
// 	int i;
// 	int j;
// 	char *joined;

// 	i = 0;
// 	j = 0;
// 	if (s1 == NULL || s2 == NULL)
// 		return (NULL);
// 	joined = (char *)malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
// 	if (joined == NULL)
// 		return (NULL);
// 	while (s1[i] != '\0')
// 	{
// 		joined[i] = s1[i];
// 		i++;
// 	}
// 	while (s2[j] != '\0')
// 	{
// 		joined[i] = s2[j];
// 		i++;
// 		j++;
// 	}
// 	joined[i] = '\0';
// 	if (s1)
// 	{
// 		free(s1);
// 		s1 = NULL;
// 	}
// 	return (joined);
// }

// char *clean_end_of_line(char *str)
// {
// 	char *cleaned;
// 	int i;

// 	i = 0;
// 	if (str[i] == 0)
// 		return (NULL);
// 	while (str[i] && str[i] != '\n')
// 		i++;
// 	cleaned = (char *)malloc(sizeof(char) * i + 2);
// 	if (cleaned == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (str[i] && str[i] != '\n')
// 	{
// 		cleaned[i] = str[i];
// 		i++;
// 	}
// 	if (str[i] == '\n')
// 	{
// 		cleaned[i] = str[i];
// 		i++;
// 	}
// 	cleaned[i] = '\0';
// 	return (cleaned);
// }

// char *clean_start_of_line(char *str)
// {
// 	char *cleaned;
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	while (str[i] && str[i] != '\n')
// 		i++;
// 	if (str[i] == 0)
// 	{
// 		free(str);
// 		str = NULL;
// 		return (NULL);
// 	}
// 	cleaned = (char *)malloc(sizeof(char) * (ft_strlen(str) - i) + 1);
// 	if (cleaned == NULL)
// 		return (NULL);
// 	i++;
// 	while (str[i] && str[i] != '\0')
// 	{
// 		cleaned[j] = str[i];
// 		i++;
// 		j++;
// 	}
// 	cleaned[j] = '\0';
// 	if (str)
// 	{
// 		free(str);
// 		str = NULL;
// 	}
// 	return (cleaned);
// }

// char *get_next_line(int fd)
// {
// 	static char *line;
// 	char *buffer;
// 	char *tmp;
// 	int lecture;
// 	char *returned_line;

// 	lecture = 1;
// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	buffer = (char *)malloc(BUFFER_SIZE + 1);
// 	if (buffer == NULL)
// 		return (NULL);
// 	tmp = line;
// 	while (lecture != 0 && ft_strchr(tmp, '\n') == NULL)
// 	{
// 		lecture = read(fd, buffer, BUFFER_SIZE);
// 		if (lecture == -1)
// 		{
// 			free(buffer);
// 			return (NULL);
// 		}
// 		buffer[lecture] = '\0';
// 		if (!tmp)
// 		{
// 			tmp = (char *)malloc(sizeof(char) * 1);
// 			tmp[0] = '\0';
// 		}
// 		tmp = strjoin(tmp, buffer);
// 	}
// 	if (buffer)
// 	{
// 		free(buffer);
// 		buffer = NULL;
// 	}
// 	returned_line = clean_end_of_line(tmp);
// 	line = clean_start_of_line(tmp);
// 	return (returned_line);
// }

//  int main()
//  {
//  	int fd;
//  	char *line;
//  	int d;

//  	d = 0;
//  	fd = open("test.txt", O_RDONLY);
//  	line = get_next_line(fd);
//  	printf("line %d : %s", d, line);
//  	line = get_next_line(fd);
//  	d++;
//  	printf("line %d : %s", d, line);
//  }
