/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:20:49 by cpapot            #+#    #+#             */
/*   Updated: 2025/05/12 17:11:20 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H
# include "get_next_line.h"
# include "../srcs/ft_printf/ft_printf.h"
# include "../srcs/ft_printf_fd/ft_printf_fd.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdbool.h>
# include <errno.h>

# define INT_MAX	2147483647
# define INT_MIN	-2147483647
# define LLONG_MAX	9223372036854775807
# define LLONG_MIN	-9223372036854775807

# define RESET              "\001\x1b[0m\002"
# define BLACK              "\001\x1b[30m\002"
# define RED                "\001\x1b[31m\002"
# define GREEN              "\001\x1b[32m\002"
# define YELLOW             "\001\x1b[33m\002"
# define BLUE               "\001\x1b[34m\002"
# define MAGENTA            "\001\x1b[35m\002"
# define CYAN               "\001\x1b[36m\002"
# define WHITE              "\001\x1b[37m\002"

typedef struct s_list_of_char	t_lstc;

struct s_list_of_char
{
	t_lstc	*next;
	char	c;
};

typedef struct s_memstock
{
	void				*content;
	struct s_memstock	*next;
}						t_memlist;

typedef struct s_intlist
{
	int					cont;
	struct s_intlist	*next;
}					t_int_list;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_bzero(void *s, size_t n);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_lstdelone(t_list *lst);
void		ft_lstiter(t_list *lst, void (*f)(void *));
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstintadd_back(t_int_list **lst, t_int_list *new);
void		ft_lstintadd_front(t_int_list **lst, t_int_list *new);
void		ft_lstintclear(t_int_list **lst);
void		ft_lstintdelone(t_int_list *lst);
void		stock_free(t_memlist **stock);
void		*stock_malloc(size_t size, t_memlist **stock);
void		ft_lstintiter(t_int_list *lst, int (*f)(int));
t_int_list	*ft_lstintlast(t_int_list *lst);
t_int_list	*ft_lstintmap(t_int_list *lst, int (*f)(int), t_memlist **stock);
t_int_list	*ft_lstintnew(int cont, t_memlist **mem);
int			ft_lstintsize(t_int_list *lst);
void		ft_lstclear(t_list **lst);
void		*ft_calloc(size_t count, size_t size);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_lstsize(t_list *lst);
int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_isprint(int c);
int			ft_isdigit(int c);
int			ft_isascii(int c);
int			ft_isalpha(int c);
int			ft_isalnum(int c);
int			ft_atoi(const char *str);
bool		ft_atoi_on(const char *str, int *dst);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_itoa(int n);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strjoin(char const *s1, char const *s2, t_memlist **stock);
char		*ft_strdup(const char *s1, t_memlist **stock);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_stsubstr(char const *s, int start, size_t len, t_memlist **st);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		**ft_split(char *str, char *charset, t_memlist **stock);
char		**ft_split_no(char const *str, char delim);
int			ft_strcmp(const char *s1, const char *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dest, const char *src, size_t dstsize);
size_t		ft_strlen(const char *str);
t_list		*ft_lstnew(void *content, t_memlist **mem);
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), t_memlist **mem);
long long	ft_atoll(const char *str);
bool		ft_atoll_on(const char *str, long long *dst);
void		*ft_free_split(char **split);

#endif
