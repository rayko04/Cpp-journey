
#include <iostream>
#include <random>
int getRandomNumber(){
    std::random_device rd{};
    std::seed_seq ss{rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd()};
    static std::mt19937 mt{ss};
    std::uniform_int_distribution<int>range{1, 100};
    return range(mt);
}
using namespace std;

do{
	int main()
   {

	cout<<"Lets play a number guessing game."
	    <<"I am thinking of a number b/w 1 and 100."
	    <<"\nYou have 7 tries to guess the number?"<<endl;
	
	int randomNumber = getRandomNumber(), no;
	
		for(int i =1; i<=8; i++)
		{
			cout<<"\nInput number b/w 1 and 100: ";
	    	cin >> no;
			if(no==randomNumber)
			{
				cout<<"You Won!"<<endl;
				return 0;
	    	}
			else if(no>randomNumber)
			cout<<"Random Number is smaller"<<endl;
			else
			cout<<"Random Number is greater"<<endl;
		
			if(i==8)
			{
			cout<<"You Lost! "<<"Random Number is "<<randomNumber<<endl;
			return 0;
			}
		}
	bool playAgain(){
    std::cout << "Play again y/n: ";
    char input{};
    std::cin >> input;
    if(input == 'y'){
        return true;
    }
    else{
        return false;
    	}	
    }
	
	
	return 0;
	
	}

}while(playAgain());