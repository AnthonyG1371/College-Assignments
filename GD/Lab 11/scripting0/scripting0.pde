int x;
int y;
color mycolor;
int widenum;
int highnum;


void setup() {
  size(400,300);
  surface.setResizable(true);
  mycolor = #000000;
  ellipseMode( CORNER );
  readAndProcessScript();
} // end of setup()

void readAndProcessScript() {
  BufferedReader myfile;
  try {
    myfile = createReader( "myscript.txt" );
    String myline = myfile.readLine();
    println( "line read from file: [" + myline + "]" );
    println(myline.substring(41,46));
    println(myline.substring(48,53));
     
    if(myline.substring(41,46).equals("x = ") && myline.substring(48,53).equals("y = "))
    {
      x = int(myline.substring(45,48));
      y = int(myline.substring(52,54));
      println("x = " + x);
      println("y = " + y);
    }
    if ( myline.substring( 0,11 ).equals( "mycolor = #" )) {
     println( "match found!" );
     mycolor = color( unhex( "ff" + myline.substring(11,17)));
     println( "fill shape with this color: " + hex( mycolor ));
    }
    if(myline.substring(17,25).equals("width = ") && myline.substring(28,37).equals("height = "))
    {
     String wide, high;
     wide = myline.substring(25,28);
     high = myline.substring(37,40);
     widenum = int(wide);
     highnum = int(high);
     println(widenum);
     println(highnum);
     surface.setSize(widenum, highnum);
     //size(widenum, highnum);
    }
    
    else {
      println( "no match :-(" );
    }
    myfile.close();
  }
  catch( IOException e ) {
    e.printStackTrace();
  }
} // end of parse


void draw() {
  background( #ffffff );
  fill( mycolor );
  ellipse( x, y, 100, 100 );
} // end of draw()