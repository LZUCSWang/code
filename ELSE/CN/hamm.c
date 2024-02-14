/*
 * @Author: WangXianYi
 * @School: LZU
 * @Date: 2023-10-18 09:02:12
 * @Description:
 */
#include <stdio.h>
int i;
// Function to calculate the parity of a given bit position
int calculate_parity(int data, int position)
{
    int parity = 0;
    for (i = 1; i <= data; i <<= 1)
    {
        if (i & position)
        {
            parity ^= 1;
        }
    }
    return parity;
}

// Function to correct errors in the received Hamming code
void correct_hamming_code(int *received_code, int code_length)
{
    int error_position = 0;
    int parity_check = 0;

    // Calculate the parity of each position
    for (i = 1; i <= code_length; i <<= 1)
    {
        int parity = 0;
        for (int j = i; j <= code_length; j++)
        {
            if (j & i)
            {
                parity ^= received_code[j - 1];
            }
        }
        if (parity != received_code[i - 1])
        {
            error_position += i;
            parity_check = 1;
        }
    }

    if (parity_check)
    {
        printf("Error detected at position %d.\n", error_position);
        received_code[error_position - 1] ^= 1; // Correct the error by flipping the bit
        printf("Corrected Hamming code: ");
        for (int i = 0; i < code_length; i++)
        {
            printf("%d", received_code[i]);
        }
        printf("\n");
    }
    else
    {
        printf("No errors detected.\n");
    }
}

// int main() {
//     int received_code[] = {1, 0, 1, 1, 0, 0, 1}; // Replace this with the received Hamming code
//     int code_length = 7; // Replace this with the length of your Hamming code

//     printf("Received Hamming code: ");
//     for (i = 0; i < code_length; i++) {
//         printf("%d", received_code[i]);
//     }
//     printf("\n");

//     correct_hamming_code(received_code, code_length);

//     return 0;
// }
int main()
{
    int received_code[] = {1, 0, 1, 1, 0, 0, 1};
    int code_length = 7;
    printf("Received Hamming code:");
    for (i = 0; i < code_length; i++)
    {
        printf("%d", received_code[i]);
    }
}