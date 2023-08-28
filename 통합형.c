#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h> 
#include <stdbool.h>

#define MAX_WORD_LENGTH 100
#define MAX_MEANING_LENGTH 100
#define MAX_DICTIONARY_SIZE 100
#define NUM_WORDS 20
#define DISPLAY_TIME 1000 // 단어 한 개 보여주는데 드는 시간 1초 (밀리초 단위로 표현)
#define INPUT_TIME 5000  // 단어 한 개 입력하는데 주어진 시간 5초 (밀리초 단위)
#define N 41

int see();
int memorize();


struct Word {
    char korean[50];
    char english[50];
    char hint[50];
};

typedef struct {
    char word[MAX_WORD_LENGTH];
    char meaning[MAX_MEANING_LENGTH];
} WordEntry;
void print_start()
{
    printf("Select the game!!!\n");
    printf("1. animal_quiz\n");
    printf("2. city_quiz\n");
    printf("3. fruit_quiz\n");
}
void shuffleArray(int* array, int size);
void showing_word(char* word); // 단어를 보여준다
void fade_away(); // 화면 사라지게 함
int arrange(const void* a, const void* b); // qsort 함수에 사용할 비교 함수


int main()
{
    int pjh0917 = 0;

    int point = 0;
    char* animal_quiz[NUM_WORDS] = {
        "human","tiger","dragon","monkey","bird",
        "cormorant","armadillo","pigeon","parrot","dog",
        "cat","killer whale","anteater","sloth","fox",
        "jaguar","puma","capybara","lion","boar"
    }; // 출제될 단어들

    char* city_quiz[NUM_WORDS] = {
        "Seoul","Busan","Suwon","Rome","Madrid",
        "Beijng","New York","London","Cairo","Berlin",
        "Athene","Istanbul","Barcelona","Manchester","Moscow",
        "Pyongyang","Dubai","Toronto","Manhatton","Shanghai"
    };// 출제될 도시 단어들

    char* fruit_quiz[NUM_WORDS] = {
        "apple","pear","watermelon","melon","banana",
        "mango","lemon","peach","plum","grape",
        "cherry","kiwi","coconut","pineapple","strawberry",
        "rasberry","blackberry","papaya","durian"
    };//출제될 과일 단어들



    
    int a = 0;


    printf("쓰고 싶은 프로그램 선택하세요:\n1.메모장 단어장 프로그램\n2.타임어택 단어 게임\n3.?\n4.?\n");
    scanf("%d", &pjh0917);
    getchar();

    switch (pjh0917)
    {
    case 1:

        //////////////////

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
        break;


    case 2:

        print_start();
        int selection;
        scanf_s("%d", &selection);
        char** quiz_selected = NULL;
        int num_words = 0;

        switch (selection)
        {
        case 1:
            quiz_selected = animal_quiz;
            num_words = sizeof(animal_quiz) / sizeof(animal_quiz[0]);
            break;
        case 2:
            quiz_selected = city_quiz;
            num_words = sizeof(city_quiz) / sizeof(city_quiz[0]);
            break;
        case 3:
            quiz_selected = fruit_quiz;
            num_words = sizeof(fruit_quiz) / sizeof(fruit_quiz[0]);
            break;
        default:
            printf("It's not a proper number.\n");
            return 0;
        }

        



      

        printf("Press Enter to start the game!!");
        getchar(); // 입력을 받는다


          // 단어들을 글자 순으로 정렬
        qsort(quiz_selected, NUM_WORDS, sizeof(char*), arrange);



        for (int i = 0; i < NUM_WORDS; i++)
        {
            printf("\nCurrent Score: %d\n", point);
            showing_word(quiz_selected[i]); // 매개변수 quiz_selected[i]의 단어를 매개변수로 받음
            Sleep(DISPLAY_TIME); // Sleep 함수를 사용하여 display_time의 시간 1초만큼 일시정지를 시키는 것
            fade_away();

            printf("\n%s", "Enter the word: ");
            time_t timestart = time(NULL); // time(NULL) 함수는 시스템의 현재 시간을 초 단위로 반환, time_t는 시간 정보를 저장하는 데이터 형식, 게임에서 시간 제한을 구현하는데 사용하는 코드. timestart에 현재 시간을 저장함으로써 플레이어가 단어를 입력하기 시작한 시간을 기록.

            while (difftime(time(NULL), timestart) * 1000 <= INPUT_TIME) // c언어에서 difftime 함수는 시차를 계산할 때 사용, difftime(time(NULL), timestart)는 현재 시간과 timestart 사이의 차이를 초 단위로 반환.
            {
                if (_kbhit()) // 키가 키보드에서 눌렸는지 확인한다.
                {
                    char wordinput[200];

                    fgets(wordinput, sizeof(wordinput), stdin); // stdin에서 사용자가 키보드로 입력한 문자열을 wordinput 배열에 저장한다. sizeof(wordinput)는 wordinput 배열의 크기를 나타낸다. 입력받을 최대 문자열 길이를 제한한다->오버플로우 방지, stdin 사용해서 키보드로 입력한 문자열을 프로그램에서 받아온다. fgets 함수 자체가 입력된 문자들과 함께 개행문자를 입력버퍼에서 가져온다.

                    wordinput[strcspn(wordinput, "\n")] = '\0'; // 현재 사용자가 입력한 문자열은 wordinput에 저장되어 있다. strcspn은 wordinput 문자열에서 개행문자 "\n"이 처음으로 나타나는 위치를 찾아서 반환한다. 그리고 이것을 널로 바꿔준다.

                    if (strcmp(wordinput, quiz_selected[i]) == 0) // strcmp는 문자열을 비교하는 함수 string.h에서 가져온다. strcmp는 ()안에 비교하려는 문자열이 같으면 0이라고 한다.
                    {
                        point += 1;
                    }
                    else
                    {
                        point -= 1;
                    }
                    break;
                }
            }

            showing_word("Next word will appear!!!");
            Sleep(DISPLAY_TIME);
            fade_away();
        }

        printf("\n\nGame Over! Your Record is %d\n", point);

        return 0;
        break;


    case 3:


        printf("***프로그램 용어 단어장***\n\n");
        printf("보기용을 보시려면 '1', 암기용를 보시려면 '2'를 눌러주세요.\n");
        scanf(" %d", &a);

        if (a == 1) {
            see();
        }
        else if (a == 2) {
            memorize();
        }
        else {
            while (1) {
                printf("'1'또는 '2' 둘 중에 하나를 골라주십시오.\n");
                scanf(" %d", &a);
                if (a == 1) {
                    see();
                    break;
                }
                else if (a == 2) {
                    memorize();
                    break;
                }
            }
        }
        return 0;

        break;


    case 4:
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
}


void showing_word(char* word)
{
    printf("\n****************************************\n");
    printf("            wordinput:%s                \n", word);
    printf("\n****************************************\n");
}

void fade_away()
{
    system("cls"); // window 운영체제에서 사용하는 것. 현재 화면에 출력된 내용을 모두 지워주는 것. cls -> clear screen
}

int arrange(const void* a, const void* b)
{
    // 글자 수를 비교하여 정렬
    return strlen(*(char**)a) - strlen(*(char**)b);
}

void shuffleArray(int* array, int size) {//배열의 순서 무작위로 섞기 피셔-예이츠 셔플 알고리즘 사용
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

int see() {
    printf("여기서부터는 '보기용' 단어장입니다.\n");

    char list1[N][20] = { "전처리", "컴파일","링크" "함수","printf ","Stdio.h", " 제어문자","상수","변수","int",
    "double","char","Scanf","산술연산자","대입연산자","증감연산자","관계연산자","논리연산자","sizeof연산자","조건연산자",
    "if문","if~else문", "If~else if~else문","Switch~case문","while문", "함수 선언","함수 정의","함수 호출","배열", "gets",
    "for문","do~while문","gets", "puts",  "포인터","strcpy","strlen","strcat", "strcmp","지역변수",
    "전역변수","정적지역변수" };//42개

    char list2[N][100] = { "NULL","NULL","NULL","NULL",  "printf(“  ”);" , "Include <stdio.h> ","NULL", "Ex. 태어난 시간(장소), 생물학적 부모님 ",  "Ex. 나이, 키, 몸무게",
    "int age; ","double height; ", "char food; ", "scanf(“%d”, &a); ", "c=a+b;,c=a-b;c=a/b;, c=a*b; c=a%b; ", "=  ",
    "++a;, b++;, --c;, d--; ", "a>b;, a<b;, a>=b;, a<=b;, a==b;, a!=b; ","(a>10)&&(a>7);,(a>10)||(a>7);,!(a>10); ",
     "sizeof(변수명 또는 자료형) ","(조건) ? (참일 시) : (거짓일 시);", "If(조건식) 실행문; ", "if(조건문) 실행문1; else 실행문2; ",
    " else if (조건문2) 실행문2;else 실행문; ", "switch(조건식){ case상수식1; 실행문; break;case 상수식2; 실행문; break;default; 실행문; break; } ",
     "while(조건식){ 실행문; } ", "변수형 함수명(변수명,1 변수명2); ", "변수형 함수 이름(변수명1,변수명2){기능; reture 반환값;} ",
    "함수이름(변수명3,변수명4) ; ", "자료형 배열명[N]={값1,값2,값3.....값N}; ","for(초기식; 조건식; 증감식){ 실행문; } ",
    "Do{실행문; }while (조건식); ",  "gets(배열명); ","puts(배열명); ", "변수형 *포인터명=&변수명 ",
    "Strcpy(문자열1,문자열2); ","Strlen(문자열); ", "Strcat(문자열1, 문자열2); ",  "strcmp (문자열1, 문자열2); ",
     "함수 안에서 변수 선언 ", "함수밖에서 변수 선언 ","static 변수형 변수명;  " };

    char list3[N][250] = {
     "전처리 지시자에 따라 소스파일을 가공하는 과정"
    ,"CPU가 해설할 수 있는 명령어들로 구성된 개체파일로 바꾸는 과정 "
    ,"개체파일에 startup code를 결합하는 과정 "
    ,"머리(함수 원형)와 몸통으로 구성되어 있다. "
    ,"화면에 데이터를 일정한 형식에 따라 출력할 수 있다."
    ,"C언어에서 기본으로 사용하는 입출력 함수가 들어가 있다."
    ,"NULL"
    ,"값이 변하지 않는 데이터 "
    ,"값이 바뀌는 데이터 "
    ,"변수형 중 하나로 정수를 넣을 수 있다. 관련된 출력 변환 문자: %d "
    ,"변수형 중 하나로 실수를 넣을 수 있다. 관련된 출력 변환 문자: %lf "
    ,"변수형 중 하나로 실수를 넣을 수 있다. 관련된 출력 변환 문자: %lf "
    ,"입력 문자들을 스캔하여 원하는 형태의 데이터를 변수에 삽입할 수 있다. *주의사항: 문자열 변환문자를 제외한 변수명 앞에 &를 붙여야 정상적으로 작동한다. 또한 띄어쓰기를 할 시 뒤 문장은 인식하지 못한다 "
    ,"덧셈, 뺄셈, 나눗셈, 곱셈, 나머지를 계산하는 연산자 "
    ,"변수에 값을 대입하는 연산자 "
    ,"변수의 값을 1씩 증가시키거나 감소시킬 수 있다. 변수명 앞에 있으면 계산 전에, 뒤에 있으면 계산 후에 변수값을 변경시킨다"
    ,"“크다, 작다, 크거나 같다, 작거나 같다, 같다, 같지 않다” 와 같이 변수 간의 관계를 계산한다. 컴퓨터는 ‘0’를 거짓, ‘0’를 제외한 모든 수를 참이라고 판단한다.(보통 참의 표시로’1’를 쓰곤 한다) "
    ,"집합에서 쓰이는 합집합, 교집합, 여집합를 뜻하며 참과 거짓을 판단하는데 쓰이는 연사자 "
    ,"피연산자의 크기를 바이트 단위로 계산해서 알려줄 수 있는 연산자 "
    ,"조건이 참이냐 거짓이냐에 따라 다른 명령을 수행하도록 하는 연산자 "
    ,"조건식이 참일 시 실행문 실행, 거짓이면 아무것도 실행하지 않음. "
    ,"조건식1이 참이면 실행문1만 실행, 조건식2이 참이면 실행문2을 실행함"
    ,"조건이 참이냐 거짓이냐에 따라 다른 명령을 수행하도록 하는 연산자 "
    ,"조건이 참이냐 거짓이냐에 따라 다른 명령을 수행하도록 하는 연산자 "
    ,"조건이 참이냐 거짓이냐에 따라 다른 명령을 수행하도록 하는 연산자 "
    ,"형식이 while문과 다르긴 하지만 원리는 똑같다. 정확한 숫자를 반복하기에 유용하다. "
    ,"특이하게 실행문을 무조건 실행한 후 조건에 맞으면 반복이 되는 반복문으로 무조건 한 번은 실행되어야 한다면 해당 반복문을 쓰는 게 효율적이다. "
    ,"함수의 형태를 알리며, 컴퓨터가 함수의 존재를 인식할 수 있도록 코드 처음에 함수 선언을 써 놓는다.  "
    ,"해당 함수의 기능을 구현한다. 보통 메인 코드 앞에 놓아 함수선언을 하는 귀찮음을 없앤다. "
    ,"함수를 사용하는 명령어로 함수에 필요한 값을 인수로 준다. "
    ,"각 변수가 일련의 연관성이 있을 경우, 효율성을 위해 사용하곤 한다. *주의 사항: 변수의 요소는 0~N-1이다. 2차원,3차원 배열도 있다. "
    ,"Scanf과 같이 문자열을 받을 수 있으나 띄어쓰기를 하면 뒤는 나오지 않는 Scanf와 달리 Enter직전까지 모든 문자열이 다 저장된다. 하지만 입력한 배열의 크기를 검사하지 않기 때문에 오류가 생길 수도 있으니 주의해야한다. "
    ,"Printf와 같은 기능을 수행하지만 출력 후 수동으로 줄을 바꿔줘야하는 printf와 달리 자동으로 줄을 바꿔준다.  "
    ,"NULL"
    ,"문자열2를 문자열1에 복사한다. "
    ,"문자열의 길이(문자수)를 구해 반환시킨다. "
    ,"문자열2에다가 문자열1를 이어붙임 "
    ,"문자열1이 문자열2보다 크면 1반환하고 무자열1이 문자열2보다 작으면 -1반환, 둘이 같은 문자열이면 0반환한다. "
    ,"지역변수란 일정한 지역에서만 사용할 수 있는 변수를 뜻합니다. 그렀기 때문에 이름이 같아도 선언된 함수가 다르다면 가각 독립된 저장공간을 갖습니다. 메모리를 효율적으로 사용 가능하며 디버깅에 유리하기 때문에 사용합니다. "
    ,"코드의 모든 함수 내외에서 사용이 가능합니다. 그렀기 때문에 여러 함수에서 쉽게 공유가능하다는 장점이 있지만 용량을 많이 사용하며 전역변수의 값이 잘못된다면 전역 변수가 사용된 모든 함수를 고쳐야 한다는 단점이 있습니다. "
    ,"프로그램이 실행될 동안에 계속 유지되므로써 함수가 끝나면 초기화되는 지역변수와 차이가 있다. "
    };
    int q = 1;
    for (int p = 0; p < N; p++) {
        printf("\n%d.%s", q, list1[p]);
        q++;
        printf("\n:");
        printf("%s\n", list3[p]);
        printf("형식: %s\n", list2[p]);
    }
}


int memorize() {
    int b = 0;
    printf("여기서부터는 '암기용' 단어장입니다.\n");
    printf("용어 가림막으로 볼려면 '1', 설명 가림막으로 볼려면 '2'를 눌러주세요.\n");
    scanf("%d", &b);
    char list1[N][20] = { "전처리", "컴파일","링크" "함수","printf ","Stdio.h", " 제어문자","상수","변수","int",
 "double","char","Scanf","산술연산자","대입연산자","증감연산자","관계연산자","논리연산자","sizeof연산자","조건연산자",
 "if문","if~else문", "If~else if~else문","Switch~case문","while문", "함수 선언","함수 정의","함수 호출","배열", "gets",
 "for문","do~while문","gets", "puts",  "포인터","strcpy","strlen","strcat", "strcmp","지역변수",
 "전역변수","정적지역변수" };//42개

    char list2[N][100] = { "NULL","NULL","NULL","NULL",  "printf(“  ”);" , "Include <stdio.h> ","NULL", "Ex. 태어난 시간(장소), 생물학적 부모님 ",  "Ex. 나이, 키, 몸무게",
    "int age; ","double height; ", "char food; ", "scanf(“%d”, &a); ", "c=a+b;,c=a-b;c=a/b;, c=a*b; c=a%b; ", "=  ",
    "++a;, b++;, --c;, d--; ", "a>b;, a<b;, a>=b;, a<=b;, a==b;, a!=b; ","(a>10)&&(a>7);,(a>10)||(a>7);,!(a>10); ",
     "sizeof(변수명 또는 자료형) ","(조건) ? (참일 시) : (거짓일 시);", "If(조건식) 실행문; ", "if(조건문) 실행문1; else 실행문2; ",
    " else if (조건문2) 실행문2;else 실행문; ", "switch(조건식){ case상수식1; 실행문; break;case 상수식2; 실행문; break;default; 실행문; break; } ",
     "while(조건식){ 실행문; } ", "변수형 함수명(변수명,1 변수명2); ", "변수형 함수 이름(변수명1,변수명2){기능; reture 반환값;} ",
    "함수이름(변수명3,변수명4) ; ", "자료형 배열명[N]={값1,값2,값3.....값N}; ","for(초기식; 조건식; 증감식){ 실행문; } ",
    "Do{실행문; }while (조건식); ",  "gets(배열명); ","puts(배열명); ", "변수형 *포인터명=&변수명 ",
    "Strcpy(문자열1,문자열2); ","Strlen(문자열); ", "Strcat(문자열1, 문자열2); ",  "strcmp (문자열1, 문자열2); ",
     "함수 안에서 변수 선언 ", "함수밖에서 변수 선언 ","static 변수형 변수명;  " };

    char list3[N][250] = {
     "전처리 지시자에 따라 소스파일을 가공하는 과정"
    ,"CPU가 해설할 수 있는 명령어들로 구성된 개체파일로 바꾸는 과정 "
    ,"개체파일에 startup code를 결합하는 과정 "
    ,"머리(함수 원형)와 몸통으로 구성되어 있다. "
    ,"화면에 데이터를 일정한 형식에 따라 출력할 수 있다."
    ,"C언어에서 기본으로 사용하는 입출력 함수가 들어가 있다."
    ,"NULL"
    ,"값이 변하지 않는 데이터 "
    ,"값이 바뀌는 데이터 "
    ,"변수형 중 하나로 정수를 넣을 수 있다. 관련된 출력 변환 문자: %d "
    ,"변수형 중 하나로 실수를 넣을 수 있다. 관련된 출력 변환 문자: %lf "
    ,"변수형 중 하나로 실수를 넣을 수 있다. 관련된 출력 변환 문자: %lf "
    ,"입력 문자들을 스캔하여 원하는 형태의 데이터를 변수에 삽입할 수 있다. *주의사항: 문자열 변환문자를 제외한 변수명 앞에 &를 붙여야 정상적으로 작동한다. 또한 띄어쓰기를 할 시 뒤 문장은 인식하지 못한다 "
    ,"덧셈, 뺄셈, 나눗셈, 곱셈, 나머지를 계산하는 연산자 "
    ,"변수에 값을 대입하는 연산자 "
    ,"변수의 값을 1씩 증가시키거나 감소시킬 수 있다. 변수명 앞에 있으면 계산 전에, 뒤에 있으면 계산 후에 변수값을 변경시킨다"
    ,"“크다, 작다, 크거나 같다, 작거나 같다, 같다, 같지 않다” 와 같이 변수 간의 관계를 계산한다. 컴퓨터는 ‘0’를 거짓, ‘0’를 제외한 모든 수를 참이라고 판단한다.(보통 참의 표시로’1’를 쓰곤 한다) "
    ,"집합에서 쓰이는 합집합, 교집합, 여집합를 뜻하며 참과 거짓을 판단하는데 쓰이는 연사자 "
    ,"피연산자의 크기를 바이트 단위로 계산해서 알려줄 수 있는 연산자 "
    ,"조건이 참이냐 거짓이냐에 따라 다른 명령을 수행하도록 하는 연산자 "
    ,"조건식이 참일 시 실행문 실행, 거짓이면 아무것도 실행하지 않음. "
    ,"조건식1이 참이면 실행문1만 실행, 조건식2이 참이면 실행문2을 실행함"
    ,"조건이 참이냐 거짓이냐에 따라 다른 명령을 수행하도록 하는 연산자 "
    ,"조건이 참이냐 거짓이냐에 따라 다른 명령을 수행하도록 하는 연산자 "
    ,"조건이 참이냐 거짓이냐에 따라 다른 명령을 수행하도록 하는 연산자 "
    ,"형식이 while문과 다르긴 하지만 원리는 똑같다. 정확한 숫자를 반복하기에 유용하다. "
    ,"특이하게 실행문을 무조건 실행한 후 조건에 맞으면 반복이 되는 반복문으로 무조건 한 번은 실행되어야 한다면 해당 반복문을 쓰는 게 효율적이다. "
    ,"함수의 형태를 알리며, 컴퓨터가 함수의 존재를 인식할 수 있도록 코드 처음에 함수 선언을 써 놓는다.  "
    ,"해당 함수의 기능을 구현한다. 보통 메인 코드 앞에 놓아 함수선언을 하는 귀찮음을 없앤다. "
    ,"함수를 사용하는 명령어로 함수에 필요한 값을 인수로 준다. "
    ,"각 변수가 일련의 연관성이 있을 경우, 효율성을 위해 사용하곤 한다. *주의 사항: 변수의 요소는 0~N-1이다. 2차원,3차원 배열도 있다. "
    ,"Scanf과 같이 문자열을 받을 수 있으나 띄어쓰기를 하면 뒤는 나오지 않는 Scanf와 달리 Enter직전까지 모든 문자열이 다 저장된다. 하지만 입력한 배열의 크기를 검사하지 않기 때문에 오류가 생길 수도 있으니 주의해야한다. "
    ,"Printf와 같은 기능을 수행하지만 출력 후 수동으로 줄을 바꿔줘야하는 printf와 달리 자동으로 줄을 바꿔준다.  "
    ,"NULL"
    ,"문자열2를 문자열1에 복사한다. "
    ,"문자열의 길이(문자수)를 구해 반환시킨다. "
    ,"문자열2에다가 문자열1를 이어붙임 "
    ,"문자열1이 문자열2보다 크면 1반환하고 무자열1이 문자열2보다 작으면 -1반환, 둘이 같은 문자열이면 0반환한다. "
    ,"지역변수란 일정한 지역에서만 사용할 수 있는 변수를 뜻합니다. 그렀기 때문에 이름이 같아도 선언된 함수가 다르다면 가각 독립된 저장공간을 갖습니다. 메모리를 효율적으로 사용 가능하며 디버깅에 유리하기 때문에 사용합니다. "
    ,"코드의 모든 함수 내외에서 사용이 가능합니다. 그렀기 때문에 여러 함수에서 쉽게 공유가능하다는 장점이 있지만 용량을 많이 사용하며 전역변수의 값이 잘못된다면 전역 변수가 사용된 모든 함수를 고쳐야 한다는 단점이 있습니다. "
    ,"프로그램이 실행될 동안에 계속 유지되므로써 함수가 끝나면 초기화되는 지역변수와 차이가 있다. "
    };


    if (b == 1) {//용어 가림막
        for (int p = 0, q = 1; p < 41; p++, q++) {
            printf("\n%d. ??? \n", q);
            printf(":%s\n", list3[p]);
        }
        /*srand((unsigned int)time(NULL));
        int k1[N] = { NULL };
        int n = 100;//100은 의미없는 숫자
        n = (rand() % N) + 1;
        int g = 0;
        while (1) {
           if (k1[g] != n) {
              k1[g] = n;
              g++;
           }
           else {
              n//중복된 n은 아예 제외시키거시ㅠㅇ느

           }*/




    }
    else if (b == 2) {//설명 가림막
        for (int p = 0, q = 1; p < N; p++, q++) {
            printf("\n%d.%s\n", q, list1[p]);
            printf("설명: ???\n");
        }
    }
    else {
        while (1) {
            printf("'1'또는 '2' 둘 중에 하나를 골라주십시오.\n");
            scanf(" %d", &b);

        }
    }
}
