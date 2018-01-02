#include <stdio.h>
#include <stdlib.h>

void display( void ); // refresh the board
void BOARD_init( void ); // generate a new board
void block_init( int piece, int rotation ); // generate a new block
void block_fall( void ); // make the block fall
void block_turn( void );
int can_fall( void ); // check if the block can fall

char BOARD[ 21 ][ 12 ] = {0}; // 20x10 without borders
char PIECES[ 7 ][ 4 ][ 4 ][ 4 ] = // 7 kinds, 4 rotations, stored in 4x4
{
	{ // O
		{
			{ 0, 0, 0, 0 },
			{ 0, 1, 2, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 1, 2, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 1, 2, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 1, 2, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 0, 0 }
		}
	}, // end O
	{ // I
		{
			{ 0, 0, 0, 0 },
			{ 1, 1, 2, 1 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 1, 0 },
			{ 0, 0, 2, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 1, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 1, 1, 2, 1 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 1, 0 },
			{ 0, 0, 2, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 1, 0 }
		}
	}, // end I
	{ // S
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 2, 1 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 1, 0 },
			{ 0, 0, 2, 1 },
			{ 0, 0, 0, 1 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 2, 1 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 1, 0 },
			{ 0, 0, 2, 1 },
			{ 0, 0, 0, 1 },
			{ 0, 0, 0, 0 }
		}
	}, // end S
	{ // Z
		{
			{ 0, 0, 0, 0 },
			{ 0, 1, 2, 0 },
			{ 0, 0, 1, 1 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 1 },
			{ 0, 0, 2, 1 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 1, 2, 0 },
			{ 0, 0, 1, 1 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 1 },
			{ 0, 0, 2, 1 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 0, 0 }
		}
	}, // end Z
	{ // L
		{
			{ 0, 0, 0, 0 },
			{ 0, 1, 2, 1 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 1, 0 },
			{ 0, 0, 2, 0 },
			{ 0, 0, 1, 1 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 1 },
			{ 0, 1, 2, 1 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 1, 1, 0 },
			{ 0, 0, 2, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 0, 0 }
		}
	}, // end L
	{ // J
		{
			{ 0, 0, 0, 0 },
			{ 0, 1, 2, 1 },
			{ 0, 0, 0, 1 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 1, 1 },
			{ 0, 0, 2, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 1, 0, 0 },
			{ 0, 1, 2, 1 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 1, 0 },
			{ 0, 0, 2, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 0, 0 }
		}
	}, // end J
	{ // T
		{
			{ 0, 0, 0, 0 },
			{ 0, 1, 2, 1 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 1, 0 },
			{ 0, 0, 2, 1 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 1, 0 },
			{ 0, 1, 2, 1 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 1, 0 },
			{ 0, 1, 2, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 0, 0 }
		}
	} // end T
}; // end PIECES

void display( void )
{
	int i, j; // counter
	system( "CLS" ); // refresh the screen
	printf( "\n" );
	for ( i = 0; i < 20; i++ ) {
		printf( "�@�@�@" );
		for ( j = 0; j < 12; j++ ) {
			if ( j == 0 ) printf( "�x" ); // print left border
			else if ( j == 11 ) {
				printf( "�x" ); // print right border
				if ( i == 1 ) printf( "�@�@�Xù����� ver1.00 by ���a�~"  );
				else if ( i == 4 ) printf( "�@�@Bug1. ���ѨM�w�ɸ��U�P���Կ�J���Ĭ�" );
				else if ( i == 5 ) printf( "�@�@      �����z�L�����J�ϵ{���~�����" );
				else if ( i == 7 ) printf( "�@�@Bug2. ���ѨM��J�r�ꪺ���ݦh�l��\"\\n\"" );
				else if ( i == 8 ) printf( "�@�@      ��������J���|�Ϥ�����U�@��" );
				else if ( i == 10 ) printf( "�@�@Bug3. ���ѨM��� getche() ����J�^��" );
				else if ( i == 11 ) printf( "�@�@      �ɭP�����J�|�X�{�b�e�����@��" );
				else if ( i == 13 ) printf( "�@�@�q�ާ@�����r���������ܭ^���J" );
				else if ( i == 15 ) printf( "�@�@Enter: �U���@��@�@S: �U�����" );
				else if ( i == 17 ) printf( "�@�@A: �����@�@�@�@�@�@D: �k��" );
				else if ( i == 19 ) printf( "�@�@W: ����" );
				printf( "\n" );
			} else {
				if ( BOARD[ i ][ j ] == 0 ) printf( "�@" );
				else if ( BOARD[ i ][ j ] == 1 || BOARD[ i ][ j ] == 2 ) printf( "��" );
				else if ( BOARD[ i ][ j ] == 3 ) printf( "��" );
			} // end else
		} // end for
	} // end for
	printf( "�@�@�@�|�w�w�w�w�w�w�w�w�w�w�}" ); // print bottom border
}

void BOARD_init( void )
{
	int i, j;
	for ( i = 0; i < 21; i++ )
		for ( j = 0; j < 12; j++ ) {
			if ( i == 20 ) BOARD[ i ][ j ] = 4;
			else if ( j == 0 || j == 11 ) BOARD[ i ][ j ] = 4;
			else BOARD[ i ][ j ] = 0;
		}
	display();
}

void block_init( int piece, int rotation )
{
	int i, j;
	for ( i = 0; i < 4; i++)
		for ( j = 0; j < 4; j++)
			if ( BOARD[ i ][ j + 3 ] == 0 )
				BOARD[ i ][ j + 3 ] = PIECES[ piece ][ rotation ][ i ][ j ];
	display();
}

int can_fall( void )
{
	int i, j;
	for ( i = 19; i >= 0 ; i-- ) { 
		for ( j = 1; j < 11; j++ ) {
			if ( BOARD[ i ][ j ] >= 1 && BOARD[ i ][ j ] <= 2  && BOARD[ i + 1 ][ j ] > 2 ) return 0;
		}
	}
	return 1;
}

void block_fall( void )
{
	int i, j;
	for ( i = 19; i >= 0 ; i-- ) { 
		for ( j = 1; j < 11; j++ ) {
			if ( BOARD[ i ][ j ] == 1 || BOARD[ i ][ j ] == 2 ) {
				BOARD[ i + 1 ][ j ] = BOARD[ i ][ j ]; 	// replace the next line with current line
				BOARD[ i ][ j ] = 0; // clean the current line
			}
		}
	} 
	display();
}

void block_turn( void )
{
	int i, j;
	for ( i = 19; i >= 0 ; i-- ) { 
		for ( j = 1; j < 11; j++ ) {
			if ( BOARD[ i ][ j ] == 1 || BOARD[ i ][ j ] == 2 ) BOARD[ i ][ j ] = 3;
		} 
	}
	display();
}
