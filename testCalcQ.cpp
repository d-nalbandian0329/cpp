// Calculate survival probability of branching process.
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <cmath>

#define threL 1.0E-3
#define threS 1.0E-4

// Number of links to next layer units from one unit.
#define CN 6

// SIGMA loop end.
#define END 3.01

using namespace std;

typedef basic_ifstream<char> ifstream;
typedef basic_ofstream<char> ofstream;

typedef basic_stringstream<char> stringstream;


struct Entry{
  double np;
  double nq;
};


double calc(double q, double SIGMA){
  double p = SIGMA / CN;
  double ret = pow((p * q + 1 - p), CN);

  return ret;
}

void makeFile(string fname){
  ofstream ofs;
  double SIGMA = 0.1;

  while(SIGMA < END){
    stringstream ss;  //ss.precision(6);  <- default
    ss << SIGMA;

    string str = "/Users/iwaitoshiya/u226136/C++-Pro/Q_CSV2/SIGMA_"
      + ss.str() + "_";

    ofs.open(str+fname, ios::out);

    for(double q = 0.01; q <= 1.0009; q += 0.01)
      ofs << q << ',' << calc(q, SIGMA) << endl;

    ofs.close();

    SIGMA += 0.1;
  }

}

void readFile(string fname, list<Entry>& pqlist){
  ifstream ifs;

  ifs.open(fname);

  while(!ifs.eof()){
    string buf;
    double ret;

    getline(ifs, buf, ',');
    // Convert string into double.
    ret = stod(buf);

    if(threS <= abs(ret) && abs(ret) <= abs(ret)){
      double p, q;
      string sp, sq;

      getline(ifs, sp, ',');
      getline(ifs, sq);

      // Convert string data into double data.
      stringstream s_sp(sp), s_sq(sq);
      s_sp >> p;
      s_sq >> q;

      Entry e = {p, q};

      pqlist.push_back(e);
    }

  }


  ifs.close();

}

void showEntry(const Entry& e){
  cout << "p : " << e.np << "\nq : " << e.nq
       << "\nSIGMA : " << (e.np*CN) << "\n\n";
}

void showResult(list<Entry>& pqlist){
  typedef list<Entry>::const_iterator LI;

  for(LI i = pqlist.begin(); i != pqlist.end(); i++)
    showEntry(*i);
}




int main(){
  list<Entry> pqlist;
  string fname = "CalcQ.csv";

  makeFile(fname);

  readFile(fname, pqlist);

  showResult(pqlist);

  return 0;
}
