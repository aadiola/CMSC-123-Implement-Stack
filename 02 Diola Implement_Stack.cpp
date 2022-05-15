/*
REQUIREMENT #2
A C++ code demonstrating an implementation of a stack together with appropriate functions in fulfillment of the course Data Strctures.
Code Written By: Alex Diola
*/



#include <iostream>

using namespace std;

int numSpaces (int); //Used for the printing of a Stack Diagram


class Node{         //Node Class for int data type

    private:
        int data;
        Node *nodeBelow = nullptr;

    public:
        Node(int initialData){  //Constructor for the Node class
            data = initialData; //Insertion of Data to Node
        }
        void setBelow(Node *newBelow){ //Setter Next Node/ Node belo
            nodeBelow = newBelow;
        }
        int getData(void){      //Get the data of the node. This function is necessary since the data is of private access
            return data;
        }
        Node *getNodeBelow(void){ //Get the next node. This function is necessary since nodeBelow is of private access
            return nodeBelow;
        }
};

class Stack{    //Stack class using a singly linked list for int nodes

    private:
        Node *top = nullptr;
        int levels = 0; //Used for keeping position of nodes, but can be removed if positioning property is not needed

    public:
        bool isEmpty(void){     //Checks if the Stack is empty
            return top==nullptr;  
        }
        void push(int data){    //Creates a new data node, and pushes it to top of stack
            Node *newNode = new Node(data);
            if(!isEmpty()){     //If stack is not empty, then previousTop is set as belowNode of new node (top)
                newNode->setBelow(top);
            }
            top = newNode;      //New node is always the new top
            levels++;           //Increments levels/listLength/Position Tracker
            return;
        }
        int pop(void){          //Pops the top node, and returns data in node
            Node *nodeToPop = top;
            int returnVal = nodeToPop->getData();
            top = top->getNodeBelow(); //Node is dereferenced
            delete nodeToPop;   //Deallocates node, not just dereferenced
            levels--;
            return returnVal;
        }
        void printStackDiagram(void){   //Prints that stack in a diagram form for easier visual comprehension
            if(isEmpty()){              //Catches if Stack is empty to print empty stack, and notify user
                cout <<  "|___________|" << endl;
                cout << "\nStack is empty." << endl;
                return;
            }
            Node *currentNode = top;
            int level = levels;         //Position of node in stack
            while(currentNode != nullptr){
                int i;  //Initialized here so that no initialization occurs in multiple ff for-loops
                cout << "\t|           |\n";
                cout << "(" << level-1 << ")\t|"; 
                for(i=0; i<numSpaces(currentNode->getData())/2; i++) cout << " "; //numSpaces is divided by two for both sides
                cout << currentNode->getData();
                for(i=0; i<(1+numSpaces(currentNode->getData()))/2; i++) cout << " "; //has a plus 1 to compensate for in division round down (e.g. 7/2 = 3 int)
                cout << "|\n\t|___________|" << endl;
                currentNode = currentNode->getNodeBelow();
                level--;
            }
            cout << "\nStack has " << levels << " nodes.\n" << endl;
            return;
        }
        void printStackList(void){      //Prints stack in a linear fashion for easier content analysis  
            if(isEmpty()){              //Catches if user tries to print an empty stack   
                cout << "\nStack is empty.\n" << endl;
                return;
            }
            Node *currentNode = top;
            cout << "[TOP]\t---->\t[BOTTOM]\n" << endl; //Shows user the flow of the direction of arrow
            while(currentNode->getNodeBelow()!=nullptr){
                cout << currentNode->getData() << " --> ";
                currentNode = currentNode->getNodeBelow();
            }
            cout << currentNode->getData()<< endl;
            return;
        }
        void findNode(void){        //Finds Data using a Node level or position
            if(isEmpty()){              //Catches if user tries to print an empty stack   
                cout << "\nStack is empty.\n" << endl;
                return;
            }
            int nodeLevel;
            cout << "Enter Level of Node to Locate[0:" << levels-1<< "]: ";
            cin >> nodeLevel;
            while(nodeLevel < 0 || nodeLevel > levels-1){ //Catches if user tries top input an invalid position / level
                cout << "Invalid level. Please enter a valid level from 0 to " << levels-1 << "." << endl;
                cout << "Enter Level of Node to Locate[0:" << levels-1<< "]: ";
                cin >> nodeLevel;
            }        
            Node *currentNode = top;
            while(nodeLevel>0){
                currentNode = currentNode->getNodeBelow();
                nodeLevel--;
            }
            cout << "Data Found: " << currentNode->getData() << endl;
            return;
        }
        void findData(void){        //Find the level and times a data occurs in the stack, or if it occurs
            if(isEmpty()){              //Catches if user tries to print an empty stack   
                cout << "\nStack is empty.\n" << endl;
                return;
            }
            int data, occurences = 0, nodeLevel = levels - 1;
            cout << "Enter Data to Search: ";
            cin >> data;
            Node *currentNode = top;
            while(currentNode!=nullptr){
                if(currentNode->getData() == data){
                    cout << data << " located at Node level " << nodeLevel << "." << endl;
                    occurences++;
                }
                currentNode = currentNode->getNodeBelow();
                nodeLevel--;
            }
            if(!occurences){
                cout << "The data inputted (" << data <<") does not exist in the stack." << endl;
            } else {
                cout << "The data occured " << occurences << " time/s in the stack." << endl;
            }
            return;
        }
};


int main(void){

    Stack *testStack = new Stack(); //Creating a stack using a signly linked list
    bool run=true;                  //Allows cleanups when program is about to exit
    int option;

    cout << "\n\t\tRequirement 2: Stack" << endl;
    do{
        cout << "\nPlease choose one of the following options:" <<endl;     //Tab character is added before output in cout
        cout <<     "\t1 -- Push to Stack" << endl;                         //-> To mimic actual output during program run
        cout <<     "\t2 -- Pop Stack" << endl;                             //For ease of recheck of code
        cout <<     "\t3 -- Print Stack (Diagram)" << endl;               //Since it does not affect actual code run/compile
        cout <<     "\t4 -- Print Stack (Linear)" << endl;
        cout <<     "\t5 -- Find a Node (Using Level/Position)" << endl;
        cout <<     "\t6 -- Find Data" << endl;
        cout <<     "\t7 -- Check if Stack is Empty" << endl;
        cout <<     "\t0 -- Exit Program" << endl;
        cout << "OPTION SELECTED: ";
        cin >> option;
        switch (option){
            case 0:
                cout << "EXITING PROGRAM\n" << endl;
                run = false;    //Allows conditional statements after do-while loop in case more cleanup is needed.
                delete testStack; //Proper cleanup.
                break;
            case 1:
                int data;
                cout << "\nOPTION SELECTED:\tPUSH TO STACK\n" <<endl;
                cout << "\nEnter Data to Push: ";
                cin >> data;
                testStack->push(data);
                cout << "Data pushed." << endl;
                break;
            case 2:
                cout << "\nOPTION SELECTED:\tPOP STACK\n" <<endl;
                if(testStack->isEmpty()){
                    cout << "Error: Stack is empty. No node can be popped.\n" << endl;
                } else {
                    cout << "Data Popped: " << testStack->pop() << endl;
                }
                break;        
            case 3:
                cout << "\nOPTION SELECTED:\tPRINT STACK (DIAGRAM)\n" << endl;
                testStack->printStackDiagram();
                break;
            case 4:
                cout << "\nOPTION SELECTED:\tPRINT STACK (LINEAR)\n"<< endl;
                testStack->printStackList();
                break;
            case 5:
                cout << "\nOPTION SELECTED:\tFIND A NODE (USING LEVEL/POSITION)" << endl;
                testStack->findNode();
                break;
            case 6:
                cout << "\nOPTION SELECTED:\tFIND DATA" << endl;
                testStack->findData();
                break;
            case 7:
                cout << "\nOPTION SELECTED:\tCHECK IF STACK IS EMPTY" <<endl;
                if(testStack->isEmpty()){
                    cout<< "\nThe stack is empty." << endl;
                } else {
                    cout << "\nThe stack is not empty." << endl;
                }
                break; 
            default:
                cout << "\nInvalid option selected. Please select an option from menu given." << endl;
        }
    }while(run);


    return 0;
}

int numSpaces(int num){     //Counts the numbers of spaces needed to center-print data in diagram
    int characters = 0;     //Number of characters (digits + sign) in data
    int charMax = 11;       //Since int type has a lower bound of -2147483647 which has 11 characters
    if(num<0){
        characters++;
        num*=(-1);
    }
    do{
        characters++;
        num/=10;
    }while(num>0);
    return charMax-characters; //The number of spaces is the number of characters allowed - # characters of data
}