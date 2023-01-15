#include <string>
//#include <bitset>
using namespace std;
//-------------------------------------------------------------------------------------------------------------------------------
typedef bool BIT;
typedef unsigned long long ULL;
class LFSR {
private:
	size_t N;
	size_t tap;
	BIT *bits;
public:
	LFSR(size_t N, string seed, size_t tap);		//  constructor to create LFSR with the given N - length, initial seed and tap
	LFSR(string seed, size_t tap);					//  constructor to create LFSR with the given initial seed and tap
	virtual ~LFSR();
	int step();										//  simulate one step and return the new bit as 0 or 1
	ULL generate(int k);							//  simulate k steps and return k-bit integer
	string toString() const;						//  return a string representation of the LFSR
	friend ostream & 
		operator << (ostream &os, const LFSR &ref);	// output lfsr state to the stream
};
