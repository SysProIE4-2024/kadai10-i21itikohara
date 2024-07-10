/*
 *  mysystem.c : system 関数のクローン
 */

#include <stdio.h>
#include <stdlib.h>    // exit, system のため
#include <unistd.h>    // fork, execXX のため
#include <sys/wait.h>  // wait のため
#include "mysystem.h"  // インタフェース

// system関数のクローン
static char *execpath="/bin/sh";
int mysystem(char *command) {
  int status=0;
  pid_t pid;
  if(command == NULL) {
    return 1;
  } else if((pid=fork())<0) {
    return -1;
  }
  if(pid != 0) {
    
    while(wait(&status) != pid)
      ;
    
  } else {
    execl(execpath, "sh", "-c", command, (char *)NULL);
    exit(127);
  }

  return status;
}


/* 実行例
ichikoharario@ichikohararionoMacBook-Air kadai10-i21itikohara % make          
cc -Wall -std=c99 -o mysysmain mysysmain.c  mysystem.c
ichikoharario@ichikohararionoMacBook-Air kadai10-i21itikohara % ./mysysmain ls
mysystem:
Makefile	README.pdf	mysysmain.c	mysystem.h
README.md	mysysmain	mysystem.c	x.txt
retval = 00000000
system:
Makefile	README.pdf	mysysmain.c	mysystem.h
README.md	mysysmain	mysystem.c	x.txt
retval = 00000000

　〜2つ以上のコマンドを入力したいとき〜
ichikoharario@ichikohararionoMacBook-Air kadai10-i21itikohara % ./mysysmain "ls -l"
mysystem:
total 624
-rw-r--r--  1 ichikoharario  staff     143  7  4 09:45 Makefile
-rw-r--r--  1 ichikoharario  staff    2795  7  4 09:45 README.md
-rw-r--r--@ 1 ichikoharario  staff  238232  7  4 09:45 README.pdf
-rwxr-xr-x  1 ichikoharario  staff   50376  7  9 15:01 mysysmain
-rw-r--r--  1 ichikoharario  staff     933  7  9 14:58 mysysmain.c
-rw-r--r--  1 ichikoharario  staff    1517  7  9 15:14 mysystem.c
-rw-r--r--  1 ichikoharario  staff      90  7  4 09:45 mysystem.h
-rw-r--r--@ 1 ichikoharario  staff      20  7  4 10:11 x.txt
retval = 00000000
system:
total 624
-rw-r--r--  1 ichikoharario  staff     143  7  4 09:45 Makefile
-rw-r--r--  1 ichikoharario  staff    2795  7  4 09:45 README.md
-rw-r--r--@ 1 ichikoharario  staff  238232  7  4 09:45 README.pdf
-rwxr-xr-x  1 ichikoharario  staff   50376  7  9 15:01 mysysmain
-rw-r--r--  1 ichikoharario  staff     933  7  9 14:58 mysysmain.c
-rw-r--r--  1 ichikoharario  staff    1517  7  9 15:14 mysystem.c
-rw-r--r--  1 ichikoharario  staff      90  7  4 09:45 mysystem.h
-rw-r--r--@ 1 ichikoharario  staff      20  7  4 10:11 x.txt
retval = 00000000

　〜コマンドがエラーになる場合〜
ichikoharario@ichikohrionoAir kadai10-i21itikohara % ./mysysmain "rename a b"
mysystem:
sh: rename: command not found
retval = 00007f00
system:
sh: rename: command not found
retval = 00007f00
返り値127が16進数に変換されて7fと表示される。

　〜コマンドを入力しない場合〜
ichikoharario@ichikohararionoMacBook-Air kadai10-i21itikohara % ./mysysmain    
使い方 : ./mysysmain コマンド文字列

*/
