/*
 * vectorMathTests.c
 *
 *  Created on: Jan 19, 2011
 *      Author: ryanbelt
 */
#include <stdio.h>
#include "../headers/vectorMathTests.h"
#include "../headers/vector_math.h"

void vect_2_tests();
void vect_3_tests();

//int main()
//{
//	mainVectorTests();
//	return 0;
//}

void mainVectorTests()
{
	printf("vect_2_tests:\n\n");
	vect_2_tests();
	printf("\n\nvect_3_tests:\n\n");
	vect_3_tests();
}

void vect_2_tests()
{
	vec2_t v1,v2, add, sub, scale, copyV2, invert, normV1;
	v1[0] = 1;
	v1[1] = 3;
	v2[0] = -4;
	v2[1] = 6;
	float dotProd = dotProd_2(v1,v2);
	vect_add_2(v1,v2,add);
	vect_subtr_2(v1,v2,sub);
	vect_scale_2(v1,3,scale);
	vect_copy(v2,2,copyV2);
	vect_invert(v2,2,invert);
	vect_normalize(v1,2,normV1);

	printf("v1:");
	vect_print_2(v1);
	printf("\nv2:");
	vect_print_2(v2);
	printf("\ndot product:%g",dotProd);
	printf("\nv1+v2:");
	vect_print_2(add);
	printf("\nv1-v2:");
	vect_print_2(sub);
	printf("\nv1 scaled by 3:");
	vect_print_2(scale);
	printf("\ncopy of v2:");
	vect_print_2(copyV2);
	printf("\ninverted v2:");
	vect_print_2(invert);
	printf("\nnormalized v1:");
	vect_print_2(normV1);
	vect_clear(v1,2);
	printf("\ncleared v1:");
	vect_print_2(v1);

}

void vect_3_tests()
{
	vec3_t v1,v2, add, sub, scale, copyV2, invert, normV1;
	v1[0] = -4;
	v1[1] = 2;
	v1[2] = 13;
	v2[0] = 5;
	v2[1] = -7;
	v2[2] = -104;
	float dotProd = dotProd_3(v1,v2);
	vect_add_3(v1,v2,add);
	vect_subtr_3(v1,v2,sub);
	vect_scale_3(v1,3,scale);
	vect_copy_3(v2,copyV2);
	vect_invert_3(v2,invert);
	vect_normalize_3(v1,normV1);

	printf("v1:");
	vect_print_3(v1);
	printf("\nv2:");
	vect_print_3(v2);
	printf("\ndot product:%g",dotProd);
	printf("\nv1+v2:");
	vect_print_3(add);
	printf("\nv1-v2:");
	vect_print_3(sub);
	printf("\nv1 scaled by 3:");
	vect_print_3(scale);
	printf("\ncopy of v2:");
	vect_print_3(copyV2);
	printf("\ninverted v2:");
	vect_print_3(invert);
	printf("\nnormalized v1:");
	vect_print_3(normV1);
	vect_clear_3(v1);
	printf("\ncleared v1:");
	vect_print_3(v1);

}
