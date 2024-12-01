#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

// 임의의 단어를 반환하는 함수
string GetRandomWord() {
    vector<string> words = {"apple", "banana", "cherry", "grape", "orange"};
    srand(time(0));
    return words[rand() % words.size()];
}

// 현재 상태를 출력하는 함수
void Display(const string& word, const vector<bool>& guessed) {
    for (size_t i = 0; i < word.length(); ++i) {
        if (guessed[i]) {
            cout << word[i];
        } else {
            cout << "_";
        }
        cout << " ";
    }
    cout << endl;
}

int main() {
    string setting = "";
    string difficulty = "";
    int max_attempts = 0;
    string word = "";

    // 설정에 따른 단어 저장
    while (true) {
        cout << "설정 : 1. 혼자(저장되어있는 단어가 랜덤으로 선택됩니다.) 2. 같이(상대방이 맞출 단어를 직접 입력합니다.) : ";
        cin >> setting;

        if (setting == "1") {
            word = GetRandomWord();
            cout << "저장된 단어 중 하나를 랜덤으로 선택했습니다." << endl;
            break;
        } else if (setting == "2") {
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

        if (difficulty == "1") {
            max_attempts = 8;
            cout << "쉬움을 선택했습니다. 기회는 8번 입니다." << endl;
            break;
        } else if (difficulty == "2") {
            max_attempts = 7;
            cout << "보통을 선택했습니다. 기회는 7번 입니다." << endl;
            break;
        } else if (difficulty == "3") {
            max_attempts = 6;
            cout << "어려움을 선택했습니다. 기회는 6번 입니다." << endl;
            break;
        } else {
            cout << "1, 2, 3 중 하나를 입력해주세요.\n" << endl;
        }
    }

    int wrong_guesses = 0;
    vector<bool> guessed(word.length(), false);
    vector<char> wrong_letters;

    cout << "\n행맨 게임을 시작합니다!" << endl;

    while (wrong_guesses < max_attempts) {
        Display(word, guessed);

        cout << "남은 기회 : " << max_attempts - wrong_guesses << endl;
        cout << "틀린 글자 : ";
        for (char c : wrong_letters) {
            cout << c << " ";
        }
        cout << endl;

        // 입력받기
        string input;
        char guess;

        while (true) {
            cout << "글자를 입력하세요: ";
            cin >> input;

            if (input.length() != 1) {
                cout << "하나씩 입력해 주세요.\n";
            } else {
                guess = input[0]; // 유효한 입력
                break;
            }
        }

        bool already_guessed = false;
        for (size_t i = 0; i < word.length(); ++i) {
            if (word[i] == guess && guessed[i]) {
                already_guessed = true;
                break;
            }
        }

        for (char c : wrong_letters) {
            if (c == guess) {
                already_guessed = true;
                break;
            }
        }
        
        if (already_guessed) {
            cout << "이미 입력한 글자입니다. 다시 입력하세요.\n" << endl;
            continue;
        }

        bool correct_guess = false;
        for (size_t i = 0; i < word.length(); ++i) {
            if (word[i] == guess && !guessed[i]) {
                guessed[i] = true;
                correct_guess = true;
            }
        }

        if (!correct_guess) {
            wrong_guesses++;
            wrong_letters.push_back(guess);
        }

        bool all_guessed = true;
        for (bool letter_guessed : guessed) {
            if (!letter_guessed) {
                all_guessed = false;
                break;
            }
        }

        if (all_guessed) {
            cout << "\n축하합니다. 단어(" << word << ")를 맞췄습니다." << endl;
            break;
        }

        cout << "\n";
    }

    if (wrong_guesses >= max_attempts) {
        cout << "기회를 모두 사용했습니다. 맞출 단어는 " << word << " 이었습니다." << endl;
    }

    return 0;
}