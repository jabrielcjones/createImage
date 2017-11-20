// file name -- blur.h
// This header file contains the specifications needed to draw
// and blur an object.

#ifndef CLASS_BLUR_
#define CLASS_BLUR_


const int BLACK_CODE = 0;
const int WHITE_CODE = 16777215;
const int BLUE_CODE = 255;
const int GREEN_CODE = 65280;


class Blur
{
   private:
      int *colors;
      int rows;
      int columns;

   public:
      Blur(int rows = 10, int columns = 10,
           int frist = BLACK_CODE, int second = BLUE_CODE, int reamaining = GREEN_CODE);  // default contructor
      Blur(const Blur&);      // copy constructor
      ~Blur();    // destructor

      int getRows();                      // accessor function
      int getColumns();                   // accessor function
      void changeColor(int, int, int);    // mutator function
      int getColor(int, int);             // accessor function
      void blend();                       // mutator function
      Blur operator=(const Blur&);        // operator overload
      void draw(int, int, int);           // mutator function
}; // class Blur

#endif
