//  file name -- random.cpp
//  This program contains the implementation of the random class.

//  ======================= header files ===========================
#include "random.h"                  // for random class
#include <time.h>                    // for time function
#include <stdlib.h>                  // for random number generation
#include <limits.h>                  // for predefined limits


/**
   purpose: set zero as the default see for generating a sequence of
            pseudo random numbers
   precondition: none
   postcondition: the default seed, zero, is set for generating a sequence
            of random numbers
*/
Random::Random()
{
   srand(0);
}  // end of Random::Random


/**
   purpose: set the given seed as the seed for generating a sequence
            of pseudo random numbers
   precondition: none
   postcondition: the given seed is set for generating a sequence of
            random numbers
*/
Random::Random(int seed)
{
   srand(seed);
}  // end of Random::Random


/**
   purpose: set the system time as the seed for generating a sequence of
            pseudo random numbers
   precondition: none
   postcondition: the system time is used as the seed for generating a sequence
            of random numbers
*/
void Random::randomize()
{
   time_t x;

   x = 0;
   srand((unsigned int) time(&x));
}  // end of Random::randomize


/**
   purpose: generate an integer value between 0 and n - 1
   precondition: n is positive
   postcondition: an integer value between 0 and n - 1, inclusive, is
            generated and returned
*/
int Random::next(int n)
{
   return (abs(rand()) % n);
}  // end of Random::next


/**
   purpose: generate a floating point value between 0 and 1
   precondition: none
   postcondition: a floating point pseudo random number between 0 and 1 is
            generated and returned
*/
float Random::next()
{
   float sum;

   sum = LONG_MAX + 1;
   return ((float) abs(rand()) / sum);
}  // end of Random::next
