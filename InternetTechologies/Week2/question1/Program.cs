using System;

namespace question1
{
    class Program
    {
        static void Main(string[] args)
        {
            int num1, num2, choice, result; // Two numbers and results 
            choice = 0;
            result = 0;
            string temp; 
            while (choice != 5) {
                Console.WriteLine("Choose Operation - 1. Sum 2. Difference 3. Product 4. Division 5. Exit ");
                temp = Console.ReadLine();
                int.TryParse(temp, out choice);
                if (choice == 5)
                    break;
                Console.WriteLine("Enter number 1 : ");
                string n1 = Console.ReadLine(); // Readline() method returns string type
                Console.WriteLine("Enter number 2 : ");
                string n2 = Console.ReadLine();
                int.TryParse(n1, out num1);
                int.TryParse(n2, out num2); // Now the numbers have the value 
                if (choice == 1)
                    result = num1 + num2;
                else if (choice == 2)
                    result = num1 - num2;
                else if (choice == 3)
                    result = num1 * num2;
                else if (choice == 4)
                    result = num1 / num2;
                Console.WriteLine("The result of Operation of {0} and {1} is {2}", num1, num2, result);
            }
        }
    }
}