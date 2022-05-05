# Reversi-Game
C++ Reversi Game Simulation

General Overview (most info is commented in actual code)

The Game of FlipFlop is a strategy oriented board game with the following rules:
1. The game begins on a board of N squares by N squares. N must be at least 8 and N must be even,
2. The game is played by two players using game pieces that are placed on the squares of the board.
One player uses white game pieces; the other player uses black game pieces.
3. White moves first.
4. The game ends when of the conditions below is true
a.The black player has taken N^2/2 turns
b.When a player plays 0 game pieces and their opponent then also plays 0 game pieces


White and Black are both trying to capture as many spaces as possible. Capturing 2 or more opposite color spaces results in a second turn if the user chooses to do so. 
The game will give error feedback if user inputs incorrect value or board space. 
