#include <dirent.h>
#include <stdio.h>
using namespace std;
int main()
{
  DIR *dpdf;
  struct dirent *epdf;

  dpdf = opendir("./images/");
  int count=0;
  if (dpdf != NULL){
    while (epdf = readdir(dpdf)){
	count++;
        printf("Filename: %s\n",epdf->d_name);
	// std::out << epdf->d_name << std::endl;
    }
  }
  printf("%d\n",count);
//   return 0;
}