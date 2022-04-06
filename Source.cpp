#include <iostream>
#include <vector>
#include <ctime>
#include <conio.h>

#define RIGHT 0
#define DOWN 1
#define LEFT 2
#define UP 3


int main()
{
	srand(time(0));
	//Init values
	std::pair<int, int> field = { 50, 20 };
	std::pair<int, int> snake_head = { field.first / 2, field.second / 2 };
	std::vector<std::pair<int, int>> snake_body = { {(field.first / 2) - 1, field.second / 2}, {(field.first / 2) - 2, field.second / 2} };
	std::pair<int, int> apple = { 1 + (rand() % (field.first - 2)), 1 + (rand() % (field.second - 2)) };
	

	//Logic values
	bool rungame = true;
	bool find_body = false;
	bool direction[4] = { true, false, false, false };

	//Game
	while (rungame)
	{
		//Control
		if (_kbhit()) // if key is down
		{
			switch (_getch())
			{
			case 27: // Key escape
				rungame = false;
				break;
			case 72: // Key up
				if (!direction[DOWN])
				{
					for (int i = 0; i < sizeof(direction) / sizeof(direction[0]); i++)
					{
						if (i == UP)
						{
							direction[i] = true;
						}
						else
						{
							direction[i] = false;
						}
					}
				}
				
				break;
			case 80: // Key down
				if (!direction[UP])
				{
					for (int i = 0; i < sizeof(direction) / sizeof(direction[0]); i++)
					{
						if (i == DOWN)
						{
							direction[i] = true;
						}
						else
						{
							direction[i] = false;
						}
					}
				}
				break;
			case 75: // Key left
				if (!direction[RIGHT])
				{
					for (int i = 0; i < sizeof(direction) / sizeof(direction[0]); i++)
					{
						if (i == LEFT)
						{
							direction[i] = true;
						}
						else
						{
							direction[i] = false;
						}
					}
				}
				break;
			case 77: // Key right
				if (!direction[LEFT])
				{
					for (int i = 0; i < sizeof(direction) / sizeof(direction[0]); i++)
					{
						if (i == RIGHT)
						{
							direction[i] = true;
						}
						else
						{
							direction[i] = false;
						}
					}
				}
				break;

			default:
				break;
			}
		}


		//Render
		system("cls");

		for (int col = 0; col <= field.second; col++)
		{
			for (int row = 0; row <= field.first; row++)
			{
				find_body = false;
				for (int snake_element = 0; snake_element < size(snake_body); snake_element++)
				{
					if (row == snake_body[snake_element].first && col == snake_body[snake_element].second)
					{
						std::cout << "o";
						find_body = true;
					}
				}
				if (row == 0 || row == field.first || col == 0 || col == field.second)
				{
					std::cout << "X";
				}
				else if (row == snake_head.first && col == snake_head.second)
				{
					std::cout << '+';
				}
				else if (row == apple.first && col == apple.second)
				{
					std::cout << '&';
				}

				else if (!find_body)
				{
					std::cout << ' ';
				}
			}
			std::cout << std::endl;
		}
		std::cout << "Snake head position: x=" << snake_head.first << " y=" << snake_head.second << std::endl;
		std::cout << "Apple position: x=" << apple.first << " y=" << apple.second << std::endl;
		std::cout << "Snake lenght: " << size(snake_body) + 1 << " points" << std::endl;		

		//Logic
		// Game over
		if (snake_head.first == 0 || snake_head.first == field.first ||
			snake_head.second == 0 || snake_head.second == field.second)
		{
			rungame = false;
		}
		for (int snake_element = 0; snake_element < size(snake_body); snake_element++)
		{
			if (snake_head == snake_body[snake_element])
			{
				rungame = false;
			}
		}
		
		//Snake eat apple
		snake_body.insert(snake_body.begin(), snake_head);
		if (snake_head == apple)
		{
			apple = { 1 + (rand() % (field.first - 2)), 1 + (rand() % (field.second - 2)) };
		}
		else
		{
			snake_body.pop_back();
		}
		// //Snake body tick
		
		
		
		//Snake head direction
		if (direction[RIGHT])
		{
			snake_head.first++;
		}
		else if (direction[DOWN])
		{
			snake_head.second++;
		}
		else if (direction[LEFT])
		{
			snake_head.first--;
		}
		else if (direction[UP])
		{
			snake_head.second--;
		}
		
		
	}
	system("pause");
}