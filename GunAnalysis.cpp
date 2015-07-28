// Jason Mora
// Engineering 050
// The Gun Analysis 

/*
	The following program is designed to make a compuational analysis of two different
rifles. The rifles are manufactured in the United States and Russia. The analysis will be broken
down into two parts which will also consist of the two seperate classes created to do this analysys.
One class will calculate the overall trajectory of the bullet and this will mainly calculate the bullets
maximum height, the bullets range, and the bullets velocity out the barrel of the respective gun. The 
second class will consist of calculating the the data points throughout the barrel of the gun i.e;
the bullets velocities, the accelerations, and times. 
*/

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;

// Creating a Rifle class that will inherit the properties of the Tracjectory class
class Rifle
{
	// List of public fields and functions in the Rifle class
	public:
		void input_Rifle_Data();		
		void output_Rifle_Data();
		double get_Mass();
		double get_Radius();
		
		double velocity;
		double range;
		double max_height;
		
		double velocities[49];
		double accelerations[49];
		double times[49];
		void set_Data_Arrays(double distances[], double pressures[], int length);
		void TxtPrint_Data(double times[],double velocities[],double accelerations[],int length, ofstream &outputFile);
		void PrntScrn_Velocities(double times[],double pressures[], int length);
		void PrntScrn_Accelerations(double times[],double accelerations[], int length);
		void set_Range(double angle);
		void set_Max_Height(double angle);
		void set_Velocity(double distances[], double pressures[],int length);
		double get_Velocity();
		double get_Range();
		double get_Max_Height();
		
	// List of private fields and functions in the Rifle class
	private:
		string name;
		string manufacturer;
		string country;
		string material;
		string type;
		double radius;
		double mass;
	
};
// End of the Rifle class

// List of functions that will be included in the main funcition
int array_length(std::string input);
void US_Data_Output(int length, Rifle R_one);
void Russian_Data_Output(int length, Rifle R_two);
void US_Prnt_Output(int length, Rifle R_one, std::string input);
void Russian_Prnt_Output(int length, Rifle R_two, std::string input);

// Creating the main method that will run the analysis
int main()
{
	// List of local variables in the main function
	double angle;
	double radians;
	const double PI = 3.1415926538;
	int length;
	string input;
	char ans;

	int choice;

	// Creating the Rifle objects to run my analysis
	Rifle US_M86;
	Rifle Russian_Dragunov;

	// Gets the user to enter information of the rifle
	US_M86.input_Rifle_Data();

	// Creates space
	cout<<endl;

	// Gest the user to enter the information of thee rifle
	Russian_Dragunov.input_Rifle_Data();

	// Creates space between inputs
	cout<<endl;

	// Creating a do-while loop that will loop this program until the user decides to quit
	do
	{
		// Gets the user to enter the angle of the trajectory
		cout<<"Enter the angle of the trajector: ";
		cin>>angle;

		// Ensures that ueer does not enter a negative value
		// for purposes of this experiment, we are only concern with angles between 0 and 90
		while (angle < 0 || angle > 90)
		{
			if (angle < 0 || angle > 90)
			{
				// Sends an error message ot he user
				cout<<"Error. Please enter a value between 0 and 90 degress."<<endl;
			
				// Creates space between inputs
				cout<<endl;

				// Gets the user to re-enter the value for the angle
				cout<<"Please enter a value for the angle: ";
				cin>>angle;
			}
		}

		// Converts the angle into radians
		radians = angle * (PI / 180);
		
		// Creates space between inputs
		cout<<endl;
		
		// Gets the user to enter the name of the text file of data
		cout<<"Enter the name of the text file of data: ";
		cin.ignore();
		getline(cin,input);

		// Creates space between inputs
		cout<<endl;

		// Creating the ifstream function
		ifstream inputFile;
		
		// Opens the text file of data
		inputFile.open(input.c_str());

		// Creating a function that will get the lenght of data
		length = array_length(input);;

		// Declaring a dynamic array that will have length data file
		double *US_Pressures = new double[length];
		double *RUS_Pressures = new double[length];
		double *distances = new double[length];

		// Creating a loop that will enter the data into their respective arrays
		for (int index = 0; index < length; index++)
		{
			inputFile>>distances[index]>>US_Pressures[index]>>RUS_Pressures[index];
		}

		// Calling the function that will calculate the velocity of the bullet
		// for both rifles
		US_M86.set_Velocity(distances,US_Pressures,length);
		Russian_Dragunov.set_Velocity(distances,RUS_Pressures,length);
		
		// Calling the functions that will calculate the range of the function
		// for both rifles
		US_M86.set_Range(angle);
		Russian_Dragunov.set_Range(angle);

		// Calling the function that will calcualte the maximum height of the bullet
		// for both rifles
		US_M86.set_Max_Height(angle);
		Russian_Dragunov.set_Max_Height(angle);
		
		// Calls the functions that will create the arrays for the analysis in the barrel
		US_M86.set_Data_Arrays(distances,US_Pressures,length);
		Russian_Dragunov.set_Data_Arrays(distances,RUS_Pressures,length);
		
		// Gets the users input to see if they wish to print on screen or into a text file
		cout<<endl;
		cout<<endl;
		cout<<endl;
		cout<<"How would you like your data presented?"<<endl;
		cout<<"---------------------------------------"<<endl;
		cout<<"Print data on the screen (1)"<<endl;
		cout<<"Print data on a text file (2): "<<endl;
		cout<<"---------------------------------------"<<endl;
		cout<<"Enter your choice: ";
		cin>>choice;
		
		// Ensures that user does not enter a bigger than the menu
		while (choice < 1 || choice > 2)
		{
			if (choice < 1 || choice > 2) 
			{
				// Sends an error message to the user
				cout<<"Error! This is not a selection from the menu."<<endl;
				
				// Creates space
				cout<<endl;
				
				// Gets the user to re-enter the value from the menu
				cout<<"Please enter a value from the menu: ";
				cin>>choice;
			}
		}
		
		// Creates space between inptus
		cout<<endl;
		cout<<endl;
		cout<<endl;
		cout<<endl;
		cout<<endl;
		cout<<endl;
		cout<<endl;
		
		// Creaitng a switch statement that will determine how the user will get their analysis
		switch (choice) 
		{
			// Case 1 will print out the values onto the screen
			case 1:
			{
				// Calls the function that will print out the values for the US rifle
				cout<<"\t\tThe information and data for the first rifle"<<endl;
				US_Data_Output(length,US_M86);
			
				// Creates space
				cout<<endl;
				cout<<endl;
				cout<<endl;
				cout<<endl;
				
				// Calls the function that will print out the values for the Russian Rifle
				cout<<"\t\tThe information and the data for the second rifle"<<endl;
				Russian_Data_Output(length,Russian_Dragunov);
				
				// Breaks out of this case
				break;
			}

			// Case 2 will print out the values into text file that the user will input
			case 2:
			{
				// List of local variables inside Case 2
				string US_Data;
				string RUS_Data;
				
				// Gets the user to enter the names of the text files
				cout<<endl;
				cout<<endl;
				cout<<endl;
				cout<<endl;
				cout<<endl;
				cout<<endl;
				cout<<"When saving the data, the following information will be included:"<<endl;
				cout<<"** Gun Information"<<endl;
				cout<<"** The Trajectory Data"<<endl;
				cout<<"** The Times and Velocities"<<endl;
				cout<<"** The Times and Accelerations"<<endl;
				cout<<endl;
				cout<<endl;
				cout<<"Enter a name to save the data for the first rifle: ";
				getline(cin,US_Data);
				cin.ignore();
				cout<<endl;
				cout<<"Enter a name to safve the data for the second rifle: ";
				getline(cin,RUS_Data);
				cin.ignore();
				
				// Calling the function that will print out the data into text files
				US_Prnt_Output(length,US_M86,US_Data);
				Russian_Prnt_Output(length,Russian_Dragunov,RUS_Data);
				
				// Breaks out of this case
				break;
			}
		}
		
		// Gets the user to enter the answer if he wants to continue with the program
		cout<<"Would you like to run another analysis?"<<endl;
		cout<<"Enter (Y/N): ";
		cin>>ans;

		// Ensures that user input is upper cased
		ans = toupper(ans);

		cout<<endl;
		cout<<endl;

	} while(ans == 'Y' || ans == 'y');

	// Closes the function
	return 0;
}
// End of the main function

// Creating a function that will calculate the lenght of the array
int array_length (string input)
{
	// List of local variables in the array_length function
	int length = 0;
	double dummy;

	// Creating the ifstream function that will read input
	ifstream inputFile;
	
	// Opens the text file of data
	inputFile.open(input.c_str());

	// Creating a loop that will calculate the length of the array
	while (!inputFile.eof())
	{
		inputFile>>dummy>>dummy>>dummy;
		length++;
	}

	// Closes the text file
	inputFile.close();

	// Returns the length of the array
	return length;
}
// End of the array_length function

// Creating a function that will print out the values of the US data
void US_Data_Output(int length, Rifle US_M86)
{
	
	cout<<"**********************************************************************"<<endl;
	US_M86.output_Rifle_Data();
	cout<<endl;
	cout<<endl;
	cout<<"\tThe Trajectory of the bullet"<<endl;
	cout<<"--------------------------------------"<<endl;
	cout<<"The velocity of the bullet: "<<US_M86.get_Velocity()<<endl;
	cout<<"The Range of the bullet: "<<US_M86.get_Range()<<endl;;
	cout<<"The Maximum Height of the bullet: "<<US_M86.get_Max_Height()<<endl;;
	cout<<endl;
	cout<<endl;
	US_M86.PrntScrn_Velocities(US_M86.times,US_M86.velocities,length);
	cout<<endl;
	cout<<endl;
	US_M86.PrntScrn_Accelerations(US_M86.times,US_M86.accelerations,length);
}
// End of the US_Data_Output.

// Creating a function that will print out the values of the Russian data
void Russian_Data_Output(int length, Rifle Russian_Dragunov)
{
	
	cout<<"**********************************************************************"<<endl;
	Russian_Dragunov.output_Rifle_Data();
	cout<<endl;
	cout<<endl;
	cout<<"--------------------------------"<<endl;
	cout<<"The velocity of the bullet: "<<Russian_Dragunov.get_Velocity()<<endl;
	cout<<"The Range of the bullet: "<<Russian_Dragunov.get_Range()<<endl;
	cout<<"The Maximum Height of the bullet: "<<Russian_Dragunov.get_Max_Height()<<endl;
	cout<<endl;
	cout<<endl;
	Russian_Dragunov.PrntScrn_Velocities(Russian_Dragunov.times,Russian_Dragunov.velocities,length);
	cout<<endl;
	cout<<endl;
	Russian_Dragunov.PrntScrn_Accelerations(Russian_Dragunov.times,Russian_Dragunov.accelerations,length);
}
// End of the Russian_Data_Output function

// Creating a function that will print out the values into a text file for the first rifle
void US_Prnt_Output(int length, Rifle US_M86,string input)
{
	// Creating the ofstream function that will print out the data into a text file
	ofstream US_Write;
	
	// Opens the text file of data
	US_Write.open(input.c_str());
	
	// Calls the function that will print out the data into the text file
	US_M86.TxtPrint_Data(US_M86.times,US_M86.velocities,US_M86.accelerations,length,US_Write);
}

// Creating a function that will print out the values into a text file for the second rifle
void Russian_Prnt_Output(int length,Rifle Russian_Dragunov,string input)
{
	// Creating the ofstream function that will print out the data into a text file
	ofstream RUS_Write;
	
	// Opens the text file of data
	RUS_Write.open(input.c_str());
	
	// Calls the function that will print out the values into a text file
	Russian_Dragunov.TxtPrint_Data(Russian_Dragunov.times,Russian_Dragunov.velocities,Russian_Dragunov.accelerations,length,RUS_Write);
}


/*
	The following functions are functions created for the entire class, these functions are 
are for all the classes that were created for the making of this analysis.

*/

// Gets the user to enter the information of the gun.
void Rifle::input_Rifle_Data()
{	
	// Gets the user to enter the name of the gun
	cout<<"Enter the name of the gun: ";
	getline(cin,name);

	// Creates space
	cout<<endl;
	
	// Gets the user to enter the manufacturers name
	cout<<"Enter the name of the manufacture: ";
	getline(cin,manufacturer);

	// Creates space
	cout<<endl;

	// Gets the user to enter the country in which its made
	cout<<"Enter the country of origin of the gun: ";
	getline(cin,country);

	// Creates space
	cout<<endl;
	
	// Gets the user to enter the material the gun is made out of
	cout<<"Enter the name of material your gun is made out of: ";
	getline(cin,material);

	// Creates space
	cout<<endl;

	// Gets the user to enter the type of gun it is
	cout<<"Enter the classification of the weapon: ";
	cin.ignore();
	getline(cin,type);

	// Creates space
	cout<<endl;
	
	// Gets the user to enter the mass of the bullet
	cout<<"Enter the mass of the bullet: ";
	cin>>mass;

	// Ensures that the user does not enter negative values for the mass
	while (mass < 0)
	{
		if (mass < 0)
		{
			// Sends an error message to the user
			cout<<"Error! Please enter positive values for the mass of the bullet."<<endl;
		
			// Creates space
			cout<<endl;

			// Gets the user to re-enter the mass of the bullet
			cout<<"Please re-enter the value of the bullet: ";
			cin>>mass;
		}
	}

	// Creates space between inputs
	cout<<endl;

	// Gets the user to enter the radius of the bullet
	cout<<"Enter the radius of the bullet: ";
	cin>>radius;

	// Ensures that the user does not enter negative values for the radius
	while (radius < 0)
	{
		if (radius < 0)
		{
			// Sends an message to the user
			cout<<"Error! Please enter positive values for the radius of the bullet."<<endl;
			
			// Creates space between inputs
			cout<<endl;

			// Gets the user to re-enter the value of the radius
			cout<<"Please re-enter the value of the radius: ";
			cin>>radius;
		}
	}
	
	// Creates space
	cout<<endl;
	
	// Consumes the next line
	cin.ignore();
}
// End of the input function

// Creating a function that will print out the infromation of the rifle
void Rifle::output_Rifle_Data()
{
	cout<<"The name of the gun: "<<name<<endl;
	cout<<"The manufacture of the gun: "<<manufacturer<<endl;
	cout<<"The country of origin: "<<country<<endl;
	cout<<"The gun's material is: "<<material<<endl;
	cout<<"The type of gun: "<<type<<endl;
	cout<<"The mass of the bullet the gun uses: :"<<mass<<endl;
	cout<<"The radius of the bullet the gun uses: "<<radius<<endl;
	
}

// Creating a function that will calculate the velocity of the bullet
// To calculate the velocity, the Simpson's Rule algorithm was used as a numerical integration technique
void Rifle::set_Velocity(double distances[], double pressures[], int length)
{
	// List of local variables in the set_velocity function
	const double PI = 3.1415926538;
	double mass = get_Mass();
	double radius = get_Radius();
	double area;
	double even_sum = 0;
	double odd_sum = 0;
	double alpha;
	double first_last_sum;
	double delta;
	
	// Calculates the first element and the last element for the total sum
	first_last_sum = pressures[length - 1] + pressures[0];
	
	// Calculates the value for delta;
	delta = (2 *.0127) / (3 * length);
	
	// Calculates the area of the tail of the bullet
	area = PI * pow(radius,2);
	
	// Calculates the the value for alpha
	alpha = (area / mass) * delta;

	// Creating a loop that will calculate the total pressures
	for (int index = 1; index < length - 1; index++)
	{
		if (index % 2 == 0)
		{
			even_sum += 2 * pressures[index];
		}
		else
		{
			odd_sum += 4 * pressures[index];
		}
	}
	

	// Calculates the velocity of the bullet
	velocity = alpha * (first_last_sum + even_sum + odd_sum);
}
// End of the set_velocity function

// Creating a function that will calculate the maximum height of the bullet
void Rifle::set_Max_Height(double angle)
{
	// List of local variables in the set_max_height function
	const double g = 9.8;
	double velocity = get_Velocity();

	// Calculates the max height of the bullet
	max_height = 0.5 * velocity * sin(2*angle) / g;
}
// End of the set_Max_Height function

// Creating a function that will calcluate the range of the bullet
void Rifle::set_Range(double angle)
{
	// List of local variables in the set_range function
	const double g = 9.8;
	double velocity = get_Velocity();
	
	// Calculates the value for the range of the bullet
	range = pow(velocity,2) * pow(sin(2*angle),2) / g;
}
// End of the set_range function

// Creating a fucntion that will create the arrays for the following variables:
// The velocities, the accerlations, the times
void Rifle::set_Data_Arrays(double distances[], double pressures[], int length)
{
	// List of local variables in the set_Data_Arrays function
	double mass = get_Mass();
	double radius = get_Radius();
	double area;
	const double PI = 3.1415926538;
	
	// Calculates the area of the cross section of the bullet
	area = PI * pow(radius,2);
	
	// Calculates the velocities at the first and last element
	velocities[0] = 0.5 *(area / mass) * pressures[0] * distances[0];
	velocities[length - 1] = 0.5 * (area / mass) * (pressures[length - 1] + pressures[length - 2]) * (distances[length - 1] - distances[length - 2]);
	
	// Calculates the velocities at every point in the barrel, stores them into an array
	for (int index = 1; index < length - 1; index++)
	{
		velocities[index] = (area / mass) * (pressures[index + 1] + pressures[index]);
	}
	
	// Calculates the acclerations for the first and last element
	accelerations[0] = pow(velocities[0],2)  / distances[0];
	accelerations[length - 1] = (pow(velocities[length - 1],2) - pow(velocities[length - 2],2))  / (distances[length - 1] - distances[length -2] - 2);
		
	// Calculates the accelerations at every point in the barrel, stores them into an array
	for (int index = 1; index < length - 1; index++)
	{
		accelerations[index] = (0.5) *  (pow(velocities[index + 1],2) - pow(velocities[index],2)) / (distances[index + 1] - distances[index]);
	}
	
	
	
	// Calcalutes the times at every point in the barrel, store them into an array
	for (int index = 0; index < length; index++)
	{
		times[index] = (velocities[index + 1] - velocities[index]) / accelerations[index];
	}
}
// End of the set_Data_Arrays fucntion

// Creating a function that will get the mass of the bullet
double Rifle::get_Mass()
{
	return mass;
}
// End of the get_Mass function

// Creating a function that will get the radius of the bullet
double Rifle::get_Radius()
{
	return radius;
}
// End of the get_Radius function

// Creating the function that will get the velocity
double Rifle::get_Velocity()
{
	return velocity;
}
// End of the get_Velocity function

// Creating a function that will get the range
double Rifle::get_Range()
{
	return range;
}
// End of the get_Range function
	
// Creating a function that will get the maximum height
double Rifle::get_Max_Height()
{
	return max_height;
}
// End of the get_Max_Height function

// Creating a fucntion that will print out the velocities on the screen
void Rifle::PrntScrn_Velocities(double times[], double velocities[], int length)
{
	cout<<"\t\tVelocities Inside the Gun Barrel"<<endl;
	cout<<"Time\t\t    Velocites"<<endl;
	cout<<"-----------------------------------------------------"<<endl;
	for (int index = 0; index < length; index++)
	{
		cout<<times[index]<<"\t\t"<<velocities[index]<<endl;
	}
}
// End of the PrntScrn_Velocities

// Creating a function that will print out the accelerations on the screen
void Rifle::PrntScrn_Accelerations(double times[], double accelerations[], int length)
{
	cout<<"\t   Accelerations Inside the Gun Barrel"<<endl;
	cout<<"Time\t\t   Accelerations"<<endl;
	cout<<"-----------------------------------------------------"<<endl;
	for(int index = 0; index < length; index++)
	{
		cout<<times[index]<<"\t\t"<<accelerations[index]<<endl;
	}
}
// End of the PrntScrn_Accelerations function

// Creating a fucntion that will print out the velocities into the text file
void Rifle::TxtPrint_Data(double times[], double velocities[], double accelerations[], int length, ofstream& outputFile)
{
	outputFile<<"\t\tVelocities Inside the Gun Barrel"<<endl;
	outputFile<<"Time\t\t    Velocites"<<endl;
	outputFile<<"-----------------------------------------------------"<<endl;
	for (int index = 0; index < length; index++)
	{
		outputFile<<times[index]<<"\t\t"<<velocities[index]<<endl;
	}
	
	// Creates space between inputs
	outputFile<<endl;
	outputFile<<endl;
	outputFile<<endl;
	outputFile<<endl;
	outputFile<<endl;
	outputFile<<endl;
	outputFile<<endl;
	
	outputFile<<"\t   Accelerations Inside the Gun Barrel"<<endl;
	outputFile<<"Time\t\t   Accelerations"<<endl;
	outputFile<<"-----------------------------------------------------"<<endl;
	for(int index = 0; index < length; index++)
	{
		outputFile<<times[index]<<"\t\t"<<accelerations[index]<<endl;
	}
	
	// Closes the text file of data
	outputFile.close();
}
// End of the TxtPrn_Velocities function