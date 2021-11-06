/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_casting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:32:00 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/19 13:36:41 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int main()
{
	int64_t a = 1;
	
	printf("before shift: %lld, after shift: %lld\n", a, a << 33);
	a <<= 33;
	printf("before casting: %lld, after casting: %u\n", a, (unsigned int)a);
}