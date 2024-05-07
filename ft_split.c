/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrechuli <mrechuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:11:54 by mrechuli          #+#    #+#             */
/*   Updated: 2024/04/21 17:29:43 by mrechuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	count_words(char *str, char separator)
{
	int	count;
	int	k; // zmienna ktora pomaga nam okreslic czy jestesmy jeszcze wewnatrz wyrazenia oddzielonego separatorem

	count = 0;
	while (*str)
	{
		k = 0;
		while (*str == separator && *str)
			str++;
		while (*str != separator && *str)
		{
			if (k == 0)
			{
				count++;
				k = 1;
			}
			str++;
		}
	}
	return (count);
}

static char *get_next_word(char *str, char separator)
{
	char		*next_str;
	int			len;
	int			x;
	static int	index = 0; // index jest static poniewaz potrzebujemy zapamietywac, w ktorym miejscy stringa skonczylismy ostatnie dzialanie

	len = 0;
	x = 0;
	while (str[index] == separator)
		index++;
	while ((str[index + len] != separator) && str[index + len])
		len++;
	next_str = malloc(sizeof(char) * (size_t)(len) + 1);
	if (next_str == NULL)
		return (NULL);
	while ((str[index] != separator) && str[index])
		next_str[x++] = str[index++];
	next_str[x] = '\0';
	return (next_str);
}

// ft_split tworzy z zadeklarowanego stringa, tablice w ktorej beda
// znajdowac sie "strings":
// - strings[0] = '\0' - na pierwszym miejscu jest '\0'
// - strings [x] = NULL - na ostatnim miejscu jest NULL
// - w srodku sa "strings" ktore zawieraja wyciagniete liczby oddzielone separatorem
// '\0' i NULL na koncu sa dlatego, poniewaz chce, aby mialo to budowe jak argv (przyda sie to podczas dalszych dzialan)

char **ft_split(char *str, char separator)
{
	int		words_num;
	char	**strings; //to sa poszczegolne ciagi znakow, oddzielone separatorem, czyli poszczegolne liczby, ktore wyciagamy ze stringa
	int		x;

	x = 0;
	words_num = count_words(str, separator);
	if (!words_num)
		exit (1); // bo jesli words_num wyrzuci blad to musimy wymusic zakonczenie programu bo to oznacza ze jest blad
	strings = malloc(sizeof(char *) * (size_t)(words_num + 2)); // +2 poniewaz dodatkowe miesjce dla koncwowego NULL i dodatkowe '\0' na poczatku zeby odzwierciedlic argv
	if (strings == NULL)
		return (NULL);
	while (words_num-- >= 0)
	{
		if (x == 0) // ten warunek jest po to, aby do pierwszega "strings" wstawic \0
		{
			strings[x] = malloc(sizeof(char));
			if (strings[x] == NULL)
				return (NULL);
			strings[x++][0] = '\0';
			continue ;
		}
		strings[x++] = get_next_word (str, separator); // kazde kolejne wywolanie tego, wstawi w kolejny "strings" liczbe wyciagnieta z zadeklarowanego stringa
	}
	strings[x] = NULL; // wstawia NULL na koncu tablicy zawierajacej "strings"
	return (strings);
}

// int main(void)
// {
//     char *text = "4 2 -5 -6 135";
//     char **parts = ft_split(text, ' ');

//     if (parts == NULL)
// 	{
//         printf("Błąd alokacji pamięci!\n");
//         return (1);
//     }

// 	char **tmp = parts;

//    while (*tmp)
//    {
//         printf("%s\n", *tmp);
//         free(*tmp);
//         tmp++;
//     }
//     free(parts); // Zwolnienie pamięci dla tablicy wskaźników
//     return (0);
// }