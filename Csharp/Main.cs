using System;
using System.IO;
using System.Linq;
using System.Collections.Generic;

// Yes, although normally each class gets its own file, for a comparison
// it's easier to use only one file
public class WordleSolver {
    List<string> wordList;

    enum LetterResponse {
        GRAY, ORANGE, GREEN
    }

    public WordleSolver(List<string> words) {
        wordList = words;
    }

    string findBestWord(IEnumerable<string> words) {
        Dictionary<char, int> frequencies = new Dictionary<char, int>();
        foreach (string word in words) {
            foreach (char chr in word) {
                int count = 0;
                frequencies.TryGetValue(chr, out count);
                frequencies[chr] = count+1;
            }
        }
        int bestScore = 0;
        string best = null;
        foreach (string word in words) {
            int score = word.ToCharArray().Distinct()
                            .Select(chr => frequencies[chr]).Sum();
            if (score > bestScore) {
                bestScore = score;
                best = word;
            }
        }
        return best;
    }

    List<LetterResponse> getWordleResponse(string guess, string target) {
        return guess.ToCharArray().Zip(target.ToCharArray(), (gchar, tchar) => {
            if (gchar == tchar) {
                return LetterResponse.GREEN;
            } else if (target.Contains(gchar)) {
                return LetterResponse.ORANGE;
            } else {
                return LetterResponse.GRAY;
            }
        }).ToList();
    }

    IEnumerable<string> filterWordsGivenResponse(IEnumerable<string> words, List<LetterResponse> response, string guess) {
        return words.Where(word => Enumerable.Range(0, word.Length).All(i => {
            char wchar = word[i];
            LetterResponse lresponse = response[i];
            char gchar = guess[i];
            if (lresponse == LetterResponse.GREEN) {
                return wchar == gchar;
            } else if (lresponse == LetterResponse.ORANGE) {
                return word.Contains(gchar) && wchar != gchar;
            } else {
                return !word.Contains(gchar);
            }
        }));
    }
    
    public bool DoWordle(string target) {
        IEnumerable<string> words = wordList;
        for (int i = 0; i < 6; i++) {
            string guess = findBestWord(words);
            if (guess == target)
                return true;
            List<LetterResponse> response = getWordleResponse(guess, target);
            words = filterWordsGivenResponse(words, response, guess);
        }
        return false;
    }
}

public class Epsilon {
    public static void Main() {
        List<string> words = new List<string>();
        using (StreamReader file = new StreamReader("words.txt")) {
            while (true) {
                string word = file.ReadLine();
                if (word == null) break;
                words.Add(word);
            }
        }

        WordleSolver solver = new WordleSolver(words);

        int succeeded = 0;
        int failed = 0;

        foreach (string target in words) {
            bool success = solver.DoWordle(target);
            if (success) {
                succeeded++;
            } else {
                failed++;
            }
        }

        Console.WriteLine($"Succeeded: {succeeded}");
        Console.WriteLine($"Failed: {failed}");
    }
}
