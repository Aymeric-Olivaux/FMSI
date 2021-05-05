#include <iostream>
#include <math.h>

int main(int argc, char *argv[])
{
    for (int i = 0; i < argc; i++)
    {
	std::string arg(argv[i]);
	if (arg == "-h")
	{
	    std::cout 
		<< "Alice & Bob help documentation:\n"
		<< "Please use as described:\n"
		<< ">_   ./AliceEtBob p g message\n"
		<< "Where:\n"
		<< "p is a prime number            (int)\n"
		<< "g is a base                    (int)\n"
		<< "a message u want to serialize  (char*)\n";
	    exit(2);
	}
    }
    if (argc != 2)
    {
	std::cerr << "Bad number of argument! please try the -h flag\n";
	exit(1);
    }

    int p = 23;
    int g = 5;
    std::string message(argv[1]);
    
    int a = 6; //SecretNumberAlice
    int b = 15; //SecretNumberBob

    long A = pow(g, a);
    A = A % p;
    
    long B = pow(g, b);
    B = B % p;


    long skA = pow(B, a); //SecretKeyA
    skA = skA % p;

    long skB = pow(A, b); //SecretKeyB
    skB = skB % p;
    std::cout << "skA: " << skA << " skB: " << skB << '\n';
}


