#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct Cell
{
  Cell() = default;
  Cell(const int X, const int Y)
  {
    x = X;
    y = Y;
    up = true, left = true, visited = false;
  }
  int x, y;
  bool up, left, visited;
};

vector<Cell*> findNeighbors(const vector<vector<Cell*>>& arr, int x, int y, int sizeX, int sizeY);

int main()
{
  int x, y, s;
  constexpr int RandomLength = 100;
  int Random[RandomLength] =
  {
    72, 99, 56, 34, 43, 62, 31,  4, 70, 22,  6, 65, 96, 71, 29,  9, 98, 41, 90,  7, 30,  3, 97, 49, 63,
    88, 47, 82, 91, 54, 74,  2, 86, 14, 58, 35, 89, 11, 10, 60, 28, 21, 52, 50, 55, 69, 76, 94, 23, 66,
    15, 57, 44, 18, 67,  5, 24, 33, 77, 53, 51, 59, 20, 42, 80, 61,  1,  0, 38, 64, 45, 92, 46, 79, 93,
    95, 37, 40, 83, 13, 12, 78, 75, 73, 84, 81,  8, 32, 27, 19, 87, 85, 16, 25, 17, 68, 26, 39, 48, 36
  };

  //Fill Nodes
  cin >> x >> y >> s;
  vector<vector<Cell*>> arr(y, vector<Cell*>(x));

  for(int i = 0; i < y; ++i)
  {
    for(int j = 0; j < x; j++)
    {
      arr[i][j] = new Cell(j, i);
    }
  }


  stack<Cell*> st;
  st.push(arr[0][0]);

  while(!st.empty())
  {
    st.top()->visited = true;
    vector<Cell*> neighbors = findNeighbors(arr, st.top()->x, st.top()->y, x, y);
    if(neighbors.empty())
    {
      st.pop();
    }
    else
    {
      Cell *selectedNeighbor;
      if(neighbors.size() == 1)
        selectedNeighbor = neighbors.front();
      else
      {
        selectedNeighbor = neighbors[(Random[s++]) % (int)neighbors.size()];
        if(s >= RandomLength) s = 0;
      }

      if(selectedNeighbor->x > st.top()->x)
      {
        selectedNeighbor->left = false;
      }
      else if(selectedNeighbor->x < st.top()->x)
      {
        st.top()->left = false;
      }
      else if(selectedNeighbor->y > st.top()->y)
      {
        selectedNeighbor->up = false;
      }
      else if(selectedNeighbor->y < st.top()->y)
      {
        st.top()->up = false;
      }
      st.push(selectedNeighbor);
    }
  }

  //maze top
  for(int i = 0; i < x; ++i)
  {
    cout << " ";
    if(arr[0][i]->up) cout << "_";
    else cout << " ";
  }

  cout << "  " << endl;

  //maze core
  for(int i = 0; i < y; ++i)
  {
    for(int j = 0; j < x; j++)
    {
      if(arr[i][j]->left) cout << "|";
      else cout << " ";
      if(i == y - 1 || arr[i+1][j]->up) cout << "_";
      else cout << " ";
    }
    cout << "| " << endl;
  }

  //cleaning to avoid data leaks
  for (int i = 0; i < y; ++i)
  {
    for (int j = 0; j < x; j++)
    {
      delete arr[i][j];
    }
  }

  return 0;
}

vector<Cell*> findNeighbors(const vector<vector<Cell*>>& arr, const int x, const int y, const int sizeX, const int sizeY)
{
  vector<Cell*> neighbors;
  if(y - 1 >= 0 && !arr[y-1][x]->visited) // up
    neighbors.push_back(arr[y-1][x]);

  if(x + 1 < sizeX && !arr[y][x+1]->visited) // right
    neighbors.push_back(arr[y][x+1]);

  if(y + 1 < sizeY && !arr[y+1][x]->visited) // down
    neighbors.push_back(arr[y+1][x]);

  if(x - 1 >= 0 && !arr[y][x-1]->visited) // left
    neighbors.push_back(arr[y][x-1]);

  return neighbors;
}