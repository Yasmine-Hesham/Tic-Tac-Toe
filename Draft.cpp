#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<direct.h>
#include<io.h>
#include<iostream>
using namespace std;
#define maxstack 100 
#define success true
#define underflow false
#define overflow false
const int n = 3;//board size
char player1[25], player2[25];
class Move {
public:
    int row;
    int col;
    int pos;
     Move(){//default constructor
    row=-1;
    col=-1;
    pos=0;}
    Move(int p){ //parameterized constructor
        pos=p;
        row=(p-1)/n;
        col=(p-1)%n;
    }
};
struct node {
    char val;
    struct node* next;
    struct node* down;  //like a 2 dimension linked list
};
class Stack {
public:
    Stack();
    bool empty()const; //this function returns if the string is empty 
    bool pop();
    bool top(Move& item); //assigning a reference 
    bool push(const Move& item);//assigining a reference 
private:
    int count;
    Move entry[maxstack]; //it is an array named entry of type Move and size 100
};
Stack::Stack()
{
    count = 0;// count de hya el top bs bade2 men zero
}
bool Stack::push(const Move& item)
{
    bool outcome =success;
    if (count >= maxstack)
        return overflow;
    else
        entry[count++] = item; //if there is still space then push the "item" into element no. "count++" in "entry"
    return outcome;
}
bool Stack::pop()
{
    bool outcome = success;
    if (count == 0)
        outcome = underflow;
    else --count;
    return outcome;
}
bool Stack::top(Move& item)
{
    bool outcome = seccess;
    if (count == 0)
        return underflow;
    else
        item = entry[count - 1]; //count -1 as the 1st element [0] is of count 1
    return outcome;
}
bool Stack::empty()const
{ //it checks if the stack is empty or not
    bool outcome = true;
    if (count > 0) //if count >0 then it's not empty
        outcome = false;
    return outcome;
}
class Board{
public:
    Board();
    void printBoard();
    Move getposition(Move new_move);
    Move input();
    void perform_move(Move step);
    int isGameOver();
    bool done();
    void playerWins(char c);
    int legal_moves(Stack& moves);
    bool is_ok(Move step);
    int evaluate();
    int worst_case();
    bool better(int value, int old_value);
    int moves_done;
    int Winner;
    int pl;
    struct node* arr[n];
};
Board:: Board() {
    moves_done = 0;
    pl=1;
    Winner=0;
    int i, j;
    struct node* newNode, * ptr;
    for (i = 0; i < n; i++) {//initialize the board
        for (j = 0; j < n; j++) {
            newNode = new node();
            newNode->next = NULL;
            newNode->down = NULL;
            newNode->val = ' ';//makes the values of the board empty
            if (j == 0) {
                arr[i] = newNode;//put the head of the linked list in the array elements
                ptr = arr[i];
            }
            else {//create the rows by creating nodes of the linkedlists
                ptr->next = newNode;
                ptr = ptr->next;
            }
        }
    }
    //down pointer
    for (j = 0; j < n - 1; j++) {
        ptr = arr[j];//
        newNode = arr[j + 1];
        for (i = 0; i < n; i++) {//links each node with the node beneath it
            ptr->down = newNode;
            ptr = ptr->next;
            newNode = newNode->next;
        }
    }
}
//prints the board
void Board::printBoard() {//**ba3dein
    int i, j, k;
    struct node *ptr;
    for(k=0;k<n;k++){
   		cout<<" ---------------";
    }
    cout<<"\n";
    for(i=0; i<n; i++) {

   		cout<<"|";
   		for(k=0;k<n;k++){
   			cout<<"               |";
   		}
   		cout<<"\n";       
   		cout<<"|";
   		for(k=0;k<n;k++){
   			cout<<"               |";
   		}
   		cout<<"\n";

        ptr = arr[i];
        for(j=1; j<=n; j++) {
            if(ptr->val == ' '){
                cout<<"|\t"<<i*n+j<<"\t";
            }
            else{
            	if(ptr->val=='X'){
            		cout<<"|";
               		cout<<"\t"<<ptr->val<<"\t";
           		}
           		else{
            		cout<<"|";           			
           			cout<<"\t"<<ptr->val<<"\t";
           		}
            }
            ptr=ptr->next;
        }
        cout<<"|";
        cout<<"\n";


        cout<<"|";
   		for(k=0;k<n;k++){
   			cout<<"               |";
   		}
   		cout<<"\n";       
   		cout<<"|";
   		for(k=0;k<n;k++){
   			cout<<"               |";
   		}
   		cout<<"\n";       
        for(k=0;k<n;k++){
   			cout<<" ---------------";
    	}
    	cout<<"\n";


    }
}
int validinput(int choice)//retakes input when users enters a character not an integer
   { while (cin.fail())  //while the data type declared doesn't match data type entered
	{
	cout << "Invalid Choice.  Select again: ";  //error msg
			cin.clear();   //clear istream
			cin.ignore();  //repair istream
			cin >> choice; //get user input again
	}
    return choice;}
bool Board::is_ok(Move step)
/**Judging whether this step is feasible**/
{
    if(step.pos<1 || step.pos>n*n){
        return false;}// if move is outside the board
    struct node *ptr; 
    ptr =arr[step.row];
	for(step.pos=0; step.pos!=step.col; step.pos++) {
	    ptr = ptr->next;
	    }
	if(ptr->val != ' ') {// if the destination is already taken
	    return false;}
    else return true;
}
Move Board:: getposition(Move new_move) {//gets the row and coloumn of the entered position
    new_move.row = (new_move.pos - 1) / n;
    new_move.col = (new_move.pos - 1) % n;
    return new_move;
}
Move Board::input(){
    Move step;
    cout<<("Enter a number to place your symbol there: ");
    cin>>step.pos;
    step.pos=validinput(step.pos);//checks that the input is not a character
    step= getposition(step);
    if (!is_ok(step))//if input move is invalid it takes another input
    {
        cout<<("Invalid position\n");
        step=input();
    }
    return step;
}
int Board::isGameOver() {
    int gameOver, i, j;
    struct node *ptr;
    char values[n];//*array to
    //Horizontal Check
    for (i = 0; i < n; i++)//to check each row
    {
        gameOver = 1;
        ptr = arr[i];
        for (j = 0; j < n; j++) {//puts each element in the row in array values
            values[j] = ptr->val;
            ptr = ptr->next;
        }
        //checking if row is equal
        for (j = 0; j < n - 1; j++) {
            if (values[j] == ' ' || values[j + 1] == ' ') {//if there is a vacancy in the row then still no winner
                gameOver = 0;
                break;
            }
            else if (values[j] != values[j + 1]) {//if an element in the array isn't the same as the element after it then still no winner
                gameOver = 0;
                break;
            }
        }
        if (gameOver == 1) {
            playerWins(values[j]);//sends X or O according the winner
            return gameOver;
        }
    }
    //Vertical Check
    for (i = 0; i < n; i++) {
        ptr = arr[0];
        for (j = 0; j < i; j++) {
            ptr = ptr->next;
        }
        gameOver = 1;
        for (j = 0; j < n; j++) {
            values[j] = ptr->val;//puts element in the coloumn in array values
            ptr = ptr->down;
        }
        //checking if column is equal
        for (j = 0; j < n - 1; j++) {
            if (values[j] == ' ' || values[j + 1] == ' ') {
                gameOver = 0;
                break;
            }
            if (values[j] != values[j + 1]) {
                gameOver = 0;
                break;
            }
        }
        if (gameOver == 1) {
            playerWins(values[j]);
            return gameOver;
        }
    }
    //leading Diagonal
    for (i = 0; i < n; i++) {
        gameOver = 1;
        ptr = arr[i];
        for (j = 0; j < i; j++) {//row number is the number of the element in the diagonal
            ptr = ptr->next;
        }
        values[i] = ptr->val;//puts the element of the diagonal in value
        //checking if leading diagonal is equal
        for (j = 0; j < n - 1; j++) {
            if (values[j] == ' ' || values[j + 1] == ' ') {
                gameOver = 0;
                break;
            }
            if (values[j] != values[j + 1]) {
                gameOver = 0;
                break;
            }
        }
        if (gameOver == 1) {
            playerWins(values[j]);
            return gameOver;
        }
    }
    //other Diagonal
    for (i = n - 1; i >= 0; i--) {//bada2t men akher row
        gameOver = 1;
        ptr = arr[n - i - 1];
        for (j = 0; j < i; j++) {
            ptr = ptr->next;
        }
        values[n - i - 1] = ptr->val;
        //checking if non-leading diagonal is equal
        for (j = 0; j < n - 1; j++) {
            if (values[j] == ' ' || values[j + 1] == ' ') {
                gameOver = 0;
                break;
            }
            if (values[j] != values[j + 1]) {
                gameOver = 0;
                break;
            }
        }
        if (gameOver == 1) {
            playerWins(values[j]);
            return gameOver;
        }
    }
    return gameOver;
}
bool Board::done()
/**Judging whether the game is over**/
{
    if(isGameOver())
        return 1;//if there is a winner return true
    return (moves_done == n*n );//if its a draw return true
}
//indicates which player wins
void Board:: playerWins(char c) {
    if (c == 'X') {
        Winner= 1;
    }
    else {
        Winner= 2;
    }
}
void Board ::perform_move (Move step){// perform the move step on the board
    struct node *ptr;
    ptr =arr[step.row];
    for(step.pos=0; step.pos!=step.col; step.pos++) {
        ptr = ptr->next;
        }
    if(pl % 2 == 1 ) {//player1
      ptr->val = 'X';
      pl++;// increments player counter to make it the next player's turn
     }
    else {
      ptr->val = 'O';//player2
      pl++;
    }
    moves_done++;//increments the moves counter 
    return;
}
int Board:: evaluate()
/**Return to a number, which reflects the winning or losing and how many steps have been taken.
   For calculating the final result of each feasible step in the following recursive function**/
{
    if (Winner == 1)
        return 10 - moves_done;// returns the number of moves remaining to reach the worst case
    else if (Winner == 2)
        return moves_done - 10;// returns the number of moves remaining to reach the worst case but -ve to differentiate between players
    else
        return 0;//It ends in a draw
}
int Board::worst_case() 
/*Return the worst case for easy comparison in recursion*/
{
    if (moves_done % 2)    //For Player 2
        return 10;
    else return -10;    //For Player 1
}
bool Board::better(int value, int old_value)
/*Compare the two values which is best*/
{
    if (moves_done % 2)    //For Player 2
        return value < old_value;
    else                //For Player 1
        return value > old_value;
}
int Board::legal_moves(Stack& moves) 
/*Store all feasible steps in the incoming stack*/
{
    int count = 0;
    while (!moves.empty()) //while the stack "moves" is not empty 
        moves.pop(); //empty it first
    for (int i = 1; i < n*n+1; i++)
        {
            Move can_play;
            can_play(i);
            if(is_ok(can_play))//checks if the move is feasible
               { moves.push(can_play); //and it's pushed in the stack moves
                count++;}
        }
    return count;
}
void assign(Board& new_game, Board game) {//copies board game in board new_game
	int i,j;
	struct node *ptr1, *ptr2;
	for(i=0; i<n; i++) {
		ptr1 = game.arr[i];
        ptr2 = new_game.arr[i];
		for(j=0; j<n; j++) {
			ptr2->val =ptr1->val;
			ptr1 = ptr1->next;
            ptr2 = ptr2->next;
		}
	}
    new_game.Winner=game.Winner;
    new_game.pl= game.pl;
    new_game.moves_done= game.moves_done;
}
int look_ahead(Board& game, int depth, Move& recommended) 
{
    if (game.done() || depth == 0) //if the game is over or depth(IQ) is zero return game evaluation to help computer decide the best move
        return game.evaluate(); 
    else
    {
        Stack moves;
        game.legal_moves(moves);
        int value;
        int best_value = game.worst_case();
        while (!moves.empty()) //while the stack is not empty 
        {
            Move try_it, reply; //declares 2 objects of the class Move 
            moves.top(try_it); //peak the last move added and store it in try_it
            Board new_game;
            assign(new_game, game);  //copy the board game to board new_game for the computer to try moves on
            new_game.perform_move(try_it); //perform the move
            value = look_ahead(new_game, depth - 1, reply); //call look_ahead to get the best next move
            if (game.better(value, best_value)) //if value is better than best value 
            {
                best_value = value; //make value the new better value 
                recommended = try_it; //make the recommended move equal try_it
            }
            moves.pop(); //pop the move that was tried to try another
        }
        return best_value; //in the end it'll come back with the best decision 
    }
}
void player1info (){\\ fuction to get player1's info
    system("cls");
    cout<<"Player 1 Enter your name: \n";
    cin>>player1;//string
    cout<<player1<< " your symbol is X\n\n\n";
}
int playing(int intel, int mode)
{
    Board game;
    Move comp_move;
    do{ // stay in loop untill all blocks are filled
         system("cls");
        game.printBoard();
        if(game.pl % 2 != 0){//takes player 1's input and performs the move
            cout<<"\nYour move "<<player1<<"\n";
            game.perform_move(game.input());
            system("cls");
        }
        else if(mode==1) {//takes player2's input and performs the move
            cout<<"\nYour move "<<player2<<"\n";
            game.perform_move(game.input());
            system("cls");
        }
        else {// perform computer's move
            look_ahead(game, intel,comp_move);
            game.perform_move(comp_move);
            system("cls");
            }
        }while(!game.done());
    system("cls");
    game.printBoard();//??
    return game.Winner;
}

/////////////////////////////////////////////////////////////////////////////////////////
    int main()
    {

    }
