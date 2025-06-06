// 06/06/2025
// i have replaced (almost) every char* with str because inside strutils.h,
// there's a typedef that defines char* to be str.
// i'm not sure if this will work for a long time, but... yeah
#include "libmenu.h"
#include "strutils.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, str* argv) {
  int anl = 128;
  int fnl = 512;
  int fl = 2048;
  int debug = 0;
  for (int i = 0; i < argc; i++) {
    if (strcmp("-anl", argv[i]) == 0)
      anl = atoi(argv[i+1]);
    if (strcmp("-fnl", argv[i]) == 0)
      fnl = atoi(argv[i+1]);
    if (strcmp("-fl", argv[i]) == 0)
      fl = atoi(argv[i+1]);
    if (strcmp("-d", argv[i]) == 0)
      debug = 1;
  }
  int optionsN = 3;
  int optionsAN = 2;
  str* options = malloc(sizeof(str) * optionsN);
  if (!options) return 1;
  // i don't want to hear ANY of you say i need to handle errors in here too.
  // if it says (null) or outputs garbage mem it's YOUR problem for not having
  // enough memory available at the disposal of this program
  options[0] = strdup("make canvas");
  options[1] = strdup("view canvas");
  options[2] = strdup("info");
  str* optionsA = malloc(sizeof(str) * optionsAN);
  if (!optionsA) {
    dptrfree((void**)options, optionsN);
    return 1;
  }
  optionsA[0] = strdup("toggle pixel");
  optionsA[1] = strdup("invert every pixel");

  // i love making my own libs and using them to my advantage
  Menu* menu = initMenu("Cdraw", "alpha3-rc2", options, optionsN, "exit");
  // manual memory management is very fun indeed
  //
  // (i hate it)
  if (!menu) {
    dptrfree((void**)options, optionsN);
    dptrfree((void**)optionsA, optionsAN);
    return 1;
  }
  Menu* drawing = initMenu("actions:", "", optionsA, optionsAN, "save canvas & exit");
  if (!drawing) {
    dptrfree((void**)options, optionsN);
    dptrfree((void**)optionsA, optionsAN);
    free(menu);
    return 1;
  }

  str FV = getFormattedVersion(menu, 1);

  int b = 0;

  // do you think it's a good idea to do this?
  Menu* menus[] = {menu, drawing};
  clear();
  while (!b) {
    int mO;
    printAndGetInput(menu, &mO, 1, 1);
    switch (mO) {
      case 0: {
        clear();
        b++;
        break;
      }
      case 1: {
        clear();
        int w;
        int h;
        int fail = 0;
        printf("width: ");
        scanf("%d", &w);
        printf("height: ");
        scanf("%d", &h);
        clear();
        if (h < 2 || w < 2) {
          error("it's impossible to generate a canvas that has less than 2 pixels of height or width without being corrupted on the output");
          sep();
          break;
        }
        int** canvas = malloc(sizeof(int*) * h);
        if (canvas == NULL) {
          error("canvas creation failed - breaking now");
          sep();
          break;
        }
        for (int i = 0; i < h; i++) {
          canvas[i] = malloc(sizeof(int) * w);
          if (canvas[i] == NULL) {
            for (int j = 0; j < i; j++) free(canvas[j]);
            free(canvas);
            // fail pro max
            fail++;
            error("canvas creation failed (one of the elements couldn't be allocated) - breaking now");
            sep();
            break;
          }
          for (int j = 0; j < w; j++) canvas[i][j] = 0;
        }
        if (fail != 0) break;
        int b2 = 0;
        while (!b2) {
          for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++)
              printf("%s", (canvas[i][j] == 0 ? ". " : "@ "));
            putchar('\n');
          }
          sep();
          int dO;
          printAndGetInput(drawing, &dO, 1, 0);
          switch (dO) {
            case 1: {
              clear();
              int x;
              int y;
              printf("X coordinate (1-%d): ", w);
              scanf("%d", &x);
              printf("Y coordinate (1-%d): ", h);
              scanf("%d", &y);
              // i can do better than this i promise
              if (x-1 <= w && y-1 <= h && y-1 >= 0 && x-1 >= 0)
                canvas[y-1][x-1] = !canvas[y-1][x-1];
              clear();
              break;
            }
            case 2: {
              clear();
              for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++)
                  canvas[y][x] = !canvas[y][x];
              }
              break;
            }
            case 0: {
              clear();
              b2++;
              time_t _time = time(NULL);
              char aname[anl];
              printf("author name (max. %d characters): ", anl);
              ignorePrev();
              fgets(aname, anl, stdin);
              aname[strlen(aname) - 1] = 0x0;
              // char[] variables aren't modifiable
              // horrible fate
              str nname = strreplace(aname, ';', '_', NULL);
              // simplifying h * w + (h - 1) + 1 to (h * 2) * w doesn't work for some reason....
              // also, i've tried redoing the code from this line until the line that sets the
              // second from last character to a null terminator, but failed MISERABLY as it not
              // only output garbage memory when height or width were below 2, it started to output
              // 2 bytes of garbage memory EVERY time at the start, so the check in line 64 will
              // remain there until i'm smart enough to PREDICT what this god-doesn't-even-know-
              // what-this-is abomination of code will generate.
              str cuh1 = malloc(h * w + (h - 1) + 1);
              if (!cuh1) {
                clear();
                // truly heartbreaking
                error("generating canvas failed - your artwork has NOT been saved...");
                sep();
                break;
              }
              int g = 0;
              for (int i = 0; i < h; i++) {
                for (int j = 0; j < w; j++) {
                  cuh1[g] = (canvas[i][j] == 0 ? '0' : '1');
                  g++;
                }
                cuh1[g] = '.';
                g++;
              }
              cuh1[strlen(cuh1) - 1] = 0x0;
              str cuh[] = {"CDC", cuh1, nname};
              // i love making my own libs and using them to my advantage
              str cuh3 = strjoin(cuh, 3, ';');
              char fname[fnl];
              printf("filename (max. %d characters & defaults to current directory): ", fnl);
              fgets(fname, fnl, stdin);
              fname[strlen(fname) - 1] = 0x0;
              clear();
              FILE* file = fopen(fname, "w");
              if (!file) {
                error("file could not be opened - data will be printed");
                // i found using fprintf to output data to stdout funny
                // ...i'm not sorry
                fprintf(stdout, "%s;%ld\n", cuh3, _time);
                sep();
              } else
                fprintf(file, "%s;%ld", cuh3, _time);
              dptrfree((void**)canvas, h);
              free(cuh1);
              free(nname);
              free(cuh3);
              if (file) fclose(file);
              break;
            }
            default: {
              clear();
              inputErr(&dO);
              sep();
              break;
            }
          }
        }
        break;
      }
      case 2: {
        clear();
        char fname[fnl];
        printf("filename (max. %d characters & defaults to current directory): ", fnl);
        ignorePrev();
        fgets(fname, fnl, stdin);
        fname[strlen(fname) - 1] = 0x0;
        FILE* file = fopen(fname, "r");
        clear();
        if (!file) {
          error("file doesn't exist");
          sep();
          break;
        }
        /*
           _ _                         _                               
          (_| )_ __ ___    _ __   ___ | |_   ___  ___  _ __ _ __ _   _ 
          | |/| '_ ` _ \  | '_ \ / _ \| __| / __|/ _ \| '__| '__| | | |
          | | | | | | | | | | | | (_) | |_  \__ \ (_) | |  | |  | |_| |
          |_| |_| |_| |_| |_| |_|\___/ \__| |___/\___/|_|  |_|   \__, |
                                                                  |___/
        */
        char buf[fl];
        fgets(buf, fl, file);
        size_t l = 0;
        size_t lc = 0;
        str* split = strsplit(buf, ';', &l);
        if (strcmp(split[0], "CDC") != 0 || l != 4) {
          error("file is in the wrong format");
          sep();
          fclose(file);
          dptrfree((void**)split, l);
          break;
        }
        time_t _time = atoi(split[3]);
        struct tm* times = localtime(&_time);
        char tb[100];
        str canvas = strdup(split[1]);
        strftime(tb, 100, "%m/%d/%Y @ %H:%M:%S", times);
        printf("painted by: %s\ntime painted: %s\n\n", split[2], tb);
        // this is terrible fucking code but it's the best i can do
        // so if it works, don't touch it
        for (size_t i = 0; i < strlen(canvas); i++) {
          if (canvas[i] == '1')
            printf("@ ");
          else if (canvas[i] == '0')
            printf(". ");
          else if (canvas[i] == '.')
            printf("\n");
        }
        printf("\n");
        dptrfree((void**)split, l);
        free(canvas);
        fclose(file);
        sep();
        break;
      }
      case 3: {
        clear();
        printf("%s - DRAWscii in C\nlicensed under MIT license\nmade with love and patience by greg\n", FV);
        sep();
        break;
      }
      default: {
        clear();
        inputErr(&mO);
        sep();
        break;
      }
    }
  }
  for (int i = 0; i < 2; i++) deallocMenu(menus[i]);
  free(FV);
  return 0;
}

// compiling:
// make