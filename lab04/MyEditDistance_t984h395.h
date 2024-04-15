#ifndef _MY_EDIT_DISTANCE_H_
#define _MY_EDIT_DISTANCE_H_

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

/*------------------------------------------------------------------------------
    EditDistance: find the minimum number of edits that converts one string to another

        str1: the first input string, has an alphabet of [A, C, G, T]
        str2: the second input string, has an alphabet of [A, C, G, T]
        operations: the list of edit operations as string:
            [M] for match, [C] for convert, [I] for insert, [D] for delete

        returns the number of edit distance
------------------------------------------------------------------------------*/
unsigned int EditDistance(
    const std::string &str1,
    const std::string &str2, std::string &operations)
{
    /*------ CODE BEGINS ------*/
    size_t len1 = str1.length();
    size_t len2 = str2.length();
    std::vector<std::vector<int>> dp(2, std::vector<int>(len2 + 1));

    // Initialize the first row of the DP table for insertions
    for (size_t j = 0; j <= len2; ++j)
    {
        dp[0][j] = j;
    }

    // Fill the DP table using only two rows
    for (size_t i = 1; i <= len1; ++i)
    {
        dp[i % 2][0] = i; // Deletions from str1 to match empty str2 prefix
        for (size_t j = 1; j <= len2; ++j)
        {
            int cost = (str1[i - 1] == str2[j - 1]) ? 0 : 1;
            dp[i % 2][j] = std::min({
                dp[(i - 1) % 2][j - 1] + cost, // Replace or match
                dp[(i - 1) % 2][j] + 1,        // Delete from str1
                dp[i % 2][j - 1] + 1           // Insert into str1
            });
        }
    }

    // Reconstruct operations from the DP table
    operations = "";
    size_t i = len1, j = len2;
    while (i > 0 && j > 0)
    {
        if (str1[i - 1] == str2[j - 1] && dp[i % 2][j] == dp[(i - 1) % 2][j - 1])
        {
            operations = 'M' + operations; // Match
            i--;
            j--;
        }
        else if (dp[i % 2][j] == dp[(i - 1) % 2][j] + 1)
        {
            operations = 'D' + operations; // Delete
            i--;
        }
        else if (dp[i % 2][j] == dp[i % 2][j - 1] + 1)
        {
            operations = 'I' + operations; // Insert
            j--;
        }
        else
        {
            operations = 'C' + operations; // Substitute
            i--;
            j--;
        }
    }
    while (i > 0)
    {
        operations = 'D' + operations;
        i--;
    } // Clean up remaining deletions
    while (j > 0)
    {
        operations = 'I' + operations;
        j--;
    } // Clean up remaining insertions

    return dp[len1 % 2][len2];
    /*------ CODE ENDS ------*/
}

/*------------------------------------------------------------------------------
    PrintAlgnment: prints the two aligned sequences and the corresponding operations
        in the alignment form to stdout

        str1: the first input string, has an alphabet of [A, C, G, T]
        str2: the second input string, has an alphabet of [A, C, G, T]
        operations: the list of edit operations as string:
            [M] for match, [C] for convert, [I] for insert, [D] for delete

    The alignment output should contain three rows:
        The first row corresponds to the first sequence with gaps
        The second row corresponds to the list of operations
        The third row corresponds to the second sequence with gaps
        A match [M] operation should be represented using '|'
        A convert [C] operation should be represented using '*'
        Insert and delete operations should be represented using ' ' (empty space)

    Example:
        str1: "ACAACC"
        str2: "CAAAAC"
        operations: "DMMMICM"

        output alignment:
        ACAA-CC
         ||| *|
        -CAAAAC
------------------------------------------------------------------------------*/
void PrintAlignment(
    const std::string &str1,
    const std::string &str2,
    const std::string &operations)
{
    std::string align1, align2, alignOps;
    size_t index1 = 0, index2 = 0;

    for (char op : operations)
    {
        switch (op)
        {
        case 'M':
            align1 += str1[index1];
            align2 += str2[index2];
            alignOps += '|';
            index1++;
            index2++;
            break;
        case 'C':
            align1 += str1[index1];
            align2 += str2[index2];
            alignOps += '*';
            index1++;
            index2++;
            break;
        case 'I':
            align1 += '-';
            align2 += str2[index2];
            alignOps += ' ';
            index2++;
            break;
        case 'D':
            align1 += str1[index1];
            align2 += '-';
            alignOps += ' ';
            index1++;
            break;
        }
    }

    std::cout << align1 << std::endl;
    std::cout << alignOps << std::endl;
    std::cout << align2 << std::endl;
}

#endif
