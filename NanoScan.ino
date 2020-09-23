// NanoScan
// Keyboard Matrix Scanner (6x6) based on Arduino Nano
// incl 8 buttons with led's readout

int s[30]; // 30 stops default off

#define DEBUG
#define MIDICH 5

void setup()
{
  Serial.begin(115200);
#ifdef DEBUG
  Serial.println("Debugging NanoScan");
#endif

  pinMode( 13, OUTPUT ); // D13 is a led output, ignore
  pinMode( 12, INPUT_PULLUP );
  pinMode( 11, INPUT_PULLUP );
  pinMode( 10, INPUT_PULLUP );
  pinMode( 9, INPUT_PULLUP );
  pinMode( 8, INPUT_PULLUP );
  pinMode( 7, OUTPUT );
  pinMode( 6, OUTPUT );
  pinMode( 5, OUTPUT );
  pinMode( 4, OUTPUT );
  pinMode( 3, OUTPUT );
  pinMode( 2, OUTPUT );

  for( int i=0; i<30; i++ ) s[i]=1;

}

void loop()
{

  for( int i=2; i<=7; i++ )
  {
    int j=i-1;
    if( j<2) j=7;
    digitalWrite( j, 1 );
    digitalWrite( i, 0 );
    delay( 10 );   
     
    for( int k=8; k<=12; k++ )
    {
      int n=(k-8)*6+(i-2);
      int v =  digitalRead(k);
        
      if( s[n] != v )
      { 
#ifdef DEBUG        
        Serial.print(v); Serial.print(":"); Serial.println(n);          
#else
       if(v)
        { // NoteOff
          Serial.print( (char)(0x80+MIDICH)); Serial.print( (char)(0x20+n)); Serial.print( (char)0x40);
        }
        else
        { // NoteOn
          Serial.print( (char)(0x90+MIDICH)); Serial.print( (char)(0x20+n)); Serial.print( (char)0x40);        
        }
#endif
        s[n]=v;
      }
    }
  }
}
