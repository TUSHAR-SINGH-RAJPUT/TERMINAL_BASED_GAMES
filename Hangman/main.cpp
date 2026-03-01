#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

class Hangman
{
private:
    string word;
    string guessedWord;
    string hint;
    int attempts;

public:
    Hangman(string w, string question)
    {
        word = w;
        hint = question;
        attempts = 6;
        guessedWord = string(word.length(), '_');
        cout << "\n\t\t\tWelcome to Hangman!" << endl;
    }
    void display()
    {
        int ch = 0;
        while (1)
        {
            cout << "1. Start Game\n2. Exit\nEnter your choice: ";
            
            cin >> ch;
            if (ch == 2)
            {
                cout << "Thank you for playing!" << endl;
                return;
            }
        cout << "\nThe word has " << word.length() << " letters." << endl;
            while (attempts > 0 && guessedWord != word)
            {
                draw();
                char gues;
                cout << "Enter your guess: ";
                cin >> gues;
                guess(gues);
                if(guessedWord == word)
                {
                    cout << "Congratulations! You've guessed the word: " << word << endl;
                    return;
                }
            }
        }
    }

    void draw()
    {
        cout << "\nHint: " << hint << "\n"
             << endl;
        cout << "Word: " << guessedWord << endl;
        cout << "Attempts left: " << attempts << endl;
    }
    void guess(char c)
    {
        bool correct = false;

        for (int i = 0; i < word.length(); i++)
        {
            if (word[i] == c)
            {
                guessedWord[i] = c;
                correct = true;
            }
        }

        if (!correct)
        {
            attempts--;
            skeleton();
        }
    }
    void skeleton()
    {
        if (attempts <= 5)
            cout << "  O  " << endl;

        if (attempts <= 4)
            cout << " /";

        if (attempts <= 3)
            cout << "|";

        if (attempts <= 2)
            cout << "\\" << endl;

        if (attempts <= 1)
            cout << " /";

        if (attempts <= 0){
            cout << " \\ " << endl;
            cout << "Game Over! The word was: " << word << endl;
            // system("cls");
        }
            return;
    }
};

int main()
{
    vector<pair<string, string>> mpp = {
        {"apple", "A fruit that keeps the doctor away."},
        {"banana", "A long yellow fruit."},
        {"cat", "A small domesticated carnivorous mammal."},
        {"dog", "A domesticated carnivorous mammal that typically has a long snout."},
        {"elephant", "The largest land animal."},
        {"guitar", "A musical instrument with six strings."},
        {"house", "A building for human habitation."},
        {"island", "A piece of land surrounded by water."},
        {"jungle", "An area of dense tropical vegetation."},
        {"kangaroo", "A marsupial from Australia."},
        {"lion", "A large carnivorous feline mammal."},
        {"mountain", "A large natural elevation of the earth's surface."},
        {"notebook", "A small book with blank or ruled pages for writing notes."},
        {"ocean", "A vast body of salt water that covers almost three-quarters of the earth's surface."},
        {"piano", "A musical instrument with a keyboard."},
        {"quilt", "A warm bed covering made of padding enclosed between layers of fabric."},
        {"river", "A large natural stream of water flowing in a channel to the sea, a lake, or another river."},
        {"sunflower", "A tall plant with a large yellow flower head."},
        {"tiger", "A large carnivorous feline mammal with a striped coat."},
        {"umbrella", "A device for protection against the rain or sun."},
        {"volcano", "A mountain or hill with a crater or vent through which lava, rock fragments, hot vapor, and gas are being or have been erupted from the earth's crust."},
        {"whale", "A large marine mammal."},
        {"xylophone", "A musical instrument played by striking a row of wooden bars of graduated length with one or more small wooden or plastic mallets."},
        {"yacht", "A medium-sized sailboat equipped for cruising or racing."},
        {"zebra", "An African wild horse with black-and-white stripes."},
        {"avocado", "A pear-shaped fruit with a rough leathery skin and smooth, oily edible flesh."},
        {"bicycle", "A vehicle composed of two wheels held in a frame one behind the other, propelled by pedals and steered with handlebars attached to the front wheel."},
        {"candle", "A cylinder or block of wax or tallow with a central wick that is lit to produce light as it burns."},
        {"dolphin", "A small gregarious toothed whale that typically has a beaklike snout and a curved fin on the back."},
        {"eagle", "A large bird of prey with a massive hooked bill and long broad wings, renowned for its keen sight and powerful soaring flight."}

    };
    srand(time(0));
    int r = rand() % mpp.size();

    Hangman game(mpp[r].first, mpp[r].second);

    game.display();

    return 0;
}