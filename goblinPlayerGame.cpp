#include <iostream>
#include <random>

class Creature
{
private:
    int health;
    int hitPoint;
    int loot;
    bool isAlive;

public:
    Creature() : health(10), hitPoint(2), loot(100), isAlive(true) {}

    int getHealth()
    {
        // std::cout << " Health is: " << health << '\n';
        return health;
    }
    void setHealth(int h)
    {
        health = h;
        // std::cout << " Health is: " << health << '\n';
    }
    void setHitPoint(int h)
    {
        hitPoint = h;
    }
    int getHitPoint()
    {
        std::cout << " HitPoint is: " << hitPoint << '\n';
        return hitPoint;
    }
    int getLoot()
    {
        std::cout << "Loot is: " << loot << '\n';
        return loot;
    }
    void setLoot(int l)
    {
        std::cout << l << " loot found." << '\n';
        loot += l;
    }
    bool getIsAlive()
    {
        if (health > 0)
            isAlive = true;
        else
            isAlive = false;

        return isAlive;
    }
};

class Player : public Creature
{
private:
    std::string name;
    int lvl;

public:
    Player() : Creature(), name("Player"), lvl(1) {}

    void setName(std::string n)
    {
        name = n;
    }
    void incrementLevel()
    {
        ++lvl;
    }
    void incrementLevel(int l) // show
    {
        std::cout << " level: " << lvl << '\n';
    }
};

int getRandomNumber()
{
    std::random_device rd{};
    std::seed_seq ss{rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd()};
    std::uniform_int_distribution uid{1, 2};

    std::mt19937 mt{ss};

    return uid(mt);
}

bool playAgain()
{
start:

    std::cout << std::endl;
    std::cout << "Play Again? (y/n): ";
    char choice;
    std::cin >> choice;

    switch (choice)
    {
    case 'y':
    case 'Y':
        return true;
    case 'n':
    case 'N':
        return false;
    default:
        goto start;
    }
}

int main()
{
    do
    {
        Creature goblin;
        Player p1;

        do
        {
            std::cout << std::endl;
            char input;
            std::cout << "Enter 'h' to attack with 50% chance to hit goblin while 50% to hit player: ";
            std::cin >> input;
            std::cout << std::endl;

            if (input == 'h')
            {
                switch (getRandomNumber())
                {
                case 1:
                {
                    std::cout << "Goblin hit!";
                    int hit = p1.getHitPoint();
                    int health = goblin.getHealth();
                    health -= hit;
                    goblin.setHealth(health);
                    std::cout << " Health is: " << health << '\n';

                    if (health <= 0)
                    {
                        int gloot = goblin.getLoot();
                        p1.setLoot(gloot);

                        p1.incrementLevel();

                        goblin.setHealth(10);
                    }
                    break;
                }

                case 2:
                {
                    std::cout << "Player hit!";
                    int hit = goblin.getHitPoint();
                    int health = p1.getHealth();
                    health -= hit;
                    p1.setHealth(health);
                    std::cout << " Health is: " << health << '\n';

                    if (health <= 0)
                    {
                        p1.getLoot();
                        p1.incrementLevel(1);
                    }
                    break;
                }
                }
            }
            else
                continue;
        } while (p1.getIsAlive());

    } while (playAgain());

    std::cout << "Thanks for Playing!" << std::endl;
    return 0;
}
