#include "GameFunctions.h"


int main() {
    Menu();

    int choice;
    scanf("%d", &choice);

    char stringAreaContent[117][6][15];
    int flag = 1;
    while (flag) {

        switch (choice) {

            case 1: {
                for (int i = 0; i < 117; i++) {
                    for (int j = 0; j < 6; j++) {
                        strcpy(stringAreaContent[i][j], "");
                    }
                }
                //opening initial map
                FILE *fp_initial_map = fopen("InitialMap.txt", "r");
                int **type_area = array_type_area_initially(fp_initial_map);
                struct Area **Whitechapel = InitialMap(type_area);

                FillingAreaContent(Whitechapel, stringAreaContent);



                //saving game until now
                FILE *fp_saved_map = fopen("SavedMap.bin", "wb");
                saved_map_file(fp_saved_map, type_area);

//--------------------------------------------------------------------------------------------------------------------->
                //initial set
                int which_set = 0;
                struct cards *game_cards = ShuffleCards();
                struct Node *list_characters = list_of_all_characters();

                //first innocent cards
                int *used_innocent_cards = (int *)malloc(8 * sizeof(int));
                for(int i = 0; i < 8; i++){
                    used_innocent_cards[i] = -1;
                }


                //Initially, I take random card for Mr.Jack
                int mr_jack = get_innocent_card(used_innocent_cards);

                //update used characters for innocent
                used_innocent_cards[0] = mr_jack;


                //at first no one was used
                int *used_character_index = (int *)malloc(4 * sizeof(int));
                for(int i = 0; i < 4; i++){
                    used_character_index[i] = -1;
                }

                playing_actions(which_set, game_cards, Whitechapel, used_character_index, list_characters, stringAreaContent, type_area, used_innocent_cards, mr_jack);
                check_visibility(type_area, list_characters, stringAreaContent, Whitechapel, mr_jack);
                //check escape
                mr_jack_escape(list_characters, mr_jack, type_area);


                which_set++;
                //close light number 1
                type_area[6][1] = close_light;

                //print_set_cards(which_set, game_cards, used_character_index);
                playing_actions(which_set, game_cards, Whitechapel, used_character_index, list_characters, stringAreaContent, type_area, used_innocent_cards, mr_jack);
                check_visibility(type_area, list_characters, stringAreaContent, Whitechapel, mr_jack);

                //check escape
                mr_jack_escape(list_characters, mr_jack, type_area);

//--------------------------------------------------------------------------------------------------------------------->
                //shuffling cards
                game_cards = ShuffleCards();
                for(int i = 0; i < 4; i++){
                    used_character_index[i] = -1;
                }
                //close light number 2
                type_area[1][2] = close_light;

                which_set++;
                //print_set_cards(which_set, game_cards, used_character_index);
                playing_actions(which_set, game_cards, Whitechapel, used_character_index, list_characters, stringAreaContent, type_area, used_innocent_cards, mr_jack);
                check_visibility(type_area, list_characters, stringAreaContent, Whitechapel, mr_jack);

                //check escape
                mr_jack_escape(list_characters, mr_jack, type_area);



                which_set++;
                //close light number 4
                type_area[5][5] = close_light;

                //print_set_cards(which_set, game_cards, used_character_index);
                playing_actions(which_set, game_cards, Whitechapel, used_character_index, list_characters, stringAreaContent, type_area, used_innocent_cards, mr_jack);
                check_visibility(type_area, list_characters, stringAreaContent, Whitechapel, mr_jack);

                //check escape
                mr_jack_escape(list_characters, mr_jack, type_area);

//--------------------------------------------------------------------------------------------------------------------->
                //shuffling cards
                game_cards = ShuffleCards();
                for(int i = 0; i < 4; i++){
                    used_character_index[i] = -1;
                }
                //close light number 5
                type_area[3][7] = close_light;


                which_set++;
                //print_set_cards(which_set, game_cards, used_character_index);

                playing_actions(which_set, game_cards, Whitechapel, used_character_index, list_characters, stringAreaContent, type_area, used_innocent_cards, mr_jack);
                check_visibility(type_area, list_characters, stringAreaContent, Whitechapel, mr_jack);

                //check escape
                mr_jack_escape(list_characters, mr_jack, type_area);



                which_set++;
                //print_set_cards(which_set, game_cards, used_character_index);
                //close light number 7
                type_area[6][10] = close_light;

                playing_actions(which_set, game_cards, Whitechapel, used_character_index, list_characters, stringAreaContent, type_area, used_innocent_cards, mr_jack);
                check_visibility(type_area, list_characters, stringAreaContent, Whitechapel, mr_jack);

                //check escape
                mr_jack_escape(list_characters, mr_jack, type_area);


//--------------------------------------------------------------------------------------------------------------------->
                //shuffling cards
                game_cards = ShuffleCards();
                for(int i = 0; i < 4; i++){
                    used_character_index[i] = -1;
                }
                //close light number 8
                type_area[2][11] = close_light;

                which_set++;
                //print_set_cards(which_set, game_cards, used_character_index);
                playing_actions(which_set, game_cards, Whitechapel, used_character_index, list_characters, stringAreaContent, type_area, used_innocent_cards, mr_jack);
                check_visibility(type_area, list_characters, stringAreaContent, Whitechapel, mr_jack);

                //check escape
                mr_jack_escape(list_characters, mr_jack, type_area);


                which_set++;
                //print_set_cards(which_set, game_cards, used_character_index);
                playing_actions(which_set, game_cards, Whitechapel, used_character_index, list_characters, stringAreaContent, type_area, used_innocent_cards, mr_jack);
                check_visibility(type_area, list_characters, stringAreaContent, Whitechapel, mr_jack);

                system("cls");
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                printf("\t\t\t\t\t\t\t\t\a");
                printf(YELHB ANSI_COLOR_BLUE "Mr.Jack Win The Game\n\n" ANSI_COLOR_RESET);
                printf("\t\t\t\t\t\t\t\t\a");
                printf(YELHB ANSI_COLOR_BLUE "Inspector Amallan Bakht Dad\n\n" ANSI_COLOR_RESET);


                flag = 0;
                break;
            }


            case 2: {
                for (int i = 0; i < 117; i++) {
                    for (int j = 0; j < 6; j++) {
                        strcpy(stringAreaContent[i][j], "");
                    }
                }

                //opening saved map
                FILE *fp_saved_map = fopen("SavedMap.bin", "rb");
                int **type_area = load_array_type_area(fp_saved_map);
                struct Area **Whitechapel = InitialMap(type_area);
                FillingAreaContent(Whitechapel, stringAreaContent);
                CreateMap(stringAreaContent);

                flag = 0;
                break;
            }

            case 3: {
                system("cls");
                printf("\t\t\t\t\t\t\t\a");
                puts(ANSI_COLOR_YELLOW "Are you sure you want exit the game? " ANSI_COLOR_RESET);
                printf("\t\t\t\t\t\t\t");
                puts(ANSI_COLOR_RED "1)Yes" ANSI_COLOR_RESET);
                printf("\t\t\t\t\t\t\t");
                puts(ANSI_COLOR_BLUE "2)No" ANSI_COLOR_RESET);


                int quit_game;
                printf(ANSI_COLOR_YELLOW "\t\t\t\t\t\t\t\t\a?:" ANSI_COLOR_RESET);
                scanf("%d", &quit_game);

                switch (quit_game) {
                    case 1:
                        system("cls");
                        printf(BLUHB"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                        printf("\t\t\t\t\t\t\t\t");
                        puts(ANSI_COLOR_YELLOW "----GOOD BYE :))----");
                        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" reset);
                        return 0;
                        break;

                    case 2:
                        Menu();
                        scanf("%d", &choice);
                        break;
                    default:
                        system("cls");
                        printf("\t\t\t\t\t\t\t");
                        puts(ANSI_COLOR_YELLOW "Wrong choice was entered!\nso I assume you want quit game." ANSI_COLOR_RESET);
                        system("cls");
                        printf("\t\t\t\t\t\t");
                        puts(ANSI_COLOR_YELLOW "----GOOD BYE :))----" ANSI_COLOR_RESET);
                        return 0;
                }

                break;
            }

            default:
                Menu();
                scanf("%d", &choice);
        }
    }

    return 0;
}