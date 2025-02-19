#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
	struct file_Crime 
	{
		char name[100];
		int outbreak;
		int arrest;
		
	};
    FILE *file = fopen("C:\\Users\\user\\Desktop\\f1.csv", "r"); // 경로
    if (!file) {
        perror("File open failed");  // 오류 메시지 출력
        return; // 파일 열기에 실패하면 종료
    }
	struct file_Crime crime[500];
	
    char line[1024];
    char * token;
    int cnt = 0;

    while (fgets(line, sizeof(line), file)) { 
    	
        token = strtok(line, ",");
        token = strtok(NULL, ",");
        token = strtok(NULL, ",");
        printf("%s ", token);
        //crime[cnt].name = token;
        //printf("%s ", crime[cnt].name);
        token = strtok(NULL, ",");
        crime[cnt].outbreak = token;
        printf("%s ", crime[cnt].outbreak);
        token = strtok(NULL, ",");
        printf("%s\n", crime[cnt].arrest);
        crime[cnt].arrest = token;
        cnt++;
    }
    fclose(file);
}
