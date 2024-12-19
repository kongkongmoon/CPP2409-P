#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <set>
using namespace std;

// 단어 데이터를 관리하는 클래스
class WordManager {
private:
    vector<string> words; 
    vector<string> hints; 

public:
    // 단어와 힌트를 파일에서 불러오는 함수
    void LoadWordsFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("파일을 열 수 없습니다: " + filename);
        }

        string word, hint;
        while (file >> word >> hint) {
            words.push_back(word);
            hints.push_back(hint);
        }
        file.close();

        if (words.empty()) {
            throw runtime_error("파일에 단어가 없습니다.");
        }
    }

    // 랜덤으로 단어와 힌트를 반환하는 함수
    pair<string, string> GetRandomWord() const {
        srand(time(0));
        int index = rand() % words.size();
        return {words[index], hints[index]};
    }

    bool IsEmpty() const {
        return words.empty();
    }
};

// 게임을 관리하는 클래스
class HangmanGame {
private:
    string word; 
    string hint; 
    int max_attempts; 
    int wrong_guesses; 
    vector<bool> guessed; 
    vector<char> wrong_letters;
    set<char> used_letters; // 이미 입력된 글자

public:
    HangmanGame(const string& word, const string& hint, int max_attempts)
        : word(word), hint(hint), max_attempts(max_attempts), wrong_guesses(0), guessed(word.length(), false) {}

    // 현재 상태를 출력하는 함수
    void Display() const {
        for (size_t i = 0; i < word.length(); ++i) {
            if (guessed[i]) {
                cout << word[i];
            } else {
                cout << "_";
            }
            cout << " ";
        }
        cout << endl;
        cout << "남은 기회 : " << max_attempts - wrong_guesses << endl;
        cout << "틀린 글자 : ";
        for (char c : wrong_letters) {
            cout << c << " ";
        }
        cout << endl;
    }

    // 플레이어의 입력을 처리하는 함수
    bool ProcessInput(char guess) {
        // 이미 입력한 글자인지 확인
        if (used_letters.find(guess) != used_letters.end()) {
            cout << "\n이미 입력한 글자입니다. 다시 입력해주세요.\n\n";
            return true; // 입력을 다시 요구하므로 틀린 입력으로 처리하지 않음
        }

        used_letters.insert(guess); // 새로운 입력으로 추가

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

        return correct_guess;
    }

    // 힌트를 보여주는 함수
    void ShowHint() const {
        cout << "\n힌트를 사용했습니다. 단어의 뜻: " << hint << "\n" << endl;
    }

    // 게임 종료 여부 확인
    bool IsGameOver() const {
        return wrong_guesses >= max_attempts;
    }

    bool IsWordGuessed() const {
        return all_of(guessed.begin(), guessed.end(), [](bool g) { return g; });
    }

    // 남은 시도 횟수 반환
    int GetRemainingAttempts() const {
        return max_attempts - wrong_guesses;
    }
    // 단어 반환
    string GetWord() const {
        return word;
    }
};

// 메인 함수
int main() {
    WordManager wordManager;

    // 파일에서 단어 불러오기
    try {
        wordManager.LoadWordsFromFile("words.txt");
    } catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }

    if (wordManager.IsEmpty()) {
        cerr << "단어 데이터가 비어있습니다." << endl;
        return 1;
    }

    string setting; 
    string difficulty; 
    int max_attempts;  

    // 설정 입력
    while (true) {
        cout << "설정 : 1. 혼자(저장된 단어가 랜덤으로 선택됩니다.)     2. 같이(상대방이 맞출 단어를 직접 입력합니다.) : ";
        cin >> setting;

        if (setting == "1" || setting == "2") {
            break;
        }
        cout << "\n잘못된 입력입니다. 1 또는 2를 입력해주세요.\n";
    }

    string word, hint;
    if (setting == "1") {
        auto selectedWord = wordManager.GetRandomWord();
        word = selectedWord.first;
        hint = selectedWord.second;
    } else {
        cout << "상대방이 맞출 단어를 입력해주세요: ";
        cin >> word;
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"; //터미널 창에 따라서 변경해야 함
    }

    // 난이도 설정
    while (true) {
        cout << "\n난이도 선택 : 1. 쉬움(기회: 8)   2. 보통(기회: 7)    3. 어려움(기회: 6) : ";
        cin >> difficulty;

        if (difficulty == "1") {
            max_attempts = 8;
            break;
        } else if (difficulty == "2") {
            max_attempts = 7;
            break;
        } else if (difficulty == "3") {
            max_attempts = 6;
            break;
        }
        cout << "\n잘못된 입력입니다. 1, 2 또는 3을 입력해주세요.";
    }

    HangmanGame game(word, hint, max_attempts);

    cout << "\n행맨 게임을 시작합니다!" << endl;

    while (!game.IsGameOver()) {
        game.Display();

        string input;
        cout << "글자를 입력하세요 (힌트를 보려면 'hint' 입력): ";
        cin >> input;

        if (input == "hint") {
            if (setting == "2") {
                cout << "\nsetting이 2일 때는 힌트를 사용할 수 없습니다. \n";
            } else if (game.GetRemainingAttempts() == 1) {
                game.ShowHint();
            } else {
                cout << "\n힌트는 남은 기회가 1일 때만 사용할 수 있습니다.\n";
            }
            continue;
        }

        if (input.length() != 1) {
            cout << "\n하나의 글자를 입력해 주세요.\n";
            continue;
        }

        char guess = input[0];
        if (!game.ProcessInput(guess)) {
            cout << "\n틀렸습니다!\n";
        }

        if (game.IsWordGuessed()) {
            cout << "\n축하합니다! 단어(" << game.GetWord() << ")를 맞췄습니다." << endl;
            return 0;
        }
    }

    cout << "\n기회를 모두 사용했습니다. 맞출 단어는 " << game.GetWord() << " 이었습니다." << endl;
    return 0;
}
