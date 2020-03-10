#include<iostream>
#include<fstream>
#include <vector> 
#include <sstream> 
#include <string> 
#include<thread>
#include<mutex>
using namespace std;

int operate(string operation,int num1,int num2)
{
    if(operation=="add")
        return num1+num2;
    if(operation=="sub")
        return num1-num2;
    if(operation=="mul")
        return num1*num2;
    if(operation=="div")
        return num1/num2;    
}
std::mutex mtx; 
void print(string operation,int num1,int num2,int result)
{
    mtx.lock();
    if(operation=="add")
        cout<<num1<<'+'<<num2<<'='<<result<<"\n";
    if(operation=="sub")
        cout<<num1<<'-'<<num2<<'='<<result<<"\n";
    if(operation=="mul")
        cout<<num1<<'*'<<num2<<'='<<result<<"\n";
    if(operation=="div")
        cout<<num1<<'/'<<num2<<'='<<result<<"\n";
    mtx.unlock();
}
void task(string operation,int num1,int num2)
{
    print(operation,num1,num2,operate(operation,num1,num2));
}
vector<thread> threadPool; 
void read_record() 
{ 

	// File pointer 
	fstream fin; 

	// Open an existing file 
	fin.open("input.csv", ios::in); 

	// Read the Data from the file 
	// as String Vector 
	vector<string> row; 
	string line, word; 
    // read an entire row and 
    // store it in a string variable 'line' 

	while (getline(fin, line)) { 

		row.clear(); 
		// used for breaking words 
		istringstream s(line); 
		// read every column data of a row and 
		// store it in a string variable, 'word' 
		while (getline(s, word, '|')) { 
			// add all the column data 
			// of a row to a vector 
			row.push_back(word); 
        } 
        getline(s, word);
        row.push_back(word); 

		// convert string to integer for comparision 
		 int num1  = stoi(row[1]); 
		 int num2  = stoi(row[2]); 

        (task(row[0],num1,num2));
        //threadPool.push_back(funcTest1);
        //main is blocked until funcTest1 is not finished
		
	} 
    fin.close();
    for(std::vector<thread>::size_type i = 0; i != threadPool.size(); i++) {
    /* std::cout << v[i]; ... */
    threadPool[i].join();}
}


int main(int argc, char *argv[])
{
    read_record();
    return 0;
}