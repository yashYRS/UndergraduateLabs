using System;

namespace question3
{
    public class TrafficSignal
    {
        string status; 
        public string Status
        {
            get
            {
                return status; 
            }
            set
            {
                status = value; 
            }
        }
        public static void Yellow(TrafficSignal obj )
        {
            obj.status = " Careful ";
            Console.WriteLine("\n Status - " + obj.status); 
        }

        public static void Green(TrafficSignal obj )
        {
            obj.status = " Move ";
            Console.WriteLine("\n Status - " + obj.status );
        }

        public static void Red(TrafficSignal obj )
        {
            obj.status = " Stop ";
            Console.WriteLine("\n Status - " + obj.status);
        }
    }
    public delegate void TrafficDel(TrafficSignal obj); // Declaration of a delegate  

    class Program
    {
        static void Main(string[] args)
        {
            // Instantiate the delegate variables with methods 
            TrafficSignal street = new TrafficSignal();
            TrafficDel signal = new TrafficDel(TrafficSignal.Yellow);
            signal(street);
            signal = TrafficSignal.Red;  // usage of delegate 
            signal(street);
            signal = TrafficSignal.Green; 
            signal(street);
            Console.Read(); 
            
        }
    }
}