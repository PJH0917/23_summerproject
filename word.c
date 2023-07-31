#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORD_LENGTH 100
#define MAX_MEANING_LENGTH 100
#define MAX_DICTIONARY_SIZE 100

typedef struct {
    char word[MAX_WORD_LENGTH];
    char meaning[MAX_MEANING_LENGTH];
} WordEntry;

void shuffleArray(int* array, int size) {//배열의 순서 무작위로 섞기 피셔-예이츠 셔플 알고리즘 사용
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

int main() {
    
    srand(time(NULL));

    
    WordEntry dictionary[MAX_DICTIONARY_SIZE];

    
    const char* filePath = "C:\\Users\\a9125\\OneDrive\\바탕 화면\\words.txt";//사용자의 메모장 저장 위치를 기입(사용자마다 다르기에 수정 필요)

    
    FILE* file = fopen(filePath, "r");//파일 불러오기 오류 발생 시 출력
    if (file == NULL) {
        printf("사전 파일을 열 수 없습니다.\n");
        return 1;
    }

    // 단어 개수 및 사전 데이터 초기화
    int wordCount = 0;
    char line[MAX_WORD_LENGTH + MAX_MEANING_LENGTH + 2];
    while (fgets(line, sizeof(line), file)) {
        
        line[strcspn(line, "\n")] = '\0';

        // 단어와 뜻 처리 tab을 통해 처리함
        char* word = strtok(line, "\t");
        char* meaning = strtok(NULL, "\t");

        if (word != NULL && meaning != NULL) {
            strncpy(dictionary[wordCount].word, word, sizeof(dictionary[wordCount].word));
            strncpy(dictionary[wordCount].meaning, meaning, sizeof(dictionary[wordCount].meaning));
            wordCount++;
        }
    }

    fclose(file);

    // 무작위로 30개의 단어 선택(시럼지가 30문제로 나올 예정이기에 30개가 기준임. 이 부분은 이용자의 선호에 따라 개수를 바꿀 수 있음;다만 30과 관련된 모든 수를 변경해야 된다)
    if (wordCount > 0) {//단어 데이터가>0 즉 존재할 때 실행
        int randomIndices[MAX_DICTIONARY_SIZE];//무작위 인덱스 배열 생성
        for (int i = 0; i < wordCount; i++) {
            randomIndices[i] = i;
        }

        shuffleArray(randomIndices, wordCount);//초반부에 서술한 알고리즘을 이용해 배열 무작위로 섞기

        printf("=== 영단어 암기 프로그램 ===\n");
        printf("30개의 영단어 뜻을 맞춰보세요.\n");

        int score = 0;
        for (int i = 0; i < 30 && i < wordCount; i++) {//기준은 마찬가지로 30개
            int index = randomIndices[i];
            WordEntry* entry = &dictionary[index];

            printf("\n단어 #%d: %s\n", i + 1, entry->word);//단어 제시

            char userMeaning[MAX_MEANING_LENGTH];//입력한 단어 얻기
            printf("뜻을 입력하세요: ");
            fgets(userMeaning, sizeof(userMeaning), stdin);

            
            userMeaning[strcspn(userMeaning, "\n")] = '\0';

            if (strcmp(userMeaning, entry->meaning) == 0) {
                printf("정답입니다!\n");
                score++;
            }
            else {
                printf("틀렸습니다. 정답은 '%s'입니다.\n", entry->meaning);
            }
        }

        printf("\n암기 점수: %d / 30\n", score);//최종 점수를 보여준다
    }
    else {//메모장에 기빙된 단어가 없을 시 출ㄹ력한다
        printf("사전에 단어가 없습니다.\n");
    }

    return 0;
}
//주의사항:한글 특성상 언어가 영어가 아니기에 깨지는 오류가 발생할 수가 있는데, 단어장인 메모장을 ansi형태로 인코딩하여 저장한다면 해걀이 된다.
//또한 단어장을 만들 떄 프로그램에 작성된대로 뜻과 영어 단어를 tab으로 구분하여 작성해야된다 (형식은{영어단어tab뜻})
/*
예시
apple	사과
banana	바나나
carrot	당근
dog	개
elephant	코끼리
fox	여우
grape	포도
hat	모자
ice cream	아이스크림
jacket	재킷
kangaroo	캥거루
lion	사자
mango	망고
nut	견과류
orange	오렌지
pencil	연필
queen	여왕
rabbit	토끼
strawberry	딸기
tiger	호랑이
umbrella	우산
vase	꽃병
watermelon	수박
xylophone	실로폰
yacht	요트
zebra	얼룩말
ear	귀
mouth	입
time	시간
wind	바람

이런식으로 작성하면 된다




*/