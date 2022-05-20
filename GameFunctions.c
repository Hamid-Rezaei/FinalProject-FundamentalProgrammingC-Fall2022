#include "GameFunctions.h"


//empty = 0   building = 1  open-pit = 2   close-light = 3   out-range = 4   close-pit = 5   open-light = 6   close-exit = 7  open-exit = 8

//Sherlock Holmes = 0, John H. Watson = 1, John Smith = 2, Inspector Lestrade = 3, Miss Stealthy = 4, Sergeant Goodley = 5, William Gull = 6
//Jeremy Bert = 7

//-------------------------------------------------------------------------------------------------------------------------------------------//




// File Functions
int **array_type_area_initially(FILE *fp_initial){

    int **type_area = (int **)malloc(9 * sizeof(int *));
    for(int i = 0; i < 9; i++)
        type_area[i] = (int *)malloc(13 * sizeof(int));


    int type;
    int row = 0, col = 0;

    while(!feof(fp_initial)){
        type = fgetc(fp_initial);
        if(type == '\n'){
            row++;
            col = 0;
        }
        else{
            type_area[row][col] = type - '0';
            col++;
        }
    }
    fclose(fp_initial);

    return type_area;
}


void saved_map_file(FILE *fp_saved, int **array_type){
    int array[9][13];
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 13; j++){
            array[i][j] = array_type[i][j];
        }
    }

    fwrite(array, sizeof(int), 9 * 13, fp_saved);
    fclose(fp_saved);
}


int **load_array_type_area(FILE *fp_saved){
    int **type_area = (int **)malloc(9 * sizeof(int *));
    for(int i = 0; i < 9; i++)
        type_area[i] = (int *)malloc(13 * sizeof(int));

    int array[9 * 13];
    fread(array, sizeof(int), 9 * 13, fp_saved);
    fclose(fp_saved);

    int k = 0;
    for(int i = 0; i < 9; i++) {
        for (int j = 0; j < 13; j++){
            type_area[i][j] = array[k++];
        }
    }

    return type_area;
}



//Map Functions
void Menu(void){
    system("cls");

    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t\t\t\t\t\a");
    printf(YELHB ANSI_COLOR_BLUE "1)Playing new game\n\n" ANSI_COLOR_RESET);
    printf("\t\t\t\t\t\t\t\t\a");
    printf(YELHB ANSI_COLOR_MAGENTA "2)Playing saved game\n\n" ANSI_COLOR_RESET);
    printf("\t\t\t\t\t\t\t\t\a");
    printf(YELHB ANSI_COLOR_RED "3)Quit\n\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "\t\t\t\t\t\t\t\t\t\a?:" ANSI_COLOR_RESET);
}


struct Area **InitialMap(int **type_area){

    struct Area **Whitechapel = (struct Area **) calloc(9, sizeof(struct Area *));
    for(int i = 0; i < 9; i++){
        Whitechapel[i] = (struct Area *) calloc(13, sizeof(struct Area));
    }

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 13; j++){
            Whitechapel[i][j].list_characters_in = NULL;
            Whitechapel[i][j].is_out_range = 0;
            Whitechapel[i][j].is_empty = 0;
            Whitechapel[i][j].is_building = 0;
            Whitechapel[i][j].is_open_exit= 0;
            Whitechapel[i][j].is_open_light = 0;
            Whitechapel[i][j].is_open_pit = 0;
            Whitechapel[i][j].is_close_exit = 0;
            Whitechapel[i][j].is_close_light = 0;
            Whitechapel[i][j].is_close_pit = 0;
        }
    }


    for(int row = 0; row < 9; row++){
        for(int col = 0; col < 13; col++){
            if(row == 0 && col == 4)
                insert(&Whitechapel[row][col].list_characters_in, WG);

            else if(row == 4 && col == 0)
                insert(&Whitechapel[row][col].list_characters_in, JW);

            else if(row == 4 && col == 4)
                insert(&Whitechapel[row][col].list_characters_in, IL);

            else if(row == 2 && col == 6)
                insert(&Whitechapel[row][col].list_characters_in, JS);

            else if(row == 5 && col == 6)
                insert(&Whitechapel[row][col].list_characters_in, SH);

            else if(row == 3 && col == 8)
                insert(&Whitechapel[row][col].list_characters_in, JB);

            else if(row == 7 && col == 8)
                insert(&Whitechapel[row][col].list_characters_in, MS);

            else if(row == 3 && col == 12)
                insert(&Whitechapel[row][col].list_characters_in, SG);
        }
    }


    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 13; j++){
            switch (type_area[i][j]) {
                case 0:
                    Whitechapel[i][j].is_empty = 1;
                    break;
                case 1:
                    Whitechapel[i][j].is_building = 1;
                    break;
                case 2:
                    Whitechapel[i][j].is_open_pit = 1;
                    break;
                case 3:
                    Whitechapel[i][j].is_close_light = 1;
                    break;
                case 4:
                    Whitechapel[i][j].is_out_range = 1;
                    break;
                case 5:
                    Whitechapel[i][j].is_close_pit = 1;
                    break;
                case 6:
                    Whitechapel[i][j].is_open_light = 1;
                    break;
                case 7:
                    Whitechapel[i][j].is_close_exit = 1;
                    break;
                case 8:
                    Whitechapel[i][j].is_open_exit = 1;
            }
        }
    }

    return Whitechapel;
}


void FillingAreaContent(struct Area **Whitechapel, char stringContent[][6][15]){

    int area = 0;
    for(int row = 0; row < 9; row++){
        for(int col = 0; col < 13; col++){
            if(Whitechapel[row][col].is_empty)
                strcpy(stringContent[area][2], "");

            else if(Whitechapel[row][col].is_building) {
                strcpy(stringContent[area][0], "BB");
                strcpy(stringContent[area][1], "BB");
                strcpy(stringContent[area][2], "BUILD");
                strcpy(stringContent[area][3], "BB");
                strcpy(stringContent[area][4], "BB");
                strcpy(stringContent[area][5], "BB");
            }
            else if(Whitechapel[row][col].is_open_pit){
                if(row == 2 && col == 0)
                    strcpy(stringContent[area][2], "OPit1");
                else if(row == 6 && col == 2)
                    strcpy(stringContent[area][2], "OPit2");
                else if(row == 0 && col == 5)
                    strcpy(stringContent[area][2], "OPit3");
                else if(row == 3 && col == 5)
                    strcpy(stringContent[area][2], "OPit4");
                else if(row == 5 && col == 7)
                    strcpy(stringContent[area][2], "OPit5");
                else if(row == 8 && col == 7)
                    strcpy(stringContent[area][2], "OPit6");
                else if(row == 1 && col == 11)
                    strcpy(stringContent[area][2], "OPit7");
                else if(row == 4 && col == 12)
                    strcpy(stringContent[area][2], "OPit8");
            }


            else if(Whitechapel[row][col].is_close_pit){
                if(row == 2 && col == 0)
                    strcpy(stringContent[area][2], "CPit1");
                else if(row == 6 && col == 2)
                    strcpy(stringContent[area][2], "CPit2");
                else if(row == 0 && col == 5)
                    strcpy(stringContent[area][2], "CPit3");
                else if(row == 3 && col == 5)
                    strcpy(stringContent[area][2], "CPit4");
                else if(row == 5 && col == 7)
                    strcpy(stringContent[area][2], "CPit5");
                else if(row == 8 && col == 7)
                    strcpy(stringContent[area][2], "CPit6");
                else if(row == 1 && col == 11)
                    strcpy(stringContent[area][2], "CPit7");
                else if(row == 4 && col == 12)
                    strcpy(stringContent[area][2], "CPit8");
            }

            else if(Whitechapel[row][col].is_open_light){
                if(row == 6 && col == 1)
                    strcpy(stringContent[area][2], "OLit1");
                else if(row == 1 && col == 2)
                    strcpy(stringContent[area][2], "OLit2");
                else if(row == 1 && col == 5)
                    strcpy(stringContent[area][2], "OLit3");
                else if(row == 5 && col == 5)
                    strcpy(stringContent[area][2], "OLit4");
                else if(row == 3 && col == 7)
                    strcpy(stringContent[area][2], "OLit5");
                else if(row == 7 && col == 7)
                    strcpy(stringContent[area][2], "OLit6");
                else if(row == 6 && col == 10)
                    strcpy(stringContent[area][2], "OLit7");
                else if(row == 2 && col == 11)
                    strcpy(stringContent[area][2], "OLit8");
            }

            else if(Whitechapel[row][col].is_close_light){
                if(row == 6 && col == 1)
                    strcpy(stringContent[area][2], "CLit1");
                else if(row == 1 && col == 2)
                    strcpy(stringContent[area][2], "CLit2");
                else if(row == 1 && col == 5)
                    strcpy(stringContent[area][2], "CLit3");
                else if(row == 5 && col == 5)
                    strcpy(stringContent[area][2], "CLit4");
                else if(row == 3 && col == 7)
                    strcpy(stringContent[area][2], "CLit5");
                else if(row == 7 && col == 7)
                    strcpy(stringContent[area][2], "CLit6");
                else if(row == 6 && col == 10)
                    strcpy(stringContent[area][2], "CLit7");
                else if(row == 2 && col == 11)
                    strcpy(stringContent[area][2], "CLit8");
            }

            else if(Whitechapel[row][col].is_open_exit){
                if(row == 0 && col == 1)
                    strcpy(stringContent[area][2], "OOut1");
                else if(row == 8 && col == 1)
                    strcpy(stringContent[area][2], "OOut2");
                else if(row == 0 && col == 11)
                    strcpy(stringContent[area][2], "OOut3");
                else if(row == 7 && col == 12)
                    strcpy(stringContent[area][2], "OOut4");
            }

            else if(Whitechapel[row][col].is_close_exit){
                if(row == 0 && col == 1)
                    strcpy(stringContent[area][2], "COut1");
                else if(row == 8 && col == 1)
                    strcpy(stringContent[area][2], "COut2");
                else if(row == 0 && col == 11)
                    strcpy(stringContent[area][2], "COut3");
                else if(row == 7 && col == 12)
                    strcpy(stringContent[area][2], "COut4");
            }

            else if(Whitechapel[row][col].is_out_range){
                strcpy(stringContent[area][2], "EXTRA");
            }

            area++;
        }
    }

    area = 0;
    for(int row = 0; row < 9; row++){
        for(int col = 0; col < 13; col++){
            //WG
            if(row == 0 && col == 4)
                strcpy(stringContent[area][0],Whitechapel[row][col].list_characters_in->character.name);

                //JW
            else if(row == 4 && col == 0)
                strcpy(stringContent[area][0],Whitechapel[row][col].list_characters_in->character.name);

                //IL
            else if(row == 4 && col == 4)
                strcpy(stringContent[area][0],Whitechapel[row][col].list_characters_in->character.name);

                //JS
            else if(row == 2 && col == 6)
                strcpy(stringContent[area][0],Whitechapel[row][col].list_characters_in->character.name);

                //SH
            else if(row == 5 && col == 6)
                strcpy(stringContent[area][0],Whitechapel[row][col].list_characters_in->character.name);

                //JB
            else if(row == 3 && col == 8)
                strcpy(stringContent[area][0],Whitechapel[row][col].list_characters_in->character.name);

                //MS
            else if(row == 7 && col == 8)
                strcpy(stringContent[area][0],Whitechapel[row][col].list_characters_in->character.name);

                //SG
            else if(row == 3 && col == 12)
                strcpy(stringContent[area][0],Whitechapel[row][col].list_characters_in->character.name);

            area++;
        }
    }

}


void CreateMap(char objects[][6][15]){
    system("cls");

    int pass = 0, roll1 = 0, roll2 = 1;
    char c='A';
    printf(" ");
    for(int i = 0; i < 13; i++)
        printf(ANSI_COLOR_YELLOW "%4d  " ANSI_COLOR_RESET, i);
    printf("\n ");
    for (int i = 0; i < 6; i++)
        printf(ANSI_COLOR_CYAN "        ____" ANSI_COLOR_RESET);


    for(int j = 0; j < 9; j++) {
        printf("\n ");
        pass = roll2;

        for (int i = 0; i < 6; i++) {
            if(pass < 14){
                printf(ANSI_COLOR_CYAN "\\      /"reset HYEL"%2s"HYEL"%2s" ANSI_COLOR_RESET, objects[pass][0], objects[pass][1]);
            }
            else{
                printf(ANSI_COLOR_CYAN "\\"reset HYEL"%2s%2s%2s"reset ANSI_COLOR_CYAN"/"reset HYEL"%2s%2s" ANSI_COLOR_RESET, objects[pass - 14][3], objects[pass - 14][4], objects[pass - 14][5], objects[pass][0], objects[pass][1]);
            }
            pass = pass + 2;
        }
        printf(ANSI_COLOR_CYAN "\\      /\n" ANSI_COLOR_RESET);


        pass = roll2;
        printf(" ");
        for (int i = 0; i < 6; i++) {
            printf(ANSI_COLOR_CYAN " \\____/"reset HRED "%5s" ANSI_COLOR_RESET, objects[pass][2]);
            pass = pass + 2;
        }
        printf(ANSI_COLOR_CYAN " \\____/" ANSI_COLOR_RESET);

        printf("\n  ");


        pass = roll1;
        for (int i = 0; i < 7; i++) {
            if(pass < 116){
                printf(ANSI_COLOR_CYAN "/"reset HYEL"%2s%2s"reset ANSI_COLOR_CYAN"\\"reset  HYEL"%2s%2s%2s" ANSI_COLOR_RESET, objects[pass][0], objects[pass][1], objects[pass + 1][3], objects[pass + 1][4], objects[pass + 1][5]);
            }
            else{
                printf(ANSI_COLOR_CYAN "/"reset HYEL"%2s%2s" reset HYEL"\\" ANSI_COLOR_RESET, objects[pass][0], objects[pass][1]);
            }
            pass = pass + 2;
        }
        printf("\n");

        pass = roll1;
        printf(ANSI_COLOR_YELLOW "%c" ANSI_COLOR_RESET,c++);
        for (int i = 0; i < 6; i++) {
            printf(ANSI_COLOR_CYAN "/"reset HRED "%6s"reset ANSI_COLOR_CYAN"\\____" ANSI_COLOR_RESET, objects[pass][2]);
            pass = pass + 2;
        }
        printf(ANSI_COLOR_CYAN "/"reset HRED "%6s"reset ANSI_COLOR_CYAN"\\" ANSI_COLOR_RESET, objects[pass][2]);
        pass = pass + 2;
        roll2=pass;
        roll1= pass - 1;
    }
    printf("\n ");
    pass=104;
    for (int i = 0; i < 7; i++) {
        printf(ANSI_COLOR_CYAN "\\"reset HYEL"%2s%2s%2s"reset ANSI_COLOR_CYAN"/    " ANSI_COLOR_RESET, objects[pass][3], objects[pass][4], objects[pass][5]);
        pass = pass + 2;
    }
    printf("\n ");
    for (int i = 0; i < 7; i++)
        printf(ANSI_COLOR_CYAN " \\____/     " ANSI_COLOR_RESET);

    puts("");
}




//Linked List Functions
struct Node *create_character(CHARACTER character){
    struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));
    new_node->character = character;
    new_node->next = NULL;

    return new_node;
}


void add_font(struct Node **head, struct Node *new_node){
    new_node->next = *head;
    *head = new_node;
}


void add_end(struct Node *head, struct Node *new_node){
    struct Node *current = head;
    while(current->next != NULL){
        current = current->next;
    }

    current->next = new_node;
    new_node->next = NULL;
}


void insert(struct Node **head, CHARACTER character){
    if(*head == NULL){
        add_font(head, create_character(character));
    }
    else{
        add_end(*head, create_character(character));

    }
}


void delete_node(struct Node **head, int which_character){
    struct Node *previous = NULL;
    struct Node *current = *head;

    if(*head == NULL)
        return;

    if((*head)->character.is_which == which_character){
        *head = current->next;
        current->next = NULL;
        free(current);
        return;
    }

    while(current){
        previous = current;
        current = current->next;

        if(current->character.is_which == which_character){
            previous->next = current->next;
            current->next = NULL;
            free(current);
            return;
        }
    }
}


struct Node *list_of_all_characters(){
    struct Node *list = (struct Node *)malloc(sizeof(struct Node));
    list = NULL;

    //SH = 0
    insert(&list, SH);
    //JW = 1
    insert(&list, JW);
    //JS = 2
    insert(&list, JS);
    //IL = 3
    insert(&list, IL);
    //MS = 4
    insert(&list, MS);
    //SG = 5
    insert(&list, SG);
    //WG = 6
    insert(&list, WG);
    //JB = 7
    insert(&list, JB);

    return list;
}


struct Node *get_character(struct Node *head, int index){
    struct Node *current = head;
    int i = 0;
    while(i < index){
        i++;
        current = current->next;
    }

    return current;
}


void print_list(struct Node *head, int index){
    struct Node *current = head;
    while(current){
        if(current->character.is_which == index) {
            printf(BHCYN "\t%s\n\tMove 1 to %d houses.\n%s\n" reset,
                   current->character.name, current->character.max_move, current->character.ability);
        }
        current = current->next;
    }
    puts("");
}




//Playing Functions


int in_array(int array[], int len, int key){
    for(int i = 0; i < len; i++){
        if(array[i] == key)
            return 1;
    }
    return 0;
}


void print_innocent_card(int index_character){
    switch (index_character) {
        case sh:
            printf("\n\n\t\t\t\t\t\t\t\t");
            printf(ANSI_COLOR_GREEN "%d)Sherlock Holmes\n\n" ANSI_COLOR_RESET, sh);
            break;
        case jw:
            printf("\n\n\t\t\t\t\t\t\t\t");
            printf(ANSI_COLOR_GREEN "%d)John H. Watson\n\n" ANSI_COLOR_RESET , jw);
            break;
        case js:
            printf("\n\n\t\t\t\t\t\t\t\t");
            printf(ANSI_COLOR_GREEN "%d)John Smith\n\n" ANSI_COLOR_RESET, js);
            break;
        case il:
            printf("\n\n\t\t\t\t\t\t\t\t");
            printf(ANSI_COLOR_GREEN "%d)Inspector Lestrade\n\n" ANSI_COLOR_RESET, il);
            break;
        case ms:
            printf("\n\n\t\t\t\t\t\t\t\t");
            printf(ANSI_COLOR_GREEN "%d)Miss Stealthy\n\n" ANSI_COLOR_RESET, ms);
            break;
        case sg:
            printf("\n\n\t\t\t\t\t\t\t\t");
            printf(ANSI_COLOR_GREEN "%d)Sergeant Goodley\n\n" ANSI_COLOR_RESET, sg);
            break;
        case wg:
            printf("\n\n\t\t\t\t\t\t\t\t");
            printf(ANSI_COLOR_GREEN "%d)William Gull\n\n" ANSI_COLOR_RESET, wg);
            break;
        case jb:
            printf("\n\n\t\t\t\t\t\t\t\t");
            printf(ANSI_COLOR_GREEN "%d)Jeremy Bert\n\n" ANSI_COLOR_RESET, jb);
            break;
        default:
            ;
    }

}


int get_innocent_card(int *used_innocent_cards){
    srand(time(NULL));

    int innocent_card;
    while(1) {
        int random = rand() % 8;
        if(!in_array(used_innocent_cards, 8, random)){
            innocent_card = random;
            break;
        }
    }

    return innocent_card;
}


struct cards *ShuffleCards(){
    struct cards *game_cards = (struct cards *) malloc(sizeof(struct cards));

    //seeding srand
    static int seed = INT_MAX;
    srand(seed);

    int i = 0;
    while(1){
        if(i == 4)
            break;
        int random_number = rand() % 8;
        if(!in_array(game_cards->firstSet, i, random_number)){
            game_cards->firstSet[i++] = random_number;
        }
    }


    for(int t = 0; t < 4; t++){
        for(int j = 0; j < 8; j++){
            if(!in_array(game_cards->firstSet, 4, j)){
                if(!in_array(game_cards->secondSet, t, j))
                    game_cards->secondSet[t] = j;
            }
        }
    }

    //update seed
    seed--;
    return game_cards;
}


int choice_card(){
    int card_index;
    printf("\n\n\t\t\t\t\t\t\t\a");
    printf(ANSI_COLOR_CYAN "with which character you play\n\n" ANSI_COLOR_RESET);
    printf( ANSI_COLOR_YELLOW "    \t\t\t\t\t\t\t\t\a?:" ANSI_COLOR_RESET);
    scanf("%d", &card_index);

    return card_index;
}



int when_use_ability(){
    int when;
    printf(ANSI_COLOR_CYAN "\n\n\t\t\t\t\t\t\tWhen you use character ability\n\n" ANSI_COLOR_RESET);
    printf( ANSI_COLOR_CYAN "\n\n\t\t\t\t\t\t\t\a1)before"
           "\n\n\t\t\t\t\t\t\t\a2)after\n\n" ANSI_COLOR_RESET);
    printf("    \t\t\t\t\t\t\t\t\a?:" ANSI_COLOR_RESET);
    scanf("%d", &when);

    return when;
}



int max_move_you_want(){
    int max_move;
    printf("\n\n\t\t\t\t\t\t\t\a");
    printf(ANSI_COLOR_CYAN " How many houses you want go\n\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "   \t\t\t\t\t\t\t\t\a?:" ANSI_COLOR_RESET);
    scanf("%d", &max_move);

    return max_move;
}


//empty = 0   building = 1  open-pit = 2   close-light = 3   out-range = 4   close-pit = 5   open-light = 6   close-exit = 7  open-exit = 8

int what_is_type_of_area(int **type_area, int row, int col){
    if(row >= 9 || col >= 13)
        return 4;

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 13; j++){
            if(i == row && j == col){
                return type_area[i][j];
            }
        }
    }
    return 4;
}



//UP_LEFT = 0, UP = 1, UP_RIGHT = 2, DOWN_RIGHT = 3, DOWN = 4, DOWN_LEFT = 5

int get_valid_direction(int **type_area, int character_index, struct Node *listOfCharacters){
    struct Node *character = get_character(listOfCharacters, character_index);
    int row = character->character.row;
    int col = character->character.col;

    //because miss stealthy can cross from building ...
    int Is_Miss_Stealthy = (character_index == ms);

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 13; j++){
            if(i == row && j == col){

                //check current location is manhole
                int type =  what_is_type_of_area(type_area, i, j);
                if(type == open_pit){
                    printf(ANSI_COLOR_MAGENTA "\n\n\t\t\t\t\t\tfrom which manhole you want get out\n\n" ANSI_COLOR_RESET);
                    if(row != 2 && col != 0 && type_area[2][0] == open_pit){
                        printf("\n\n\t\t\t\t\t\t\t");
                        printf(ANSI_COLOR_CYAN "--   pit1   = 6 --\n\n" ANSI_COLOR_RESET);
                    }
                    if(row != 6 && col != 2 && type_area[6][2] == open_pit){
                        printf("\n\n\t\t\t\t\t\t\t");
                        printf(ANSI_COLOR_CYAN "--   pit2   = 7 --\n\n" ANSI_COLOR_RESET);
                    }
                    if(row != 0 && col != 5 && type_area[0][5] == open_pit){
                        printf("\n\n\t\t\t\t\t\t\t");
                        printf(ANSI_COLOR_CYAN "--   pit3   = 8 --\n\n" ANSI_COLOR_RESET);
                    }
                    if(row != 3 && col != 5 && type_area[3][5] == open_pit){
                        printf("\n\n\t\t\t\t\t\t\t");
                        printf(ANSI_COLOR_CYAN "--   pit4   = 9 --\n\n" ANSI_COLOR_RESET);
                    }
                    if(row != 5 && col != 7 && type_area[5][7] == open_pit){
                        printf("\n\n\t\t\t\t\t\t\t");
                        printf(ANSI_COLOR_CYAN "--   pit5   = 10 --\n\n" ANSI_COLOR_RESET);
                    }
                    if(row != 8 && col != 7 && type_area[8][7] == open_pit){
                        printf("\n\n\t\t\t\t\t\t\t");
                        printf(ANSI_COLOR_CYAN "--   pit6   = 11 --\n\n" ANSI_COLOR_RESET);
                    }
                    if(row != 1 && col != 11 && type_area[0][11] == open_pit){
                        printf("\n\n\t\t\t\t\t\t\t");
                        printf(ANSI_COLOR_CYAN "--   pit7   = 12 --\n\n" ANSI_COLOR_RESET);
                    }
                    if(row != 4 && col != 12 && type_area[4][12] == open_pit){
                        printf("\n\n\t\t\t\t\t\t\t");
                        printf(ANSI_COLOR_CYAN "--   pit8   = 13 --\n\n" ANSI_COLOR_RESET);
                    }
                }

                if(Is_Miss_Stealthy){
                    printf("\n\n\t\t\t\t\t");
                    printf(ANSI_COLOR_BLUE "UP_LEFT = 0, UP = 1, UP_RIGHT = 2, DOWN_RIGHT = 3, DOWN = 4, DOWN_LEFT = 5\n\n" ANSI_COLOR_RESET);
                    printf("\n\n\t\t\t\t\t");
                    printf(ANSI_COLOR_RED "Take note that you cant stand on invalid house. just cross from them!\n\n" ANSI_COLOR_RESET);
                }

                //check up_left
                if(j % 2 == 0){
                    type =  what_is_type_of_area(type_area, i, j - 1);
                }
                else{
                    type =  what_is_type_of_area(type_area, i - 1, j - 1);
                }
                if(!Is_Miss_Stealthy && (type == empty || type == open_pit || type == close_pit)) {
                    printf("\n\n\t\t\t\t\t\t\t");
                    printf(ANSI_COLOR_BLUE "-- UP_Left = 0 --\n\n" ANSI_COLOR_RESET);
                }


                //check up
                type =  what_is_type_of_area(type_area, i - 1, j);
                if(!Is_Miss_Stealthy && (type == empty || type == open_pit || type == close_pit)) {
                    printf("\n\n\t\t\t\t\t\t\t");
                    printf(ANSI_COLOR_BLUE "-- UP = 1 --\n\n" ANSI_COLOR_RESET);
                }


                //check up_right
                if(j % 2 == 0){
                    type =  what_is_type_of_area(type_area, i, j + 1);
                }
                else{
                    type =  what_is_type_of_area(type_area, i - 1, j + 1);
                }
                if(!Is_Miss_Stealthy && (type == empty || type == open_pit || type == close_pit)) {
                    printf("\n\n\t\t\t\t\t\t\t");
                    printf(ANSI_COLOR_BLUE "-- UP_RIGHT = 2 --\n\n" ANSI_COLOR_RESET);
                }

                //check down_right
                if(j % 2 == 0){
                    type =  what_is_type_of_area(type_area, i + 1, j + 1);
                }
                else{
                    type =  what_is_type_of_area(type_area, i, j + 1);
                }
                if(!Is_Miss_Stealthy && (type == empty || type == open_pit || type == close_pit)){
                    printf("\n\n\t\t\t\t\t\t\t");
                    printf(ANSI_COLOR_BLUE "-- DOWN_RIGHT = 3 --\n\n" ANSI_COLOR_RESET);
                }

                //check down
                type =  what_is_type_of_area(type_area, i + 1, j);
                if(!Is_Miss_Stealthy && (type == empty || type == open_pit || type == close_pit)){
                    printf("\n\n\t\t\t\t\t\t\t");
                    printf(ANSI_COLOR_BLUE "-- DOWN = 4 --\n\n" ANSI_COLOR_RESET);
                }

                //check down_left
                if(j % 2 == 0){
                    type =  what_is_type_of_area(type_area, i + 1, j - 1);
                }
                else{
                    type =  what_is_type_of_area(type_area, i, j - 1);
                }
                if(!Is_Miss_Stealthy && (type == empty || type == open_pit || type == close_pit)){
                    printf("\n\n\t\t\t\t\t\t\t");
                    printf(ANSI_COLOR_BLUE "-- DOWN_LEFT = 5 --\n\n" ANSI_COLOR_RESET);
                }

                break;
            }
        }
    }

    int dir;
    printf(ANSI_COLOR_YELLOW "\n  \t\t\t\t\t\t\t\t\a?:" ANSI_COLOR_RESET);
    scanf("%d", &dir);

    return dir;
}


//if j % 2 == 0
//up_left->i, j-1 | up->i-1, j | up_right->i, j+1 | down_right->i+1, j+1 | down->i+1, j | down_left->i+1, j-1 |

//if j % 2 != 0
//up_left->i-1, j-1 | up->i-1, j | up_right->i-1, j+1 | down_right->i, j+1 | down->i+1, j | down_left->i, j-1 |


struct Coordinate *update_location(int direction, struct Node *character){
    int i = character->character.row;
    int j = character->character.col;



    // update location

    //if we do not cross manholes
    if(direction <= 5){
        if(j % 2 == 0){

            switch (direction) {
                case up_left:
                    character->character.row = i;
                    character->character.col = j - 1;
                    break;
                case up:
                    character->character.row = i - 1;
                    character->character.col = j;
                    break;
                case up_right:
                    character->character.row = i;
                    character->character.col = j + 1;
                    break;
                case down_right:
                    character->character.row = i + 1;
                    character->character.col = j + 1;
                    break;
                case down:
                    character->character.row = i + 1;
                    character->character.col = j;
                    break;
                case down_left:
                    character->character.row = i + 1;
                    character->character.col = j - 1;
                    break;
                default:
                    ;
            }
        }
        else{
            switch (direction) {
                case up_left:
                    character->character.row = i - 1;
                    character->character.col = j - 1;
                    break;
                case up:
                    character->character.row = i - 1;
                    character->character.col = j;
                    break;
                case up_right:
                    character->character.row = i - 1;
                    character->character.col = j + 1;
                    break;
                case down_right:
                    character->character.row = i;
                    character->character.col = j + 1;
                    break;
                case down:
                    character->character.row = i + 1;
                    character->character.col = j;
                    break;
                case down_left:
                    character->character.row = i;
                    character->character.col = j - 1;
                    break;
                default:
                    ;
            }
        }
    }
        //if we cross the manholes
        //initially manhole and there status
        //pit6 = 2, 0 open | pit7 = 6, 2 close | pit8 = 0, 5 open | pit9 = 3, 5 open |
        //pit10 = 5, 7 open | pit11 = 8, 7 open | pit12 = 0, 11 close | pit13 = 4, 12 open

    else{
        switch (direction) {
            case 6:
                character->character.row = 2;
                character->character.col = 0;
                break;
            case 7:
                character->character.row = 6;
                character->character.col = 2;
                break;
            case 8:
                character->character.row = 0;
                character->character.col = 5;
                break;
            case 9:
                character->character.row = 3;
                character->character.col = 5;
                break;
            case 10:
                character->character.row = 5;
                character->character.col = 7;
                break;
            case 11:
                character->character.row = 8;
                character->character.col = 7;
                break;
            case 12:
                character->character.row = 1;
                character->character.col = 11;
                break;
            case 13:
                character->character.row = 4;
                character->character.col = 12;
                break;
            default:
                ;
        }
    }

    struct Coordinate *coordinate = (struct Coordinate *) malloc(sizeof(struct Coordinate));

    coordinate->x = character->character.row;
    coordinate->y = character->character.col;

    return coordinate;
}



void InsertCharacterToDesirablePosition(struct Node *character, struct Area **Whitechapel, char stringAreaContent[][6][15]){
    int i = character->character.row;
    int j = character->character.col;

    int area = 0;
    for(int row = 0; row < 9; row++){
        for(int col = 0; col < 13; col++){
            if(row == i && col == j){
                //insert to appropriate location
                insert(&Whitechapel[row][col].list_characters_in, character->character);

                //update content area string
                if(strcmpi(stringAreaContent[area][0], "") == 0)
                    strcpy(stringAreaContent[area][0], character->character.name);

                else if(strcmpi(stringAreaContent[area][3], "") == 0)
                    strcpy(stringAreaContent[area][3], character->character.name);

                else if(strcmpi(stringAreaContent[area][4], "") == 0)
                    strcpy(stringAreaContent[area][4], character->character.name);

                else if(strcmpi(stringAreaContent[area][5], "") == 0)
                    strcpy(stringAreaContent[area][5], character->character.name);
                //break;
            }
            area++;

        }
    }

}


void RemoveCharacterFromCurrentPosition(int index, struct Node *character, struct Area **Whitechapel, char stringAreaContent[][6][15]){
    int i = character->character.row;
    int j = character->character.col;

    int area = 0;
    for(int row = 0; row < 9; row++){
        for(int col = 0; col < 13; col++){
            if(row == i && col == j){
                //delete was chosen character form Whitechapel
                delete_node(&Whitechapel[row][col].list_characters_in, index);

                //update content area string
                if(strcmpi(stringAreaContent[area][0], character->character.name) == 0)
                    strcpy(stringAreaContent[area][0],"");

                else if(strcmpi(stringAreaContent[area][3], character->character.name) == 0)
                    strcpy(stringAreaContent[area][3],"");

                else if(strcmpi(stringAreaContent[area][4], character->character.name) == 0)
                    strcpy(stringAreaContent[area][4],"");

                else if(strcmpi(stringAreaContent[area][5], character->character.name) == 0)
                    strcpy(stringAreaContent[area][5],"");

                //break;
            }
            area++;
        }
    }

}


void move_character(int direction, int index, struct Node *listOfCharacters, struct Area **Whitechapel, char stringAreaContent[][6][15]){
    struct Node *character = get_character(listOfCharacters, index);


    // removing section
    RemoveCharacterFromCurrentPosition(index, character, Whitechapel, stringAreaContent);


    // update location
    update_location(direction, character);


    // update map
    InsertCharacterToDesirablePosition(character, Whitechapel, stringAreaContent);
}


//SH = 0, JW = 1, JS = 2, IL = 3, MS = 4, SG = 5, WG = 6, JB = 7
int check_first_or_last_use_ability(int index_character){
    int type_of_use_of_ability;
    switch (index_character) {
        case sh:
            type_of_use_of_ability = MUST_be_used_at_the_end;
            break;
        case jw:
            type_of_use_of_ability = MUST_be_used_at_the_end;
            break;
        case js:
            type_of_use_of_ability = MUST_be_used_before_or_after;
            break;
        case il:
            type_of_use_of_ability = MUST_be_used_before_or_after;
            break;
        case ms:
            type_of_use_of_ability = CAN_be_used_during;
            break;
        case sg:
            type_of_use_of_ability = MUST_be_used_before_or_after;
            break;
        case wg:
            type_of_use_of_ability = CAN_be_used_instead;
            break;
        case jb:
            type_of_use_of_ability = MUST_be_used_before_or_after;
            break;
    }

    return type_of_use_of_ability;
}

void using_sh_ability(int *used_innocent_cards){
    //because mr.jack index is 0 so
    static int k = 1;
    int innocent_character = get_innocent_card(used_innocent_cards);
    puts(ANSI_COLOR_CYAN "\n\t\t\t\t\t\t\tOne of innocent character is:\n" ANSI_COLOR_RESET);
    print_innocent_card(innocent_character);

    //update used characters for innocent
    used_innocent_cards[k++] = innocent_character;

}


void using_jw_ability(struct Node *character){
    int standing_direction;
    printf("\n\n\t\t\t\t\t\t\t\tWhat is your standing direction");
    printf("\n\n\t\t\t\t\t");
    printf("UP_LEFT = 0, UP = 1, UP_RIGHT = 2, DOWN_RIGHT = 3, DOWN = 4, DOWN_LEFT = 5\n\n");
    printf("\n  \t\t\t\t\t\t\t\t\a?:");
    scanf("%d", &standing_direction);

    switch (standing_direction) {
        case up_left:
            character->character.direction = up_left;
            break;
        case up:
            character->character.direction = up;
            break;
        case up_right:
            character->character.direction = up_right;
            break;
        case down_right:
            character->character.direction = down_right;
            break;
        case down:
            character->character.direction = down;
            break;
        case down_left:
            character->character.direction = down_left;
            break;
        default:
            ;
    }

   // printf("\n\n\n\n\n\t\t\t\t\t\t\t-------direction----- %d\n\n", character->character.direction);
}


//initially lights and there status
//light1 = 6, 0 open |light2 = 1, 2 open |light3 = 1, 5 close |light4 = 5, 5 open |
//light5 = 3, 7 open |light6 = 7, 7 close |light7 = 6, 10 open |light8 = 2, 11 open |

struct Coordinate *light_coordinate(int light_number){
    struct Coordinate *coordinate = (struct Coordinate *) malloc(sizeof(struct Coordinate));

    switch (light_number) {
        case light1:
            coordinate->x = 6;
            coordinate->y = 1;
            break;
        case light2:
            coordinate->x = 1;
            coordinate->y = 2;
            break;
        case light3:
            coordinate->x = 1;
            coordinate->y = 5;
            break;
        case light4:
            coordinate->x = 5;
            coordinate->y = 5;
            break;
        case light5:
            coordinate->x = 3;
            coordinate->y = 7;
            break;
        case light6:
            coordinate->x = 7;
            coordinate->y = 7;
            break;
        case light7:
            coordinate->x = 6;
            coordinate->y = 10;
            break;
        case light8:
            coordinate->x = 2;
            coordinate->y = 11;
            break;
        default:
            ;
    }


    return coordinate;
}


//getting token1 and its type and replace with token2
void update_array_area_type(int **area_type, struct Coordinate *token1, struct Coordinate *token2, int type1, int type2){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 13; j++){
            if(token1->x == i && token1->y == j){
                area_type[i][j] = type2;
            }
            if(token2->x == i && token2->y == j){
                area_type[i][j] = type1;
            }
        }
    }

}


void update_whitechapel(int **area_type, struct Area **Whitechapel){

    //reset all status
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 13; j++){
            Whitechapel[i][j].is_out_range = 0;
            Whitechapel[i][j].is_empty = 0;
            Whitechapel[i][j].is_building = 0;
            Whitechapel[i][j].is_open_exit= 0;
            Whitechapel[i][j].is_open_light = 0;
            Whitechapel[i][j].is_open_pit = 0;
            Whitechapel[i][j].is_close_exit = 0;
            Whitechapel[i][j].is_close_light = 0;
            Whitechapel[i][j].is_close_pit = 0;
        }
    }

    //set new status
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 13; j++){
            switch (area_type[i][j]) {
                case empty:
                    Whitechapel[i][j].is_empty = 1;
                    break;
                case building:
                    Whitechapel[i][j].is_building = 1;
                    break;
                case open_pit:
                    Whitechapel[i][j].is_open_pit = 1;
                    break;
                case close_light:
                    Whitechapel[i][j].is_close_light = 1;
                    break;
                case out_range:
                    Whitechapel[i][j].is_out_range = 1;
                    break;
                case close_pit:
                    Whitechapel[i][j].is_close_pit = 1;
                    break;
                case open_light:
                    Whitechapel[i][j].is_open_light = 1;
                    break;
                case close_exit:
                    Whitechapel[i][j].is_close_exit = 1;
                    break;
                case open_exit:
                    Whitechapel[i][j].is_open_exit = 1;
            }
        }
    }
}


void update_area_content_token_names(struct Area **Whitechapel, char stringContent[][6][15]){
    int area = 0;
    for(int row = 0; row < 9; row++){
        for(int col = 0; col < 13; col++){
            if(Whitechapel[row][col].is_empty)
                strcpy(stringContent[area][2], "");

            else if(Whitechapel[row][col].is_building) {
                strcpy(stringContent[area][0], "BB");
                strcpy(stringContent[area][1], "BB");
                strcpy(stringContent[area][2], "BUILD");
                strcpy(stringContent[area][3], "BB");
                strcpy(stringContent[area][4], "BB");
                strcpy(stringContent[area][5], "BB");
            }

            else if(Whitechapel[row][col].is_open_pit){
                if(row == 2 && col == 0)
                    strcpy(stringContent[area][2], "OPit1");
                else if(row == 6 && col == 2)
                    strcpy(stringContent[area][2], "OPit2");
                else if(row == 0 && col == 5)
                    strcpy(stringContent[area][2], "OPit3");
                else if(row == 3 && col == 5)
                    strcpy(stringContent[area][2], "OPit4");
                else if(row == 5 && col == 7)
                    strcpy(stringContent[area][2], "OPit5");
                else if(row == 8 && col == 7)
                    strcpy(stringContent[area][2], "OPit6");
                else if(row == 1 && col == 11)
                    strcpy(stringContent[area][2], "OPit7");
                else if(row == 4 && col == 12)
                    strcpy(stringContent[area][2], "OPit8");
            }


            else if(Whitechapel[row][col].is_close_pit){
                if(row == 2 && col == 0)
                    strcpy(stringContent[area][2], "CPit1");
                else if(row == 6 && col == 2)
                    strcpy(stringContent[area][2], "CPit2");
                else if(row == 0 && col == 5)
                    strcpy(stringContent[area][2], "CPit3");
                else if(row == 3 && col == 5)
                    strcpy(stringContent[area][2], "CPit4");
                else if(row == 5 && col == 7)
                    strcpy(stringContent[area][2], "CPit5");
                else if(row == 8 && col == 7)
                    strcpy(stringContent[area][2], "CPit6");
                else if(row == 1 && col == 11)
                    strcpy(stringContent[area][2], "CPit7");
                else if(row == 4 && col == 12)
                    strcpy(stringContent[area][2], "CPit8");
            }

            else if(Whitechapel[row][col].is_open_light){
                if(row == 6 && col == 1)
                    strcpy(stringContent[area][2], "OLit1");
                else if(row == 1 && col == 2)
                    strcpy(stringContent[area][2], "OLit2");
                else if(row == 1 && col == 5)
                    strcpy(stringContent[area][2], "OLit3");
                else if(row == 5 && col == 5)
                    strcpy(stringContent[area][2], "OLit4");
                else if(row == 3 && col == 7)
                    strcpy(stringContent[area][2], "OLit5");
                else if(row == 7 && col == 7)
                    strcpy(stringContent[area][2], "OLit6");
                else if(row == 6 && col == 10)
                    strcpy(stringContent[area][2], "OLit7");
                else if(row == 2 && col == 11)
                    strcpy(stringContent[area][2], "OLit8");
            }

            else if(Whitechapel[row][col].is_close_light){
                if(row == 6 && col == 1)
                    strcpy(stringContent[area][2], "CLit1");
                else if(row == 1 && col == 2)
                    strcpy(stringContent[area][2], "CLit2");
                else if(row == 1 && col == 5)
                    strcpy(stringContent[area][2], "CLit3");
                else if(row == 5 && col == 5)
                    strcpy(stringContent[area][2], "CLit4");
                else if(row == 3 && col == 7)
                    strcpy(stringContent[area][2], "CLit5");
                else if(row == 7 && col == 7)
                    strcpy(stringContent[area][2], "CLit6");
                else if(row == 6 && col == 10)
                    strcpy(stringContent[area][2], "CLit7");
                else if(row == 2 && col == 11)
                    strcpy(stringContent[area][2], "CLit8");
            }

            else if(Whitechapel[row][col].is_open_exit){
                if(row == 0 && col == 1)
                    strcpy(stringContent[area][2], "OOut1");
                else if(row == 8 && col == 1)
                    strcpy(stringContent[area][2], "OOut2");
                else if(row == 0 && col == 11)
                    strcpy(stringContent[area][2], "OOut3");
                else if(row == 7 && col == 12)
                    strcpy(stringContent[area][2], "OOut4");
            }


            else if(Whitechapel[row][col].is_close_exit){
                if(row == 0 && col == 1)
                    strcpy(stringContent[area][2], "COut1");
                else if(row == 8 && col == 1)
                    strcpy(stringContent[area][2], "COut2");
                else if(row == 0 && col == 11)
                    strcpy(stringContent[area][2], "COut3");
                else if(row == 7 && col == 12)
                    strcpy(stringContent[area][2], "COut4");
            }


            else if(Whitechapel[row][col].is_out_range)
                strcpy(stringContent[area][2], "EXTRA");

            area++;
        }
    }
}


void using_js_ability(int **area_type, struct Area **Whitechapel, char stringContent[][6][15]){

    int num_open_light;

    printf(ANSI_COLOR_BLUE "\n\n\t\t\t\t\t\t\tFirst enter the number of open light\n" ANSI_COLOR_RESET);
    printf("\n  \t\t\t\t\t\t\t\t\a?:");
    scanf("%d", &num_open_light);

    int num_close_light;
    printf(ANSI_COLOR_RED "\n\n\t\t\t\t\t\t\tThen enter the number of close light\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "\n  \t\t\t\t\t\t\t\t\a?:" ANSI_COLOR_RESET);
    scanf("%d", &num_close_light);



    struct Coordinate *open_light_coor = light_coordinate(num_open_light);
    struct Coordinate *close_light_coor = light_coordinate(num_close_light);

    //close-light = 3   open-light = 6
    update_array_area_type(area_type, open_light_coor, close_light_coor, open_light, close_light);
    update_whitechapel(area_type, Whitechapel);
    update_area_content_token_names(Whitechapel, stringContent);

}


struct Coordinate *exit_coordinate(int out_number){
    struct Coordinate *coordinate = (struct Coordinate *) malloc(sizeof(struct Coordinate));
    switch (out_number) {
        case out1:
            coordinate->x = 0;
            coordinate->y = 1;
            break;
        case out2:
            coordinate->x = 8;
            coordinate->y = 1;
            break;
        case out3:
            coordinate->x = 0;
            coordinate->y = 11;
            break;
        case out4:
            coordinate->x = 7;
            coordinate->y = 12;
            break;
        default:
            ;
    }

    return coordinate;
}


void using_il_ability(int **area_type, struct Area **Whitechapel, char stringContent[][6][15]){

    int num_open_exit;
    printf(ANSI_COLOR_BLUE "\n\n\t\t\t\t\t\t\tFirst enter the number of open exit\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "\n  \t\t\t\t\t\t\t\t\a?:" ANSI_COLOR_RESET);
    scanf("%d", &num_open_exit);

    int num_close_exit;
    printf(ANSI_COLOR_RED "\n\n\t\t\t\t\t\t\tThen enter the number of close exit\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "\n  \t\t\t\t\t\t\t\t\a?:" ANSI_COLOR_RESET);
    scanf("%d", &num_close_exit);

    struct Coordinate *open_exit_coor = exit_coordinate(num_open_exit);
    struct Coordinate *close_exit_coor = exit_coordinate(num_close_exit);

    //close-exit =  7  open-exit = 8
    update_array_area_type(area_type, open_exit_coor, close_exit_coor, open_exit, close_exit);
    update_whitechapel(area_type, Whitechapel);
    update_area_content_token_names(Whitechapel, stringContent);
}


//closing up to 3 character to himself
//detecting count of character with comparing character_index with -1

int take_name_get_index(char *character_name){
    int index = -1;
    if(strcmpi(character_name, "SH") == 0)
        index = sh;
    else if(strcmpi(character_name, "JW") == 0)
        index = jw;
    else if(strcmpi(character_name, "JS") == 0)
        index = js;
    else if(strcmpi(character_name, "IL") == 0)
        index = il;
    else if(strcmpi(character_name, "MS") == 0)
        index = ms;
    else if(strcmpi(character_name, "SG") == 0)
        index = sg;
    else if(strcmpi(character_name, "WG") == 0)
        index = wg;
    else if(strcmpi(character_name, "JB") == 0)
        index = jb;

    return index;
}

void using_sg_ability(int **type_area, struct Node *list_characters, struct Area **Whitechapel, char stringContent[][6][15]){

    int count;
    printf(ANSI_COLOR_BLUE "\n\n\t\t\t\t\t\t\tHow many character you want move" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "\n  \t\t\t\t\t\t\t\t\a?:" ANSI_COLOR_RESET);
    scanf("%d", &count);


    for(int i = 0; i < count; i++){

        char character_name[10];
        printf(ANSI_COLOR_RED "\n\n\t\t\t\t\t\t\tEnter name of character you want move" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_YELLOW "\n  \t\t\t\t\t\t\t\t\a?:" ANSI_COLOR_RESET);
        scanf("\n%[^\n]", character_name);

        int which_character = take_name_get_index(character_name);
        int max_move = max_move_you_want();
        for (int j = 0; j < max_move; j++) {
            CreateMap(stringContent);
            int dir = get_valid_direction(type_area, which_character, list_characters);
            move_character(dir, which_character, list_characters, Whitechapel, stringContent);
        }
        CreateMap(stringContent);
    }


}


void using_wg_ability(struct Node *listOfCharacters, struct Area **Whitechapel, char stringContent[][6][15]){
    char character_name[10];
    printf(ANSI_COLOR_BLUE "\n\n\t\t\t\t\t\t\tEnter name of character you want replace location" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "\n\n  \t\t\t\t\t\t\t\t\a?:" ANSI_COLOR_RESET);
    scanf("\n%[^\n]", character_name);


    //finding out character index
    int index = take_name_get_index(character_name);


    struct Node *character = get_character(listOfCharacters, index);
    struct Node *wg_character = get_character(listOfCharacters, wg);

    int i1_temp = character->character.row;
    int j1_temp = character->character.col;

    //changing location of desirable character
    RemoveCharacterFromCurrentPosition(index, character, Whitechapel, stringContent);
    //taking location of wg to desirable character
    character->character.row = wg_character->character.row;
    character->character.col = wg_character->character.col;

    InsertCharacterToDesirablePosition(character, Whitechapel, stringContent);



    //changing location of WG
    RemoveCharacterFromCurrentPosition(wg, wg_character, Whitechapel, stringContent);
    //taking location of desirable character to wg
    wg_character->character.row = i1_temp;
    wg_character->character.col = j1_temp;

    InsertCharacterToDesirablePosition(wg_character, Whitechapel, stringContent);


}



//---------------------------------------------------------------
struct Coordinate *manhole_coordinate(int pit_number){
    struct Coordinate *coordinate = (struct Coordinate *) malloc(sizeof(struct Coordinate));

    switch (pit_number) {
        case pit1:
            coordinate->x = 2;
            coordinate->y = 0;
            break;
        case pit2:
            coordinate->x = 6;
            coordinate->y = 2;
            break;
        case pit3:
            coordinate->x = 0;
            coordinate->y = 5;
            break;
        case pit4:
            coordinate->x = 3;
            coordinate->y = 5;
            break;
        case pit5:
            coordinate->x = 5;
            coordinate->y = 7;
            break;
        case pit6:
            coordinate->x = 8;
            coordinate->y = 7;
            break;
        case pit7:
            coordinate->x = 1;
            coordinate->y = 11;
            break;
        case pit8:
            coordinate->x = 4;
            coordinate->y = 12;
            break;
        default:
            ;
    }

    return coordinate;
}



void using_jb_ability(int **area_type, struct Area **Whitechapel, char stringContent[][6][15]) {
    int num_open_pit;
    printf(ANSI_COLOR_BLUE "\n\n\t\t\t\t\t\t\tFirst enter the number of open pit\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "\n  \t\t\t\t\t\t\t\t\a?:" ANSI_COLOR_RESET);
    scanf("%d", &num_open_pit);

    int num_close_pit;
    printf(ANSI_COLOR_RED "\n\n\t\t\t\t\t\t\tThen enter the number of close pit\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "\n  \t\t\t\t\t\t\t\t\a?:" ANSI_COLOR_RESET);
    scanf("%d", &num_close_pit);

    struct Coordinate *open_pit_coor = manhole_coordinate(num_open_pit);
    struct Coordinate *close_pit_coor = manhole_coordinate(num_close_pit);

    //close-pit =  5  open-pit = 2
    update_array_area_type(area_type, open_pit_coor, close_pit_coor, open_pit, close_pit);
    update_whitechapel(area_type, Whitechapel);
    update_area_content_token_names(Whitechapel, stringContent);

}



void use_ability(int which_character, struct Node *list_characters, struct Area **Whitechapel, int *used_innocent_cards, int **type_area, char stringAreaContent[][6][15]) {

    int type_of_use_of_ability_of_character = check_first_or_last_use_ability(which_character);
//    struct Node *list_characters = list_of_all_characters();
    switch (which_character) {
        case sh:
            using_sh_ability(used_innocent_cards);
            break;
        case jw: {
            using_jw_ability(get_character(list_characters, jw));
            break;
        }
        case js: {
            using_js_ability(type_area, Whitechapel, stringAreaContent);
            break;
        }
        case il: {
            using_il_ability(type_area, Whitechapel, stringAreaContent);
            break;
        }
        case ms:
            //nothing
            break;
        case sg: {
            using_sg_ability(type_area, list_characters, Whitechapel, stringAreaContent);
            break;
        }
        case wg: {
            using_wg_ability(list_characters, Whitechapel, stringAreaContent);
            break;
        }
        case jb: {
            using_jb_ability(type_area, Whitechapel, stringAreaContent);
            break;
        }

        default:
            ;
    }

}



void print_set_cards(int which_set, struct cards *game_cards, int *used_character_index) {

    struct Node *list_characters = list_of_all_characters();

    // key stored couples of set
    int key = which_set / 2;
    static int flag_title_contains_call_number = 1;

    switch (key) {
        // which means we are in first couples of set
        case 0: {

            if (which_set == 0) {

                if(flag_title_contains_call_number %  5 != 0)
                    puts(ANSI_COLOR_YELLOW GRNHB"\n\n\n\t\t\t\t\t\t\t--------------first set------------\n\n\n" ANSI_COLOR_RESET);

                for (int i = 0; i < 4; i++) {
                    if(!in_array(used_character_index, 4, game_cards->firstSet[i])){
                        printf(YELHB UMAG"\n\tIndex of character is %d\n\n" ANSI_COLOR_RESET , game_cards->firstSet[i]);
                        print_list(list_characters, game_cards->firstSet[i]);
                    }
                }
            } else if (which_set == 1) {

                if(flag_title_contains_call_number %  5 != 0)
                    puts(ANSI_COLOR_YELLOW GRNHB"\n\n\n\t\t\t\t\t\t\t--------------second set------------\n\n\n" ANSI_COLOR_RESET);

                for (int i = 0; i < 4; i++) {
                    if(!in_array(used_character_index, 4, game_cards->secondSet[i])){
                        printf(YELHB UMAG"\n\tIndex of character is %d\n\n" ANSI_COLOR_RESET, game_cards->secondSet[i]);
                        print_list(list_characters, game_cards->secondSet[i]);
                    }
                }
            }
            break;
        }

            // which means we are in second couples of set

        case 1: {

            if (which_set == 2) {

                if(flag_title_contains_call_number %  5 != 0)
                    puts(ANSI_COLOR_YELLOW GRNHB"\n\n\n\t\t\t\t\t\t\t--------------third set------------\n\n\n" ANSI_COLOR_RESET);

                for (int i = 0; i < 4; i++) {
                    if(!in_array(used_character_index, 4, game_cards->firstSet[i])){
                        printf(YELHB UMAG"\n\tIndex of character is %d\n\n" ANSI_COLOR_RESET, game_cards->firstSet[i]);
                        print_list(list_characters, game_cards->firstSet[i]);
                    }
                }
            } else if (which_set == 3) {
                if(flag_title_contains_call_number %  5 != 0)
                    puts(GRNHB"\n\n\n\t\t\t\t\t\t--------------fourth set------------\n\n\n" ANSI_COLOR_RESET);

                for (int i = 0; i < 4; i++) {
                    if(!in_array(used_character_index, 4, game_cards->secondSet[i])){
                        printf(YELHB UMAG"\n\tIndex of character is %d\n\n" ANSI_COLOR_RESET, game_cards->secondSet[i]);
                        print_list(list_characters, game_cards->secondSet[i]);
                    }
                }
            }

            break;
        }

            // which means we are in third couples of set
        case 2: {

            if (which_set == 4) {

                if(flag_title_contains_call_number %  5 != 0)
                    puts(ANSI_COLOR_YELLOW GRNHB"\n\n\n\t\t\t\t\t\t\t--------------fifth set------------\n\n\n" ANSI_COLOR_RESET);

                for (int i = 0; i < 4; i++) {
                    if(!in_array(used_character_index, 4, game_cards->firstSet[i])){
                        printf(YELHB UMAG"\n\tIndex of character is %d\n\n" ANSI_COLOR_RESET, game_cards->firstSet[i]);
                        print_list(list_characters, game_cards->firstSet[i]);
                    }
                }
            } else if (which_set == 5) {
                if(flag_title_contains_call_number %  5 != 0)
                    puts(ANSI_COLOR_YELLOW GRNHB"\n\n\n\t\t\t\t\t\t\t--------------sixth set------------\n\n\n" ANSI_COLOR_RESET);

                for (int i = 0; i < 4; i++) {
                    if(!in_array(used_character_index, 4, game_cards->secondSet[i])){
                        printf(YELHB UMAG"\n\tIndex of character is %d\n\n" ANSI_COLOR_RESET, game_cards->secondSet[i]);
                        print_list(list_characters, game_cards->secondSet[i]);
                    }
                }
            }

            break;
        }

            // which means we are in last couples of set
        case 3: {

            if (which_set == 6) {

                if(flag_title_contains_call_number %  5 != 0)
                    puts(ANSI_COLOR_YELLOW GRNHB"\n\n\n\t\t\t\t\t\t\t--------------seventh set------------\n\n\n" ANSI_COLOR_RESET);

                for (int i = 0; i < 4; i++) {
                    if(!in_array(used_character_index, 4, game_cards->firstSet[i])){
                        printf(YELHB UMAG"\n\tIndex of character is %d\n\n" ANSI_COLOR_RESET, game_cards->firstSet[i]);
                        print_list(list_characters, game_cards->firstSet[i]);
                    }
                }
            } else if (which_set == 7) {

                if(flag_title_contains_call_number %  5 != 0)
                    puts(ANSI_COLOR_YELLOW GRNHB"\n\n\n\t\t\t\t\t\t\t--------------eighth set------------\n\n\n");

                for (int i = 0; i < 4; i++) {
                    if(!in_array(used_character_index, 4, game_cards->secondSet[i])){
                        printf(YELHB UMAG"\n\tIndex of character is %d\n\n" ANSI_COLOR_RESET, game_cards->secondSet[i]);
                        print_list(list_characters, game_cards->secondSet[i]);
                    }
                }
            }

            break;
        }
        default:
            break;
    }

    flag_title_contains_call_number++;

}


void print_turn(int i, int which_set){

    //first and last turn
    if(i == 0 || i == 3){
        if(which_set % 2 == 0){
            printf("\n\n \t\t\t\t\t\t\t\a");
            printf(CYNHB ANSI_COLOR_RED"----It's turn of inspector----\n\n\n" ANSI_COLOR_RESET);
        }
        else{
            printf("\n\n \t\t\t\t\t\t\t\a");
            printf(REDHB ANSI_COLOR_BLUE"----It's turn of Mr.Jack----\n\n\n" ANSI_COLOR_RESET);
        }
    }
        //middle turns
    else{
        if(which_set % 2 == 0){
            printf("\n\n \t\t\t\t\t\t\t\a");
            printf(REDHB ANSI_COLOR_BLUE"----It's turns of Mr.Jack----\n\n\n" ANSI_COLOR_RESET);
        }
        else{
            printf("\n\n \t\t\t\t\t\t\t\a");
            printf(CYNHB ANSI_COLOR_RED"----It's turns of inspector----\n\n\n" ANSI_COLOR_RESET);
        }
    }

}


void playing_actions(int which_set, struct cards *game_cards, struct Area **Whitechapel, int *used_character_index,
                     struct Node *list_characters, char stringAreaContent[][6][15], int **type_area, int *used_innocent_cards, int mr_jack){


    //update character is_mr_jack
    get_character(list_characters, mr_jack)->character.Mr_Jack = 1;



    //Initially, print random card for Mr.Jack
    if(which_set == 0) {
        system("cls");
        printf(ANSI_COLOR_RED MAGHB "\n\n\n\t\t\t\t\t\t\t\tEnter to Show Mr.Jack \n" ANSI_COLOR_RESET);
        getch();
        //first print of map
        CreateMap(stringAreaContent);
        printf(ANSI_COLOR_RED MAGHB "\n\n\n\t\t\t\t\t\t\t\tMr.Jack Character Is: \n" ANSI_COLOR_RESET);
        print_innocent_card(mr_jack);
    }

    print_set_cards(which_set, game_cards, used_character_index);

    //moving section
    //if set 0, 2, 4, 6 so at first and last inspector plays
    //else if set 1, 3, 5, 7 so at first and last mr.jack plays
    int k = 0;
    for(int i = 0; i < 4; i++) {
        print_turn(i, which_set);


        int which_character = choice_card();
        //update used character index
        used_character_index[k++] = which_character;

        int type_of_use_of_ability_of_character = check_first_or_last_use_ability(which_character);

        switch (type_of_use_of_ability_of_character) {
            case MUST_be_used_before_or_after:{
                //when == 1 -> before,  when == 2 -> after
                int when = when_use_ability();
                if(when == 1){
                    //use ability
                    //take note---------------------------------------------------------->
                    CreateMap(stringAreaContent);
                    use_ability(which_character, list_characters, Whitechapel, used_innocent_cards, type_area, stringAreaContent);

                    //moving section
                    //take note---------------------------------------------------------->
                    CreateMap(stringAreaContent);
                    int max_move = max_move_you_want();
                    for (int j = 0; j < max_move; j++) {
                        CreateMap(stringAreaContent);
                        int dir = get_valid_direction(type_area, which_character, list_characters);
                        move_character(dir, which_character, list_characters, Whitechapel, stringAreaContent);
                    }
                    CreateMap(stringAreaContent);
                    print_set_cards(which_set, game_cards, used_character_index);

                }
                else if(when == 2){

                    //moving section
                    int max_move = max_move_you_want();
                    for (int j = 0; j < max_move; j++) {
                        CreateMap(stringAreaContent);
                        int dir = get_valid_direction(type_area, which_character, list_characters);
                        move_character(dir, which_character, list_characters, Whitechapel, stringAreaContent);
                    }
                    CreateMap(stringAreaContent);
                    print_set_cards(which_set, game_cards, used_character_index);


                    //use ability
                    CreateMap(stringAreaContent);
                    use_ability(which_character, list_characters,Whitechapel, used_innocent_cards, type_area, stringAreaContent);
                    CreateMap(stringAreaContent);
                    print_set_cards(which_set, game_cards, used_character_index);

                }

                break;
            }

            case MUST_be_used_at_the_end:{
                //moving section
                int max_move = max_move_you_want();
                for (int j = 0; j < max_move; j++) {
                    CreateMap(stringAreaContent);
                    int dir = get_valid_direction(type_area, which_character, list_characters);
                    move_character(dir, which_character, list_characters, Whitechapel, stringAreaContent);
                }
                CreateMap(stringAreaContent);
                print_set_cards(which_set, game_cards, used_character_index);


                //use ability
                use_ability(which_character, list_characters,Whitechapel, used_innocent_cards, type_area, stringAreaContent);

                break;
            }


            case CAN_be_used_instead: {
                int which;
                printf(ANSI_COLOR_GREEN "\n\n\t\t\t\t\t\t\tIf you 1)Using ability, 2)Moving instead" ANSI_COLOR_RESET);
                printf(ANSI_COLOR_YELLOW "\n\n  \t\t\t\t\t\t\t\t\a?:" ANSI_COLOR_RESET);
                scanf("%d", &which);

                //1)Using ability
                if(which == 1){
                    use_ability(which_character, list_characters, Whitechapel, used_innocent_cards, type_area, stringAreaContent);
                    CreateMap(stringAreaContent);
                    print_set_cards(which_set, game_cards, used_character_index);
                }
                //2)Moving instead
                else{
                    int max_move = max_move_you_want();
                    for (int j = 0; j < max_move; j++) {
                        CreateMap(stringAreaContent);
                        int dir = get_valid_direction(type_area, which_character, list_characters);
                        move_character(dir, which_character, list_characters, Whitechapel, stringAreaContent);
                    }
                    CreateMap(stringAreaContent);
                    print_set_cards(which_set, game_cards, used_character_index);
                }


                break;
            }
            case CAN_be_used_during:{

                int max_move = max_move_you_want();
                for (int j = 0; j < max_move; j++) {
                    CreateMap(stringAreaContent);
                    int dir = get_valid_direction(type_area, which_character, list_characters);
                    move_character(dir, which_character, list_characters, Whitechapel, stringAreaContent);
                }
                CreateMap(stringAreaContent);
                print_set_cards(which_set, game_cards, used_character_index);

                break;
            }

            default:
                ;
        }

        check_inspector_win_lose(i, which_set, mr_jack);
    }

}


int **check_hex_illuminated_by_the_lantern(int **type_area, struct Node *list_characters){
    struct Node *character = get_character(list_characters, jw);
    int i = character->character.row;
    int j = character->character.col;
    int direction = character->character.direction;

    int **illuminated_hexes = (int **) malloc(13 * sizeof(int *));
    for(int t = 0; t < 13; t++)
        illuminated_hexes[t] = (int *) malloc(2 * sizeof(int));

    for(int a = 0; a < 13; a++){
        illuminated_hexes[a][0] = -1;
        illuminated_hexes[a][1] = -1;
    }

    int k = 0;
    int type;
    switch (direction) {
        case up_left:{
               while((0 <= i && i < 9) && (0 <= j && j < 13)){
                   if(j % 2 == 0){
                       j -= 1;
                       illuminated_hexes[k][0] = i;
                       illuminated_hexes[k][1] = j;
                       k++;
                       type = what_is_type_of_area(type_area, i, j);
                       if(type == building || type == out_range || type == open_light || type == close_light)
                           break;
                   }
                   else{
                       i -= 1;
                       j -= 1;
                       illuminated_hexes[k][0] = i;
                       illuminated_hexes[k][1] = j;
                       k++;
                       type = what_is_type_of_area(type_area, i, j);
                       if(type == building || type == out_range || type == open_light || type == close_light)
                           break;
                   }
               }

            break;
        }

        case up:{
            while((0 <= i && i < 9) && (0 <= j && j < 13)){
                    i -= 1;
                    illuminated_hexes[k][0] = i;
                    illuminated_hexes[k][1] = j;
                    k++;
                    type = what_is_type_of_area(type_area, i, j);
                    if(type == building || type == out_range || type == open_light || type == close_light)
                        break;
            }
            break;
        }

        case up_right:{
            while((0 <= i && i < 9) && (0 <= j && j < 13)){
                if(j % 2 == 0){
                    j += 1;
                    illuminated_hexes[k][0] = i;
                    illuminated_hexes[k][1] = j;
                    k++;
                    type = what_is_type_of_area(type_area, i, j);
                    if(type == building || type == out_range || type == open_light || type == close_light)
                        break;
                }
                else{
                    i -= 1;
                    j += 1;
                    illuminated_hexes[k][0] = i;
                    illuminated_hexes[k][1] = j;
                    k++;
                    type = what_is_type_of_area(type_area, i, j);
                    if(type == building || type == out_range || type == open_light || type == close_light)
                        break;
                }
            }

            break;
        }

        case down_right:{
            while((0 <= i && i < 9) && (0 <= j && j < 13)){
                if(j % 2 == 0){
                    i += 1;
                    j += 1;
                    illuminated_hexes[k][0] = i;
                    illuminated_hexes[k][1] = j;
                    k++;
                    type = what_is_type_of_area(type_area, i, j);
                    if(type == building || type == out_range || type == open_light || type == close_light)
                        break;
                }
                else{
                    j += 1;
                    illuminated_hexes[k][0] = i;
                    illuminated_hexes[k][1] = j;
                    k++;
                    type = what_is_type_of_area(type_area, i, j);
                    if(type == building || type == out_range || type == open_light || type == close_light)
                        break;
                }
            }

            break;
        }

        case down:{
            while((0 <= i && i < 9) && (0 <= j && j < 13)){
                i += 1;
                illuminated_hexes[k][0] = i;
                illuminated_hexes[k][1] = j;
                k++;
                type = what_is_type_of_area(type_area, i, j);
                if(type == building || type == out_range || type == open_light || type == close_light)
                    break;
            }

            break;
        }

        case down_left:{
            while((0 <= i && i < 9) && (0 <= j && j < 13)){
                if(j % 2 == 0){
                    i += 1;
                    j -= 1;
                    illuminated_hexes[k][0] = i;
                    illuminated_hexes[k][1] = j;
                    k++;
                    type = what_is_type_of_area(type_area, i, j);
                    if(type == building || type == out_range || type == open_light || type == close_light)
                        break;
                }
                else{
                    j -= 1;
                    illuminated_hexes[k][0] = i;
                    illuminated_hexes[k][1] = j;
                    k++;
                    type = what_is_type_of_area(type_area, i, j);
                    if(type == building || type == out_range || type == open_light || type == close_light)
                        break;
                }
            }

            break;
        }
        default:
            ;
    }

    return illuminated_hexes;
}


void check_visibility(int **type_area, struct Node *list_characters, char stringAreaContent[][6][15],struct Area **Whitechapel, int mr_jack){

    int **illuminated_hexes = check_hex_illuminated_by_the_lantern(type_area, list_characters);
    for(int cha = 0; cha < 8; cha++) {
        int flag = 0;
        struct Node *character = get_character(list_characters, cha);
        int row = character->character.row;
        int col = character->character.col;

        //check current house

        for (int i = 0; i < 8; i++) {
            struct Node *character_surr = get_character(list_characters, i);
            int x = character_surr->character.row;
            int y = character_surr->character.col;
            if (i != take_name_get_index(character->character.name) && x == row && y == col) {
                character->character.is_visible = 1;
                flag = 1;
                break;
            }
        }


        //check surrounding houses
        int type;
        //check up_left
        if (col % 2 == 0) {
            type = what_is_type_of_area(type_area, row, col - 1);
        } else {
            type = what_is_type_of_area(type_area, row - 1, col - 1);
        }
        if (type == open_light) {
            character->character.is_visible = 1;
            flag = 1;
        }


        //check up
        type = what_is_type_of_area(type_area, row - 1, col);
        if (type == open_light) {
            character->character.is_visible = 1;
            flag = 1;
        }


        //check up_right
        if (col % 2 == 0) {
            type = what_is_type_of_area(type_area, row, col + 1);
        } else {
            type = what_is_type_of_area(type_area, row - 1, col + 1);
        }
        if (type == open_light) {
            character->character.is_visible = 1;
            flag = 1;
        }

        //check down_right
        if (col % 2 == 0) {
            type = what_is_type_of_area(type_area, row + 1, col + 1);
        } else {
            type = what_is_type_of_area(type_area, row, col + 1);
        }
        if (type == open_light) {
            character->character.is_visible = 1;
            flag = 1;
        }

        //check down
        type = what_is_type_of_area(type_area, row + 1, col);
        if (type == open_light) {
            character->character.is_visible = 1;
            flag = 1;
        }

        //check down_left
        if (col % 2 == 0) {
            type = what_is_type_of_area(type_area, row + 1, col - 1);
        } else {
            type = what_is_type_of_area(type_area, row, col - 1);
        }
        if (type == open_light) {
            character->character.is_visible = 1;
            flag = 1;
        }

        //check_hex_illuminated_by_the_lantern

        for(int i = 0; i < 13; i++){
            if(row == illuminated_hexes[i][0] && col == illuminated_hexes[i][1]){
                character->character.is_visible = 1;
                flag = 1;
                break;
            }
        }

        if(!flag){
            character->character.is_visible = 0;
        }
    }

    struct Node *MrJack = get_character(list_characters, mr_jack);
    if(MrJack->character.is_visible){

        //illustrate innocent characters
        for(int c = 0; c < 8; c++){
            struct Node *inno_character = get_character(list_characters, c);
            int row = inno_character->character.row;
            int col = inno_character->character.col;
            if(!inno_character->character.is_visible){
                //changing innocent name
                char tmp[3] = {(char)tolower(inno_character->character.name[0]), (char)tolower(inno_character->character.name[1]), '\0'};
                strcpy(inno_character->character.name, tmp);
                //delete_node(&Whitechapel[row][col].list_characters_in, inno_character->character.is_which);
                RemoveCharacterFromCurrentPosition(inno_character->character.is_which, inno_character, Whitechapel, stringAreaContent);

                //insert(&Whitechapel[row][col].list_characters_in, inno_character->character);
                InsertCharacterToDesirablePosition(inno_character, Whitechapel, stringAreaContent);

            }
        }
        CreateMap(stringAreaContent);
        printf("\n\n\t\t\t\t\t\t\t\t\a");
        printf(HMAG "Mr. Jack is visible\n\n" ANSI_COLOR_RESET);
        printf("\t\t\t\t\t\t\t\a");
        printf(HMAG "Innocent characters is illustrated by lower alphabet\n\n" ANSI_COLOR_RESET);
    }
    else{
        CreateMap(stringAreaContent);
        printf("\n\n\t\t\t\t\t\t\t\a");
        printf(HMAG "Mr. Jack is invisible\n\n" ANSI_COLOR_RESET);
    }

}

void mr_jack_escape(struct Node *list_characters, int mr_jack, int **type_area){
    int is_escape = 0;
    struct Node *MRJACK = get_character(list_characters, mr_jack);
    int row = MRJACK->character.row;
    int col = MRJACK->character.col;

    int type = what_is_type_of_area(type_area, row, col);
    if(type == open_exit)
        is_escape = 1;

    if(is_escape){
        system("cls");

        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t\t\t\t\t\a");
        printf(YELHB ANSI_COLOR_BLUE "Mr.Jack Win The Game\n\n" ANSI_COLOR_RESET);
        printf("\t\t\t\t\t\t\t\t\a");
        printf(YELHB ANSI_COLOR_BLUE "Inspector Amallan Bakht Dad\n\n" ANSI_COLOR_RESET);
        exit(0);
    }
}

void check_inspector_win_lose(int i, int which_set, int mr_jack){

    int choice;

    //first and last turn
    if(i == 0 || i == 3){
        if(which_set % 2 == 0){
            printf("\n\n \t\t\t\t\t\t\a");
            printf(BHMAG "Do you take Mr.Jack?\n\n\n" ANSI_COLOR_RESET);
            printf("\n\n \t\t\t\t\t\t\a");
            printf(BHMAG "\t1)Yes 2)No\n\n\n" ANSI_COLOR_RESET);
            printf(ANSI_COLOR_YELLOW "\t\t\t\t\t\t\t\t\t\a?:" ANSI_COLOR_RESET);
            scanf("%d", &choice);
            if(choice == 1){
                printf("\n\n \t\t\t\t\t\t\a");
                printf(BHMAG "Enter name of Mr.Jack\n\n\n" ANSI_COLOR_RESET);
                char name[4];
                printf(ANSI_COLOR_YELLOW "\t\t\t\t\t\t\t\t\a?:" ANSI_COLOR_RESET);
                scanf("\n%[^\n]", name);
                if(take_name_get_index(name) == mr_jack){
                    system("cls");
                    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                    printf("\n\n \t\t\t\t\t\t\t\a");
                    printf(BHMAG "Inspector Win The game\n\n\n" ANSI_COLOR_RESET);
                    exit(0);
                }
                system("cls");
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                printf("\t\t\t\t\t\t\t\t\a");
                printf(BHMAG "Mr.Jack Win The Game\n\n" ANSI_COLOR_RESET);
                printf("\t\t\t\t\t\t\t\t\a");
                printf(BHMAG "Inspector Amallan Bakht Dad\n\n" ANSI_COLOR_RESET);
                exit(0);
                }
            }
        }

    //middle turns
    else{
        if(which_set % 2 != 0){
            printf("\n\n \t\t\t\t\t\t\a");
            printf(CYNHB BHMAG"Do you take Mr.Jack?\n\n\n" ANSI_COLOR_RESET);
            printf("\n\n \t\t\t\t\t\t\t\a");
            printf(CYNHB BHMAG"1)Yes 2)No\n\n\n" ANSI_COLOR_RESET);
            printf(ANSI_COLOR_YELLOW "\t\t\t\t\t\t\t\t\a?:" ANSI_COLOR_RESET);
            scanf("%d", &choice);
            if(choice == 1){
                printf("\n\n \t\t\t\t\t\t\a");
                printf(CYNHB BHMAG"Enter name of Mr.Jack\n\n\n" ANSI_COLOR_RESET);
                char name[4];
                printf(ANSI_COLOR_YELLOW "\t\t\t\t\t\t\t\t\a?:" ANSI_COLOR_RESET);
                scanf("\n%[^\n]", name);
                if(take_name_get_index(name) == mr_jack){
                    system("cls");
                    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                    printf("\n\n \t\t\t\t\t\t\t\a");
                    printf(CYNHB BHMAG"Inspector Win The game\n\n\n" ANSI_COLOR_RESET);
                    exit(0);
                }
                system("cls");
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                printf("\t\t\t\t\t\t\t\t\a");
                printf(YELHB ANSI_COLOR_BLUE "Mr.Jack Win The Game\n\n" ANSI_COLOR_RESET);
                printf("\t\t\t\t\t\t\t\t\a");
                printf(YELHB ANSI_COLOR_BLUE "Inspector Amallan Bakht Dad\n\n" ANSI_COLOR_RESET);
                exit(0);
            }
        }
    }

}