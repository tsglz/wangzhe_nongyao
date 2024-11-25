#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <locale.h>

int login() {
    setlocale(LC_CTYPE, ""); // 设置区域，以支持宽字符
    wchar_t username[50], password[50], stored_user[50], stored_pass[50];
    FILE *fp = fopen("users.txt", "r+");
    if (!fp) fp = fopen("users.txt", "w+");

    printf("请输入用户名: ");
    scanf("%ls", username);
    printf("请输入密码: ");
    scanf("%ls", password);

    while (fscanf(fp, "%s %s", stored_user, stored_pass) != EOF) {
        if (wcscmp(username, stored_user) == 0) {
            if (wcscmp(password, stored_pass) == 0) {
                fclose(fp);
                return 1; // 登录成功
            } else {
                printf("密码错误！\n");
                fclose(fp);
                return 0;
            }
        }
    }

    fprintf(fp, "%ls %ls\n", username, password);
    fclose(fp);
    printf("注册成功！\n");
    return 0;
}
