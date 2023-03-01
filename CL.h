// Project Started: 30 March 2022
// Last worked on: 6 April 2022
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class member
{
    public:
    string name;
    int money;

    member(ifstream &k);
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
    
    transaction(ifstream &k);

    transaction(vector<member> k, int tn);
};

int digit(int x);

int get_digits(int num, int st);

void read_trans(vector<transaction> &t);

void read_mem(vector<member> &t);

void print_ledger(vector<transaction> t);

void newentry(transaction n);

int mem_ind(vector<member> k, string s);

void to_settle(vector<member> k, vector<transaction> t);