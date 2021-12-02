using System;
using System.Collections.Generic;
using System.Text;

namespace TestTask2
{
    public class StringIndex
    {
        public enum StringLanguage
        {
            Russian, English
        }
        public static List<char> FilterChars { get; } = new List<char>() { ' ', ',', '.', '_', '!', '?', '-', '\'', '\"' };
        private string _str; //Source string
        private string _fstr; //Filtered string
        private string _comment; //Comment
        private float _index; //Value of string index
        private StringLanguage _lang; //Language of string
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
                if (parts.Length > 1) _comment = parts[1];
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
}
