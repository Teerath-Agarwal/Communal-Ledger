#include "CL.h"
#include "ES.h"
#include "filesys.h"

int main()
{
    short int z;
    // system("cd data");
    cout<<"1. Open existing Ledgers\n2. Create new Ledger\n3. Exit\n-> ";
    cin>>z;
    cin.ignore((numeric_limits<streamsize>::max)(),'\n');
    string s,pw;
    fstream nl;
    switch (z){
        case 3: return 0;
        case 2: 
            cout<<"Enter a name for the Ledger: ";
            getline(cin,s);
            s += ".cld";
            system(to_char("touch data/" + s));
            pw = new_pass();
            break;
        default:
            auto fl = file_list();
            cout<<"Select a ledger to open:\n";
            for (int i=1; i<=fl.size(); i++) cout<<i<<". "<<fl[i-1]<<'\n';
            cout<<"-> ";
            cin>>z;
            s = fl[z-1] + ".cld";
            break;
    }
    cout<<"\n"<<s<<" is opened.\n\n";
    return 0;
    vector<transaction> t;
    vector<member> x;
    read_mem(x);
    read_trans(t);

    while(1)
    {
        cout<<"1. Enter a new transaction\n2. Display all transactions\n3. Display amount to be settled\n4. Exit\n-> ";
        cin>>z;

        if(z==1)
        {
            cout<<endl;
            transaction n(x,t.size());
            t.push_back(n);
            newentry(n);
            z=2;
        }
        switch (z)
        {
            case 2:
                print_ledger(t);
            case 3:
                to_settle(x,t);
                break;
            default:
                return 0;
       }
    }
    return 0;
}