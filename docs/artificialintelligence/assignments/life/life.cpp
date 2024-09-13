#include <iomanip>;
#include <iostream>
#include <string>;

using namespace std;

int countNeighbors(bool* arr, int x, int y, int sizeX, int sizeY);

int main()
{
  int x, y, s;
  cin >> x >> y >> s;
  cin.ignore();
  bool* arr;
  arr = new bool[y*x];
  
  // access by showing arr[x_value * x + y]
  // arr[9 * x + 10] = 87; for y = 9, x = 10
  for (int i = 0; i < y; i++)
  {
      string str;
      getline(cin, str);
      const char* input = str.c_str();
      for (int j = 0; j < x; j++)
      {
        arr[i * x + j] = input[j] == '#';
      }
  }

  for (int k = 0; k < s; k++)
  {
    bool* next;
    next = new bool[y * x];
    for (int i = 0; i < y; i++) {
      for (int j = 0; j < x; j++) {
        if (!arr[i * x + j])
        {
          next[i * x + j] = countNeighbors(arr, i, j, x, y) == 3;
        }
        else
        {
          if (countNeighbors(arr, i, j, x, y) < 2 || countNeighbors(arr, i, j, x, y) > 3)
            next[i * x + j] = false;
          else
            next[i * x + j] = true;
        }
      }
    }

    arr = next;
    next = nullptr;
  }
  //system("cls");

  for (int i = 0; i < y; i++)
  {
      for (int j = 0; j < x; j++)
      {
          char out = arr[i * x + j] ? '#' : '.';
          cout << out;
      }
      cout << "\n";
  }
}

int countNeighbors(bool* arr, int x, int y, int sizeX, int sizeY) {
    int down = (y - 1) < 0 ? y-1 + sizeY : (y - 1);
    int up = (y + 1) % sizeY;
    int left = (x - 1) < 0 ? x - 1 + sizeX : (x - 1);
    int right = (x + 1) % sizeX;

    int sum = 0;
    sum += arr[left * sizeX + up];
    sum += arr[left * sizeX + y];
    sum += arr[right * sizeX + y];
    sum += arr[right * sizeX + up];
    sum += arr[x * sizeX + up];
    sum += arr[left * sizeX + down];
    sum += arr[x * sizeX + down];
    sum += arr[right * sizeX + down];
    return sum;
}