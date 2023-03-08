// Project Started: 30 March 2022
#include "CL.h"

member::member(string name){
    this->name = name;
    money = 0;
}

member::member(istream &k){
    k >> name;
    money = 0;
}

void member::print_money(){
    cout << abs(money);
}

transaction::transaction(istream &k){
    k>>sno;
    k>>date;
    k>>creditor;
    k>>amount;
    k>>debtor;
}

transaction::transaction(vector<member> &k, int tn){
    int t;
    auto check_validity = [&] (int &v, int ub) {
        cin>>v;
        char c;
        while (v>ub || v<1){
            cout<<"Out of bound data, try again? (Y) Discard? (N) -> ";
            cin.ignore((numeric_limits<streamsize>::max)(),'\n');
            cin>>c;
            if (c=='N' || c=='n') {
                cout<<"\n\n";
                sno = -1;
                return;
            }
            cout<<"Enter value -> ";
            cin>>v;
        }
    };
    sno = tn+1;
    cout<<"Date in DDMMYY format: ";
    cin >> date;
    cout<<"Transaction Amount: ";
    check_validity(amount,99999);
    if (sno<0) return;
    for (int i=0; i<k.size(); i++)
        cout<<(i+1)<<". "<<k[i].name<<"    ";
    cout<<"\nCreditor (will owe): ";
    check_validity(t,k.size());
    if (sno<0) return;
    creditor = k[t-1].name;
    cout<<"Debtor (will get): ";
    check_validity(t,k.size());
    if (sno<0) return;
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

void print_ledger(vector<transaction> &t)
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

void newentry(transaction &n, string path, string pw)
{
    ifstream inp(path);
    set_tc(inp);
    string dec = decrypt(decrypt(inp,pw+str_code),pw);
    remove(to_char(path));
    ofstream k(path);
    k << dec;
    // k.open(path, ios::app);
    k<<"\n"<<n.sno<<" ";
    k<<n.date<<" ";
    k<<n.creditor<<" ";
    k<<n.amount<<" ";
    k<<n.debtor;
    k.close();
    inp.open(path);
    enc_algo1(inp,path,pw);
    return;
}

int mem_ind(vector<member> &k, string s)
{
    for (int i=0; i<k.size(); i++)
    if (!s.compare(k[i].name)) return i;
    return -1;
}

void to_settle(vector<member> &k, vector<transaction> &t)
{
    for (auto &i:k) i.money = 0;

    for (auto &i:t){
        k[mem_ind(k,i.creditor)].money -= i.amount;
        k[mem_ind(k,i.debtor)].money += i.amount;
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

vector<string> add_new_mem(string mem_path, string pw){
    ifstream inp(mem_path);
    set_tc(inp);
    string dec = decrypt(decrypt(inp,pw+str_code),pw);
    vector<string> users;
    set<string> users_set;
    stringstream filedat(dec);
    while(!filedat.eof()){
        string t;
        getline(filedat,t);
        users_set.insert(t);
    }
    cout<<"Enter the number of members you want to add (may change later):\n-> ";
    int z;
    cin>>z;
    if (z>0) cout<<"Enter the names (max length 10) one by one:\n";
    string name;
    for (int i=1; i<=z; i++){
        cout<<i<<".) ";
        cin>>name;
        if (users_set.find(name)!=users_set.end()) {
            cout<< "\nThis username is not available.\n\n";
            i--;
        }
        else {
            users_set.insert(name);
            users.push_back(name);
        }
    }
    ofstream outp;
    remove(to_char(mem_path));
    outp.open(mem_path);
    outp << dec;
    for (auto u:users)
    outp<<u<<'\n';
    outp.close();
    inp.open(mem_path);
    enc_algo1(inp,mem_path,pw);
    cout<<"\nUsers successfully added!\n\n";
    return users;
}

template <typename T> vector<T> read_(string path, string pw){
    vector<T> t;
    ifstream inp;
    inp.open(path);
    set_tc(inp);
    string dec = decrypt(decrypt(inp,pw+str_code),pw);
    stringstream k(dec);
    while (!k.eof())
    {
        T temp(k);
        t.push_back(temp);
    }
    return t;
}

template vector<member> read_<member>(string path, string pw);

template vector<transaction> read_<transaction>(string path, string pw);