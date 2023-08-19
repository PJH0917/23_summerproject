#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

struct Word {
    char korean[50];
    char english[50];
    char hint[50];
};

int main() {
    printf("\n# English word guessing program #\n");
    printf("(If you want a hint, type 'hint')\n\n");

    struct Word words[] = {
        { "인정, 찬성; 승인", "approval", "starting with 'a', 8 letters" },
        { "참다; 감당하다; 지탱하다", "bear", "starting with 'b', 4 letters" },
        { "사로잡힌; 포로", "captive", "starting with 'c', 7 letters" },
        { "폭로", "disclosure", "starting with 'd', 10 letters" },
        { "동등한; 상당하는 것", "equivalent", "starting with 'e', 10 letters" },
        { "가능하게 하다", "facilitate", "starting with 'f', 10 letters" },
        { "원한; 억울해하다", "grudge", "starting with 'g', 6 letters" },
        { "저해하다", "hinder", "starting with 'h', 6 letters" },
        { "도입하다; 부과하다", "impose", "starting with 'i', 6 letters" },
        { "어렴풋이 보이다", "loom", "starting with 'l', 4 letters" },
        { "합병하다", "merge", "starting with 'merge', 5 letters" },
        { "스며들다", "permeate", "starting with 'p', 8 letters" },
        { "포기하다; 버리다", "renounce", "starting with 'r', 8 letters" },
        { "연대, 결속", "solidarity", "starting with 's', 10 letters" },
        { "의심할 여지없는", "unquestionable", "starting with 'u', 14 letters" },
        { "입증하다", "validate", "starting with 'v', 8 letters" },
        { "물러나다; 철회하다; 탈퇴하다", "withdraw", "starting with 'withdraw', 8 letters" },
        // 단어, 뜻, 힌트 필요한 개수만큼 추가 가능
    };

    int totalWords = sizeof(words) / sizeof(words[0]);
    int randomIndex;
    char guess[50];
    int correctCount = 0;
    int incorrectCount = 0;

    srand(time(0));

    while (correctCount + incorrectCount < totalWords) {
        // 아직 출제되지 않은 단어 중 랜덤으로 선택
        do {
            randomIndex = rand() % totalWords;
        } while (words[randomIndex].english[0] == '\0'); // 이미 출제된 단어인 경우 다시 선택

        printf("%s\n", words[randomIndex].korean);
        scanf("%s", guess);

        // 힌트를 원하는 경우 힌트 제공, 이어서 문제 풀기
        if (strcmp(guess, "hint") == 0) {
            printf("%s\n\n", words[randomIndex].hint);
            printf("%s\n", words[randomIndex].korean);
            scanf("%s", guess);
        }

        // 정답을 비교하여 정답 여부를 판단하고 결과 제공
        if (strcmp(guess, words[randomIndex].english) == 0) {
            printf("Correct!\n\n");
            correctCount++;
        }
        else {
            printf("Incorrect. The answer is %s.\n\n", words[randomIndex].english);
            incorrectCount++;
        }

        // 이미 출제된 단어로 표시하여 중복 출제 방지
        words[randomIndex].english[0] = '\0';
    }

    // 모든 문제를 푼 후 피드백 제공
    printf("*** RESULT ***\n");
    printf("Number of correct words: %d\n", correctCount);
    printf("Number of incorrect words: %d\n", incorrectCount);
    printf("Accuracy: %.2f%%\n\n", (float)correctCount / totalWords * 100);

    // 다시 시도 여부를 묻는 메시지 출력
    char tryAgain;
    printf("You've completed all the words. Do you wanna try again? (y/n): ");
    scanf(" %c", &tryAgain);

    if (tryAgain == 'y' || tryAgain == 'Y') {
        // 사용자가 다시 시도하는 경우 - 출제된 단어를 초기화하고 게임 재시작
        for (int i = 0; i < totalWords; i++) {
            words[i].english[0] = words[i].korean[0]; // 재출제를 위해 영어 단어를 다시 초기화
        }
        correctCount = 0;
        incorrectCount = 0;
        main(); // 함수를 재호출하여 게임 재시작
    }
    else {
        // 사용자가 재시도하지 않는 경우 - 프로그램 종료
        printf("Thank you for playing!\n");
    }
    return 0;
}
