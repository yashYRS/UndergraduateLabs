using System;

namespace question1
{

    public delegate void PriceChangedEventHandler(string val );
    class Item {
        int price;
        string name;
        

        public event PriceChangedEventHandler PriceChanged; 
        // Create the event variable 
        public string Name {
            get
            {
                return name; 
            }
            
            set
            {
                name = value; 
            } 
        }
        public int Price 
        {
            get
            {
                return price; 
            }
            set
            {
                price = value;
                // Fire the event 
                if ( PriceChanged != null ) // if the variable has been assigned to a method 
                {
                    PriceChanged(price.ToString() );  
                }

            }

        }


    }


    class Program
    {
        static void Main(string[] args)
        {
            Item itemObj = new Item();
            itemObj.Price = 1023;
            itemObj.Name = "Book A ";
            Console.Write(" Old values - " + itemObj.Price + " for name - " + itemObj.Name ); 
            itemObj.PriceChanged += showInConsole ;

            itemObj.Price = itemObj.Price + 3245 ;
            itemObj.Price = itemObj.Price + 1982 ;
            Console.Read(); 
        }
        public static void showInConsole(string val )
        {
            Console.Write("\n Price changed to " + val );
        }
    }
}