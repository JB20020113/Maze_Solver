#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Maze {
private:
    char grid[20][20];
    bool visited[20][20];
    bool solvable;
    int startR, startC;

public:
    Maze(ifstream &fin) {
        solvable = false;

        // Read 20 lines for the maze
        for (int r = 0; r < 20; r++) {
            string line;
            getline(fin, line);

            for (int c = 0; c < 20; c++) {
                grid[r][c] = line[c];
                visited[r][c] = false;

                if (grid[r][c] == 'S') {
                    startR = r;
                    startC = c;
                }
            }
        }

        // Skip blank line between mazes (if present)
        fin.ignore(1000, '\n');

        solvable = dfs(startR, startC);
    }

    bool dfs(int r, int c) {
        // Out of bounds
        if (r < 0 || r >= 20 || c < 0 || c >= 20) return false;

        // Wall or visited
        if (grid[r][c] == '#' || visited[r][c]) return false;

        // Found the end
        if (grid[r][c] == 'E') return true;

        visited[r][c] = true;

        // Try moving in all 4 directions
        return dfs(r+1, c) ||
               dfs(r-1, c) ||
               dfs(r, c+1) ||
               dfs(r, c-1);
    }

    string toString() {
        return solvable ? "Maze: YES" : "Maze: NO";
    }
};

int main() {
    ifstream fin("maze.dat");
    if (!fin) {
        cout << "Cannot open maze.dat\n";
        return 0;
    }

    // If the file contains multiple mazes, process them all
    while (!fin.eof()) {
        Maze m(fin);
        cout << m.toString() << endl;
    }

    fin.close();
    return 0;
}
