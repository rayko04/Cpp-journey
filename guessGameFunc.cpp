#include <iostream>
#include <random>

int getRandomNum()
{
    std::random_device rd{};
    std::seed_seq ss{rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd()};
    std::uniform_int_distribution hi_lo{1, 100};
    std::mt19937 mt{ss};

    return hi_lo(mt);
}
bool playGame(const int chances, int num)
{
    for (int i{1}; i <= chances; i++)
    {
        int guess{};
        std::cout << "Guess " << i << ": ";
        std::cin >> guess;

        if (guess < num)
            std::cout << "Your guess is too low." << '\n';
        else if (guess > num)
            std::cout << "Your guess id too high." << '\n';
        else
            return true;
    }

    return false;
}
bool playAgain()
{
    while (true)
    {
        char choice{};
        std::cout << "Play Again?(y/n) : ";
        std::cin >> choice;

        switch (choice)
        {
        case 'y':
        case 'Y':
            return true;
        case 'n':
        case 'N':
            return false;
        }
    }
}
int main()
{
    constexpr int chances{7};
    do
    {
        int num = getRandomNum();
        std::cout << "Let's play a game. I'm thinking of a number between 1 and 100. You have 7 tries to guess what it is." << '\n';

        bool won{playGame(chances, num)};

        if (won)
            std::cout << "Correct! You win!" << '\n';
        else
            std::cout << "Sorry, you lose. The correct number was " << num << '\n';
    } while (playAgain());

    std::cout << "Thanks for playing!" << std::endl;
    return 0;
}
