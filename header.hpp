#include<iostream>
#include<fstream>

using namespace std;

class car_store {
private:
    int pcode; //car code
    float price;
    float dis; //discount
    string carname; //name of the car

public:
    //public function
    void menu();
    void administrator(); //for administrators
    void buyer(); //for buyer
    void add(); //to add a car
    void edit(); //to edit the price, name etc
    void rem(); //to remove a car
    void list(); //to list all the items
    void receipt();  //to get the receipt
};

//declaring the definition of the menu function outside the class using the scope resolution operator
//scope resolution operator helps us in defining the function body outside the class
void car_store::menu()
{
    int choice;
    string email;
    string password;
    while (1) {
        cout << "\t_______________________________________________________________\n";
        cout << "\t|                                                              |\n";
        cout << "\t|                          Car Store Menu                      |\n";
        cout << "\t|                                                              |\n";
        cout << "\t|______________________________________________________________|\n";
        cout << endl;

        cout << "\t|                        (1) Administrator                     |\n";
        cout << "\t|                                                              |\n";
        cout << "\t|                        (2) Buyer                             |\n";
        cout << "\t|                                                              |\n";
        cout << "\t|                        (3) Exit                              |\n";
        cout << "\t|                                                              |\n";

        cout << endl;

        cout << "\t  Please Select  : "; cin >> choice; //getting the user choice 

        switch (choice)
        {
        case 1:
        {
            cout << "\t  Please Login  \n";
            cout << "\t  Enter Your Email : ";
            cin >> email; //getting the email of the user
            cout << "\t  Enter Password  : ";
            cin >> password;

            //checking for authentication
            if (email == "admin@gmail.com" && password == "1")
            {
                administrator(); //we will call the administrator function if the email and password is correct
            }
            else
            {
                cout << "\t  Invalid Email Or Password \n";
            }

            break; //to stop the case here
        }

        case 2:
        {
            buyer();
            break;
        }

        case 3:
        {
            exit(0);//it will mark successfull termination of the programme
            break;
        }
        default:
        {
            cout << "\t  Please select from the given Options \n";
        }
        }
    }
}

void car_store::administrator()
{

    int choice;
    while (1) {
        cout << endl;
        cout << "\t Administrator Menu \n";
        cout << "\n\t|__________1) Add new car_____________________|";
        cout << "\n\t|                                             |";
        cout << "\n\t|__________2) Modify the car__________________|";
        cout << "\n\t|                                             |";
        cout << "\n\t|__________3) Remove car______________________|";
        cout << "\n\t|                                             |";
        cout << "\n\t|__________4) Back to Main menu_______________|";
        cout << endl;

        cout << "\n\t  Please Enter your choice  ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            add(); //to add a new car
            break;
        }
        case 2:
        {
            edit(); //to modify or edit the existing car
            break;
        }
        case 3:
        {
            rem(); //to remove the car
            break;
        }
        case 4:
        {
            menu(); //to display the menu
            break;
        }
        default:
            cout << "\t  Invalid Choice !!";
        }

    }
}

//this function will helps us to add the car in the cart
void car_store::add()
{
m:
    fstream data;
    int c;
    int token = 0;
    float p;
    float d;
    string n;

    cout << "\n\n\t  Add new car  ";
    cout << "\n\n\t  Enter car code ";
    cin >> pcode;
    cout << "\n\n\t  Name of the car (Toyota, Tesla, Kia, Ford, Honda,...) ";
    cin >> carname;
    cout << "\n\n\t  Price of the car ";
    cin >> price;
    cout << "\n\n\t  Discount on car  ";
    cin >> dis;

    data.open("database.txt", ios::in);//ios :: in -- is used to read from the file

    if (!data) //if the file doesnt exist
    {
        data.open("database.txt", ios::app | ios::out);//ios::app is used to append to the file and ios:: out is used to write in the file
        data << " " << pcode << " " << carname << " " << price << " " << dis << "\n";
        data.close(); //closing the file
    }
    else
    {
        data >> c >> n >> p >> d; //if the file exists then we will iterate over the file values

        while (!data.eof()) //this will help us to iterate till the last of the file
        {
            if (c == pcode) //if a car with the same code exists then we will not add it again and thats why we are using token variable to keep count if it already exists or not
            {
                token++;
            }

            data >> c >> n >> p >> d;
        }
        data.close(); //closing the file

        if (token == 1) //if the token value is incremented to 1 it means that the car is already present 
        {
            goto m;
        }
        else
        {
            data.open("database.txt", ios::app | ios::out);//ios::app is used to append to the file and ios:: out is used to write in the file
            data << " " << pcode << " " << carname << " " << price << " " << dis << "\n";
            data.close(); //closing the file
        }
    }

    cout << "\n\t  Record Inserted Successfully !!" << endl;
}

void car_store::edit()
{
    fstream data, data1; //creating two objects of the fstream class 
    int pkey; //to get the car code from the administrator
    int token = 0;
    int c;
    float p;
    float d;
    string n;

    cout << "\n\t  Modify the car product ";
    cout << "\n\t  Enter car Code  :";
    cin >> pkey;

    data.open("database.txt", ios::in);

    if (!data) //if the file doesnt exist
    {
        cout << "\n\n\t  File doesn't Exist ! ";
    }
    else
    {
        //we will write the updated value in the database1 file and then we will update its name to database after we make the changes 
        data1.open("database1.txt", ios::app | ios::out);

        data >> pcode >> carname >> price >> dis;

        while (!data.eof())
        {
            if (pkey == pcode) //if the car exists
            {
                cout << "\n\t  Car new Code  :";
                cin >> c;
                cout << "\n\t  Name of the car  :";
                cin >> n;
                cout << "\n\t  Price  :";
                cin >> p;
                cout << "\n\t  Discount :";
                cin >> d;

                //enter the new record
                data1 << " " << c << " " << n << " " << p << " " << d << "\n";
                cout << "\n\n\t  Record Edited  ";
                token++; //incrementing token bcs we find the car with the same car code
            }
            else // when the pkey entered by the user doesnt matches with the existing cars code
            {
                data1 << " " << pcode << " " << carname << " " << price << " " << dis << "\n";
            }

            data >> pcode >> carname >> price >> dis; //this will helps us in iterating again and again
        }
        //closing both the files
        data.close();
        data1.close();

        //we will firstly remove the old database file and then we will rename the database1.txt to database.txt
        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0) //it means that the car with the pcode is not present as the token value is not incremented
        {
            cout << "\n\n\t  Sorry! Record not found ";
        }
    }
}

void car_store::rem()
{
    fstream data, data1;//creating object of the fstream class
    int pkey;
    int token = 0;
    cout << "\n\n\t  Delete car ";
    cout << "\n\n\t  Car code  :";
    cin >> pkey;

    data.open("database.txt", ios::in);//opening the file

    if (!data) //if file doesn't exist
    {
        cout << "\t  File doesn't Exist" << endl;
    }
    else
    {
        data1.open("database1.txt", ios::app | ios::out);
        data >> pcode >> carname >> price >> dis; //getting the values of the different variables so that we can iterate over the file

        while (!data.eof()) //we will iterate till the end of the file
        {
            if (pcode == pkey)
            {
                cout << "\n\n\t  Car deleted Successfully ";
                token++; //incrementing the token because we find the car
            }
            else
            {
                data1 << " " << pcode << " " << carname << " " << price << " " << dis << "\n";//writing into the file
            }

            data >> pcode >> carname >> price >> dis; //for iteratiion
        }

        //closing the opened files 
        //and removing and renaming the files

        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0)
        {
            cout << "\n\t  Record Not found" << endl;
        }

    }
}

//this function will displays all the items present to the users
void car_store::list()
{
    fstream data;
    data.open("database.txt", ios::in);

    cout << "\n\n\t|____________________________________________________________________|\n";
    cout << "\t  Car No. \t  Name \t\t Price \n";
    cout << "\n\n\t|____________________________________________________________________|\n";
    data >> pcode >> carname >> price >> dis;

    while (!data.eof())
    {
        cout << "\t   " << pcode << "\t\t" << carname << "\t\t " << price << "\n";
        data >> pcode >> carname >> price >> dis; //for iteration purpose
    }

    data.close();

}

void car_store::receipt()
{
m:
    fstream data;

    int arrc[100]; //we are taking a array to hold the code of the various car
    int arrq[100]; //we are taking a array to hold the quantity of each car

    string choice;
    int c = 0; //counter
    float amount = 0;
    float dis = 0;
    float total = 0;

    cout << "\n\n\t                          RECEIPT                      ";
    data.open("database.txt", ios::in); //opening the database file in read mode

    if (!data) //if the file doesn't exists
    {
        cout << "\n\n\t  Empty database" << endl;
        return;
    }
    else
    {
        data.close(); //we will closed the already opened file first

        list(); //if the file exists then we will show its content to the user

        cout << "\n\t__________________________________________________\n";
        cout << "\n\t|                                                 |\n";
        cout << "\n\t|            Please place your order              |\n";
        cout << "\n\t|                                                 |\n";
        cout << "\n\t__________________________________________________\n";


        //we are going to use do while loop here

        do
        {
            cout << "\n\n\t  Enter car Code  :";
            cin >> arrc[c]; //getting the car code in our array
            cout << "\n\n\t  Enter the Car Quantity  :";
            cin >> arrq[c];

            //checking if we ordering duplicate items or not
            for (int i = 0; i < c; i++)
            {
                if (arrc[c] == arrc[i])
                {
                    cout << "\n\n\t  Duplicate car Code . Please try again :";
                    goto m;
                }
            }
            //if it is not a duplicate car code then we are going to increase the count of car
            c++;

            cout << "\n\n\t  Do you want to Buy another car ? If yes then Press 'y' else 'n' ";
            cin >> choice;
        } while (choice == "y" || choice == "yes" || choice == "Yes" || choice == "Y"); //if the user wants to buy then we will repeat the loop


        cout << "\n\n\t_________________________________RECEIPT________________________\n";
        cout << "\n\t Car No.\t Car Name\t car quantity\t Price\t Amount\t Amount with Discount\n";

        //iterating over the file to get the cars and generate the prices and receipt
        for (int i = 0; i < c; i++)
        {
            data.open("database.txt", ios::in);
            data >> pcode >> carname >> price >> dis;

            while (!data.eof())
            {
                if (pcode == arrc[i]) //checking if the car key matches with any key in the whole file or not
                {
                    amount = price * arrq[i];
                    dis = amount - (amount * dis / 100);
                    total = total + dis;
                    cout << "\n\t  " << pcode << "\t\t  " << carname << "\t\t" << arrq[i] << "\t\t" << price << "\t" << amount << "\t\t" << dis;
                }
                data >> pcode >> carname >> price >> dis;
                i++;
            }
        }

        data.close();
    }

    cout << "\n\n\t___________________________________________________________";
    cout << "\n\t  Total Amount :  " << total << endl;

}

void car_store::buyer()
{
m: //label for goto statement
    int choice;
    cout << "\t  Buyer Menu \n";
    cout << "\n\t|______1) Buy car_______|";
    cout << "\n\t|                           |";
    cout << "\n\t|______2) Go back___________|";
    cout << endl;

    cout << "\t  Enter your Choice  : ";

    cin >> choice;

    switch (choice)
    {
    case 1:
    {
        receipt();
        break;
    }
    case 2:
    {
        menu();
        break;
    }
    default:
        cout << "\t Invalid Choice !!" << endl;

    }

    goto m;
}