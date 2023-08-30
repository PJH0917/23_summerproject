#define NUM_WORDS 20
#define DISPLAY_TIME 1000 // 단어 한 개 보여주는데 드는 시간 1초 (밀리초 단위로 표현)
#define INPUT_TIME 5000  // 단어 한 개 입력하는데 주어진 시간 5초 (밀리초 단위)

#include <stdio.h>
#include <stdlib.h> // system 함수, "cls" (Windows에서 화면을 지우는 명령어)
#include <string.h> // strcmp (문자열을 비교하는 함수), 사용자가 입력한 단어와 정답 단어를 비교하는데 사용
#include <windows.h> // Sleep 함수 (현재 스레드를 일정 시간 동안 대기시키는데 사용, 각 단어를 보여주는 시간을 지정함), _kbhit 함수 (키보드에서 입력된 문자를 확인하는데 사용되며, 해당 코드에서는 사용자가 단어를 입력했는지 여부를 체크한다.)
#include <time.h> // time_t 사용

void print_start()
{
    printf("Select the word game: !!!\n");
    printf("1. animal_quiz\n");
    printf("2. city_quiz\n");
    printf("3. fruit_quiz\n");

}
void showing_word(char* word); // 단어를 보여준다
void fade_away(); // 화면 사라지게 함

int arrange(const void* a, const void* b)
{
    return strlen(*(char**)a) - strlen(*(char**)b);
}


int main()
{
    int point = 0;
    char* animal_quiz[NUM_WORDS] = {
        "human","tiger","dragon","monkey","bird",
        "cormorant","armadillo","pigeon","parrot","dog",
        "cat","killer whale","anteater","sloth","fox",
        "jaguar","puma","capybara","lion","boar"
    }; // 출제될 동물 단어들

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



    
    printf("Press Enter to start the game!!");
    getchar(); // 입력을 받는다

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

    printf("Press Enter to start the game.\n");
    getchar();

    qsort(quiz_selected, num_words, sizeof(char*), arrange);
    
    for (int i = 0; i < NUM_WORDS; i++)
    {
        printf("\nCurrent Score: %d\n", point);
        showing_word(quiz_selected[i]); // 매개변수 animal_quiz[i]의 단어를 매개변수로 받음
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


