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
        delete[] new_wals;
    }

    Wallet newWallet;
    newWallet.name = wallet_name;
    newWallet.wallet_id = wallet_record.size + 1; // Simple incremental ID
    newWallet.balance = amount;

    //add to record
    wallet_record.wals[wallet_record.size++] = newWallet;
}