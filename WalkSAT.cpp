// #include <bits/stdc++.h>
#include "bits/stdc++.h"
#include<random>

using namespace std;

int m, n;		//m - No. of variables, n - No. of clauses
vector < vector <int> > clauses(1000);		//Vector to store clauses read from input file
vector <int> M(1000);		//M - Assignment
set <int> S;		//Set of variables appearing in false clauses

void read_input_dimacs() {		//Function to read input file in DIMACS format

	int temp;
  	string token, type, ignore;
	ifstream reader("input.txt");		//Input file in DIMACS format
	  		
	if(!reader) {
	    cout << "Error opening input file" << endl;
	    exit(0);
  	}

	while(!reader.eof()){
	  	reader >> token;
	  	if(token == "c") {
	  		// cout << "c found!"<<endl;
	  		getline(reader, ignore);
	  	}
	  	else if(token == "p") {
	  		// cout << "p found" << endl;
	  		reader >> type;
	  		reader >> n;
	  		reader >> m;
	  		cout << "m: " << m << endl << "n: " << n << endl;
	  		int i=0;
	  		while(i<m) {
	  			reader >> temp;
	  			if(temp != 0)
	  				clauses[i].push_back(temp);
	  			else
	  				i++;
	  		}
	  	}
	}

	// cout<<"Clauses: "<<endl;
 //  	for(int i=0; i<m; i++) {
 //  		for(int j=0; j<clauses[i].size(); j++) {
 //  			cout<<clauses[i][j]<<" ";
 //  		}
 //  		cout<<endl;
 //  	}

}

void generate_random_M() {		//Function to generate random initial assignment
	
	int temp_array[n];
	for(unsigned i=0; i<n; i++) {
		temp_array[i] = i;
	}
	srand ( unsigned ( std::time(0) ) );
	random_shuffle(temp_array, temp_array + n);		//Temp Array of random indices
	int random_no = (rand()%n)+1;
	for(int i=0; i<random_no; i++) {		//Random number of indices are assigned with True value to generate random assignment
		M[temp_array[i]] = 1;
	}
	cout<<"Randomly Generated Assignment: "<<endl;
	for(int i=0; i<n; i++) {
		cout<<M[i]<<" ";
	}
	cout<<endl;

}

void check_sat() {		//Function for testing
	int temp_array[250] = {-1, -2, 3, 4, 5, 6, -7, 8, 9, -10, -11, 12, 13, 14, -15, 16, -17, 18, -19, 20, 21, -22, -23, 24, -25, -26, -27, 28, -29, -30, -31, -32, 33, 34, -35, 36, -37, -38, 39, -40, -41, -42, -43, 44, -45, -46, 47, -48, -49, 50, 51, -52, -53, -54, -55, -56, 57, 58, 59, 60, -61, 62, -63, -64, 65, 66, 67, -68, -69, -70, -71, -72, -73, 74, -75, -76, 77, 78, 79, -80, 81, -82, -83, -84, -85, 86, -87, -88, -89, 90, 91, 92, -93, 94, 95, 96, 97, -98, 99, 100, -101, -102, 103, 104, -105, -106, -107, 108, -109, 110, 111, -112, 113, -114, -115, 116, -117, 118, -119, 120, 121, -122, 123, 124, -125, 126, 127, -128, 129, 130, 131, -132, 133, -134, -135, 136, 137, -138, 139, -140, -141, -142, -143, 144, -145, 146, 147, -148, 149, 150, -151, -152, -153, -154, 155, -156, -157, -158, 159, 160, -161, -162, 163, -164, 165, -166, -167, -168, 169, -170, -171, -172, -173, -174, -175, 176, 177, 178, 179, 180, -181, -182, 183, 184, 185, 186, 187, -188, 189, -190, -191, -192, -193, -194, 195, 196, 197, 198, -199, -200, -201, 202, -203, 204, -205, 206, -207, -208, -209, -210, -211, 212, -213, 214, -215, 216, -217, -218, 219, 220, 221, -222, -223, 224, 225, 226, 227, 228, 229, -230, 231, -232, -233, -234, 235, -236, -237, -238, -239, -240, -241, 242, -243, 244, 245, -246, -247, 248, -249, 250};
	for(int i=0; i<n; i++) {
		if(temp_array[i] < 0) {
			M[i] = 0;
		}
		else M[i] = 1;
	}
}

bool satisfies() {		//Function to check if the clauses are satisfied

	int result = 1;
	for(int i=0; i<m; i++) {		//Iterate over all the clauses
		for(int j=0; j<clauses[i].size(); j++) {		//Iterate over all the variables
			if(clauses[i][j] < 0) {
				result = 1-M[abs(clauses[i][j])-1];
			}
			else {
				result = M[abs(clauses[i][j])-1];
			}
			if(result == 1) {		//If atleast one variable in the clause is true, break as the clause is satisfied
				break;
			}
		}
		if(result == 0) {		//If all the variables in a clause are false, return false
			return false;
		}
	}
	return true;		//If all clauses are satisfied, return true

}

void display_sat() {		//Function to display the satisfying assignment
	cout<<"SAT ";
	for(int i=0; i<n; i++) {
		if(M[i] == 0) {
			cout<<"-"<<i+1<<" ";
		}
		else {
			cout<<i+1<<" ";
		}
	}
	cout<<endl;
}

void find_variables_in_false_clauses() {		//Function to find variables in false clauses
	
	S.clear();
	int result = 1;
	for(int i=0; i<m; i++) {
		for(int j=0; j<clauses[i].size(); j++) {
			if(clauses[i][j] < 0) {
				result = 1-M[abs(clauses[i][j])-1];
			}
			else {
				result = M[abs(clauses[i][j])-1];
			}
			if(result == 1) {
				break;
			}
		}
		if(result == 0) {		
			for(int k=0; k<clauses[i].size(); k++) {		//Inserts all variables in the false clause to S
				int var = clauses[i][k];
				S.insert(abs(var));
			}
		}
	}
	cout<<"S: ";
	for(auto it=S.begin(); it!=S.end(); it++) {
		cout<<*it<<" ";
	}
	cout<<endl;
	
}

void flip_variables(int v) {		//Function to flip v variables randomly
	
	cout<<"Flipping "<<v<<" Variables"<<endl;
	vector <int> temp_vec(S.begin(), S.end());
	random_shuffle(temp_vec.begin(), temp_vec.end());		//Temp Vector of random indices
	
	if(v>S.size()) {		//If v is greater than size of S, flip all variables
		for(int i=0; i<temp_vec.size(); i++) {
			// cout<<"Flipping "<<temp_vec[i]<<endl;
			M[temp_vec[i]] = 1-M[temp_vec[i]];
		}
	}
	else {
		for(int i=0; i<v; i++) {		//If v is smaller than size of S, flip v variables (randomly)
			// cout<<"Flipping "<<temp_vec[i]<<endl;
			M[temp_vec[i]] = 1-M[temp_vec[i]];
		}
	}
	find_variables_in_false_clauses();
}

void find_min_conflicting_v_vars(int v) {		//Function to find minimum conflicting v variables

	cout<<"Finding min. conflicting "<<v<<" vars"<<endl;
	vector< pair<int, int> > variable_false_clause_pairs;		//Pair to store no. of false clauses corresponding to each variable
	for(auto it=S.begin(); it != S.end(); it++) {
		int no_of_false_clauses = 0;		//No. of false clauses initially set to 0
		// cout<<"Flipping "<<*it<<endl;
		M[*it-1] = 1-M[*it-1];		//Flipping one variable
		int result = 1;
		for(int i=0; i<m; i++) {
			for(int j=0; j<clauses[i].size(); j++) {
				if(clauses[i][j] < 0) {
					result = 1-M[abs(clauses[i][j])-1];
				}
				else {
					result = M[abs(clauses[i][j])-1];
				}
				if(result == 1) {
					break;
				}
			}
			if(result == 0) {
				no_of_false_clauses++;		//Adding no. of false clauses
			}
		}
		// cout<<"Turning "<<*it<<" back"<<endl;
		M[*it-1] = 1-M[*it-1];
		variable_false_clause_pairs.push_back(make_pair(no_of_false_clauses, *it));		//Storing no. of false clauses due to flipping the variable
	}
	sort(variable_false_clause_pairs.begin(), variable_false_clause_pairs.end());		//Sorting the pair in asc. order of no. of false clauses
	if(v > S.size()) {		//If v is greater than size of S, flip all variables in S	
		for(int i=0; i<S.size(); i++) {
			// cout<<"Flipping "<<variable_false_clause_pairs[i].second<<endl;
			M[variable_false_clause_pairs[i].second-1] = 1-M[variable_false_clause_pairs[i].second-1];
		}
	}
	else {
		for(int i=0; i<v; i++) {		//If v is smaller than size of S, flip minimum conflicting v variables
			// cout<<"Flipping "<<variable_false_clause_pairs[i].second<<endl;
			M[variable_false_clause_pairs[i].second-1] = 1-M[variable_false_clause_pairs[i].second-1];
		}
	}

	find_variables_in_false_clauses();

}

int main() {
	
	int maxit, maxv, v, total_iterations = 0, cur_it;		//maxit - Max. no. of assignments to be tried in each run, maxv - Max. no of variables to be simultaneously flipped
	float p;		//Probability of flipping
	bool flag = false;		//Flag to check if the problem is satisfied within given iterations

	read_input_dimacs();		//Read the input file
	
	cout<<"Enter max. no. of assignments to be tried in each run: "<<endl;
	cin>>maxit;
	// maxit = 100;

	cout<<"Enter max. no. of variables to be simultaneously flipped: "<<endl;
	cin>>maxv;
	// maxv = n;

	cout<<"Enter probability of flipping: "<<endl;
	cin>>p;
	
	M.resize(n);
	generate_random_M();		//Generate initial random assignment
	// check_sat();

	v=0;
	while(v<maxv) {
		v++;
		cout<<"Running with v = "<<v<<endl;
		// maxit = 100;
		cur_it = maxit;
		while(cur_it--) {
			total_iterations++;
			cout<<"Current Iteration = "<<cur_it<<endl;
			if(satisfies()) {		//Check if clause is satisfied, if so break
				cout<<"Clause is satisfied!"<<endl;
				display_sat();
				flag = true;
				break;
			}

			find_variables_in_false_clauses();		//Find variables in false clauses and store in S
			
			// p = .5;
			random_device rd;  //Will be used to obtain a seed for the random number engine
		    mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
		    uniform_real_distribution<> dis(0.0, 1.0);
			// cout<<"Random no: "<<dis(gen);

			if(dis(gen) >= p) {		//If random no. is greater than p, Flip variables
				flip_variables(v);
			}
			else {
				find_min_conflicting_v_vars(v);		//Else, Flip v variables causing minimum false clauses.
			}
		}
		if(flag == true) {
			break;
		}
	}
	if(flag == false) {		//If problem is not satisfied after input iterations, output Failure
		cout<<"Failure"<<endl;
	}
	else {
		cout<<"Success"<<endl;		//If problem is satisfied, output Success
	}
	cout<<"Total Iterations: "<<total_iterations;		//Output Total no. of Iterations Completed
	return 0;

}