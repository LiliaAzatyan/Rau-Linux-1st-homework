#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

void listFilesRec(char *bPath){
  struct dirent *dp;
  char path[1000];
  DIR *dir = opendir(bPath);
  if(!dir){
    return;
  }
  while((dp = readdir(dir)) != NULL){
    if(strcmp(dp-> d_name, ".") != 0 && 
    strcmp(dp->d_name, "..") != 0){
      printf("%s\n", dp->d_name);
      strcpy(path, bPath);
      strcat(path, "/");
      strcat(path, dp->d_name);
      listfr(path);
    }
  }
  closedir(dir);
}

int main(void) {
 char path[100];
 printf("Enter path to list files:");
 scanf("%s", path);
 listfr(path);

  return 0;
}
