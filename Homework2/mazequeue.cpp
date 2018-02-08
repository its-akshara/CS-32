// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
#include<string>
#include<iostream>
using namespace std;
#include<queue>
class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    queue<Coord> coordStack;
    coordStack.push(Coord(sr,sc));
    
    maze[sr][sc] = 'o';
    while (!coordStack.empty()) {
        Coord current = coordStack.front();
        coordStack.pop();
        int c = current.c(), r=current.r();
        
        if(r == er && c == ec)
            return true;
        //North
        if((r>0) && (maze[r-1][c] == '.'))
        {
            coordStack.push(Coord(r-1,c));
            maze[r-1][c]='o';
        }
        //East
        if(((c+1)<nCols) && (maze[r][c+1] == '.'))
        {
            coordStack.push(Coord(r,c+1));
            maze[r][c+1]='o';
        }
        //South
        if(((r+1)<nRows) && (maze[r+1][c] == '.'))
        {
            coordStack.push(Coord(r+1,c));
            maze[r+1][c]='o';
        }
        //West
        if((c>0) && (maze[r][c-1] == '.'))
        {
            coordStack.push(Coord(r,c-1));
            maze[r][c-1]='o';
        }
        
    }
    return false;
}
int main()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X........X",
        "XX.X.XXXXX",
        "X..X.X...X",
        "X..X...X.X",
        "XXXX.XXX.X",
        "X.X....XXX",
        "X..XX.XX.X",
        "X...X....X",
        "XXXXXXXXXX"
    };
    
    if (pathExists(maze, 10,10, 6,4, 1,1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}
