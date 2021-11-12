#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>

//#define BUFSIZE 256


long int GET_SIZE (const char* file_name)
{
  struct stat st;
  if(stat(file_name) == 0)
  {
    return st.st_size;
  } 
  else
  {
    return -1;
  }
}

int main(int argc, char** argv[])
{
  //char buf[BUFSIZE];
  char buffer[256];
  const char* f1 = "/home/lilia/Desktop/Homeworks/names.txt";
  const char* f2 = "/home/lilia/Desktop/Homeworks/names3.txt";
  int filedisc1 = open(f1, O_RDONLY);
  int filedisc2 = open(f2, O_RDONLY);
  if(filedisc1 == 0 || filedisc2 == 0)
  {
    printf("Failed to open the file");
    exit(EXIT_FAILURE);
  }
  int filedisc = open("output.txt", O_RDONLY | O_CREAT);
  
  int size1 = GET_SIZE("names.txt");
  int size2 = GET_SIZE("names3.txt");
  read(filedisc1, buf, size1);
  read(filedisc2, buf, size2);
  write(buf, filedisc, sizeof(buf));

  close(filedisc1);
  close(filedisc2);
  close(filedisc);
  
  return 0;
}
