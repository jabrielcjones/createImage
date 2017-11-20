// file name -- assign04.cpp

// This program is creates an image with either a random or fixed
// pattern and blends it.


// ============================== header files ==============================
#include <sketch.h>                     // for Sketch class
#include "blur.h"                     // for blur class definition
#include <iostream>                   // for input/output stream
#include "random.h"                   // for random class
#include <cstdlib>
using namespace std;


// ============================ named constants =============================
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

// ========================== function prototypes ================
void prompt(int&, int&, int&, char&);
void drawImage(Blur, int);
void generateRandom(Blur&);

int main()
{
   int rows, columns, scaling;
   char response;

   prompt(rows, columns, scaling, response);
   Blur one(rows, columns);

   if(toupper(response) == 'Y')
      generateRandom(one);

   drawImage(one, scaling);

   return 0;
} // main function

void prompt(int& rows, int& columns, int& scaling, char& response)
/**
   preconditions: none

   postconditions: prompts user to enter the number of rows,
                   columns, and scaling factor for the image
                   and asks if the the colors should be generated
                   at random.
**/
{
   cout << "Please enter the number of rows: "
        << endl;
   cin >> rows;
   cout << "Please enter the number of columns: "
        << endl;
   cin >> columns;
   cout << "Please enter the scaling factor (1-10): "
        << endl;
   cin >> scaling;
   cout << "Would you like to generate a pattern at random (Y/N)? ";
   cin >> response;
}  // prompt function


void generateRandom(Blur& image)
/**
   preconditions: user wants to render pattern at random

   postconditions: pattern generated at random.
**/
{
   Random randomizer;

   for(int row_index = 0; row_index < image.getRows(); row_index++)
      for(int column_index = 0; column_index < image.getColumns(); column_index++)
         image.changeColor(row_index, column_index, randomizer.next(16777216));

}  // generateRandom function


void drawImage(Blur image, int scaling)
/**
   preconditions: none

   postconditions: draws and blurs image
**/
{
   image.draw(WINDOW_WIDTH/4, WINDOW_HEIGHT * 3/4, scaling);
}  // drawImage function
