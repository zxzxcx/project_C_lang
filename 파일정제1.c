#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024
#define MAX_COLUMNS 100
#define MAX_CRIMES 8  

struct CrimeData {
    char crime_name[100];
    char crime_sname[100];
    int occurrences[MAX_COLUMNS - 1];
};

void trim_whitespace(char *str) {
    char *end;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return;

    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
}

int parse_int(const char *str) {
    int value = 0;
    if (sscanf(str, "%d", &value) != 1) {
        return -1;
    }
    return value;
}

void process_year(int year) {
    char input_path[256];
    char output_path[256];

    sprintf(input_path, "C:\\Users\\user\\Desktop\\%d_crime.csv", year);
    sprintf(output_path, "C:\\Users\\user\\Desktop\\%d_total.csv", year);

    FILE *input_file = fopen(input_path, "r");
    if (input_file == NULL) {
        printf("File open failed: %s\n", input_path);
        return;
    }

    FILE *output_file = fopen(output_path, "w");
    if (output_file == NULL) {
        printf("File write failed: %s\n", output_path);
        fclose(input_file);
        return;
    }

    char line[MAX_LINE_LENGTH];
    struct CrimeData crimes[MAX_CRIMES]; 
    memset(crimes, 0, sizeof(crimes));  // 배열 전체 초기화

    int row_count = 0;
    int column_count = 0;

    // 헤더 처리
    if (fgets(line, sizeof(line), input_file)) {
        trim_whitespace(line);
        char *token = strtok(line, ",");

        fprintf(output_file, "%d_crime", year);
        while (token != NULL) {
            trim_whitespace(token);
            if (column_count > 0) {
                fprintf(output_file, ",%s", token);
            }
            column_count++;
            token = strtok(NULL, ",");
        }
        fprintf(output_file, "\n");
    }

    // 데이터 읽기 (최대 8행만 강력범죄까지)
    while (fgets(line, sizeof(line), input_file) && row_count < MAX_CRIMES) {
        trim_whitespace(line);
        char *token = strtok(line, ",");
        int col_index = 0;  // 0부터 시작하도록 수정

        memset(&crimes[row_count], 0, sizeof(struct CrimeData));  // 한 행을 저장할 때 초기화

        if (token != NULL) {
            trim_whitespace(token);
            strncpy(crimes[row_count].crime_name, token, sizeof(crimes[row_count].crime_name) - 1);
            crimes[row_count].crime_name[sizeof(crimes[row_count].crime_name) - 1] = '\0';
        } else {
            continue;  // 빈 행은 건너뛰기
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            trim_whitespace(token);
            strncpy(crimes[row_count].crime_sname, token, sizeof(crimes[row_count].crime_sname) - 1);
            crimes[row_count].crime_sname[sizeof(crimes[row_count].crime_sname) - 1] = '\0';
        }

        token = strtok(NULL, ",");
        while (token != NULL && col_index < MAX_COLUMNS - 1) {
            trim_whitespace(token);
            int occurrences = parse_int(token);
            if (occurrences >= 0) {  // 유효한 숫자만 저장
                crimes[row_count].occurrences[col_index] = occurrences;
            }
            col_index++;
            token = strtok(NULL, ",");
        }

        // 유효한 데이터인지 확인 후 저장
        if (strlen(crimes[row_count].crime_name) > 0) {
            fprintf(output_file, "%s,", crimes[row_count].crime_name);
            fprintf(output_file, "%s", crimes[row_count].crime_sname);
            for (int i = 0; i < col_index; i++) {  // 실제 데이터 개수만큼 출력
                fprintf(output_file, ",%d", crimes[row_count].occurrences[i]);
            }
            fprintf(output_file, "\n");

            row_count++;  // 유효한 데이터가 저장된 경우에만 증가
        }
    }

    fclose(input_file);
    fclose(output_file);
}

int main() {
    for (int year = 2018; year <= 2022; year++) {
        process_year(year);
    }

    printf("Processing complete.\n");
    return 0;
}
