#include "Recurring.h"
#include "recurring.h"
#include "Expense.h"
#include "Wallet.h"
#include "WriteString.h"

Recurring_Record recurring_record;



// Add a Recurring to the Record
void addRecurringRecord(Recurring newRecurring) {

    // Double the capacity if size reaches capacity
    if(recurring_record.size == recurring_record.capacity){

        int new_capacity = (recurring_record.capacity == 0) ? 1 : recurring_record.capacity * 2;
        Recurring *new_recd = new Recurring[new_capacity];

        // Copy old data and paste to the new house
        for(int i = 0; i < recurring_record.size; ++i){
            new_recd[i] = recurring_record.recd[i];
        }
        
        // Deleting old array and updating pointer and capacity
        delete[] recurring_record.recd;
        recurring_record.recd = new_recd;
        recurring_record.capacity = new_capacity;
    }

    // Add new recurring record
    recurring_record.recd[recurring_record.size] = newRecurring;
    recurring_record.size++;
}

// Append a Recurring to the BIN file
void appendRecurringToFile(Recurring newRecurring){
    // Open and check
    std::ofstream fout("data/RecurringRecord.bin", std::ios::binary | std::ios::app);
    if (!fout.is_open()) return;

    // Transaction data
        // Type
        fout.write(reinterpret_cast<const char*>(&newRecurring.typeTransaction), sizeof(newRecurring.typeTransaction));
        // Date
        writeString(fout, newRecurring.date);
        // ID
        fout.write(reinterpret_cast<const char*>(&newRecurring.transaction_id), sizeof(newRecurring.transaction_id));
        // Amount
        fout.write(reinterpret_cast<char*>(&newRecurring.amount), sizeof(newRecurring.amount));
        // Wallet ID
        fout.write(reinterpret_cast<const char*>(&newRecurring.wallet_id), sizeof(newRecurring.wallet_id));
        // Description
        writeString(fout, newRecurring.description);

    // Recurring data
        // ID
        fout.write(reinterpret_cast<const char*>(&newRecurring.recurring_id), sizeof(newRecurring.recurring_id));
        // Start Date
        writeString(fout, newRecurring.startDate);
        // End Date
        writeString(fout, newRecurring.endDate);
        // Last Month Applied
        fout.write(reinterpret_cast<char*>(&newRecurring.lastAppliedMonth), sizeof(newRecurring.lastAppliedMonth));

    fout.close();
}

// Input a Recurring from the console
void InputIncome() {
    Income newIncome;
    
    std::cout << "Enter date (YYYY-MM-DD): ";
    std::cin >> newIncome.date;
    
    std::cout << "Choose source from the income list. If not listed, you must manually add new source" << std::endl;
    std::cout << "Enter source:";
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

