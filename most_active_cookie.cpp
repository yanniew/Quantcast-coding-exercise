//Yannie Wu

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unordered_map>
using namespace std;

//g++ most_active_cookie.cpp -o most_active_cookie		Compiles code to be executed in expected format


/*Tests to be performed using given cookie log file (most_active_cookie.csv):

Test 1: Use 2018-12-06 as the date to test if there are no active cookies
	Should print out nothing

Test 1: Use 2018-12-07 as the date to test if there is only one active cookie
    Should print out 4sMM2LxV07bPJzwf

Test 2: Use 2018-12-09 as the date to test if there are multiple active cookies and a single most active cookie
    Should print out AtY0laUfhglK3lC7

Test 3: Use 2018-12-08 as the date to test if there are multiple most active cookies
	Should print out fbcn5UAVanZf6UtG, 4sMM2LxV07bPJzwf, SAZuXPGUrfbcn5UA */


int main(int argc, char** argv) {
    // verify the correct number of parameters
    if (argc != 4) {
        cout << "Must supply file name and date" << endl;
        exit(1);
    }

    string param = argv[2];
    string key_date = argv[3];

   // attempt to open the supplied file
    ifstream file(argv[1], ifstream::binary);
    // report any problems opening the file and then exit
    if (!file.is_open()) {
        cout << "Unable to open file '" << argv[1] << "'." << endl;
        exit(2);
    }

    string cookie = "";
    string date = "";
    unordered_map<string, int> freq;
    bool search = true;
    int maxFreq = 1;

    // search file
    while(getline(file, cookie, ',') && search){ 	//get cookie

    	getline(file, date); 						// get date

    	if(date.find(key_date) != string::npos){	// if date == given date, add to map
    		if(freq.find(cookie) != freq.end()){
    			freq[cookie] = freq[cookie] + 1; // update current frequency of cookie and max frequency
    			if(freq[cookie] > maxFreq)
    				maxFreq = freq[cookie];   			
    		}
    		else                       // add cookie to map if it does not yet exist
    			freq[cookie] = 1;        		
    	}

    	if (freq.size() >= 1 && !(date.find(key_date) != string::npos))	// stop searching after all cookies for given date are found
    		search = false;    	
    }

    file.close();

    // print list of most active cookies
    for(auto x : freq){
    	if(x.second == maxFreq)
    		cout << x.first << endl;    	
    }


}



