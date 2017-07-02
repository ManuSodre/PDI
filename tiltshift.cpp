#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>

using namespace cv;
using namespace std;

int d_slider = 0;
int d_max = 100;

int sup_slider = 0;
int sup_max;

int inf_slider = 0;
int inf_max;

Mat original, borrada, final ;
Mat imageTop;

char TrackbarName[50];

double calcAlpha(double x, double l1, double l2, double d){
  return 0.5*(tanh((x-l1)/d) - tanh((x-l2)/d));
}

void blend(int, void*){
 for (int i = 0; i < original.rows ; i++)
 {
   double alpha = calcAlpha(i,sup_slider,inf_slider,d_slider);
   addWeighted(original.row(i),alpha, borrada.row(i),1-alpha,0.0,final.row(i));
 }
 imshow("resultado", final);
 imwrite("resutTiltShift.jpg", final);
}

int main(int argvc, char** argv){

  original = imread("india.jpg");
  original.copyTo(borrada);
  original.copyTo(final);
  namedWindow("resultado", 1);

  float media[] = {1,1,1,
           1,1,1,
           1,1,1};
  Mat mask(3,3,CV_32F), mask1;

  mask = Mat(3, 3, CV_32F, media);
  scaleAdd(mask, 1/9.0, Mat::zeros(3,3,CV_32F), mask1);
  mask = mask1;

  for (int i = 0; i < 40; ++i)
  {
    filter2D(original, borrada, original.depth(), mask, Point(1,1), 0);
  }

  sup_max = original.rows;
  inf_max = original.rows;

  sprintf( TrackbarName, "Decaimento");
  createTrackbar( TrackbarName, "resultado",
          &d_slider,
          d_max,
          blend );
  blend(d_slider, 0 );

  sprintf( TrackbarName, "Limite superior");
  createTrackbar( TrackbarName, "resultado",
          &sup_slider,
          sup_max,
          blend);
  blend(sup_slider, 0 );

  sprintf( TrackbarName, "Limite inferior");
  createTrackbar( TrackbarName, "resultado",
          &inf_slider,
          inf_max,
          blend );
  blend(inf_slider, 0 );


  waitKey(0);
  return 0;
}