#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image;
  int width, height;
  VideoCapture cap;
  Mat hist, oldHist;
  int nbins = 64;
  float range[] = {0, 256};
  const float *histrange = { range };
  bool uniform = true;
  bool acummulate = false;
  cap.open(0);
  
  if(!cap.isOpened()){
    cout << "cameras indisponiveis";
    return -1;
  }
  
  width  = cap.get(CV_CAP_PROP_FRAME_WIDTH);
  height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

  cout << "largura = " << width << endl;
  cout << "altura  = " << height << endl;

  int histw = nbins, histh = nbins/2;
  Mat histImg(histh, histw, CV_8UC1, Scalar(0));
  int count = 0; 
  double histDiff = 0; 

  while(1){   
    cap >> image;
    cvtColor(image, image, CV_BGR2GRAY);

    calcHist(&image, 1, 0, Mat(), hist, 1,
             &nbins, &histrange,
             uniform, acummulate);
    normalize(hist, hist, 0, histImg.rows, NORM_MINMAX, -1, Mat());

    histImg.setTo(Scalar(0));

    for(int i=0; i<nbins; i++){
      line(histImg, Point(i, histh),
           Point(i, cvRound(hist.at<float>(i))),
           Scalar(255), 1, 8, 0);
   }
    
    histImg.copyTo(image(Rect(0, 0       ,nbins, histh)));
    imshow("image", image);
    
    if(count >=1)
       histDiff = compareHist(hist, oldHist, 0);
   
    if( histDiff < 0.98)
       cout << "motion detected, histDiff = " << histDiff << endl;
    oldHist = hist.clone();
    count++;
    if(waitKey(30) >= 0) break;
  }
  return 0;
}

