## MineSweeper-Clone
     Minesweeper is a single-player puzzle game. The objective of the game is to predetermine Mines placed in a cell.

# Rule :
     1. The board is devided into cell, With Mines (10) randomly distributed.
     2. To Win, you need to open all the Cell. 
     3. You will loose, if you open Mines cell.
     4. After opening cell the number on Cell represent the number of Mines adjecent to it.
        Using this information you can determine Cells are safe or contain Mines.
     5. If open cell has number '0', then its adjecent cell doesn't have any Mines.
     5. If you think that in perticular cell could be a Mine , You can set that cell as a flag.

# How to Play :
     1. Select option - 
          1) Open Cell - To open a new Cell. "<<endl;
          2) Set Flag - If cells not safe to open, you can mark it as flag.
     2. Enter Row and Coloum number to open or set Flag.
