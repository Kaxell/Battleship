/**
 * @file BattleshipGame.cpp
 *
 * @brief A Battleship game simulated in terminal. 
 * Implemented with OOP principles.    
 *
 * @author Ertugrul Akay
 */

#include <iostream>
#include <string>

using namespace std;

//CONSTANT VALUES
const int ROWS = 8;
const int COLUMNS = 8;
const char HIT = 'H';
const char MISS = 'M';
const char EMPTY = 'E';
const char SHIP = 'S';
const char NORTH = 'N';
const char SOUTH = 'S';
const char EAST = 'E';
const char WEST = 'W';
const int SHIPCOUNT = 5;

void EnterToContinue();

class Ship
{

private:
    int size;
    int hits;
    string type;

public:

    Ship(string type, int size)
    {
        this->size = size,
        this->type = type;
        this->hits = 0; //Initializing hits to 0
    }

    bool IsSunk()
    {
        return hits == size;
    }

    int GetSize()
    {
        return size;
    }

    string GetType()
    {
        return type;
    }

    void Hit()
    {
        hits++;
        if (hits > size)
        {
            hits = size;
        }
    }
};



class BattleShipSquare 
{

private:
    Ship *ship;
    bool isFired;
    
public:

    BattleShipSquare()
    {
        Reset();
    }

    void Reset() 
    {
        ship = NULL;
        isFired = false;
    }

    void AddShip(Ship *ship)
    {
        this->ship = ship;
    }

    char GetStatus() 
    {
        if (isFired) 
        {
            return ship == NULL ? MISS : HIT;
        }
        else
        {
            return ship == NULL ? EMPTY : SHIP;
        }            
    }

    bool Fire()
    {
        if (ship != NULL && !isFired && !ship->IsSunk()) 
        {
            ship->Hit();
            isFired = true;
            return true;
        }

        return false;            
    }
};


class Board
{

private:
    //Data members
    BattleShipSquare squares[ROWS][COLUMNS];

    //Assigns the values to the passed input variables x and y
    void GetCoordinates(char& x, char& y)
    {
        do
        {
            cout << "Enter the x cordinate (A-H):" << endl;
            cin >> x;
        } while (x < 65 || x >= 73);

        do
        {
            cout << "Enter the y cordinate (1-8):" << endl;
            cin >> y;
        } while (y < 49 || y >= 57);
    }


public:

    //Constructor 
    Board()
    {
        ResetBoard();
    }


    //Member functions
    bool PlaceShip(char xCoordinate, char yCoordinate, char direction, Ship* ship)
    {
        int shipSize = ship->GetSize();
        int column = xCoordinate - 'A';
        int row = yCoordinate - '1';
        //87W, 69E, 83S, 78N

        if (direction == NORTH)
        {
            if (row < shipSize)
            {
                cout << "Cannot place the ship on: " << yCoordinate << " with direction " << direction << endl;
                return false;
            }
            for (int point = row; point > row - shipSize; point--)
            {
                if (squares[point][column].GetStatus() == SHIP)
                {
                    cout << "Intersects with another ship!" /*<< point << column*/ << endl;
                    return false;
                }
            }

            for (int point = row; point > row - shipSize; point--)
            {
                squares[point][column].AddShip(ship);
                //DEBUG cout << "Ship is placed on " << point << column << endl;
            }

            return true;
        }
        else if (direction == SOUTH)
        {
            if (row > ROWS - shipSize)
            {
                cout << "Cannot place the ship on: " << yCoordinate << " with direction " << direction << endl;
                return false;
            }
            for (int point = row; point < row + shipSize; point++)
            {
                if (squares[point][column].GetStatus() == SHIP)
                {
                    cout << "Intersects with another ship!" /*<< point << column*/ << endl;
                    return false;
                }
            }

            for (int point = row; point < row + shipSize; point++)
            {

                squares[point][column].AddShip(ship);
                //DEBUG cout << "Ship is placed on " << point << column << endl;
            }

            return true;
        }
        else if (direction == WEST)
        {
            if (column < shipSize)
            {
                cout << "Cannot place the ship on: " << xCoordinate << " with direction " << direction << endl;
                return false;
            }
            for (int point = column; point > column - shipSize; point--)
            {
                if (squares[row][point].GetStatus() == SHIP)
                {
                    cout << "Intersects with another ship!" /*<< row << point*/ << endl;
                    return false;
                }
            }

            for (int point = column; point > column - shipSize; point--)
            {
                squares[row][point].AddShip(ship);
                //DEBUG cout << "Ship is placed on " << row << point << endl;
            }

            return true;
        }
        else if (direction == EAST)
        {
            if (column > COLUMNS - shipSize)
            {
                cout << "Cannot place the ship on: " << xCoordinate << " with direction " << direction << endl;
                return false;
            }
            for (int point = column; point < column + shipSize; point++)
            {
                if (squares[row][point].GetStatus() == SHIP)
                {
                    cout << "Intersects with another ship!" /*<< row << point*/ << endl;
                    return false;
                }
            }

            for (int point = column; point < column + shipSize; point++)
            {
                squares[row][point].AddShip(ship);
                //DEBUG cout << "Ship is placed on " << row << point << endl;
            }

            return true;
        }

        return false;
    }



    void DisplayBoard(bool isShipPlacementState, string playerName, int turn = -1)
    {
        if (turn != -1)
        {
            cout << "\nTurn: " << turn << endl;
        }
        cout << "\nDisplaying the current board state of " << playerName << "!" << endl;
        cout << "---A--B--C--D--E--F--G--H" << endl;

        cout << "--------------------------" << endl;

        for (int x = 0; x < ROWS; x++)
        {
            cout << x + 1 << "| ";
            for (int y = 0; y < COLUMNS; y++)
            {
                char valueToShow = ' ';
                if (isShipPlacementState)
                {
                    valueToShow = squares[x][y].GetStatus() == EMPTY ? ' ' : squares[x][y].GetStatus();

                    cout << valueToShow << "  ";
                }
                else
                {
                    if (squares[x][y].GetStatus() == HIT || squares[x][y].GetStatus() == MISS)
                    {
                        cout << squares[x][y].GetStatus() << "  ";
                    }
                    else //Hide SHIP and EMPTY squares
                    {
                        cout << "   ";
                    }
                }
            }

            cout << endl << "--------------------------" << endl;
        }
    }

    char GetSquareState(int xCoordinate, int yCoordinate)
    {
        int column = xCoordinate - 'A';
        int row = yCoordinate - '1';
        return squares[row][column].GetStatus();
    }

    void SetSquareState(char state, int xCoordinate, int yCoordinate)
    {
        int column = xCoordinate - 'A';
        int row = yCoordinate - '1';
        squares[row][column].Fire();// = state;
    }


    void PlaceShip(string playerName, Ship* ships[])
    {
        //Variables
        int addedShipCount;
        char xCoordinate;
        char yCoordinate;
        char direction;

        //Menu 
        cout << "\n---------------------------------" << endl;
        cout << "\tAdd Ship" << endl;
        cout << "---------------------------------" << endl;
        cout << "\tNo Name\tSquares" << endl;
        cout << "---------------------------------" << endl;
        cout << "\t1 Carrier\t5" << endl;
        cout << "\t1 Battleship\t4" << endl;
        cout << "\t2 Cruiser\t3" << endl;
        cout << "\t1 Submarine\t3" << endl;
        cout << "\t1 Destroyer\t2" << endl;
        cout << "---------------------------------" << endl;
        cout << "\n";

        for (addedShipCount = 1; addedShipCount <= SHIPCOUNT; addedShipCount++)
        {
            do
            {
                cout << "\nPlayer " << playerName << " adds " << ships[addedShipCount - 1]->GetType() << " with size " << ships[addedShipCount - 1]->GetSize() << endl;
                cout << "---" << addedShipCount << " of " << SHIPCOUNT << "---" << endl;
                GetCoordinates(xCoordinate, yCoordinate);

                //Gets Direction 
                do
                {
                    cout << "Enter the direction (N/E/S/W):" << endl;
                    cin >> direction;
                } while (direction != 'N' && direction != 'S' && direction != 'W' && direction != 'E');

            } while (!PlaceShip(xCoordinate, yCoordinate, direction, ships[addedShipCount - 1]));

            cout << playerName << " added a ship to x:" << xCoordinate << " and y:" << yCoordinate << "with direction: " << direction << endl;
            DisplayBoard(true, playerName, -1);
        }

        EnterToContinue();
    }

    void FireAtSquare(int& turn, const string playerName)
    {
        //Variables
        char xCoordinate;
        char yCoordinate;
        bool isValidSquare;

        DisplayBoard(false, playerName, turn);

        cout << "\nPlayer " << playerName << " enter coordinates to fire" << endl;
        cout << "---------------------------------" << endl;

        do
        {
            GetCoordinates(xCoordinate, yCoordinate);
            cout << playerName << " fired at " << "x:" << xCoordinate << " y:" << yCoordinate << endl;

            char square = GetSquareState(xCoordinate, yCoordinate);
            if (square == SHIP)
            {
                SetSquareState(HIT, xCoordinate, yCoordinate);
                cout << "HIT!" << endl;
                isValidSquare = true;
            }
            else if (square == EMPTY)
            {
                SetSquareState(MISS, xCoordinate, yCoordinate);
                cout << "MISS!" << endl;
                isValidSquare = true;
            }
            else
            {
                cout << "This square is already hit." << endl;
                isValidSquare = false;
            }
        } while (!isValidSquare);

        turn++;
        EnterToContinue();
    }


    void ResetBoard()
    {
        //Reset Board  
        for (int x = 0; x < ROWS; x++)
        {
            for (int y = 0; y < COLUMNS; y++)
            {
                squares[x][y].Reset();
            }
        }
    }
};

class Player
{
private:
    string name;
    Board board;
    Ship* ships[5];

    void initShipArray() 
    {
        //Should be equal to SHIPCOUNT
        string shipNames[] = { "Carrier", "Battleship", "Cruiser", "Submarine", "Destroyer" };
        int shipSizes[] = { 5, 4, 3, 3, 2 };
        
        for (int i = 0; i < SHIPCOUNT; i++)
        {
            ships[i] = new Ship(shipNames[i], shipSizes[i]);
        }      
    }

public:

    Player(string name, Board board)
    {
        this->name = name;
        this->board = board;
        initShipArray();
    }

    ~Player() 
    {
        for (int i = 0; i < SHIPCOUNT; i++)
        {
            delete ships[i];
        }
    }

    Ship* GetShip(int i) 
    {
        return ships[i];
    }

    void SetName(string name)
    {
        this->name = name;
    }

    string GetName()
    {
        return name;
    }

    void Fire(int& turn, string name) //Return type might be bool. 
    {
        board.FireAtSquare(turn, name);
    }

    void PlaceShip()
    {
        return board.PlaceShip(name, ships);
    }

    void DisplayBoard(bool isShipPlacementState, int const turn = -1)
    {
        board.DisplayBoard(isShipPlacementState, name, turn);
    }

    bool CheckLost()
    {
        for (int i = 0; i < SHIPCOUNT; i++) 
        {
            if (!ships[i]->IsSunk())
            {
                return false;
            }
        }
        return true;
    }

    void ResetBoard()
    {
        board.ResetBoard();
    }

};



//Functions for main

char DisplayMainMenu()
{  
    char menuSelection;
    bool isMenuInvalid;

    //Menu 
    cout << "\x1B[2J\x1B[H";
    cout << "---------------------------------" << endl;
    cout << "\tBattleships" << endl;
    cout << "\tMain Menu" << endl;
    cout << "---------------------------------" << endl;
    cout << "\t1. Start Game" << endl;
    cout << "\t2. Exit Game" << endl;
    cout << "\n";

    //Logic
    do
    {
        cout << "Enter menu selection(1-2):" << endl;
        cin >> menuSelection;

        isMenuInvalid = menuSelection != 49 && menuSelection != 50;
        if (isMenuInvalid)
        {
            cout << "Invalid Entry! Please try again" << endl;
        }
    } while (isMenuInvalid);

    return menuSelection;
}

//Gets the player’s name and return the value.
string GetPlayerName(int playerIndex)
{
    string playerName;

    cout << "**Player " << playerIndex << ", enter your name:" << endl;
    
    cin >> playerName;

    return playerName;
}



void EnterToContinue()
{
    cout << "\nPress enter to continue!";
    cin.clear(); //clears the stream
    cin.ignore(50, '\n'); //ignores next line(enter)
    cin.get(); //“cin>>” expects at least one char input, just enter doesn’t work    
}



int main()
{
    //Variables
    string playerName;    
    char selectedMenu;
    int turn = 0;
    Player* attackingPlayer;
    Player* defendingPlayer;

    selectedMenu = DisplayMainMenu();

    if (selectedMenu == 49) //Option 1
    {    
        //Game Starts
        turn = 1;
        
        //Create two player objects
    
        attackingPlayer = new Player(GetPlayerName(1), Board());
        defendingPlayer = new Player(GetPlayerName(2), Board());        

        attackingPlayer->PlaceShip();
        defendingPlayer->PlaceShip();

        bool attackerWon = false;
        while (!attackerWon)
        {
            defendingPlayer->Fire(turn, attackingPlayer->GetName());

            //FireAtSquare(turn, playerName, gameBoard);
            attackerWon = defendingPlayer->CheckLost();
            
            if (!attackerWon) 
            {
                swap(attackingPlayer, defendingPlayer);
            }

        }

        cout << attackingPlayer->GetName() << " " << "won!" << endl;

        delete(attackingPlayer);
        delete(defendingPlayer);
    }
    else if (selectedMenu == 50) //Option 2
    {
        cout << "Goodbye!" << endl;
        return 0;
    }

}