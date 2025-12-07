#include<iostream>
#include<algorithm>
#include<fstream>
#include<iomanip>

#include <filesystem>


#include "Income.h"
#include "Expense.h"
#include "Wallet.h"

int main(){
	//must load initial data from files 
	LoadIncomeFromFile();
	LoadExpenseFromFile(); 
	LoadWalletFromFile(); 
    
	addExpenseCategory("Food");
	InputExpense();

	return 0;
}







