#include <iostream>
#include <cstring>
#include <math.h>
#include <fstream>

void argument(int argc, char *argv[])
{
    for (int i = 0; i < argc; i++)
    {
	std::string arg(argv[i]);
	if (arg == "-h")
	{
	    std::cout 
		<< "Alice & Bob help documentation:\n"
		<< "Please use as described:\n"
		<< ">_   ./AliceEtBob p g message (-p)\n"
		<< "Where:\n"
		<< "p is a prime number            (int)\n"
		<< "g is a base                    (int)\n"
		<< "a message u want to serialize  (char*)\n";
	    exit(2);
	}
    }
    if (argc > 3)
    {
	std::cerr << "Bad number of argument! please try the -h flag\n";
	exit(1);
    }
}


int main(int argc, char *argv[])
{
    argument(argc, argv);

    int printflag = 0;

    if (argc >= 3)
    {
        std::string temp = std::string(argv[1]);
        std::string temp2 = std::string(argv[2]);

        if ((temp.compare("-p") != 0) &&  (temp2.compare("-p") != 0))
        {
            std::cerr << "Bad argument! please try the -h flag\n";
            return 1;
        }

        else
            printflag = 1;
    }

    int p = 23; //prime
    int g = 5; //generator
    
    int a = 6; //SecretNumberAlice
    int b = 15; //SecretNumberBob

    long A = pow(g, a); //g^a
    A = A % p;
    
    long B = pow(g, b); //g^b
    B = B % p;


    long skA = pow(B, a); //SecretKeyA
    skA = skA % p;

    long skB = pow(A, b); //SecretKeyB
    skB = skB % p;

    if(printflag)
    std::cout << "skA: " << skA << " skB: " << skB << '\n';

    //Chiffrement
    char* message = argv[1];
    if ((argc > 2) && (std::string(argv[1]).compare("-p")) == 0){
    message = argv[2]; 
    }

    char* encrypted = message;
    for (size_t i = 0; i < strlen(message); i++)
    {
	encrypted[i] = message[i] + skB;
    }
    std::cout << "Encrypted message: " << encrypted << "\n";

    std::ofstream flux("hacked.txt");
    if (!flux)
	std::runtime_error("Cannot open the file\n");

    flux << p << '\n';
    flux << g << '\n';
    flux << A << '\n';
    flux << B << '\n';
    flux << encrypted << '\n';
    return 0;


}

