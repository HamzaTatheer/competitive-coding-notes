#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;



string convert(string s, int numRows) {

	if (numRows == 1)
		return s;

	string ans = "";
	int diagLen = numRows - 2;


	for (int i = 0; i < numRows; i++) {


		int j = i;
		int k = numRows + diagLen - i;

		if (i == 0) {
			while (j < s.length()) {
				ans += s.at(j);
				j+= (diagLen + numRows);
			}
		}
		else {

			while (true) {


				if (j >= s.length() && k >= s.length())
					break;

				if (j < s.length())
					ans += s.at(j);

				if (k < s.length() && i < numRows - 1) {
					ans += s.at(k);
				}

				
				

				k += (diagLen + numRows);
				j += (diagLen + numRows);
			}
		}
	}

	return ans;
}



int main() {	
	cout << convert("paypalishiring", 4);
}