#include<iostream>
#include<string>
using namespace std;

int main()

{
   //The required information for calculating the bill is input here, as either an integer or string.
    
    cout << "Minutes used: ";
    int minutesUsed;
    cin >> minutesUsed;
    
    cout << "Text messages: ";
    int textMessages;
    cin >> textMessages;
    cin.ignore(10000,'\n');
    
    cout << "Customer name: ";
    string customerName;
    getline(cin, customerName);
    
    cout << "Month number (1=Jan, 2=Feb, etc.): ";
    int monthNumber;
    cin >> monthNumber;
    
    cout << "---" << endl;
    
    double monthlyBill;
    monthlyBill = 40.00;
    
    //Calculates the minutesUsed into the bill if the customer goes over the 500 minute limit
    
    if (minutesUsed > 500)
        {
            monthlyBill = monthlyBill + (minutesUsed - 500) * 0.45;
        }
    
    //From October to May, the program calculates the textMessages into the bill from 201 to 400 texts and from over 400 texts, since the rates are different for both ranges.
    
   if (((monthNumber >= 10) && (monthNumber <=12)) || ((monthNumber >= 1) && (monthNumber <= 5)))
       {
           if (textMessages > 200 && textMessages < 401)
           {
            monthlyBill = monthlyBill + (textMessages - 200) * 0.03;
           }
           
           if (textMessages > 400)
           {
               monthlyBill = monthlyBill + 6 + (textMessages - 400) * 0.11;
            }
       }
    
    //From June to September, the program calculates the textMessages into the bill at the special summer rate from 201 to 400 texts and from over 400 texts, since the rates are different for both ranges.
    
    if ((monthNumber >= 6) && (monthNumber <= 9))
        {
            if (textMessages > 200 && textMessages < 401)
            {
                monthlyBill = monthlyBill + (textMessages - 200) * 0.02;
            }
            
            if (textMessages > 400)
            {
                monthlyBill = monthlyBill + 4 + (textMessages - 400) * 0.11;
            }
        }
    
    //The error messages will read here if any of the following conditions are met.
    
    if (minutesUsed < 0)
        {
            cout << "The number of minutes used must be nonnegative. \n";
            return 0;
        }
    
    if (textMessages < 0)
        {
            cout << "The number of text messages must be nonnegative. \n";
            return 0;
        }
    
    if (customerName.length() == 0)
        {
            cout << "You must enter a customer name. \n";
            return 0;
        }
    
    if ((monthNumber < 1) || (monthNumber > 12))
        {
            cout << "The month number must be in the range 1 through 12. \n";
            return 0;
        }
    
    //If all inputs are valid, the following statement will read with the actual amount of the monthlyBill.
    
    cout.setf(ios::fixed);
    cout.precision(2);
    cout << "The bill for " << customerName << " is $" << monthlyBill << endl;
    
}


