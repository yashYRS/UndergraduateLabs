using System;

namespace question2
{
    class Item {
        public string Name { get; set; }
        static float cost ;
        public static float Cost { get => cost; set => cost = value; }

        // automatic property       
        public float CalcGST( ) {
            if ( Cost < 0  ) {
               return 0 ; 
            }
            else {
                return Cost*0.08F  ;  
            }
        }

    }

    class Program
    {
        static void Main(string[] args)
        {
            Item iobj1 = new Item() ; 
            Item iobj2 = new Item() ;
            Item []iobj = { iobj1, iobj2 } ; 
            string tname ;
            Item.Cost = 45.2F;
            for ( int i = 0 ; i < 2 ; i++ ) {
                Console.Write( "\n\n Enter name "+ (i+1).ToString()  + " - ");
                tname = Console.ReadLine() ; 
              //  float.TryParse( Console.ReadLine() , out tcost ) ;      
                iobj[i].Name = tname ; 
                Console.WriteLine( "\n Object name - " + iobj[i].Name ) ; 
                Console.Write ( "\n The GST for the cost - " +  iobj[i].CalcGST().ToString() ) ; 
            }
            Console.Read(); 
        }
    }
}