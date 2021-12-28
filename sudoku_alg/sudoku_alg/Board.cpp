#include "Board.h"

Board::Board(std::string b)
{
    int count = 0;
    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        for (size_t j = 0; j < BOARD_SIZE; j++)
        {
            this->board[i][j] = b[count];
            count++;
        }
    }

    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        this->number_amount[i] = this->CountNumber(b, i+1);
    }
}

bool Board::AddNumber(PlaceInfo place)
{
    if (this->board[place.rowNumber][place.columnNumber] == 0)
    {
        this->board[place.rowNumber][place.columnNumber] = place.number;
        this->number_amount[place.number - 1] = this->number_amount[place.number - 1] + 1;
    }
}

bool Board::CheckForRow(int rNum, int num)
{
    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        if (this->board[rNum][i] == num)
            return true;
    }
    return false;
}

bool Board::CheckForColumn(int cNum, int num)
{
    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        if (this->board[i][cNum] == num)
            return true;
    }
    return false;
}

int Board::HowManyMissingR(int rNum)
{
    return 0;
}

int Board::HowManyMissingC(int cNum)
{
    return 0;
}

bool Board::AddMissingR(int rNum)
{
    return false;
}

bool Board::AddMissingC(int cNum)
{
    return false;
}


//helpers
int Board::CountNumber(std::string b, int number)
{
    return std::count(b.begin(), b.end(), number);
}

