#include "Income.h"
#include "Wallet.h"

Income_Record income_record;
Income_Source_Record income_source_record;

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
    income_record.incd[income_record.size] = newIncome;
    income_record.size++;

    //write income record to binary file
    addToBinaryFile(newIncome);
}
void addToBinaryFile(Income newIncome){
    std::fstream fout("data/IncomeRecord.bin",std::ios::out | std::ios::binary | std::ios::app);


    // Write the income record to the file
    fout.write(reinterpret_cast<char*>(&newIncome.date), sizeof(newIncome.date));
    fout.write(reinterpret_cast<char*>(&newIncome.source), sizeof(newIncome.source));
    fout.write(reinterpret_cast<char*>(&newIncome.amount), sizeof(newIncome.amount));
    fout.write(reinterpret_cast<char*>(&newIncome.wallet), sizeof(newIncome.wallet));
    fout.write(reinterpret_cast<char*>(&newIncome.description), sizeof(newIncome.description));

    fout.close();
}
// Function to input income details from user
void InputIncome(){
    Income newIncome;
    
    std::cout << "Enter date (YYYY-MM-DD): ";
    std::cin >> newIncome.date;
    
    std::cout << "Choose source from the income list. If not listed, you must manually add new source" << std::endl;
    std:: cout << "Enter source:";
    std::cin >> newIncome.source;
    
    std::cout << "Enter amount: ";
    std::cin >> newIncome.amount;
    
    std::cout << "Choose wallet from the wallet list. If not listed, you must manually add new wallet" << std::endl;
    std::cout << "Enter wallet: ";
    std::cin >> newIncome.wallet;
    
    std::cout << "Enter description: ";
    std::cin.ignore(); // to ignore the newline character left in the buffer
    std::getline(std::cin, newIncome.description);
    
    addIncomeSource(newIncome.source); // Ensure source is added automatically if user forgets
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
void LoadIncomeSourceFromFile(){ 
    std::fstream fin("data/IncomeRecord.bin",std::ios::in | std::ios::binary);

    if (!fin.is_open()){
        std::ofstream fout("data/IncomeRecord.bin",std::ios::out | std::ios::binary);
        fout.close();
        return;
    }

    //read file content into income_source_record
    int record_count = 0;
    fin.read(reinterpret_cast<char*>(&record_count), sizeof(record_count));

    //read each income record and add to income_source_record
    for(int i = 0; i < record_count; ++i){
        std::string name;
        fin.read(reinterpret_cast<char*>(&name), sizeof(name));
        addIncomeSource(name);
    }
}

//add, edit, remove income source functions 
void listIncomeSources(){
    std::cout << "Income Sources:" << std::endl;
    for (int i = 0; i < income_source_record.size; ++i){
        std::cout << income_source_record.sources[i].source_id << ". " << income_source_record.sources[i].name << std::endl;
    }
}

void addIncomeSource(std::string source_name){
    //if size == capacity, double the capacity
    if (income_source_record.size == income_source_record.capacity){
        int new_capacity = (income_source_record.capacity == 0) ? 1 : income_source_record.capacity * 2;
        Income_Source *new_sources = new Income_Source[new_capacity];
        for (int i = 0; i < income_source_record.size; ++i){
            new_sources[i] = income_source_record.sources[i];
        }

        //deleting old array and updating pointer and capacity
        delete[] income_source_record.sources;
        income_source_record.sources = new_sources;
        income_source_record.capacity = new_capacity;
    }

    //add to record
    Income_Source newSource;
    newSource.name = source_name;
    newSource.source_id = income_source_record.size + 1; // Simple incremental ID
    income_source_record.sources[income_source_record.size] = newSource;
    income_source_record.size++;
}

void editIncomeSource(int source_id, std::string new_name){
    for (int i = 0; i < income_source_record.size; ++i){
        if (income_source_record.sources[i].source_id == source_id){
            income_source_record.sources[i].name = new_name;
            return;
        }
    }
}

void removeIncomeSource(int source_id){
    for (int i = 0; i < income_source_record.size; ++i){
        if (income_source_record.sources[i].source_id == source_id){
            //shift elements to the left to fill the gap
            for (int j = i; j < income_source_record.size - 1; ++j){
                income_source_record.sources[j] = income_source_record.sources[j + 1];
            }
            income_source_record.size--;
            return;
        }
    }
}

