#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define WORDLE_LEN 5

enum LetterResponse {
    GRAY, ORANGE, GREEN
};

struct WordList {
    char **words;
    int count;
};

void freeList(struct WordList *list) {
    free(list->words);
    free(list);
}

char *findBestWord(struct WordList *list) {
    int frequencies[26] = {0};
    for (int i = 0; i < list->count; i++) {
        char *word = list->words[i];
        for (int j = 0; j < WORDLE_LEN; j++) {
            frequencies[word[j]-'a']++;
        }
    }
    int bestScore = 0;
    char *bestWord = NULL;
    for (int i = 0; i < list->count; i++) {
        int score = 0;
        char *word = list->words[i];
        for (int j = 0; j < WORDLE_LEN; j++) {
            char chr = word[j];
            int unique = 1;
            for (int k = 0; k < j; k++) {
                if (word[k] == chr) {
                    unique = 0;
                    break;
                }
            }
            if (unique) {
                score += frequencies[chr-'a'];
            }
        }
        if (score > bestScore) {
            bestScore = score;
            bestWord = word;
        }
    }
    return bestWord;
}

enum LetterResponse *getWordleResponse(char *guess, char *target) {
    enum LetterResponse *response = malloc(WORDLE_LEN*sizeof(enum LetterResponse));
    for (int i = 0; i < WORDLE_LEN; i++) {
        char gchar = guess[i];
        char tchar = target[i];
        if (gchar == tchar) {
            response[i] = GREEN;
        } else {
            int noMatch = 1;
            for (int j = 0; j < WORDLE_LEN; j++) {
                if (i == j) continue;
                char hchar = target[j];
                if (gchar == hchar) {
                    response[i] = ORANGE;
                    noMatch = 0;
                    break;
                }
            }
            if (noMatch) {
                response[i] = GRAY;
            }
        }
    }
    return response;
}

struct WordList *filterWordsGivenResponse(struct WordList *old, enum LetterResponse *response, char *guess) {
    char **words = malloc(sizeof(char*)*old->count);
    int count = 0;
    for (int i = 0; i < old->count; i++) {
        char *word = old->words[i];
        int valid = 1;
        char invalid[WORDLE_LEN] = {0};
        int invalidCount = 0;
        for (int j = 0; j < WORDLE_LEN; j++) {
            enum LetterResponse lresponse = response[j];
            char gchar = guess[j];
            if (lresponse == GREEN) {
                if (word[j] != gchar) {
                    valid = 0;
                    break;
                }
            } else if (lresponse == GRAY) {
                invalid[invalidCount++] = gchar;
            } else { // must be orange
                if (word[j] == gchar) {
                    valid = 0;
                    break;
                }
                int noChar = 1;
                for (int k = 0; k < WORDLE_LEN; k++) {
                    if (j == k) continue;
                    if (word[k] == gchar) noChar = 0;
                }
                if (noChar) {
                    valid = 0;
                    break;
                }
            }
        }
        if (valid) {
            for (int j = 0; j < WORDLE_LEN; j++) {
                char wchar = word[j];
                for (int i = 0; i < invalidCount; i++) {
                    if (invalid[i] == wchar) {
                        valid = 0;
                        break;
                    }
                }
            }
            if (valid) words[count++] = word;
        }
    }
    struct WordList *list = malloc(sizeof(struct WordList));
    list->words = words;
    list->count = count;
    return list;
}

int doWordle(struct WordList *list, char *target) {
    for (int i = 0; i < 6; i++) {
        char *guess = findBestWord(list);
        if (memcmp(guess, target, WORDLE_LEN) == 0) {
            if (i > 0) freeList(list);
            return 1;
        }
        enum LetterResponse *response = getWordleResponse(guess, target);
        struct WordList *newList = filterWordsGivenResponse(list, response, guess);
        free(response);
        if (i > 0) freeList(list);
        list = newList;
    }
    freeList(list);
    return 0;
}

int main() {
    FILE *file = fopen("words.txt", "r");
    if (file == NULL)
        exit(1);

    int wordCapacity = 100;
    int wordCount = 0;
    char **words = malloc(wordCapacity*sizeof(char*));
    
    while (1) {
        char *word = NULL;
        size_t len = 0;
        ssize_t read = getline(&word, &len, file);
        if (read == -1) {
            free(word);
            break;
        }
        word[WORDLE_LEN] = '\0'; // remove possible trailing newline
        wordCount++;
        if (wordCount > wordCapacity) {
            wordCapacity = (wordCapacity*3)/2;
            words = realloc(words, wordCapacity*sizeof(char*));
        }
        words[wordCount-1] = word;
    }

    fclose(file);

    struct WordList *list = malloc(sizeof(struct WordList));
    list->words = words;
    list->count = wordCount;

    int succeeded = 0;
    int failed = 0;

    for (int i = 0; i < wordCount; i++) {
        char *word = words[i];
        if (doWordle(list, word)) {
            succeeded++;
        } else {
            failed++;
        }
    }

    printf("Succeeded: %d\n", succeeded);
    printf("Failed: %d\n", failed);

    for (int i = 0; i < list->count; i++) {
        free(list->words[i]);
    }
    freeList(list);
    
    return 0;
}
