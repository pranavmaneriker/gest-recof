#include "gest-record.cpp"
#include <stdlib.h>

#define PATH "./" //./gestures/gesture3/
string path=PATH;

int count_files()
{
  DIR *dpdf;
  struct dirent *epdf;
  dpdf = opendir(PATH);
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

int main(int argc, char * argv[])	//arguments are path/pic
{
  int c=count_files();
  rec_gest();
  //if(argc<=1)
  int count=count_files()+1;
  stringstream ss;
  ss<<c;
  string s=ss.str();
  string filename="lol.png";//path+"gesture"+s+".png";
  imwrite(filename,rescaled);
  FILE *f=popen("./class","r");
  int t;
  fscanf(f,"%d",&t);
  printf("%d\n",t);
  return 0;
}