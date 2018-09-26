/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MD5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acakste <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 19:58:11 by acakste           #+#    #+#             */
/*   Updated: 2018/09/23 19:58:12 by acakste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>


t_512_block	*new_block(void)
{
	t_512_block	*new;
	int			i;

	new = (t_512_block*)malloc(sizeof(t_512_block));
	if (!new)
		return (NULL);
	i = 0;
	while (i < 16)
	{
		new->M[i] = 0;
		i++;
	}
	i = 0;
	while (i < 64)
	{
		new->message[i] = 0;
		i++;
	}
	new->next = NULL;
	return (new);
}

void	add_block(t_512_block **start, t_512_block *new)
{
    t_512_block *trav;


    write(1, "$", 1);
	if (start && new)
	{
		if (*start == NULL)
		{
			write(1, "1", 1);
			*start = new;
			return ;
		}
        trav = *start;
        while (trav && trav->next)
        {
        	write(1, "&", 3);
            trav = trav->next;
        }
        write(1, "=", 3);
        trav->next = new;
	}
}

//big endian in each byte, little endian for the bytes
void show_mem_rep(unsigned char *start, int n) 
{
    int i;

    for (i = 0; i < n; i++)
	{
        ft_printf(" %.8b", start[i]);
	}
	ft_printf("\n");
	for (i = 0; i < n; i++)
	{
        printf(" %8.2x", (unsigned char)start[i]);
	}
    printf("\n");
}

uint32_t    left_rotate(uint32_t x, uint32_t c)
{
	return ((x << c) | (x >> (32 - c)));
}

t_512_block	*convert_to_words(t_512_block *blocks)
{
	t_512_block *trav;
	int			i;
	int			j;

	trav = blocks;
	while (trav)
	{
		i = 0;
		j = 0;
		while (i < 16 && j < 64)
		{
			trav->M[i] += (uint32_t)trav->message[j];
			trav->M[i] += (uint32_t)trav->message[j + 1] << 8;
			trav->M[i] += (uint32_t)trav->message[j + 2] << 16;
			trav->M[i] += (uint32_t)trav->message[j + 3] << 24;
			i++;
			j += 4;
		}
		trav = trav->next;
	}
	return (blocks);
}

uint32_t	reverse(uint32_t i)
{
	uint32_t new;

	new = 0;
	new += i << 24 & 0xff000000;
	new += i << 8 & 0xff0000;
	new += i >> 8 & 0xff00;
	new += i >> 24 & 0xff;
	return (new);
}
/*
char		*append_digest(uint32_t a0, uint32_t b0, uint32_t c0, uint32_t d0)
{
	a0 = reverse(a0);
	b0 = reverse(b0);
	c0 = reverse(c0);
	d0 = reverse(d0);
	printf("DIGEST: ");
	printf("%.8x", a0);
	printf("%.8x", b0);
	printf("%.8x", c0);
	printf("%.8x\n", d0);
	return (NULL);
}*/

char    *gen_digest(t_512_block *blocks, uint32_t *s, uint32_t *k)
{
    t_512_block		*trav;
    t_words         words0;
    t_words         digest;
    uint32_t       	i;
    uint32_t        F;
    uint32_t        g;

    words0.a = 0x67452301;
    words0.b = 0xefcdab89;
    words0.c = 0x98badcfe;
    words0.d = 0x10325476;
    trav = blocks;
    while (trav)
    {
 		digest.a = words0.a;
        digest.b = words0.b;
        digest.c = words0.c;
        digest.d = words0.d;
        i = 0;
        while (i < 64)
        {
            if (i < 16)
            {
                F = (digest.b & digest.c) | ((~digest.b) & digest.d);
                g = i;
            }
            else if (i < 32)
            {
                F = (digest.d & digest.b) | ((~digest.d) & digest.c);
                g = ((5 * i) + 1) % 16;
            }
            else if (i < 48)
            {
                F = digest.b ^ digest.c ^ digest.d;
                g = ((3 * i) + 5) % 16;
            }
            else if (i < 64)
            {
                F = digest.c ^ (digest.b | (~digest.d));
                g = (7 * i) % 16;
            }
            F = F + digest.a + k[i] + trav->M[g];
            digest.a = digest.d;
            digest.d = digest.c;
            digest.c = digest.b;
            digest.b += (F << s[i]) | (F >> (32 - s[i]));
 			i++;
        }
		words0.a += digest.a;
		words0.b += digest.b;
		words0.c += digest.c;
		words0.d += digest.d;
		trav = trav->next;
	}
	words0.a = reverse(words0.a);
	words0.b = reverse(words0.b);
	words0.c = reverse(words0.c);
	words0.d = reverse(words0.d);
	ft_printf("%.8x%.8x%.8x%.8x", words0.a, words0.b, words0.c, words0.d);
	return (NULL);
}

char    *md5(char *str)
{
    uint32_t	*s;
    uint32_t	*k;
	t_512_block		*blocks;
	t_512_block		*trav;
	int			i;

    s = init_S();
    k = calc_K();
	blocks = preprocessing((unsigned char*)str);
	blocks = convert_to_words(blocks);
 	/*trav = blocks;
	while (trav)
	{
		i = 0;
		while (i < 64)
		{
			show_mem_rep((unsigned char *)&trav->message[i], 4);
			i += 4;
		}
		ft_printf("\n\n");
		trav = trav->next;
	}*/
	trav = blocks;
	while (trav)
	{
		i = 0;
		while (i < 16)
		{
			show_mem_rep((unsigned char *)&trav->M[i], 4);
			i++;
		}
		ft_printf("\n\n");
		trav = trav->next;
	}

	gen_digest(blocks, s, k);
  	return (str);

}

