#include <iostream>
#include "Random.h"
#include <vector>
#include <string_view>

namespace Settings
{
    constexpr int wrongGuessAllowed{6};
}
namespace WordList
{
    std::vector words{"mystery", "broccoli", "account", "almost", "spaghetti", "opinion", "beautiful", "distance", "luggage"};

    std::string_view getRandomWord()
    {
        return words[Random::get<std::size_t>(0, words.size() - 1)];
    }
}

class Session
{
private:
    std::string m_word{WordList::getRandomWord()};
    int m_wrongGuessLeft{Settings::wrongGuessAllowed};
    std::vector<bool> m_track{std::vector<bool>(26)};

    std::size_t toIndex(char ch) const { return static_cast<std::size_t>((ch % 32) - 1); }

public:
    std::string_view getWord() const { return m_word; }

    int getWrongGuessLeft() const { return m_wrongGuessLeft; }
    void removeGuess() { --m_wrongGuessLeft; }

    void setTrack(char ch) { m_track[toIndex(ch)] = true; }
    bool isTrack(char ch) const { return m_track[toIndex(ch)]; }

    bool isInWord(char ch)
    {
        for (auto c : m_word)
        {
            if (c == ch)
                return true;
        }
        return false;
    }

    bool won()
    {
        for (auto c : m_word)
        {
            if (!isTrack(c))
                return false;
        }

        return true;
    }
};

void basicState(const Session &s)
{
    std::cout << "\nThe word is: ";

    for (auto c : s.getWord())
    {
        if (s.isTrack(c))
            std::cout << c;
        else
        {
            std::cout << '_';
        }
    }

    std::cout << " Wrong guesses: ";
    for (int i{0}; i < s.getWrongGuessLeft(); i++)
        std::cout << '+';

    std::cout << std::endl;
}

char getInput(Session &s)
{
    while (true)
    {
        std::cout << "Enter your next letter: ";
        char ch;
        std::cin >> ch;

        if (!std::cin)
        {
            std::cin.clear();
            std::cout << "That wasn't a valid input. Try again.\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (ch < 'a' || ch > 'z')
        {
            std::cout << "That wasn't a valid input. Try again.\n";
            continue;
        }

        if (s.isTrack(ch))
        {
            std::cout << "You already guessed that. try again.\n";
            continue;
        }

        return ch;
    }
}

void handleGuess(Session &s, char ch)
{
    s.setTrack(ch);

    if (s.isInWord(ch))
    {
        std::cout << "yes, " << ch << " is in the word.\n";
        return;
    }

    std::cout << "No, " << ch << " is not in word.\n";
    s.removeGuess();
}

int main()
{
    std::cout << "Welcome to C++man (a variant of Hangman)\n";
    std::cout << "To win: guess the word. To lose: run out of pluses.\n";

    Session s{};

    while (s.getWrongGuessLeft() && !s.won())
    {
        basicState(s);
        char ch{getInput(s)};
        handleGuess(s, ch);
    }

    basicState(s);

    if (!s.getWrongGuessLeft())
        std::cout << "You lost! The word was: " << s.getWord() << std::endl;
    else
        std::cout << "you won!\n";

    return 0;
}
