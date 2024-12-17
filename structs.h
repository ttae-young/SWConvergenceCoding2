#ifndef STRUCTS_H
#define STRUCTS_H
// 구조체 계속 사용하니까 헤더파일로 만들어서 사용
struct tour {
	char city_name[10];
	char spot_name[30];
	int latitude;
	int longitude;
	int purpose;
	char pur_description[200];
	int popularity;
	char pop_description[200];
	int season;
	char s_description[200];
	int theme;
	char t_description[200];
};

#endif