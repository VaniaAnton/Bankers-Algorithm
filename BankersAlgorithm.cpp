// C++ Program to Print all possible safe sequences using banker's algorithm
#include <iostream>
#include <string.h>
#include <vector>
// total number of processes
#define P 5
// total number of resources
#define R 4

// total safe-sequences
int total = 0;

using namespace std;

// function to check if process
// can be allocated or not
bool is_available(int process_id, int allocated[][R],
				int max[][R], int need[][R], int available[])
{

	bool flag = true;

	// check if all the available resources
	// are less greater than need of process
	for (int i = 0; i < R; i++) {

		if (need[process_id][i] > available[i])
			flag = false;
	}

	return flag;
}

// Print all the safe-sequences
void safe_sequence(bool marked[], int allocated[][R], int max[][R],
				int need[][R], int available[], vector<int> safe)
{
	for (int i = 0; i < P; i++) {

		// check if it is not marked
		// already and can be allocated
		if (!marked[i] && is_available(i, allocated, max, need, available)) {

			// mark the process
			marked[i] = true;
			// increase the available
			// by deallocating from process i
			for (int j = 0; j < R; j++)
				available[j] += allocated[i][j];

			safe.push_back(i);
			// find safe sequence by taking process i
			safe_sequence(marked, allocated, max, need, available, safe);
			safe.pop_back();

			// unmark the process
			marked[i] = false;

			// decrease the available
			for (int j = 0; j < R; j++)
				available[j] -= allocated[i][j];
		}
	}

	// if a safe-sequence is found, display it
	if (safe.size() == P) {
		total++;
		for (int i = 0; i < P; i++) {

			cout << "P" << safe[i];
			if (i != (P - 1))
				cout << "--> ";
		}
		cout << endl;
	}
}


// Driver Code
int main()
{
    cout<<endl;
    cout<<"Banker's Algorithm"<<endl;
    cout<<"Processes(P) ="<<P<<" Resources(R)="<<R<<" by default, you can change it everytime if you need(in the beginning of the code)"<<endl;
    cout<<"Enter the allocated matrix of size P*R: (row by row)";
    int allocated[P][R];
    for (int i = 0; i < P; i++){
        for (int j = 0; j < R; j++){
            cin >> allocated[i][j];
        }
    }
    cout<<"Enter the max matrix of size P*R: (row by row)";
    int max[P][R];
    for (int i = 0; i < P; i++){
        for (int j = 0; j < R; j++){
            cin >> max[i][j];
        }
    }
    cout<<"Enter total resources of size R: ";
    int resources[R];
    for (int i = 0; i < R; i++){
        cin >> resources[i];
    }
    //print allocated matrix
    cout << "Allocated Matrix is:" << endl;
    for (int i = 0; i < P; i++){
        for (int j = 0; j < R; j++){
            cout << allocated[i][j] << "  ";
        }
        cout << endl;
    }
    //print max matrix
    cout << "Max Matrix is:" << endl;
    for (int i = 0; i < P; i++){
        for (int j = 0; j < R; j++){
            cout << max[i][j] << "  ";
        }
        cout << endl;
    }
    //print resources
    cout << "Resources are:" << endl;
    for (int i = 0; i < R; i++){
        cout << resources[i] << "  ";
    }
    cout << endl;
	// available vector of size R
	int available[R];

	for (int i = 0; i < R; i++) {

		int sum = 0;
		for (int j = 0; j < P; j++)
			sum += allocated[j][i];

		available[i] = resources[i] - sum;
	}
    //print available vector
    cout << "Available vector is:" << endl;
    for (int i = 0; i < R; i++){
        cout << available[i] << "  ";
    }
    cout << endl;

	// safe vector for displaying a safe-sequence
	vector<int> safe;

	// marked of size P for marking allocated process
	bool marked[P];
	memset(marked, false, sizeof(marked));

	// need matrix of size P*R
	int need[P][R];
	for (int i = 0; i < P; i++)
		for (int j = 0; j < R; j++)
			need[i][j] = max[i][j] - allocated[i][j];
    //print need matrix
    cout << "Need Matrix is:" << endl;
    for (int i = 0; i < P; i++){
        for (int j = 0; j < R; j++){
            cout << need[i][j] << "  ";
        }
        cout << endl;
    }
    cout<<"If you need to calculate vector changes, just take one of the folowing safe sequences\n and add processes from allocated vector to available in order"<<endl;
	cout << "Safe sequences are:" << endl;
	safe_sequence(marked, allocated, max, need, available, safe);

	cout << "\nThere are total " << total << " safe-sequences" << endl;
	return 0;
}
