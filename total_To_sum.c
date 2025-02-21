#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024  // 한 줄의 최대 길이
#define MAX_COLUMNS 100       // CSV에서 다룰 최대 열 수
#define MAX_ROWS 100          // CSV에서 다룰 최대 행 수
#define NUM_YEARS 6           // 2018-2023까지의 년도

// 문자열 앞뒤 공백을 제거하는 함수
void trim_whitespace(char *str) {
    char *end;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
}

// CSV 파일을 읽어 데이터를 배열로 저장하는 함수
int read_csv(FILE *file, int data[MAX_ROWS][MAX_COLUMNS], char string_data[MAX_ROWS][2][MAX_LINE_LENGTH], int max_rows) {
    char line[MAX_LINE_LENGTH];
    int row_count = 0;

    // 첫 번째 줄(헤더) 스킵
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file) && row_count < max_rows) {
        trim_whitespace(line);
        char *token = strtok(line, ",");
        int col_count = 0;

        while (token != NULL) {
            trim_whitespace(token);
            if (col_count < 2) {
                // 첫 2개 열은 문자열로 저장
                strncpy(string_data[row_count][col_count], token, MAX_LINE_LENGTH);
                string_data[row_count][col_count][MAX_LINE_LENGTH - 1] = '\0';
            } else {
                // 숫자로 변환하여 저장
                data[row_count][col_count - 2] = atoi(token);
            }
            col_count++;
            token = strtok(NULL, ",");
        }
        row_count++;
    }
    return row_count;
}

// 특정 범위의 열 합산 함수
int sum_indextoindex(int data[MAX_ROWS][MAX_COLUMNS], int row, int index1, int index2) {
    int column_sum = 0;
    for (int i = index1; i <= index2; i++) {
        column_sum += data[row][i];
    }
    return column_sum;
}

int main() {
    FILE *output_file = fopen("C:\\Users\\user\\Desktop\\2018_2022_sum.csv", "w");
    if (output_file == NULL) {
        perror("Error opening output file");
        return 1;
    }

    int data[MAX_ROWS][MAX_COLUMNS];  // CSV 데이터를 저장할 배열
    char string_data[MAX_ROWS][2][MAX_LINE_LENGTH]; // 문자열 데이터 저장
    int row_count;

    // 결과 파일에 첫 번째 행을 그대로 출력 (열 이름)
    fprintf(output_file, "년도,범죄번호,범죄중분류,서울,부산,대구,인천,광주,대전,울산,세종,경기,강원,충북,충남,전북,전남,경북,경남,제주,기타도시,도시이외\n");

    // 2018부터 2022년까지의 데이터를 처리
    for (int year = 2018; year <= 2022; year++) {
        char input_file_name[50];
        snprintf(input_file_name, sizeof(input_file_name), "C:\\Users\\user\\Desktop\\%d_total.csv", year);
        FILE *input_file = fopen(input_file_name, "r");
        if (input_file == NULL) {
            perror("Error opening input file");
            fclose(output_file);
            return 1;
        }

        // CSV 파일 데이터를 읽어오기
        row_count = read_csv(input_file, data, string_data, MAX_ROWS);

        // 모든 행 처리
        for (int row = 0; row < row_count; row++) {
            // 특정 열 범위를 합산하여 저장
            data[row][10] = sum_indextoindex(data, row, 10, 37);
            data[row][11] = sum_indextoindex(data, row, 38, 44);
            data[row][12] = sum_indextoindex(data, row, 45, 47);
            data[row][13] = sum_indextoindex(data, row, 48, 55);
            data[row][14] = sum_indextoindex(data, row, 56, 61);
            data[row][15] = sum_indextoindex(data, row, 62, 66);
            data[row][16] = sum_indextoindex(data, row, 67, 76);
            data[row][17] = sum_indextoindex(data, row, 77, 84);
            data[row][18] = sum_indextoindex(data, row, 85, 86);
            data[row][19] = sum_indextoindex(data, row, 87, 87);
            data[row][20] = sum_indextoindex(data, row, 88, 88);

            // 결과를 CSV로 기록 (각 년도별로 기록)
            fprintf(output_file, "%d,%s,%s", year, string_data[row][0], string_data[row][1]);
            for (int col = 0; col < 19; col++) {
                fprintf(output_file, ",%d", data[row][col]);
            }
            fprintf(output_file, "\n");
        }

        fclose(input_file);  // 파일 닫기
    }

    fclose(output_file);  // 결과 파일 닫기
    return 0;
}
