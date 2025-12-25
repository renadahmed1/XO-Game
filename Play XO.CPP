/*
 اول حاجه هعمل لوب تسالهم هل مستعدين يبداو و عارفين القواعد ولا لا
لو مش عارفين هعمل خانه فانكشن فيها القواعد
ولو عارفين و هيبداو هيختار start
ولو مش عايزين يلعبو تاني يختارو exit
*/

/*
لو اختار start هعمل function هتكون مصممه مصفوفه 3 * 3
و فيها علامه _ في كل خانه
  كل ما اللاعب يحط حرف في مكان معين بيبدا يشيل ال _ و يحط مكانها الحرف
*/

/*
اللعبه بين شخصين فانا هبدا اسال اللاعب الاول عايز يلعب ب x or o
ولو اختار o اللاعب تاني هيلعب ب x
ولو اختار xاللاعب التاني هيلعب ب o
*/

/*
احتمالات الفوز
1- الصفوف فيها 3 علامات متشابه
2- الاعمده فيها 3 علامات متشابه
3- القطر الرئيسي فيه 3 علامات متشابه
4- القطر الثانوي فيه 3 علامات متشابه
لو اي من الاحتمالات دي حصلت هيبقا في فايز
لكن لو المصفوفه امتلئت و مفيش فايز هيبقا تعادل
و هنسالهم لو عايزين يلعبو تاني ولا لا
*/


#include <iostream>
#include <string>
using namespace std;
// class 
/* اسم اللاعب الأول player1
اسم اللاعب الثاني player2
رمز اللاعب الأول symbol1 (مثلاً 'X')
رمز اللاعب الثاني symbol2 (مثلاً 'O')
المصفوفة اللي بتمثل اللوحة board[3][3]
عدد الأدوار أو الدور الحالي turn
(اختياري) متغير لحالة اللعبة زي gameOver أو winner */

class playXO {
public:
	string player1, player2;
	char symbol1, symbol2;
	char board[3][3];
	int turn;
	bool gameOver;

	void showRules(); // عرض القواعد
	void setupBoard(); // تهيئة اللوحة
	void displayBoard(); // عرض اللوحة
	void startGame(); // بدء اللعبة
	bool checkWin(); // التحقق من الفوز

};
// عرض القواعد
void playXO::showRules() {
	cout << "\n===== GAME RULES =====\n";
	cout << "1. The game is played between two players.\n";
	cout << "2. Player 1 chooses their symbol (X or O).\n";
	cout << "3. The goal is to make a row, column, or diagonal with three matching symbols.\n";
	cout << "4. If the board is full and no one wins → the game ends in a draw.\n";
	cout << "=========================\n\n";
}

// تهيئة اللوحة
void playXO::setupBoard() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			board[i][j] = '_';
		}
	}
}

// عرض اللوحة
void playXO::displayBoard() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

// بدء اللعبة
void playXO::startGame() {
	setupBoard(); // تهيئة اللوحة
	turn = 0; // بدء من الدور الأول
	gameOver = false; // اللعبة لسه مخلصتش

	// هنا هيبقا في لوب بتاع اللعب
	cout << "Enter player 1 name: ";
	cin >> player1;
	cout << "Enter player 2 name: ";
	cin >> player2;
	cout << player1 << " , choose your symbol (X/O): ";
	cin >> symbol1;

	if (symbol1 == 'X' || symbol1 == 'x') {
		symbol1 = 'X';
		symbol2 = 'O';
	}
	else {
		symbol1 = 'O';
		symbol2 = 'X';
	}
	cout << player1 << " will play with " << symbol1 << endl;
	cout << player2 << " will play with " << symbol2 << endl;

	displayBoard(); // عرض اللوحة
	while (!gameOver) {
		int row, col; // متغيرين لاختيار الصف والعمود
		char currentSymbol; // رمز اللاعب الحالي
		string currentPlayer; // اسم اللاعب الحالي

		// تحديد مين اللي عليه الدور
		if (turn % 2 == 0) { // لو الدور زوجي يبقي اللاعب الأول
			currentSymbol = symbol1;
			currentPlayer = player1;
		}
		else { // لو فردي يبقي اللاعب الثاني
			currentSymbol = symbol2;
			currentPlayer = player2;
		}
		// طلب الصف والعمود من اللاعب الحالي
		cout << "Enter row and column (1-3): ";
		cin >> row >> col; // المستخدم يدخل من 1 إلى 3
		// تحويلها لمؤشر من 0 إلى 2
		row--;
		col--;

		// التحقق من أن المكان داخل حدود اللوحة
		if (row < 0 || row > 2 || col < 0 || col > 2) {
			cout << "Invalid position! Try again.\n";
			continue; // نرجع بداية اللوب
		}

		// التحقق من أن الخانة فاضية
		if (board[row][col] != '_') {
			cout << "This place is already taken! Try another.\n";
			continue; // نرجع بداية اللوب
		}
		// لو فاضي، نحط الرمز
		board[row][col] = currentSymbol;

		// نعرض اللوحة بعد الحركة
		displayBoard();
		// بعد كل حركة، نتحقق لو في فائز
		if (checkWin()) {
			cout << currentPlayer << " wins! \n";
			gameOver = true;
		}
		else if (turn == 8) { // بعد 9 أدوار (من 0 إلى 8)
			cout << "It's a draw!\n";
			displayBoard(); // عرض اللوحة النهائية
			gameOver = true;
		}
		else {
			turn++; // ننتقل للدور التالي
		}
	}
}
// التحقق من الفوز

bool playXO::checkWin() {
	// التحقق من الصف
	for (int i = 0; i < 3; i++) {
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != '_') {
			return true;
		}
	}
	// التحقق من العمود
	for (int j = 0; j < 3; j++) {
		if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != '_') {
			return true;
		}
	}
	// التحقق من القطر الرئيسي
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '_') {
		return true;
	}
	// التحقق من القطر الثانوي
	if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '_') {
		return true;
	}
	return false; // مفيش فائز
}
int main() {
	playXO play;
	string choice;

	while (true) {
		cout << "\n===== Welcome to XO Game =====\n";
		cout << "Type 'start' to play\n";
		cout << "Type 'rules' to see the rules\n";
		cout << "Type 'exit' to quit\n";
		cout << "Your choice: ";
		cin >> choice;

		if (choice == "start" || choice == "Start") {
			play.startGame(); // يبدأ اللعبة
		}
		else if (choice == "rules" || choice == "Rules") {
			play.showRules(); // يعرض القواعد
		}
		else if (choice == "exit" || choice == "Exit") {
			cout << "Thanks for playing! Goodbye \n";
			break; // خروج من اللوب و إنهاء البرنامج
		}
		else {
			cout << "Invalid choice, please try again.\n";
		}
	}
}