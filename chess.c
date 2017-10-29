#include <stdio.h>
#include <stdlib.h>
#define BOARD_SIZE 8
void initBoard(char *board);
void getPosition(char *col, int *row);
int isValidCell(char col, int row);
void printBoard(char *board);
int isPieceMovable(char *board, char sc, int sr, char tc, int tr);
int isInCheck(char* board);
int makeMove(char *board, char sc, int sr, char tc, int tr);
int isRookMovable(char *board , char sourceCol, int sourceRow, char targetCol, int targetRow);
int isKnightMovable(char *board,char sourceCol,int sourceRow,char targetCol,int targetRow);
int isBishopMovable(char *board,char sourceCol,int sourceRow,char targetCol,int targetRow);
int isKingMovable(char *board,char sourceCol,int sourceRow,char targetCol,int targetRow);
int isQueenMovable(char *board,char sourceCol,int sourceRow,char targetCol,int targetRow);
int isPawnMovable(char *board,char sourceCol,int sourceRow,char targetCol,int targetRow);
int colRowToNumberConverter(char col, int row);
int colourCheck(char *board, int source);
int numberToRowConverter(int num);
char numberToColConverter(int num);
int getPlayer(char *board, char col, int row);
int isWhite(int input);
int isBlack(int input);
int main(){
    char board [BOARD_SIZE*BOARD_SIZE], empty;
    int player = 1; 
    char sc,tc; 
    int sr,tr; 
    int moveStatus = 0;
    int checkStatus = 0;
    char currPlayer;

    initBoard(board);
	do {
        printBoard(board);
        printf("%s player move > ", player ? "White" : "Black");
        getPosition(&sc,&sr);
        scanf("%c", &empty);
        getPosition(&tc,&tr);
        scanf("%c", &empty);
        currPlayer = getPlayer(board,sc,sr);
	if(!isValidCell(sc,sr)){
            printf("Source position is invalid\n");
            continue;
        }
        if(!isValidCell(tc,tr)){
            printf("Target position is invalid\n");
            continue;
        }
	//if it is black's turn but you move white piece.
        if((isBlack(currPlayer) && player) || (isWhite(currPlayer) && !player)) {
        	printf("Illegal piece. \n");
                 continue;
        }
	moveStatus = makeMove(board,sc,sr,tc,tr);
        switch(moveStatus){
            case 0:
                printf("Invalid move!\n");
                break;
            case 1:
                printf("Your king is in check!\n");
                ++checkStatus;
                break;
            case 3:
                printf("Check!\n");
            case 2:
                player = !player;
                checkStatus = 0;
                break;
        }
    } 
	while(checkStatus < 2);
    		printf("%s player WINS!\n", player ? "Black" : "White");
    return 0;
}														 
void initBoard(char *board)
{
	int i;	
	board[0]='r';
	board[1]='n';
	board[2]='b';
	board[3]='q';
	board[4]='k';
	board[5]='b';
	board[6]='n';
	board[7]='r';
	for (i=8; i<=15; ++i){
		board[i]='p';
	}

	for(i=16; i<=47; i++){
		board[i]=' ';
	}
	for (i=48; i<=55; ++i){
		board[i]='P';
	}
	board[56]='R';
	board[57]='N';
	board[58]='B';
	board[59]='Q';
	board[60]='K';
	board[61]='B';
	board[62]='N';
	board[63]='R';
}
void getPosition(char *col, int *row){
	scanf("%c%d", col, row);
}
int isValidCell(char col, int row){
	if (((col >= 'a' && col <= 'h') || (col >= 'A' && col <= 'H')) && row >= 1 && row <= 8){
		return 1;
	}
	else{
		return 0;
	}
}												
void printBoard(char *board){
	int i = 0, count = 7, line;
	printf("  a b c d e f g h\n");
	printf("  - - - - - - - -\n");
	for (line = 8; line >= 1; --line){
		printf("%d|", line);
		while (i <= count){
			printf("%c", board[i]);
			if(i%8 != 7)
				printf(" ");
			else
				printf("|\n");
			i++;
		}
		count+=8;
	}
	printf("  - - - - - - - -\n");
}
int isPieceMovable(char *board, char sc, int sr, char tc, int tr){
	if (sc >= 'A' && sc <= 'H'){
		sc += 32;
	}
	if (tc >= 'A' && tc <= 'H'){
		tc += 32;
	}
	if((sc == tc) && (sr == tr)){
		return 0;
	}
	if (isValidCell(sc,sr) == 0 || isValidCell(tc,tr) == 0){
		return 0;
	}
	else{
		switch(board[colRowToNumberConverter(sc,sr)]){
			case 'p':	
			case 'P':
				return isPawnMovable(board,sc,sr,tc,tr);
			case 'r':
			case 'R':
				return isRookMovable(board,sc,sr,tc,tr);
			case 'n':
			case 'N': 
				return isKnightMovable(board,sc,sr,tc,tr);
			case 'b':	
			case 'B':
				return isBishopMovable(board,sc,sr,tc,tr);
			case 'q':
			case 'Q':
				return isQueenMovable(board,sc,sr,tc,tr);
			case 'k':
			case 'K': 
				return isKingMovable(board,sc,sr,tc,tr);
			default: return 0;
		}
		return 0;
	}
}
int isRookMovable(char *board , char sourceCol, int sourceRow, char targetCol, int targetRow){
	int source=colRowToNumberConverter(sourceCol,sourceRow),
		target=colRowToNumberConverter(targetCol,targetRow),
		i=source;
	if (sourceRow==targetRow){	//if the rook is moving in the same row
		if (target>source){
			i+=1;		//moving right
			if (i==target){
				if (colourCheck(board,target)==-1){
					return 1;
				}
				else{
					if (colourCheck(board,source)==colourCheck(board,target)){
						return 0;
					}
					else{
						return 1;
					}
				}
			}
			else{
				while (i<target){
					if(board[i]!=' '){
						return 0;
					}
					i+=1;
					if(i==target){
						if (colourCheck(board,target)==-1){
							return 1;
						}
						else{
							if (colourCheck(board,source)==colourCheck(board,target)){
								return 0;
							}
							else {
								return 1;
							}
						}
					}
				}
			}
		}
		else{
			i-=1;// moving left
			if (i==target){
				if (colourCheck(board,target)==-1){
					return 1;
				}
				else{
					if (colourCheck(board,source)==colourCheck(board,target)){
						return 0;
					}
					else{
						return 1;
					}
				}
			}
			else{
				while (i>target){
					if(board[i]!=' '){
						return 0;
					}
					i-=1;
					if(i==target){
						if (colourCheck(board,target)==-1){
							return 1;
						}
						else{
							if (colourCheck(board,source)==colourCheck(board,target)){
								return 0;
							}
							else{
								return 1;
							}
						}
					}
				}
			}
		}
	}
	else if ((target-source)%8==0){		//if the rook is moving in the same col.
		if (target>source){
			i+=8;
			if (i==target){
				if (colourCheck(board,target)==-1){
					return 1;
				}
				else{
					if (colourCheck(board,source)==colourCheck(board,target)){
						return 0;
					}
					else{
						return 1;
					}
				}
			}
			else{
				while (i<target){
					if(board[i]!=' '){
						return 0;
					}
					i+=8;
					if(i==target){
						if (colourCheck(board,target)==-1){
							return 1;
						}
						else{
							if (colourCheck(board,source)==colourCheck(board,target)){
								return 0;
							}
							else{
								return 1;
							}
						}
					}
				}
			}
		}
		else{
			i-=8;
			if (i==target){
				if (colourCheck(board,target)==-1){
					return 1;
				}
				else{
					if (colourCheck(board,source)==colourCheck(board,target)){
						return 0;
					}
					else {
						return 1;
					}
				}
			}
			else{
				while (i>target){
					if(board[i]!=' '){
						return 0;
					}
					i-=8;
					if(i==target){
						if (colourCheck(board,target)==-1){
							return 1;
						}
						else{
							if (colourCheck(board,source)==colourCheck(board,target)){
								return 0;
							}
							else {
								return 1;
							}
						}
					}
				}
			}
		}
	}
	else{
		return 0;
	}

	return -11;
}
int isKnightMovable(char *board, char sourceCol, int sourceRow, char targetCol, int targetRow){
	int source=colRowToNumberConverter(sourceCol,sourceRow),
		target=colRowToNumberConverter(targetCol,targetRow);
	if (sourceRow==targetRow || abs(sourceCol-targetCol) > 2){
		return 0;
	}
	else if (abs(target-source)==6 || abs(target-source)==10 || 
			 abs(target-source)==15 || abs(target-source)==17){
		if (colourCheck(board,target)==-1){
			return 1;
		}
		else{
			if (colourCheck(board,source)==colourCheck(board,target)){
				return 0;
			}
			else{
				return 1;
			}
		}
	}
	else{
		return 0;
	}
}
int isBishopMovable(char *board,char sourceCol,int sourceRow,char targetCol,int targetRow){
	int source=colRowToNumberConverter(sourceCol,sourceRow),
		target=colRowToNumberConverter(targetCol,targetRow),
		i=source;
	if (sourceRow==targetRow){
		return 0;
	}
	else if (abs(target-source) == (abs(targetRow-sourceRow)*7)){    //downward left and upward right
		if (target>source){
			i+=7;
			if (i==target){
				if (colourCheck(board,target)==-1){
					return 1;
				}
				else{
					if (colourCheck(board,source)==colourCheck(board,target)){ //
						return 0;
					}
					else{
						return 1;
					}
				}
			}
			else{
				while (i<target){
					if(board[i]!=' '){
						return 0;
					}
					i+=7;
					if(i==target){
						if (colourCheck(board,target)==-1){	//if there is nothing in that position
							return 1;
						}
						else{
							if (colourCheck(board,source)==colourCheck(board,target)){
								return 0;
							}
							else{
								return 1;
							}
						}
					}
				}
			}
		}
		else{
			i-=7;
			if (i==target){
				if (colourCheck(board,target)==-1){
					return 1;
				}
				else{
					if (colourCheck(board,source)==colourCheck(board,target)){
						return 0;
					}
					else{
						return 1;
					}
				}
			}
			else{
				while (i>target){
					if(board[i]!=' '){
						return 0;
					}
					i-=7;
					if(i==target){
						if (colourCheck(board,target)==-1){
							return 1;
						}
						else{
							if (colourCheck(board,source)==colourCheck(board,target)){
								return 0;
							}
							else{
								return 1;
							}
						}
					}
				}
			}
		}
	}
	else if (abs(target-source) == (abs(targetRow-sourceRow)*9)){	// downward right and upward left
		if (target>source){
			i+=9;
			if (i==target){
				if (colourCheck(board,target)==-1){
					return 1;
				}
				else{
					if (colourCheck(board,source)==colourCheck(board,target)){
						return 0;
					}
					else{
						return 1;
					}
				}
			}
			else{
				while (i<target){
					if(board[i]!=' '){
						return 0;
					}
					i+=9;
					if(i==target){
						if (colourCheck(board,target)==-1){
							return 1;
						}
						else{
							if (colourCheck(board,source)==colourCheck(board,target)){
								return 0;
							}
							else{
								return 1;
							}
						}
					}
				}
			}
		}
		else{
			i-=9;
			if (i==target){
				if (colourCheck(board,target)==-1){
					return 1;
				}
				else{
					if (colourCheck(board,source)==colourCheck(board,target)){
						return 0;
					}
					else{
						return 1;
					}
				}
			}
			else{
				while (i>target){
					if(board[i]!=' '){
						return 0;
					}
					i-=9;
					if(i==target){
						if (colourCheck(board,target)==-1){
							return 1;
						}
						else{
							if (colourCheck(board,source)==colourCheck(board,target)){
								return 0;
							}
							else{
								return 1;
							}
						}
					}
				}
			}
		}
	}
	else{
		return 0;
	}
	return -11;
}
int isKingMovable(char *board,char sourceCol,int sourceRow,char targetCol,int targetRow){
	int source=colRowToNumberConverter(sourceCol,sourceRow),
		target=colRowToNumberConverter(targetCol,targetRow);
	if(sourceRow==targetRow && abs(target-source)==7){
		return 0;
	}
	else if ((abs(target-source)==1 || abs(target-source)==7 || 
			 abs(target-source)==8 || abs(target-source)==9) && 
			 abs(sourceCol-targetCol)<=1){
		if (colourCheck(board,target)==-1){
			return 1;
		}
		else{
			if (colourCheck(board,source)==colourCheck(board,target)){
				return 0;
			}
			else{
				return 1;
			}
		}
	}
	else{
		return 0;
	}
}
int isQueenMovable(char *board,char sourceCol,int sourceRow,char targetCol,int targetRow){
	if (isRookMovable(board,sourceCol,sourceRow,targetCol,targetRow)==1 ||
		isBishopMovable(board,sourceCol,sourceRow,targetCol,targetRow)==1){
		return 1;
	}
	else{
		return 0;
	}
}
int isPawnMovable(char *board,char sourceCol,int sourceRow,char targetCol,int targetRow){
	int source=colRowToNumberConverter(sourceCol,sourceRow),
		target=colRowToNumberConverter(targetCol,targetRow);
	if (sourceRow==targetRow){
		return 0;
	}
	else if (colourCheck(board,source)==0) {		// for black pawn
		if (source>target){
			return 0;
		}
		else if (target-source==8){
			if (colourCheck(board,target)==-1){
				return 1;
			}
			else{
				return 0;
			}
		}
		
		else if ((target-source==9) && abs(sourceRow-targetRow)==1){
			if (colourCheck(board,source)==colourCheck(board,target)){
				return 0;
			}
			else{
				return 1;	
			}
		}
		else if ((target-source==7) && abs(sourceRow-targetRow)==1){
			if (colourCheck(board,source)==colourCheck(board,target)){
				return 0;
			}
			else{
				return 1;	
			}
		}	
		else
			return 0;
	}
	else if (colourCheck(board,source)==1){	 //for white pawn
		if (target>source){
			return 0;
		}
		else if (source-target==8){
			if (colourCheck(board,target)==-1){
				return 1;
			}
			else{
				return 0;
			}
		}
		else if ((source-target==9) && abs(sourceRow-targetRow)==1){
			if (colourCheck(board,source)==colourCheck(board,target)){
				return 0;
			}
			else{
				return 1;	
			}
		}
		else if ((source-target==7) && abs(sourceRow-targetRow)==1){
			if (colourCheck(board,source)==colourCheck(board,target)){
				return 0;
			}
			else{
				return 1;	
			}
		}
		else
			return 0;
	}
	else{
		return 0;
	}
	return -12;
}													
int colRowToNumberConverter(char col, int row){
	int colNumber;
	switch(col){
		case 'a':
		case 'A': 
			colNumber=1;
			break;
		case 'b':
		case 'B': 
			colNumber=2;
			break;
		case 'c': 
		case 'C':
			colNumber=3;
			break;
		case 'd': 
		case 'D':
			colNumber=4;
			break;
		case 'e': 
		case 'E':
			colNumber=5;
			break;
		case 'f': 
		case 'F':
			colNumber=6;
			break;
		case 'g': 
		case 'G':
			colNumber=7;
			break;
		case 'h': 
		case 'H':
			colNumber=8;
			break;
	}
	
	return (((9-row)-1)*8+colNumber)-1;
}
int colourCheck(char *board, int source){
	switch(board[source]){
		case 'r':	
		case 'n':
		case 'b':
		case 'q':
		case 'k':
		case 'p': 
			return 0;
		case 'R':	
		case 'N':
		case 'B':
		case 'Q':
		case 'K':
		case 'P': 
			return 1;
		default: return -1;
	}
}
int numberToRowConverter(int num){
	return 9-((num+8)/8);//gives you the position of the piece in terms of row
}
char numberToColConverter(int num){
	switch(num%8){	//gives you the position of the piece in terms of col
		case 0: 
			return 'a';
		case 1: 
			return 'b';
		case 2:
			return 'c';
		case 3:
			return 'd';
		case 4:
			return 'e';
		case 5:
			return 'f';
		case 6:
			return 'g';
		case 7:
			return 'h';
	}
	return ' ';
}										
int getPlayer(char *board, char col, int row){
	int source = colRowToNumberConverter(col,row);
	int colour;
	colour = colourCheck(board,source);
	if(colour == 1)
		return 1;
	else 
		return 0;
}
int isInCheck(char* board){
	int i;	
	char wsc, bsc, isc;

	int wsr = 0,bsr = 0, isr;		
	for (i = 0; i < 64; ++i){
		if(board[i] == 'K'){
			wsc = numberToColConverter(i);
			wsr = numberToRowConverter(i);
		}
		if(board[i] == 'k'){
			bsc = numberToColConverter(i);
			bsr = numberToRowConverter(i);
		}
	}
	for (i = 0; i < 64; ++i){
		isc = numberToColConverter(i);
		isc = numberToColConverter(i);
		isr = numberToRowConverter(i);
		switch(board[i]){
			case 'P':		// sourceRC targetRC
				if(isPawnMovable(board,isc,isr,bsc,bsr) == 1 && bsr != 0){
					return 1;
				}
				break;
			case 'R':
				if(isRookMovable(board,isc,isr,bsc,bsr) == 1 && bsr != 0){
					return 1;
				}
				break;
			case 'N': 
				if(isKnightMovable(board,isc,isr,bsc,bsr) == 1 && bsr != 0){
					return 1;
				}
				break;
			case 'B':
				if(isBishopMovable(board,isc,isr,bsc,bsr) == 1 && bsr != 0){
					return 1;
				}
				break;
			case 'Q':
				if(isQueenMovable(board,isc,isr,bsc,bsr) == 1 && bsr != 0){
					return 1;
				}
				break;
			case 'K':
				if(isKingMovable(board,isc,isr,bsc,bsr) == 1 && bsr != 0){
					return 1;
				}
			case 'p':
				if(isPawnMovable(board,isc,isr,wsc,wsr) == 1 && wsr != 0){
					return 2;
				}
				break;
			case 'r':
				if(isRookMovable(board,isc,isr,wsc,wsr) == 1 && wsr != 0){
					return 2;
				}
				break;
			case 'n': 
				if(isKnightMovable(board,isc,isr,wsc,wsr) == 1 && wsr != 0){
					return 2;
				}
				break;
			case 'b':
				if(isBishopMovable(board,isc,isr,wsc,wsr) == 1 && wsr != 0){
					return 2;
				}
				break;
			case 'q':
				if(isQueenMovable(board,isc,isr,wsc,wsr) == 1 && wsr != 0){
					return 2;
				}
				break;
			case 'k':
				if(isKingMovable(board,isc,isr,bsc,bsr) == 1 && bsr != 0){
					return 2;
				}
		}
	}
	return 0;
}
int makeMove(char *board, char sc, int sr, char tc, int tr){
	int source = colRowToNumberConverter(sc,sr),
		target = colRowToNumberConverter(tc,tr);
	char tmpSource, tmpTarget; 
	if(isPieceMovable(board,sc,sr,tc,tr) == 0){
		return 0;
	}
	if(isPieceMovable(board,sc,sr,tc,tr) == 1){
		tmpSource = board[source];
		tmpTarget = board[target];
		board[target] = tmpSource;
		board[source] = ' ';	//the piece get moved from source to target and the source position attains null value
		if((isInCheck(board) == 1 && colourCheck(board, target) == 1) || 
			(isInCheck(board) == 2 && colourCheck(board, target) == 0)){  //it gives check 1,1 ->black king; check 2,0 ->white king	
			return 3;
		}
		if((isInCheck(board) == 1 && colourCheck(board, target) == 0) || 
			(isInCheck(board) == 2 && colourCheck(board, target) == 1)){  //it gives warning 
			board[target] = tmpTarget;
			board[source] = tmpSource;
			return 1;
		}
		return 2; 
	}
	return -12;
}
int isWhite(int input){
	if(input == 1)
		return 1;
	else 
		return 0;
}
int isBlack(int input){
	if(input == 0)
		return 1;
	else 
		return 0;
}
