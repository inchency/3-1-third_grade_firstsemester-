#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class shape {
private:
	double x;
	double y;
	double r;
public:
	void TC();
	void RC();
	void CC();
	void getxy(int xx, int yy);
	void getr(int rr);
};

void shape::TC() {
	cout << "triangle " << x << " " << y << " " << x * y * 0.5 << endl;
}

void shape::RC() {
	cout << "rectangle " << x << " " << y << " " << x * y << endl;
}

void shape::CC() {
	cout << "circle " << r << " " << r * r * 3.14 << endl;
}

void shape::getxy(int xx, int yy) {
	x = xx;
	y = yy;
}

void shape::getr(int rr) {
	r = rr;
}


int main() {
	shape s1;
	string a;
	int xx, yy, rr;

	cout.setf(ios::fixed);
	cout.precision(2);
	fstream instream("input.txt");
	if (!instream.is_open()) {
		cout << "Error (Not found data file)";
		return 1;
	}

	while (instream >> a) {
		if (a == "triangle") {
			instream >> xx >> yy;
			s1.getxy(xx, yy);
			s1.TC();
		}
		else if (a == "rectangle") {
			instream >> xx >> yy;
			s1.getxy(xx, yy);
			s1.RC();
		}
		else if (a == "circle") {
			instream >> rr;
			s1.getr(rr);
			s1.CC();
		}
		else
			cout << "도형 입력 오류";
	}
	return 0;
}