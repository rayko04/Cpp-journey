#include <iostream>

struct node
{
    int data{};
    node* next{nullptr};
};

class cirList
{
    private:
        node* head{nullptr};
    public:
        bool empty() {return head==nullptr;}
        node* search(int val)
        {
            node* temp{head};
            do
            {
                if(temp->data == val)
                    return temp;
                temp = temp->next;
            }
            while(temp != head);
            return nullptr;
        }

        void insertAtEnd(int val)
        {
            node* newer{new node};
            newer->data = val;

            if(empty())
            {
                newer->next = newer;
                head = newer;
            }
            else
            {
                node* temp{head};
                while(temp->next != head)
                    temp = temp->next;
                
                temp->next = newer;
                newer->next = head;
            }           
        }


        void delParticular(int key)
        {
            if(empty())
            {
                std::cout << "empty!" << '\n';
                return;
            }

            node* found{search(key)};
            if(found == nullptr)
            {
                std::cout << key << " not found." << '\n';
                return;
            }

            if(found == head && singleNode())
            {
                std::cout << head->data << " deleted\n";
                delete head;
                head = nullptr;
                return;
            }

            if(found == head)
            {
                head = found->next;
            }

            node* temp{head};
            while(temp->next != found)
                temp = temp->next;

            temp->next = found->next;

            std::cout << found->data << " deleted\n";
            delete found;
        }

        void show()
        {
            if(empty())
                return;

            node* temp{head};
            do
            {
                std::cout << temp->data << " ";
                temp = temp->next;
            }
            while(temp != head);
            std::cout << '\n';
        }

       bool singleNode() {return head->next == head;}

        void josephusWin(int k)
        {
            node* temp{head};
            while(!singleNode())
            {
                for(int i{0}; i < k-1; i++)
                {
                    temp = temp->next;
                }
                node* todel{temp};
                temp = temp->next;
                delParticular(todel->data);
            }
        }
};

void makeList(cirList& l, int n)
{
    for(int i{1}; i <= n; i++)
        l.insertAtEnd(i);
}

int main()
{
    std::cout << "enter no of players: ";
    int n{};
    std::cin >> n;

    cirList l{};
    makeList(l, n);

    std::cout << "enter no of players to skip before a kill: ";
    int k{};
    std::cin >> k;

    l.show();
    l.josephusWin(k);
    l.show();

    return 0;
}
