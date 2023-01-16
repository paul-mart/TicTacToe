/*****************************************************
Paul Martin
TicTacToe Project
Last updated: 1/16/23
*****************************************************/

#include <iostream>
using namespace std;

class TicTacToe
{
public:
    void displayBoard(); //displays playing board

    char winner(); //checks for winner
    bool placeMarker(int slot); //places marker

    void swapPlayerAndMarker(); //swaps player and marker

    void game(); //main game function

private:
    char board[3][3] = { {'1', '2','3'}, {'4','5','6'}, {'7','8','9'} }; //used to update board for live display
    char currentMarker = 'A'; //marker default A but uses as X or O
    int currentPlayer; //whos playing
    int slot; //slot


};

char TicTacToe::winner() //checks for winner
{
    for (int i = 0; i < 3; i++)
    {
        //row
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return currentPlayer; //goes through loop with i and checks possible win

        //colum
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return currentPlayer; //goes through loop with i and checks possible win


    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) { return currentPlayer; } //diagonal win
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) { return currentPlayer; } //other diagonal win

    return 0;
}
void TicTacToe::swapPlayerAndMarker()
{
    if (currentMarker == 'X') currentMarker = 'O'; //swap x to o
    else currentMarker = 'X'; //else if already o, make X

    if (currentPlayer == 1) currentPlayer = 2; //swap 1 to 2
    else currentPlayer = 1; //else if already 2, make 1
}
void TicTacToe::game() //main game function
{
    char marker_player1; //
    cout << "Player one, choose your marker; X or O \n";
    cin >> marker_player1;

    currentPlayer = 1;
    currentMarker = marker_player1;

    displayBoard(); //displays board

    int player_won; //used for win message

    for (int i = 0; i < 9; i++) //main game, where slots are taken and placed, etc
    {
        if (currentPlayer == 1) //user
        {
            cout << "It's your your turn. Enter your slot. \n"; //prompt user to enter slot
            cin >> slot; //read in slot
        }
        else if (currentPlayer == 2) //"ai" or computer turn
        {
            if (board[0][0] && board[0][1] == 'X' && board[0][2] == '3') { slot = 3; } //causing infinite loop because even tho 3rd slot is taken already, it keeps telling it to take it 
            else if (board[1][0] && board[1][1] == 'X' && board[1][2] == '6') { slot = 6; }

            else {
                srand((unsigned)time(0)); //random slot
                slot = (rand() % 9);
            }
        }
        else
        {
            cout << "Error, \n"; //safety error message
        }


        if (currentPlayer == 1)
        {

            while (slot < 1 || slot > 9) //loop while go until a valid slot number is entered (1-9)
            {
                cout << "Slot is nonexistent. Please enter a valid slot number (1-9) \n"; 
                cin >> slot; //reads in slot
            }

        }
        else
        {
            i--; //returns back a play
        }

        if (!placeMarker(slot)) //if this condition is not true
        {
            if (currentPlayer == 1) //if its a user, give error message so they can place a marker again
            {
                cout << "That slot is occupied! Try another slot! \n";
            }
            i--;
            slot++; //increment slot to find new one
            continue;
        }
        cout << '\n'; //newline to seperate new board
        displayBoard(); //dispays board

        player_won = winner(); //check for winner

        if (player_won == 1) { cout << "Player 1 Won! Congratulations!"; break; } //you win
        if (player_won == 2) { cout << "The AI Won! Better luck next time!"; break; } //computer wins


        swapPlayerAndMarker(); //swaps player and marker for a new turn after someone goes


    }

    if (player_won == 0) { cout << "It was a tie game :("; } //tie
}



void TicTacToe::displayBoard() //displays board, which can update since it uses a char array which is a data member
{
    cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << " ----------\n";
    cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << " ----------\n";
    cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
}

bool TicTacToe::placeMarker(int slot) //function for placing market, takes slot as parameter
{
    int row = slot / 3; //remained of row, uses this later if nt 3, 6, or 9
    int colum;

    if (slot % 3 == 0) //if slot is 3, 6, or 9
    {
        row = (slot / 3) - 1; //row is -1 due to rows starting at 0 (0,1,2)
        colum = 2; //if slot is 3,6, or 9 then the colum is automatically 2 as seen in the board and char array
    }

    else colum = (slot % 3) - 1; //if slot isnt 3,6, or 9, uses algorith to place colum

    //places marker after figuring out row and colum based off of slot int
    if (board[row][colum] != 'X' && board[row][colum] != 'O') //if it isnt taken, its ok to place
    {
        return board[row][colum] = currentMarker; //place market at row and colum of board
    }
    else return false; //return false if cant place

}


int main()
{
    TicTacToe play; //object play
    play.game(); //call to game function on object
}
