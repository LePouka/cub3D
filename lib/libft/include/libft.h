/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtissera <rtissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:07:42 by rtissera          #+#    #+#             */
/*   Updated: 2024/05/03 16:33:59 by rtissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*   DEFINES                                                                  */
/* ************************************************************************** */
#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 420
# endif

# if BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

/* ************************************************************************** */
/*   INCLUDES                                                                 */
/* ************************************************************************** */
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdarg.h>

/* ************************************************************************** */
/*   STRUCTURES                                                               */
/* ************************************************************************** */
typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_buff
{
	char			buf[BUFFER_SIZE + 1];
	struct s_buff	*next;
}	t_buff;

/* ************************************************************************** */
/*   FUNCTIONS                                                                */
/* ************************************************************************** */

/* ************************************************************************** */
/*   MANDATORY                                                                */
/* ************************************************************************** */
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_atoi(const char *nptr);
int		ft_putnbr_fd(int n, int fd);
int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(char *s, int fd);
int		ft_putendl_fd(char *s, int fd);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_memcmp(const void *str1, const void *str2, size_t n);
char	*ft_itoa(int n);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strtrim(char const *s1, const char *set);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strnstr(const char *big, const char *little, size_t len);
void	*free_error(char **s);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_intlen(int nb);

/* ************************************************************************** */
/*   BONUS                                                                    */
/* ************************************************************************** */
int		ft_lstsize(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(char *content);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* ************************************************************************** */
/*   DPRINTF                                                                  */
/* ************************************************************************** */
int		ft_putu_fd(unsigned int n, int fd);
int		ft_dprintf(int fd, const char *str, ...);
int		ft_putvoid_fd(unsigned long int n, int fd);
int		ft_putnbr_base_fd(unsigned long int n, int base, int fd);

/* ************************************************************************** */
/*   GET_NEXT_LINE                                                            */
/* ************************************************************************** */
int		linelen(t_buff **lst, int boool);
char	*get_next_line(int fd);
char	*put_in_line(t_buff **lst, int i, int j);
void	*read_error(t_buff **lst);
void	clear_old_line(t_buff **lst);
void	ft_buffadd_back(t_buff **lst, t_buff *new);
t_buff	*ft_bufflast(t_buff *lst);
t_buff	*read_line(t_buff **lst, int fd);

#endif
