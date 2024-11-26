#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

typedef struct 
{
    char name[10];
    char phone_number[20];
    char email[30];
    char memo[100];
    int is_deleted;  
} Contact;

Contact phonebook[100];
int count = 0;

void load_contact() 
{
    FILE* file = fopen("phonebook.txt", "r");
    if (!file) 
        return;

    while (fscanf(file, "%9s %19s %29s %99s %d\n", phonebook[count].name, phonebook[count].phone_number,
        phonebook[count].email, phonebook[count].memo, 
        &phonebook[count].is_deleted) == 5) 
    {
        if (!phonebook[count].is_deleted) 
            count++;
    }
    fclose(file);
}

void save_contact() 
{
    FILE* file = fopen("phonebook.txt", "w");
    if (!file) 
    {
        printf("파일을 저장할 수 없습니다.\n");
        return;
    }
    for (int i = 0; i < count; i++) 
    {
        if (!phonebook[i].is_deleted) 
        {
            fprintf(file, "%s %s %s %s %d\n", phonebook[i].name, phonebook[i].phone_number, 
                phonebook[i].email, phonebook[i].memo, phonebook[i].is_deleted);
        }
    }
    fclose(file);
}

void add_contact() 
{
    if (count >= 100) 
    {
        printf("전화번호부가 가득 차서 추가할 수 없습니다.\n");
        return;
    }

    printf("이름: ");
    scanf("%s", phonebook[count].name);
    printf("전화번호: ");
    scanf("%s", phonebook[count].phone_number);
    printf("이메일: ");
    scanf("%s", phonebook[count].email);
    printf("메모: ");
    scanf("%s", phonebook[count].memo);
    phonebook[count].is_deleted = 0;
    count++;
    printf("연락처가 성공적으로 추가되었습니다.\n");
}

void delete_contact() 
{
    char name[10];
    printf("삭제할 이름을 입력하세요: ");
    scanf("%s", name);

    for (int i = 0; i < count; i++) 
    {
        if (!phonebook[i].is_deleted && strcmp(phonebook[i].name, name) == 0) 
        {
            phonebook[i].is_deleted = 1;
            printf("연락처가 성공적으로 삭제되었습니다.\n");
            return;
        }
    }
    printf("연락처를 삭제하는데 실패했습니다.\n");
}

void update_contact() 
{
    char name[10];
    printf("수정할 이름을 입력하세요: ");
    scanf("%s", name);

    for (int i = 0; i < count; i++) 
    {
        if (!phonebook[i].is_deleted && strcmp(phonebook[i].name, name) == 0) 
        {
            printf("새로운 이름: ");
            scanf("%s", phonebook[i].name);
            printf("새로운 전화번호: ");
            scanf("%s", phonebook[i].phone_number);
            printf("새로운 이메일: ");
            scanf("%s", phonebook[i].email);
            printf("새로운 메모: ");
            scanf("%s", phonebook[i].memo);
            printf("연락처가 성공적으로 수정되었습니다.\n");
            return;
        }
    }
    printf("연락처를 수정하는데 실패했습니다.\n");
}

void search_contact() 
{
    char name[10];
    printf("검색할 이름을 입력하세요: ");
    scanf("%s", name);

    for (int i = 0; i < count; i++) 
    {
        if (!phonebook[i].is_deleted && strcmp(phonebook[i].name, name) == 0) 
        {
            printf("이름: %s, 전화번호: %s, 이메일: %s, 메모: %s\n", phonebook[i].name, phonebook[i].phone_number, 
                phonebook[i].email, phonebook[i].memo);
            return;
        }
    }
    printf("연락처를 찾을 수 없습니다.\n");
}

void list_contact() 
{
    for (int i = 0; i < count - 1; i++) 
    {
        for (int j = i + 1; j < count; j++) 
        {
            if (!phonebook[i].is_deleted && !phonebook[j].is_deleted && strcmp(phonebook[i].name, phonebook[j].name) > 0) 
            {
                Contact temp = phonebook[i];
                phonebook[i] = phonebook[j];
                phonebook[j] = temp;
            }
        }
    }

    printf("---- 연락처 리스트 ----\n");
    for (int i = 0; i < count; i++) 
    {
        if (!phonebook[i].is_deleted) 
        {
            printf("이름: %s, 전화번호: %s, 이메일: %s, 메모: %s\n", phonebook[i].name, phonebook[i].phone_number,
                phonebook[i].email, phonebook[i].memo);
        }
    }
}

void menu() 
{
    printf("1. 연락처 추가\n");
    printf("2. 연락처 삭제\n");
    printf("3. 연락처 수정\n");
    printf("4. 연락처 검색\n");
    printf("5. 연락처 리스트\n");
    printf("6. 종료\n");
}

int main() 
{
    load_contact();

    int choice;
    while (1) 
    {
        menu();
        printf("선택: ");
        scanf("%d", &choice);

        switch (choice) 
        {
        case 1:
            add_contact();
            break;
        case 2:
            delete_contact();
            break;
        case 3:
            update_contact();
            break;
        case 4:
            search_contact();
            break;
        case 5:
            list_contact();
            break;
        case 6:
            save_contact();
            printf("프로그램을 종료합니다.\n");
            return 0;
        default:
            printf("입력이 잘못되었습니다.\n");
        }
    }
}
