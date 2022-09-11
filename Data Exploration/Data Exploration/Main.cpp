//Ethan Huynh
//EXH190016
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

// sums up all elements of some vector of type double and returns as a double
double sum(vector<double> v) {
    return accumulate(v.begin(), v.end(), 0.0);
}

// takes the sum and divides it by the size of the vector to find mean
double mean(vector<double> v) {
    return sum(v)/v.size();
}

// partial sorts the vector and then returns the middle element or the average of the middle elements
double median(vector<double> v) {
    // sort vector up to half way 
    auto m = v.begin() + v.size()/2 ;
    nth_element(v.begin(), m, v.end());

    // if size is even
    if (v.size()%2 == 0) {
        //take the two middle elements and average them
        return (v[v.size()/2] + v[v.size()/2-1])/2;
    }
    // else size is odd
    else {
        return v[v.size()/2];
    }
}

// sums the difference between each element of each vector with its respective mean
double covariance(vector<double> v1, vector<double> v2)
{
    double sum = 0;
    double m1 = mean(v1);
    double m2 = mean(v2);
    for (int i = 0; i < v1.size(); i++)
        sum += (v1.at(i) - m1) * (v2.at(i) - m2);
    return sum / (v1.size() - 1);
}

// function that returns correlation coefficient.
float correlation(vector<double> v1, vector<double> v2)
{
    // get covariance
    double covar = covariance(v1, v2);
    
    // calculate standard deviation
    double m1 = mean(v1);
    double m2 = mean(v2);
    double sum1 = 0, sum2 = 0;
    double n = v1.size();

    for (int i = 0; i < v1.size(); i++) {
        sum1 += (v1.at(i) - m1) * (v1.at(i) - m1);
        sum2 += (v2.at(i) - m2) * (v2.at(i) - m2);
    }

    sum1 /= (n-1);
    sum2 /= (n-1);

    double std1 = sqrt(sum1);
    double std2 = sqrt(sum2);
  
    // calculate correlation coefficient
    return covar/(std1*std2);
}

// prints out all the basic stats for the given vector with the given name
void print_stats(vector<double> v, string name) {
    cout << "Stats for " << name << endl;
    cout << name << " Sum: " << sum(v) << endl;
    cout << name << " Mean: " << mean(v) << endl;
    cout << name << " Median: " << median(v) << endl;
    const auto [min, max] = minmax_element(v.begin(), v.end());
    cout << name << " Range (min-max): " << *min << "-" << *max << endl;
}

// Driver function
int main()
{
    ifstream inFS;  //input file stream
    string line;
    string rm_in, medv_in;
    const int MAX_LEN = 1000;
    vector<double> rm(MAX_LEN);
    vector<double> medv(MAX_LEN);

    //Attempt to open file
    cout << "Opening Boston.csv" << endl;

    inFS.open("Boston.csv");
    if (!inFS.is_open()) {
        cout << "Error opening Boston.csv" << endl;
        return 1;
    }

    //Read the open Boston.csv file
    cout << "Reading line 1" << endl;
    getline(inFS, line);

    //print the columns headers
    cout << "Headers: " << line << endl;

    int numObservations = 0;
    while (inFS.good()) {
        // read first column into rm_in, and second column into medv_in
        getline(inFS, rm_in, ',');
        getline(inFS, medv_in, '\n');

        //store the read values into their respective vectors
        rm.at(numObservations) = stof(rm_in);
        medv.at(numObservations) = stof(medv_in);

        numObservations++;
    }
    //close file
    inFS.close();

    //resize vectors
    rm.resize(numObservations);
    medv.resize(numObservations);
    
    print_stats(rm, "rm");
    print_stats(medv, "medv");

    cout << "\n Covariance = " << covariance(rm, medv) << endl;
    cout << "\n Correlation = " << correlation(rm, medv) << endl;
    return 0;
}
