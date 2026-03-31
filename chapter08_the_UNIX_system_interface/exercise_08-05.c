// Exercise 8.5
// Modify the fsize program to print the other information contained
// in the inode entry.

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

void fsize(char *);
void dirwalk(char *, void (*fcn)(char *));

/* print file sizes */
int main(int argc, char **argv){
  if(argc == 1)        /* default: current directory */
    fsize(".");
  else
    while (--argc > 0)
      fsize(*++argv);

  return 0;
}

/* fsize: print size of file "name" */
void fsize(char *name){
  struct stat stbuf;

  if(stat(name, &stbuf) == -1){
    fprintf(stderr, "fsize: can't access %s\n", name);
    return;
  }

  if((stbuf.st_mode & S_IFMT) == S_IFDIR)
    dirwalk(name, fsize);

  printf("inode: %ld | mode: %o | links: %ld | uid: %d | gid: %d | size: %lld | %s\n",
    (long)stbuf.st_ino,
    (unsigned int)stbuf.st_mode,
    (long)stbuf.st_nlink,
    stbuf.st_uid,
    stbuf.st_gid,
    (long long)stbuf.st_size,
    name);
}

/* dirwalk: apply fcn to all files in dir */
void dirwalk(char *dir, void (*fcn)(char *)){
  char name[1024];
  struct dirent *dp;
  DIR *dfd;

  if((dfd = opendir(dir)) == NULL){
    fprintf(stderr, "dirwalk: can't open %s\n", dir);
    return;
  }

  while((dp = readdir(dfd)) != NULL){
    if(strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
      continue;

    snprintf(name, sizeof(name), "%s/%s", dir, dp->d_name);
    (*fcn)(name);
  }

  closedir(dfd);
}
