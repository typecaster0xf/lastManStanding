#include <iostream>

using namespace std;

int main()
{
	for(int c = 0; c < 256; c++)
		cout << c << '\t' << static_cast<char>(c) << '\n';
	cout << flush;
	return 0;
}
