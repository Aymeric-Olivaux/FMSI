#include <iostream>
#include <stdio.h>
#include <cstring>
#include <math.h>
#include <fstream>
#include <string>


void new_xab( int &x, int &a, int &b, int n, int N, int alpha, int beta) {
    switch( x%3 ) {
	case 0: x = x*x     % N;  a =  a*2  % n;  b =  b*2  % n;  break;
	case 1: x = x*alpha % N;  a = (a+1) % n;                  break;
	case 2: x = x*beta  % N;                  b = (b+1) % n;  break;
    }
}



int main(int argc, char *argv[])
{
    int printflag = 0;

    if (argc >= 2)
    {
        if (std::string(argv[1]).compare("-p") != 0)
        {
            std::cout << "Usage : -p option to print detail" << std::endl;
            return 1;
        }
        else
            printflag = 1;
    }

    std::ifstream flux("hacked.txt");

    int p;
    int g;
    int ga;
    int gb;
    std::string encrypted;

    flux >> p;
    flux >> g;
    flux >> ga;
    flux >> gb;

    if (printflag){
    std::cout << "p: " << p << '\n';
    std::cout << "g: " << g << '\n';
    std::cout << "g^a: " << ga  << '\n';
    std::cout << "g^b " << gb << "\n\n";
    }

    flux >> encrypted;

    int n = p - 1; //n l'odre du groupe;

    int x=1, a=0, b=0;
    int X=x, A=a, B=b;
    for(int i = 1; i < n; ++i ) {
	new_xab( x, a, b, n, p, g, gb );
	new_xab( X, A, B, n, p, g, gb );
	new_xab( X, A, B, n, p, g, gb );

        if (printflag)
	printf( "%3d  %4d %3d %3d  %4d %3d %3d\n", i, x, a, b, X, A, B );

	if( x == X ) break;
    }
    double gamma = (a - A) / (B - b);
    if (printflag){
    std::cout << "a: " << a << "\n";
    std::cout << "b: " << b << "\n";
    std::cout << "A: " << A << "\n";
    std::cout << "B: " << B << "\n";
    }
    if (gamma < 0)
	gamma += n;
    if (printflag)
    std::cout << "Gamma: " << gamma << "\n";

    long key = pow(ga, gamma);
    key = key % p;

    if (printflag)
    std::cout << "key: " << key << '\n';

    char *message = new char[encrypted.length() + 1];
    strcpy(message, encrypted.c_str());

    for (size_t i = 0; i < strlen(message); i++)
    {
	message[i] = encrypted[i] - key;
    }

    std::cout << "Decrypted Message: " << message << "\n";

    delete [] message;

    return 0;
}
