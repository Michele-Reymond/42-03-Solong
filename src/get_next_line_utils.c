#include "get_next_line.h"

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
		joined[i++] = s2[j++];
	joined[i] = '\0';
    free(s1);
    s1 = NULL;
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
		cleaned[j++] = str[i++];
	cleaned[j] = '\0';
    free(str);
    str = NULL;
	return (cleaned);
}