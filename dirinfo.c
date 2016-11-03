#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

int main(){
  DIR *dir = opendir(".");
  struct dirent *entry;
  int size = 0;
  struct stat buf;
  char directories[256] = "";
  char files[256] = "";
  while ((entry = readdir(dir)) != NULL){
    if (entry -> d_type == DT_DIR){
      strcat(directories, "\t");
      strcat(directories, entry -> d_name);
      strcat(directories, "\n");
    }
    else {
      strcat(files, "\t");
      strcat(files, entry -> d_name);
      strcat(files, "\n");
      stat(entry -> d_name, &buf);
      size += buf.st_size;
    }
  }
  printf("Statistics for directory:\n");
  printf("Total Directory Size:");
  if (size == 0)
    printf("%d B", size);
  if (size > 1000000000){
    printf("%d GB ", size / 1000000000);
    size = size % 1000000000;
  }
  if (size > 1000000){
    printf("%d MB ", size / 1000000);
    size = size % 1000000;
  }
  if (size > 1000){
    printf("%d KB ", size / 1000);
    size = size % 1000;
  }
  if (size > 0){
    printf("%d B", size);
    size = 0;
  }
  printf("\n");
  printf("directories:\n%s", directories);
  printf("regular files:\n%s", files); 
  return 0;
}
