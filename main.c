#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[])
{
  char * d = malloc(100);
  if(argv[1])
  {
    d = argv[1];
  }
  else
  {
    printf("Nothing was scanned. Please enter a directory to scan.\n");
    fgets(d, 100, stdin);
    d[strlen(d) - 1] = 0;
  }
  DIR * mydir = opendir(d);
  int bytes = 0;

  if(errno)
  {
    printf("Invalid directory (or no directory at all) was entered\n");
    printf("%d: %s\n", errno, strerror(errno));
  }

  char *dir = calloc(1000, sizeof(char));
  char *files = calloc(1000, sizeof(char));

  struct stat statistics;
  stat(d, &statistics);

  if(errno)
  {
    printf("%d: %s\n", errno, strerror(errno));
  }


  struct dirent * file = readdir(mydir);
  if(errno)
  {
    printf("%d: %s\n", errno, strerror(errno));
  }

  while(file)
  {
    stat(file->d_name, &statistics);

    bytes += statistics.st_size;
    if(statistics.st_mode / 01000 == 040)
    {
      strcat(dir, file->d_name);
      strcat(dir, "\n");
    }
    else
    {
      strcat(files, file->d_name);
      strcat(files, "\n");
    }
    file = readdir(mydir);
  }
  printf("Statistics for directory \"%s\"\nTotal directory size: %lld Bytes\n\n", d, bytes);
  printf("Directories:\n%sRegular files:\n%s\n", dir, files);
  return 0;
}
