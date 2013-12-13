/*******************************************************************************************
 *FILENAME    :ElectricityCalculator													   *
 *PROGRAMMER  :Timothy Wiggins															   *
 *PURPOSE     :This program figures the total amount of an eletric bill, with discounts    *
 *				when needed, and then figures the total amount of all bills and kwh used.  *
 *																						   *
 *******************************************************************************************/


#include <iostream>
#include <string>
#include <iomanip>
using namespace std;


//function prototypes
string get_cust_ID();
double get_cust_kwh();
double calc_charge(double &kwhUsed);
double gold_star_deduct(string custId, double totCost);
char getKeepLooping();
void display_cust_data(double totCost, double kwhUsed, string custId);
void display_final_report(int custAcc, double kwhUsedAcc, double averageKwh, double totCostAcc);


int main ()
{
	// Declarations
	string custId, goldStar, clear;
	char keepLooping = ' ';
	int custAcc = 0;
	double totCost = 0.0, averageKwh = 0.0, totCostAcc = 0.0, kwhUsed, kwhUsedAcc = 0.0;

	//Loop, Calling Functions, and Accumulators
	do //begin looping
	{
		//initialize functions
		custId = get_cust_ID();
		cout << endl;
		kwhUsed = get_cust_kwh();
		cout << endl;
		totCost = calc_charge(kwhUsed);

		cout << "THIS IS TOTAL COST" << kwhUsed << endl;
		totCost = gold_star_deduct(custId, totCost);

		cout << fixed << setprecision(2) << endl << endl;

		//Current Customer Data Output
		display_cust_data(totCost, kwhUsed, custId);

	    //Inputs 
		keepLooping = getKeepLooping();
		getline(cin, clear);
		cout << endl << endl;
		custAcc += 1;
		kwhUsedAcc += kwhUsed;
		totCostAcc += totCost;
	}	while (toupper(keepLooping) == 'Y');

	//Average KWH's 
	averageKwh = kwhUsedAcc / custAcc;

	//Clear Screen
	system("cls");

	//Final Output
	display_final_report(custAcc, kwhUsedAcc, averageKwh, totCostAcc);

	system("pause");
	return 0;
}


//***********************Function definitions***********************************

/******************************************************************************
*Purpose: To get the customer Id											  *
*Passed In: Nothing                                                           *
*Returned: Customer Id                                                        *
*******************************************************************************/

string get_cust_ID()
{
	//Declarations
	string response;
		cout << "Please enter the three digit customer id " << endl;
		getline(cin, response);
		return response;
}//End of get customer id function




/******************************************************************************
*Purpose: To get the customers amount of kwh's used                           *
*Passed In: Nothing                                                           *
*Returned: Customer's KWH used                                                *
******************************************************************************/

double get_cust_kwh()
{
	//Declarations
		double response;
		cout << "Please enter the kwh's used: " << endl;
		cin >> response;
		return response;
}//End of get customer kwh used function




/******************************************************************************
*Purpose: To get the total cost of electicity bill                            *  
*Passed In: kwhUsed                                                           *
*Returned: totCost(which is the total cost of the bill)                       *
******************************************************************************/

double calc_charge(double &kwhUsed)
{
	//Declarations
	const double firstRate = .12;
	const double secondRate = .09;
	const double thirdRate = .06;
	const double fourthRate = .04;
	double totCost = 0.0, firstCost, secondCost, thirdCost, fourthCost, newKwh;

			//Conditions and Calculations
			if (kwhUsed <= 300)
			{
				totCost = kwhUsed * firstRate;
			}
			else if (kwhUsed <=600)
			{
				firstCost = 300 * firstRate;
				newKwh = kwhUsed - 300;
				secondCost = newKwh * secondRate;
				totCost = firstCost + secondCost;
			}
			else if (kwhUsed <= 1000)
			{
				firstCost = 300 * firstRate;
				secondCost = 300 * secondRate;
				newKwh = kwhUsed - 600;
				thirdCost = newKwh * thirdRate;
				totCost = firstCost + secondCost + thirdCost;
			}
			else 
			{
				firstCost = 300 * firstRate;
				secondCost = 300 * secondRate;
				thirdCost = 400 * thirdRate;
				newKwh = kwhUsed - 1000;
				fourthCost = newKwh * fourthRate;
				totCost = firstCost + secondCost + thirdCost + fourthCost;
			} // end if

	kwhUsed = 300;
	return totCost;
}//End of calc_charge function




/******************************************************************************
*Purpose:To check in eligable for discount and then calculate                 *
*Passed In: custId, totCost                                                   *
*Returned: The new total cost                                                 *
*******************************************************************************/

double gold_star_deduct(string custId, double totCost)
{ 
	//Declarations
	double discountAmount; 
	string goldStar;

	goldStar = custId.substr(0, 1);

	//Condition for Gold Star Members
	if (goldStar == "8" || goldStar == "9")
	{
		discountAmount = totCost * 0.05;
		totCost -= discountAmount;
	}//End if

	return totCost;
}//End of Gold Star Deduct Function




/******************************************************************************
*Purpose: To display the current customer's data                              *
*Passed In: totCost, kwhUsed, custId                                          *
*Returned: Nothing                                                            *
******************************************************************************/

void display_cust_data(double totCost, double kwhUsed, string custId)
{
		cout << "Cust_ID" << "	       " << "KWHours" << "	         " << "Charge ($) " << endl;
		cout << "    " << custId << "          " << kwhUsed << "              " << totCost << endl << endl << endl;
}//End Display of Current Customer's Data




/*******************************************************************************
*Purpose: To keep looping or not                                               *
*Passed In: Nothing                                                            *
*Returned: respone(Which is whether or not to keep looping)                    *
*******************************************************************************/

char getKeepLooping()
{
	char response;
	cout << "Would you like to enter another customer? Y/N" << endl;
	cin >> response;
	return response;
}//End of Keep Looping Function




/******************************************************************************
*Purpose: To display the final output                                         *
*Passed In: custAcc, kwhUsedAcc, averageKwh, totCostAcc                       *
*Returned: Nothing                                                            *
******************************************************************************/

void display_final_report(int custAcc, double kwhUsedAcc, double averageKwh, double totCostAcc)
{

	cout << "Total Customers" << "   " << "Total Kilowatt-hours" << "   " << "Kilowatt Average" << "   " << "Total Charges ($)" << endl;
	cout << "             " << custAcc << "                  " << kwhUsedAcc << "            " << averageKwh <<  "          " << totCostAcc << endl << endl;

}//End of Final Output Function
