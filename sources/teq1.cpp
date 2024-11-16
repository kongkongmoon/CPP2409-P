#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

// 임의의 단어를 반환하는 함수
string getRandomWord() {
    vector<string> words = {"apple", "banana", "cherry", "grape", "orange"}; //다음에 추가예정
    srand(time(0));
    return words[rand() % words.size()]; // 무작위 단어 반환
}

// 현재 상태를 출력하는 함수
void display(const string& word, const vector<bool>& guessed) {
    for (size_t i = 0; i < word.length(); ++i) {
        if (guessed[i]) {
            cout << word[i]; // 맞춘 글자 출력
        } else {
            cout << "_"; // 못 맞춘 글자는 밑줄 출력
        }
        cout << " ";
    }
    cout << endl;
}

int main() {
    int setting = 0; // 설정을 위한 변수
    int difficulty = 0; // 난이도 선택을 위한 변수
    int maxAttempts = 0; // 최대 횟수
    string word = ""; // 단어 저장을 위한 변수

    // 설정에 따른 단어 설정
    while (true) {
        cout << "설정 : 1. 혼자(저장되어있는 단어가 랜덤으로 선택됩니다.) 2. 같이(상대방이 맞출 단어를 직접 입력합니다.) : ";
        cin >> setting;

        if (setting == 1) { //혼자
            word = getRandomWord();
            cout << "저장된 단어 중 하나를 랜덤으로 선택했습니다." << endl;
            break;
        } else if (setting == 2) { //같이
            cout << "상대방이 맞출 단어를 입력해주세요:";
            cin >> word;
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
            break;
        } else {
            cout << "1 또는 2를 입력해주세요.\n" << endl;
        }
    }

    // 난이도 설정
    while (true) {
        cout << "\n난이도 선택 : 1.쉬움(기회: 8) Easy 2.보통(기회: 7) 3.어려움(기회: 6) : ";
        cin >> difficulty;

        if (difficulty == 1) {
            maxAttempts = 8; // 쉬움
            cout << "쉬움을 선택했습니다. 기회는 8번 입니다." << endl;
            break;
        } else if (difficulty == 2) {
            maxAttempts = 7; // 보통
            cout << "보통을 선택했습니다. 기회는 7번 입니다." << endl;
            break;
        } else if (difficulty == 3) {
            maxAttempts = 6; // 어려움
            cout << "어려움을 선택했습니다. 기회는 6번 입니다." << endl;
            break;
        } else {
            cout << "1, 2, 3 중 하나를 입력해주세요.\n" << endl;
        }
    }

    int wrongGuesses = 0; // 틀린 횟수를 위한 변수
    vector<bool> guessed(word.length(), false); // 맞춘 상태 저장하기위한 벡터
    vector<char> wrongLetters; // 틀린 글자를 저장하기 위한 벡터

    cout << "\n행맨 게임을 시작합니다!" << endl;

    // 맞추는 루프
    while (wrongGuesses < maxAttempts) {
        display(word, guessed); // 현재 상태 출력

        // 남은 기회와 틀린 글자 출력
        cout << "남은 기회 : " << maxAttempts - wrongGuesses << endl;
        cout << "틀린 글자 : ";
        for (char c : wrongLetters) {
            cout << c << " ";
        }
        cout << endl;

        // 입력 안내 및 입력 받기
        char guess;
        cout << "글자를 입력하세요: ";
        cin >> guess;

        // 이미 입력한 글자인지 확인
        bool alreadyGuessed = false;
        for (size_t i = 0; i < word.length(); ++i) {
            if (word[i] == guess && guessed[i]) {
                alreadyGuessed = true;
                break;
            }
        }
        for (char c : wrongLetters) {
            if (c == guess) {
                alreadyGuessed = true;
                break;
            }
        }
        if (alreadyGuessed) {
            cout << "이미 입력한 글자입니다. 다시 입력하세요.\n" << endl;
            continue;
        }

        bool correctGuess = false;

        // 입력한 글자가 단어에 있는지 확인
        for (size_t i = 0; i < word.length(); ++i) {
            if (word[i] == guess && !guessed[i]) {
                guessed[i] = true;
                correctGuess = true;
            }
        }
        if (!correctGuess) { // 틀렸을 경우
            wrongGuesses++;
            wrongLetters.push_back(guess);
        }

        // 모든 글자를 맞췄는지 확인
        bool allGuessed = true;
        for (bool letterGuessed : guessed) {
            if (!letterGuessed) {
                allGuessed = false;
                break;
            }
        }
        
        // 승리 메시지 출력
        if (allGuessed) {
            cout << "축하합니다. 단어 (" << word << ")를 맞췄습니다." << endl;
            break;
        }

        cout << "\n";
    }

    // 패배 메시지 출력
    if (wrongGuesses >= maxAttempts) {
        cout << "기회를 모두 사용했습니다. 맞출 단어는 " << word << " 이었습니다." << endl;
    }

    return 0;
}
