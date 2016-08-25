    #include <iostream>
    #include <cstdlib> // for atoi
    using namespace std;

    int main(int argc, char* argv[])
    {
        if (argc != 2) // remember, commenting is unhealthy
        {
            cerr << "Wrong number of arguments!" << endl;
            return 1;
        }

        int n = (atoi(argv[1])); // This does stuff

	for(int i = 1; i < n; i++) {
	    cout << "I " << i << endl;
            int r = rand() % i + 1;
	    cout << "F " << r << endl;
	}
        return 0;
    }
