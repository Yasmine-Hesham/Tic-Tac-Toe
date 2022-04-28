#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<direct.h>
#include<io.h>
#include<iostream>
using namespace std;
#define Stack_entry Move 
#define maxstack 100
#define n 3
int p;
int draw=0;

class Move {//move de el move rl ha3melha ta2reebn?
public:
    int row;
    int col;
    int pos;
	Move(){//default constructor
	row=0;
	col=0;
	pos=0;
	}
};
struct node{
    char val;
    struct node *next;
    struct node *down;  //*like a 2 dimention linked list
};
class Stack {
public:
    Stack();
    bool empty()const; //this function returns if the string is empty 
    bool pop();
    bool top(Stack_entry& item); //??
    bool push(const Stack_entry& item);//??
private:
    int count;
    Stack_entry entry[maxstack]; //I guess, it's an array named entry of type Move and size 100
};
Stack::Stack()
{
    count = 0;//*count de hya el top bs bade2 men zero
}
bool Stack::push(const Stack_entry& item)//??
{
    bool outcome = success;
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
bool Stack::top(Stack_entry& item)
{
    bool outcome = success;
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
void initializeBoard(struct node *arr[], int n) {
    int i, j;
    struct node *newNode, *ptr;//??
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            newNode = new node();
            newNode->next = NULL;//*kda ana 3amlt node gdeeda w khaltha fadya w mesh betshawer 3ala 7aga y3ni ll men node wa7da
            newNode->down = NULL;
            newNode->val = ' ';
            if(j==0) {//*awel node f kol row
                arr[i] = newNode;//*bakhali awel element hya el ll el fadya kda ana khadt el kan newnode byshawer 3aleih w 2a2dar akhali nn teshwar 3ala 7aga tany
                ptr = arr[i];//*bakhalai el pointer yeshawer 3aleiha
            }
            else{//*ana kda akeni ba3mel 2d array bs awel coloumn array well tale3 menha ll 3shan akmel ba2eit el array
                ptr->next = newNode;
                ptr = ptr->next;
            }
        } 
    }
    //down pointer
    for(j=0; j<n-1; j++) {//*j-1 3shan akher row mafeesh 7aga ta7to awaslo biha
        ptr = arr[j];//*kda ana ba link kol el element el fel array b b3d
        newNode = arr[j+1];
        for(i=0; i<n; i++) {
            ptr->down = newNode;
            ptr = ptr->next;
            newNode = newNode->next;
        }
    }
}
//prints the board
void printBoard(struct node *arr[], int n) {//**ba3dein
    int i, j, k;
    struct node *ptr;
    for(k=0;k<n;k++){
   		cout<<(" ---------------");
    }
    cout<<("\n");
    for(i=0; i<n; i++) {


   		cout<<("|");
   		for(k=0;k<n;k++){
   			cout<<("               |");
   		}
   		cout<<("\n");       
   		cout<<("|");
   		for(k=0;k<n;k++){
   			cout<<("               |");
   		}
   		cout<<("\n");


        ptr = arr[i];
        for(j=1; j<=n; j++) {
            if(ptr->val == ' '){
                cout<<("|\t%d\t", i*n+j);
            }
            else{
            	if(ptr->val=='X'){
            		cout<<("|");
               		cout<<("\t%c\t", ptr->val);
           		}
           		else{
            		cout<<("|");           			
           			cout<<("\t%c\t", ptr->val);
           		}
            }
            ptr=ptr->next;
        }
        cout<<("|");
        cout<<("\n");


        cout<<("|");
   		for(k=0;k<n;k++){
   			cout<<("               |");
   		}
   		cout<<("\n");       
   		cout<<("|");
   		for(k=0;k<n;k++){
   			cout<<("               |");
   		}
   		cout<<("\n");       
        for(k=0;k<n;k++){
   			cout<<(" ---------------");
    	}
    	cout<<("\n");


    }
}
Move getposition(Move new_move){
    new_move.row = (new_move.pos-1)/n;    
    new_move.col = (new_move.pos-1)%n;
    return new_move;}
int input(struct node* arr[], int pl){
    Move step;
    cout<<("Enter a number to place your symbol there: ");
    cin>>step.pos;
    step=getposition(step)
    struct node *ptr; 
    if (!is_ok(arr, step))
    {
        cout<<("Invalid position\n");
        input(arr,pl);
    }   
    ptr =arr[step.row];
	for(step.pos=0; step.pos!=step.col; step.pos++) {
	    ptr = ptr->next;
	    }
	if(pl % 2 == 1 ) {//*player1
      ptr->val = 'X';
     }
	else {
      ptr->val = 'O';//*player2
	}
	//increments the draw counter
	draw++;//*3shan awel ema draw de tewsal le n*n byb2a draw
    return draw;
}
int isGameOver(struct node *arr[], int n){
	int gameOver,i,j;
    struct node *ptr;
    char values[n];//*array to
    //Horizontal Check
    for (i = 0; i < n; i++)
    {
    	gameOver = 1;
    	ptr = arr[i];
    	for(j=0; j<n; j++) {//* akhadt el values beta3t awel row kolo w 7atetha f array lwa7do
    		values[j] = ptr->val;
    		ptr= ptr->next;
	   	}
        //checing if row is equal
    	for(j=0; j<n-1; j++){
    		if(values[j]==' ' || values[j+1] == ' '){//*lw fi ay wa7da fadya yeb2a maksebesh
    			gameOver = 0;
    			break;
    		}
    		else if(values[j] != values[j+1]){//*aw lw fi ay wa7da mesh zy el b3dha matnfa3sh
    			gameOver = 0;
    			break;
    		}
    	}
    	if(gameOver == 1){
    		playerWins(values[j]);//*bab3at X aw O 7asab meen el keseb
    		return gameOver;
		}    		    	
    }
    //Vertical Check
    for(i=0; i<n; i++){
        ptr = arr[0];
        for(j=0; j<i; j++) {
            ptr = ptr->next;
        }
        gameOver = 1;
        for(j=0; j<n; j++){
            values[j] = ptr->val;//*hya hya bs akhat coloumn
            ptr = ptr->down;
        }
        //checking if column is equal
        for(j=0; j<n-1; j++) {
            if(values[j]==' ' || values[j+1] == ' '){
    			gameOver = 0;
    			break;
    		}
            if(values[j] != values[j+1]) {
                gameOver = 0;
                break;
            }
        }
        if(gameOver == 1){
        	playerWins(values[j]);
    		return gameOver;
		}
    }
    //leading Diagonal
    for(i=0; i<n; i++){
        gameOver = 1;
        ptr = arr[i];
        for(j=0; j<i; j++){//*rakam el row hwa rakan el element el hatetakhed fel diagonal
            ptr = ptr->next;
        }
        values[i] = ptr->val;//*kda value fiha el diagonal
        //checking if leading diagonal is equal
        for(j=0; j<n-1; j++) {
            if(values[j]==' ' || values[j+1] == ' '){
    			gameOver = 0;
    			break;
    		}
            if(values[j] != values[j+1]) {
                gameOver = 0;
                break;
            }
        }
        if(gameOver == 1){
        	playerWins(values[j]);
    		return gameOver;
		}
    }
    //other Diagonal
    for(i=n-1; i>=0; i--){//bada2t men akher row
        gameOver = 1;
        ptr = arr[n-i-1];
        for(j=0; j<i; j++){
            ptr = ptr->next;
        }
        values[n-i-1] = ptr->val;
        //checking if non-leading diagonal is equal
        for(j=0; j<n-1; j++) {
            if(values[j]==' ' || values[j+1] == ' '){
    			gameOver = 0;
    			break;
    		}
            if(values[j] != values[j+1]) {
                gameOver = 0;
                break;
            }
        }
        if(gameOver == 1){
        	playerWins(values[j]);
    		return gameOver;
		}
    }
    return gameOver;
}
bool done()const
/**Judging whether the game is over**/
{
    return (draw == 9 || isGameOver(struct node *arr[], int n));//moves_done = draw
}
//indicates which player wins
void playerWins(char c){
	if(c=='X'){
		P=1;
	}
	else{
		P=2;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
int legal_moves(Stack& moves, struct node* arr[])const //stack named moves .. by refrence 
/**Store all feasible steps in the incoming stack**/
{
    int count = 0;
    while (!moves.empty()) //while the stack "moves" is not empty 
        moves.pop(); //empty it first
    for (int i = 1; i < 10; i++)
        {
            Move can_play;
            can_play.pos=i;
            can_play=getposition(can_play);
            if(is_ok(arr[],can_play))//?? 
               { moves.push(can_play); //and it's pushed in the stack moves
                count++;}
        }
    return count;
}
bool is_ok(struct *arr[], move step)
/**Judging whether this step is feasible**/
{
    if(step.pos<1 || step.pos>n*n){
        return false;
    struct node *ptr; 
    ptr =arr[step.row];
	for(step.pos=0; step.pos!=step.col; step.pos++) {
	    ptr = ptr->next;
	    }
	if(ptr->val != ' ') 
	    return false;
    else return true;
}
int Board::evaluate()const
/**Return to a number, which reflects the winning or losing and how many steps have been taken.
   For calculating the final result of each feasible step in the following recursive function**/
{
    int winner = the_winner();
    if (winner == 1)
        return 10 - draw;//If the winner is 1, the return value is positive. The larger the number, the better for player 1. // I don't get why 10?

    else if (winner == 2)
        return draw - 10;//Winner is 2, then the return value is negative. The smaller the number, the better for player 2.
    else
        return 0;//It ends in a draw
}
int evaluate()const
/**Return to a number, which reflects the winning or losing and how many steps have been taken.
   For calculating the final result of each feasible step in the following recursive function**/
{
    int winner = the_winner();// int winner =P
    if (winner == 1)
        return 10 - draw;//If the winner is 1, the return value is positive. The larger the number, the better for player 1. // I don't get why 10?

    else if (winner == 2)// winner==2 && ch=1
        return draw - 10;//Winner is 2, then the return value is negative. The smaller the number, the better for player 2.
    else
        return 0;//It ends in a draw
}
int Board::worst_case()const //no idea
/**Return to the worst case for easy comparison in recursion**/
{
    if (draw % 2)	//For Player 2
        return 10;
    else return -10;	//For Player 1
}

bool Board::better(int value, int old_value)const
/**Compare the two values which is the best**/
{
    if (draw % 2)	//For Player 2
        return value < old_value;
    else				//For Player 1
        return value > old_value;
}
int look_ahead(const Board& game, int depth, Move& recommended) 
{
    if (game.done() || depth == 0) //depth will be the iq of the computer but it must be larger than 1
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
            moves.top(try_it); //peak the last move added 
            Board new_game = game;  //a new stack to put "game" in 
            new_game.play(try_it); //perform "X" or "O" or blank
            value = look_ahead(new_game, depth - 1, reply); //recursive 
            if (game.better(value, best_value)) //if value is better than best value 
            {
                best_value = value; //make value the new bet value 
                recommended = try_it; //add the "try it " move in the object "recommended" of type move
            }
            moves.pop(); //I think it means "next " Elly b3dooooo
        }
        return best_value; //in the end it'll come back with the best decision 
    }
}
