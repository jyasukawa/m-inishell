#include "libft.h"

void	*ft_memcpy(void *dst, void *src, size_t n)
{
	size_t	i;

	if (dst == NULL && src == NULL)
		return (NULL);
  i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((const unsigned char *)src)[i];
			i++;
	}
	return (dst);
}
