#include "opencv2/opencv.hpp"
#include "cv.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sstream>
#include <dirent.h>
#include <fstream>

#define PATH "./gestures_2/"
using namespace std;
using namespace cv;

string path =PATH;
int ct;
int count_files()
{
  DIR *dpdf;
  struct dirent *epdf;
  dpdf = opendir("./2_col_train/");
  int count=0;
  if (dpdf != NULL)
  {
    while (epdf = readdir(dpdf))
    {
	count++;
    }
  }
  return count-2;
}

int main()
{
  CvSVMParams params;
  params.svm_type    = CvSVM::C_SVC;
  params.kernel_type = CvSVM::LINEAR;
  params.term_crit   = cvTermCriteria(CV_TERMCRIT_ITER, 1000, 1e-6);
  CvSVM svm;
  ct=count_files();
  Mat rowimg(51,51,CV_32FC1);
  Point prev(0,0);
  ifstream instream;
  instream.open("lol");
  int x,y;
  for(int k=0;k<30;k++)
  {
	  instream >> x >> y;
	  line(rowimg,Point(25+x,25+y),prev,Scalar((k+1)*8),1,4);
	  prev.x=25+x;prev.y=25+y;
  }
  Mat img_mat_1d(1,51*51,CV_32FC1);
  int ii=0;
  for(int i=0;i<51;++i)
  {
    for(int j=0;j<51;++j)
    {
      img_mat_1d.at<float>(0,ii++)=rowimg.at<float>(i,j);
    }
  }
    //printf("%s\n",p);
    svm.load("./2_col_train/traindata"); // loading
    float pred=svm.predict(img_mat_1d);
    printf("%d\n",(int)pred);
    return 0;
}
