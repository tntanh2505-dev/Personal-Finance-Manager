#ifndef EXPENSE_H
#define EXPENSE_H

#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<math.h>
#include<cmath>

struct Expense{
    std::string date;

    std::string category;
    int category_id;

    double amount;

    std::string wallet;
    int wallet_id;

    std::string description;
};

struct Expense_Record{
    Expense *exs;
    int size;
    int capacity;
};

extern Expense_Record expense_record;
void InputExpense();
void addExpenseRecord(Expense newExpense);
void LoadExpenseFromFile();

#endif