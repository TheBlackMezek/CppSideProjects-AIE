
#include <iostream>



//Is passing arrays bad?
void renderWindow(int blocks[][22], std::string msg);



//Default console size at home is 80x24 characters. Check at AIE.


int main()
{
	std::cout << "Hello world!" << std::endl;

	int blockTest[80][22];
	for (int y = 0; y < 22; ++y)
	{
		for (int x = 0; x < 80; ++x)
		{
			blockTest[x][y] = 1;
		}
	}

	renderWindow(blockTest, "Test message. This has to be very long so that I can test the string resize function. I don't have a clue how many characters I've written in it so far.");

	system("pause");

	return 0;
}


void renderWindow(int blocks[][22], std::string msg)
{
	//Makeshift "clear window"
	std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

	//Renders from top-left to bottom-right
	//The y loop increments backwards here so blocks can be set intuitively elsewhere
	for (int y = 22; y >= 0; --y)
	{
		for (int x = 0; x < 80; ++x)
		{
			if (blocks[x][y] == 0) {
				std::cout << " ";
			}
			else
			{
				//E is for Error
				std::cout << "E";
			}
		}
	}

	//If the msg is longer, it might create a new line, which would hide some of the world render.
	msg.resize(80, ' ');
	std::cout << msg.c_str();
}