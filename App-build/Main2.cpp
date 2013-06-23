#include "color_2.cpp"
#include <stdlib.h>

#define PATH "./gestures_2/gesture2/" //./gestures/gesture3/
#define MILS_IN_MID 400

string path=PATH,s;

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
  //"./gestures_2/gesture2/1.txt","w");	//modify to put numbered file
  int count=count_files()+1;
  stringstream ss;
  ss<<count;
  s=ss.str();
  rec_gest();
  filename="lol";	//this is for recording
  //fp=fopen(&filename[0],"w");
  save_callback(0);
  system("./class2");
  return 0;
}
