#ifndef WALLET_H
#define WALLET_H

#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<math.h>
#include<cmath>

struct Wallet{
    std::string name;
    int wallet_id;
    double balance;
};

struct Wallet_Record{
    Wallet *wals;
    int size = 0;
    int capacity = 0;
};

extern Wallet_Record wallet_record;
void addToWalletBalance(std::string wallet_name, double amount);

void LoadWalletFromFile();

#endif