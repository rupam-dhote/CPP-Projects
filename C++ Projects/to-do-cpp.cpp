#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
#include <conio.h>
#include <filesystem>
#include <fstream>
#include <cstdlib>

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[30m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"
using namespace std;
namespace fs = std::filesystem;

// task user data type
struct Task
{
      string data = "";
      bool done = false;
};

// function to create folder
string getDesktopPath()
{
      char *user = getenv("USERPROFILE");

      if (user == nullptr)
      {
            return "C:\\Users\\Public\\Desktop"; // fallback
      }

      return string(user) + "\\Desktop";
}

// function to get file path
string getFilePath()
{
      string desktop = getDesktopPath();
      string folder = desktop + "\\toDo_List";
      string file = folder + "\\toDo_Tasks.txt";

      // if folder not exist then creating it;
      if (!fs::exists(folder))
      {
            bool ok = fs::create_directory(folder);
            if (ok)
            {
                  ofstream f(file);
                  f.close();
            }
      }
      // then created file
      else if (!fs::exists(file))
      {
            ofstream f(file);
            f.close();
      }

      return file;
}

void saveTask(const vector<Task> &task)
{
      string path = getFilePath();
      ofstream file(path);

      for (const auto &i : task)
      {
            file << i.done << "|" << i.data << endl;
      }

      file.close();
}

void loadTask(vector<Task> &task)
{
      string path = getFilePath();
      ifstream file(path);
      if (!file.is_open())
      {
            cout << "here" << endl;
            return;
      }

      task.clear();
      string line;

      while (getline(file, line))
      {

            int pos = line.find('|');
            if (pos == string::npos)
            {
                  continue;
            }
            bool done = (line.substr(0, pos) == "1");
            string data = line.substr(pos + 1);

            task.push_back({data, done});
      }

      file.close();
}

void waitForKey()
{
      // clear any pending special key part
      while (_kbhit())
            _getch();
      _getch(); // now really wait
}
void printLeft(int n)
{
      for (int i = 0; i < 62 - n; i++)
      {
            cout << " ";
      }
      cout << MAGENTA << "|" << RESET;
}

// printing Task based on selected value--------
void printTask(vector<Task> &task, int isSelected)
{
      cout << MAGENTA << "|                                                                      |" << RESET;
      if (isSelected == -1)
      {
            cout << endl
                 << MAGENTA << "|" << RESET << RED << "------------------------ No Task In Your List ------------------------" << RESET << MAGENTA << "|" << RESET << endl;
            cout << MAGENTA << "|                                                                      |" << endl;
            cout << "|______________________________________________________________________|" << RESET << endl
                 << endl;
            return;
      }
      int size = task.size();
      cout << endl
           << MAGENTA << "|" << RESET << CYAN << "----------------------------- YOUR TASKS -----------------------------" << RESET << MAGENTA << "|" << RESET << endl;
      for (int i = size - 1; i >= 0; i--)
      {
            if (isSelected == i)
            {
                  cout << MAGENTA << "| " << RESET << GREEN << "->" << RESET << " ";
            }
            else
            {
                  cout << MAGENTA << "| " << RESET << "   ";
            }

            if (task[i].done)
            {
                  cout << YELLOW << "[" << RESET << RED << "X" << RESET << YELLOW << "]" << RESET << " ";
            }
            else
            {
                  cout << YELLOW << "[ ]" << RESET << " ";
            }

            isSelected == i ? cout << GREEN << task[i].data << RESET : cout << CYAN << task[i].data << RESET;
            int s = task[i].data.length();
            printLeft(s);
            cout << endl;
      }
      cout << MAGENTA << "|                                                                      |" << endl;
      cout << "|______________________________________________________________________|" << RESET << endl
           << endl;
}

void showRule()
{
      cout << MAGENTA << " ______________________________________________________________________" << RESET;
      cout << endl
           << MAGENTA << "|                                                                      |" << RESET;
      cout << endl
           << MAGENTA << "|" << RESET << BLUE << "----------------------------- TO-DO LIST -----------------------------" << RESET << MAGENTA << "|" << endl;
      cout << MAGENTA << "| ENTER, A = Add || D = Delete || C = complete || E = Edit || Q = Quit |" << RESET;
      cout << endl
           << MAGENTA << "|" << RESET << BLUE << "----------------------------------------------------------------------" << RESET << MAGENTA << "|" << endl;
}

void addTask(vector<Task> &task, int index = -1)
{
      string addTask = "";
      cout << endl
           << MAGENTA << "Enter your task ...." << RESET << endl;

      getline(cin, addTask);
      while (addTask == "")
      {
            cout << RED << "Please enter a valid task.." << RESET << endl;
            cout
                << MAGENTA << "Enter your task ...." << RESET << endl;
            getline(cin, addTask);
      }

      if (index != -1)
      {
            task[index].data = addTask;
            cout << GREEN << "Task Edited seccessfully !" << RESET << endl;
      }
      else
      {
            task.push_back({addTask, false});
            cout << GREEN << "Task added seccessfully !" << RESET << endl;
      }
      cout << "Press any key to continue...";
      waitForKey();
}

void deleteTask(vector<Task> &task, int index)
{
      task.erase(task.begin() + index);
      cout << GREEN << "Task deleted successfully !" << RESET << endl;
      cout << "Press any key to continue...";
      waitForKey();
}

void completeTask(vector<Task> &task, int index)
{
      task[index].done = !task[index].done;
}

void editTask(vector<Task> &task, int index)
{
      if (index == -1)
      {
            cout << RED << "There Is No Task In List, Add task first" << RESET << endl;
            return;
      }
      addTask(task, index);
}

int main()
{
      vector<Task> task;
      loadTask(task);
      int isSelected = -1;
      if (!task.empty())
      {
            isSelected = task.size() - 1;
      }
      while (true)
      {
            system("CLS");
            showRule();
            printTask(task, isSelected);
            if (!task.empty() && isSelected == -1)
                  isSelected = task.size() - 1;

            int get = _getch();
            if (get == 224)
            {
                  get = _getch();
                  switch (get)
                  {
                  case 72: // UP arrow
                        if (!task.empty())
                        {
                              if (isSelected < task.size() - 1)
                                    isSelected++;
                              else
                                    isSelected = 0;
                        } // circular}
                        break;

                  case 80: // DOWN arrow
                        if (!task.empty())
                        {
                              if (isSelected > 0)
                                    isSelected--;
                              else
                                    isSelected = task.size() - 1;
                        } // circular
                        break;
                  default:
                        break;
                  }
            }
            else
            {
                  char key = (char)get;
                  key = tolower(key);
                  switch (key)
                  {
                  case 'a':
                        addTask(task);
                        isSelected = task.size() - 1;
                        break;
                  case 'd':
                        if (isSelected >= 0 && !task.empty())
                        {
                              deleteTask(task, isSelected);
                              if (task.empty())
                                    isSelected = -1;
                              else if (isSelected >= task.size())
                                    isSelected = task.size() - 1;
                        }
                        break;

                  case 'c':
                        if (isSelected >= 0 && !task.empty())
                        {
                              completeTask(task, isSelected);
                        }
                        break;

                  case 'q':
                        saveTask(task);
                        cout << GREEN << "                        All tasks saved !";
                        cout << endl
                             << "----------------- Thank you For using this To Do App ------------------" << RESET << endl
                             << endl;
                        exit(0);
                        break;
                  case 'e':
                        if (isSelected >= 0 && !task.empty())
                        {
                              editTask(task, isSelected);
                        }
                        break;

                  default:

                        cout << endl
                             << RED << "Please Enter A valid Key !" << RESET << endl;
                        cout << "Press any key to continue....";
                        waitForKey();
                        break;
                  }
            }
      }

      return 0;
}
