// Project Started: 30 March 2022
#include "CL.h"

member::member(ifstream &k){
    k >> name;
    money = 0;
}

void member::print_money(){
    cout << abs(money);
}

transaction::transaction(ifstream &k){
    k>>sno;
    k>>date;
    k>>creditor;
    k>>amount;
    k>>debtor;
}

transaction::transaction(vector<member> k, int tn){
    int t;
    sno = tn+1;
    cout<<"Date in DDMMYY format: ";
    cin >> date;
    cout<<"Transaction Amount: ";
    cin >> amount;
    for (int i=0; i<k.size(); i++)
    cout<<(i+1)<<". "<<k[i].name<<"    ";
    cout<<"\nCreditor: ";
    cin >> t;
    creditor = k[t-1].name;
    cout<<"Debtor: ";
    cin >> t;
    debtor = k[t-1].name;
}

int digit(int x)
{
    if (!x) return 1;
    int k=0;
    while (x>=1)
    {
        x/=10;
        k++;
    }
    return k;
}

int get_digits(int num, int st)
{
    int d, k=1;
    /* Removing the extra digits from LHS */
    d=1;
    for (int x=1; x<=st; x++) d = d*10;
    num %= d;
    /* Removing the extra digits from RHS */
    d=1;
    for (int x=1; x<=st-k; x++) d = d*10;
    num /= d;
    return num;
}

void read_trans(vector<transaction> &t)
{
    ifstream k;
    k.open("Ledger.dat");
    while (!k.eof())
    {
        transaction temp(k);
        t.push_back(temp);
    }
    k.close();
    return;
}

void read_mem(vector<member> &t)
{
    ifstream k;
    k.open("Members.dat");
    while (!k.eof())
    {
        member temp(k);
        t.push_back(temp);
    }
    k.close();
    return;
}

void print_ledger(vector<transaction> t)
{
    cout<<endl;
    cout<<"╔═══════╦════════════╦════════════╦═════════════╦════════════╗\n";
    cout<<"║ S.No. ║    Date    ║  Creditor  ║ Transaction ║   Debtor   ║\n";
    cout<<"║       ║            ║            ║   Amount    ║            ║\n";
    cout<<"╠═══════╬════════════╬════════════╬═════════════╬════════════╣\n";
    
    for (int i=0; i<t.size(); i++)
    {
        cout << "║ ";
        for (int j=0; j<(4-digit(t[i].sno)); j++)
        cout<<" ";
        cout<<t[i].sno << ". ║ ";
        for (int j=6 ; j>=3; j--)
        {
            cout<<get_digits(t[i].date,j);
            if (j%2) cout<<"/";
        }
        cout<<"20"<<t[i].date%100<<" ║  ";
        
        cout<<t[i].creditor;
        for (int j=0; j<10-t[i].creditor.length(); j++)
        cout << " ";
        cout << "║ Rs.";
        for (int j=0; j<(6-digit(t[i].amount)); j++)
        cout << " ";
        cout << t[i].amount << "/- ║  ";
        cout<<t[i].debtor;
        for (int j=0; j<10-t[i].debtor.size(); j++)
        cout << " ";
        cout << "║\n";
    }
    cout<<"╚═══════╩════════════╩════════════╩═════════════╩════════════╝\n";
}

void newentry(transaction n)
{
    ofstream k;
    k.open("Ledger.dat", ios::app);
    k<<"\n"<<n.sno<<" ";
    k<<n.date<<" ";
    k<<n.creditor<<" ";
    k<<n.amount<<" ";
    k<<n.debtor;
    k.close();
    return;
}

int mem_ind(vector<member> k, string s)
{
    for (int i=0; i<k.size(); i++)
    if (!s.compare(k[i].name)) return i;
    return -1;
}

void to_settle(vector<member> k, vector<transaction> t)
{
    for (int i=0; i<t.size(); i++)
    {
        k[mem_ind(k,t[i].creditor)].money -= t[i].amount;
        k[mem_ind(k,t[i].debtor)].money += t[i].amount;
    }

    cout<<"\nTransactions to be settled are:\n";
    for (int i=0; i<k.size(); i++)
    {
        cout<<k[i].name;
        for (int j=0; j<11-k[i].name.size(); j++)
        cout << " ";
        if (k[i].money < 0) cout<<" owes  ";
        else cout<<" gets  ";
        cout<<"Rs.";
        if (!k[i].money) cout << " ──nil──\n";
        else
        {
            for (int j=0; j<(6-digit(abs(k[i].money))); j++)
            cout << " ";
            cout<<abs(k[i].money)<<"/-\n";
        }
    }
    cout<<"\n\n";
}