#include <iostream>

using namespace std;

void coutp(unsigned int x);
unsigned int firstTask(unsigned int x);
unsigned int secondTask(unsigned int x);
unsigned int thirdTask(unsigned int x);
unsigned int fourthTask(unsigned int x);
unsigned int fifthTask(unsigned int x, int n);

int main()
{
	cout << "11 variant (Khrechko (29))" << endl;
	cout << "pick task 1-5" << endl;
	//I don't do protection against wront input
	int pick;
	cin >> pick;
	unsigned int x;
	switch (pick)
	{
	case 1:
		cout << "first task" << endl;
		x = 0x7;
		coutp(x);
		coutp(firstTask(x));
		break;
	case 2:
		cout << "second task" << endl;
		cout << "input x" << endl;
		cin >> x;
		coutp(x);
		coutp(secondTask(x));
		break;
	case 3:
		cout << "third task" << endl;
		cout << "input x" << endl;
		cin >> x;
		cout << thirdTask(x);
		break;
	case 4:
		cout << "fourth task" << endl;
		cout << "input x" << endl;
		cin >> x;
		cout << fourthTask(x);
		break;
	case 5:
		cout << "fifth task" << endl;
		cout << "input x" << endl;
		cin >> x;
		coutp(x);
		cout << "input n" << endl;
		int n;
		cin >> n;
		coutp(fifthTask(x ,n));
		break;
	default:
		cout << "wrong input" << endl;
		break;
	}
	return 0;
}

unsigned int firstTask(unsigned int x)
{
	unsigned int mask = 0b111100000;
	return(x | mask);
}

unsigned int secondTask(unsigned int x)
{
	unsigned int mask = 0b10100000;
	mask = ~mask;
	return(x & mask);
}

unsigned int thirdTask(unsigned int x)
{
	return(x << 5);
}

unsigned int fourthTask(unsigned int x)
{
	return(x >> 5);
}

unsigned int fifthTask(unsigned int x, int n)
{
	unsigned int mask = 1;
	mask = mask << n;
	return(x & (~mask));
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