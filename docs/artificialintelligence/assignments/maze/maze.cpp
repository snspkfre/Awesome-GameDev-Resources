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
    up = true, down = true, left = true, right = true, visited = false;
  }
  int x, y;
  bool up, down, left, right, visited;
};

vector<Cell*> findNeighbors(Cell** arr, int x, int y, int sizeX, int sizeY);

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

  Cell** arr = new Cell*[x];
  for(int i = 0; i < x; i++)
  {
    arr[i] = new Cell[y];
  }

  for(int i = 0; i < x; i++)
  {
    for(int j = 0; j < y; j++)
    {
      arr[i][j] = Cell(i, j);
    }
  }


  stack<Cell*> st;
  st.push(&arr[0][0]);
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
      Cell *selectedNeighbor = neighbors[0];
      if(neighbors.size() != 1)
      {
        selectedNeighbor = neighbors[Random[s++] % neighbors.size()];
        if(s >= RandomLength) s = 0;
      }

      if(selectedNeighbor->x > st.top()->x)
      {
        st.top()->right = false;
        selectedNeighbor->left = false;
      }
      else if(selectedNeighbor->x < st.top()->x)
      {
        st.top()->left = false;
        selectedNeighbor->right = false;
      }
      else if(selectedNeighbor->y > st.top()->y)
      {
        st.top()->down = false;
        selectedNeighbor->up = false;
      }
      else if(selectedNeighbor->y < st.top()->y)
      {
        st.top()->up = false;
        selectedNeighbor->down = false;
      }
      st.push(selectedNeighbor);
    }
  }

  //maze top
  for(int i = 0; i < x; i++)
  {
    cout << " ";
    if(arr[0][i].up) cout << "_";
    else cout << " ";
  }

  cout << "  " << endl;

  //maze core
  for(int i = 0; i < y; i++)
  {
    for(int j = 0; j < x; j++)
    {
      if(arr[j][i].left) cout << "|";
      else cout << " ";
      if(arr[j][i].down) cout << "_";
      else cout << " ";
    }
    cout << "| " << endl;
  }

  //cleaning to avoid data leaks
  for(int i = 0; i < x; i++)
  {
    delete[] arr[i];
  }
  delete[] arr;

  return 0;
}

vector<Cell*> findNeighbors(Cell** arr, int x, int y, int sizeX, int sizeY)
{
  vector<Cell*> neighbors;
  if(y != 0 && !arr[y-1][x].visited)
    neighbors.push_back(&arr[y-1][x]);

  if(x != sizeX - 1 && !arr[y][x+1].visited)
    neighbors.push_back(&arr[y][x+1]);

  if(y != sizeY - 1 && !arr[y+1][x].visited)
    neighbors.push_back(&arr[y+1][x]);

  if(x != 0 && !arr[y][x-1].visited)
    neighbors.push_back(&arr[y][x-1]);

  return neighbors;
}