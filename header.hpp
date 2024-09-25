#include<iostream>
#include<fstream>

using namespace std;

class car_store {
private:
    int pcode; //product code
    float price;
    float dis; //discount
    string carname; //name of the car

public:
    //public function
    void menu();
    void administrator();
    void add();
};

//declaring the definition of the menu function outside the class using the scope resolution operator
//scope resolution operator helps us in defining the function body outside the class
void car_store::menu()
{
    int choice;
    string email;
    string password;
    while (1) {
        cout << "\t_______________________________________________________________________________\n";
        cout << "\t|                                                                              |\n";
        cout << "\t|                          Car Store Menu                                      |\n";
        cout << "\t|                                                                              |\n";
        cout << "\t|______________________________________________________________________________|\n";
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
        }

        case 3:
        {
            exit(0);//it will mark successfull termination of the programme
            break;
        }
        default:
        {
            cout << "\t\t\t\t\t\t  Please select from the given Options \n";
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
            //edit(); //to modify or edit the existing car
            break;
        }
        case 3:
        {
            //rem(); //to remove the car
            break;
        }
        case 4:
        {
            menu(); //to display the menu
            break;
        }
        default:
            cout << "\t\t\t\t\t\t  Invalid Choice !!";
        }

    }
}

//this function will helps us to add the product in the cart
void car_store::add()
{
m:
    fstream data;
    int c;
    int token = 0;
    float p;
    float d;
    string n;

    cout << "\n\n\t\t\t\t\t\t  Add new product  ";
    cout << "\n\n\t\t\t\t\t\t  Enter Product code ";
    cin >> pcode;
    cout << "\n\n\t\t\t\t\t\t  Name of the Product ";
    cin >> carname;
    cout << "\n\n\t\t\t\t\t\t  Price of the Product ";
    cin >> price;
    cout << "\n\n\t\t\t\t\t\t  Discount on Product  ";
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
            if (c == pcode) //if a product with the same code exists then we will not add it again and thats why we are using token variable to keep count if it already exists or not
            {
                token++;
            }

            data >> c >> n >> p >> d;
        }
        data.close(); //closing the file

        if (token == 1) //if the token value is incremented to 1 it means that the product is already present 
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

    cout << "\n\t\t\t\t\t\t  Record Inserted Successfully !!" << endl;
}