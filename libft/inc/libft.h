/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drontome <drontome@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:26:38 by drontome          #+#    #+#             */
/*   Updated: 2023/01/02 14:44:02 by drontome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
/**********************************INC*****************************************/
# include <fcntl.h>
# include <float.h>
# include <limits.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
/*********************************GNL_DEF**************************************/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
/*********************************STRUCTS**************************************/
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
/*********************************GNL_STR**************************************/
typedef struct s_var
{
	char			*line;
	char			*aux;
	char			*eln;
	size_t			i;
	int				flag;
	ssize_t			size;
}					t_var;
/*******************************BASIC_FUNC*************************************/
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
size_t				ft_strlen(const char *s);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_atoi(const char *str);
char				*ft_strdup(const char *s1);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
/*********************************GNL_FUNC*************************************/
char				*get_next_line(int fd);
void				ft_init_var(t_var *var);
size_t				ft_strlen_gnl(const char *s);
void				ft_cpy(char *dst, char *src, size_t n);
char				*ft_new_line(t_var *var, char *buf);
/*******************************PRINTF_FUNC************************************/
int					ft_printf(char const *s, ...);
int					ft_putchar(int ap);
int					ft_putstr(char *ap);
int					ft_getformat(char c, va_list ap);
int					ft_put_ptr(void *ap);
int					ft_putnbr_hex(unsigned int nbr, char c);
int					ft_putnbr_int(int ap);
int					ft_putnbr_uns(unsigned int ap);
/********************************EXTRA_FUNC************************************/
int					ft_str_ends_with(const char *str, const char *end);
char				*ft_strjoin_free(char *s1, char *s2);
int					ft_just_strchr(const char *chr, const char *str);
void				*ft_free_matrix(char **mtx);
char				**ft_dup_matrix(char **mtx);
int					ft_len_matrix(char **matrix);
int					ft_isspace(int c);
void				ft_lstswap(t_list *a, t_list *b);
t_list				*ft_lstpenult(t_list *lst);
double				ft_atof(const char *str);
double				ft_strtod(const char *str, char **endptr);

#endif
