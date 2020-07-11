
#include "libft.h"
#include <stdlib.h>

/* INPUT PARAMS: 
 * 	str0: first string
 * 	str1: second string, which will be appended behind the first string
 * 	strbase: (base string) either 0 or 1.
 * 	  0: the first string is the base and needs to be reallocated & freed
 * 	  1: the second string is the base and  needs to be reallocated & freed
 * REQUIREMENT:
 * 	The "base string" needs to be allocated on the heap as it will be freed
 * EXAMPLE 0:
 * 	Have a base of "555-5555" and want to append an extension "ext: 42"
 * 		base_num = ft_strdup("555-5555");
 * 		ext_num = " ext: 42";
 * 		base_num = ft_strappd(base_num, ext_num, 0);
 *
 * EXAMPLE 1:
 * 	Have a base of "555-5555" and want to append an area code "(510) "
 * 		base_num = ft_strdup("555-5555");
 * 		area_code = "(510) ";
 * 		base_num = ft_strappd(area_code, base_num, 1);
 */

char	*ft_strappd(char *str0, char *str1, int strbase)
{
	char    *temp;

	temp = ft_strjoin(str0, str1);
	if (strbase == 0)
		free(str0);
	else if (strbase == 1)
		free(str1);
	else
		return (NULL);
	return (temp);
}
