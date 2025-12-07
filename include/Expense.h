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
    int size = 0;
    int capacity = 0;
};

struct Expense_Category{
    std::string name;
    int category_id;
};

struct Expense_Category_Record{
    Expense_Category *categories;
    int size = 0;
    int capacity = 0;
};

extern Expense_Record expense_record;
extern Expense_Category_Record expense_category_record;

void InputExpense();
void addExpenseRecord(Expense newExpense);
void LoadExpenseFromFile();

//manage category
void addExpenseCategory(std::string category_name);
void listExpenseCategories();
void removeExpenseCategory(int category_id);
void editExpenseCategory(int category_id, std::string new_name);
void checkExistingExpenseCategory(std::string category_name);


#endif