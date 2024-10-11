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

int main()
{
    char choice{};
    do{
        int num = getRandomNum();
        std::cout << "Let's play a game. I'm thinking of a number between 1 and 100. You have 7 tries to guess what it is." << '\n';

        int guess{};
        for(int i = 1; i <= 7; i++)
        {
            std::cout << "Guess " << i << ": ";
            std::cin >> guess;

            if(guess < num)
            {
                std::cout << "Your guess is too low." << '\n';
                if(i == 7)
                    std::cout << "Sorry. You lost! The correct answer was " << num << '\n';
            }
            else if(guess > num)
            {
                std::cout << "Your guess id too high." << '\n';
                if(i == 7)
                    std::cout << "Sorry. You lost! The correct answer was " << num << '\n';
            }
            else
            {
                std::cout << "Correct! You win!" << '\n';
                break;
            }
        }

        choice = 't';                 //to remove last inputted value
        while(choice != 'y' && choice != 'Y' && choice != 'N' && choice != 'n')
        {
            std::cout << "Play Again?(y/n) : ";
            std::cin >> choice;
        }
    }
    while(choice == 'y' || choice == 'Y');

    std::cout << "Thanks for playing!" << std::endl;
    return 0;
}
