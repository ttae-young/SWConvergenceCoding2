#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <direct.h>
#include "structs.h"

void deleteTouristSpot();
void sortTouristSpots();
void pur_Select();
void pop_Select();
void s_Select();
void t_Select();

struct tour tour_list[100] = {0};   // 선택된 시의 모든 관광지 데이터를 담을 구조체 배열
struct tour choice_list[10] = {0}; // 현재 선택된 관광지들을 담을 구조체 배열
int spotCount = 0;				   // 선택된 시의 모든 관광지 데이터 담는 구조체 배열 작성할 때 활용
int allCount = 0;

void selected_list() // 선택한 관광지 목록 확인 함수
{
	int i;
	if (spotCount == 0)
	{
		printf("선택한 관광지가 없습니다.\n");
		return;
	}

	for (i = 0; i < spotCount; i++)
	{
		printf("%d. %s %s\n", i + 1, choice_list[i].city_name, choice_list[i].spot_name); // 시이름& 관광지 이름 출력
	}
	return;
}
int main(void) // 메인 함수
{
	int province; // 사용자가 선택한 도 저장
	char city[5]; // 사용자가 선택한 시 저장

	printf("1.경기도\n2.전라도\n3.강원도\n4.제주도\n5.서울\n6.부산\n\n");
	printf("여행할 지역을 선택해 번호를 입력하세요: ");
	scanf("%d", &province);

	FILE* fp = NULL;
	switch (province)
	{ // 선택된 지역에 따라 텍스트 파일 오픈
	case 1:
		fp = fopen("Textfile/Gyeonggi.txt", "r");
		if (fp == NULL)
		{
			printf("파일을 열 수 없습니다.\n");
			return 1;
		}
		printf("\n1.수원시\n2.용인시\n3.포천시\n4.가평군\n5.이천시\n\n");
		break;
	case 2:
		fp = fopen("Textfile/Jeollado.txt", "r");
		if (fp == NULL)
		{
			printf("파일을 열 수 없습니다.\n");
			return 1;
		}
		printf("\n1.군산시\n2.전주시\n3.목포시\n4.여수시\n5.순천시\n\n");
		break;
	case 3:
		fp = fopen("Textfile/Gangwondo.txt", "r");
		if (fp == NULL)
		{
			printf("파일을 열 수 없습니다.\n");
			return 1;
		}
		printf("\n1.속초시\n2.삼척시\n3.강릉시\n4.춘천시\n5.평창군\n\n");
		break;
	case 4:
		fp = fopen("Textfile/Jejudo.txt", "r");
		if (fp == NULL)
		{
			printf("파일을 열 수 없습니다.\n");
			return 1;
		}
		printf("\n1.서귀포시\n2.제주시\n\n");
		break;
	case 5:
		fp = fopen("Textfile/Seoul.txt", "r");
		if (fp == NULL)
		{
			printf("파일을 열 수 없습니다.\n");
			return 1;
		}
		printf("\n1.동부\n2.서부\n\n");
		break;
	case 6:
		fp = fopen("Textfile/Busan.txt", "r");
		if (fp == NULL)
		{
			printf("파일을 열 수 없습니다.\n");
			return 1;
		}
		printf("\n1.동부\n2.서부\n\n");
		break;
	}
	printf("여행할 도시(지방)를 선택해 이름을 입력하세요: "); // 사용자가 시선택
	scanf("%s", city);
	getchar();

	char line[350];
	while (fgets(line, sizeof(line), fp) != NULL) // 텍스트 파일에서 기존 내용을 한 줄씩 읽어온다.
	{
		char* token = strtok(line, "/\n");
		if (token != NULL && strcmp(token, city) == 0) // 선택된 시에 해당하는 관광지 정보들만 관광지 데이터를 담는 구조체에 저장
			strncpy(tour_list[allCount].city_name, token, sizeof(tour_list[allCount].city_name) - 1);
		else
			continue;

		token = strtok(NULL, "/\n");
		if (token != NULL)
			strncpy(tour_list[allCount].spot_name, token, sizeof(tour_list[allCount].spot_name) - 1);

		token = strtok(NULL, "/\n");
		if (token != NULL)
			tour_list[allCount].latitude = atoi(token);

		token = strtok(NULL, "/\n");
		if (token != NULL)
			tour_list[allCount].longitude = atoi(token);

		token = strtok(NULL, "/\n");
		if (token != NULL)
			tour_list[allCount].purpose = atoi(token);

		token = strtok(NULL, "/\n");
		if (token != NULL)
			strncpy(tour_list[allCount].pur_description, token, sizeof(tour_list[allCount].pur_description) - 1);


		token = strtok(NULL, "/\n");
		if (token != NULL)
			tour_list[allCount].popularity = atoi(token);

		token = strtok(NULL, "/\n");
		if (token != NULL)
			strncpy(tour_list[allCount].pop_description, token, sizeof(tour_list[allCount].pop_description) - 1);

		token = strtok(NULL, "/\n");
		if (token != NULL)
			tour_list[allCount].season = atoi(token);

		token = strtok(NULL, "/\n");
		if (token != NULL)
			strncpy(tour_list[allCount].s_description, token, sizeof(tour_list[allCount].s_description) - 1);


		token = strtok(NULL, "/\n");
		if (token != NULL)
			tour_list[allCount].theme = atoi(token);

		token = strtok(NULL, "/\n");
		if (token != NULL)
			strncpy(tour_list[allCount].t_description, token, sizeof(tour_list[allCount].t_description) - 1);
		
		allCount++;

		
	}
		fclose(fp);
		printf("\n여행할 곳이 정상적으로 선택되었습니다!\n");

		while (1) // 메뉴 출력
		{
			int menu_choice;
			int add_choice;
			printf("\n\n***************************\n");
			printf("1. 선택한 관광지 목록 확인\n2. 관광지 삽입\n3. 관광지 삭제\n4. 거리 기반 관광 코스 추천\n5. 프로그램 종료");
			printf("\n***************************\n\n");
			printf("메뉴에서 원하는 기능의 번호를 입력하세요.: ");
			scanf("%d", &menu_choice);

			switch (menu_choice)
			{
			case 1:
				selected_list();
				break;
			case 2:
				printf("\n1. 목적 기반 관광지 추천\n2. 인기 기반 관광지 추천\n3. 계절 기반 관광지 추천\n4. 테마 기반 관광지 추천\n\n");
				printf("원하시는 관광지 추천 방법 번호를 입력하세요: ");
				scanf("%d", &add_choice);
				getchar();
				switch (add_choice)
				{
				case 1:
					pur_Select();
					break;
				case 2:
					pop_Select();
					break;
				case 3:
					s_Select();
					break;
				case 4:
					t_Select();
					break;
				}
				break;
			case 3:
				deleteTouristSpot();
				break;
			case 4:
				sortTouristSpots();
				break;
			case 5:
				return 0;
			default:
				printf("\n잘못된 선택입니다. 1~5 사이의 숫자를 입력하세요.\n");
			}
		}
	
}