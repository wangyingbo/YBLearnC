#include <stdio.h>
#include "student.h"
#include "file.h"
#include "interface.h"



/**
 * 
 * 作者：晓亮Albert
 * 链接：https://www.zhihu.com/question/19592260/answer/3083892859
 * 
 */
int main() {
    Student students[MAX_STUDENTS];
    int count = 0;
    int choice;

    loadStudentsFromFile(students, &count);

    do {
        displayMenu();
        choice = getUserChoice();

        switch (choice) {
            case 1:
                addStudent(students, &count);
                break;
            case 2:
                displayStudents(students, count);
                break;
            case 3:
                searchStudent(students, count);
                break;
            case 4:
                updateStudent(students, count);
                break;
            case 5:
                deleteStudent(students, &count);
                break;
            case 0:
                saveStudentsToFile(students, count);
                printf("谢谢使用！\n");
                break;
            default:
                printf("无效选项，请重新输入。\n");
                break;
        }
    } while (choice != 0);

    return 0;
}