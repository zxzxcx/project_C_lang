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
		double ratio;
	};
    FILE *file = fopen("C:\\Users\\user\\Desktop\\f1.csv", "r"); // 경로
    if (!file) {
        perror("File open failed.\n");  // 오류 메시지 출력
        return; // 파일 열기에 실패하면 종료
    }
	struct file_Crime crime[500];
	FILE *fileWrite = fopen("C:\\Users\\user\\Desktop\\f1out.csv", "w");  // 파일 열기 (쓰기 모드)
	if (fileWrite == NULL) {
        printf("File open failed.\n");
        return 1;
    }
	fprintf(fileWrite, "소분류,발생,검거,검거비율\n");
	
    char line[1024];
    char * token;
    int cnt = 0;
    int cnt_Outbreak_Max = 0;
    int outbreak_Max = 0;
    int cnt_Outbreak_Min = 0;
    int outbreak_Min_Notzero = 9999;
    int cnt_Ratio_Max = 0;
    double ratio_Max = 0;
    int cnt_Ratio_Min = 0;
    double ratio_Min_Notzero = 9.0;
    int sum_Outbreak = 0;
    int sum_Arrest = 0;
    double total_Ratio;

   
		fgets(line, sizeof(line), file);
	    while (fgets(line, sizeof(line), file)) {  // 한 줄씩 파일에서 읽기
        // 파일에서 읽은 내용 출력
        //printf("read Line : %s\n", line);
        
        token = strtok(line, ",");
        token = strtok(NULL, ",");
        token = strtok(NULL, ",");  // 첫 번째 컬럼(이름)
        if (token != NULL) {
            strncpy(crime[cnt].name, token, sizeof(crime[cnt].name) - 1);  // 이름 저장
            crime[cnt].name[sizeof(crime[cnt].name) - 1] = '\0';  // 안전하게 문자열 종료 처리
        }

        token = strtok(NULL, ",");  // 두 번째 컬럼(발생 수)
        if (token != NULL) 
		{
            crime[cnt].outbreak = atoi(token);  // 문자열을 정수로 변환하여 저장
            sum_Outbreak += crime[cnt].outbreak;
            if (crime[cnt].outbreak > outbreak_Max)
            {
            	cnt_Outbreak_Max = cnt;
            	outbreak_Max = crime[cnt].outbreak;
			}
			if (crime[cnt].outbreak < outbreak_Min_Notzero && crime[cnt].outbreak != 0)
            {
            	cnt_Outbreak_Min = cnt;
            	outbreak_Min_Notzero = crime[cnt].outbreak;
			}
        }
		
        token = strtok(NULL, ",");  // 세 번째 컬럼(체포 수)
        if (crime[cnt].outbreak == 0 && crime[cnt].arrest == 0)	//발생수 검거수 0이면 스킵 
        {
        	continue;
		}
        if (token != NULL) 
		{
            crime[cnt].arrest = atoi(token);  // 문자열을 정수로 변환하여 저장
            sum_Arrest += crime[cnt].arrest;
            
        }

        // 비율 계산: 체포 수 / 발생 수 (0으로 나누는 것을 방지하기 위해 조건 추가)
        if (crime[cnt].outbreak != 0) {
            crime[cnt].ratio = (double)crime[cnt].arrest / (double)crime[cnt].outbreak;
        } else {
            crime[cnt].ratio = 0.0;  // 발생 수가 0일 경우 비율을 0으로 처리
        }
        if (crime[cnt].ratio > ratio_Max)
        {
           	cnt_Ratio_Max = cnt;
         	ratio_Max = crime[cnt].ratio;
		}
		if (crime[cnt].ratio < ratio_Min_Notzero && crime[cnt].ratio != 0.0)
        {
           	cnt_Ratio_Min = cnt;
           	ratio_Min_Notzero = crime[cnt].ratio;
		}        
        

		//파일입력
		fprintf(fileWrite, "%s,", crime[cnt].name);
		fprintf(fileWrite, "%d,", crime[cnt].outbreak);
		fprintf(fileWrite, "%d\n", crime[cnt].arrest);
		
		
		
        // 결과 출력
        printf("crime name: %s, outbreak : %d, arrest : %d, ratio : %.4f\n", 
               crime[cnt].name, crime[cnt].outbreak, crime[cnt].arrest, crime[cnt].ratio);

        cnt++;  // 데이터 개수 증가
    }
    
    total_Ratio = (double)sum_Arrest / (double)sum_Outbreak;
    printf("=== Results ===\n");
    printf("Maximum outbreak count: %d (Crime type: %s)\n", outbreak_Max, crime[cnt_Outbreak_Max].name);
    printf("Minimum outbreak count (non-zero): %d (Crime type: %s)\n", outbreak_Min_Notzero, crime[cnt_Outbreak_Min].name);
    printf("Maximum ratio: %.4f (Crime type: %s)\n", ratio_Max, crime[cnt_Ratio_Max].name);
    printf("Minimum ratio (non-zero): %.4f (Crime type: %s)\n", ratio_Min_Notzero, crime[cnt_Ratio_Min].name);
    printf("Total outbreak count: %d\n", sum_Outbreak);
    printf("Total arrest count: %d\n", sum_Arrest);
    printf("Overall ratio (Total arrest / Total outbreak): %.4f\n", total_Ratio);

	    

    fclose(file);
}
