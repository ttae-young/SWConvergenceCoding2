#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

extern struct tour tour_list[50];
extern struct tour choice_list[10];
extern int spotCount; // 태영님 코드에서 저장된 관광지 수 저장하는 변수
extern int allCount;

int dupCheck(int latitude, int longitude) { // 이미 선택된 관광지인지 확인하는 함수 ( 정수로 비교하는게 나을것같아서 좌표로 비교 )
    for (int i = 0; i < spotCount; i++) {
        if (choice_list[i].latitude == latitude && choice_list[i].longitude == longitude) return 1;
    }
    return 0;
};
void select(struct tour temp[], int count) {
    while (1) {
        printf("원하는 관광지의 번호를 입력해주세요.\n(0 을 입력하면 메인화면으로 돌아갑니다.)\n");
        int num;
        scanf("%d", &num);
        num--; // 입력값은 1부터 셀 것이기 때문에 index접근 쉽게하기위해 1 빼고시작함
        if (num < 0 || num > count) return;

        if (dupCheck(temp[num].latitude, temp[num].longitude) == 0) {
            choice_list[spotCount++] = temp[num];
            printf("\n선택이 완료되었습니다.\n");
            return;
        }
        printf("\n이미 선택된 관광지입니다.\n\n");
    }
}

void pur_Select() {
    int num;
    int count = 0;
    struct tour temp[30] = { 0 };
    printf("관광 목적을 선택해주세요.\n");
    printf("1. 혼자\n2. 친구\n3. 가족\n4. 연인\n");
    scanf("%d", &num);
    for (int i = 0; i < allCount; i++) {
        if (tour_list[i].purpose == num) {
            printf("(%d) %s : %s\n", count + 1, tour_list[i].spot_name, tour_list[i].pur_description);
            temp[count++] = tour_list[i];
        }
    }
    printf("----------------------------------------------\n");
    select(temp, count);
}
void pop_Select() {
    int num;
    int count = 0;
    struct tour temp[30] = { 0 };
    printf("어떤 관광지를 원하는지 알려주세요.\n");
    printf("1. 대표 명소\n2. 숨겨진 명소\n");
    scanf("%d", &num);
    for (int i = 0; i < allCount; i++) {
        if (tour_list[i].popularity == num) {
            printf("(%d) %s : %s\n", count + 1, tour_list[i].spot_name, tour_list[i].pop_description);
            temp[count++] = tour_list[i];
        }
    }
    printf("----------------------------------------------\n");
    select(temp, count);
}
void s_Select() {
    int num;
    int count = 0;
    struct tour temp[30] = { 0 };
    printf("어떤 계절에 어울리는 관광지를 추천해드릴까요?.\n");
    printf("1. 봄\n2. 여름\n3. 가을\n4. 겨울\n");
    scanf("%d", &num);
    for (int i = 0; i < allCount; i++) {
        if (tour_list[i].season == num) {
            printf("(%d) %s : %s\n", count + 1, tour_list[i].spot_name, tour_list[i].s_description);
            temp[count++] = tour_list[i];
        }
    }
    printf("----------------------------------------------\n");
    select(temp, count);
}
void t_Select() {
    int num;
    int count = 0;
    struct tour temp[30] = { 0 };
    printf("어떤 테마에 맞춰 관광지를 추천해드릴까요?.\n");
    printf("1. 힐링과 자연\n2. 문화와 역사\n3. 모험과 탐험\n4. 음식과 풍미\n");
    scanf("%d", &num);
    for (int i = 0; i < allCount; i++) {
        if (tour_list[i].theme == num) {
            printf("(%d) %s : %s\n", count + 1, tour_list[i].spot_name, tour_list[i].t_description);
            temp[count++] = tour_list[i];
        }
    }
    printf("----------------------------------------------\n");
    select(temp, count);
}