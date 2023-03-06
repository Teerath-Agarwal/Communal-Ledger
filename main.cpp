#include "CL.h"
#include "filesys.h"

int main()
{
    short int z;
    cout<<"1. Open existing Ledgers\n2. Create new Ledger\n3. Exit\n-> ";
    cin>>z;
    cin.ignore((numeric_limits<streamsize>::max)(),'\n');
    string led_name,mem_path,led_path,pw;
    ifstream inp;
    switch (z){
        case 3:
            cout<<"\nThank You! Have a beautiful day!\nCode written by Teerath Agarwal";
            enter();
            return 0;
        case 2: 
            cout<<"Enter a name for the Ledger: ";
            getline(cin,led_name);
            led_path = ".data/" + led_name + ".cld";
            mem_path = ".data/."+ led_name + ".mem";
            system(to_char("touch " + led_path));
            pw = new_pass();
            inp.open(mem_path);
            enc_algo1(inp,mem_path,pw);
            add_new_mem(mem_path,pw);
            break;
        default:
            auto fl = file_list();
            cout<<"Select a ledger to open:\n";
            for (int i=1; i<=fl.size(); i++) cout<<i<<". "<<fl[i-1]<<'\n';
            cout<<"-> ";
            cin>>z;
            led_name = fl[z-1];
            led_path = ".data/" + led_name + ".cld";
            mem_path = ".data/."+ led_name + ".mem";
            if (!input_pass(led_path,pw)) {
                main();
                return 0;
            }
            break;
    }
    cout<<'\n'<<led_name<<" is now open.\n\n";

    vector<member> x = read_<member>(mem_path, pw);
    vector<transaction> t = read_<transaction>(led_path, pw);

    while(1)
    {
        cout<<"1. Enter a new transaction\n2. Display all transactions\n3. Display amount to be settled\n4. Add new members\n5. Exit\n-> ";
        cin>>z;

        if(z==1)
        {
            cout<<endl;
            transaction n(x,t.size());
            t.push_back(n);
            newentry(n,led_path,pw);
            z=2;
        }
        switch (z)
        {
            case 2:
                print_ledger(t);
            case 3:
                to_settle(x,t);
                break;
            case 4:{
                    // auto new_mems = add_new_mem(mem_path,pw);
                    // for (auto &nm:new_mems) x.push_back(member(nm));
                }
                for (auto nm:add_new_mem(mem_path,pw)) x.push_back(member(nm));
                break;
            default:
                return 0;
       }
    }
    return 0;
}