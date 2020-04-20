#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <math.h>

using namespace std;

const int MADBEAR = 1;
const int BANDIT = 2;
const int EVENT_SIZE = 100;
const int MAX_CHARACTER_EACH_LINE = 250;

struct knight
{
   int HP;
   int level;
   int remedy;
   int maidenkiss;
   int phoenixdown;
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


// -- Code section
#define RESULT(hp, level, remedy, maidenkiss, pheonixdown) (hp+level+remedy+maidenkiss+pheonixdown)
#define MIN(a, b) (a<b?a:b)
#define MAX(a, b) (a>b?a:b)

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
    LIGHTWING = 21,
    DRAGONSWORD = 23
};

enum Special {
    SURRENDER = 0,
    MERLIN = 18,
    ABYSS = 19,
    GUNIEVERE = 20,
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


void handle_fight(struct knight *theKnight, int& character, int maxHP, int opponent, int eventNum)
{
    int level = theKnight->level;
    int b = eventNum % 10;
    int level_oppnent = eventNum>6 ? (b>5?b:5):b;

    bool autowin = (    (character == Character::ARTHUR)          ||
                        (character == Character::DRAGONKNIGHT)    || 
                        (character == Character::LANCELOT && (level & 1UL)) ||
                        (character == Character::PALADIN && (level >= 8) )  ||
                        (character == Character::KNIGHT && (level == 10))
                    );

    if (opponent == Opponent::BOWSER) {
        if (autowin)
            theKnight->level = 10;
        else
            Game = GameState::GAMEOVER;
        return;
    }

    autowin = autowin || 
        (character == Character::UNDRAGONKNIGHT &&  (level > level_oppnent)) ||
        (character == Character::LANCELOT && !(level & 1UL) && (level > level_oppnent)) ||
        (character == Character::KNIGHT && (level > level_oppnent));

    switch (opponent) {
        case Opponent::VAJSH: { // 7
            if (autowin) {
                theKnight->level = MIN(10, level + 2);
            }
            else if (character != Character::DWARF &&character != Character::FROG && level < level_oppnent) {
                if (theKnight->maidenkiss > 0)
                    theKnight->maidenkiss--;
                else {
                    theKnight->level = 1;
                    character = Character::FROG;
                }
            }
        } return;

        case Opponent::SHAMAN: { // 6
            if (autowin) {theKnight->level = MIN(10, level + 2);}
            else if (character != Character::DWARF && character != Character::FROG && level < level_oppnent) {
                theKnight->HP = MAX(1, (int)(theKnight->HP/5) );
                if (theKnight->remedy > 0) {
                    theKnight->remedy--;
                    theKnight->HP = MIN(maxHP, 5*theKnight->HP);
                }
                else
                    character = Character::DWARF;
            }
        } return;

        default: {
            if (autowin)    {theKnight->level = MIN(10, level + 1);} 
            else if (level < level_oppnent) {
                float basedame = 1.0f;
                if (opponent == Opponent::BANDIT_)          basedame = 1.5;
                else if (opponent == Opponent::LORDLUPIN)   basedame = 4.5;
                else if (opponent == Opponent::ELF)         basedame = 6.5;
                else if (opponent == Opponent::TROLL)       basedame = 8.5;

                theKnight->HP = (int)(theKnight->HP - level_oppnent*basedame*10.0f);
            }
        } break;
    }

    if (theKnight->HP <= 0) {
        if (theKnight->phoenixdown > 0) {
            theKnight->phoenixdown--;
            theKnight->HP = maxHP;

            // TODO: character
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
    // TODO:

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

    // Check identity
    Character o_character = get_character(theKnight.HP);

    // TODO: Enter event loop
	for (i = 0; i < nEvent; i++)
	{
		int theEvent = arrEvent[i];
		//cout << theEvent << endl;
		switch (theEvent)
		{
		case MADBEAR:
			//deal with MadBear here
		break;

		case BANDIT:
			//deal with Bandit here
		break;
		}
	}

    display(nOut);
	return 0;
}

