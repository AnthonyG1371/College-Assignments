#include<iostream>
#include<fstream>
#include "binary_tree.h"
using namespace std;
ifstream infile;
ofstream outfile;

binary_tree checktree(binary_tree &, binary_tree::node *);

int main()
{
    //Stranswer and answer are used for cin.
    //Animaltree is obviously the binary tree I am using.
    //Current is the current node, which starts at root here, but changes in
    //checktree() when it is called recursively
    string stranswer;
    char answer[256];
    binary_tree animaltree;
    binary_tree::node *current;
    bool valid;
  
//The commented out lines would be used if I was reading in a text file,
//but I'm not.    
//    fstream infile("animalTree.txt", fstream::in);
//    if(infile.fail())
//    {
//        cout << "Error: File not found. Proceeding with New Game" << endl;
        cout << "Proceeding with New Game" << endl;
        cout << "Input an animal to start with: ";
        cin.getline(answer, 256);
        stranswer = answer;
        animaltree.addRoot(answer);
//    }
    
    cout << "\nThe program will now try to 'guess' the animal you are thinking about \nby asking questions. Please respond by inputting 'y' or'n' to answer" << endl;
//    system("pause");
    cout << endl << endl;
    
    do
    {
        valid = false;
        stranswer = "";
        cout << "Think of an animal." << endl;
        current = animaltree.getRoot();
        checktree(animaltree, current);
        cout << "Play again? ";
        while(!valid)
        {
            cin.getline(answer, 256);
            stranswer = answer;
            if(stranswer == "y" || stranswer == "n") {valid = true;}
            else {cout << "Invalid Response. Please input again: ";}
        }
        cout << endl << endl;
    }while(stranswer != "n");
    
    animaltree.print();
    
//    system("pause");
    return 0;
}

/*
  Checktree() is the function that contains a reference to animaltree to ensure it
  is modified as the program runs. It checks if the current node is a leaf or not
  and runs different operations depending on that. See below for details.
*/
binary_tree checktree(binary_tree &animaltree, binary_tree::node *current)
{
    char answer[256];
    string stranswer, question, animal;
    bool valid;
        
    //Checks if root has a left and a right: If true, it is a question node
    //If false, it is a leaf, and will ask if that is the correct animal.
    if(current->left && current->right)
    {   
        valid = false;
        cout << current->data << " ";
        
        //Asks the yes or no question and recursivley calls the function
        //checktree() again until it hits a leaf.  
        while(!valid)
        {
            cin.getline(answer, 256);
            stranswer = answer;
            
            if(stranswer == "y")
            {
                checktree(animaltree, current->left);
                valid = true;
            }
            else if(stranswer == "n")
            {
                checktree(animaltree, current->right);
                valid = true;
            }
            else
            {
                cout << "Invalid Response. Please input agian" << endl;
            }
        }
    }
    else //If this node is a leaf.
    {
        valid = false;
        cout << "Is the animal a " << current->data  << "? ";
        
        while(!valid)
        {
            cin.getline(answer, 256);
            stranswer = answer;
            
            if(stranswer == "y")
            {
                //If the computer was "correct"
                cout << "I thought so ^_^" << endl;
                valid = true;
            }
            else if(stranswer == "n")
            {
                //If this is not the correct animal, ask for the requested animal.
                //Block of code to set new animal by asking various questions.
                cout << "What animal is it? " << endl;
                cin.getline(answer, 256);
                animal = answer;
                
                cout << "What yes/no question can be used to deterimine this animal?" << endl;
                cin.getline(answer, 256);
                question = answer;
                
                stranswer = "";
                while(!valid)
                {
                    cout << "Is the answer to this question to determine a " << animal << " yes or no? Input y or n: ";
                    cin.getline(answer, 256);
                    stranswer = answer;
                    if(stranswer == "y" || stranswer == "n") {valid = true;}
                    else {cout << "Invalid Response. Please input again: ";}
                }
                if(stranswer == "y")
                {
                    animaltree.addRight(current, current->data);
                    animaltree.addLeft(current, animal);
                    current->data = question;
                }
                else if(stranswer == "n")
                {
                    animaltree.addRight(current, animal);
                    animaltree.addLeft(current, current->data);
                    current->data = question;
                }
                valid = true;
            }
            else
            {
                cout << "Invalid Response. Please input again: ";
            }
        }
    }
}
