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
#define PATH "./test/"

using namespace std;
using namespace cv;

int main()
{
  int correct=0,t;
  FILE *fp;
  for(int i=0;	i<5;++i)
  {
    stringstream ss;
    ss <<i+1;
    ifstream instream;
    string s,b=PATH;
    Mat img;
    for(int no=1;no<=10;++no)
    {
      stringstream ss2;
      ss2<< no;
      s=b+"gesture"+ss.str()+"/gesture"+ss2.str()+".png";
      img=imread(s);
      imwrite("lol.png",img);
      fp=popen("./class","r");
      fscanf(fp,"%d",&t);
      if(t==i+1)correct++;
      else{
	printf("Classified as:%d actual:%d\n",t,i+1);
	imshow("img",img);
	waitKey(0);
      }
    }
  }
  printf("Correct:%d , percentage:%0.2f\n",correct,(correct*100.0)/50);
  
    return 0;
}
