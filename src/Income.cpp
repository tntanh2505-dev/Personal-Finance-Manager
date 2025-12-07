#include "Income.h"
#include "Wallet.h"

Income_Record income_record;
//add income record to dynamic array
void addIncomeRecord(Income newIncome){
    //  double the capacity if size reaches capacity
    if(income_record.size == income_record.capacity){
        //expand capacity
        int new_capacity = (income_record.capacity == 0) ? 1 : income_record.capacity * 2;
        Income *new_incd = new Income[new_capacity];
        for(int i = 0; i < income_record.size; ++i){
            new_incd[i] = income_record.incd[i];
        }
        
        //deleting old array and updating pointer and capacity
        delete[] income_record.incd;
        income_record.incd = new_incd;
        income_record.capacity = new_capacity;
    }
    /// Add new income record
    income_record.incd[income_record.size++] = newIncome;
}

// Function to input income details from user
void InputIncome(){
    Income newIncome;
    
    std::cout << "Enter date (YYYY-MM-DD): ";
    std::cin >> newIncome.date;
    
    std::cout << "Enter source: ";
    std::cin >> newIncome.source;
    
    std::cout << "Enter source ID: ";
    std::cin >> newIncome.source_id;
    
    std::cout << "Enter amount: ";
    std::cin >> newIncome.amount;
    
    std::cout << "Enter wallet: ";
    std::cin >> newIncome.wallet;
    
    std::cout << "Enter wallet ID: ";
    std::cin >> newIncome.wallet_id;
    
    std::cout << "Enter description: ";
    std::cin.ignore(); // to ignore the newline character left in the buffer
    std::getline(std::cin, newIncome.description);
    
    addIncomeRecord(newIncome);
    addToWalletBalance(newIncome.wallet, newIncome.amount);
}


//load income from binary file if necessary
void LoadIncomeFromFile(){ 
    std::fstream fin("data/IncomeRecord.bin",std::ios::out | std::ios::binary);

    if (!fin.is_open()){
        // File does not exist, create an empty file
        std::ofstream dummy("data/IncomeRecord.bin", std::ios::out | std::ios::binary);
        dummy.close();
        return;
      }
    
    // Read existing records from the file
    int record_count = 0;
    fin.read(reinterpret_cast<char*>(&record_count), sizeof(record_count));

    // Initialize income_record
    for (int i = 0 ; i < record_count ; i++){
        Income tempIncome;
        
        fin.read(reinterpret_cast<char*>(&tempIncome.date), sizeof(tempIncome.date));
        fin.read(reinterpret_cast<char*>(&tempIncome.source), sizeof(tempIncome.source));
        fin.read(reinterpret_cast<char*>(&tempIncome.amount), sizeof(tempIncome.amount));
        fin.read(reinterpret_cast<char*>(&tempIncome.wallet), sizeof(tempIncome.wallet));
        fin.read(reinterpret_cast<char*>(&tempIncome.description), sizeof(tempIncome.description));
        addIncomeRecord(tempIncome);
    }
}