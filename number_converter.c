
#define CHAR_0 '0'
#define CHAR_1 '1'
#define CHAR_2 '2'
#define CHAR_3 '3'
#define CHAR_4 '4'
#define CHAR_5 '5'
#define CHAR_6 '6'
#define CHAR_7 '7'
#define CHAR_8 '8'
#define CHAR_9 '9'

#define INT_0 0
#define INT_1 1
#define INT_2 2
#define INT_3 3
#define INT_4 4
#define INT_5 5
#define INT_6 6
#define INT_7 7
#define INT_8 8
#define INT_9 9

int convert_char(char char_s) {
	int number = -1;
	switch(char_s) {
			case CHAR_0:
				number = INT_0;
				break;
			case CHAR_1:
				number = INT_1;
				break;
			case CHAR_2:
				number = INT_2;
				break;
			case CHAR_3:
				number = INT_3;
				break;
			case CHAR_4:
				number = INT_4;
				break;
			case CHAR_5:
				number = INT_5;
				break;
			case CHAR_6:
				number = INT_6;
				break;
			case CHAR_7:
				number = INT_7;
				break;
			case CHAR_8:
				number = INT_8;
				break;
			case CHAR_9:
				number = INT_9;
				break;
		}
	return number;
}
