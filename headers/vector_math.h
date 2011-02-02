/*
 * vector_math.h
 *
 *  Created on: Jan 19, 2011
 *      Author: shawn
 */

#ifndef VECTOR_MATH_H_
#define VECTOR_MATH_H_

typedef float vec_t;
typedef vec_t vec2_t[2];
typedef vec_t vec3_t[3];
typedef vec_t vec4_t[4];
typedef vec_t vec5_t[5];

/*
 * Dot product for 2 dimensional vectors
 */
#define dotProd_2(v1,v2) (v1[0]*v2[0]+v1[1]*v2[1])
/*
 * Dot product for 3 dimensional vectors
 */
#define dotProd_3(v1,v2) (v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2])
/*
 * Dot product for 4 dimensional vectors
 */
#define dotProd_4(v1,v2) (v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2]+v1[3]*v2[3])
/*
 * Dot product for 5 dimensional vectors
 */
#define dotProd_5(v1,v2) (v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2]+v1[3]*v2[3]+v1[4]*v2[4])

/*
 * Cross product of v1 x v2, stores the result in the third vector
 */
#define crossProduct(v1,v2,out) {out[0]=v1[1]*v2[2]-v1[2]*v2[1];out[1]=v1[2]*v2[0]-v1[0]*v2[2];out[2]=v1[0]*v2[1]-v1[1]*v2[0];}

/**
 * Adds the first two 2-dimensional vectors and stores the result
 * in the third
 */
#define vect_add_2(v1,v2,out) {out[0]=v1[0]+v2[0];out[1]=v1[1]+v2[1];}
/**
 * Adds the first two 3-dimensional vectors and stores the result
 * in the third
 */
#define vect_add_3(v1,v2,out) {out[0]=v1[0]+v2[0];out[1]=v1[1]+v2[1];out[2]=v1[2]+v2[2];}
/**
 * Adds the first two 4-dimensional vectors and stores the result
 * in the third
 */
#define vect_add_4(v1,v2,out) {out[0]=v1[0]+v2[0];out[1]=v1[1]+v2[1];out[2]=v1[2]+v2[2];out[3]=v1[3]+v2[3];}
/**
 * Adds the first two 5-dimensional vectors and stores the result
 * in the third
 */
#define vect_add_5(v1,v2,out) {out[0]=v1[0]+v2[0];out[1]=v1[1]+v2[1];out[2]=v1[2]+v2[2];out[3]=v1[3]+v2[3];out[4]=v1[4]+v2[4];}

/**
 * Subtracts the first two 2-dimensional vectors and stores the result
 * in the third
 */
#define vect_subtr_2(v1,v2,out) {out[0]=v1[0]-v2[0];out[1]=v1[1]-v2[1];}
/**
 * Subtracts the first two 3-dimensional vectors and stores the result
 * in the third
 */
#define vect_subtr_3(v1,v2,out) {out[0]=v1[0]-v2[0];out[1]=v1[1]-v2[1];out[2]=v1[2]-v2[2];}
/**
 * Subtracts the first two 4-dimensional vectors and stores the result
 * in the third
 */
#define vect_subtr_4(v1,v2,out) {out[0]=v1[0]-v2[0];out[1]=v1[1]-v2[1];out[2]=v1[2]-v2[2];out[3]=v1[3]-v2[3];}
/**
 * Subtracts the first two 5-dimensional vectors and stores the result
 * in the third
 */
#define vect_subtr_5(v1,v2,out) {out[0]=v1[0]-v2[0];out[1]=v1[1]-v2[1];out[2]=v1[2]-v2[2];out[3]=v1[3]-v2[3];out[4]=v1[4]-v2[4];}

/*
 * Multiplies the 2-D vector (1st parameter) by the scalar (2nd parameter)
 * and stores the result in the output vector (3rd parameter)
 */
#define vect_scale_2(v,c,out) {out[0]=v[0]*c;out[1]=v[1]*c;}
/*
 * Multiplies the 3-D vector (1st parameter) by the scalar (2nd parameter)
 * and stores the result in the output vector (3rd parameter)
 */
#define vect_scale_3(v,c,out) {out[0]=v[0]*c;out[1]=v[1]*c;out[2]=v[2]*c;}
/*
 * Multiplies the 4-D vector (1st parameter) by the scalar (2nd parameter)
 * and stores the result in the output vector (3rd parameter)
 */
#define vect_scale_4(v,c,out) {out[0]=v[0]*c;out[1]=v[1]*c;out[2]=v[2]*c;out[3]=v[3]*c;}
/*
 * Multiplies the 5-D vector (1st parameter) by the scalar (2nd parameter)
 * and stores the result in the output vector (3rd parameter)
 */
#define vect_scale_5(v,c,out) {out[0]=v[0]*c;out[1]=v[1]*c;out[2]=v[2]*c;out[3]=v[3]*c;out[4]=v[4]*c;}

/*
 * Copies the N-D vector (1st parameter) into the output vector
 * where N is the 2nd parameter and the output is the 3rd
 */
#define vect_copy(v,n,out) {int i;for(i=0;i<n;i++){out[i]=v[i];}}

/*
 * Copies the 3-D vector (1st parameter) into the output vector
 * which is the 2rd parameter
 */
#define vect_copy_3(v,out) {out[0]=v[0];out[1]=v[1];out[2]=v[2];}

/*
 * Clears the N-D vector (1st parameter)
 * where N is the 2nd parameter
 */
#define vect_clear(v,n) {int i;for(i=0;i<n;i++){v[i]=0;}}

/*
 * Clears the 3-D vector (1st parameter)
 */
#define vect_clear_3(v) {v[0]=v[1]=v[2]=0;}

/*
 * Inverts the N-D vector (1st parameter) where N is the 2nd parameter
 * and the output is in the 3rd parameter
 */
#define vect_invert(v,n,out) {int i;for(i=0;i<n;i++){out[i]=-v[i];}}

/*
 * Inverts the 3-D vector (1st parameter) where the output
 * is in the 2nd parameter
 */
#define vect_invert_3(v,out) {out[0]=-v[0];out[1]=-v[1];out[2]=-v[2];}

/*
 * Returns the magnitude of the N-D vector
 * v - the vector
 * n - the number of dimensions
 * returns :: the magnitude of the vector
 */
float vect_magnitude(vec_t v[], int n);

/*
 * Normalizes a N-D vector (1st parameter) and puts the result
 * in the output vector (3rd parameter) where N is the 2nd parameter
 */
#define vect_normalize(v,n,out) {float mag = vect_magnitude(v,n);int i;for(i=0;i<n;i++){out[i]=v[i]/mag;}}

/*
 * Normalizes a 3-D vector (1st parameter) and puts the result
 * in the output vector (3rd parameter)
 */
#define vect_normalize_3(v,out) {float mag = vect_magnitude(v,3);out[0]=v[0]/mag;out[1]=v[1]/mag;out[2]=v[2]/mag;}

#define vect_print_2(v) {printf("<%g,%g>", v[0],v[1]);}

#define vect_print_3(v) {printf("<%g,%g,%g>", v[0],v[1], v[2]);}

#endif /* VECTOR_MATH_H_ */
