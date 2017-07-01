
#include <cv.h>
#include <highgui.h>

#include <stdio.h>

#include <iostream>

#include <string.h>

using namespace std;
using namespace cv;

int main(int, char**){
  Mat image;
  Vec3b val;
  int x1,x2,y1,y2;

  image= imread("imagem.jpg",CV_LOAD_IMAGE_GRAYSCALE);
 
  cout << "Digite P1 : ";
  cin >>  x1;
  cout << "Digite P1 : ";
  cin >>  y1;
  cout << "Digite P2 : ";
  cin >>  x2;
  cout << "Digite P2 : ";
  cin >>  y2;

   for (int i = x1; i < x2; ++i)
        {
             for (int j = y1; j < y2; ++j)
             {
            image.at<uchar>(i,j) = 255 - image.at<uchar>(i,j);
         }
        }

 
  imshow("janela", image);  
  waitKey();
  return 0;
}