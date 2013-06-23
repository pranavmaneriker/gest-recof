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
#define PATH "./test_2/"

using namespace std;
using namespace cv;

int main()
{
  int correct=0,t;
  FILE *fp;
  FILE *op;
  ifstream  src;
  ofstream dst;
  string line;
  for(int i=0;	i<3;++i)
  {
    stringstream ss;
    ss <<i+1;
    string s,b=PATH;
    for(int no=1;no<=10;++no)
    {
      stringstream ss2;
      ss2<< no;
      s=b+"gesture"+ss.str()+"/gesture"+ss2.str()+"";
      src.open(&s[0]);
      op=fopen("lol","w");
      while(!src.eof())
      {
	getline(src,line);
	fprintf(op,"%s\n",&line[0]);
      }
      fp=popen("./class2","r");
      fscanf(fp,"%d",&t);
      fclose(fp);
      if(t==i+1)correct++;
      else{
	printf("Classified as:%d actual:%d\n",t,i+1);
      }
    }
  }
  printf("Correct:%d\n",correct);
    return 0;
}
