#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

void showmatrix(int arr[][4]);
void gamerule(int arr[][4]);
int shiftleft(int arr[][4]);
int shiftup(int arr[][4]);
int shiftdown(int arr[][4]);
int shiftright(int arr[][4]);
void creatmatrix(int arr[][4]);
int readenteredkey();
void swap(int *, int *);

void showmatrix(int arr[][4])
{
   int i, j;
   printf("--------------------\n");
   for (i = 0; i < 4; i++)
   {
      printf("|");
      for (j = 0; j < 4; j++)
      {
         if (arr[i][j] != 0)
            printf("%2d |", arr[i][j]);
         else
            printf("  | ");
      }
      printf("\n");
   }

   printf("--------------------\n");
}

int winner(int arr[][4])
{
   int i, j, k = 1;
   for (i = 0; i < 4; i++)
   {
      for (j = 0; j < 4; j++, k++)
         if (arr[i][j] != k && k != 16)
            break;
      if(j<4)      
      break;
   }
   if (j < 4)
      return 0;
   return 1;
}

void gamerule(int arr[][4])
{
   system("cls");

   int i, j, k = 1;

   printf("\t\t  MATRIX PUZZLE GAME \n");
   printf("\n");
   printf(ANSI_COLOR_RED "                 RULES OF PUZZLE GAME             \n" ANSI_COLOR_RESET);
   printf(ANSI_COLOR_RED "\n1.You can move only one 1 step at a time by arrow key" ANSI_COLOR_RESET);
   printf("\n\tmove up   : by up arrow key");
   printf("\n\tmove down : by down arrow key");
   printf("\n\tmove left : by left arrow key");
   printf("\n\tmove right : by right arrow key");

   printf(ANSI_COLOR_RED "\n2.you can move number at empty space only" ANSI_COLOR_RED);
   printf("\n");
   printf(ANSI_COLOR_RED "\n3.for each valid move : your total number of moves will decreases by 1 \n" ANSI_COLOR_RED);
   printf(ANSI_COLOR_RED "\n4. wining situation :" ANSI_COLOR_RED);
   printf(ANSI_COLOR_RED "\n Numbers in 4*4 matrix should be in  order frome 1 to 15 " ANSI_COLOR_RED);
   printf("\n\n       wining situation       \n");
   printf(ANSI_COLOR_YELLOW "--------------------\n" ANSI_COLOR_RED);
   for (i = 0; i < 4; i++)
   {
      printf(ANSI_COLOR_YELLOW "| " ANSI_COLOR_RESET);
      for (j = 0; j < 4; j++)
      {
         if (arr[i][j] != 0)
            printf(ANSI_COLOR_MAGENTA "%2d |" ANSI_COLOR_RESET,4*i+j+1);
         else
            printf(ANSI_COLOR_MAGENTA "  |" ANSI_COLOR_RESET);
      }
      printf("\n");
   }
   printf(ANSI_COLOR_YELLOW "--------------------\n" ANSI_COLOR_RESET);
   printf("\n5. You can exit the game at any time by pressing 'E' or 'e' ");

   printf("\n so try to win in minimum number of moves \n");
   printf(" Enter any key to start .....");

   int x = readenteredkey();
}

int main()
{
   int arr[4][4];
   int maxtry = 300;
   char name[20];
   for (int k = 0; k < 3; k++)
      printf("\n");
   printf("player name:");
   scanf("%s", &name);

   system("cls");

   while (1)
   {
      creatmatrix(arr);
      gamerule(arr);

      while (!winner(arr))
      {
         system("cls");
         if (!maxtry)
            break;
         printf("\n\n player name: %s, move remaing : %d\n\n", name, maxtry);
         showmatrix(arr);
         int key = readenteredkey();
         switch (key)
         {
         case 101:
         case 69:
            printf("\a\a\a\a\a\a\n   Thanks for playing ! \n\a\a");
            printf("\nhit 'enter' to exit the game \n");
            key = readenteredkey();
            return 0;
         case 72:
            if (shiftup(arr))
               maxtry--;
            break;
         case 80:
            if (shiftdown(arr))
               maxtry--;
            break;
         case 77:
            if (shiftright(arr))
               maxtry--;
            break;
         case 75:
            if (shiftleft(arr))
               maxtry--;
            break;
         default:
            printf("\n\n  \a\a\a\a Not allowed \a\a");
         }
      }

      if (!maxtry)
         printf(ANSI_COLOR_RED "\n\a\a        YOU LOSE  !   \a\a\a\n" ANSI_COLOR_RESET);
      else
         printf(ANSI_COLOR_GREEN "\n\a!!!!!!!!!!!!!!!!!!Congratulation %s for winning this game !!!!!!!!!!!!!!!\a\a\a\a\a\a\a\a\a\n"ANSI_COLOR_RESET,name);

      fflush(stdin);
      char check;
      printf(ANSI_COLOR_YELLOW "\n\nWant to play again ? \n\n" ANSI_COLOR_RESET);
      printf("enter 'y' to play again :");
      scanf("%c", &check);

      if ((check != 'y') && (check != 'Y'))
         break;

      maxtry = 300;
   }

   return 0;
}

void creatmatrix(int arr[][4])
{
   int n = 15;
   int num[n], i, j;
   for (i = 0; i < 15; i++)
      num[i] = i + 1;

   srand(time(NULL));
   int lastindex = n - 1, index;
   for (i = 0; i < 4; i++)
   
      for (j = 0; j < 4; j++)
      {
         if (lastindex >= 0)
         {
            index = rand() % (lastindex + 1);
            
            arr[i][j] = num[index];
            num[index] = num[lastindex--];
         }
      }
   
   arr[i - 1][j - 1] = 0;
}

int shiftup(int arr[][4])
{
   int i, j;
   for (i = 0; i < 4; i++)
   {
      for (j = 0; j < 4; j++)
         if (arr[i][j] == 0)
            break;
      if (j < 4)
         break;
   }
   if (i == 3)
      return 0;

   swap(&arr[i][j], &arr[i + 1][j]);
   return 1;
}
int shiftdown(int arr[][4])
{
   int i, j;
   for (i = 0; i < 4; i++)
   {
      for (j = 0; j < 4; j++)
         if (arr[i][j] == 0)
            break;
      if (j < 4)
         break;
   }
   if (i == 0)
      return 0;

   swap(&arr[i][j], &arr[i - 1][j]);
   return 1;
}
int shiftright(int arr[][4])
{
   int i, j;
   for (i = 0; i < 4; i++)
   {
      for (j = 0; j < 4; j++)
         if (arr[i][j] == 0)
            break;
      if (j < 4)
         break;
   }
   if (j == 0)
      return 0;

   swap(&arr[i][j], &arr[i][j - 1]);
   return 1;
}
int shiftleft(int arr[][4])
{
   int i, j;
   for (i = 0; i < 4; i++)
   {
      for (j = 0; j < 4; j++)
         if (arr[i][j] == 0)
            break;
      if (j < 4)
         break;
   }
   if (j == 3)
      return 0;

   swap(&arr[i][j], &arr[i][j + 1]);
   return 1;
}

void swap(int *a, int *b)
{
   *a = *a + *b;
   *b = *a - *b;
   *a = *a - *b;
   printf("");
}

int readenteredkey()
{
   char c;
   c = _getch();
   if (c == -32)
      c = _getch();

   return c;
}