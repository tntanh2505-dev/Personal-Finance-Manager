#include<iostream>
#include<algorithm>
#include<fstream>
#include<iomanip>

#include "include/Income.h"
#include "include/Expense.h"
#include "include/Wallet.h"

int main(){
	//must load initial data from files 
	LoadIncomeFromFile();
	LoadExpenseFromFile(); //to be implemented
	//LoadWalletFromFile(); //to be implemented
	std::cout <<" AS";
	int n;
	std::cin >> n;
	
	return 0;
}







