// Project Started: 30 March 2022
#ifndef CL_H
#define CL_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <set>
#include "Encryption-Software/ES.h"
using namespace std;

class member
{
    public:
    string name;
    int money;

    member(string name);
    member(istream &k);
    void print_money();
};

class transaction
{
    public:
    int sno;
    int date;
    int amount;
    string creditor;
    string debtor;
    
    transaction(istream &k);

    transaction(vector<member> &k, int tn);
};

int digit(int x);

int get_digits(int num, int st);

template <typename T> vector<T> read_(string path, string pw);

void print_ledger(vector<transaction> &t);

void newentry(transaction &n, string path, string pw);

int mem_ind(vector<member> &k, string s);

void to_settle(vector<member> &k, vector<transaction> &t);

vector<string> add_new_mem(string s, string pw);

#endif