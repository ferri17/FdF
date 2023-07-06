/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:07:55 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/06 21:09:14 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char) c)
			return ((char *) s);
		s++;
	}
	/* if ((char) c == '\0')
		return ((char *) s); */
	return (NULL);
}

static unsigned int	word_count(char const *s, char *sep)
{
	unsigned int	words;

	words = 0;
	if (ft_strchr(sep, *s) == NULL && *s != '\0')
		words++;
	while (*s)
	{
		if (ft_strchr(sep, *s) != NULL)
		{
			while (ft_strchr(sep, *s) != NULL)
				s++;
			if (*s != '\0')
				words++;
			else
				break ;
		}
		s++;
	}
	return (words);
}

static char	*split_words(char const **str, char *sep)
{
	char			*word;
	unsigned int	i;
	size_t			word_len;

	while (ft_strchr(sep, **str) != NULL)
		*str = *str + 1;
	word_len = 0;
	while (ft_strchr(sep, str[0][word_len]) == NULL && str[0][word_len] != '\0')
		word_len++;
	word = (char *)malloc(sizeof(char) * word_len + 1);
	if (word == NULL)
		return (NULL);
	i = 0;
	while (i < word_len)
	{
		word[i++] = **str;
		*str = *str + 1;
	}
	word[i] = '\0';
	return (word);
}

static void	free_malloc(char **arr, int i)
{
	while (i >= 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
}

char	**ft_split_str(char const *s, char c)
{
	char			sep[2];
	sep[0] = c;
	sep[1] = 0;
	char			**arr;
	unsigned int	words;
	unsigned int	i;

	words = word_count(s, sep);
	arr = (char **)ft_calloc(sizeof(char *), (words + 1));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (i < words)
	{
		arr[i] = split_words(&s, sep);
		if (arr[i] == NULL)
		{
			free_malloc(arr, i);
			return (NULL);
		}
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
