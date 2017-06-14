#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ctime>
#include <cstdlib>

using namespace std;
using namespace cv;

#define STEP 5
#define JITTER 3
#define RAIO 5

int main(int argc, char** argv){
  Mat Original, borderOriginalImage;
  Mat Pontilhismo;
  int x, y, width, height, gray;
  //arrays de índices que servirão para identificar elementos da imagem de referência
  vector<int> yrange;
  vector<int> xrange;

  srand(time(0));

  Original= imread("imagem.jpg" ,CV_LOAD_IMAGE_GRAYSCALE);

  width = Original.size().width;
  height = Original.size().height;
  xrange.resize(height/STEP);
  yrange.resize(width/STEP);
  iota(xrange.begin(), xrange.end(), 0);
  iota(yrange.begin(), yrange.end(), 0);

  for(uint i=0; i<xrange.size(); i++){
    xrange[i]= xrange[i]*STEP+STEP/2;
  }

  for(uint i=0; i<yrange.size(); i++){
    yrange[i]= yrange[i]*STEP+STEP/2;
  }

  Original.copyTo(Pontilhismo);

  //Executa o pontilhismo;
  for(auto i : xrange){
    random_shuffle(yrange.begin(), yrange.end());
    for(auto j : yrange){
      x = i+rand()%(2*JITTER)-JITTER+1;
      y = j+rand()%(2*JITTER)-JITTER+1;
      gray = Original.at<uchar>(x,y);
      circle(Pontilhismo, cv::Point(y,x), RAIO, CV_RGB(gray,gray,gray), -1, CV_AA);
    }
  }

  imshow("Imagem Pontilhista", Pontilhismo);
  imwrite("imagemComPontilhismo.jpg", Pontilhismo);

   //Aplica Canny
   for(int z=0; z<5; z++){
     Canny(Original, borderOriginalImage, 10*z, 50*z);
     int raio = 5-z;

     for(int i=0; i<height; i++ ){
        for(int j=0; j<width; j++){
           if(borderOriginalImage.at<uchar>(i,j) == 255){
              gray = Original.at<uchar>(i,j);
              circle(Pontilhismo, cv::Point(j,i), raio, CV_RGB(gray,gray,gray), -1, CV_AA);
             }
        }
    }
    
    //Limiar = Limiar*10;
  }
  imshow("Pontilhismo", Pontilhismo);
  imwrite("imagemComPontilhismo.jpg", Pontilhismo);
 

   waitKey();
  return 0;
}



