#include "Board.h"
#include <iostream>
#include <string>

Board::Board(std::string b)
{
    int count = 0;
    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        for (size_t j = 0; j < BOARD_SIZE; j++)
        {
            this->board[i][j] = b[count] - 48;
            count++;
        }
    }

    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        this->number_amount[i] = this->CountNumber(b, i+1);
    }
    
    this->number_count = 81 - this->CountNumber(b,0);
    
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
        for (size_t j = 0; j < BOARD_SIZE; j++)
        {
            if (j % 3 == 0)
                std::cout << "| ";

            std::cout << this->board[i][j] << " ";
        }
        std::cout << "|";

        std::cout << std::endl;

        if (i % 3 == 2)
            std::cout << "-------------------------" << std::endl;
    }
}

//helpers
int Board::CountNumber(std::string b, int number)
{
    int count = 0;
    std::string c = std::to_string(number);

    for (int i = 0; i < b.size(); i++)
        if (b[i] == c[0]) count++;

    return count;
}

int Board::GetCount()
{
    return this->number_count;
}

