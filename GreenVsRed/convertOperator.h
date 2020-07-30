#pragma once

inline unsigned short int convertCharToInt(char _char) {
	return _char - '0';
}

inline unsigned short int convertStringToInt(string _string) {
	reverse(_string.begin(), _string.end());

	int i = 0, result = 0;
	while (_string[i] != '\0'){
		result += convertCharToInt(_string[i]) * pow(10, i);
		i++;
	}
	return result;
}