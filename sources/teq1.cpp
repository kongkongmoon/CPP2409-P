#include <iostream>
using namespace std;

int main() {
    int setting = 0;
    int difficulty = 0;
    int tryNum = 0;
    string word = "";

    //설정에 따른 맞출 단어 설정
    while(1){
        cout << "Setting: (1) alone (2) together: ";
        cin >> setting;

        switch (setting) {
        case 1:
            cout << "저장되어있는 단어 중 하나를 랜덤으로 불러왔습니다." << endl;
            //word = rand~
            break;
        case 2:
            cout << "상대방이 맞출 단어를 입력해주세요" << endl;
            cin >> word;
            break;
        default:
            cout << "1, 2 중 하나를 입력해주세요." << endl;
            break;
        }

        if(setting == 1 || setting == 2){break;}
        else {continue;}
    }
    
    // 난이도에 따른 틀린 횟수 설정
    while(1){
        cout << "Select Difficulty: (1) Easy (2) Medium (3) Hard: ";
        cin >> difficulty;

        switch (difficulty) {
        case 1:
            tryNum = 8; // 쉬움: 틀린 횟수 8번
            break;
        case 2:
            tryNum = 6; // 보통: 틀린 횟수 6번
            break;
        case 3:
            tryNum = 4; // 어려움: 틀린 횟수 4번
            break;
        default:
            cout << "1, 2, 3중 하나를 입력해주세요." << endl;
            break;
        }

        if(difficulty == 1 || difficulty == 2 || difficulty == 3){break;}
        else {continue;}
    }
    return 0;

}
