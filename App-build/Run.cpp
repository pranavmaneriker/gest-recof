#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sstream>
using namespace std;

FILE *fp;

int main(int argc, char * argv[])	//arguments are path/pic
{
  string bash1="bash ./scripts/";
  string bash2="bash ./scripts_2/";
  string sh=".sh";
  int retval;
  while(1)
  {
    fp=popen("./main","r");
    fscanf(fp,"%d",&retval);
    //pclose(fp);
    //if(retval<5)
    {
      //fp=popen("./main","r");
      fscanf(fp,"%d",&retval);
      printf("%d\n",retval);
      //pclose(fp);
      stringstream ss;
      ss<< retval;
      string name=(bash1+ss.str()+sh);
	  char * p;
	  p=&name[0];
      system(p);
    }
    /*if(retval==5)
    {
      fp=popen("./main2","r");
      pclose(fp);
      fp=popen("./class2","r");
      fscanf(fp,"%d",&retval);
      printf("%d\n",retval);
      pclose(fp);
      stringstream ss;
      ss<< retval;
      string name=(bash2+ss.str()+sh);
      char * p;
      p=&name[0];
      system(p);
    }*/
  }
  return 0;
}
