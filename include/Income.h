#ifndef INCOME_H
#define INCOME_H

#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<math.h>
#include<cmath>

struct Income{
    std::string date;

    std::string source;
    int source_id;

    double amount;

    std::string wallet;
    int wallet_id;

    std::string description;
};

struct Income_Record{
    Income *incd;
    int size = 0;
    int capacity = 0;
};

extern Income_Record income_record;

void InputIncome();
void addIncomeRecord(Income newIncome);

//load income from binary file if necessary
void LoadIncomeFromFile();

#endif