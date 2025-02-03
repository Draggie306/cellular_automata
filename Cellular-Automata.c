#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int convert_binary_decimal(int binary_num);

int main(int argc, char *argv[])
{
    /* argvs */
    int cells_in_gen = 0, generations_number = 0, wolfram_code_binary = 0;

    /* loops */
    int i, left_neighbour, right_neighbour, current_gen_index=0;

    /* 3 bits */
    int three_bits = 0, neighbours_decimal = 0;
    unsigned char shifted_rule_num = 0;

    /* arrays */
    int *current_generation, *next_generation;

    /* some stupid thing */
    char *endptr;

    /*
    cells_in_gen = 10;
    generations_number = 20;
    wolfram_code_binary = 101;
    */

    
    if (!(argc == 4)) {
        printf("incorrect arguments inputted\n");
        return -1;
    }

    cells_in_gen = strtol(argv[1], &endptr, 10);
    generations_number = strtol(argv[2], &endptr, 10);
    wolfram_code_binary = strtol(argv[3], &endptr, 10);


    if (generations_number < 1 || cells_in_gen < 1) {
        printf("Cannot evolve over negative generations.\n");
        return -1;
    }

    if (wolfram_code_binary <0 || wolfram_code_binary >255) {
        printf("Wolfram code must be between 0 and 255.");
        return -1;
    }

    /*return 0;*/

    /*
    cells_in_gen = 8;
    generations_number = 40;
    wolfram_code_binary = 110;
    */

    /*
    printf("Wolfram code binary: %d\n", wolfram_code_binary);

    printf("the number of cells in the one-dimensional grid: %d\n", cells_in_gen);
    printf("the number of generations to evolve: %d\n", generations_number);
    printf("wolfram code ruleset to evolve with: %d\n", wolfram_code_binary);
    */

    if (!(current_generation = (int *) calloc(cells_in_gen, sizeof(int)))) 
    {
        printf("unable to allocate memory for current_generation\n");
        return -1;
    }


    if (!(next_generation = (int *) calloc(cells_in_gen, sizeof(int)))) 
    {
        printf("unable to allocate memory for next_generation\n");
        return -1;
    }

    current_generation[(cells_in_gen/2)] = 1;

    /* Outer loop: iterate over each generation*/
    for (current_gen_index = 0; current_gen_index < generations_number; current_gen_index++) {
        
        
        for (i = 0; i < cells_in_gen; i++) {
            /* Inner loop: iterate over each cell in*/    


            /* Apply wrap-around for the array */
            if (i == 0) {
                /* Test case for not looking out of the array lower bounds */
                left_neighbour = cells_in_gen - 1;
                right_neighbour = i + 1;
            }
            else if (i == cells_in_gen-1)
            {
                /* and case for when will increase bounds to above array length */
                right_neighbour = 0;
                left_neighbour = i - 1;
            }
            else 
            {
                left_neighbour = i - 1;
                right_neighbour = i + 1;
            }

            /* assemble binary number */
            three_bits = current_generation[left_neighbour];
            three_bits = three_bits * 10;
            three_bits = three_bits + current_generation[i];
            three_bits = three_bits * 10;
            three_bits = three_bits + current_generation[right_neighbour];

            /* First, treat 101 as a binary number and convert it to decimal */

            neighbours_decimal = convert_binary_decimal(three_bits);

            /* Right shift rule number by the integer of cell neighbours  */
            shifted_rule_num = (wolfram_code_binary >> neighbours_decimal);

            /*  
                Look at the value of the least significant bit i.e. 0. 
                This is the state of the cell in the next generation. 
            */

            next_generation[i] = shifted_rule_num & 1;

            if (current_generation[i] == 1) {
                printf("*");
            } else {
                printf(" ");
            }
        }

        printf("\n");
        /* Now out of inner loop, copy next_generation to current_generation */
        
        for (i = 0; i < cells_in_gen; i++) {
            current_generation[i] = next_generation[i];
        }
    }

    /*
        iterate over each generation.
        for each, iterate over the cells.
        compare the state of the cells to its neighbours
        calculate the state for next generation, and store in their array.
        once done, print out next generation.
    */


    free(current_generation);
    free(next_generation);

    return 0;
}

int convert_binary_decimal(int binary_num)
{
    int decimal_value = 0, base_value = 1, last_digit=0;
    int tmp = binary_num;

    while(tmp) {
        last_digit = tmp % 10; /* Get (least significant) digit */

        tmp = tmp/10;

        decimal_value += last_digit * base_value; /* */
        base_value = base_value*2;
    }

    return decimal_value;
}

/*
int convert_dec_to_binary(int decimal)
{ 

}
*/
