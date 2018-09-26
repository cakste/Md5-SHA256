/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MD5_preprocessing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acakste <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 17:52:35 by acakste           #+#    #+#             */
/*   Updated: 2018/09/24 17:52:36 by acakste          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

uint32_t    *calc_K(void)
{
    int i;
    uint32_t *k;

    k = (uint32_t*)malloc(sizeof(uint32_t) * 64);
    if (!k)
        return (NULL);
    i = 0;
    while (i < 64)
    {
        k[i] = floor(pow(2, 32) * fabs(sin(i + 1)));
        i++;
    }
    return (k);
}

void     round_shift(int i, uint32_t *s)
{
    if (i < 16)
    {
        if (i % 4 == 0)
            s[i] = 7;
        else if (i % 4 == 1)
            s[i] = 12;
        else if (i % 4 == 2)
            s[i] = 17;
        else
            s[i] = 22;
    }
    else if (i >= 16 && i < 32)
    {
       if (i % 4 == 0)
            s[i] = 5;
        else if (i % 4 == 1)
            s[i] = 9;
        else if (i % 4 == 2)
            s[i] = 14;
        else
            s[i] = 20;
    }
    else if (i >= 32 && i < 48)
    {
        if (i % 4 == 0)
            s[i] = 4;
        else if (i % 4 == 1)
            s[i] = 11;
        else if (i % 4 == 2)
            s[i] = 16;
        else
            s[i] = 23;
    }
    else if (i >= 48 && i < 64)
    {
        if (i % 4 == 0)
            s[i] = 6;
        else if (i % 4 == 1)
            s[i] = 10;
        else if (i % 4 == 2)
            s[i] = 15;
        else
            s[i] = 21;
    }
}

uint32_t    *init_S(void)
{
    uint32_t i;
    uint32_t *s;

    s = (uint32_t*)malloc(sizeof(uint32_t) * 64);
    if (!s)
        return (NULL);
    i = 0;
    while (i < 64)
    {
        round_shift(i, s);
        i++;
    }
    return (s);
}
/*
t_512_block	*preprocessing(uint32_t *message)//, int numbit_block) add a dispatch table for this, maybe
{
	t_512_block	*blocks;
    uintmax_t   i;
    uint64_t	len;

    i = 0;
	blocks = NULL;
	add_block(&blocks, new_block());
    while (message[i])
	{
        write(1, "|", 1);
		if (i % 16 == 0 && i != 0)
		{
			add_block(&blocks, new_block());
			if (!blocks)
				return (NULL);
			//printf("\n\n");
		}
        //ft_printf("message of i: %.8b\n", message[i]);
        //test = (unsigned char)(message[i] << 1);
       // ft_printf("one shifed  : %.8b\n", test);
		blocks->M[i % 16] = message[i];
		i++;
	}
	//have to look at block[i - 1], append 1 bit there
	//ft_printf("message of i: %.8b\n", message[i]);
	if (i % 16 != 0 || i < 16)
		blocks->M[i % 16] = (unsigned char)128;
	if ((i % 16) >= 14 || (i % 16 == 0 && i >= 16))
	{
		add_block(&blocks, new_block());
			if (!blocks)
				return (NULL);
		if (i % 16  == 0 && i >= 16)
			blocks->M[i % 16] = (unsigned char)128;
	}
     // should be mod 2^64
    while (i % 16 != 14)
        i++;
	len = (int64_t)i;
    ft_memcpy(&(blocks->M[i % 16]), &len, 8);
    return (blocks);
}*/
// these conditions are shit, rewrite from the start.

/*

t_512_block *preprocessing(unsigned char *message)
{

}
*/
t_512_block	*preprocessing(unsigned char *message)//, int numbit_block) add a dispatch table for this, maybe
{
	t_512_block	*blocks;
    t_512_block *trav;
    uintmax_t   i;
    //uintmax_t   j;
    uint64_t		len;

    i = 0;
	blocks = NULL;
	add_block(&blocks, new_block());
    trav = blocks;
    while (message[i])
	{
        if (i % 64 == 0 && i != 0)
            trav = trav->next;
		if (i % 64 == 56 && i != 0)
		{
			add_block(&blocks, new_block());
			if (!blocks)
				return (NULL);
			printf("\n\n");
		}
		trav->message[i % 64] = message[i];
		i++;
	}
	len = (int64_t)i * 8;
	if (i % 64 != 0 || i < 64)
		trav->message[i % 64] = (unsigned char)1 << 7;
    printf("\n i == %ju\n", i);
    if (i % 64 >= 56 && trav->next)
        trav = trav->next;
	if ((i % 64) == 56)
	{
        write(1, "NOT", 3);
		add_block(&blocks, new_block());
        trav = trav->next;

        /*if (trav && trav->next)
        {
            printf("blocks : %c", (unsigned char)blocks->message[0]);
            printf("blocks->next : %c", (unsigned char)blocks->message[0]);
            write(1, "NEW BLOCK", 9);
		}*/
    	if (!blocks)
			return (NULL);
		if (i % 64 == 0 && i >= 64)
			trav->message[i % 64] = (unsigned char)1 << 7;
	}
    while (i % 64 != 56)
        i++;
    ft_memcpy(&(trav->message[i % 64]), &len, 8);
    return (blocks);
}
