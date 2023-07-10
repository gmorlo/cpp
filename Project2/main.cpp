#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>

class Card {
private:
    std::string name;
    std::vector<int> traits;

public:
    Card(const std::string& name, const std::vector<int>& traits) : name(name), traits(traits) {}

    const std::string& getName() const {
        return name;
    }

    const std::vector<int>& getTraits() const {
        return traits;
    }
};

class Player {
private:
    std::vector<Card*> hand;

public:
    void addToHand(Card* card) {
        hand.push_back(card);
    }

    void removeFromHand(Card* card) {
        hand.erase(std::remove(hand.begin(), hand.end(), card), hand.end());
    }

    const std::vector<Card*>& getHand() const {
        return hand;
    }
};

class Game {
private:
    std::vector<Card*> drawPile;
    std::vector<Card*> discardPile;
    std::vector<Player> players;
    int currentPlayer;
    int roundCount;
    int traitCount;

public:
    Game() : currentPlayer(0), roundCount(1), traitCount(8) {
        // Inicjalizacja kart
        std::vector<std::string> names = {
            "Lew", "Słoń", "Krokodyl", "Zebra", "Panda", "Koala", "Wieloryb", "Orzeł"
        };

        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < names.size(); j++) {
                std::vector<int> traits(traitCount, 0);
                traits[i] = 1;
                drawPile.push_back(new Card(names[j], traits));
            }
        }

        // Tasowanie talii
        std::srand(static_cast<unsigned int>(std::time(0)));
        std::random_shuffle(drawPile.begin(), drawPile.end());

        // Rozdanie kart początkowych
        for (int i = 0; i < players.size(); i++) {
            for (int j = 0; j < 5; j++) {
                Card* card = drawCard();
                players[i].addToHand(card);
            }
        }
    }

    ~Game() {
        // Zwalnianie pamięci zajmowanej przez karty
        for (Card* card : drawPile) {
            delete card;
        }
        for (Card* card : discardPile) {
            delete card;
        }
    }

    void play() {
        while (!drawPile.empty() || !discardPile.empty()) {
            std::cout << "----- Runda " << roundCount << " -----" << std::endl;

            developmentPhase();
            battlePhase();

            currentPlayer = (currentPlayer + 1) % players.size();
            roundCount++;
        }

        calculateScores();
        displayResults();
    }

private:
    Card* drawCard() {
        if (drawPile.empty()) {
            // Tasowanie kart ze stosu odrzuconych
            std::random_shuffle(discardPile.begin(), discardPile.end());
            drawPile = discardPile;
            discardPile.clear();
        }

        Card* card = drawPile.back();
        drawPile.pop_back();
        return card;
    }

    void developmentPhase() {
        Player& player = players[currentPlayer];

        // Dobieranie kart
        int drawCount = player.getHand().size() + 1;
        for (int i = 0; i < drawCount; i++) {
            Card* card = drawCard();
            player.addToHand(card);
        }

        // Wyświetlanie ręki gracza
        std::cout << "Gracz " << currentPlayer + 1 << ", Twój ręka to: ";
        const std::vector<Card*>& hand = player.getHand();
        for (Card* card : hand) {
            std::cout << card->getName() << " ";
        }
        std::cout << std::endl;
    }

    void battlePhase() {
        Player& currentPlayer = players[this->currentPlayer];
        Player& nextPlayer = players[(this->currentPlayer + 1) % players.size()];

        std::cout << "Gracz " << this->currentPlayer + 1 << ", atakuje gracza " << (this->currentPlayer + 1) % players.size() + 1 << std::endl;

        // Atak zwierząt
        for (Card* attacker : currentPlayer.getHand()) {
            for (Card* defender : nextPlayer.getHand()) {
                if (canAttack(attacker, defender)) {
                    attack(attacker, defender);
                    break;  // Każde zwierzę może wykonać tylko jeden atak
                }
            }
        }

        // Usuwanie martwych zwierząt z rąk graczy
        removeDeadCards(currentPlayer);
        removeDeadCards(nextPlayer);
    }

    bool canAttack(Card* attacker, Card* defender) {
        const std::vector<int>& attackerTraits = attacker->getTraits();
        const std::vector<int>& defenderTraits = defender->getTraits();

        for (int i = 0; i < traitCount; i++) {
            if (attackerTraits[i] == 1 && defenderTraits[i] == 1) {
                return true;  // Atak możliwy tylko wtedy, gdy istnieje cecha, którą można zaatakować
            }
        }

        return false;
    }

    void attack(Card* attacker, Card* defender) {
        const std::string& attackerName = attacker->getName();
        const std::string& defenderName = defender->getName();

        std::cout << "Zwierzę " << attackerName << " atakuje zwierzę " << defenderName << std::endl;

        const std::vector<int>& attackerTraits = attacker->getTraits();
        const std::vector<int>& defenderTraits = defender->getTraits();

        for (int i = 0; i < traitCount; i++) {
            if (attackerTraits[i] == 1 && defenderTraits[i] == 1) {
                if (i == 0) {
                    std::cout << "Ostry wzrok - " << attackerName << " zjada " << defenderName << std::endl;
                    discardPile.push_back(defender);
                    players[(currentPlayer + 1) % players.size()].removeFromHand(defender);
                }
                else if (i == 1) {
                    std::cout << "Kamuflaż - " << attackerName << " nie może zjeść " << defenderName << std::endl;
                }
                else if (i == 2) {
                    std::cout << "Duże szczęki - " << attackerName << " zjada " << defenderName << std::endl;
                    discardPile.push_back(defender);
                    players[(currentPlayer + 1) //Gracz, który zdobył najwięcej punktów na podstawie posiadanych zwierząt i cech, wygrywa grę.

//Teraz dodajemy logikę zakończenia gry i podliczania punktów. Po zakończeniu gry, będziemy sortować graczy według ich punktów i wyświetlać wyniki.


    void calculateScores() {
        std::vector<int> scores(players.size(), 0);

        for (const Player& player : players) {
            for (Card* card : player.getHand()) {
                scores[currentPlayer] += 2;  // 2 punkty za zwierzę
                const std::vector<int>& traits = card->getTraits();
                for (int trait : traits) {
                    if (trait == 1) {
                        scores[currentPlayer] += 1;  // 1 punkt za cechę
                    }
                }
            }
        }

        // Sortowanie graczy według punktów
        std::vector<int> sortedIndices(players.size());
        for (int i = 0; i < players.size(); i++) {
            sortedIndices[i] = i;
        }

        std::sort(sortedIndices.begin(), sortedIndices.end(), [&scores](int a, int b) {
            return scores[a] > scores[b];
        });

        // Wyświetlanie wyników
        std::cout << "----- Wyniki -----" << std::endl;
        for (int i = 0; i < players.size(); i++) {
            int playerIndex = sortedIndices[i];
            std::cout << "Gracz " << playerIndex + 1 << ": " << scores[playerIndex] << " punktów" << std::endl;
        }
    }

    void displayResults() {
        std::cout << "----- Koniec gry -----" << std::endl;
        calculateScores();
    }
};

int main() {
    Game game;
    game.play();

    return 0;
}
