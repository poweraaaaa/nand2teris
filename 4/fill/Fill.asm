// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

//// Replace this comment with your code.
(START)
@24575
D=A
@0
M=D
@SCREEN
D=A
@1
M=D
@KBD
D=M
@CLEAR
D;JEQ
@BLACK
0;JMP


(BLACK)
@1
D=M                                                                                  
A=D
M=-1

@0
D=M
@1
M=M+1
D=D-M
@BLACK
D;JGE
@START
0;JMP


(CLEAR)
@1
D=M
A=D
M=0

@0
D=M
@1
M=M+1
D=D-M
@CLEAR
D;JGE
@START
0;JMP

