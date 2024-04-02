# Procedure to Benchmark

* Open a Linux computer, with `nix` installed
* Open `bash`
* Install the `nix` packages `llvmPackages.clangUseLLVM`, `python310`,  `python310Packages.virtualenv`, `llvmPackages_14.libllvm`, `rustc`, and `mono5`
* Git clone this repo with the command `git clone https://github.com/budopod1/epsilon-comparison.git`
* Setup the comparison with `./setup.bash`
* Compile all programs with `./compile.bash`
* Benchmark all programs with `python benchmark.bash`, which will automatically perform 30 trials
* Save the results as CSV file
* Compute the average run time, standard deviation, and 95% confidence interval for each language
