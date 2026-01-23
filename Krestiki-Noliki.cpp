#include <iostream>
#include <array>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>

using namespace std;
using namespace sf;

enum class Sign{X,O,Void};
const int LOSE{ -10 };
const int WIN{ 10 };
const int num{ 3 };
Sign PLAYER;
const array<Sign, num* num> BasicBoard{Sign::Void,Sign::Void ,Sign::Void ,Sign::Void ,Sign::Void ,Sign::Void ,Sign::Void,Sign::Void ,Sign::Void};

Sign win(array<Sign,num*num> board) {
	Sign res = Sign::Void;
	for (int i{};i < num*num;i += num) {
		bool mathTree{ true };
		for (int j{1};j < num&&mathTree;j++) {
			if (board[i] != board[i + j]) mathTree = false;
		}
		if (mathTree) return board[i];
	}
	if ((board[0] == board[4] && board[0] == board[8]) || (board[2] == board[4] && board[2] == board[6])) return board[4];
	return Sign::Void;
}

Sign playerSign() {
	Sign player{ Sign::Void };
	char in;
	while (player == Sign::Void) {
		cout << "Выберите Крестик или Нолик <X/O>" << endl;
		cin >> in;
		if (in == 'X' || in == 'x')player = Sign::X;
		if (in == 'O' || in == 'o')player = Sign::O;
	}
	return player;
}

vector<int> givEmptyCells(array<Sign, num* num> board){
	vector<int> cells;
	for (int i{};i < num * num;i++) {
		if (board[i] == Sign::Void) {
			cells.push_back(i);
		}
	}
	return cells;
}

int minimax(array<Sign,num*num> board,Sign player,int move=0) {
	Sign play = win(board);
	if (play == PLAYER) {
		return move + WIN;
	}
	else if (play != Sign::Void) {
		return move + LOSE;
	}
	else {
		vector<int> emptyBord = givEmptyCells(board);
		pair<int, int> maxi{0,-1}, mini{0,-1};
		Sign enemy;
		if (player == Sign::X) enemy = Sign::O;
		else enemy = Sign::X;
		for (int i{};i < emptyBord.size();i++) {
			array<Sign, num* num> b2 = board;
			b2[emptyBord[i]] = player;
			int score = minimax(b2, enemy, move + 1);
			if(maxi.second==-1) maxi = { score,emptyBord[i] };
			if(mini.second ==-1)mini = { score,emptyBord[i] };
			if (score > maxi.first) {
				maxi = { score,emptyBord[i] };
			}
			if (score < mini.first) {
				mini = { score,emptyBord[i] };
			}
		}
		if (player == PLAYER) {
			return maxi.second;
		}
		else return mini.second;
		
	}
}

int main() {
	setlocale(LC_ALL, "RUS");

	RenderWindow window(VideoMode({ 600,600 }), "Tic-Tac-Toe",Style::Close, State::Windowed);

	while (window.isOpen()) {
		while (const optional event = window.pollEvent()) {
			if (event->is<Event::Closed>()) {
				window.close();
			}
		}

		window.clear();
		window.display();
	}
}