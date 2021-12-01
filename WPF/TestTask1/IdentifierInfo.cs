using System;
using System.Collections.Generic;
using System.Text;

namespace TestTask1
{
    public struct IdentifierText
    {
        public string text;
    }
    public class IdentifierInfo : BaseVM
    {
        public static readonly HashSet<char> Vowels = new HashSet<char>(){ 'a', 'i', 'o', 'e', 'u', 'y', 'а', 'ы', 'е', 'ё', 'о', 'э', 'и', 'у', 'ю', 'я' };

        private int _id;
        private string _text;
        private int _wordCount;
        private int _vowelCount;

        public int ID { get => _id; set => _id = value; }
        public string Text
        {
            get => _text;
            set
            {
                _text = value;
                CalculateNewTextStats();
                OnPropertyChanged("Text");
            }
        }
        public int WordCount { get => _wordCount; }
        public int VowelCount { get => _vowelCount; }
        public IdentifierInfo(int id)
        {
            _id = id;
        }

        private void CalculateNewTextStats()
        {
            _wordCount = GetWordCount();
            _vowelCount = GetVowelCount();
        }
        private int GetWordCount()
        {
            return _text.Split(new char[] { ' ', '\r', '\n' }, StringSplitOptions.RemoveEmptyEntries).Length;
        }

        private int GetVowelCount()
        {
            int count = 0;
            for(int i = 0; i < _text.Length; i++)
            {
                if (Vowels.Contains(_text[i])) 
                    count++;
            }
            return count;
        }
    }
}
