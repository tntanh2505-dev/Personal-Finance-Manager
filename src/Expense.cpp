#include "Expense.h"
#include "Wallet.h"

Expense_Record expense_record;

//add expense record to dynamic array
void addExpenseRecord(Expense newExpense){
    //  double the capacity if size reaches capacity
    if(expense_record.size == expense_record.capacity){
        //expand capacity
        int new_capacity = (expense_record.capacity == 0) ? 1 : expense_record.capacity * 2;
        Expense *new_exs = new Expense[new_capacity];
        for(int i = 0; i < expense_record.size; ++i){
            new_exs[i] = expense_record.exs[i];
        }
        
        //deleting old array and updating pointer and capacity
        delete[] expense_record.exs;
        expense_record.exs = new_exs;
        expense_record.capacity = new_capacity;
    }
    /// Add new expense record
    expense_record.exs[expense_record.size++] = newExpense;
}

void InputExpense(){
    Expense newExpense;
    
    std::cout << "Enter date (YYYY-MM-DD): ";
    std::cin >> newExpense.date;
    
    std::cout << "Enter category: ";
    std::cin >> newExpense.category;
    
    std::cout << "Enter category ID: ";
    std::cin >> newExpense.category_id;
    
    std::cout << "Enter amount: ";
    std::cin >> newExpense.amount;
    
    std::cout << "Enter wallet: ";
    std::cin >> newExpense.wallet;
    
    std::cout << "Enter wallet ID: ";
    std::cin >> newExpense.wallet_id;
    
    std::cout << "Enter description: ";
    std::cin.ignore(); // to ignore the newline character left in the buffer
    std::getline(std::cin, newExpense.description);
    
    addExpenseRecord(newExpense);
    addToWalletBalance(newExpense.wallet, -newExpense.amount);
}


//load expense from binary file if necessary
void LoadExpenseFromFile(){ 
    std::fstream fin("data/ExpenseRecord.bin",std::ios::in | std::ios::binary);

    if (!fin.is_open()){
        std::ofstream fout("data/ExpenseRecord.bin",std::ios::out | std::ios::binary);
        fout.close();
        return;
    }

    //read file content into expense_record
    int record_count = 0;
    fin.read(reinterpret_cast<char*>(&record_count), sizeof(int));

    //read each expense record and add to expense_record
    for(int i = 0; i < record_count; ++i){
        Expense tempExpense;

        fin.read(reinterpret_cast<char*>(&tempExpense.date), sizeof(tempExpense.date));
        fin.read(reinterpret_cast<char*>(&tempExpense.category), sizeof(tempExpense.category));
        fin.read(reinterpret_cast<char*>(&tempExpense.amount), sizeof(tempExpense.amount));
        fin.read(reinterpret_cast<char*>(&tempExpense.wallet), sizeof(tempExpense.wallet));
        fin.read(reinterpret_cast<char*>(&tempExpense.description), sizeof(tempExpense.description));
        addExpenseRecord(tempExpense);
    }


    fin.close();
}