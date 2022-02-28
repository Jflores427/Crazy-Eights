#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

class Card{
	char m_suit;
	int m_num;
public:
	Card(const char s, const int n) : m_suit(s), m_num(n) {}
	friend char sfinder(const Card& l){ return l.m_suit; }
	friend int nfinder (const Card& l){ return l.m_num; }
	friend ostream& operator<<(ostream& o, const Card& c){
	o << c.m_suit;
	switch(c.m_num){
	case 14: o << '*'; break;
	case 13: o << 'K'; break;
	case 12: o << 'Q'; break;
	case 11: o << 'J'; break;
	case 1: o << 'A'; break;
	default: o << c.m_num; break;
	}
	return o;
	}
};

class Player{
		string m_name;
		vector<Card> m_hand;

public:
	Player(const string& n): m_name(n){}

		void push_back(const Card& c) {
			m_hand.push_back(c);
		}

		void reveal(){
			vector<char> choice;
			for(int i = 0, len = m_hand.size() + 1; i < len; ++i) choice.push_back('a' + i);
			for(int i =0, len = m_hand.size(); i < len; ++i){ cout<< "(" << choice.at(i)  << ")" << " " << m_hand.at(i) << "  " ; }
			cout<< "(" << choice.back() << ")" << " " << "draw" << endl;
		}

		char finder(const char& t){ return sfinder(m_hand.at(t - 'a')); }
		int num_finder(const char& t){ return nfinder(m_hand.at(t - 'a')); }
		int fsize(){ return m_hand.size(); }
		Card decide(const char& e){ return m_hand.at(e - 'a'); }
		void erase(const char& z){ m_hand.erase(m_hand.begin() + (z - 'a')); }

		friend ostream& operator<<(ostream& o, const Player& p){
			o << p.m_name << "  ";
			vector<char> choice;
			for(int i = 0, len = p.m_hand.size() + 1; i < len; ++i) choice.push_back('a' + i);
			for(int i =0, len = p.m_hand.size(); i < len; ++i){
				o << "(" << choice.at(i)  << ")" << " " << p.m_hand.at(i) << "  ";
			}
			cout << endl;
			return o;
		}
};

	char finders(const Card& g) { return sfinder(g); }
	int num_finders(const Card& g){ return nfinder(g); }

int main() {
	srand(time(NULL)); //If you want a random game every time you run the program.
	char cardLetter;
	int k = 0;
	char suitChoice;
	vector<Card> pile;
	vector<Card> deck; deck.reserve(52);
	for (int i = 1; i <=13; ++i) deck.push_back(Card('C', i));
	for (int i = 1; i <=13; ++i) deck.push_back(Card('S', i));
	for (int i = 1; i <=13; ++i) deck.push_back(Card('D', i));
	for (int i = 1; i <=13; ++i) deck.push_back(Card('H', i));
	random_shuffle(deck.begin(), deck.end());

	vector<Player> players;
	Player p0("Player 0"), p1("Player 1"), p2("Player 2"), p3("Player 3");
	players.push_back(p0); players.push_back(p1); players.push_back(p2); players.push_back(p3);

	for (int i= 0, len = players.size(); i < len; ++i){
		for(int j = 0; j < 6; ++j){
			players.at(i).push_back(deck.back());
			deck.pop_back();
		}
	}

	while(num_finders(deck.back()) == num_finders(Card('C', 8))){ random_shuffle(deck.begin(), deck.end()); }
	pile.push_back(deck.back());
	deck.pop_back();

	while(true){ //Rounds begins
		if(players.at(3).fsize() == 0 || deck.size() == 0) break;
		if(k % 4 == 0){
			cout << "Pile has " << pile.back() << " <--- your turn" << endl;
			players.at(0).reveal();
			cout << "Which one to play?"; cin >> cardLetter;
			cout << endl;

			while(cardLetter == '?'){
				for(int i = 1, len = players.size(); i < len; ++i){ cout<< players.at(i) << endl; }
				cout << "Which one to play?"; cin >> cardLetter;
			}

			while(cardLetter - 'a' == players.at(0).fsize() && deck.size() != 0){
				players.at(0).push_back(deck.back());
				deck.pop_back();
				players.at(0).reveal();
				cout << "Which one to play?"; cin >> cardLetter;
			}

			if(deck.size() == 0){ cout<< "Deck has finished" << endl; break; }

			while(players.at(0).finder(cardLetter) != finders(pile.back()) && cardLetter - 'a' != players.at(0).fsize() && players.at(0).num_finder(cardLetter) != num_finders(pile.back()) && players.at(0).num_finder(cardLetter) != 8){
				cout << "Invalid card selection, try again." << endl; cin >> cardLetter;

				while(cardLetter == '?'){
					for(int i = 1, len = players.size(); i < len; ++i){ cout<< players.at(i) << endl;}
					cout << "Which one to play?" ; cin >> cardLetter; break;
				}

				while(cardLetter - 'a' == players.at(0).fsize() && deck.size() != 0){
					players.at(0).push_back(deck.back());
					deck.pop_back();
					players.at(0).reveal();
					cout << "Which one to play?"; cin >> cardLetter;
				}

				if(deck.size() == 0){ cout<< "Deck has finished" << endl; break; }
			}

			if(players.at(0).num_finder(cardLetter) == 8){
				cout << "Which suit do you want?";
				cin >> suitChoice;
				pile.push_back(Card(toupper(suitChoice), 14));
				cout << "Pile has " << pile.back() << endl;
				players.at(0).erase(cardLetter);
			}

			else if (deck.size() != 0){
				pile.push_back(players.at(0).decide(cardLetter));
				cout << "Pile has " << pile.back() << endl;
				players.at(0).erase(cardLetter);
			}
			++k;
		}

		if(players.at(0).fsize() == 0 ||deck.size() == 0) break;
		if(k % 4 == 1)	{
			char cpuSuitChoice;
			for(char i = 'a', len = 'a' + players.at(1).fsize(); i < len; ++i){

				if(players.at(1).finder(i) == finders(pile.back())){
				cout<< "		Player 1 chose " << players.at(1).decide(i) << endl;
				pile.push_back(players.at(1).decide(i));
				players.at(1).erase(i);
				cout<< "Pile has " << pile.back() << endl;
				++k;
				break;
				}

				else if(players.at(1).num_finder(i) == num_finders(pile.back())){
				cout<< "		Player 1 chose " << players.at(1).decide(i) << endl;
				pile.push_back(players.at(1).decide(i));
				players.at(1).erase(i);
				cout << "Pile has " << pile.back() << endl;
				++k;
				break;
				}

				else if(players.at(1).num_finder(i) == 8){
					cout << " 		Player 1 chose " << players.at(1).decide(i) << endl;
					players.at(1).erase(i);
					int C = 0;
					int D = 0;
					int S = 0;
					int H = 0;
					for(char i = 'a', len = players.at(1).fsize(); i < len; ++i){
						if(players.at(1).finder(i) == 'C') ++C;
						else if(players.at(1).finder(i) == 'D') ++D;
						else if(players.at(1).finder(i) == 'S') ++S;
						else if(players.at(1).finder(i) == 'H') ++H;
					}

					if(C >= D && C >= S && C >= H) cpuSuitChoice = 'C';
					else if(D >= C && D >= S && D >= H) cpuSuitChoice = 'D';
					else if(S >= C && S >= D && S >= H) cpuSuitChoice = 'S';
					else if(H >= C && H >= S && H >= D) cpuSuitChoice = 'H';

					cout << "		Player 1 declared suite " << cpuSuitChoice << endl;
					pile.push_back(Card(cpuSuitChoice, 14));
					cout << "Pile has " << pile.back() << endl;
					++k;
					break;
				}

				else if (i == 'a' + players.at(1).fsize() - 1){
					if(deck.size() == 0) break;
					cout << "		Player 1 drawing..." << endl;
					players.at(1).push_back(deck.back());
					deck.pop_back();
					if(players.at(1).finder('a' + players.at(1).fsize() - 1) != finders(pile.back()) && players.at(1).num_finder('a' + players.at(1).fsize() - 1) != num_finders(pile.back()) && players.at(1).num_finder('a' + players.at(1).fsize() - 1) != 8) ++len;
				}
			}
			if(deck.size() == 0){ cout<< "Deck has finished" << endl; break; }
		}

		if(players.at(1).fsize() == 0 || deck.size() == 0) break;
		if(k % 4 == 2)	{
			char cpuSuitChoice;
			for(char i = 'a', len = 'a' + players.at(2).fsize(); i < len; ++i){

				if(players.at(2).finder(i) == finders(pile.back())){
				cout<< "		Player 2 chose " << players.at(2).decide(i) << endl;
				pile.push_back(players.at(2).decide(i));
				players.at(2).erase(i);
				cout<< "Pile has " << pile.back() << endl;
				++k;
				break;
				}

				else if(players.at(2).num_finder(i) == num_finders(pile.back())){
				cout<< "		Player 2 chose " << players.at(2).decide(i) << endl;
				pile.push_back(players.at(2).decide(i));
				players.at(2).erase(i);
				cout << "Pile has " << pile.back() << endl;
				++k;
				break;
				}

				else if(players.at(2).num_finder(i) == 8){
					cout << "		Player 2 chose " << players.at(2).decide(i) << endl;
					players.at(2).erase(i);
					int C = 0;
					int D = 0;
					int S = 0;
					int H = 0;
					for(char i = 'a', len = players.at(2).fsize(); i < len; ++i){
						if(players.at(2).finder(i) == 'C') ++C;
						else if(players.at(2).finder(i) == 'D') ++D;
						else if(players.at(2).finder(i) == 'S') ++S;
						else if(players.at(2).finder(i) == 'H') ++H;
					}

					if(C>=D && C>=S && C>=H) cpuSuitChoice = 'C';
					else if(D>=C && D>=S && D>=H) cpuSuitChoice = 'D';
					else if(S>=C && S>=D && S>=H) cpuSuitChoice = 'S';
					else if(H>=C && H>=S && H>=D) cpuSuitChoice = 'H';

					cout << "		Player 2 declared suite " << cpuSuitChoice << endl;
					pile.push_back(Card(cpuSuitChoice, 14));
					cout << "Pile has " << pile.back() << endl;
					++k;
					break;
				}

				else if (i == 'a' + players.at(2).fsize() - 1){
					if(deck.size() == 0) break;
					cout << "		Player 2 drawing..." << endl;
					players.at(2).push_back(deck.back());
					deck.pop_back();
					if(players.at(2).finder('a' + players.at(2).fsize() - 1) != finders(pile.back()) && players.at(2).num_finder('a' + players.at(2).fsize() - 1) != num_finders(pile.back()) && players.at(2).num_finder('a' + players.at(2).fsize() - 1) != 8) ++len;
				}
			}
			if(deck.size() == 0){ cout<< "Deck has finished" << endl; break; }
	    }

		if(players.at(2).fsize() == 0 || deck.size() == 0) break;
		if(k % 4 == 3)	{
			char cpuSuitChoice;
			for(char i = 'a', len = 'a' + players.at(3).fsize(); i < len; ++i){

				if(players.at(3).finder(i) == finders(pile.back())){
				cout<< "		Player 3 chose " << players.at(3).decide(i) << endl;
				pile.push_back(players.at(3).decide(i));
				players.at(3).erase(i);
				++k;
				break;
				}

				else if(players.at(3).num_finder(i) == num_finders(pile.back())){
				cout<< "		Player 3 chose " << players.at(3).decide(i) << endl;
				pile.push_back(players.at(3).decide(i));
				players.at(3).erase(i);
				++k;
				break;
				}

				else if(players.at(3).num_finder(i) == 8){
					cout << "		Player 3 chose " << players.at(3).decide(i) << endl;
					players.at(3).erase(i);
					int C = 0;
					int D = 0;
					int S = 0;
					int H = 0;
					for(char i = 'a', len = players.at(3).fsize(); i < len; ++i){
						if(players.at(3).finder(i) == 'C') ++C;
						else if(players.at(3).finder(i) == 'D') ++D;
						else if(players.at(3).finder(i) == 'S') ++S;
						else if(players.at(3).finder(i) == 'H') ++H;
					}

					if(C>=D && C>=S && C>=H) cpuSuitChoice = 'C';
					else if(D>=C && D>=S && D>=H) cpuSuitChoice = 'D';
					else if(S>=C && S>=D && S>=H) cpuSuitChoice = 'S';
					else if(H>=C && H>=S && H>=D) cpuSuitChoice = 'H';

					cout << "		Player 3 declared suite " << cpuSuitChoice << endl;
					pile.push_back(Card(cpuSuitChoice, 14));
					++k;
					break;
				}

				else if (i == 'a' + players.at(3).fsize() - 1){
					if(deck.size() == 0) break;
					cout << "		Player 3 drawing..." << endl;
					players.at(3).push_back(deck.back());
					deck.pop_back();
					if(players.at(3).finder('a' + players.at(3).fsize() - 1) != finders(pile.back()) && players.at(3).num_finder('a' + players.at(3).fsize() - 1) != num_finders(pile.back()) && players.at(3).num_finder('a' + players.at(3).fsize() - 1) != 8) ++len;
				}
			}
			if(deck.size() == 0){ cout<< "Deck has finished" << endl; break; }
		}
	}
	cout<< endl;
	cout<< "The Game Has Ended" << ": ";
	if(players.at(0).fsize() == 0){
		cout<< "You Won!" << endl;
	}
	else if(players.at(1).fsize() == 0) {
		cout<< "Player 1 Won!" << endl;
	}
	else if(players.at(2).fsize() == 0){
		cout<< "Player 2 Won!" << endl;
	}
	else if(players.at(3).fsize() == 0){
		cout<< "Player 3 Won!" << endl;
	}
	else if(deck.size() == 0){
		int q = 0;
		int w = 0;
		int e = 0;
		int r = 0;

		for(char i = 'a'; i < 'a' + players.at(0).fsize(); ++i) q += players.at(0).num_finder(i);
		for(char i = 'a'; i < 'a' + players.at(1).fsize(); ++i) w += players.at(1).num_finder(i);
		for(char i = 'a'; i < 'a' + players.at(2).fsize(); ++i) e += players.at(2).num_finder(i);
		for(char i = 'a'; i < 'a' + players.at(3).fsize(); ++i) r += players.at(3).num_finder(i);

		if(q < w && q < e && q < r){
			cout << "You won with the minimum score of " << q << "." << endl;
		}
		else if(w < q && w < e && w < r){
			cout << "Player 1 won with the minimum score of " << w << "." << endl;
		}
		else if(e < w && e < q && e < r){
			cout << "Player 2 won with the minimum score of " << e << "." << endl;
		}
		else if(r < w && r < e && r < q){
			cout << "Player 3 won with the minimum score of " << r << "." << endl;
		}
		else {
			cout<< "No Winner, two or more players have tied." << endl;
		}
	}
	cout<< endl << "[ Final card distributions ]" << endl;
	for(int i = 0; i < 4; ++i) cout<< players.at(i) << endl;

	return 0;
}

