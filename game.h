#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>




class Game
{
public:
	int id;
	Game();
	Game(int index, std::string title, std::string developer, std::string review);
	~Game();
	std::string getTitle();
	std::string getDeveloper();
	std::string getReview();
	void print_game_info();
	void print_game_info_csv();
	void change_review(std::string review_content);
	void print_if_contain_in_column(std::string phrase, std::string column);


private:
	std::string title;
	std::string developer;
	std::string review;
};

Game::Game()
{
	title = "";
	developer = "";
	review = "";
}
Game::Game(int index, std::string t, std::string dev, std::string rev): id(index), title(t), developer(dev), review(rev)  {}




Game::~Game()
{
}

void Game::print_game_info() {
	std::cout << id <<" " << title << " " << developer << " " << review << "\n";
}

std::string Game::getTitle() {
	return title;
}
std::string Game::getDeveloper() {
	return developer;
}
std::string Game::getReview() {
	return review;

}

void Game::change_review(std::string review_content) {
	review = review_content;
}
void Game::print_game_info_csv() {
	std::cout<< id << "," << "\"" << title << "\"" << "," << "\"" << developer << "\"" << "," << "\"" << review << "\"" << "\n";
}

void Game::print_if_contain_in_column(std::string phrase, std::string column) {
	if (column == "title") {
		size_t found = title.find(phrase);
		if (found != std::string::npos) {
			print_game_info();
		}
	}
	else if (column == "developer") {
		size_t found = developer.find(phrase);
		if (found != std::string::npos) {
			print_game_info();
		}
	}
	else if (column == "review") {
		size_t found = review.find(phrase);
		if (found != std::string::npos) {
			print_game_info();
		}
	}
	
}
void is_phrase_contain_in_column(std::string phrase, std::string column) {

}


bool compareGamesAtributes(Game a, Game b, std::string column) {
	if (column == "title") {
		return a.getTitle() < b.getTitle();
	}
	else if (column == "developer") {
		return a.getDeveloper() < b.getDeveloper();
	}
	else if (column == "review") {
		return a.getReview() < b.getReview();
	}
	return false;
}






class GameDatabase
{
public:
	GameDatabase();
	~GameDatabase();
	void list();
	void add(std::string t, std::string dev);
	void save_database();
	void add_rewiev(int id, std::string review_content);
	void delete_game(int id);
	void csv();
	void list_sorted(std::string column);
	void search(std::string phrase, std::string column);

private:
	std::vector<Game> games;

};

GameDatabase::GameDatabase()
{
	int index = 1;
	std::string t, dev, rev;
	std::ifstream file;
	file.open("database.txt");
	while (std::getline(file, t, ';') && std::getline(file, dev, ';') &&
		std::getline(file, rev, '\n')) {
		games.emplace_back(index, t, dev, rev);
		index += 1;
	}
	file.close();
}

GameDatabase::~GameDatabase()
{


}
	
void GameDatabase::list() {
	for (int i = 0; i < games.size(); i++ ) {
		games[i].print_game_info();
	}
}
void GameDatabase::add(std::string t, std::string dev) {
	games.emplace_back(games.size()+1, t, dev, "");
}
void GameDatabase::save_database() {
	std::ofstream file;
	file.open("database.txt");
	for (int i = 0; i < games.size(); i++) {
		file << games[i].getTitle() <<";" << games[i].getDeveloper() << ";" << games[i].getReview() << "\n";
	}
	file.close();
}
void GameDatabase::add_rewiev(int id, std::string review_content) {
	games[id-1].change_review(review_content);
}
void  GameDatabase::delete_game(int id) {
	auto iterator_to_remove = games.begin() + id - 1;
	games.erase(iterator_to_remove);
}
void GameDatabase::csv() {
	for (int i = 0; i < games.size(); i++) {
		games[i].print_game_info_csv();
	}
}

void GameDatabase::list_sorted(std::string column) {
	std::vector<Game> temp = games;
	std::sort(temp.begin(), temp.end(), [column](Game a, Game b) {return compareGamesAtributes(a, b, column); });
	for (int i = 0; i < temp.size(); i++) {
		temp[i].print_game_info();
	}
}
void GameDatabase::search(std::string phrase, std::string column) {
	for (int i = 0; i < games.size(); i++) {
		games[i].print_if_contain_in_column(phrase, column);
	}
}