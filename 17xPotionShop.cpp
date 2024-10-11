#include <iostream>
#include <array>
#include <cassert>
#include <vector>
#include "Random.h"

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

namespace Shop
{
    constexpr std::array potionName{"healing", "mana", "speed", "invisibility"};
    auto length{std::size(potionName)};

    constexpr std::array potionCost{20, 30, 12, 50};

    static_assert(std::size(potionName) == std::size(potionCost), "array size error");
}

class Person
{
private:
    std::string m_name{};
    int m_gold{};
    std::vector<int> m_inventory{};

public:
    Person(std::string name, int gold = Random::get(85, 120)) : m_name{name}, m_gold{gold}, m_inventory(Shop::length, 0) {}

    std::string getName() const { return m_name; }
    int getGold() const { return m_gold; }

    bool buy(int cost)
    {
        if (m_gold >= cost)
            m_gold -= cost;
        else
            return false;

        return true;
    }

    void setInventory(std::size_t index)
    {
        m_inventory[index]++;
    }

    void showInventory()
    {
        std::cout << "Your inventory contains: \n";
        for (std::size_t i{0}; i < Shop::length; i++)
        {
            if (m_inventory[i] != 0)
                std::cout << m_inventory[i] << "x potion of " << Shop::potionName[i] << '\n';
        }
        std::cout << "You escaped with " << m_gold << " gold.\n";
    }
};

Person makePerson()
{
    std::cout << "Enter name: ";
    std::string name{};
    std::cin >> name;

    return {name};
}

void menu()
{
    std::cout << "\nHere is our selection for today:\n";

    for (std::size_t i{0}; i < size(Shop::potionName); i++)
    {
        std::cout << i << ") " << Shop::potionName[i] << " costs " << Shop::potionCost[i] << '\n';
    }
}

int charNumToInt(char c)
{
    return c - '0';
}

char getInput()
{
    char choice{};
    while (true)
    {

        std::cin >> choice;

        if (!std::cin)
        {
            std::cin.clear();
            ignoreLine();
            std::cout << "That is an invalid input. Try again: ";
            continue;
        }

        if (!std::cin.eof() && std::cin.peek() != '\n')
        {
            std::cout << "I didn't understand what you said.  Try again: ";
            ignoreLine(); // ignore any extraneous input
            continue;
        }

        if (charNumToInt(choice) >= static_cast<int>(Shop::length) && choice != 'q')
        {
            std::cout << "That is an invalid input. Try again: ";
            std::cin.clear();
            ignoreLine();
            continue;
        }

        return choice;
    }
}

void purchase(int no, Person &p)
{
    auto index{static_cast<std::size_t>(no)};
    bool bought{p.buy(Shop::potionCost[index])};

    if (bought)
    {
        std::cout << "You purchased a potion of " << Shop::potionName[index] << ". You have " << p.getGold() << " gold left.\n";

        p.setInventory(index);
    }
    else
        std::cout << "You donot have enough gold.\n";
}

int main()
{
    std::cout << "Welcome to Roscoe's potion emporium!\n";
    Person p{makePerson()};
    std::cout << "Hello, " << p.getName() << " you have " << p.getGold() << " gold.\n";

    char choice{};
    while (true)
    {
        menu();
        std::cout << "\nEnter the number of the potion you'd like to buy, or 'q' to quit: ";
        choice = getInput();

        if (choice == 'q')
            break;
        else
        {
            purchase(charNumToInt(choice), p);
        }
    }

    p.showInventory();
    std::cout << "\nThanks for shopping at Roscoe's potion emporium!\n";

    return 0;
}
