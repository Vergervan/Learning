using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.RegularExpressions;

namespace TestTask2
{
    class Program
    {
        public static List<StringIndex> indexes = new List<StringIndex>();
        static void Main(string[] args)
        {
            while (true)
            {
                Console.Write("Введите строку: ");
                string entryString = Console.ReadLine();
                StringIndex index = new StringIndex(entryString);
                indexes.Add(index);
                Console.WriteLine($"Индекс текущей строки равен {index.Index}");
                StringIndex[] matches = FindSameIndexes(index, indexes);
                Console.WriteLine($"Найдено {(matches == null ? 0 : matches.Length)} совпадений по индексам");
                if(matches != null)
                {
                    for(int i = 0; i < matches.Length; i++)
                    {
                        Console.WriteLine($"{i + 1}.{matches[i].SourceString}");
                    }
                }
                Console.WriteLine("Хотите продолжить? (y/n)");
                if (Console.ReadKey().Key == ConsoleKey.Y)
                {
                    Console.Clear();
                    continue;
                }
                return;
            }
        }
        //Finds the same value of indexes in another language
        static StringIndex[] FindSameIndexes(StringIndex index, IEnumerable<StringIndex> indexes)
        {
            List<StringIndex> matches = new List<StringIndex>();
            foreach(var item in indexes)
            {
                if (item == index || index.Language == item.Language || index.Index != item.Index) continue;
                matches.Add(item);
            }
            return matches.Count > 0 ? matches.ToArray() : null;
        }
    }
}
