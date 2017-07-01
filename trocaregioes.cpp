#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

using namespace cv;
using namespace std;

int px_1, py_1, px_2, py_2;
bool clicado = false;
Mat imgOriginal;        
Mat imgGrayscale;       
Mat imgResult;          
Mat listOfRoi[4];       


void pickARoi() {
    int index[4] = { 0,1,2,3 };

    srand(time(0));
    random_shuffle(begin(index), end(index));

 
    int ind1 = index[0];
    int ind2 = index[1];
    int ind3 = index[2];
    int ind4 = index[3];

    // imprimindo apenas para checar a ordem
   cout << "\n\nOrdem : { " << ind1 << ", " << ind2 << ", " << ind3 << ", " << ind4 << " }\n\n";

    listOfRoi[ind1].copyTo(imgResult(Rect(0,                    0,                          listOfRoi[ind1].cols,   listOfRoi[ind1].rows)));    
    listOfRoi[ind2].copyTo(imgResult(Rect(listOfRoi[ind1].cols, 0,                          listOfRoi[ind2].cols,   listOfRoi[ind2].rows)));    
    listOfRoi[ind3].copyTo(imgResult(Rect(0,                    listOfRoi[ind1].rows,       listOfRoi[ind3].cols,   listOfRoi[ind3].rows)));    
    listOfRoi[ind4].copyTo(imgResult(Rect(listOfRoi[ind1].cols, listOfRoi[ind1].rows,       listOfRoi[ind4].cols,   listOfRoi[ind4].rows)));    
}


int main() {

    string arquivo;                            
    cout << "Digite o nome do arquivo : ";
    cin >> arquivo;                            
    imgOriginal = imread(arquivo);          

    if (imgOriginal.empty()) {                                                             
        cout << "error: o arquivo --> " << arquivo << " <-- n„o pode ser lido!\n\n";     
        system("pause");
        return(0);                                                                              // saindo do programa
    }

    cvtColor(imgOriginal, imgGrayscale, CV_BGR2GRAY);      
    
    namedWindow("imgOriginal", CV_WINDOW_AUTOSIZE);
    namedWindow("imgGrayscale", CV_WINDOW_AUTOSIZE);
    namedWindow("imgResult", CV_WINDOW_AUTOSIZE);

    int col_half = imgOriginal.cols / 2;
    int row_half = imgOriginal.rows / 2;

    cout << "\n\nWidth : " << imgOriginal.cols << "px\n";
    cout << "Height : " << imgOriginal.rows << "px\n\n";
   
    Rect roi1(0,            0,          col_half,   row_half);      
    Rect roi2(col_half,     0,          col_half,   row_half);      
    Rect roi3(0,            row_half,   col_half,   row_half);      
    Rect roi4(col_half,     row_half,   col_half,   row_half);      

    listOfRoi[0] = Mat(imgGrayscale, roi1);
    listOfRoi[1] = Mat(imgGrayscale, roi2);
    listOfRoi[2] = Mat(imgGrayscale, roi3);
    listOfRoi[3] = Mat(imgGrayscale, roi4);

    imgResult = Mat(imgGrayscale.rows, imgGrayscale.cols, imgGrayscale.type());

    pickARoi();

    imshow("imgOriginal", imgOriginal);
    imshow("imgGrayscale", imgGrayscale);
    imshow("imgResult", imgResult);

    waitKey(0);
    return(0);
}