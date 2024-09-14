#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

int countNeighbors(bool** arr, int x, int y, int sizeX, int sizeY);

int main()
{
  int x, y, s;
  cin >> x >> y >> s;
  cin.ignore();
  bool** arr;
  arr = new bool*[y];
  for(int i = 0; i < y; i++)
  {
    arr[i] = new bool[x];
  }
  
  // access by showing arr[x_value * x + y]
  // arr[9 * x + 10] = 87; for y = 9, x = 10
  for (int i = 0; i < y; i++)
  {
      string str;
      getline(cin, str);
      const char* input = str.c_str();
      for (int j = 0; j < x; j++)
      {
        arr[i][j] = input[j] == '#';
      }
  }

  for (int k = 0; k < s; k++)
  {
    bool** next;
    next = new bool*[y];
    for(int i = 0; i < y; i++)
    {
      next[i] = new bool[x];
    }

    for (int i = 0; i < y; i++) {
      for (int j = 0; j < x; j++) {
        if (!arr[i][j])
        {
          next[i][j] = countNeighbors(arr, j, i, x, y) == 3;
        }
        else
        {
          if (countNeighbors(arr, j, i, x, y) < 2 || countNeighbors(arr, j, i, x, y) > 3)
            next[i][j] = false;
          else
            next[i][j] = true;
        }
      }
    }

    arr = next;
    next = nullptr;
    delete[] next;
  }
  //system("cls");

  for (int i = 0; i < y; i++)
  {
      for (int j = 0; j < x; j++)
      {
        //testing thing
        //countNeighbors(arr, i, j, x, y);
          //cout << countNeighbors(arr, i, j, x, y) << " ";
          char outValue = arr[i][j] ? '#' : '.';
          cout << outValue;
      }
      cout << "\n";
  }
  arr = nullptr;
  delete[] arr;
}

int countNeighbors(bool** arr, int x, int y, int sizeX, int sizeY) {
  int down, up, left, right;

  if(y == 0) down = sizeY - 1;
  else down = y - 1;
  if(y == sizeY - 1) up = 0;
  else up = y + 1;
  if(x == 0) left = sizeX - 1;
  else left = x - 1;
  if(x == sizeX - 1) right = 0;
  else right = x + 1;

  int sum = 0;
  sum += arr[up][left] ? 1 : 0;
  sum += arr[up][x] ? 1 : 0;
  sum += arr[up][right] ? 1 : 0;
  sum += arr[y][left] ? 1 : 0;
  sum += arr[y][right] ? 1 : 0;
  sum += arr[down][left] ? 1 : 0;
  sum += arr[down][x] ? 1 : 0;
  sum += arr[down][right] ? 1 : 0;
  return sum;
}