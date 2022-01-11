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
    
    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        this->number_count += this->number_amount[i];
    }
}

void Board::AddNumber(PlaceInfo place)
{
    if (this->board[place.rowNumber][place.columnNumber] == 0)
    {
        this->board[place.rowNumber][place.columnNumber] = place.number;
        this->number_amount[place.number - 1] = this->number_amount[place.number - 1] + 1;
        this->number_count++;
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


void Board::PrintBoard()
{
    //option 1
    /*
            -----------------------------------------
            || 0 | 9 | 8 || 0 | 4 | 5 || 1 | 3 | 7 ||
            ||-----------||-----------||-----------||
            || 0 | 0 | 0 || 0 | 0 | 0 || 0 | 0 | 0 ||
            ||-----------||-----------||-----------||
            || 0 | 0 | 0 || 0 | 0 | 0 || 0 | 0 | 0 ||
            ||-------------------------------------||
            || 0 | 0 | 0 || 0 | 0 | 0 || 0 | 0 | 0 ||
            ||-----------||-----------||-----------||
            || 0 | 0 | 0 || 0 | 0 | 0 || 0 | 0 | 0 ||
            ||-----------||-----------||-----------||
            || 0 | 0 | 0 || 0 | 0 | 0 || 0 | 0 | 0 ||
            ||-------------------------------------||
            || 0 | 0 | 0 || 0 | 0 | 0 || 0 | 0 | 0 ||
            ||-----------||-----------||-----------||
            || 0 | 0 | 0 || 0 | 0 | 0 || 0 | 0 | 0 ||
            ||-----------||-----------||-----------||
            || 0 | 0 | 0 || 0 | 0 | 0 || 0 | 0 | 0 ||
            -----------------------------------------
    */

    //option 2
    /*
           -------------------------
           | 0 9 8 | 0 4 5 | 1 3 7 |
           | 0 0 0 | 0 0 0 | 0 0 0 |
           | 0 0 0 | 0 0 0 | 0 0 0 |
           -------------------------
           | 0 0 0 | 0 0 0 | 0 0 0 |
           | 0 0 0 | 0 0 0 | 0 0 0 |
           | 0 0 0 | 0 0 0 | 0 0 0 |
           -------------------------
           | 0 0 0 | 0 0 0 | 0 0 0 |
           | 0 0 0 | 0 0 0 | 0 0 0 |
           | 0 0 0 | 0 0 0 | 0 0 0 |
           -------------------------
    */
    std::cout << "-------------------------" << std::endl;
    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        std::cout << "|";
        for (size_t j = 0; j < BOARD_SIZE; j++)
        {
            if (j % 3 == 0)
                std::cout << "| ";

            std::cout << this->board[i][j] << " ";
        }

        std::cout << std::endl;

        if (i % 3 == 0)
            std::cout << "-------------------------" << std::endl;
    }
}

//helpers
int Board::CountNumber(std::string b, int number)
{
    return std::count(b.begin(), b.end(), number);
}

int Board::GetCount()
{
    return this->number_count;
}

