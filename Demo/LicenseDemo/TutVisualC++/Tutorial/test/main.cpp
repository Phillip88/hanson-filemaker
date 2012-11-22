#include <iostream>
#include <string>
#include <conio.h>

int formatPhoneNumberC(const char *in, char *out) {
	int c = 0;
	while (*in != 0) { 
		if (c == 3 || c == 6) {
			*out++ = '-';
		}
		*out++ = *in++;
		c++;
	}
	*out = 0;
	return c + 2;
}

std::string formatPhoneNumberCpp(std::string number) {
	return number.substr(0, 3) + "-" + number.substr(3, 3) + "-" + number.substr(6);
}
	
int main() {
	char output[20];
	char phNum[] = "1234567890";
	int res = formatPhoneNumberC(phNum, output);
	std::cout << res << ": " << output << std::endl;
	std::cout << formatPhoneNumberCpp("9876543210") << std::endl;
	

	getch();
	return 0;
}