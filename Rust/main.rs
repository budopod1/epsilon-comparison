use std::fs;
use std::collections::HashSet;
use std::iter::zip;


enum LetterResponse {
    GRAY, ORANGE, GREEN
}


fn find_best_word<'a>(words: &'a Vec<&'a str>) -> &'a str {
    let mut frequencies = [0; 26];
    for word in words {
        for chr in (*word).chars() {
            frequencies[(chr as usize)-97] += 1;
        }
    }
    // max_by_key doesn't work the same as other language's maxes
    let mut best_score = 0;
    let mut best: Option<&str> = None;
    for word in words {
        let chars: HashSet<char> = (*word).chars().collect();
        let score = chars.iter().map(
            |chr| frequencies[(*chr as usize)-97]
        ).sum();
        if score > best_score {
            best_score = score;
            best = Some(word);
        }
    }
    return best.unwrap();
}


fn get_wordle_response(guess: &str, target: &str) -> Vec<LetterResponse> {
    assert_eq!(guess.len(), target.len());
    zip(guess.chars(), target.chars()).map(|(gchar, tchar)| {
        if gchar == tchar {
            return LetterResponse::GREEN;
        } else if target.contains(gchar) {
            return LetterResponse::ORANGE;
        } else {
            return LetterResponse::GRAY;
        }
    }).collect()
}


fn filter_words_given_response<'a, 'b>(words: &Vec<&'a str>, response: Vec<LetterResponse>, guess: &'b str) -> Vec<&'a str> {
    words.iter().filter(|word| {
        response.iter().enumerate().all(|(i, lresponse)| match lresponse {
            LetterResponse::GREEN => guess.chars().nth(i) == word.chars().nth(i),
            LetterResponse::ORANGE => {
                let gchar = guess.chars().nth(i);
                gchar != word.chars().nth(i) && word.contains(gchar.unwrap())
            }
            LetterResponse::GRAY => !word.contains(guess.chars().nth(i).unwrap()),
        })
    }).map(|w| *w).collect()
}


fn do_wordle<'a>(all_words: &Vec<&'a str>, target: &str) -> bool {
    let mut words = all_words;
    let mut word_history = Vec::new();
    for _ in 0..6 {
        let guess = find_best_word(words);
        if guess == target {
            return true;
        }
        let response = get_wordle_response(guess, target);
        let new_words = filter_words_given_response(words, response, guess);
        word_history.push(new_words);
        words = word_history.last().unwrap();
    }
    return false;
}


fn main() {
    let words = fs::read_to_string("words.txt")
        .expect("Unable to load words");
    let words: Vec<&str> = words.split('\n').collect();

    let mut succeeded = 0;
    let mut failed = 0;

    for target in &words {
        let success = do_wordle(&words, &target);
        if success {
            succeeded += 1;
        } else {
            failed += 1;
        }
    }

    println!("Succeeded: {succeeded}");
    println!("Failed: {failed}");
}
