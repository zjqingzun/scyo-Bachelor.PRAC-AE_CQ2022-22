#include<iostream>
#include<string>
using namespace std;

string encryptMessage(string ps, string key) {
	string cs = "";
	int keyLength = key.length();
	int j = 0; // biến đếm vị trí trong ps

	for (int i = 0; i < ps.length(); i++) {
		if (isalpha(ps[i])) {
			// Chuyển đổi ký tự thành chữ thường để dễ xử lý
			char base = isupper(ps[i]) ? 'A' : 'a';
			char keyChar = tolower(key[j % keyLength]);

			// Tính toán vị trí mới trong bảng chữ cái
			int shift = (keyChar - 'a');
			char newChar = ((ps[i] - base + shift) % 26) + base;

			cs += newChar;
			j++;
		}
		else {
			// Giữ nguyên các ký tự không phải chữ cái
			cs += ps[i];
		}
	}
	return cs;
}

string decryptMessage(string cs, string key) {
	string ps = "";
	int keyLength = key.length();
	int j = 0;

	for (int i = 0; i < cs.length(); i++) {
		if (isalpha(cs[i])) {
			// Chuyển đổi ký tự thành chữ thường để dễ xử lý
			char base = isupper(cs[i]) ? 'A' : 'a';
			char keyChar = tolower(key[j % keyLength]);

			// Tính toán vị trí mới trong bảng chữ cái
			int shift = (keyChar - 'a');
			char newChar = ((cs[i] - base - shift + 26) % 26) + base;

			ps += newChar;
			j++;
		}
		else {
			// Giữ nguyên các ký tự không phải chữ cái
			ps += cs[i];
		}
	}
	return ps;
}

int main() {
	//string ps = "Hello world";
	string ps = "abcdefghijklmnopqrstuvwxyz";
	string key = "abc";
	string cs = encryptMessage(ps, key);
	cout << "Chuoi da ma hoa: " << cs << endl;
	cout << "Chuoi da giai ma: " << decryptMessage(cs, key) << endl;
	return 0;
}

