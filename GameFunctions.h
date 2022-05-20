#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <limits.h>

//High intensty text
#define HBLK "\e[0;90m"
#define HRED "\e[0;91m"
#define HGRN "\e[0;92m"
#define HYEL "\e[0;93m"
#define HBLU "\e[0;94m"
#define HMAG "\e[0;95m"
#define HCYN "\e[0;96m"
#define HWHT "\e[0;97m"

//Bold high intensity text
#define BHBLK "\e[1;90m"
#define BHRED "\e[1;91m"
#define BHGRN "\e[1;92m"
#define BHYEL "\e[1;93m"
#define BHBLU "\e[1;94m"
#define BHMAG "\e[1;95m"
#define BHCYN "\e[1;96m"
#define BHWHT "\e[1;97m"


//High intensty background
#define BLKHB "\e[0;100m"
#define REDHB "\e[0;101m"
#define GRNHB "\e[0;102m"
#define YELHB "\e[0;103m"
#define BLUHB "\e[0;104m"
#define MAGHB "\e[0;105m"
#define CYNHB "\e[0;106m"
#define WHTHB "\e[0;107m"

//Regular underline text
#define UBLK "\e[4;30m"
#define URED "\e[4;31m"
#define UGRN "\e[4;32m"
#define UYEL "\e[4;33m"
#define UBLU "\e[4;34m"
#define UMAG "\e[4;35m"
#define UCYN "\e[4;36m"
#define UWHT "\e[4;37m"

#define reset "\e[0m"

//Regular text
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"



//SH = 0, JW = 1, JS = 2, IL = 3, MS = 4, SG = 5, WG = 6, JB = 7

enum characters_number {sh, jw, js, il, ms, sg, wg, jb};


//UP_LEFT = 0, UP = 1, UP_RIGHT = 2, DOWN_RIGHT = 3, DOWN = 4, DOWN_LEFT = 5

enum direction {up_left, up, up_right, down_right, down, down_left};


//empty = 0   building = 1  open-pit = 2   close-light = 3   out-range = 4   close-pit = 5   open-light = 6   close-exit = 7  open-exit = 8

enum area_type {empty, building, open_pit, close_light, out_range, close_pit, open_light, close_exit, open_exit};


//initially manholes and there status
//pit6 = 2, 0 open | pit7 = 6, 2 close | pit8 = 0, 5 open | pit9 = 3, 5 open |
//pit10 = 5, 7 open | pit11 = 8, 7 open | pit12 = 1, 11 close | pit13 = 4, 12 open

enum manholes{pit1 = 1, pit2, pit3, pit4, pit5, pit6, pit7, pit8};


//initially lights and there status
//light1 = 6, 1 open |light2 = 1, 2 open |light3 = 1, 5 close |light4 = 5, 5 open |
//light5 = 3, 7 open |light6 = 7, 7 close |light7 = 6, 10 open |light8 = 2, 11 open |

enum lights{light1 = 1, light2, light3, light4, light5, light6, light7, light8};


//initially exit hexes and there status
//out1 = 0, 1 open |out2 = 8, 1 close |out3 = 0, 11 close |out4 = 7, 12 open |

enum outs{out1 = 1, out2, out3, out4};


//  type of use of ability
/*
    1)the ability MUST be used before or after a
    movement

    2)the ability MUST be used at the end of a
    movement

    3)the ability CAN be used instead of a movement

    4)the ability CAN be used during a movement
 */



enum type_of_use_of_ability{
    MUST_be_used_before_or_after = 1,
    MUST_be_used_at_the_end = 2,
    CAN_be_used_instead = 3,
    CAN_be_used_during = 4
};



typedef struct {
    char name[3];
    char ability[300];
    int max_move;
    int is_which;
    int Mr_Jack;
    int row, col;
    int direction;
    int is_visible;
}CHARACTER;



struct Node{
    CHARACTER character;
    struct Node *next;
};



static CHARACTER SH = {
        "SH",
        "\tAFTER MOVEMENT,secretly draws the first card from the.\n"
        "\talibi pile and places it face down in front of him.",
        3,
        sh,
        0,
        5, 6,
        0,
        1
};


static CHARACTER JW = {
        "JW",
        "\tWatson bears a lantern, pictured on his character token. \n"
        "\tThis lantern illuminates all the characters standing straight ahead of him!!\n"
        "\tAny player moving Watson, one way or another, chooses the final facing of the character, and therefore the line \n"
        "\tilluminated by the lantern.",
        3,
        jw,
        0,
        4, 0,
        0,
        0
};


static CHARACTER JS = {
        "JS",
        "\tMove one of the lit gaslight tiles onto one of the shut-off gaslight hex.\n"
        "\tThis ability can be used before or after the movement.",
        3,
        js,
        0,
        2, 6,
        0,
        1
};


static CHARACTER IL = {
        "IL",
        "\tMove one police cordon. This will free one of the exits but block another!!\n"
        "\tThis ability can be used before or after the movement.",
        3,
        il,
        0,
        4, 4,
        0,
        1
};


static CHARACTER MS = {
        "MS",
        "\tDuring her movement, Miss Stealthy can cross any hex (building, \n"
        "\tgaslight, garden) but she must stop her movement on a street hex.",
        4,
        ms,
        0,
        7, 8,
        0,
        0
};


static CHARACTER SG = {
        "SG",
        "\tSergeant Goodley calls for help with his whistle!! You then get 3 movement \n"
        "\tpoints to use as you see fit on one or several characters in order to bring them closer to Sergeant Goodley!!\n"
        "\tThis ability can be used before or after the movement.",
        3,
        sg,
        0,
        3, 12,
        0,
        0
};


static CHARACTER WG = {
        "WG",
        "\tInstead of moving normally William Gull, you can exchange location of this character\n"
        "\twith the location of any other character.",
        3,
        wg,
        0,
        0, 4,
        0,
        0
};


static CHARACTER JB = {
        "JB",
        "\tJournalists like to search where it stinks... Jeremy Bert opens a manhole and \n"
        "\tcloses another (move one covered manhole tile on any other open manhole hex.)\n"
        "\tThis ability can be used before or after the movement.",
        3,
        jb,
        0,
        3, 8,
        0,
        1
};


struct Area{
    int is_empty, is_building, is_open_pit, is_close_light, is_out_range, is_close_pit, is_open_light, is_close_exit, is_open_exit;
    struct Node * list_characters_in;
};


struct cards{
    int firstSet[4];
    int secondSet[4];
};

struct Coordinate{
    int x;
    int y;
};




//File Functions
int **array_type_area_initially(FILE *fp_initial);
void saved_map_file(FILE *fp_saved, int **array_type);
int **load_array_type_area(FILE *fp_saved);


// Map Functions
void Menu(void);
struct Area **InitialMap(int **type_area);
void FillingAreaContent(struct Area **Whitechapel, char stringContent[][6][15]);
void CreateMap(char objects[][6][15]);


//Linked List Functions
struct Node *create_character(CHARACTER character);
void add_font(struct Node **head, struct Node *new_node);
void add_end(struct Node *head, struct Node *new_node);
void insert(struct Node **head, CHARACTER character);
void delete_node(struct Node **head, int which_character);
struct Node *list_of_all_characters();
void print_list(struct Node *head, int index);
struct Node *get_character(struct Node *head, int index);


//Playing Functions
void print_innocent_card(int index_character);
int get_innocent_card(int *used_innocent_cards);
struct cards *ShuffleCards();
int choice_card();
int when_use_ability();
int max_move_you_want();
int get_valid_direction(int **type_area, int character_index, struct Node *listOfCharacters);


struct Coordinate *update_location(int direction, struct Node *character);
void InsertCharacterToDesirablePosition(struct Node *character, struct Area **Whitechapel, char stringAreaContent[][6][15]);
void RemoveCharacterFromCurrentPosition(int index, struct Node *character, struct Area **Whitechapel, char stringAreaContent[][6][15]);
void move_character(int direction, int index, struct Node *listOfCharacters, struct Area **Whitechapel, char stringAreaContent[][6][15]);
int check_first_or_last_use_ability(int index_character);


void update_array_area_type(int **area_type, struct Coordinate *token1, struct Coordinate *token2, int type1, int type2);
void update_whitechapel(int **area_type, struct Area **Whitechapel);
void update_area_content_token_names(struct Area **Whitechapel, char stringContent[][6][15]);

int take_name_get_index(char *character_name);
struct Coordinate *exit_coordinate(int out_number);
struct Coordinate *light_coordinate(int light_number);
struct Coordinate *manhole_coordinate(int pit_number);

void using_sh_ability(int *used_innocent_cards);
void using_jw_ability(struct Node *character);
void using_js_ability(int **area_type, struct Area **Whitechapel, char stringContent[][6][15]);
void using_il_ability(int **area_type, struct Area **Whitechapel, char stringContent[][6][15]);
void using_sg_ability(int **type_area, struct Node *list_characters, struct Area **Whitechapel, char stringContent[][6][15]);
void using_wg_ability(struct Node *listOfCharacters, struct Area **Whitechapel, char stringContent[][6][15]);
void using_jb_ability(int **area_type, struct Area **Whitechapel, char stringContent[][6][15]);


void use_ability(int which_character, struct Node *list_characters, struct Area **Whitechapel, int *used_innocent_cards, int **type_area, char stringAreaContent[][6][15]);

void print_turn(int i, int which_set);
void print_set_cards(int which_set, struct cards *game_cards, int *used_character_index);
void playing_actions(int which_set, struct cards *game_cards, struct Area **Whitechapel, int *used_character_index,
                     struct Node *list_characters, char stringAreaContent[][6][15], int **type_area, int *used_innocent_cards, int mr_jack);


int **check_hex_illuminated_by_the_lantern(int **type_area, struct Node *list_characters);
void check_visibility(int **type_area, struct Node *list_characters, char stringAreaContent[][6][15],struct Area **Whitechapel, int mr_jack);


void mr_jack_escape(struct Node *list_characters, int mr_jack, int **type_area);
void check_inspector_win_lose(int i, int which_set, int mr_jack);


#endif //GAMEFUNCTIONS_H