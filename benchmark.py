import subprocess
import time


TRIAL_COUNT = 30

LANGUAGES = ["C", "Epsilon", "Rust", "C#", "Python"]
CMDS = {
    "Csharp": "mono Csharp/Main.exe",
    "Rust": "Rust/main",
    "Epsilon": "Epsilon/main",
    "C": "C/main",
    "Python": "python -OO Python/main.py"
}


def measure_time(language):
    start = time.perf_counter()
    subprocess.call(CMDS[language], shell=True, stdout=subprocess.DEVNULL)
    return time.perf_counter() - start


def main():
    results = [[None for i in range(TRIAL_COUNT)] for language in LANGUAGES]
    for trial in range(TRIAL_COUNT):
        print("Trial", trial)
        for j, language in enumerate(LANGUAGES):
            duration = measure_time(language)
            results[j][trial] = duration
    for row in results:
        print(",".join([str(round(val, 2)) for val in row]))


if __name__ == "__main__":
    main()
