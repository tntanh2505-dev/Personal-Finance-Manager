#include "Wallet.h"

Wallet_Record wallet_record;

void addToWalletBalance(std::string wallet_name, double amount){

    // Find the wallet by wallet_id and add amount to its balance
    for (int i = 0; i < wallet_record.size; ++i){
        if (wallet_record.wals[i].name == wallet_name){
            wallet_record.wals[i].balance += amount;
            return;
            //code returns if wallet found
        }
    }

    //code returns if wallet found. balance applied
    //if wallet not found, manually add new wallet

    //doubling the capacity if size reaches capacity
    if (wallet_record.size == wallet_record.capacity){
        int new_capacity = (wallet_record.capacity == 0) ? 1 : wallet_record.capacity * 2;

        Wallet *new_wals = new Wallet[new_capacity];
        for (int i = 0; i < wallet_record.size; ++i){
            new_wals[i] = wallet_record.wals[i];
        }

        //deleting old array and updating pointer and capacity
        delete[] wallet_record.wals;
        wallet_record.wals = new_wals;
        wallet_record.capacity = new_capacity;
    }

    Wallet newWallet;
    newWallet.name = wallet_name;
    newWallet.wallet_id = wallet_record.size + 1; // Simple incremental ID
    newWallet.balance = amount;

    //add to record
    wallet_record.wals[wallet_record.size] = newWallet;
    wallet_record.size++;
}


//load wallet from binary file if necessary
void LoadWalletFromFile(){ 
    std::fstream fin("data/WalletRecord.bin",std::ios::in | std::ios::binary);

    //If not opened, create a new file and return
    if (!fin.is_open()){
        std::ofstream fout("data/WalletRecord.bin",std::ios::out | std::ios::binary);
        fout.close();
        return;
    }

    // Read wallet records from file
    while(true){
        //attempt to read wallet until end of BINARY file
        Wallet tempWallet;
        if (!fin.read(reinterpret_cast<char*>(&tempWallet.name), sizeof(tempWallet.name))) break;
        //assuming the rest of files is readable
        fin.read(reinterpret_cast<char*>(&tempWallet.balance), sizeof(tempWallet.balance));

        addToWalletBalance(tempWallet.name, tempWallet.balance);
    }

    fin.close();
}

void addWallet(std::string wallet_name){
    addToWalletBalance(wallet_name, 0.0);
}

void listWallets(){
    std::cout << "Wallets:" << std::endl;
    for (int i = 0; i < wallet_record.size; ++i){
        std::cout << wallet_record.wals[i].wallet_id << ". " << wallet_record.wals[i].name 
                  << " - Balance: " << std::fixed << std::setprecision(2) << wallet_record.wals[i].balance << std::endl;
    }
}

void removeWallet(int wallet_id){
    for (int i = 0; i < wallet_record.size; ++i){
        if (wallet_record.wals[i].wallet_id == wallet_id){
            // Shift elements to the left to overwrite the removed wallet
            for (int j = i; j < wallet_record.size - 1; ++j){
                wallet_record.wals[j] = wallet_record.wals[j + 1];
            }
            wallet_record.size--;
            return;
        }
    }
}

void modifyWalletName(int wallet_id, std::string new_name){
    for (int i = 0; i < wallet_record.size; ++i){
        if (wallet_record.wals[i].wallet_id == wallet_id){
            wallet_record.wals[i].name = new_name;
            return;
        }
    }
}

void modifyWalletBalance(int wallet_id, double new_balance){
    for (int i = 0; i < wallet_record.size; ++i){
        if (wallet_record.wals[i].wallet_id == wallet_id){
            wallet_record.wals[i].balance = new_balance;
            return;
        }
    }
}








