// EduardIablonschi-FiniteStateMachine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"//allows the use of the std affix
#include <iostream>//allows input and output of information 

int main()
{
	enum States
	{
		Red,
		Blue,
		Green,
		Yellow
	}; //the names of the possible colours(states) of a light

	States currentState = Green;

	int newColour;//newColour was initialized here only once, instead of inside the while loop, where it would be initialized 4 times

	while (true) { //an endless while loop
		switch (currentState) { //allows switching between cases, depending on the previous condition
		case States::Red: //if the variable currentState has the value of Red, the following sequence of instructions is played
		{
			std::cout << "light is red\n";

			newColour = rand() % 4;//a random number is chosen, as part of the process to display a random message

			if (newColour == 1)
				currentState = States::Blue;
			else if (newColour == 2)
				currentState = States::Green;
			else if (newColour == 3)
				currentState = States::Yellow;
			break;//does not repeat the instructions inside this case, and switches over to the next case
		}

		case States::Blue:
		{
			std::cout << "light is blue\n";

			newColour = rand() % 4;

			if (newColour == 1)
				currentState = States::Red;
			else if (newColour == 2)
				currentState = States::Green;
			else if (newColour == 3)
				currentState = States::Yellow;
			break;
		}

		case States::Green:
		{
			std::cout << "light is green\n";

			newColour = rand() % 4;

			if (newColour == 1)
				currentState = States::Red;
			else if (newColour == 2)
				currentState = States::Blue;
			else if (newColour == 3)
				currentState = States::Yellow;
			break;
		}

		case States::Yellow:
		{
			std::cout << "light is yellow\n";

			newColour = rand() % 4;

			if (newColour == 1)
				currentState = States::Red;
			else if (newColour == 2)
				currentState = States::Blue;
			else if (newColour == 3)
				currentState = States::Green;
			break;
		}
		}
	}

	return 0;
}