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
        printf("������ ������ �� �����ϴ�.\n");
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
        printf("��ȭ��ȣ�ΰ� ���� ���� �߰��� �� �����ϴ�.\n");
        return;
    }

    printf("�̸�: ");
    scanf("%s", phonebook[count].name);
    printf("��ȭ��ȣ: ");
    scanf("%s", phonebook[count].phone_number);
    printf("�̸���: ");
    scanf("%s", phonebook[count].email);
    printf("�޸�: ");
    scanf("%s", phonebook[count].memo);
    phonebook[count].is_deleted = 0;
    count++;
    printf("����ó�� ���������� �߰��Ǿ����ϴ�.\n");
}

void delete_contact() 
{
    char name[10];
    printf("������ �̸��� �Է��ϼ���: ");
    scanf("%s", name);

    for (int i = 0; i < count; i++) 
    {
        if (!phonebook[i].is_deleted && strcmp(phonebook[i].name, name) == 0) 
        {
            phonebook[i].is_deleted = 1;
            printf("����ó�� ���������� �����Ǿ����ϴ�.\n");
            return;
        }
    }
    printf("����ó�� �����ϴµ� �����߽��ϴ�.\n");
}

void update_contact() 
{
    char name[10];
    printf("������ �̸��� �Է��ϼ���: ");
    scanf("%s", name);

    for (int i = 0; i < count; i++) 
    {
        if (!phonebook[i].is_deleted && strcmp(phonebook[i].name, name) == 0) 
        {
            printf("���ο� �̸�: ");
            scanf("%s", phonebook[i].name);
            printf("���ο� ��ȭ��ȣ: ");
            scanf("%s", phonebook[i].phone_number);
            printf("���ο� �̸���: ");
            scanf("%s", phonebook[i].email);
            printf("���ο� �޸�: ");
            scanf("%s", phonebook[i].memo);
            printf("����ó�� ���������� �����Ǿ����ϴ�.\n");
            return;
        }
    }
    printf("����ó�� �����ϴµ� �����߽��ϴ�.\n");
}

void search_contact() 
{
    char name[10];
    printf("�˻��� �̸��� �Է��ϼ���: ");
    scanf("%s", name);

    for (int i = 0; i < count; i++) 
    {
        if (!phonebook[i].is_deleted && strcmp(phonebook[i].name, name) == 0) 
        {
            printf("�̸�: %s, ��ȭ��ȣ: %s, �̸���: %s, �޸�: %s\n", phonebook[i].name, phonebook[i].phone_number, 
                phonebook[i].email, phonebook[i].memo);
            return;
        }
    }
    printf("����ó�� ã�� �� �����ϴ�.\n");
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

    printf("---- ����ó ����Ʈ ----\n");
    for (int i = 0; i < count; i++) 
    {
        if (!phonebook[i].is_deleted) 
        {
            printf("�̸�: %s, ��ȭ��ȣ: %s, �̸���: %s, �޸�: %s\n", phonebook[i].name, phonebook[i].phone_number,
                phonebook[i].email, phonebook[i].memo);
        }
    }
}

void menu() 
{
    printf("1. ����ó �߰�\n");
    printf("2. ����ó ����\n");
    printf("3. ����ó ����\n");
    printf("4. ����ó �˻�\n");
    printf("5. ����ó ����Ʈ\n");
    printf("6. ����\n");
}

int main() 
{
    load_contact();

    int choice;
    while (1) 
    {
        menu();
        printf("����: ");
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
            printf("���α׷��� �����մϴ�.\n");
            return 0;
        default:
            printf("�Է��� �߸��Ǿ����ϴ�.\n");
        }
    }
}
