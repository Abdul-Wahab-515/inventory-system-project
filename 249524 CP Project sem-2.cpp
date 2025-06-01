#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

//these are the global constants.
const int MAX_PRO=100;
const int NAME_LENGTH=50;
const int LOW_STOCK_THRESHOLD=5;
char proNames[MAX_PRO][NAME_LENGTH];
int proIDs[MAX_PRO], proCount=0, quantities[MAX_PRO];
float prices[MAX_PRO];

//Here Functions are called before int main to run the code. as it will not work until they are called before ijt main.
void load_file(int*, char[][NAME_LENGTH], int*, float*, int*);
void save_file(int*, char[][NAME_LENGTH], int*, float*, int*);
void add_pro(int*, char[][NAME_LENGTH], int*, float*, int*);
void sell_pro(int*, char[][NAME_LENGTH], int*, float*, int*);
void restock_pro(int*, char[][NAME_LENGTH], int*, float*, int*);
void view_inventory(int*, char[][NAME_LENGTH], int*, float*, int*);
void search_pro(int*, char[][NAME_LENGTH], int*, float*, int*);
int findProByID(int, int*, int);
int findProByName(const char[], char[][NAME_LENGTH], int);
bool isUniqueID(int, int*, int);

//This is int main, the main function which runs the code.
//in this all functions are called and utilized.

int main()
{
    load_file(proIDs, proNames, quantities, prices, &proCount);
    int choice;
    do				//This is a loop which prompt user to select the program to be performed.
	{
        cout<<"\n\n\n\n\t\t\t\t====>>> Hardware Store Inventory Management <<<====\n\n\n";
        cout<<"1. Add New Product\n";
        cout<<"2. Sell Product\n";
        cout<<"3. Restock Product\n";
        cout<<"4. View Inventory\n";
        cout<<"5. Search Product\n";
        cout<<"6. Save and Exit\n";
        cout<<"Enter your choice: ";
        cin>>choice;

        switch(choice)			//this is switch whiich help select the choice of the user to perform the task.
		{
            case 1:add_pro(proIDs, proNames, quantities, prices, &proCount);
			break;
            case 2:sell_pro(proIDs, proNames, quantities, prices, &proCount);
			break;
            case 3:restock_pro(proIDs, proNames, quantities, prices, &proCount);
			break;
            case 4:view_inventory(proIDs, proNames, quantities, prices, &proCount);
			break;
            case 5:search_pro(proIDs, proNames, quantities, prices, &proCount);
			break;
            case 6:save_file(proIDs, proNames, quantities, prices, &proCount); 
			{
			cout<<"\n\nData saved. Thanks! \n\n";
		}
			break;
            default:cout<<"\nInvalid choice. Sorry for incovinence\n";
        }
    } while (choice!=6);

    return 0;
}

//This is a function to add products in the list of inventory for hardware shop.
void add_pro(int* ids, char names[][NAME_LENGTH], int* qty, float* price, int* count) {
    if (*count>=MAX_PRO){
        cout<<"\nInventory is full. No more items can be added\n";
        return;
    }
    int id, quantity;
    float unitPrice;
    char name[NAME_LENGTH];

    cout<<"\nEnter Product ID: ";
    cin>>id;
    if (!isUniqueID(id, ids, *count))
	{
        cout<<"\nID must be unique. Select the program Again.\n";
        return;
    }
    cout<<"\nEnter Product Name: ";
    cin>>name;
    cout<<"\nEnter Quantity: ";
    cin>>quantity;
    cout<<"\nEnter Price: ";
    cin>>unitPrice;

    if (quantity<0||unitPrice<0)
	{
        cout<<"\nInvalid input.It Must be non-negative value.\n";
        return;
    }

    ids[*count]=id;
    strcpy(names[*count], name);
    qty[*count]=quantity;
    price[*count]=unitPrice;
    (*count)++;
    cout << "\nProduct added successfully.\n";
}

//this is a function written to sell products from the inventory.
void sell_pro(int* ids, char names[][NAME_LENGTH], int* qty, float* price, int* count)
{
    int id, amount;
    cout<<"\nEnter Product ID to sell: ";
    cin>>id;
    int index=findProByID(id, ids, *count);
    if (index==-1)
	{
        cout<<"\nProduct not found.\n";
        return;
    }
    cout<<"\nEnter quantity to sell: ";
    cin>>amount;
    if (amount>qty[index])
	{
        cout<<"\nInsufficient stock.\n";
    }
	else
	{
        qty[index]-=amount;
        cout<<"\n( "<<amount<<" ) Item Sold. *Congratulations*.\n";
    }
}

//this function is written to restock the products in the inventory.
void restock_pro(int* ids, char names[][NAME_LENGTH], int* qty, float* price, int* count) {
    int id, amount;
    cout<<"\nEnter Product ID to restock: ";
    cin>>id;
    int index=findProByID(id, ids, *count);
    if (index==-1)
	{
        cout<<"\nProduct not found.\n";
        return;
    }
    cout<<"\nEnter quantity to add: ";
    cin>>amount;
    if (amount<0)
	{
        cout<<"\nInvalid quantity.\n";
        return;
    }
    qty[index]+=amount;
    cout<<"\nRestocked succesfully.\n";
}
//this is the function made to view the inventory on the point where it was last saved.
void view_inventory(int* ids, char names[][NAME_LENGTH], int* qty, float* price, int* count)
{
	
    cout<<"\n(---> Inventory <---)\n";
    cout<<"\n----------------------------------------------------------------------------------------\n";
    cout<<"|ID  \t \t| Name    \t\t| Quantity \t| Price \t\t| Total\n";
    cout<<"----------------------------------------------------------------------------------------\n";
    for (int i=0; i<*count; i++)
	{int total[i];
	total[i]=price[i]*qty[i];
        cout<<"|"<<ids[i]<<"\t\t  |"<<names[i]<<"\t\t  |"<<qty[i]<<"\t\t  |Rs."<<price[i]<<"\t\t  |Rs."<<total[i];
        if (qty[i]<LOW_STOCK_THRESHOLD)
		{
		cout << " \t  \t <--- Low stock!";
		}
        cout << endl;
    }
}

//this is the function typed to find product in the inventory.
void search_pro(int* ids, char names[][NAME_LENGTH], int* qty, float* price, int* count) {
    int choice;
    cout<<"Search by: \n\t\t 1. ID \t 2. Name\nChoice: ";
    cin>>choice;
    if (choice==1)
	{
        int id;
        cout<<"\nEnter ID: ";
        cin>>id;
        int index=findProByID(id, ids, *count);
        if (index!=-1)
            cout<<"\n--->  Found: ["<<names[index]<<"], Qty: "<<qty[index]<<", Price: "<<price[index]<<endl;
        else
            cout<<"\nProduct not found.\n";
    } 
	else
	{
        char name[NAME_LENGTH];
        cout<<"\nEnter Name: ";
        cin>>name;
        int index=findProByName(name, names, *count);
        if (index!=-1)
        {
		
            cout<<"\nFound: ID: "<<ids[index]<<", Qty: "<<qty[index]<<", Price: "<<price[index]<<endl;
    }
		else
            cout<<"\nProduct not found.\n";
    }
}

//there are two options to search a product in the inventory.
//one is to search by ID.
int findProByID(int id, int* ids, int count) {
    for (int i=0; i<count; i++)
	{
	
        if (ids[i] == id)
            return i;
    }
	return -1;
}

//second one is to search by product name.
int findProByName(const char name[], char names[][NAME_LENGTH], int count) {
    for (int i=0; i<count; i++)
	{
	
        if (strcmp(names[i], name) == 0)
            return i;
    }
	return -1;
}

//this function is written to check the ID written by the user is Unique or not.
bool isUniqueID(int id, int* ids, int count)
{
    return findProByID(id, ids, count) == -1;
}

//this code is written to take data in the file named [ InventoryForProject ].
void load_file(int* ids, char names[][NAME_LENGTH], int* qty, float* price, int* count) {
    ifstream file("InventoryForProject.txt");
    *count=0;
    while (file>>ids[*count]>>names[*count]>>qty[*count]>>price[*count])
	{
        (*count)++;
    }
    file.close();
}

//this code is written to enter data in the file named [ InventoryForﬁroject ].
void save_file(int* ids, char names[][NAME_LENGTH], int* qty, float* price, int* count) {
    ofstream file("InventoryForProject.txt");
    for (int i=0; i<*count; i++)
	{
        file<<ids[i]<<" \t"<<names[i]<<"\t "<<qty[i]<<" \t"<<price[i]<<endl;
    }
    file.close();
}
