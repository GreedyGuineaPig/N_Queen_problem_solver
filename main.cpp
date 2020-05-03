#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;



class Board{
public:
    int num;
    vector<vector<int> > board;

    Board(int cell){
        num = cell;
        board.assign(num, vector<int>(num, 0));
        // for(int i = 0; i < num; i++){
        //     for(int j = 0; j < num; j++){
        //         cout << board[i][j];
        //     }
        //     cout << endl;
        // }
    }

    bool Puttable(int r, int c){
        // cout << endl << "Puttable enter" << endl;
        if(board[r][c] != 0) return false;
        int acc = 0;

        // cout << "&1";

        // cout << "num: " << num << endl;
        for(int i = 0; i < num; i++){
            // // cout << "int i: " << i << endl;
            // // cout << "board " << r << " " << i
            //  << "= " << board[r][i] << endl;
            acc = acc + board[r][i];
        }
        // cout << "acc: " << acc << endl;
        if(acc > 0) return false;
        acc = 0;

        // cout << "2";

        for(int i = 0; i < num; i++){
            acc = acc + board[i][c];
        }
        if(acc > 0) return false;
        acc = 0;

        // cout << "3";

        int LtoR = r - c;
        for(int i = 0; i < num; i++){
            for(int j = 0; j < num; j++){
                if(i - j == LtoR) acc = acc + board[i][j];
            }
        }
        if(acc > 0) return false;

        // cout << "4";

        acc = 0;
        int RtoL = r + c;
        for(int i = 0; i < num; i++){
            for(int j = 0; j < num; j++){
                if(i + j == RtoL) acc = acc + board[i][j];
            }
        }

        // cout << "5";

        if(acc > 0) return false;

        // cout << "6&" << endl;

        return true;
    }

    void put(int r, int c){
        board[r][c] = 1;
    }

    void unPut(int r, int c){
        board[r][c] = 0;
    }

    void Export(){
        ofstream writing_file("result.txt");
        cout << "writing..." << endl;
        char cell;

        for(int i = 0; i < num; i++){
            for(int j = 0; j < num; j++){
                if(board[i][j] == 0){
                    cell = '.';
                }else{
                    cell = 'O';
                }
                writing_file << cell;
            }
            writing_file << "\n";
        }
        cout << "Done!" << endl;
        writing_file << "\n\n\n\n";
        writing_file.close();
    }

    void print(){
        char cell;

        for(int i = 0; i < num; i++){
            for(int j = 0; j < num; j++){
                if(board[i][j] == 0){
                    cell = '.';
                }else{
                    cell = 'O';
                }
                cout << cell;
            }
            cout << endl;
        }
        cout << endl << endl;
    }


    void solve(int row){
        // cout << endl << endl << endl;
        // cout << "solve:" << row << endl;
        // cout << "c: ";
        vector<int> v;
        for(int c = 0; c < num; c++){
            // cout << c;
            if(Puttable(row,c)) v.push_back(c);
        }
        // cout << "v{";
        // for(int i = 0; i < v.size(); i++){
            // cout << v.at(i) << ", ";
        // }
        // cout << "}" << endl;

        int i;
        while(true){
            if(v.size() == 0) return;
            i = v.back();
            v.pop_back();
            put(row, i);
            // cout << "board[" << row << "][" << i << "]= " << board[row][i] << endl;
            if(row == num - 1){
                Export();
                // print();
                unPut(row, i);
            }else{
                solve(row + 1);
                unPut(row, i);
            }
        }
    }
};






int main(){
    cout << "type the number of Row & Col N*N, N=";
    int num;
    cin >> num;
    Board board(num);
    board.solve(0);
    cout << "Check out result.txt" << endl;
    return 0;
}

