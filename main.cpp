#include "CL.h"

int main()
{
    vector<transaction> t;
    vector<member> x;
    short int z;
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