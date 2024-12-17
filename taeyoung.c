#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "structs.h"

extern struct tour choice_list[10]; // choice_list[10] 가져와서 사용
extern int spotCount; // spot_Count 가져와서 사용

void deleteTouristSpot()
{
    int index;

    if (spotCount < 1)
    {
        printf("\n선택한 관광지가 없습니다.\n");
        return;
    }

    printf("\n현재 관광지 목록:\n");
    for (int i = 0; i < spotCount; i++)
    {
        printf("%d. %s, %s\n", i + 1, choice_list[i].city_name, choice_list[i].spot_name);
    }

    printf("\n삭제할 관광지 번호를 선택하세요: ");
    scanf("%d", &index);
    if (index < 1 || index > spotCount)
    {
        printf("잘못된 선택입니다.\n");
        return;
    }
    // 배열 재배열
    for (int i = index - 1; i < spotCount - 1; i++)
    {
        choice_list[i] = choice_list[i + 1];
    }
    spotCount--;
    printf("관광지가 삭제가 완료되었습니다.\n");
}
// 메뉴에서 switch문 같은 걸로 구현한다면 return 안해도 될 듯

// 두 관광지 사이의 거리 계산
double calculateDistance(double lat1, double lon1, double lat2, double lon2)
{
    double lat_diff = lat2 - lat1;
    double lon_diff = lon2 - lon1;
    return sqrt(lat_diff * lat_diff + lon_diff * lon_diff);
}

// 거리 기반 관광 코스를 생성
void sortTouristSpots()
{
    if (spotCount < 2)
    {
        printf("\n선택한 관광지가 2개 이상 있어야 합니다.\n");
        return;
    }

    printf("\n거리를 기준으로 관광지를 정렬하시겠습니까? ('예' 또는 '메인메뉴'): ");
    char choice[25];
    scanf("%s", choice);
    getchar();

    if (strcmp(choice, "예") != 0)
    {
        printf("\n메인 메뉴로 돌아갑니다.\n");
        return;
    }

    struct tour sortedSpots[10]; // 기준 지역만 담는 배열
    int sortedCount = 0;           // 기준 지역 개수

    int visited[100] = {0}; // 방문 여부를 저장하는 배열
    int current = -1;       // 첫 기준 지역 입력하는 변수, 일단 -1로 설정

    printf("현재 관광지 목록:\n");
    for (int i = 0; i < spotCount; i++)
    {
        printf("%d. %s, %s\n", i + 1, choice_list[i].city_name, choice_list[i].spot_name);
    }

    printf("기준 지역을 선택하세요 (번호): ");
    scanf("%d", &current);
    if (current < 1 || current > spotCount)
    {
        printf("잘못된 선택입니다.\n");
        return;
    }
    current--; // 배열 인덱스에 맞춰야 하니까

    while (spotCount > 0)
    {
        sortedSpots[sortedCount++] = choice_list[current];

        // 기준 지역 현재 관광지 목록에서 제거
        for (int i = current; i < spotCount - 1; i++)
        {
            choice_list[i] = choice_list[i + 1];
        }
        spotCount--;

        // 남은 관광지가 없으면 나오기
        if (spotCount == 0)
            break;

        current = 0;
        // 거리 비교해서 짧은 거리 구하기
        double minDistance = calculateDistance(
            sortedSpots[sortedCount - 1].latitude,
            sortedSpots[sortedCount - 1].longitude,
            choice_list[0].latitude,
            choice_list[0].longitude);
        // latitude는 위도, longitude는 경도

        for (int i = 1; i < spotCount; i++)
        {
            double distance = calculateDistance(
                sortedSpots[sortedCount - 1].latitude,
                sortedSpots[sortedCount - 1].longitude,
                choice_list[i].latitude,
                choice_list[i].longitude);
            if (distance < minDistance)
            {
                minDistance = distance;
                current = i;
            }
        }
    }

    // 기준 지역 나열한 배열을 현재 관광지 목록에 덮어쓰기
    for (int i = 0; i < sortedCount; i++)
    {
        choice_list[i] = sortedSpots[i];
    }
    spotCount = sortedCount;

    printf("\n거리 기반 관광 코스:\n");
    for (int i = 0; i < spotCount; i++)
    {
        printf("%d. %s, %s\n", i + 1, choice_list[i].city_name, choice_list[i].spot_name);
    }
}