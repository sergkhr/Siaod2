#include <iostream>

using namespace std;

void coutp(unsigned int x);
void firstTask();
void secondTask();
void thirdTask();
void fourthTask();
void fifthTask();

int main()
{
	cout << "11 variant (Khrechko (29))" << endl;
	cout << "pick task 1-5" << endl;
	//I don't do protection against wront input
	int pick;
	cin >> pick;
	switch (pick)
	{
	case 1:
		firstTask();
		break;
	case 2:
		secondTask();
		break;
	case 3:
		thirdTask();
		break;
	case 4:
		fourthTask();
		break;
	case 5:
		fifthTask();
		break;
	default:
		cout << "wrong input" << endl;
		break;
	}
	return 0;
}

void firstTask()
{
	cout << "first task" << endl;
	unsigned int x = 0xa7;
	unsigned int mask = 0b111100000;

	coutp(x);
	coutp(x | mask);
}

void secondTask()
{
	cout << "second task" << endl;
	unsigned int x;
	cout << "input x" << endl;
	cin >> x;

	unsigned int mask = 0b10100000;
	mask = ~mask;

	coutp(x);
	coutp(x & mask);
}

void thirdTask()
{
	cout << "third task" << endl;
	unsigned int x;
	cout << "input x" << endl;
	cin >> x;

	cout << (x << 5);
}

void fourthTask()
{
	cout << "fourth task" << endl;
	unsigned int x;
	cout << "input x" << endl;
	cin >> x;

	cout << (x >> 5);
}

void fifthTask()
{
	cout << "fifth task" << endl;
	unsigned int x;
	cout << "input x" << endl;
	cin >> x;
	unsigned int mask = 1;
	coutp(x);
	cout << "input n" << endl;
	int n;
	cin >> n;
	
	mask = mask << n;
	coutp(x & (~mask));
}

void coutp(unsigned int x)
{
	int n=sizeof(int)*8;
	unsigned maska=(1<<(n-1));
	for(int i=1; i<=n;i++)
	{
		cout<<((x&maska)>>(n-i));
		maska=maska>>1;
	}
	cout << endl;
}