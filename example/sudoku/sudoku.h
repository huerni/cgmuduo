#pragma once

#include <string>

using std::string;

string solveSudoku(const string& puzzle);
const int kCells = 81;

extern const char kNoSolution[];
