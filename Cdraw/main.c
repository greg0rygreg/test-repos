#include "libmenu.h"
#include "strutils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char** argv) {
  int anl = 75;
  int fnl = 512;
  for (int i = 0; i < argc; i++) {
    if (strcmp("-anl", argv[i]) == 0)
      anl = atoi(argv[i+1]);
    if (strcmp("-fnl", argv[i]) == 0)
      fnl = atoi(argv[i+1]);
  }
  int optionsN = 3;
  int optionsAN = 1;
  char** options = malloc(sizeof(char*) * 3);
  options[0] = strdup("make canvas");
  options[1] = strdup("view canvas [WIP]");
  options[2] = strdup("info");
  char** optionsA = malloc(sizeof(char*) * 1);
  optionsA[0] = strdup("toggle pixel");

  // i love making my own libs and using them to my advantage
  Menu* menu = initMenu("Cdraw", "alpha1", options, optionsN, "exit");
  Menu* drawing = initMenu("actions:", "", optionsA, optionsAN, "save canvas & exit");

  char* FV = getFormattedVersion(menu, 1);

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
        b = 1;
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
            case 0: {
              clear();
              b2++;
              time_t _time = time(NULL);
              char aname[anl];
              printf("author name (max. %d characters): ", anl);
              ignorePrev();
              fgets(aname, anl, stdin);
              aname[strlen(aname) - 1] = 0x00;
              // simplifying this to (h * 2) * w doesn't work for some reason....
              char* cuh1 = malloc(h * w + (h - 1) + 1);
              int g = 0;
              for (int i = 0; i < h; i++) {
                for (int j = 0; j < w; j++) {
                  cuh1[g] = (canvas[i][j] == 0 ? '0' : '1');
                  g++;
                }
                cuh1[g] = '.';
                g++;
              }
              cuh1[strlen(cuh1) - 1] = 0x00;
              char* cuh[] = {"CDC", cuh1, aname};
              char* cuh3 = strjoin(cuh, 3, ';');
              char fname[fnl];
              printf("filename (max. %d characters & defaults to current directory): ", fnl);
              fgets(fname, fnl, stdin);
              fname[strlen(fname) - 1] = 0x00;
              clear();
              FILE* file = fopen(fname, "w");
              if (!file) {
                error("file could not be opened - data will be printed");
                // i found using fprintf to output data to stdout funny
                // ...i'm not sorry
                fprintf(stdout, "%s;%lo\n", cuh3, _time);
                sep();
              } else
                fprintf(file, "%s;%lo", cuh3, _time);
              dptrfree((void**)canvas, h);
              free(cuh1);
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
        warning("work in progress");
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
// [...] means the thing inside it needs to be written on windows
// clang -o main[.exe] main.c libmenu.c strutils.c