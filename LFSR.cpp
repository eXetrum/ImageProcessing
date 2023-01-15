#include "LFSR.hpp"
#include <sstream>
//-------------------------------------------------------------------------------------------------------------------------------
LFSR::LFSR(size_t N, string seed, size_t tap) {
	this->N = N;
	this->tap = tap;

	bits = new BIT[N];
	for(size_t i = 0; i < seed.size(); ++i) {
		bits[N - 1 - i] = seed.at(i) == '1';
	}
	
}

LFSR::LFSR(string seed, size_t tap) {
	this->N = seed.size();
	this->tap = tap;

	bits = new BIT[N];
	for(size_t i = 0; i < seed.size(); ++i) {
		bits[N - 1 - i] = seed.at(i) == '1';
	}
}

LFSR::~LFSR() {
	delete []bits;
}

int LFSR::step() {
	BIT shift = bits[N - 1] ^ bits[tap];
	// Shift bits
	for(int i = N - 1; i > 0; --i) {
		bits[i] = bits[i - 1];
	}
	bits[0] = shift;
	return bits[0];
}

ULL LFSR::generate(int k) {
	ULL value = 0;
	for(int i = 0; i < k; ++i) {
		value |= (step() << (k - 1 - i));
	}
	return value;
}

string LFSR::toString() const {
	stringstream s;
	for(int i = N - 1; i >= 0; --i) {
		s << bits[i];
	}
	return s.str();
}

ostream & operator << (ostream &os, const LFSR &ref) {
	os << ref.toString();
	return os;
}
