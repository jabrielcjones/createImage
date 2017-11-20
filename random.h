//  file name -- random.h
//  This program contains the declaration of random class.

#ifndef class_random_
#define class_random_

class Random
{
   public:
      Random();
      Random(int);
      void randomize();
      int next(int);
      float next();
}; // end of Random class

#endif
