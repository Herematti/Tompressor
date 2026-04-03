#include "progressbar.hpp"
#define WIDTH 15

void generate_progressbar(const string message)
{
	cout << message << ": \n";
	for (int i = 0; i < WIDTH; i++)
	{
		cout << "-";
	}
	cout << "\r";
	cout.flush();
}

void update_progressbar(const int progress, const int base)
{

	if (base < WIDTH || progress % (base / WIDTH) != 0)
		return;

	int fill = (int)((double(progress) / base) * WIDTH);

	for (int i = 0; i < fill; i++)
	{
		cout << "#";
	}
	for (int i = 0; i < WIDTH - fill - 1; i++)
	{
		cout << "-";
	}
	cout << "\r";
	cout.flush();
}

void force_finish_progressbar()
{
	for (int i = 0; i < WIDTH; i++)
	{
		cout << "#";
	}
	cout << "\n";
}
