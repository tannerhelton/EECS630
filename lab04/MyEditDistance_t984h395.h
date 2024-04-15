#ifndef _MY_EDIT_DISTANCE_H_
#define _MY_EDIT_DISTANCE_H_

#include <iostream>
#include <string>
#include <vector>
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
    int len1 = str1.size();
    int len2 = str2.size();
    std::vector<std::vector<int>> dp(len1 + 1, std::vector<int>(len2 + 1));

    // Initialize the matrix
    for (int i = 0; i <= len1; i++)
    {
        for (int j = 0; j <= len2; j++)
        {
            if (i == 0)
                dp[i][j] = j; // Cost of insertions
            else if (j == 0)
                dp[i][j] = i; // Cost of deletions
            else
            {
                int match = dp[i - 1][j - 1] + (str1[i - 1] == str2[j - 1] ? 0 : 1);
                int insert = dp[i][j - 1] + 1;
                int deleteOp = dp[i - 1][j] + 1;
                dp[i][j] = std::min({match, insert, deleteOp});
            }
        }
    }

    // Traceback to find the operations
    operations.clear();
    int i = len1, j = len2;
    while (i > 0 || j > 0)
    {
        if (i > 0 && j > 0)
        {
            if (dp[i][j] == dp[i - 1][j - 1] + (str1[i - 1] != str2[j - 1]))
            {
                // Prefer match/mismatch first
                operations = (str1[i - 1] == str2[j - 1] ? 'M' : 'C') + operations;
                i--;
                j--;
            }
            else if (dp[i][j] == dp[i][j - 1] + 1)
            {
                // Then consider insertion
                operations = 'I' + operations;
                j--;
            }
            else
            {
                // Finally consider deletion
                operations = 'D' + operations;
                i--;
            }
        }
        else if (i > 0)
        {
            operations = 'D' + operations;
            i--;
        }
        else if (j > 0)
        {
            operations = 'I' + operations;
            j--;
        }
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
    std::string aligned1, aligned2, alignedOps;
    int i = 0, j = 0;
    for (char op : operations)
    {
        switch (op)
        {
        case 'M':
            aligned1 += str1[i];
            aligned2 += str2[j];
            alignedOps += '|';
            i++;
            j++;
            break;
        case 'C':
            aligned1 += str1[i];
            aligned2 += str2[j];
            alignedOps += '*';
            i++;
            j++;
            break;
        case 'I':
            aligned1 += '-';
            aligned2 += str2[j];
            alignedOps += ' ';
            j++;
            break;
        case 'D':
            aligned1 += str1[i];
            aligned2 += '-';
            alignedOps += ' ';
            i++;
            break;
        }
    }

    std::cout << aligned1 << std::endl;
    std::cout << alignedOps << std::endl;
    std::cout << aligned2 << std::endl;
}

#endif
