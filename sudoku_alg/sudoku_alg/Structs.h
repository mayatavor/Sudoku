#pragma once


struct PlaceInfo
{
	int number;
	int rowNumber;
	int columnNumber;

	PlaceInfo(int n, int r, int c)
	{
		number = n;
		rowNumber = r;
		columnNumber = c;
	}
	PlaceInfo(int r, int c)
	{
		number = 0;
		rowNumber = r;
		columnNumber = c;
	}
};


