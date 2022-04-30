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
    bool top(Stack_entry& item); //assigning a reference 
    bool push(const Stack_entry& item);//assigining a reference 
private:
    int count;
    Stack_entry entry[maxstack]; //it is an array named entry of type Move and size 100
};
class Board {
public:
    bool done();
    bool is_ok(Move step); //checks if the move is valid
    void print(struct node* arr[]); //prints the board
    int legal_moves(Stack& moves);
private:
    int square[3][3];
    int moves_done;
};
Stack::Stack()
{
    count = 0;// count de hya el top bs bade2 men zero
}
bool Stack::push(const Stack_entry& item)
{
    bool outcome = true;
    if (count >= maxstack)
        return false;
    else
        entry[count++] = item; //if there is still space then push the "item" into element no. "count++" in "entry"
    return outcome;
}
bool Stack::pop()
{
    bool outcome = true;
    if (count == 0)
        outcome = false;
    else --count;
    return outcome;
}
bool Stack::top(Stack_entry& item)
{
    bool outcome = true;
    if (count == 0)
        return false;
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
void Board:: printBoard() {
    int i, j, k;
    struct node* ptr;
    for (k = 0; k < n; k++) {
        cout << (" ---------------");
    }
    cout << ("\n");
    for (i = 0; i < n; i++) {

        cout << ("|");
        for (k = 0; k < n; k++) {
            cout << ("               |");
        }
        cout << ("\n");
        cout << ("|");
        for (k = 0; k < n; k++) {
            cout << ("               |");
        }
        cout << ("\n");

        ptr = arr[i];
        for (j = 1; j <= n; j++) {
            if (ptr->val == ' ') {
                cout << ("|\t%d\t", i * n + j);
            }
            else {
                if (ptr->val == 'X') {
                    cout << ("|");
                    cout << ("\t%c\t", ptr->val);
                }
                else {
                    cout << ("|");
                    cout << ("\t%c\t", ptr->val);
                }
            }
            ptr = ptr->next;
        }
        cout << ("|");
        cout << ("\n");


        cout << ("|");
        for (k = 0; k < n; k++) {
            cout << ("               |");
        }
        cout << ("\n");
        cout << ("|");
        for (k = 0; k < n; k++) {
            cout << ("               |");
        }
        cout << ("\n");
        for (k = 0; k < n; k++) {
            cout << (" ---------------");
        }
        cout << ("\n");

    }
}
bool Board::is_ok(Move step)
/**Judging whether this step is feasible**/
{
    if (step.row >= 0 && step.row < 3 && step.col >= 0 && step.col < 3
        && square[step.row][step.col] == 0)
        return true;
    else return false;
}
Move getposition(Move new_move) {
    new_move.row = (new_move.pos - 1) / n;
    new_move.col = (new_move.pos - 1) % n;
    return new_move;
}
int input(struct node* arr[], int pl) {
    Move step;
    bool x = true;
    cout << ("Enter a number to place your symbol there: ");
    cin >> step.pos;
    step = getposition(step);
        struct node* ptr;
    if (!is_ok(step))
    {
        cout << ("Invalid position\n");
        input(arr, pl);
    }
    ptr = arr[step.row];
    for (step.pos = 0; step.pos != step.col; step.pos++) {
        ptr = ptr->next;
    }
    if (pl % 2 == 1) {//*player1
        ptr->val = 'X';
    }
    else {
        ptr->val = 'O';//*player2
        //increments the draw counter
        draw++;//*3shan awel ema draw de tewsal le n*n byb2a draw
    }
    return draw;//??
}

int isGameOver(struct node* arr[]) {
    int gameOver, i, j;
    struct node* ptr;
    char values[n];//*array to
    //Horizontal Check
    for (i = 0; i < n; i++)
    {
        gameOver = 1;
        ptr = arr[i];
        for (j = 0; j < n; j++) {//* akhadt el values beta3t awel row kolo w 7atetha f array lwa7do
            values[j] = ptr->val;
            ptr = ptr->next;
        }
        //checing if row is equal
        for (j = 0; j < n - 1; j++) {
            if (values[j] == ' ' || values[j + 1] == ' ') {//*lw fi ay wa7da fadya yeb2a maksebesh
                gameOver = 0;
                break;
            }
            else if (values[j] != values[j + 1]) {//*aw lw fi ay wa7da mesh zy el b3dha matnfa3sh
                gameOver = 0;
                break;
            }
        }
        if (gameOver == 1) {
            playerWins(values[j]);//*bab3at X aw O 7asab meen el keseb
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
            values[j] = ptr->val;//*hya hya bs akhat coloumn
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
        for (j = 0; j < i; j++) {//*rakam el row hwa rakan el element el hatetakhed fel diagonal
            ptr = ptr->next;
        }
        values[i] = ptr->val;//*kda value fiha el diagonal
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
    return (moves_done == 9 || isGameOver(arr));//moves_done = draw
}
//indicates which player wins
void playerWins(char c) {
    if (c == 'X') {
        P = 1;
    }
    else {
        P = 2;
    }
}
void Board ::perform_move (Move step){
    struct node *ptr;
    ptr =arr[step.row];
    for(step.pos=0; step.pos!=step.col; step.pos++) {
        ptr = ptr->next;
        }
    if(pl % 2 == 1 ) {//*player1
      ptr->val = 'X';
      pl++;
     }
    else {
      ptr->val = 'O';//*player2
      pl++;
    }
    //increments the draw counter
    moves_done++;//*3shan awel ema draw de tewsal le n*n byb2a draw
    return;
}
int Board::worst_case() 
/*Return the worst case for easy comparison in recursion*/
{
    if (moves_done % 2)    //For Player 1
        return 10;
    else return -10;    //For Player 2
}
bool Board::better(int value, int old_value)
/*Compare the two values which is best*/
{
    if (moves_done % 2)    //For Player 1
        return value < old_value;
    else                //For Player 2
        return value > old_value;
}
void player1info (){
    system("cls");
    cout<<"Player 1 Enter your name: \n";
    cin>>player1;//*string
    cout<<player1<< " your symbol is X\n\n\n";
}
int playing(int intel, int mode)
{
    Board game;
    Move comp_move;
    do{ // stay in loop untill all blocks are filled
         system("cls");
        game.printBoard();
        if(game.pl % 2 != 0){//pl fel awal b 1 f awel mara hayb2a b 1 w hayfdal ema yeb2a odd yeb2a player1
            cout<<"\nYour move "<<player1<<"\n";
            game.perform_move(game.input());
            system("cls");
        }
        else if(mode==1) {
            cout<<"\nYour move "<<player2<<"\n";
            game.perform_move(game.input());
            system("cls");
        }
        else {
            look_ahead(game, intel,comp_move);
            game.perform_move(comp_move);
            system("cls");
            }
        }while(!game.done());
        //checks for winner
    system("cls");
    game.printBoard();//??
    return game.Winner;
}

/////////////////////////////////////////////////////////////////////////////////////////
    int main()
    {

    }
