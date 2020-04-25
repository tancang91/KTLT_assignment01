#include <iostream>
#include <string.h>
#include <fstream>
#include <math.h>

using namespace std;

const int EVENT_SIZE = 100;
const int MAX_CHARACTER_EACH_LINE = 250;

// -- Code section

#define TEST_1920005

#define RESULT(hp, level, remedy, maidenkiss, pheonixdown) (hp+level+remedy+maidenkiss+pheonixdown)
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

enum Opponent {
    MADBEAR_ = 1,
    BANDIT_,
    LORDLUPIN,
    ELF,
    TROLL,
    SHAMAN,
    VAJSH,
    BOWSER = 99
};

enum Item {
    EXCALIBUR = 8,
    MYTHRIL,
    EXCALIPOOR,
    MUSHMARIO,
    MUSHFIB,
    MUSHGHOST,
    MUSHKNIGHT,
    REMEDY,
    MAINDENKISS,
    PHOENIXDOWN,
    DRAGONSWORD = 23,

    NORMALSWORD = 24,
    NORMALARMOR = 25
};

enum Special {
    SURRENDER = 0,
    MERLIN = 18,
    ABYSS = 19,
    GUNIEVERE = 20,
    LIGHTWING = 21,
    ODIN = 22
};

enum Character {
    ARTHUR = 0,
    LANCELOT,
    PALADIN,
    DRAGONKNIGHT,
    UNDRAGONKNIGHT,
    KNIGHT,
    DWARF,
    FROG
};

enum GameState {
    RUNNING = 0,
    GAMEOVER,
    FINISHED
} Game;

struct knight
{
    int HP;
    int level;
    int remedy;
    int maidenkiss;
    int phoenixdown;

    int maxHP;
    int previousHP;
    int previousLevel;
    int numCursed;
    Character character;
    Character trueCharacter;

    // Item
    Item sword;
    Item armor;
    int odin;
};


// read data from input file to corresponding variables
// return 1 if successfully done, otherwise return 0
int readFile(const char* filename, knight& theKnight, int& nEvent, int* arrEvent)
{
	const char* file_name = filename;
	FILE* f = 0;
	char* str = new char[MAX_CHARACTER_EACH_LINE];
	int num;

	f = fopen(file_name, "r");
	if (f == NULL)	//file not found || cannot read
		return 0;

	fgets(str, MAX_CHARACTER_EACH_LINE, f);
	if (feof(f))
		return 0;

	int start = 0;
	int len = strlen(str);
	// read HP
	while (start < len && str[start] == ' ')
		start ++;
	num = 0;
	while (start < len && str[start] <= '9' && str[start] >= '0'){
		num = num * 10 + str[start] - '0';
		start++;
	}
	theKnight.HP = num;
	if (theKnight.HP < 1 || theKnight.HP > 999)
		return 0;

	// read level
	while (start < len && (str[start] > '9' || str[start] < '0'))
		start ++;
	num = 0;
	while (start < len && str[start] <= '9' && str[start] >= '0'){
		num = num * 10 + str[start] - '0';
		start++;
	}
	theKnight.level = num;
	if (theKnight.level < 1 || theKnight.level > 10)
		return 0;

	// read remedy
	while (start < len && (str[start] > '9' || str[start] < '0'))
		start ++;
	num = 0;
	while (start < len && str[start] <= '9' && str[start] >= '0'){
		num = num * 10 + str[start] - '0';
		start++;
	}
	theKnight.remedy = num;
	if (theKnight.remedy < 0 || theKnight.remedy > 99)
		return 0;

	// read maidenkiss
	while (start < len && (str[start] > '9' || str[start] < '0'))
		start ++;
	num = 0;
	while (start < len && str[start] <= '9' && str[start] >= '0'){
		num = num * 10 + str[start] - '0';
		start++;
	}
	theKnight.maidenkiss = num;
	if (theKnight.maidenkiss < 0 || theKnight.maidenkiss > 99)
		return 0;

	// read phoenixdown
	while (start < len && (str[start] > '9' || str[start] < '0'))
		start ++;
	num = 0;
	while (start < len && str[start] <= '9' && str[start] >= '0'){
		num = num * 10 + str[start] - '0';
		start++;
	}
	theKnight.phoenixdown = num;
	if (theKnight.phoenixdown < 0 || theKnight.phoenixdown > 99)
		return 0;

	// read events
	nEvent = 0;
	while (1){
		if (feof(f))
			break;
		fgets(str, MAX_CHARACTER_EACH_LINE, f);
		if (str == NULL)
			break;
		start = 0;
		len = strlen(str);
    // cout << "\'" << str << "\'" << "\t" << len << endl;
		while (start < len){
			while (start < len && (str[start] > '9' || str[start] < '0'))
				start++;
			if (start >= len)
				break;
			arrEvent[nEvent] = 0;
			while (start < len && str[start] <= '9' && str[start] >= '0'){
				arrEvent[nEvent] = arrEvent[nEvent] * 10 + str[start] - '0';
				start++;
			}
			nEvent++;
		}
    delete[] str;
	}
	fclose(f);
	return 1;
}

void display(int* nOut)
{
  if (nOut)
    cout << *nOut;
  else
    cout << "Error!";
}


/* Implementation */

int get_fib(int N) {
    if (N <= 1) return 2;

    int a,b,next_fib;
    a = 0; b = 1;

    do { next_fib = a + b;
        a = b;
        b = next_fib;
    } while(N >= next_fib);

    return next_fib;
};

void handle_item(struct knight *theKnight, Item item)
{
    switch(item) {
        case Item::EXCALIBUR: {
            if (theKnight->trueCharacter != Character::DRAGONKNIGHT)
                theKnight->sword = Item::EXCALIBUR;
        } break;

        case Item::MYTHRIL: {
            theKnight->armor = Item::MYTHRIL;
        } break;

        case Item::EXCALIPOOR: {
            bool isFool = (theKnight->level < 5) && 
                    (theKnight->trueCharacter == Character::KNIGHT || 
                        (theKnight->trueCharacter == Character::LANCELOT && !(theKnight->level & 1UL)));
            if (isFool)
                theKnight->sword = Item::EXCALIPOOR;
        } break;

        case Item::MUSHMARIO: {
            theKnight->HP = MIN(theKnight->HP + 50, theKnight->maxHP);
        } break;

        case Item::MUSHFIB: {
            int fib = get_fib(theKnight->HP);
            theKnight->HP = MIN(fib, theKnight->maxHP);
        } break;

        case Item::MUSHGHOST: {
            bool isSmart = (theKnight->trueCharacter == Character::PALADIN) ||
                            (theKnight->trueCharacter == Character::DRAGONKNIGHT);
            if (!isSmart)
                theKnight->HP = MAX(1, theKnight->HP-50);
        } break;

        case Item::MUSHKNIGHT: {
            theKnight->maxHP = MIN(999, theKnight->maxHP+50);
            theKnight->HP = theKnight->maxHP;
        } break;

        case Item::REMEDY:
            theKnight->remedy = MIN(99, theKnight->remedy + 1);
            if (theKnight->character == Character::DWARF)
            {
                theKnight->character = theKnight->trueCharacter;
                theKnight->HP = MIN(theKnight->maxHP, 5*theKnight->HP);
                theKnight->numCursed = 0;
                theKnight->remedy--;
            }
            break;

        case Item::MAINDENKISS: {
            theKnight->maidenkiss = MIN(99, theKnight->maidenkiss + 1);
            if (theKnight->character == Character::FROG)
            {
                theKnight->character = theKnight->trueCharacter;
                theKnight->level = theKnight->previousLevel;
                theKnight->numCursed = 0;
                theKnight->maidenkiss--;
            }
        } break;

        case Item::PHOENIXDOWN: {
            theKnight->phoenixdown = MIN(99, theKnight->phoenixdown + 1);
        } break;

        case Item::DRAGONSWORD:
            if (theKnight->trueCharacter == Character::UNDRAGONKNIGHT)
            {
                theKnight->sword = Item::DRAGONSWORD;
                theKnight->trueCharacter = Character::DRAGONKNIGHT;
            }

        default: break;
    }
}

void handle_special(struct knight *theKnight, Special event)
{
    switch(event)
    {
        case Special::SURRENDER:
            Game = GameState::FINISHED;
            break;

        case Special::MERLIN:
            // back to normal from Frog and Dwarf
            if (theKnight->character == Character::DWARF)
                theKnight->HP = MIN(theKnight->maxHP, 5*theKnight->HP);
            else if (theKnight->character == Character::FROG)
                theKnight->level = theKnight->previousLevel;
            theKnight->numCursed = 0;
            theKnight->character = theKnight->trueCharacter;

            // increase level by 1
            theKnight->level = MIN(10, theKnight->level+1);
            // HP =  maxHP
            theKnight->HP = theKnight->maxHP;
            break;

        // Gameover, except the knight is DRAGONKNIGHT or theKnight.level >= 7
        case Special::ABYSS:
            if (theKnight->level < 7)
                if (theKnight->trueCharacter != Character::DRAGONKNIGHT)
                    Game = GameState::GAMEOVER;
            break;

        //case Special::GUNIEVERE:
            //theKnight->movement = -1;
            //break;

        case Special::ODIN: {
            // Odin help 3 times, but in order to maintaince the logic flow of game_main correct
            // I add 1
            int odin = 3;
            theKnight->odin = odin + 1;
        } break;

        default: break;
    }

}

void handle_fight(struct knight *theKnight, Opponent opponent, int eventNum)
{
    int level = theKnight->level;
    Character character = theKnight->character;
    Character trueCharacter = theKnight->trueCharacter;
    int b = eventNum % 10;
    int level_oppnent = eventNum>6 ? (b>5?b:5):b;

    bool isExcalipoor = (theKnight->sword == Item::EXCALIPOOR);
    bool autowin = (    (theKnight->odin > 0)                               ||
                        (trueCharacter == Character::ARTHUR)                    ||
                        (trueCharacter == Character::DRAGONKNIGHT)              || 
                        (trueCharacter == Character::LANCELOT)                  ||
                        (trueCharacter == Character::PALADIN && (level >= 8) )  ||
                        (level == 10 && !isExcalipoor)
                    );

    if (opponent == Opponent::BOWSER) {
        if (autowin)
            theKnight->level = 10;
        else
            Game = GameState::GAMEOVER;
        return;
    }

    autowin = (         (theKnight->odin > 0)                               ||
                        (trueCharacter == Character::ARTHUR)                    ||
                        (trueCharacter == Character::DRAGONKNIGHT)              || 
                        (trueCharacter == Character::LANCELOT && (level & 1UL)) ||
                        (trueCharacter == Character::PALADIN)  ||
                        (level > level_oppnent && !isExcalipoor)
                    );

    switch (opponent) {
        case Opponent::VAJSH: // 7
            if (character == Character::FROG || character == Character::DWARF)
                return;

            if (autowin)
                theKnight->level = MIN(10, level + 2);
            else if (level < level_oppnent || isExcalipoor)
            {
                if (theKnight->maidenkiss > 0)
                    theKnight->maidenkiss--;
                else 
                {
                    theKnight->previousLevel = theKnight->level;
                    theKnight->level = 1;
                    theKnight->character = Character::FROG;
                    theKnight->numCursed = 3;
                }
            }
            return;

        case Opponent::SHAMAN: // 6
            if (character == Character::FROG || character == Character::DWARF)
                return;

            if (autowin)
                theKnight->level = MIN(10, level + 2);
            else if (level < level_oppnent || isExcalipoor)
            {
                theKnight->HP = MAX(1, (int)(theKnight->HP/5) );
                if (theKnight->remedy > 0)
                {
                    theKnight->remedy--;
                    theKnight->HP = MIN(theKnight->maxHP, 5*theKnight->HP);
                }
                else
                {
                    theKnight->character = Character::DWARF;
                    theKnight->numCursed = 3;
                }
            }
            return;

        default:
            if (autowin || theKnight->sword == Item::EXCALIBUR) 
                theKnight->level = MIN(10, level + 1);

            else if (level < level_oppnent || isExcalipoor)
            {
                if (theKnight->armor != Item::MYTHRIL)
                {
                    float basedame = 1.0f;
                    if (opponent == Opponent::BANDIT_)          basedame = 1.5;
                    else if (opponent == Opponent::LORDLUPIN)   basedame = 4.5;
                    else if (opponent == Opponent::ELF)         basedame = 6.5;
                    else if (opponent == Opponent::TROLL)       basedame = 8.5;

                    theKnight->HP = (int)(theKnight->HP - level_oppnent*basedame*10.0f);
                }
            }
            break;
    }

    // Check die
    // Use phoenix if die.
    if (theKnight->HP <= 0) {
        if (theKnight->phoenixdown > 0) {
            theKnight->phoenixdown--;
            theKnight->HP = theKnight->maxHP;
            theKnight->character = theKnight->trueCharacter;

            if(theKnight->character == Character::FROG)
                theKnight->level = theKnight->previousLevel;
        }
        else
            Game = GameState::GAMEOVER;
    }
}

bool check_prime(int number) {
    if (number < 2)
        return false;
    if (number == 2)
        return true;
    if ((number & 1UL) ^ 1UL)
        return false;

    int N = (int) (sqrt(number) + 1);
    for (int i = 3; i < N; i+=2) {
        if ((number % i) == 0)
            return false;  
    }
    return true;
}

bool check_dragonknight(int number) {
    /* -- x^2 + y^2 =z^2
     * |
     * -- x + y + z = number
     * x = m^2 - n^2
     * y = 2*m*n
     * z = m^2 + n^2
     *
     * Solution
     * 0 < (number - m*m)/m < m
     */

    // 3 + 4 + 5 = 12
    if(number < 12 || number > 999)
        return false;
    // Odd number
    if (number & 1UL)
        return false;

    int N = number/2;
    int m = 1;
    for( ; ; m++) {

        // m*m < number
        long long temp = m*m;
        if (N < temp)
            break;

        // check number/m is integer
        if (N % m != 0)
            continue;

        // check number < 2*m*m
        if (N/2 > temp)
            continue;

        return true;
    }
    return false;
}

Character get_character(int orignalHP) {
    if (orignalHP == 999)
        return Character::ARTHUR;
    else if (orignalHP == 888)
        return Character::LANCELOT;
    else if (check_prime(orignalHP))
        return Character::PALADIN;
    else if (check_dragonknight(orignalHP))
        return Character::UNDRAGONKNIGHT;

    return Character::KNIGHT;
}


int game_main(struct knight *theKnight, int *events, int numEvents)
{
    int nOut = -1;
    theKnight->odin = 0;
    theKnight->armor = Item::NORMALARMOR;
    theKnight->sword = Item::NORMALSWORD;
    theKnight->maxHP = theKnight->HP;
    theKnight->trueCharacter = theKnight->character = get_character(theKnight->HP);
    Game = GameState::RUNNING;

    int i;
    int movement = 1;
    int round = 1;
	for (i = 0; i >= 0 && i < numEvents; i+=movement, round++)
    {
        if (Game != GameState::RUNNING) break;
        theKnight->numCursed -= (int) ((theKnight->numCursed & 0x01) || (theKnight->numCursed & 0x02));
        theKnight->odin -= theKnight->odin > 0 ? 1 : 0; 

        // Events seperated into 3 categories
        // 1. Fighting
        // 2. Collect item
        // 3. Special event
        int theEvent = events[i];
        if ((theEvent >= 1 && theEvent <= 7) || theEvent == 99)
            handle_fight(theKnight, (Opponent) theEvent,round);
        else if ((theEvent >= 8 && theEvent <= 17 ) || theEvent == 23)
            handle_item(theKnight, (Item) theEvent);
        else if ((theEvent >= 18 && theEvent <= 22) || theEvent == 0)
        {
            // Event 20, go back to england
            if (theEvent == Special::GUNIEVERE)
                movement = -1;

            // LIGHTWING event 21
            else if (theEvent == Special::LIGHTWING)
            {
                if (numEvents-1-i >= 4)
                {
                    if(movement == 1)
                        for (int j = 1; j <= 3; ++j) 
                            if (events[i+j] == Special::SURRENDER || events[i+j] == Special::GUNIEVERE)
                                Game = GameState::FINISHED;
                }
                else Game = GameState::FINISHED;
                i += 3*movement; round += 3;
            }
            else
                handle_special(theKnight, (Special) theEvent);
        }

        // Check magic cursed (FROG, DWARF)
        if (theKnight->character == Character::FROG && theKnight->numCursed == 0)
        {
            theKnight->level = theKnight->previousLevel;
            theKnight->character = theKnight->trueCharacter;
        }
        else if (theKnight->character == Character::DWARF && theKnight->numCursed == 0)
        {
            theKnight->HP = MIN(theKnight->maxHP, 5*theKnight->HP);
            theKnight->character = theKnight->trueCharacter;
        }
    }
    //if (Game != GameState::GAMEOVER && i == numEvents)
    if (Game != GameState::GAMEOVER)
        nOut = RESULT(theKnight->HP, theKnight->level, theKnight->remedy,
                    theKnight->maidenkiss, theKnight->phoenixdown);
    return nOut;
};

#ifndef TEST_1920005
int main(int argc, char** argv)
{
    if (argc < 2) return 1;
    const char* filename = argv[1];;

    struct knight theKnight;
    int nEvent; //number of events
    int* arrEvent = new int[EVENT_SIZE]; // array of events
    int* nOut;                           // final result
    int i;

	readFile(filename, theKnight, nEvent, arrEvent);
	//cout << theKnight.HP << ' ' << theKnight.level << ' ' << theKnight.remedy << ' ' << theKnight.maidenkiss << ' ' << theKnight.phoenixdown << endl;

    // TODO: Enter event loop
    *nOut = game_main(&theKnight, arrEvent, nEvent);
    display(nOut);
    return 0;
}
#endif

/*
 *int main()
 *{
 *   struct knight theKnight = {.HP=888, .level=4, .remedy=2, .maidenkiss=0, .phoenixdown=0};
 *   int events[] = {10,1,10,7,5};
 *   int a = game_main(&theKnight, events, sizeof(events)/sizeof(int));
 *   printf("%d", a);
 *   return 0;
 *}
 */
