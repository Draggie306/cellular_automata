# Generating one-dimenstional cellular automata in ANSI C

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)](https://github.com/draggie306/cellular-automata)
[![ANSI C](https://img.shields.io/badge/ANSI-C-blue.svg)](https://en.wikipedia.org/wiki/ANSI_C)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

A high-performance implementation of Elementary Cellular Automata (ECA) following Stephen Wolfram's rule system, implemented in pure ANSI C.

The output of the program is an ASCII representation of the cellular automaton, where each cell is represented by a `*` character. The program is designed to be run in a terminal, where the output can be displayed in a grid.

*No libraries, other than the standard IO, string and stdlib libraries, are used in this implementation. The program is written in ANSI C and will compile on any platform with a C compiler.*

>Can't run the program? No worries, you can check out [this demo video](https://youtu.be/F4OrqiIg3Lc) to see the program in action!

## Table of Contents
- [Background](#background)
- [Examples](#examples)
- [Technical overview](#technical-overview)
  - [Rule evaluation](#rule-evaluation)
  - [Performance considerations](#performance-considerations)
- [Compiling and Running](#compiling-and-running)
- [Usage](#usage)
- [Extra reading pointers - the Game of Life](#extra-reading-pointers---the-game-of-life)
- [Further development](#further-development)
- [Contributing](#contributing)
- [License](#license)

## Background

[Cellular automata](https://en.wikipedia.org/wiki/Cellular_automaton) are fascinating models which have been studied extensively and have a wide range of applications in many fields. 

They have a long history in mathematics and computer science and were first discovered in the 1940s by John von Neumann and Stanislaw Ulam, two of the founding fathers of computer science. Since then they have found many applications in diverse field including artificial life, physics and biology. While simple to describe, they are capable of generating amazingly complex behaviour, including chaotic dynamics and universal computation.


## Examples
Rule 110 is particularly interesting as it's proven to be Turing complete:
```bash
$ ./Cellular-Automata 30 20 110
               *
              **
             ***
            ** *
           *****
          **   *
         ***  **
        ** * ***
       ******* *
      **     ***
     ***    ** *
    ** *   *****
   *****  **   *
  **   * ***  **
 ***  **** * ***
** * **  ***** *
******* **   ***             *
      ****  ** *            **
     **  * *****           ***
    *** ****   *          ** *
```

Rule 210 demonstrates fractal-like pattern generation.
```bash
./Cellular-Automata 50 50 210
                         *                        
                        * *                       
                       *   *                      
                      * * * *                     
                     *       *                    
                    * *     * *                   
                   *   *   *   *                  
                  * * * * * * * *                 
                 *               *                
                * *             * *               
               *   *           *   *              
              * * * *         * * * *             
             *       *       *       *            
            * *     * *     * *     * *           
           *   *   *   *   *   *   *   *          
          * * * * * * * * * * * * * * * *         
         *                               *        
        * *                             * *       
       *   *                           *   *      
      * * * *                         * * * *     
     *       *                       *       *    
    * *     * *                     * *     * *   
   *   *   *   *                   *   *   *   *  
  * * * * * * * *                 * * * * * * * * 
 *               *               *               *
```

Rule 30 generates a chaotic pattern.
```bash
./Cellular-Automata 50 50 30
                         *                        
                        ***                       
                       **  *                      
                      ** ****                     
                     **  *   *                    
                    ** **** ***                   
                   **  *    *  *                  
                  ** ****  ******                 
                 **  *   ***     *                
                ** **** **  *   ***               
               **  *    * **** **  *              
              ** ****  ** *    * ****             
             **  *   ***  **  ** *   *            
            ** **** **  *** ***  ** ***           
           **  *    * ***   *  ***  *  *          
          ** ****  ** *  * *****  *******         
         **  *   ***  **** *    ***      *        
        ** **** **  ***    **  **  *    ***       
       **  *    * ***  *  ** *** ****  **  *      
      ** ****  ** *  ******  *   *   *** ****     
     **  *   ***  ****     **** *** **   *   *    
    ** **** **  ***   *   **    *   * * *** ***   
   **  *    * ***  * *** ** *  *** ** * *   *  *  
  ** ****  ** *  *** *   *  ****   *  * ** ****** 
 **  *   ***  ****   ** *****   * ***** *  *     *
 ```


## Technical overview

The implementation uses:
- Bit manipulation for rule application
- Circular boundary conditions for edge cells
- Dynamic malloc for generation arrays
- Fast binary-to-decimal conversion for rule application

### Rule evaluation

As expected, the generation of each cell is determined by the state of its left and right neighbors to form a 3-bit binary number. For example, if the neighborhood is `1 0 1`, this sequence is first treated as a binary (written as `101`). The conversion is then done by the `convert_binary_decimal` function, which processes each digit from right to left, applying increasing powers of 2.


The main evolution loop performs the following steps:
1. For each cell, determine the state of its left and right neighbors, applying circular wrap-around to handle edge cases.
2. Construct a three-digit binary number from the neighboring cells.  
3. Convert this binary number to a decimal index using [`convert_binary_decimal`](Cellular-Automata.c#L123).
4. Right-shift the given Wolfram rule (`wolfram_code_binary`) by this decimal index.  
5. Extract the new state by obtaining the least-significant bit using a bitwise AND.


### Performance considerations
- Bit operations are used to apply cell rules for speed
- Two static generation arrays are used to store the current and next generations
- O(width × generations) time complexity
- O(width) space complexity

## Compiling and Running

To build, you will need a C compiler, such as `gcc` or `clang`. To compile the program, run the following command in the terminal:

```sh
$ gcc -Wall -ansi -pedantic-errors -o Cellular-Automata Cellular-Automata.c
```

## Usage
```bash
./Cellular-Automata <width> <generations> <rule>

# Arguments:
# width         - Number of cells in each generation (1-N)
# generations   - Number of generations to evolve (1-N) 
# rule          - Wolfram code between 0-255
```

### Extra reading pointers - the Game of Life

If you're as fascinated as I am about cellular automata, then have a look at John Conway's [Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life), the most famous 2D cellular automaton. Implementing and exploring this cellular automaton is lots of fun, see [this video](https://www.youtube.com/watch?v=C2vgICfQawE) for some examples of what is possible in the Game of Life. More implementation details can be found in Section 7.6 of [this chapter](http://natureofcode.com/book/chapter-7-cellular-automata/).


## Further development
I would LOVE to make this into a more accessible web-based tool, where users can interactively change the rule and see the automaton evolve in real-time. However, alas, that is a project for another day. 


## Contributing
If you have any suggestions, improvements or bug fixes, please feel free to open an issue or create a pull request. I would be happy to review and merge them.

## License
This project is licensed under the MIT License.