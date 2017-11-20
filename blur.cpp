// file name -- blur.cpp
// This file contains the implementation of the blur class

// ============== header files ================

#include "blur.h"          // for blur class
#include <sketch.h>        // for sketch class
#include <iostream>        // for input/output stream

using namespace std;

// ============== named constants ======================

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

// ============== implementation of functions ================

Blur::Blur(int new_rows, int new_columns, int first,
           int second, int remaining)
/**
   precondition: each parameter has a default value; both rows and columns
                 must be positive and bounded by the window size; while first
                 and remaining are none negative, but no larger than 16777215
   postcondition: member variables rows and columns are set to the initial
                  value; an array of integers is allocated dynamically in the
                  heap and it is pointed to by the member variables colors;
                  the elements on the first row are set the value stored in
                  first and the remaining elements are set to remaining
**/
{
   rows = new_rows;
   columns = new_columns;

   colors = new int[rows * columns];

   for(int i = 0; i < rows * columns; i++)
   {
      if(i < columns)
         colors[i] = first;
      else if(i < (columns * 2))
         colors[i] = second;
      else
         colors[i] = remaining;
   }
}

Blur::Blur(const Blur& source)
/**
   precondition: source is a well-defined Blur object.

   postcondition: copy the contents of source to the current object; deep
                  copy is used to duplicate the content of source
**/
{
   rows = source.rows;
   columns = source.columns;

   colors = new int[rows * columns];

   for(int i = 0; i < rows * columns; i++)
      colors[i] = source.colors[i];

}

Blur Blur::operator=(const Blur& source)
/**
   purpose: Assigns the object source to the current object
            which calls function.
*/
{
   rows = source.rows;
   columns = source.columns;

   colors = new int[rows * columns];

   for(int i = 0; i < rows * columns; i++)
      colors[i] = source.colors[i];

   return *this;
}


int Blur::getRows()
/**
   precondition: none

   postcondition: returns height of the digital image in pixels
**/
{
   return rows;
}


int Blur::getColumns()
/**
   precondition: none

   postcondition: returns width of the digital image in pixels.
**/
{
   return columns;
}


int Blur::getColor(int row_index, int column_index)
/**
   precondition:  row_index and column_index must be inbound based
                  on the size of the digital image.
   postcondition: Returns the composite color stored in the location
                  represented by row_index and column_index.
**/
{
   int index;

   if((row_index * column_index) < (rows * columns))
   {
      index = row_index * columns + column_index;
      return colors[index];
   }
   else
      cout << "Indexes are out of bounds"
           << endl;
      return -1;
}


void Blur::changeColor(int row_index, int column_index, int color)
/**
   precondition:  row_index and column_index must be within the bounds
                  based on the size of the digital image. Color must
                  be between 0 and 16777215.
   postcondition: Assigns the compostite color value to the corresponding
                  element based on row_index and column_index;
**/
{
   int index;

   if((row_index * column_index) < (rows * columns) && color >= 0 && color <= 16777215)
   {
      index = row_index * columns + column_index;
      colors[index] = color;
   }
   else
      cout << "Indexes and the color are out of bounds"
           << endl;
}


void Blur::blend()
/**
   preconditions: none

   postconditions: blends the pixels in the digital image
**/
{
   int index;
   int new_composite;
   int blue, blue1, blue2, blue3, blue4;
   int green, green1, green2, green3, green4;
   int red, red1, red2, red3, red4;

   for(int row_index = 0; row_index < rows; row_index++)
      for(int column_index = 0; column_index < columns; column_index++)
      {
         index = row_index * columns + column_index;

         if(row_index == 0 && column_index == 0)   // upper left corner
         {
            blue1 = colors[index+1] % 256;
            new_composite = colors[index+1] / 256;
            green1 = new_composite % 256;
            red1 = new_composite / 256;

            blue2 = colors[index+columns] % 256;
            new_composite = colors[index+columns] / 256;
            green2 = new_composite % 256;
            red2 = new_composite / 256;

            blue = (blue1 + blue2)/2;
            green = (green1 + green2)/2;
            red = (red1 + red2)/2;

            colors[index] = blue + (green * 256) + (red * 256 * 256);
         }
         else if(row_index == 0 && column_index == columns - 1)   // upper right corner
         {
            blue1 = colors[index-1] % 256;
            new_composite = colors[index-1] / 256;
            green1 = new_composite % 256;
            red1 = new_composite / 256;

            blue2 = colors[index+columns] % 256;
            new_composite = colors[index+columns] / 256;
            green2 = new_composite % 256;
            red2 = new_composite / 256;

            blue = (blue1 + blue2)/2;
            green = (green1 + green2)/2;
            red = (red1 + red2)/2;

            colors[index] = blue + (green * 256) + (red * 256 * 256);
         }
         else if(column_index == 0 && row_index == rows -1)    // bottom left corner
         {
            blue1 = colors[index+1] % 256;
            new_composite = colors[index+1] / 256;
            green1 = new_composite % 256;
            red1 = new_composite / 256;

            blue2 = colors[index-columns] % 256;
            new_composite = colors[index-columns] / 256;
            green2 = new_composite % 256;
            red2 = new_composite / 256;

            blue = (blue1 + blue2)/2;
            green = (green1 + green2)/2;
            red = (red1 + red2)/2;

            colors[index] = blue + (green * 256) + (red * 256 * 256);
         }
         else if(column_index == columns -1 && row_index == rows -1)    // bottom right corner
         {
            blue1 = colors[index-1] % 256;
            new_composite = colors[index-1] / 256;
            green1 = new_composite % 256;
            red1 = new_composite / 256;

            blue2 = colors[index-columns] % 256;
            new_composite = colors[index-columns] / 256;
            green2 = new_composite % 256;
            red2 = new_composite / 256;

            blue = (blue1 + blue2)/2;
            green = (green1 + green2)/2;
            red = (red1 + red2)/2;

            colors[index] = blue + (green * 256) + (red * 256 * 256);
         }
         else if(row_index == 0)    // top row
         {
            blue1 = colors[index-1] % 256;
            new_composite = colors[index-1] / 256;
            green1 = new_composite % 256;
            red1 = new_composite / 256;

            blue2 = colors[index+1] % 256;
            new_composite = colors[index+1] / 256;
            green2 = new_composite % 256;
            red2 = new_composite / 256;

            blue3 = colors[index+columns] % 256;
            new_composite = colors[index+columns] / 256;
            green3 = new_composite % 256;
            red3 = new_composite / 256;

            blue = (blue1 + blue2 + blue3)/3;
            green = (green1 + green2 + green3)/3;
            red = (red1 + red2 + red3)/3;

            colors[index] = blue + (green * 256) + (red * 256 * 256);
         }
         else if(row_index == rows - 1)    // bottom row
         {
            blue1 = colors[index-1] % 256;
            new_composite = colors[index-1] / 256;
            green1 = new_composite % 256;
            red1 = new_composite / 256;

            blue2 = colors[index+1] % 256;
            new_composite = colors[index+1] / 256;
            green2 = new_composite % 256;
            red2 = new_composite / 256;

            blue3 = colors[index-columns] % 256;
            new_composite = colors[index-columns] / 256;
            green3 = new_composite % 256;
            red3 = new_composite / 256;

            blue = (blue1 + blue2 + blue3)/3;
            green = (green1 + green2 + green3)/3;
            red = (red1 + red2 + red3)/3;

            colors[index] = blue + (green * 256) + (red * 256 * 256);
         }
         else if(column_index == 0)    // left column
         {
            blue1 = colors[index+1] % 256;
            new_composite = colors[index+1] / 256;
            green1 = new_composite % 256;
            red1 = new_composite / 256;

            blue2 = colors[index-columns] % 256;
            new_composite = colors[index-columns] / 256;
            green2 = new_composite % 256;
            red2 = new_composite / 256;

            blue3 = colors[index+columns] % 256;
            new_composite = colors[index+columns] / 256;
            green3 = new_composite % 256;
            red3 = new_composite / 256;

            blue = (blue1 + blue2 + blue3)/3;
            green = (green1 + green2 + green3)/3;
            red = (red1 + red2 + red3)/3;

            colors[index] = blue + (green * 256) + (red * 256 * 256);
         }
         else if (column_index == columns - 1)  // right column
         {
            blue1 = colors[index-1] % 256;
            new_composite = colors[index-1] / 256;
            green1 = new_composite % 256;
            red1 = new_composite / 256;

            blue2 = colors[index-columns] % 256;
            new_composite = colors[index-columns] / 256;
            green2 = new_composite % 256;
            red2 = new_composite / 256;

            blue3 = colors[index+columns] % 256;
            new_composite = colors[index+columns] / 256;
            green3 = new_composite % 256;
            red3 = new_composite / 256;

            blue = (blue1 + blue2 + blue3)/3;
            green = (green1 + green2 + green3)/3;
            red = (red1 + red2 + red3)/3;

            colors[index] = blue + (green * 256) + (red * 256 * 256);
         }
         else  // center
         {            
            blue1 = colors[index+1] % 256;
            new_composite = colors[index+1] / 256;
            green1 = new_composite % 256;
            red1 = new_composite / 256;

            blue2 = colors[index-1] % 256;
            new_composite = colors[index-1] / 256;
            green2 = new_composite % 256;
            red2 = new_composite / 256;

            blue3 = colors[index-columns] % 256;
            new_composite = colors[index-columns] / 256;
            green3 = new_composite % 256;
            red3 = new_composite / 256;

            blue4 = colors[index+columns] % 256;
            new_composite = colors[index+columns] / 256;
            green4 = new_composite % 256;
            red4 = new_composite / 256;

            blue = (blue1 + blue2 + blue3+ blue4)/4;
            green = (green1 + green2 + green3 + green4)/4;
            red = (red1 + red2 + red3 + red4)/4;

            colors[index] = blue + (green * 256) + (red * 256 * 256);
         }
      }
}


void Blur::draw(int new_x, int new_y, int scaling)
/**
   precondition: x and y must be inside the drawing window, and scaling
                 must be positive.
   postcondition: digital image is drawn based on compostie color values,
                  The starting point (x,y) and the value of scaling.
**/
{
   int index;
   int red;
   int blue;
   int green;
   int new_composite;
   int x;
   int y;

   createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Blur");

   if(new_x < 640 && new_y < 480)
   {
      createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Blur");

      for(int i = 0; i < 6; i++)
      {
         for(int row_index = 0, y = new_y; row_index < rows; row_index++,y -= scaling)
            for(int column_index = 0, x = new_x; column_index < columns; column_index++, x += scaling)
            {
               index = row_index * columns + column_index;

               blue = colors[index] % 256;
               new_composite = colors[index] / 256;
               green = new_composite % 256;
               red = new_composite / 256;

               setColor(red, green, blue);

               if(scaling > 0)
                  fillRectangle(x,y, scaling, scaling);
               else
               {
                  column_index = columns;
                  row_index = rows;
                  cout << "Invalid entry for scaling." << endl;
               }
            }     // accessing 2D array
         blend();
      }  // blend 5 times
   }
   else
      cout << "Invalid starting point." << endl;

   startDrawing();
}


Blur::~Blur()
/**
   preconditions: current object is well defined.

   postconditions: the array pointed to by colors is deallocated.
**/
{
   delete[] colors;
}
