using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.RegularExpressions;

namespace TestTask2
{
    public class StringIndex
    {
        public enum StringLanguage
        {
            Russian, English
        }
        public static List<char> FilterChars { get; } = new List<char>() { ' ', ',', '.', '_', '!', '?', '-', '\'', '\"' };
        private string _str;
        private string _fstr;
        private string _comment;
        private float _index;
        private StringLanguage _lang;
        public StringIndex() { }
        public StringIndex(string srcStr)
        {
            SourceString = srcStr;
        }
        public float Index { get => _index; }
        public string Comment { get => _comment; }
        public StringLanguage Language { get => _lang; }
        public string FilteredString { get => _fstr; }
        public string SourceString
        {
            get => _str;
            set
            {
                string[] parts = value.Split('|');
                _str = parts[0];
                if(parts.Length > 1) _comment = parts[1];
                _lang = Regex.IsMatch(_str, @"\p{IsCyrillic}") ? StringLanguage.Russian : StringLanguage.English;
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
            FilterChars.ForEach(x => str = str.Replace(x.ToString(), string.Empty));
            return str;
        }
    }
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
