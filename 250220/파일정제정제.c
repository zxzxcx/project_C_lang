#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024  // 한 줄의 최대 길이
#define MAX_COLUMNS 100       // CSV에서 다룰 최대 열 수
#define MAX_ROWS 100          // CSV에서 다룰 최대 행 수

// 문자열 앞뒤 공백을 제거하는 함수
void trim_whitespace(char *str) {
    char *end;
    // 문자열 앞쪽 공백 제거
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return;  // 문자열이 비어 있으면 반환
    // 문자열 뒤쪽 공백 제거
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';  // 문자열 끝에 null 문자 추가
}

// CSV 파일을 읽어 데이터를 배열로 반환하는 함수
int read_csv(FILE *file, int data[MAX_ROWS][MAX_COLUMNS], int max_rows) {
    char line[MAX_LINE_LENGTH];
    int row_count = 0;

    while (fgets(line, sizeof(line), file) && row_count < max_rows) {
        trim_whitespace(line);  // 공백 제거
        char *token = strtok(line, ",");
        int col_count = 0;

        while (token != NULL) {
            trim_whitespace(token);  // 공백 제거
            data[row_count][col_count] = atoi(token);  // 숫자로 변환하여 배열에 저장
            col_count++;
            token = strtok(NULL, ",");  // 다음 토큰으로 이동
        }
        row_count++;
    }
    return row_count;  // 읽은 행의 수 반환
}

int sum_indextoindex(int data[MAX_ROWS][MAX_COLUMNS],char line[1024], int index1, int index2, int year, FILE *input_file){
	fseek(input_file, 0, SEEK_SET);  // 파일의 처음으로 되돌아가기
	
	int column_sum = 0;
	for (index1; index1 <= index2; index1++){
		column_sum += data[1][index1];
	}
	return column_sum;
}
int main() {
    FILE *input_file = fopen("C:\\Users\\user\\Desktop\\2018_asd.csv", "r");  // CSV 파일 열기
    if (input_file == NULL) {
        perror("Error opening input.csv");
        return 1;
    }

    FILE *output_file = fopen("C:\\Users\\user\\Desktop\\2018_sum.csv", "w");  // 새로운 CSV 파일 열기
    if (output_file == NULL) {
        perror("Error opening output file");
        fclose(input_file);
        return 1;
    }

    int data[MAX_ROWS][MAX_COLUMNS];  // CSV 데이터를 저장할 배열
    int row_count;

    // CSV 파일 데이터를 읽어오기
    row_count = read_csv(input_file, data, MAX_ROWS);

    // 결과 파일에 첫 번째 행을 그대로 출력 (열 이름)
    char line[MAX_LINE_LENGTH];
    fseek(input_file, 0, SEEK_SET);  // 파일의 처음으로 되돌아가기
    fgets(line, sizeof(line), input_file);
    fprintf(output_file, "%d_crime,범죄중분류,서울,부산,대구,인천,광주,대전,울산,세종,경기,강원,충북,충남,전북,전남,경북,경남,제주,기타도시,도시이외\n");  // 첫 번째 행 생성

    // 합계를 구하기
    fgets(line, sizeof(line), input_file);
	data[1][10] = sum_indextoindex(data, line, 10, 37, 2018, input_file);
	data[1][11] = sum_indextoindex(data, line, 38, 44, 2018, input_file);
	data[1][12] = sum_indextoindex(data, line, 45, 47, 2018, input_file);
	data[1][13] = sum_indextoindex(data, line, 48, 55, 2018, input_file);
	data[1][14] = sum_indextoindex(data, line, 56, 61, 2018, input_file);
	data[1][15] = sum_indextoindex(data, line, 62, 66, 2018, input_file);
	data[1][16] = sum_indextoindex(data, line, 67, 76, 2018, input_file);
	data[1][17] = sum_indextoindex(data, line, 77, 84, 2018, input_file);
	data[1][18] = sum_indextoindex(data, line, 85, 86, 2018, input_file);
	data[1][19] = sum_indextoindex(data, line, 87, 87, 2018, input_file);
	data[1][20] = sum_indextoindex(data, line, 88, 88, 2018, input_file);
	

    // 기록
    
    for (int col = 0; col < 21; col++) {
        fprintf(output_file, "%d,", data[1][col]);
    }
    fprintf(output_file, "\n");

    fclose(input_file);
    fclose(output_file);

    

    return 0;
}
