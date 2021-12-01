using System;
using System.Collections.Generic;
using System.Linq;

namespace TestTask2
{
    public class StringIndex
    {
        public static List<char> FilterChars { get; } = new List<char>() { ' ', ',', '.', '_', '!', '?', '-', '\'', '\"' };
        private string _str;
        private string _fstr;
        private string _comment;
        private float _index;
        public StringIndex() { }
        public StringIndex(string srcStr)
        {
            SourceString = srcStr;
        }
        public float Index { get => _index; }
        public string Comment { get => _comment; }
        public string FilteredString { get => _fstr; }
        public string SourceString
        {
            get => _str;
            set
            {
                string[] parts = value.Split('|');
                _str = parts[0];
                if(parts.Length > 1) _comment = parts[1];
                _fstr = FilterString(_str);
                _index = CalculateIndex(_fstr);
            }
        }
        public void PushString(string str) => SourceString = str;
        private float CalculateIndex(string str)
        {
            if (str.Length == 0) return 0;
            float index = 0;
            float letterIndex = 0.5f;
            for (int i = 0; i < str.Length; i++, letterIndex++)
            {
                index += letterIndex;
            }
            return index * str.Length;
        }
        private string FilterString(string str)
        {
            FilterChars.ForEach(x => str = str.Replace(x.ToString(), String.Empty));
            return str;
        }
    }
    class Program
    {
        public static List<StringIndex> russianStrings = new List<StringIndex>();
        public static List<StringIndex> englishStrings = new List<StringIndex>();
        static void Main(string[] args)
        {
            while (true)
            {
                Console.WriteLine("Выберите язык строки:\n1.Русский\n2.Английский");
                ConsoleKey key = Console.ReadKey().Key;
                Console.Clear();
                Console.Write("Введите строку: ");
                string entryString = Console.ReadLine();
                StringIndex index = new StringIndex(entryString);
                Console.WriteLine(index.Index);
                switch (key)
                {
                    case ConsoleKey.D1:
                        russianStrings.Add(index);
                        break;
                    case ConsoleKey.D2:
                        englishStrings.Add(index);
                        break;
                }
            }
        }
    }
}
