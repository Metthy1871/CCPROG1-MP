/*	
	This is to certify that this project is my own work, based on my personal efforts
	in studying and applying the concepts learned. I have constructed the
	functions and their respective algorithms and corresponding code by myself.
	The program was run, tested, and debugged by my own efforts. I further
	certify that I have not copied in part or whole or otherwise plagiarized the
	work of other students and/or persons.
		
	Adrian Matthew L. Dee, DLSU ID# 12409359
*/

/*
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
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/*
	This function allows for the modification of starting Energon and Week. 
	
	@param *storage - Pointer to the current amount of Energon.
	@param *week - Pointer to the current week.
*/

void devFeature(int *storage, int *week){
	
	char dev;
	
	do{
			
		printf("\nActivate Dev Feature (y/n)?  ");
		scanf(" %c", &dev);
		
		if(dev == 'y' || dev == 'Y'){
				
			printf("Starting Energon: ");
			scanf("%d", storage);
			
			//storage must be non-negative
			if(*storage < 0)
				printf("Invalid Input\n");
			
			else{
					
				printf("Starting Week: ");
				scanf("%d", week);
					
					//week must be between 1 and 10, inclusive
					if(*week < 1 || *week > 10)
						printf("Invalid Input\n");
			}
		}
		
	} while((*storage < 0 || *week < 1 || *week > 10) && (dev == 'y' || dev == 'Y'));
}

/*
	This function allows for the weekly EST to be displayed. 
	
	@return - returns inputted decision.
*/

char checkEST(){
	
	char viewTrendDecision;
	
	printf("Display Energon Surge Trend every week (y/n)? ");
	scanf(" %c", &viewTrendDecision);
	
	printf("\n");
	
	return viewTrendDecision;
}

/*
	This function displays and updates the current week and day. 
		
	Precondition: Week does not exceed 10.
	
	@param *week - Pointer to the current week.
	@param *day - Pointer to the current day.
*/

void calendar(int *week, int *day){
	
	printf("Week %d Day %d \n", *week, *day);	

	(*day) ++; //increment day each time the function is called
	
	if(*day > 7){
		
   	    (*day) = 1; //day is reset to 1 once it exceeds 7 
    	(*week) ++; //week is incremented after 7 days pass
    }
}

/*
	This function displays the remaining amount of Energon and stacks of Energon Cubes.
	
	Precondition: Storage and stacks are non-negative values.
	
	@param storage - The current amount of Energon.
	@param stacks - The current amount of Stacks.
*/

void energonStorage(int storage, int stacks){
	
	printf("Energon Storage: %d \t Stacks: %d\n\n", storage, stacks); 
}

/*
	This function generates a random production cost between 80 and 120, inclusive.
	
	@return - returns the generated production cost.
*/

int generateProductionCost(){
	
	return (rand()% 41)+ 80;
}

/*
	This function checks if a decision (character) input is valid.
	
	@param decision - Decision input.
	
	@return - returns 1 if decision is invalid, returns 0 otherwise.
*/

int checkDecision(char decision){
	
	return decision != 'y' && decision != 'Y' && decision != 'n' && decision != 'N';
}

/*
	This function checks if an integer input is valid and if a decision input is 'y' or 'Y'
	
	Precondition: Input and stacks must be non-negative values.
	
	@param input - Integer input.
	@param *stacks - Pointer to the current number of stacks.
	@param decision - Decision input.
	
	@return - returns 1 if input is invalid, returns 0 otherwise.
*/

int checkInput(int input, int *stacks, char decision){
		
	return input > *stacks && (decision == 'y' || decision == 'Y');
}

/*
	This function runs the Cube production phase of the game.
		
	Precondition: Production cost and Storage must be non-negative value,
	Day must be equal to 1, and Week must not be greater than 10.
	
	@param productionCost - The cost of producing one Energon Cube
	@param *storage - Pointer to the remaining amount of Energon
	@param *stacks - Pointer to the remaining number of Stacks
*/
		
void cubeProduction(int productionCost, int *storage, int *stacks){
	
	int produceStacks, stackCost;
	char decision;
	
	stackCost = productionCost * 10;
	
	printf("Production cost for this week is %d Energon for 1 Cube.\n", productionCost);
	printf("It will cost %d Energon to produce 1 stack.\n", stackCost);
	
	do{
		printf("\nHow many stacks do you wish to produce for this week? ");
		scanf("%d", &produceStacks);
		
		//check for negative inputs
		if(produceStacks < 0)
			printf("\nInvalid input, please try again\n");
			
		else if(produceStacks == 1){
			
			printf("%d stack will cost %d Energon, proceed?(y/n) ", produceStacks, stackCost * produceStacks);
			scanf(" %c", &decision);
		}
	
		else{
			
			printf("%d stacks will cost %d Energon, proceed?(y/n) ", produceStacks, stackCost * produceStacks);
			scanf(" %c", &decision);
		}
		
		//check for invalid inputs
		if(checkDecision(decision) == 1)
			printf("Invalid input, please try again\n");
		
		//check if there is enough Energon to produce inputted number of Stacks
		else if(checkInput(produceStacks, stacks, decision) == 1)
			printf("You do not have enough Energon to produce %d stacks\n", produceStacks);
	
	/*loop will continue if decision input is not y or Y,there is not enough -
	Energon to produce the inputted number of Stacks, or if produceStacks input is invalid*/
	} while((decision != 'y' && decision != 'Y') || (stackCost * produceStacks > *storage) || produceStacks < 0);
	
	if(produceStacks == 1)
		printf("\n%d stack produced\n", produceStacks);

	else
		printf("\n%d stacks produced\n", produceStacks);
	
	//update the amount of remaining Energon and Stacks
	*storage -= stackCost * produceStacks;
	*stacks  += produceStacks;
}	

/*
	This function generates the Energon Surge Trend (EST) for the week.
	
	Precondition: Day is equal to 1 and Week has not exceeded 10.
	
	@param *currentEST - Pointer to the current EST.
	
	@return - returns the newly generated EST.
*/

int surgeTrend(int *currentEST){
	
	int eST;
	
	do{
		
		eST = (rand()% 3) + 1; //generate random number between 1 - 3, inclusive
		
	//repeat the randomizer if the new trend is the same as the current trend
	} while(eST == *currentEST);
	
	*currentEST = eST; //set currentEST to the newly generated eST
	
	return eST;
}

/*
	This function displays the Energon Surge Trend for the week.
	
	Precondition: viewEST was set to 'y' or 'Y' at the start of the game.
	
	@param eST - The current Energon Surge Trend.
*/

void displayEST(int eST){
	
	printf("\nCurrent Trend: ");
		
	switch(eST){
		
		case 1:
			printf("Scrap Trend\n");
			break;
			
		case 2:
			printf("Nominal Trend\n");
			break;
			
		case 3:
			printf("Primus Trend\n");
			break;
	}
}

/*
	This function generates Swindle's prices for the week depending on the EST.
	
	Precondition: eST is a value between 1 and 3, inclusive.
	
	@param productionCost - The cost of producing one Energon Cube.
	@param eST - The current surge trend.

	@return - returns the generated sell price.
*/

int surgePrice(int productionCost, int eST){
	
	int minVal, maxVal, sellPrice;
	
	//minimum and maximum sell price changes depending on the EST
	switch(eST){
		
		//scrap trend
		case 1:
				
			minVal = 20;
			maxVal = productionCost - 10;
				
			break;
		
		//nominal trend
		case 2:
				
			minVal = 80;
			maxVal = productionCost * 1.05;
				
			break;
	
		//primus trend
		case 3:
				
			minVal = productionCost;
			maxVal = productionCost * 4;
				
			break;
		}
	
	//sell price randomly generated based on the minimum and maximum values
	sellPrice = (rand() % (maxVal - minVal + 1)) + minVal;
		
	return sellPrice;
}

/*
	This function runs Swindle's Shop
		
	Precondition: Day is not equal to one, Week has not exceeded 10, and 
	productionCost, storage and stacks are all non-negative values.
	
	@param productionCost - The cost of producing one Energon Cube
	@param *storage - Pointer to the remaining amount of Energon
	@param *stacks - Pointer to the remaining number of stacks
*/

void swindle(int sellPrice, int *storage, int *stacks){
		
	int stackPrice = sellPrice * 10;
	
	int sellStacks;
	char sellDecision;
		
	printf("Swindle is buying Energon Cubes for %d Energon per cube\n", sellPrice);
	printf("You can earn %d Energon per Stack\n", stackPrice);
		
	do{
		printf("\nHow many stacks do you wish to sell to Swindle? ");
		scanf("%d", &sellStacks);
			
		//check for negative inputs
		if(sellStacks < 0)
				printf("Invalid input, please try again\n");
			
		//displays "stack" if only 1 stack is sold
		else if(sellStacks == 1){
			
			printf("You will sell %d stack to Swindle, proceed?(y/n) ", sellStacks);
			scanf(" %c", &sellDecision);
		}
			
		//displays "stacks" if more than 1 stack is sold
		else{
			
			printf("You will sell %d stacks to Swindle, proceed?(y/n) ", sellStacks);	
			scanf(" %c", &sellDecision);
		}
		
		//check for invalid inputs
		if(checkDecision(sellDecision) == 1)
			printf("Invalid input, please try again\n");
				
		//checks if there are enough Stacks to be sold
		else if(checkInput(sellStacks, stacks, sellDecision) == 1)
			printf("\nYou do not have enough stacks\n\n");
				
		/*loop will continue if sellDecision is not y or Y, 
		not enough Stacks to sell, or if sellStacks input is invalid*/
		} while((sellDecision != 'y' && sellDecision != 'Y') || (sellStacks > *stacks || sellStacks < 0));
		
	if(sellStacks == 1)
		printf("\n%d stack sold\n", sellStacks);
		
	else
		printf("\n%d stacks sold\n", sellStacks);
		
	printf("You earned %d Energon\n", stackPrice * sellStacks);
		
	//storage and stacks updated
	*storage += stackPrice * sellStacks;
	*stacks  -= sellStacks;
}

/*
	This function handles the recycling of expired stacks.
	
	Precondition: Stacks is greater than 0 and day is equal to 1.
	
	@param *recycleStacks - Pointer to the number of expired Stacks.
	@param *stacks - Pointer to the remaining number of Stacks.
*/

void recycleBin(int *recycleStacks, int *stacks){
	
	printf("\n%d stacks expired and sent to recycle bin\n", *stacks);
	
	//Expired stacks will be stored in recycleStacks
	*recycleStacks += *stacks;
	
	//Stacks reset to 0
	*stacks = 0;
}

/*
	This function allows for the selling of expired stacks.
	
	Precondition: recycleStacks and Storage are non-negative values.
	
	@param *storage - Pointer to the remaining amount of Energon.
	@param *recycleStacks - Pointer to the number of expired Stacks.
*/

void recycleShop(int *storage, int *recycleStacks){
	
	int sellRecycle;
	char recycleDecision;
	
	if(*recycleStacks == 1)
		printf("\nYou have %d stack in the recycle bin, each can be sold for only 200 Energon\n", *recycleStacks);

	else
		printf("\nYou have %d stacks in the recycle bin, each can be sold for only 200 Energon\n", *recycleStacks);
		
	printf("You can earn %d Energon per stack\n", 200);
		
	do{
			
		printf("\nHow many stacks do you wish to sell? ");
		scanf("%d", &sellRecycle);
			
		//check for negative inputs
		if(sellRecycle < 0)
			printf("Invalid input, please try again\n\n");
			
		else if(sellRecycle == 1){
				
			printf("You will sell %d stack, proceed?(y/n) ", sellRecycle);
			scanf(" %c", &recycleDecision);
		}
			
		else{
			
			printf("You will sell %d stacks, proceed?(y/n) ", sellRecycle);
			scanf(" %c", &recycleDecision);
		}
		
		//check for invalid inputs
		if(checkDecision(recycleDecision) == 1)
			printf("Invalid input, please try again\n");
			
		else if(checkInput(sellRecycle, recycleStacks, recycleDecision) == 1)
			printf("\nYou do not have enough stacks\n");
		
		/*loop will continue if recycleDecision is not y or Y, 
		not enough recycleStacks to sell, or if recycleStacks input is invalid*/
		} while((recycleDecision != 'y' && recycleDecision != 'Y') || (sellRecycle > *recycleStacks || sellRecycle < 0));
		
	if(sellRecycle == 1)
		printf("\n%d stack sold\n", sellRecycle);

	else
		printf("\n%d stacks sold\n", sellRecycle);
	
	printf("You earned %d Energon\n", sellRecycle * 200);
	
	//recycled stacks and storage updated
	*recycleStacks -= sellRecycle;
	*storage += sellRecycle * 200;
}

/*
	Description:This function skips to the next week if there are no stacks left.
		
	Precondition: Stacks is equal to zero and Day is equal to one.
	
	@param *week - Pointer to the current week.
	@param *day - Pointer to the current day
*/

void weekSkip(int *week, int *day){
	
		(*week) ++; //week is incremented
		(*day) = 1; //day is reset to 1
		
		printf("The rest of the week was skipped since you don't have stacks.\n");
}

int main()
{
	
	printf("-----------------------------------------------------------------------------------------------------------------\n");
    printf("Greetings, User. I am Soundwave.\n");
    printf("Cybertron, our home, is on the brink of collapse due to the devastation of the Great War.\n");
    printf("We must produce 1,000,000 Energon within the next 10 weeks to fuel our planet’s recovery.\n\n");
    
    printf("MISSION OBJECTIVE: Produce and sell enough Energon cubes to reach 1,000,000 Energon by the end of Week 10.\n\n");
    
    printf("MISSION DETAILS:\n");
    printf("1. Producing Energon Cubes:\n");
    printf("   - Soundwave can only generate Energon Cubes at the start of a week (Day 1).\n");
    printf("   - Cost for producing Energon Cubes varies each week (80 - 120 per Cube).\n");
    printf("   - Soundwave can only produce Cubes in stacks of 10.\n\n");
    
    printf("2. Swindle's Shop:\n");
    printf("   - Swindle's shop will be open for the rest of the week (Days 2-7).\n");
    printf("   - Swindle will buy stacks of Energon cubes in exchange for raw Energon.\n");
    printf("   - Swindle will only buy Energon cubes in stacks.\n");
    printf("   - Swindle's prices will change daily depending on the current surge trend.\n");
    printf("   - The surge trend will change weekly.\n\n");

    printf("3. Expiration and recycling:\n");
    printf("   - Energon Cubes not sold before the end of the week will expire and be sent to the recycling bin.\n");
    printf("   - Expired Cubes can still be sold to Swindle but only for 200 per stack.\n\n");
    
    printf("TIPS:\n");
    printf(" - Watch your Energon balance. If you run out, you will not be able to produce more Cubes.\n");
    printf(" - Pricing trends will not repeat in consecutive weeks so stay alert for favorable prices.\n");
    printf(" - Avoid letting your Cubes expire, even if it means selling at a low price.\n\n");

    printf("The fate of Cybertron rests in your hands.\n\nMission Begin!\n\n");
	printf("-----------------------------------------------------------------------------------------------------------------\n");
	
	
	int week = 1, day = 1;
	int storage = 10000, stacks = 0, recycleStacks = 0;
	int productionCost, sellPrice;
	int eST, currentEST = 0;
	
	char viewEST;
	
	srand(time(0));
	
	//dev Feature can be activated before the start of the game
	devFeature(&storage, &week);
	
	//displaying the weekly Energon Surge Trends can be enabled
	viewEST = checkEST();
	
	do{
				
		//game ends if there is not enough Energon to produce atleast one stack
		if(storage < 800 && recycleStacks == 0)
			printf("You do not have enough Energon to produce stacks!!!\n\n");	
		
		else{
			
			//cube production occurs at the start of every week
			while(day == 1 && week <= 10){
				
				//display and modify date	
				calendar(&week, &day);
				
				//display current inventory	
				energonStorage(storage, stacks);
				
				//generate Production Cost for the week
				productionCost = generateProductionCost();
				
				//run cube production phase			
				cubeProduction(productionCost, &storage, &stacks);
						
				//call surgeTrend to set the EST for the week
				eST = surgeTrend(&currentEST);
				
				//display EST if enabled at the start		
				if(viewEST == 'y' || viewEST == 'Y')
					displayEST(eST);
							
				printf("\n");
			}
				
			//swindle's shop will be open for the rest of the week
			while(day != 1 && week <= 10){	
					
				//weekSkip called if no stacks left
				if(stacks == 0 && recycleStacks == 0) 
					weekSkip(&week, &day);						
					
				//otherwise, proceed with Swindle's Shop
				else{
						
					calendar(&week, &day);
						
					energonStorage(storage, stacks);
					
					//call surgePrice to generate sell price
					sellPrice = surgePrice(productionCost, eST);
					
					swindle(sellPrice, &storage, &stacks);
					
					//if there are stacks in the recycle bin and it is not production day, call recycleShop
					if(recycleStacks != 0 && day != 1)
						recycleShop(&storage, &recycleStacks);
						
					//if there are unsold stacks at the end of each week, call recycleBin
					if(stacks != 0 && day == 1)
						recycleBin(&recycleStacks, &stacks);
				}
					
				printf("\n");	
			}
		}				
	//loop will continue as long a the 10th week has not passed and
	//there is atleast 800 Energon in storage or user has expired stacks in inventory
	} while(week <= 10 && (storage >= 800 || recycleStacks != 0));
	
	//game is won if user generates atleast 1,000,000 Energon by the end of week 10
	if(storage >= 1000000){
		
		printf("Congratulations! You produced 1,000,000 Energon in time\n");
		printf("Final Score: %d Energon", storage);
	}
	
	else{
	
		printf("Game Over! You were not able to produce 1,000,000 Energon in time\n");
		printf("Final Score: %d Energon", storage);
	}
	
    return 0;
}
