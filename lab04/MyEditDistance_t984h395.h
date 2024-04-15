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
    size_t len1 = str1.length(), len2 = str2.length();
    std::vector<std::vector<int>> dp(len1 + 1, std::vector<int>(len2 + 1));

    // Initialize DP table
    for (size_t i = 0; i <= len1; ++i)
        dp[i][0] = i;
    for (size_t j = 0; j <= len2; ++j)
        dp[0][j] = j;

    // Fill DP table
    for (size_t i = 1; i <= len1; ++i)
    {
        for (size_t j = 1; j <= len2; ++j)
        {
            int cost = (str1[i - 1] == str2[j - 1]) ? 0 : 1;
            dp[i][j] = std::min({dp[i - 1][j - 1] + cost, dp[i][j - 1] + 1, dp[i - 1][j] + 1});
        }
    }

    // Trace back to find the operations
    size_t i = len1, j = len2;
    operations.clear();
    while (i > 0 && j > 0)
    {
        if (dp[i][j] == dp[i - 1][j - 1] && str1[i - 1] == str2[j - 1])
        {
            operations = 'M' + operations;
            i--;
            j--;
        }
        else if (dp[i][j] == dp[i - 1][j - 1] + 1)
        {
            operations = 'S' + operations;
            i--;
            j--;
        }
        else if (dp[i][j] == dp[i][j - 1] + 1)
        {
            operations = 'I' + operations;
            j--;
        }
        else
        {
            operations = 'D' + operations;
            i--;
        }
    }
    while (i > 0)
    {
        operations = 'D' + operations;
        i--;
    }
    while (j > 0)
    {
        operations = 'I' + operations;
        j--;
    }

    return dp[len1][len2];
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
    size_t i = 0, j = 0, opIndex = 0;

    while (opIndex < operations.size())
    {
        if (operations[opIndex] == 'M')
        {
            align1 += str1[i];
            align2 += str2[j];
            alignOps += '|';
            i++;
            j++;
        }
        else if (operations[opIndex] == 'S')
        {
            align1 += str1[i];
            align2 += str2[j];
            alignOps += '*';
            i++;
            j++;
        }
        else if (operations[opIndex] == 'I')
        {
            align1 += '-';
            align2 += str2[j];
            alignOps += ' ';
            j++;
        }
        else
        { // 'D'
            align1 += str1[i];
            align2 += '-';
            alignOps += ' ';
            i++;
        }
        opIndex++;
    }

    std::cout << align1 << std::endl;
    std::cout << alignOps << std::endl;
    std::cout << align2 << std::endl;
}

#endif
