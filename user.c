#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <locale.h>

int login() {
    setlocale(LC_CTYPE, ""); // ����������֧�ֿ��ַ�
    wchar_t username[50], password[50], stored_user[50], stored_pass[50];
    FILE *fp = fopen("users.txt", "r+");
    if (!fp) fp = fopen("users.txt", "w+");

    printf("�������û���: ");
    scanf("%ls", username);
    printf("����������: ");
    scanf("%ls", password);

    while (fscanf(fp, "%s %s", stored_user, stored_pass) != EOF) {
        if (wcscmp(username, stored_user) == 0) {
            if (wcscmp(password, stored_pass) == 0) {
                fclose(fp);
                return 1; // ��¼�ɹ�
            } else {
                printf("�������\n");
                fclose(fp);
                return 0;
            }
        }
    }

    fprintf(fp, "%ls %ls\n", username, password);
    fclose(fp);
    printf("ע��ɹ���\n");
    return 0;
}
