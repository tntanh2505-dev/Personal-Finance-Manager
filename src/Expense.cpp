#include "Expense.h"
#include "Wallet.h"

Expense_Record expense_record;
Expense_Category_Record expense_category_record;

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
    expense_record.exs[expense_record.size] = newExpense;
    expense_record.size++;
}

void InputExpense(){
    Expense newExpense;
    
    std::cout << "Enter date (YYYY-MM-DD): ";
    std::cin >> newExpense.date;
    
    std::cout << "Choose category from the expense list. If not listed, you must manually add new category" << std::endl;
    std::cout << "Enter category: ";
    std::cin >> newExpense.category;
    
    std::cout << "Enter amount: ";
    std::cin >> newExpense.amount;
    
    std::cout << "Choose wallet from the wallet list. If not listed, you must manually add new wallet" << std::endl;
    std::cout << "Enter wallet: ";
    std::cin >> newExpense.wallet;
    
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

//managing categories
void addExpenseCategory(std::string category_name){
    //check if existed. If yes stop
    for (int i = 0; i < expense_record.size; ++i)
        if (expense_record.exs[i].category == category_name) return;

    //add to record
    //if capcity == size, double the capacity
    if (expense_category_record.size == expense_category_record.capacity){
        int new_capacity = (expense_category_record.capacity == 0) ? 1 : expense_category_record.capacity * 2;
        Expense_Category *new_categories = new Expense_Category[new_capacity];
        for (int i = 0; i < expense_category_record.size; ++i){
            new_categories[i] = expense_category_record.categories[i];
        }

        //deleting old array and updating pointer and capacity
        delete[] expense_category_record.categories;
        expense_category_record.categories = new_categories;
        expense_category_record.capacity = new_capacity;
    }

    Expense_Category newExpense;
    newExpense.name = category_name;
    newExpense.category_id = expense_category_record.size; // Simple incremental ID
    expense_category_record.categories[expense_category_record.size] = newExpense;
    expense_category_record.size++;
}

void listExpenseCategories(){
    std::cout << "Expense Categories:" << std::endl;
    for (int i = 0; i < expense_category_record.size; ++i){
        std::cout << expense_category_record.categories[i].category_id << ". " << expense_category_record.categories[i].name << std::endl;
    }
}






