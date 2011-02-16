/*
 * vector_math.c
 *
 *  Created on: Jan 19, 2011
 *      Author: shawn
 */
#include <math.h>
#include "../headers/vector_math.h"


/*
 * Returns the magnitude of the N-D vector
 * v - the vector
 * n - the number of dimensions
 * returns :: the magnitude of the vector
 */
float vect_magnitude(vec_t v[], int n)
{
	int i;
	float sum = 0;
	for(i = 0; i < n; i++)
		sum += v[i]*v[i];

	return sqrt(sum);
}
