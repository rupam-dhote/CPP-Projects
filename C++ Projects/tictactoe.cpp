#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

class Tictactoe
{
private:
  char arr[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
  int size = 9;
  pair<string, pair<char, int>> player1, player2;
  char flag = 'X';

  void print(char *arr)
  {

    cout << RED << endl
         << "      ----!! Tic Tac Toe !!----  " << RESET << endl;
    cout << endl
         << endl
         << "              ";
    int k = 1, j = 1;
    for (int i = 0; i < size; i++)
    {
      if (k != j * 3)
      {
        if (arr[i] == 'X')
          cout << YELLOW << arr[i] << RESET << CYAN << " | " << RESET;
        else if (arr[i] == 'O')
          cout << GREEN << arr[i] << RESET << CYAN << " | " << RESET;
        else
          cout << arr[i] << CYAN << " | " << RESET;
      }
      else
      {
        if (arr[i] == 'X')
          cout << YELLOW << arr[i] << RESET << " ";
        else if (arr[i] == 'O')
          cout << GREEN << arr[i] << RESET << " ";
        else
          cout << arr[i] << " ";
        j++;
      }

      if (k++ % 3 == 0)
      {
        if (k - 1 != 9)
          cout << endl
               << "             " << CYAN << "---|---|---" << RESET << endl
               << "              ";
      }
    }
    cout << endl
         << endl;
  }

  bool iswinning()
  {

    if ((arr[0] == arr[1] && arr[0] == arr[2] && arr[0] != ' ') || (arr[3] == arr[4] && arr[3] == arr[5] && arr[3] != ' ') || (arr[6] == arr[7] && arr[6] == arr[8] && arr[6] != ' '))
    {
      return true;
    }
    else if ((arr[0] == arr[3] && arr[0] == arr[6] && arr[0] != ' ') || (arr[1] == arr[4] && arr[1] == arr[7] && arr[1] != ' ') || (arr[2] == arr[5] && arr[2] == arr[8] && arr[2] != ' '))
    {
      return true;
    }
    else if ((arr[0] == arr[4] && arr[0] == arr[8] && arr[0] != ' ') || (arr[2] == arr[4] && arr[2] == arr[6] && arr[2] != ' '))
    {
      return true;
    }
    return false;
  }

  void drawcondition()
  {
    system("CLS");
    char arr1[9] = {'X', 'O', 'X', 'O', 'X', 'X', 'O', 'X', 'O'};
    cout << endl
         << MAGENTA << "   -----//// ! Draw Condition ! ////-----  " << RESET<<endl;

    print(arr1);

    cout << RED << "  --> Here NO one is winning because there is no three in line " << endl
         << endl
         << "  --> In this case no one can win the game so you can restart the game " << endl
         << "      If you want to read Game rule's again then you can reset the game" << RESET << endl
         << endl;
    cout << "  -->> Press any key to continue ............" << endl;
    getch();
  }

  void winningcondition()
  {
    char arr1[9] = {' ', 'O', 'X', 'O', 'X', 'O', 'X', ' ', 'O'};
    cout << endl
         << GREEN << "   -----//// ! Winning Condition ! ////-----  " << RESET << endl;

    print(arr1);

    cout << RED << "  --> Here X is winning because it has three in line " << endl
         << endl
         << "  --> It's not complusory to get diagonally three in line " << endl
         << "      you may get it row wise or column wise three in line " << RESET << endl
         << endl;
    cout << "  -->> Press any key to continue ............" << endl;
  }

public:
  void getinput()
  {
    player1.second.second = 4;
    player2.second.second = 4;
    system("CLS");
    cout << endl
         << MAGENTA << "Player1 Enter your Name : - " << endl;
    cin >> player1.first;
    cout << endl
         << MAGENTA << "Player2 Enter your Name : - " << endl;
    cin >> player2.first;
    cout << endl
         << GREEN << player1.first << RESET << " Enter What you want 'X' Or 'O' ! " << endl
         << "If you entered wrong choise then you get default 'X' || " << endl;
    cin >> flag;
    if ((flag != 'x' && flag != 'X') && (flag != 'o' && flag != 'O'))
    {
      flag = 'X';
      player1.second.first = flag;
      player2.second.first = 'O';
    }
    else if (flag >= 'a' && flag <= 'z')
    {
      flag = flag - 'a' + 'A';
      player1.second.first = flag;
      flag == 'X' ? player2.second.first = 'O' : player2.second.first = 'X';
    }
    system("CLS");
  }

  void displayName()
  {
    cout << "    " << player1.first << " is ";
    player1.second.first == 'X' ? cout << YELLOW << player1.second.first << RESET << "  ||  " : cout << GREEN << player1.second.first << RESET << "  ||  ";

    cout << player2.first << " is ";
    player2.second.first == 'X' ? cout << YELLOW << player2.second.first << RESET << endl
                                       << endl
                                : cout << GREEN << player2.second.first << RESET << endl
                                       << endl;
  }
  void Gamerule()
  {
    char array[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    system("CLS");
    cout << endl
         << endl
         << RED << "    ///-------!! GAME RULE'S !!-------///   " << RESET << endl
         << endl;
    print(array);
    cout << RED << "--> " << RESET << BLUE << "This Game is played by Only two player's " << endl
         << "    Player 1 can chose what he/she want either " << YELLOW << "'X'" << RESET << BLUE << " or " << GREEN << "'O'" << RESET << endl
         << endl;
    cout << RED << "--> " << RESET << BLUE << "IF player 1 chose " << YELLOW << "'X'" << BLUE << " Then Player 2 get " << GREEN << "'O'" << RESET << endl
         << BLUE << "    IF player 1 chose " << GREEN << "'O'" << BLUE << " Then Player 2 get " << YELLOW << "'X'" << RESET << endl
         << endl;

    cout << RED << "--> " << RESET << BLUE << "AS you can see Each block is mapped with number " << endl
         << "    you can chose one number at a time in alternate order " << RESET << endl
         << endl;
    cout << RED << "--> " << RESET << BLUE << "your chose number block is filled with your choise symbol " << RESET << endl
         << endl;
    cout << "-->> Press any key to continue........... " << endl
         << endl;
    getch();
    system("CLS");
    winningcondition();
    getch();
    drawcondition();
  }

  int startgame()
  {
    int cnt = 0;
    int validmove = 9;
    bool playerswap = true;
    while (validmove)
    {
      int num = 0;
      print(arr);
      if (playerswap)
      {

        flag == 'X' ? cout << YELLOW << player1.first << " Enter you number :- " << RESET << endl : cout << GREEN << player1.first << " Enter you number :- " << RESET << endl;
        cin >> num;
        if ((num > 0 && num < 10) && (arr[num - 1] == ' '))
        {

          arr[num - 1] = flag;
          player1.second.second--;
          flag == 'X' ? flag = 'O' : flag = 'X';
          cnt++;
          validmove--;
          playerswap = false;
        }
        else
        {
          player1.second.first == 'X' ? cout << YELLOW << player1.first << " Enter valid number :- " << RESET << endl : cout << GREEN << player1.first << " Enter valid number :- " << RESET << endl;
          getch();
          system("CLS");
          continue;
        }
      }
      else
      {
        player2.second.first == 'X' ? cout << YELLOW << player2.first << " Enter you number :- " << RESET << endl : cout << GREEN << player2.first << " Enter you number :- " << RESET << endl;
        cin >> num;
        if ((num >= 1 && num <= 10) && (arr[num - 1] == ' '))
        {
          arr[num - 1] = flag;
          flag == 'X' ? flag = 'O' : flag = 'X';
          player2.second.second--;
          validmove--;
          playerswap = true;
        }
        else
        {
          player2.second.first == 'X' ? cout << YELLOW << player2.first << " Enter valid number :- " << RESET << endl : cout << GREEN << player2.first << " Enter valid number :- " << RESET << endl;
          getch();
        }
      }
      if ((cnt > 2 && iswinning()))
      {
        return 0;
      }
      else if (player1.second.second == 0 && player2.second.second == 0)
      {
        return 1;
      }
      system("CLS");
    }

    return -1;
  }

  void print()
  {
    print(arr);
  }
  void winner()
  {
    if (flag != player1.second.first)
    {
      cout << GREEN << " --//--//-- Congratulation " << player1.first << " You Win The Game --//--//-- " << RESET << endl;
    }
    else
    {
      cout << GREEN << " --//--//-- Congratulation " << player2.first << " You Win The Game --//--//-- " << RESET << endl;
    };
  }

  void restart()
  {
    for (int i = 0; i < size; i++)
    {
      arr[i] = ' ';
    }

    player1.second.second = 4;
    player2.second.second = 4;
    flag = player1.second.first;
  }
};

int main()
{

  Tictactoe obj;
  char checkNeed = 'R';
  bool play = true;

  while (1)
  {
    system("CLS");

    if (checkNeed == 'R')
    {
      play=true;
      obj.restart();
      obj.Gamerule();
      obj.getinput();
    }

    if (play || checkNeed == 'Y')
    {
      obj.restart();
      if (obj.startgame())
      {
        system("CLS");
        obj.print();
        obj.displayName();
        cout << RED << " --!!---// THIS IS A CLEAR DRAW //---!!--  " << RESET << endl;
        cout << endl
             << endl
             << " Press 'r' or 'R' for RESET the game : - " << endl
             << " Press 'y' or 'Y' for Play Again :- " << endl
             << " Press 'e' or 'E' for Exit : - " << endl;
        cin >> checkNeed;
      }
      else
      {
        system("CLS");
        obj.print();
        obj.displayName();
        obj.winner();
        cout << endl
             << endl
             << " Press 'r' or 'R' for RESET the game : - " << endl
             << " Press 'y' or 'Y' for Play Again :- " << endl
             << " Press 'e' or 'E' for Exit : - " << endl;
        cin >> checkNeed;
      }
    }
    if (checkNeed >= 'a' && checkNeed <= 'z')
    {
      checkNeed = checkNeed - 'a' + 'A';
    }
    if (checkNeed != 'R' && checkNeed != 'E' && checkNeed != 'Y')
    {
      play = false;
      system("CLS");
      cout << CYAN << " Please Enter the valid choise : -  " << RESET;
      cout << endl
             << endl
             << " Press 'r' or 'R' for RESET the game : - " << endl
             << " Press 'y' or 'Y' for Play Again :- " << endl
             << " Press 'e' or 'E' for Exit : - " << endl;
      cin >> checkNeed;
      continue;
    }
    if (checkNeed == 'E')
    {
      system("CLS");
      obj.print();
      cout << endl
           << endl
           << RED << "  -----!!!---!! Thankyou For Playing ! hope you enjoy the Game !!---!!!-----" << RESET << endl <<endl;
      exit(0);
    }
  }
  return 0;
}