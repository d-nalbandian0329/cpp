// Calculate survival probability

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <cmath>

#define S_BIN   0.1
#define S_START 0.1
#define S_END   (5.0+S_BIN/2)

#define Q_BIN   1.0E-9
#define Q_START 1.0E-9
#define Q_END   1.2

#define THRESHOLD 1.0E-8



using namespace std;

struct Entry{
  double sigma;  // Sigma.
  double Q;      // Survival probability.
};

// Check the value within threshold or not.
bool threshold(double);

// (p*q + 1 - p)^c - q = 0
double calcQ(double p, double q, int c);

// Search q value that fullfill the requirements.
list<Entry> checkQ(double sigma, int c);

// Do all process.
void doAllProcess(string, int);



int main(){
  string path = "/Users/iwaitoshiya/u226136/C++-Pro/SP";

  for(int CN = 205; CN <= 500; CN += 5)
    doAllProcess(path, CN);

  return 0;
}



// Check the value within threshold or not.
bool threshold(double num){
//  if(abs(num) < THRESHOLD)
//    cout << "num : " << num << endl;

  return (abs(num) <= THRESHOLD);
}

// (p*q + 1 - p)^c - q = 0
double calcQ(double p, double q, int c){
  return (pow((p*q+1-p), c) - q);
}

// Search q value that fullfill the requirements.
list<Entry>& checkQ(list<Entry>& sq_list, double sigma, int c){
  double q = Q_START;
  double p = sigma / c;

  while(q <= Q_END){
    if(threshold(calcQ(p, q, c))){
      Entry e = {sigma, (1-q)};
      sq_list.push_back(e);
      cout << e.sigma << "," << e.Q << endl;
      break;
    }

    q += Q_BIN;
  }

  return sq_list;
}

// Do all process.
void doAllProcess(string path, int CN){
  list<Entry>  sq_list;
  ofstream     ofs;
  stringstream ss;
  double SIGMA = S_START;

  while(SIGMA <= S_END){
    checkQ(sq_list, SIGMA, CN);
    SIGMA += S_BIN;
  }

  ss << CN;
  string fname = path + "_CN" + ss.str() + ".csv";

  ofs.open(fname, ios::out);

  typedef list<Entry>::const_iterator LI;
  for(LI i = sq_list.begin(); i != sq_list.end(); i++){
    const Entry& e = *i;
    cout << "SIGMA:" << e.sigma << endl << "Q    :" << e.Q << endl;
    ofs << e.sigma << "," << e.Q << endl;
  }
  ofs.close();
}
