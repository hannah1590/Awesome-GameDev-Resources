#include <iostream>
#include <vector>

using namespace std;



int main(){
    int columns;
    int lines;
    int turns;

    cin >> columns >> lines >> turns;

    vector<vector<bool>> cells;
    vector<vector<bool>> newCells;

    for(int i = 0; i < lines; i++)
    {
        //cells[i] = new char[columns];
        //newCells[i] = new char[columns];
        vector<bool> temp;
        char val;
        for(int j = 0; j < columns; j++)
        {
            cin >> val;
            if(val == '#')
            {
                temp.push_back(true);
            }
            else
            {
                temp.push_back(false);
            }
        }
        cells.push_back(temp);
    }

    for(int t = 0; t < turns; t++) { // continues until all turns are done
        for (int i = 0; i < lines; i++) { // goes through rows
            for (int j = 0; j < columns; j++) { // goes through columns
                int count = 0;

                // cells directly next to each other
                if (i + 1 < lines && cells[i + 1][j])
                    count++;
                if (i - 1 >= 0 && cells[i - 1][j])
                    count++;
                if (j + 1 < columns && cells[i][j + 1])
                    count++;
                if (j - 1 >= 0 && cells[i][j - 1])
                    count++;

                // cells diagonal from each other
                if (i + 1 < lines && j + 1 < columns && cells[i + 1][j + 1])
                    count++;
                if (i + 1 < lines && j - 1 >= 0 && cells[i + 1][j - 1])
                    count++;
                if (i - 1 >= 0 && j + 1 < columns && cells[i - 1][j + 1])
                    count++;
                if (i - 1 >= 0 && j - 1 >= 0 && cells[i - 1][j - 1])
                    count++;

                // cells next to each other with the continuous map
                if (j + 1 >= columns && cells[i][0])
                    count++;
                if (j - 1 < 0 && cells[i][columns - 1])
                    count++;
                if (i + 1 >= lines && cells[0][j])
                    count++;
                if (i - 1 < 0 && cells[lines - 1][j])
                    count++;

                // diagonally with continuous map off right/bottom
                if (j + 1 >= columns && i + 1 < lines && cells[i + 1][0])
                    count++;
                if (j + 1 >= columns && i - 1 >= 0 && cells[i - 1][0])
                    count++;
                if (i + 1 >= lines && j + 1 < columns && cells[0][j + 1])
                    count++;
                if (i + 1 >= lines && j - 1 >= 0 && cells[0][j - 1])
                    count++;

                // diagonally with continuous map off left/top
                if (j - 1 < 0 && i + 1 < lines && cells[i + 1][columns - 1])
                    count++;
                if (j - 1 < 0 && i - 1 >= 0 && cells[i - 1][columns - 1])
                    count++;
                if (i - 1 < 0 && j + 1 < columns && cells[lines - 1][j + 1])
                    count++;
                if (i - 1 < 0 && j - 1 >= 0 && cells[lines - 1][j - 1])
                    count++;

                // diagonally with continuous map off diagonals
                if (j + 1 >= columns && i + 1 >= lines && cells[0][0])
                    count++;
                if (j + 1 >= columns && i - 1 < 0 && cells[lines - 1][0])
                    count++;
                if (j - 1 < 0 && i + 1 >= lines && cells[0][columns - 1])
                    count++;
                if (j - 1 < 0 && i - 1 < 0 && cells[lines - 1][columns - 1])
                    count++;

                //newCells[i][j] = cells[i][j]; // assigns holder cells current cell value
                if (count < 2 || count > 3)
                    newCells[i][j] = false; // changes holder cell value so initial cell value is still intact
                if (count == 3 || (count == 2 && cells[i][j]))
                    newCells[i][j] = true; // changes holder cell value so initial cell value is still intact
            }
        }

        for(int i = 0; i < lines; i++)
        {
            for(int j = 0; j < columns; j++)
            {
                cells[i][j] = newCells[i][j]; // replaces cells with new cell layout
            }
        }
    }

    for(int i = 0; i < lines; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            cout << cells[i][j];
        }
        cout << "\n";
    }

    //deletes memory
    //for(int i = 0; i < lines; i++)
    //{
    //    delete[] cells[i];
    //    delete[] newCells[i];
    //}
    //delete[] cells;
    //delete[] newCells;

    return 0;
}