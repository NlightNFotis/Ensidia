#include "../include/types.h"
#include "../include/stat.h"
#include "../include/user.h"

char buf[512];

void
wc(int fd, char *name)
{
  int i, n;
  int lines, words, characters, inword;

  lines = words = characters = 0;
  inword = 0;
  while((n = read(fd, buf, sizeof(buf))) > 0){
    for(i=0; i<n; i++){
      characters++;
      if(buf[i] == '\n')
        lines++;
      if(strchr(" \r\t\n\v", buf[i]))
        inword = 0;
      else if(!inword){
        words++;
        inword = 1;
      }
    }
  }
  if(n < 0){
    printf(1, "wc: read error\n");
    exit();
  }

  /* Report to the user. */
  printf(1, "Reporting for file: %s\n", name);
  printf(1, "  lines: %d\n", lines);
  printf(1, "  words: %d\n", words);
  printf(1, "  chars: %d\n", characters);
}

int
main(int argc, char *argv[])
{
  int fd, i;

  if(argc <= 1){
    wc(0, "");
    exit();
  }

  for(i = 1; i < argc; i++){
    if((fd = open(argv[i], 0)) < 0){
      printf(1, "wc: cannot open %s\n", argv[i]);
      exit();
    }
    wc(fd, argv[i]);
    close(fd);
  }
  exit();
}
