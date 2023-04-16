#include <iostream>
struct StoryNode
{
    std::string nodeAddress;
    std::string happening;
    std::string choice1;
    std::string choice2;
    bool end{};
};

void PlayGame();
void ShowStoryNode(StoryNode &storyNode);
bool CheckEndGame(StoryNode &storyNode);
StoryNode CurrentStoryNode(StoryNode* nodes, int size, std::string &currentAddress);
StoryNode CheckLoopNode(StoryNode &node);

StoryNode storyNodes[] = {
        {"0", "You wakeup in a room STARVING!\nBeside you is a Glowing ROTTEN Apple","Eat","Don't Eat", false},
        {"01", "Your arms disappear, you have INVISIBILITY!\nThere's a door on your left.\nSounds like someone on the other side", "Open Door", "Wait", false},
        {"011", "You walk to the door and open it.\nA man with a knife is shocked the door opened... ", "Stay Still", "Fight", false},
        {"0111", "The man walks in and bumps into you, \nIn confusion he swings his knife around, stabbing you.", "", "", true},
        {"0112", "He had no chance!\nYou managed to get the knife from him.", "Kill", "Spare", false},
        {"01121", "You Stabbed the man in the Chest!", "", "", true},// End - LIVE alternate
        {"01122", "You throw the knife across the room and run to safety.", "", "", true},
        {"012", "A man breaks into the room with a knife!\nBut the door is open", "Stay Still", "Run Away", false},
        {"0121", "The Man leaves and locks the door from the other side.\nYou STARVE :(", "", "", true},
        {"0122", "The man hears feet stomping but doesn't see anything. You ran to safety!", "", "", true},
        {"02", "I'm still starving...\nThere's a door on your left.\nSounds like someone on the other side", "Open Door", "Hide", false},
        {"021", "A man with a knife enters", "Fight", "Run Away", false},
        {"022", "A man breaks into the room with a knife,\nBut the door is open", "Run", "Stay Hidden", false},
        {"0221", "You Run, but the man pushes you to the ground!\n he's about to stab you!", "Fight", "Run Away", false},
        {"0222", "The Man leaves and locks the door from the other side.\nYou starve in your hiding spot. ", "", "", true},
        {"0211", "You're weak, but both of you struggle,\nThe knife SLIDES across the room", "Run Away", "Get Knife", false},
        {"0212", "You're too weak to run faster. \nHe catches you, stabbing you in the chest", "", "", true},
        {"02111", "You've got a head start,\nHe runs for the knife but you run for the door.\nYou made it out alive!", "", "", true},
        {"02112", "You're too weak to run faster,\nHe grabs the knife stabbing you in the chest.", "", "", true}
};
int main()
{
    PlayGame();
    return 0;
}
std::string GetUserInput()
{
    std::string i = "0";

    while(i == "0")
    {
        std::cin >> i;

        if(i == "1" || i == "2")
        {
            std::cout << '\n';
        }
        else
        {
            std::cout << "Choose (1 or 2)\n";
            i = "0";
        }
    }

    return i;
}
void PlayGame()
{
    bool end = false;
    std::string currentNodeAddress = "0";

    while(!end)
    {
        StoryNode node = CurrentStoryNode(storyNodes, 19, currentNodeAddress);
        node = CheckLoopNode(node);
        ShowStoryNode(node);
        end = CheckEndGame(node);
        currentNodeAddress += GetUserInput();
    }


}
StoryNode CurrentStoryNode(StoryNode* nodes, int size, std::string &currentAddress)
{
    StoryNode node = StoryNode();

    for(int i = 0; i < size; i++)
    {
        node = nodes[i];
        if(node.nodeAddress == currentAddress)
        {
            return node;
        }
    }
    return node;
}
void ShowStoryNode(StoryNode &storyNode)
{
    std::string happening = storyNode.happening;
    std::cout << "\n========================================================\n";
    std::cout << happening;
    std::cout << "\n========================================================\n\n";

    if(!storyNode.end)
    {
        std::cout << "1 - " << storyNode.choice1 << '\n';
        std::cout << "2 - " << storyNode.choice2 << '\n';
        std::cout << "Choose (1 or 2): ";
    }

}
StoryNode CheckLoopNode(StoryNode &node)
{
    if(node.nodeAddress == "0221")
    {
        // 0221 uses the same story branches as 021. So we can build from there.
        node.nodeAddress = "021";
        return node;
    }
    else
    {
     return node;
    }
}
bool CheckEndGame(StoryNode &storyNode)
{
    if(storyNode.end)
    {
        std::string endAlive[] = {"0122","01122","02111"};
        std::string endAliveAlt[] = {"01121"};
        std::string endDead[] = {"0111", "0121", "0212", "02112", "0222"};

        std::string *array = endAlive;
        for(int i = 0; i < array->length(); i++)
        {
            if(storyNode.nodeAddress == endAlive[i])
            {
                std::cout << "\n********************************************************";
                std::cout << "                          You LIVED! :D ";
                std::cout << "\n********************************************************";

                break;
            }
            else if (storyNode.nodeAddress == endAliveAlt[i])
            {
                std::cout << "\n********************************************************\n";
                std::cout << "              You Lived... But at what cost.";
                std::cout << "\n********************************************************\n";

                break;
            }
            else if (storyNode.nodeAddress == endDead[i])
            {
                std::cout << "\n********************************************************\n";
                std::cout << "                          You DIED :(";
                std::cout << "\n********************************************************\n";

                break;
            }
        }

        return true;
    }
    else
    {
        return false;
    }
}

