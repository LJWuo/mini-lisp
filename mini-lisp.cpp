# include <iostream>
# include <stdlib.h>
# include <cstring>
# include <vector>
# include <iomanip>
using namespace std ;

enum TokenType 
{
  NUM,
  ADD,
  SUB,
  MUL,
  MOD, 
  DIV,
  LP,
  RP,
  EQ,
  GR,
  SM,
  ID,
  AND,
  OR,
  NOT,
  T,
  F,
  PN,
  PB,
  IF,
  ERROR
  
};  

struct A {
  char temp[100];
  TokenType type  ;
};


class Scanner {
  public : 

  Scanner() ;

  void GetNextChar( char &ch ) {

    ch = cin.get() ;


  } // GetNextChar()

  void GetNWSChar( char &ch ) {

    GetNextChar( ch ) ; 
    while ( ch == ' ' || ch == '\t' || ch == '\n' ) {
      GetNextChar( ch ) ;
    } // while 

  } // GetNWSChar()
  
  void IDToken( char temp[100], bool &f ) {
    char ch ;
    int i = 1 ; 
    ch = cin.peek() ;
    while ( IsID( ch ) || IsNUM( ch ) || ch == '-' ) {
		
      GetNextChar( ch ) ;
      temp[i] = ch ;
      ch = cin.peek() ;
      i++ ;
    } // while 
        
    
    if ( ch != '(' && ch != ')' && ch != ' ' && ch != '\n' ) {
      f = true ;
      while ( ch != ' ' && ch != '\n' && ch != '.' && ch != '(' && ch != ')' ) {
        GetNextChar( ch ) ;
        temp[i] = ch ;
	    ch = cin.peek() ;
        i++ ;
      } // while 	
	} //  if
    
  } // IDToken()   
  

  void NumToken( char temp[100] ) {
    char ch ;
    int i = 1 ;
    int p = 0 ;
    ch = cin.peek() ;
    
    while ( IsNUM( ch ) ) {
      GetNextChar( ch ) ;

      temp[i] = ch ;
      ch = cin.peek() ;
      
      i++ ;
    } // while
  } // NumToken() 
  
    
  void CleanChar( char temp[100] ) {
    int i = 0 ;
    while ( i < 100 ) {
      temp[i] = '\0' ;  
      i++ ;
    } // while
  } // CleanChar()
  
  
  bool IsID( char ch ) { 
    if ( ch <= 122 && ch >= 97 ) {
      return true ;  
    } // else if 
    else { 
      return false ;
      
    } // else 
  } // IsID()
  
  bool IsNUM( char ch ) { 
    char c ;
    c = cin.peek() ;
    if ( ch < 58 && ch > 47 ) {
      return true ;
    } // if
	else if ( ch == '-' && c < 58 && c > 47 ) {
	  return true ;	
	} 
    else {
      return false ;
    } // else 
  } // IsNUM()
  
  bool IsSIGN( char ch ) {
    if ( ch == '=' || ch == '+' || ch == '*' || ch == '/' 
         || ch == '(' || ch == ')' || ch == '>'|| ch == '<' ) {
      return true ;  
    } // if 
    else if ( ch == '-' ) {
      char c ;
	  c = cin.peek() ;
	  if ( c == ' ' ) return true ;
	  else  return false ;
	}
    else {
      return false ;
    } // else 
  } // IsSIGN()
  
  void GetToken( char temp[100], TokenType &type ) {
    int i = 0 ;
    // GetNWSChar( temp[0] ) ;


    GetNWSChar( temp[0] ) ;


    if ( IsSIGN( temp[0] ) ) {  
      if ( temp[0] == '+' ) type = ADD ;
      else if ( temp[0] == '-' ) type = SUB ;
      else if ( temp[0] == '*' ) type = MUL ;
      else if ( temp[0] == '/' ) type = DIV ;
      else if ( temp[0] == '(' ) type = LP ;
      else if ( temp[0] == ')' ) type = RP ;
      else if ( temp[0] == '>' ) type = GR ;
      else if ( temp[0] == '<' ) type = SM ;
      else if ( temp[0] == '=' ) type = EQ ;
    } // if 
    else if ( IsNUM( temp[0] ) ) {
      NumToken( temp ) ;
      type = NUM ;
    } // if    
	else if ( IsID( temp[0] ) ) {
	  bool f = false ;
	  IDToken( temp, f ) ;
	  if ( f == true ) type = ERROR ;
      else type = ID ;
      
      if ( temp[0] == 'a' && temp[1] == 'n' && temp[2] == 'd' && temp[3] == '\0' ) type = AND ;
      else if ( temp[0] == 'n' && temp[1] == 'o' && temp[2] == 't' && temp[3] == '\0' ) type = NOT ;
      else if ( temp[0] == 'm' && temp[1] == 'o' && temp[2] == 'd' && temp[3] == '\0' ) type = MOD ;
      else if ( temp[0] == 'o' && temp[1] == 'r' && temp[2] == '\0' ) type = OR ;
	} // else if
	else if ( temp[0] = '#' ) {
	  char a ;
	  a = cin.peek();  
	  if ( a == 't' ) {
	  	a = cin.get();
	  	temp[1] = a ;
	  	type = T ;
	  }
	  else if ( a == 'f' ) {
	  	a = cin.get();
	  	temp[1] = a ;
	  	type = F ;
	  }
	  else type = ERROR ;
	}
    else {
      type = ERROR ;
	}
	
	
  } // GetToken()
  

}; // class Scanner

Scanner::Scanner() {

} // Scanner::Scanner()


class Parser {
  public:
  Scanner mscanner ;
  vector<A> mTokenGroup ;
  TokenType mtokentype ;
  int mPRn ;
  char mtokenvalue[100] ;

  
  void PrintTG() {
    int i = 0 ;
    while ( i < mTokenGroup.size() ) {
      if ( mTokenGroup[i].type == 0 ) {
	  cout << "NUM " ;
      cout << mTokenGroup[i].temp << endl ;
      } // if
      else if ( mTokenGroup[i].type == 1 ) cout << "PLUS" << endl ;
      else if ( mTokenGroup[i].type == 2 ) cout << "MINUS" << endl ;
      else if ( mTokenGroup[i].type == 3 ) cout << "MUL" << endl ;
      else if ( mTokenGroup[i].type == 4 ) cout << "MOD" << endl ;
      else if ( mTokenGroup[i].type == 5 ) cout << "DIV" << endl ;
      else if ( mTokenGroup[i].type == 6 ) cout << "LP" << endl ;
      else if ( mTokenGroup[i].type == 7 ) cout << "RP" << endl ;
      else if ( mTokenGroup[i].type == 8 ) cout << "EQ" << endl ;
      else if ( mTokenGroup[i].type == 9 ) cout << "GR" << endl ;
      else if ( mTokenGroup[i].type == 10 ) cout << "SM" << endl ;
      else if ( mTokenGroup[i].type == 12 ) {
	    cout << "AND "  ; 
        cout << mTokenGroup[i].temp << endl ;
      } // else if
      else if ( mTokenGroup[i].type == 13 ) {
	    cout << "OR "  ; 
        cout << mTokenGroup[i].temp << endl ;
      } // else if
      else if ( mTokenGroup[i].type == 11 ) {
	    cout << "ID "  ; 
        cout << mTokenGroup[i].temp << endl ;
      } // else if
      else if ( mTokenGroup[i].type == 14 )  {
	    cout << "NOT "  ; 
        cout << mTokenGroup[i].temp << endl ;
      } // else if
      else if ( mTokenGroup[i].type == 15 )  {
	    cout << "T "  ; 
        cout << mTokenGroup[i].temp << endl ;
      } // else if
      else if ( mTokenGroup[i].type == 16 )  {
	    cout << "F "  ; 
        cout << mTokenGroup[i].temp << endl ;
      } // else if
      i++ ;
    } // while
  } // PrintTG()
  
  void Final() {
  	int n = 0 ;
  	int sum = 0 ;
  	if ( mTokenGroup[n].type == LP ) {
	  n++;
	  if( mTokenGroup[n].type == PN ){
	  	n++;
		if (  mTokenGroup[n].type == NUM && mTokenGroup[n+1].type == RP ) {
		  cout << mTokenGroup[n].temp << endl ;
		  n = n + 2 ;
		}
		else if( mTokenGroup[n].type == LP && ( mTokenGroup[n+1].type == ADD || mTokenGroup[n+1].type == SUB || mTokenGroup[n+1].type == MUL || mTokenGroup[n+1].type == DIV || mTokenGroup[n+1].type == MOD ) ) {
		  sum = sum + CNT(n) ;
		  cout << sum << endl ;
		}
		else if( mTokenGroup[n].type == LP && ( mTokenGroup[n+1].type == EQ || mTokenGroup[n+1].type == GR || mTokenGroup[n+1].type == SM) ){
		  bool tfn = false ;
		  tfn = TFN( n ) ;
		  if ( tfn == true ) cout<< "#t" << endl ;
		  else 	cout<< "#f" << endl ;
		}
	  } 
	  else if ( mTokenGroup[n].type == PB ){
	  	n++ ;
	  	if (  ( mTokenGroup[n].type == T || mTokenGroup[n].type == F) && mTokenGroup[n+1].type == RP ) {
		  cout << mTokenGroup[n].temp << endl ;
		  n = n + 2 ;
		}
		else if( mTokenGroup[n].type == LP && ( mTokenGroup[n+1].type == AND || mTokenGroup[n+1].type == OR || mTokenGroup[n+1].type == NOT) ){
		  if( TFB(n) ) cout<< "#t" << endl ;
		  else 	cout<< "#f" << endl ;
		}	
	  }

	}
	   
  }

  bool TFB( int &n ) {
  	bool ans = false ;
  	int sss = 0 ;
  	TokenType a  ;
  	TokenType b  ;
    if( mTokenGroup[n].type == LP )	{
      n++;
      if( mTokenGroup[n].type == OR ){
      	n++;
      	if( mTokenGroup[n].type == T || mTokenGroup[n].type == F ){
      	  a = mTokenGroup[n].type ;
      	  n++;
		}
		else if( mTokenGroup[n].type == LP ) {
		  ans = TFB(n) ;
		  if( ans == true ) a = T ;
		  else a = F ;
	    }
      	while( mTokenGroup[n].type != RP  ){
      	  if( mTokenGroup[n].type == T || mTokenGroup[n].type == F ){
      	  	b = mTokenGroup[n].type ;
      	    if( a == T || b == T ) sss++;
		  }
		  else if( mTokenGroup[n].type == LP ){
		    ans = TFB( n ) ;
		    if( ans == true ) sss++;	    
	      }
		  n++;	
		}
	    if( sss==0 ) return false ;
	    else return true ;
	  }
	  else if( mTokenGroup[n].type == AND ){
	  	n++;
      	if( mTokenGroup[n].type == T || mTokenGroup[n].type == F ){
      	  a = mTokenGroup[n].type ;
      	  n++;
		}
		else if( mTokenGroup[n].type == LP ) {
		  ans = TFB(n) ;
		  if( ans == true ) a = T ;
		  else a = F ;
	    }
      	while( mTokenGroup[n].type != RP  ){
      	  if( mTokenGroup[n].type == T || mTokenGroup[n].type == F ){
      	  	b = mTokenGroup[n].type ;
      	    if( a == F || b == F ) sss++;  
		  }
		  else if( mTokenGroup[n].type == LP ){
		    ans = TFB( n ) ;
		    if( ans == false ) sss++;
		    else b = T ;		    
	      }
		  n++;	
		}		    
		if( sss == 0 ) return true;
      	else return false ;
	  } 
	  else if( mTokenGroup[n].type == NOT ){
	  	n++;
	  	if( mTokenGroup[n].type == T || mTokenGroup[n].type == F){
          a = mTokenGroup[n].type ;
		}
		else if( mTokenGroup[n].type == LP ) {
		  ans = TFB(n) ;
		  if( ans == true ) a = T ;
		  else a = F ;
	    }
		n++;
		if( a == T ) return false ;
		else if( a == F ) return true ;
 	  } 
	} 
  	
  }

  bool TFN( int &n ) { 
   	int a = 0 ;
   	int b = 0 ;
    if( mTokenGroup[n].type == LP )	{
      n++;
      if( mTokenGroup[n].type == EQ ){
      	n++;
      	if( mTokenGroup[n].type == NUM ){
      	  a = atoi(mTokenGroup[n].temp)	;
      	  n++;
		}
		else if( mTokenGroup[n].type == LP ) a = CNT( n ) ;
      	while( mTokenGroup[n].type != RP  ){
      	  if( mTokenGroup[n].type == NUM ){
      	  	b = atoi(mTokenGroup[n].temp)	;
      	    if( a != b ) return false;
		  }
		  else if( mTokenGroup[n].type == LP ){
		    b = CNT( n ) ;
		    if( a != b ) return false;
	      }
		  n++;	
		}
		return true;	
	  }
	  else if( mTokenGroup[n].type == SM ){
	  	n++;
	  	if( mTokenGroup[n].type == NUM ){
      	  a = atoi(mTokenGroup[n].temp)	;
		}
		else if( mTokenGroup[n].type == LP ) a = CNT( n ) ;
		n++;
		if( mTokenGroup[n].type == NUM ){
      	  b = atoi(mTokenGroup[n].temp)	;
      	  if( a < b ) return true ;
      	  else return false ;
      	  n++;
		}
		else if( mTokenGroup[n].type == LP ) {
		  b = CNT( n ) ;
		  if( a < b ) return true ;
      	  else return false ;
		}  
	  } 
	  else if( mTokenGroup[n].type == GR ){
	  	n++;
	  	if( mTokenGroup[n].type == NUM ){
      	  a = atoi(mTokenGroup[n].temp)	;
		}
		else if( mTokenGroup[n].type == LP ) a = CNT( n ) ;
		n++;
		if( mTokenGroup[n].type == NUM ){
      	  b = atoi(mTokenGroup[n].temp)	;
      	  if( a < b ) return true ;
      	  else return false ;
      	  n++;
		}
		else if( mTokenGroup[n].type == LP ) {
		  b = CNT( n ) ;
		  if( a < b ) return true ;
      	  else return false ;
		}  
	  } 
	} 
  	
  }
  
  int CNT( int &n ) {
  	int a = 0 ;

    if( mTokenGroup[n].type == LP )	{
      n++;
      if( mTokenGroup[n].type == ADD ){
      	n++;
      	if( mTokenGroup[n].type == NUM ){
      	  a = a + atoi(mTokenGroup[n].temp)	;
		}
		else if( mTokenGroup[n].type == LP ) a = a + CNT( n ) ;
		n++;
      	while( mTokenGroup[n].type != RP  ){
      	  if( mTokenGroup[n].type == NUM ){
      	    a = a + atoi(mTokenGroup[n].temp) ;
		  }
		  else if( mTokenGroup[n].type == LP ) a = a + CNT( n ) ;
		  n++;	
		}
		
		if( mTokenGroup[n].type == RP ){
		  return a;
		}
	  }
	  else if( mTokenGroup[n].type == MUL ){
      	n++;
      	if( mTokenGroup[n].type == NUM ){
      	  a = a + atoi(mTokenGroup[n].temp)	;
		}
		else if( mTokenGroup[n].type == LP ) a = a + CNT( n ) ;
		n++;
      	while( mTokenGroup[n].type != RP  ){
      	  if( mTokenGroup[n].type == NUM ){
      	    a = a * atoi(mTokenGroup[n].temp) ;
		  }
		  else if( mTokenGroup[n].type == LP ) a = a * CNT( n ) ; 
		  n++;	
	    }
		if( mTokenGroup[n].type == RP ){
		  return a;
		}
	  }
	  else if( mTokenGroup[n].type == SUB ){
	  	n++;
	  	if( mTokenGroup[n].type == NUM ){
      	  a = a + atoi(mTokenGroup[n].temp)	;
		}
		else if( mTokenGroup[n].type == LP ) a = a + CNT( n ) ;
		n++;
		if( mTokenGroup[n].type == NUM ){
      	  a = a - atoi(mTokenGroup[n].temp)	;
      	  n++;
		}
		else if( mTokenGroup[n].type == LP )  a = a - CNT( n ) ;
		if( mTokenGroup[n].type == RP ){
		  return a;
		}
	  } 
	  else if( mTokenGroup[n].type == DIV ){
	  	n++;
	  	if( mTokenGroup[n].type == NUM ){
      	  a = a + atoi(mTokenGroup[n].temp)	;
		}
		else if( mTokenGroup[n].type == LP ) a = a + CNT( n ) ;
		n++;
		if( mTokenGroup[n].type == NUM ){
      	  a = a / atoi(mTokenGroup[n].temp)	;
      	  n++;
		}
		else if( mTokenGroup[n].type == LP )  a = a / CNT( n ) ;
		if( mTokenGroup[n].type == RP ){
		  return a;
		}
	  } 
	  else if( mTokenGroup[n].type == MOD ){
	  	n++;
	  	if( mTokenGroup[n].type == NUM ){
      	  a = a + atoi(mTokenGroup[n].temp)	;
		}
		else if( mTokenGroup[n].type == LP ) a = a + CNT( n ) ;
		n++;
		if( mTokenGroup[n].type == NUM ){
      	  a = a%atoi(mTokenGroup[n].temp) ;
      	  n++;
		}
		else if( mTokenGroup[n].type == LP )  a = a%CNT( n ) ;

		if( mTokenGroup[n].type == RP ){
		  return a;
		}
	  } 
	}
  } 
  
  void CleanChar( char temp[100] ) {
    int i = 0 ;
    while ( i < 100 ) {
      temp[i] = '\0' ;  
      i++ ;
    } // while
  } // CleanChar()
  
  void PusH( char temp[100], TokenType type ) {
    A tTemp ;
    strcpy( tTemp.temp, temp );
    tTemp.type = type ;
    mTokenGroup.push_back( tTemp ) ;
  } // PusH()
  
  bool Stmts() {
    /* 
    STMT ::= EXP | DEF-STMT | PRINT-STMT
    */

    CleanChar( mtokenvalue ) ;
    mPRn = 0 ; 
    char ch ;
    bool gAY = false ;
    TokenType temptype ;
    
    

    CleanChar( mtokenvalue ) ;

    //if ( cin.peek() == ' ' || cin.peek() == '\n' || cin.peek() == '\t' || cin.peek() == '\0')  return true ;
    

	if( Pstmt() ) {
		
		return true ;
	}
	else if( EXP() ) {
		return true ;
	}
	else {

	 return false ; 
    }  
  } // Stmts()
  
  bool Pstmt() {
  	/*
  	PRINT-STMT ::= (print-num EXP) | (print-bool EXP)
  	*/
  	char ch ;
  	if ( cin.peek() == '\n') ch = cin.get();
  	if( cin.peek() == '(' ){
  		CleanChar( mtokenvalue ) ;
        mscanner.GetToken( mtokenvalue, mtokentype ) ;
        if( cin.peek() == 'p' ) {
          PusH( mtokenvalue, mtokentype ) ;
          
          CleanChar( mtokenvalue ) ;
          mscanner.GetToken( mtokenvalue, mtokentype ) ;
          
          if ( strcmp( mtokenvalue, "print-num" ) == 0 || strcmp( mtokenvalue, "print-bool" ) == 0 ) {
          	if( strcmp( mtokenvalue, "print-num" ) == 0 ) mtokentype = PN ;
          	else if ( strcmp( mtokenvalue, "print-bool" ) == 0 ) mtokentype = PB ;
          	PusH( mtokenvalue, mtokentype ) ;
          	if ( EXP() ) {
          	  
          	  if ( cin.peek() == ')' ) {
				CleanChar( mtokenvalue ) ;
        		mscanner.GetToken( mtokenvalue, mtokentype ) ;
       			PusH( mtokenvalue, mtokentype ) ;
				return true ;
		      }
		      else return false ;
			}
			else return false ; 
		  }
		  else return false ;
		}
		else {
	      cin.putback('(') ;
	      return false ;
	    } 
	}
	else return false ;
	
  }
  
  bool EXP() {
  	/*
  	EXP = bool-val | number | VARIABLE | NUM-OP | LOGICAL-OP 
    | FUN-EXP | FUN-CALL | IF-EXP
  	*/
  	char ch ;
  	int a = 0 ;
  	char c ;
  	ch = cin.peek() ;
  	
  	while( ch == ' ' || ch == '\t' || ch == '\n'  ) {
  	  ch = cin.get() ;
	  ch = cin.peek();	
	}
  	if ( ch == '-' ) {
	  ch = cin.get() ;
	  c = cin.peek() ;
	  if ( mscanner.IsNUM(c) )  {
	  	cin.putback( ch ); 
	  	a = 1 ;
	  }
    }
    
  	if( ch  == '#') {
  		CleanChar( mtokenvalue ) ;
        mscanner.GetToken( mtokenvalue, mtokentype ) ;
        if ( mtokentype == T || mtokentype == F ) {
          PusH( mtokenvalue, mtokentype ) ;
          return true ;
        }
        else return false ;
	}
	else if ( mscanner.IsNUM(ch) || a == 1 ) {

	  CleanChar( mtokenvalue ) ;
      mscanner.GetToken( mtokenvalue, mtokentype ) ;
      PusH( mtokenvalue, mtokentype ) ;
      return true ;
	}
	else if ( NOP() ) {
	  return true ;
	}
  	else if ( LOOP() ) {
  	  return true ;
	}
  	else {  	  
  	  return false ;
	}
  } 
 
  bool NOP() {
  	/*
	NUM-OP = PLUS | MINUS | MULTIPLY | DIVIDE | MODULUS | GREATER
    | SMALLER | EQUAL
	*/
	if ( cin.peek() == '(') {
      CleanChar( mtokenvalue ) ;
      mscanner.GetToken( mtokenvalue, mtokentype ) ;
	  if( cin.peek() == '+' ) {
	  	PusH( mtokenvalue, mtokentype ) ;
	    CleanChar( mtokenvalue ) ;
        mscanner.GetToken( mtokenvalue, mtokentype ) ;
        PusH( mtokenvalue, mtokentype ) ;
        if ( EXP() ) {
	      while( EXP() ){
			  if ( cin.peek() == ')' ) {
	      	  CleanChar( mtokenvalue ) ;
              mscanner.GetToken( mtokenvalue, mtokentype ) ;
              PusH( mtokenvalue, mtokentype ) ;
              return true ;
		      }
	      }

		  return false ;	
	    }
	    else {
	    	return false ;
	    	
		}
	  }
	  else if( cin.peek() == '-' ) {
	  	PusH( mtokenvalue, mtokentype ) ;
	    CleanChar( mtokenvalue ) ;
        mscanner.GetToken( mtokenvalue, mtokentype ) ;
        PusH( mtokenvalue, mtokentype ) ;
		if ( EXP() ) {
	      if( EXP() ){
	  	    if ( cin.peek() == ')' ) {
	      	  CleanChar( mtokenvalue ) ;
              mscanner.GetToken( mtokenvalue, mtokentype ) ;
              PusH( mtokenvalue, mtokentype ) ;
              return true ;
		    } 
		    else return false ;
	      }
		  else return false ;	
	    }
	    else return false ;
	  }
	  else if( cin.peek() == '/' ) {
	  	PusH( mtokenvalue, mtokentype ) ;
	    CleanChar( mtokenvalue ) ;
        mscanner.GetToken( mtokenvalue, mtokentype ) ;
        PusH( mtokenvalue, mtokentype ) ;
		if ( EXP() ) {
	      if( EXP() ){
	  	    if ( cin.peek() == ')' ) {
	      	  CleanChar( mtokenvalue ) ;
              mscanner.GetToken( mtokenvalue, mtokentype ) ;
              PusH( mtokenvalue, mtokentype ) ;
              return true ;
		    } 
		    else return false ;
	      }
		  else return false ;	
	    }
	    else return false ;
	  }
	  else if( cin.peek() == 'm' ) {
	  	PusH( mtokenvalue, mtokentype ) ;
	    CleanChar( mtokenvalue ) ;
        mscanner.GetToken( mtokenvalue, mtokentype ) ;
        if ( mtokentype != MOD ) return false ; 
        PusH( mtokenvalue, mtokentype ) ;
		if ( EXP() ) {
	      if( EXP() ){
	  	    if ( cin.peek() == ')' ) {
	      	  CleanChar( mtokenvalue ) ;
              mscanner.GetToken( mtokenvalue, mtokentype ) ;
              PusH( mtokenvalue, mtokentype ) ;
              return true ;
		    } 
		    else return false ;
	      }
		  else return false ;	
	    }
	    else return false ;
	  }
	  else if( cin.peek() == '>' ) {
	  	PusH( mtokenvalue, mtokentype ) ;
	    CleanChar( mtokenvalue ) ;
        mscanner.GetToken( mtokenvalue, mtokentype ) ;
        PusH( mtokenvalue, mtokentype ) ;
		if ( EXP() ) {
	      if( EXP() ){
	  	    if ( cin.peek() == ')' ) {
	      	  CleanChar( mtokenvalue ) ;
              mscanner.GetToken( mtokenvalue, mtokentype ) ;
              PusH( mtokenvalue, mtokentype ) ;
              return true ;
		    } 
		    else return false ;
	      }
		  else return false ;	
	    }
	    else return false ;
	  }	  
	  else if( cin.peek() == '<' ) {
	  	PusH( mtokenvalue, mtokentype ) ;
	    CleanChar( mtokenvalue ) ;
        mscanner.GetToken( mtokenvalue, mtokentype ) ;
        PusH( mtokenvalue, mtokentype ) ;
		if ( EXP() ) {
	      if( EXP() ){
	  	    if ( cin.peek() == ')' ) {
	      	  CleanChar( mtokenvalue ) ;
              mscanner.GetToken( mtokenvalue, mtokentype ) ;
              PusH( mtokenvalue, mtokentype ) ;
              return true ;
		    } 
		    else return false ;
	      }
		  else return false ;	
	    }
	    else return false ;
	  }
	  else if( cin.peek() == '*' ) {
	  	PusH( mtokenvalue, mtokentype ) ;
	    CleanChar( mtokenvalue ) ;
        mscanner.GetToken( mtokenvalue, mtokentype ) ;
        PusH( mtokenvalue, mtokentype ) ;
        if ( EXP() ) {
	      while( EXP() ){
            if ( cin.peek() == ')' ) {
	      	  CleanChar( mtokenvalue ) ;
              mscanner.GetToken( mtokenvalue, mtokentype ) ;
              PusH( mtokenvalue, mtokentype ) ;
              return true ;
		    }
	      }

		  return false ;	
	    }
	    else return false ;
	  }
	  else if( cin.peek() == '=' ) {
	  	PusH( mtokenvalue, mtokentype ) ;
	    CleanChar( mtokenvalue ) ;
        mscanner.GetToken( mtokenvalue, mtokentype ) ;
        PusH( mtokenvalue, mtokentype ) ;
        if ( EXP() ) {
	      while( EXP() ){
	  	    if ( cin.peek() == ')' ) {
	      	  CleanChar( mtokenvalue ) ;
              mscanner.GetToken( mtokenvalue, mtokentype ) ;
              PusH( mtokenvalue, mtokentype ) ;
              return true ;
		    }
	      }
		  return false ;	
	    }
	    else return false ;
	  }
	  else{
	  	cin.putback('(') ;
	  	return false ;
	  } 		  
    }
    else{
      return false ;
	} 
  }
  
  bool LOOP() {
  	/*
  	LOGICAL-OP = AND-OP | OR-OP | NOT-OP
    */
      if ( cin.peek() == '(') {
      CleanChar( mtokenvalue ) ;
      mscanner.GetToken( mtokenvalue, mtokentype ) ;
	  if( cin.peek() == 'a' ) {
	  	PusH( mtokenvalue, mtokentype ) ;
	    CleanChar( mtokenvalue ) ;
        mscanner.GetToken( mtokenvalue, mtokentype ) ;
        PusH( mtokenvalue, mtokentype ) ;
        if ( EXP() ) {
	      while( EXP() ){
	  	    if ( cin.peek() == ')' ) {
	      	  CleanChar( mtokenvalue ) ;
              mscanner.GetToken( mtokenvalue, mtokentype ) ;
              PusH( mtokenvalue, mtokentype ) ;
              return true ;
		    }
	      }
		  return false ;	
	    }
	    else return false ;
	  }
	  else if( cin.peek() == 'n' ) {
	  	PusH( mtokenvalue, mtokentype ) ;
	    CleanChar( mtokenvalue ) ;
        mscanner.GetToken( mtokenvalue, mtokentype ) ;
        PusH( mtokenvalue, mtokentype ) ;
		if ( EXP() ) {
	  	    if ( cin.peek() == ')' ) {
	      	  CleanChar( mtokenvalue ) ;
              mscanner.GetToken( mtokenvalue, mtokentype ) ;
              PusH( mtokenvalue, mtokentype ) ;
              return true ;
		    } 
		    else return false ;	
	    }
	    else return false ;
	  }
	  else if( cin.peek() == 'o' ) {
	  	PusH( mtokenvalue, mtokentype ) ;
	    CleanChar( mtokenvalue ) ;
        mscanner.GetToken( mtokenvalue, mtokentype ) ;
        PusH( mtokenvalue, mtokentype ) ;
        if ( EXP() ) {
	      while( EXP() ){
	  	    if ( cin.peek() == ')' ) {
	      	  CleanChar( mtokenvalue ) ;
              mscanner.GetToken( mtokenvalue, mtokentype ) ;
              PusH( mtokenvalue, mtokentype ) ;
              return true ;
		    }
	      }
		  return false ;	
	    }
	    else return false ;
	  }
	  else{
	  	cin.putback('(') ;
	  	return false ;
	  } 	  
    }
    else return false ;
  }
  
  
};





int main( int argc, char** argv ) {
  Parser parser ;
  Scanner scanner ;
  char ch ;
  bool ok = false ;
  A biTcH ;
  strcpy( biTcH.temp, "\0" ) ;

  while ( cin.peek() != EOF ) {

    if ( parser.Stmts() ) {
      //parser.PrintTG() ;
      parser.Final() ;
      ch = cin.peek();
      while( ch == ' ' || ch == '\t' || ch == '\n' ){
      	ch = cin.get() ; 
      	ch = cin.peek() ;
	  } // while 

    }  // if
    else {
      ch = cin.peek() ;	
      while( ch != '\n' ){
      	ch = cin.get() ; 
      	ch = cin .peek() ;
	  } // while
	  cout << "syntax error" << endl ;
	  while( ch == '\n' ) {
	  	ch = cin.get() ; 
      	ch = cin.peek() ;
	  }


    } //else
    parser.mTokenGroup.clear() ;
    ch = cin.peek() ;
  } // While()
  
  
} // main()


