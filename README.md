# CCPROG1-MP
CCPROG1 MP. Year 1, Term 1

Program Description:
		
	-This program simulates 10 weeks of strategic resource management where the user produces
	 and sells Energon Cubes to accumulate raw Energon.
	-The goal is to accumulate 1 million Energon by the end of week 10.
	-The main gameplay loop involves the production phase (Day 1) and selling phase (Day 2 - 7).
	
	Mechanics:
	
	1. General
	
	-Default starting Energon level is 10,000 and the game starts at Week 1 Day 1.
	-Dev feature can be activated before the game starts to modify starting Energon and Week.
	-Energon Cubes can only be produced and sold in stacks of 10.
	-The week will automatically skip to the next if no stacks can be sold.
	
	2. Production 
	
	-The production cost is randomly generated at the start of each week.
	-Production cost can be between 80 and 120 (inclusive).
	
	3. Selling
	
	-Swindle's prices change daily depending on the Energon Surge Trend (EST).
	-EST is randomized at the start of each week and cannot repeat in consecutive weeks.
	-There is an option to display the weekly EST before the game starts.
	
	4. Expiring
	
	-Stacks not sold before the end of each week will expire.
	-Expired stacks can still be sold but only at a rate of 200 per stack.
	
	5. Game Over
	
		Victory
		- The user accumulates over 1 million Energon by the end of the 10th week.
	
		Defeat
		-The game will end if there is not enough Energon (800) to produce atleast one stack.
		-The user does not reach 1 million Energon by the end of the 10th week.
	
	|Production phase (Day 1)|
	
	-User can produce stacks of Energon Cubes
	-The EST is randomly generated.
	-The EST will be displayed if activated before the game, otherwise it is invisible.

	|Selling phase (Day 2 - 7)|
	
	-Swindle's prices are randomly generated depending on the EST.
	-User can sell stacks of Energon Cubes to Swindle.
	-Unsold stacks expire at the end of the week.
	-User can sell expired stacks as long as Swindle's Shop is open.

		
	Programmed by: Adrian Matthew L. Dee, S25A
	Last Modified: November 24, 2024
	Version: 1.0
