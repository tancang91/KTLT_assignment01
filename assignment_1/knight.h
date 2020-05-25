#ifndef KNIGHT_H_4UNFRJ8C
#define KNIGHT_H_4UNFRJ8C

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

// Function define
void handle_item(struct knight *theKnight, Item item);
void handle_special(struct knight *theKnight, Special event);
void handle_fight(struct knight *theKnight, Opponent opponent, int eventNum);
bool check_prime(int number);
bool check_dragonknight(int number);
Character get_character(int orignalHP);
int game_main(struct knight *theKnight, int *events, int numEvents);
int get_fib(int N);

#endif /* end of include guard: KNIGHT_H_4UNFRJ8C */
