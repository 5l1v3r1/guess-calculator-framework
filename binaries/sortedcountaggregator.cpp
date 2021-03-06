// sortedcountaggregator.cpp - read in a table of the type generated by
//   GeneratePatterns from stdin, sorted in decreasing order, and output
//   lines with counts accumulated
//
// Use of this source code is governed by the GPLv2 license that can be found
//   in the LICENSE file.
//
// Version 0.2
// Author: Saranga Komanduri
//
// Modified: Thu Sep 11 12:17:50 2014
//

// This class is fairly crude and I iterated on it a few times before
// arriving at the code below.  It seems too slow for code that just
// takes in input and produces almost the same output, but perhaps the
// GMP calls are necessarily slow. With cin.sync_with_stdio(false) it is
// significantly faster.
//
// The code was written will before the OOP code in the rest of the
// framework, so it is not as strictly written.  For example, I use
// "using namespace std" here which is not used in any of the newer code.
// Overall, the code could definitely use revision.
//

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <gmp.h>

using namespace std;

int main(int argc, char *argv[]) {
  string inputLine;
  char accstring[255];
  mpz_t acc;
  mpz_t cur;
  mpz_init_set_ui(acc,1);   // Start at the first guess
  mpz_init(cur);
  int marker1, marker2;
  double prob, last_prob = 1;
  string curTerm;

  cin.sync_with_stdio(false);  // This makes line-by-line reading from stdin significantly faster!

  while (getline(cin,inputLine)) {
    mpz_set_ui(cur,0);
    // Find the counter
    marker1 = inputLine.find("\t");
    // Probability is the first field
    prob = strtod((inputLine.substr(0, marker1)).c_str(), NULL);
    //cout << inputLine.substr(0, marker1) << endl;

    // Make sure probabilities are always decreasing
    if (last_prob < prob) {
      fprintf(stderr, "Found instance where input table is not sorted by "
                      "decreasing probability! Found probability %a followed "
                      "by %a!\n", last_prob, prob);
      exit(EXIT_FAILURE);
    }

    // Count is the second field
    marker2 = (inputLine.substr(marker1+1, inputLine.size())).find("\t");
    mpz_set_str(cur,(inputLine.substr(marker1+1,marker2)).c_str(), 10);
    //cout << inputLine.substr(marker1+1,marker2) << endl;

    // Terminal string is the third field and goes to the end of the line
    curTerm = inputLine.substr(marker1+marker2+2, inputLine.size());
    //cout << curTerm << endl;

    mpz_get_str(accstring, 10, acc);
    printf("%a\t%s\t%s\n", prob, accstring, curTerm.c_str());
    // cout << prob << "\t" << acc << "\t" << curTerm << endl;

    mpz_add(acc, acc, cur);
    last_prob = prob;
  }

  mpz_sub_ui(acc, acc, 1);  // Adjust total count by 1 because acc is actually the index of the next guess, but there is no next guess at the end of the file
  mpz_get_str(accstring, 10, acc);
  printf("Total count\t%s\n", accstring);
  
  exit(0);
}
