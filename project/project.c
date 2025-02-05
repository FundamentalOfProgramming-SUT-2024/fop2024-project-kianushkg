#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ncurses.h>
#include<time.h>
#include<locale.h>

typedef struct{
    char* email;
    char* username;
    char* password;
    int rank;
    int score;
    int gold;
    int exprience;
} player_info;

typedef struct{
    int x;
    int y;
    int height;
    int width;
    int state;
    char** map;
    int** unicode_map;
    int type;
} room_info;

typedef struct{
    int health;
    int gold;
    int score;
    int floor;
    int dagger;
    int wand;
    int arrow;
    int sword;
    int weapon;
    int hunger;
    int food;
    int food1;
    int food2;
    int food3;
    int* spell;
    int* spell_state;
    char** explored_map;
    int* enemy_health;
    int hunger_distance;
    int regen_distance;
    int hunger_health_distance;
    int exprience;
    int x;
    int y;
} game;


void get_email();
char* get_username1();
void get_username2();
char* get_password1();
void get_password2();
void email_check();
void user_exist_check();
void user_pass_check1();
void user_pass_check2();
void password_format_check();
void sign_in();
void login_options();
void login_menu_print();
void login1();
void login2();
void login3();
void profile_menu();
void pregame_menu();
void pregame_menu_print();
void settings();
void setting_menu1_print();
void setting_menu2_print();
void scoreboard();
int score_check();
int rank_check();
room_info* create_map_floor1();
room_info* create_map_floor2();
char** create_map();
void draw_room();
void door_placement();
void doorway_placement();
int gameplay();
int movement();
int move_check();
void move_initialize();
void in_room_check();
void doorway_check();
void m_button_function();
void new_floor_message();
void new_room_message();
void pick_gold_message();
void delete_message();
void game_status_print();
void trap_search();
void trap_found_message();
void stepontrap_message();
void pick_diamond_message();
void secret_room();
void pick_dagger_message();
void pick_wand_message();
void pick_arrow_message();
void pick_sword_message();
void sword_have_message();
void i_button_function();
void select_weapon();
void q_button_function();
int pick_food();
void e_button_function();
void consume_food();
void consume_selected_food();
void health_spell();
void health_regen();
void hunger_health();
void hunger();
void pick_spell_message();
void select_spell();
void save_game();
void new_game();
void load_game();
void enemy_check();
void enemy_action();
void damage_spell();
void room_color_on();
void room_color_off();
int no_health_death();
int win_game();




int main(){
    setlocale(LC_ALL, "");
    srand(time(NULL));
    initscr();
    start_color();
    init_color(99, 275, 208, 694);
    // gold like :
    init_color(98, 784, 298, 20);
    // brown like :
    init_color(97, 600, 486, 439);
    // purpul like :
    init_color(96, 553, 43, 256);
    // light blue :
    init_color(95, 216, 686, 882);
    // light blue 2 :
    init_color(89, 376, 545, 757);
    // light red :
    init_color(94, 973, 478, 325);
    // light green :
    init_color(93, 533, 761, 451);
    // light green 2
    init_color(92, 694, 839, 565);
    // purpul like 2
    init_color(91, 391, 51, 373);
    // beige
    init_color(90, 831, 741, 675);

    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_YELLOW, COLOR_BLACK);
    init_pair(8, 99, COLOR_BLACK);
    // weapon pick up
    init_pair(9, 98, COLOR_BLACK);
    // sword already have
    init_pair(10, 97, COLOR_BLACK);
    // status
    init_pair(11, 96, COLOR_BLACK);
    // select weapon
    init_pair(12, 95, COLOR_BLACK);
    // select weapon fail
    init_pair(13, 94, COLOR_BLACK);
    // gaining health
    init_pair(14, 93, COLOR_BLACK);
    // normal room
    init_pair(15, 92, COLOR_BLACK);
    // normal room 2
    init_pair(18, 89, COLOR_BLACK);
    // spell room
    init_pair(16, 91, COLOR_BLACK);
    // menu 
    init_pair(17, 90, COLOR_BLACK);

    int screen_height, screen_width;
    int players_count=4;
    getmaxyx(stdscr, screen_height, screen_width);
    
    player_info* players_info = (player_info*)malloc(110 * sizeof(player_info));
    for(int i=1; i<=110; i++){
        players_info[i].email = (char*)malloc(50 * sizeof(char));
        players_info[i].username = (char*)malloc(50 * sizeof(char));
        players_info[i].password = (char*)malloc(50 * sizeof(char));
    }

    FILE* info = fopen("user_pass.txt", "r");
    char line[500];
    for(int i=1; i<=players_count; i++){
        fgets(line, sizeof(line), info);
        sscanf(line, "%s", players_info[i].email);
        fgets(line, sizeof(line), info);
        sscanf(line, "%s", players_info[i].username);
        fgets(line, sizeof(line), info);
        sscanf(line, "%s", players_info[i].password);
        fgets(line, sizeof(line), info);
        sscanf(line, "%d %d %d", &players_info[i].score, &players_info[i].gold, &players_info[i].exprience);
    }

    login_options(screen_height, screen_width, players_info, &players_count);

    clear();
    refresh();
    
    pregame_menu(screen_height, screen_width, players_info, &players_count);

    clear();
    refresh();


    endwin();
    return 0;
}


void get_email(int screen_height, int screen_width, player_info* players_info, int* players_count){
    mvprintw(screen_height/2 - 1, screen_width/2 - 20, "please enter an email : ");
    refresh();
    getnstr(players_info[(*players_count)].email, 49);
    email_check(screen_height, screen_width, players_info, players_count);
}


char* get_username1(int screen_height, int screen_width, player_info* players_info, int* players_count){
    mvprintw(screen_height/2 - 1, screen_width/2 - 20, "please enter your username : ");
    refresh();
    char* user = (char*)malloc(50 * sizeof(char));
    getnstr(user, 49);
    return user;
}


void get_username2(int screen_height, int screen_width, player_info* players_info, int* players_count){
    mvprintw(screen_height/2, screen_width/2 - 20, "please enter a username : ");
    refresh();
    getnstr(players_info[(*players_count)].username, 49);
}


char* get_password1(int screen_height, int screen_width, player_info* players_info, int* players_count){
    mvprintw(screen_height/2 + 1, screen_width/2 - 20, "please enter your password : ");
    refresh();
    char* pass = (char*)malloc(50 * sizeof(char));
    getnstr(pass, 49);
    return pass;
}


void get_password2(int screen_height, int screen_width, player_info* players_info, int* players_count){
    mvprintw(screen_height/2 + 1, screen_width/2 - 20, "please enter a password : ");
    attron(COLOR_PAIR(1));
    mvprintw(screen_height / 2 - 4, screen_width / 2 - 47, "password must be atleast 7 characters and contain lowercase and uppercase letters and a number");
    refresh();
    attroff(COLOR_PAIR(1));
    move(screen_height / 2 + 1, screen_width / 2 + 6);
    getnstr(players_info[(*players_count)].password, 49);
    password_format_check(screen_height, screen_width, players_info, players_count);
}


void email_check(int screen_height, int screen_width, player_info* players_info, int* players_count){
    int check_counter=0;
    int atsign=0;
    int dot=0;
    int length = strlen(players_info[(*players_count)].email);
    for(int i=0; i < length; i++){
        if(players_info[(*players_count)].email[i] == '@'){
            atsign++;
            if( (players_info[(*players_count)].email[i + 1]  != '.') && (i != 0)){
            if((players_info[(*players_count)].email[i - 1] != '.'))
            check_counter++;
            }
        }

        if(players_info[(*players_count)].email[i] == '.'){
            dot++;
        }
    }

    if( (players_info[(*players_count)].email[length - 3] != '@') && (players_info[(*players_count)].email[length - 3] != '.')
        && (players_info[(*players_count)].email[length - 2] != '@') && (players_info[(*players_count)].email[length - 2] != '.')
        && (players_info[(*players_count)].email[length - 1] != '@') && (players_info[(*players_count)].email[length - 1] != '.') ){
            check_counter++;
        }

        if( (atsign == 1) && (dot >= 1) && (check_counter == 2)){
            mvprintw(screen_height / 2 - 3, screen_width / 2 - 20, "                       ");
            return;
        }

        else{
            attron(COLOR_PAIR(1));
            mvprintw(screen_height / 2 - 3, screen_width / 2 - 20, "invalid email format");
            refresh();
            attroff(COLOR_PAIR(1));
            move(screen_height / 2 - 1, screen_width / 2 + 4);
            attron(COLOR_PAIR(2));
            for(int i=1; i<=length; i++)
            printw(" ");
            refresh();
            attroff(COLOR_PAIR(2));
            get_email(screen_height, screen_width, players_info, players_count);
        }
    
}


void user_exist_check(int screen_height, int screen_width, player_info* players_info, int* players_count){
    int state = 0;
    int length = strlen(players_info[(*players_count)].username);

    for(int i=1; i<(*players_count); i++){
        if(strcmp(players_info[(*players_count)].username, players_info[i].username) == 0)
        state = 1;
    }

    if(state){
    attron(COLOR_PAIR(1));
        mvprintw(screen_height / 2 - 3, screen_width / 2 - 20, "username already exists");
        refresh();
        attroff(COLOR_PAIR(1));
        move(screen_height / 2, screen_width / 2 + 6);
        attron(COLOR_PAIR(2));
        for(int i=1; i<=length; i++)
        printw(" ");
        refresh();
        attroff(COLOR_PAIR(2));
        get_username2(screen_height, screen_width, players_info, players_count);
        user_exist_check(screen_height, screen_width, players_info, players_count);
    }

    else{
        mvprintw(screen_height / 2 - 3, screen_width / 2 - 20, "                           ");
        refresh();
        /*FILE *user_write = fopen("user_pass.txt", "a");
        fprintf(user_write,"%s ", players_info[players_count].username);
        fclose(user_write);*/
        return;
    }
}


void user_pass_check1(int screen_height, int screen_width, player_info* players_info, int* players_count, char** user){
    int state = 0;
    int length = strlen(*user);
    char line[100], temp_user[50], temp_pass[50];
    //FILE* user_check = fopen("user_pass.txt", "r");
    for(int i=1; i<=(*players_count); i++){
        //fgets(line, sizeof(line), user_check);
        //sscanf(line, "%s %s", temp_user, temp_pass);
        if(strcmp(*user, players_info[i].username) == 0)
        state = 1;
    }
    
    if(!state){
        attron(COLOR_PAIR(1));
        mvprintw(screen_height / 2 - 3, screen_width / 2 - 10, "username not found");
        refresh();
        attroff(COLOR_PAIR(1));
        move(screen_height/2 - 1, screen_width/2 + 9);
        for(int i=1; i<=length; i++)
        printw(" ");
        refresh();
        *user = get_username1(screen_height, screen_width, players_info, players_count);
        user_pass_check1(screen_height, screen_width, players_info, players_count, user);
    }

    else{
        mvprintw(screen_height / 2 - 3, screen_width / 2 - 10, "                  ");
        refresh();
    }
}


void user_pass_check2(int screen_height, int screen_width, player_info* players_info, int* players_count, char* user, char* pass){
    int state = 0;
    int length = strlen(pass);
    
    for(int i=1; i<=(*players_count); i++){
        if((strcmp(user, players_info[i].username) == 0) && (strcmp(pass, players_info[i].password) == 0))
        state = 1;
    }

    if(state){
        mvprintw(screen_height / 2 - 3, screen_width / 2 - 10, "                 ");
        refresh();
    }

    else{
        attron(COLOR_PAIR(1));
        mvprintw(screen_height / 2 - 3, screen_width / 2 - 10, "password is wrong");
        refresh();
        attroff(COLOR_PAIR(1));
        move(screen_height/2 + 1, screen_width/2 + 9);
        for(int i=1; i<=length; i++)
        printw(" ");
        refresh();
        pass = get_password1(screen_height, screen_width, players_info, players_count);
        user_pass_check2(screen_height, screen_width, players_info, players_count, user, pass);
    }
}


void password_format_check(int screen_height, int screen_width, player_info* players_info, int* players_count){
    int length = strlen(players_info[(*players_count)].password);
    int check_counter=0, uppercase=0, lowercase=0, number=0;

    for(int i=0; i<length; i++){
        if((players_info[(*players_count)].password[i] >= 65) && (players_info[(*players_count)].password[i] <= 90))
        uppercase++;

        if((players_info[(*players_count)].password[i] >= 97) && (players_info[(*players_count)].password[i] <= 122))
        lowercase++;

        if((players_info[(*players_count)].password[i] >= 48) && (players_info[(*players_count)].password[i] <= 57))
        number++;
    }

    if(uppercase && lowercase && number && (length >= 7)){
        mvprintw(screen_height / 2 - 3, screen_width / 2 - 18, "                                     ");
        mvprintw(screen_height / 2 - 4, screen_width / 2 - 50, "                                                                                                   ");
        refresh();
        /*FILE *pass_write = fopen("user_pass.txt", "a");
        fprintf(pass_write,"%s ", players_info[players_count].password);
        fclose(pass_write);*/
        return;
    }

    else{
        attron(COLOR_PAIR(1));
        mvprintw(screen_height / 2 - 3, screen_width / 2 - 21, "password does not satisfy the rules");
        refresh();
        attroff(COLOR_PAIR(1));
        move(screen_height / 2 + 1, screen_width / 2 + 6);
        attron(COLOR_PAIR(2));
        for(int i=1; i<=length; i++)
        printw(" ");
        refresh();
        attroff(COLOR_PAIR(2));
        get_password2(screen_height, screen_width, players_info, players_count);
    }
}


void login_options(int screen_height, int screen_width, player_info* players_info, int* players_count){
    noecho();
    cbreak();
    int chosen_option=1, final_choice=0;
    char** options = (char**)malloc(4 * sizeof(char*));
    options[1] = "sign in to your account";
    options[2] = "create a new account";
    options[3] = "enter as a guest";

    WINDOW *menu = newwin(7, 30, screen_height/2 - 3, screen_width/2 - 15);
    keypad(menu, TRUE);
    mvwprintw(menu, 2, 3, "%s", options[1]);
    mvwprintw(menu, 3, 3, "%s", options[2]);
    mvwprintw(menu, 4, 3, "%s", options[3]);
    wrefresh(menu);
    login_menu_print(screen_height, screen_width, menu, chosen_option, options);

    while(1){
        int c = wgetch(menu);
        if(c == KEY_UP){
            if(chosen_option == 1)
            chosen_option = 1;
            else if(chosen_option == 2){
                mvwprintw(menu, 3, 3, "%s", options[2]);
                wrefresh(menu);
                chosen_option = 1;
            }
            else if(chosen_option == 3){
               mvwprintw(menu, 4, 3, "%s", options[3]);
               wrefresh(menu);
               chosen_option = 2;
               }
        }

        else if(c == KEY_DOWN){
            if(chosen_option == 1){
                mvwprintw(menu, 2, 3, "%s", options[1]);
                wrefresh(menu);
                chosen_option = 2;
            }
            else if(chosen_option == 2){
                mvwprintw(menu, 3, 3, "%s", options[2]);
                wrefresh(menu); 
                chosen_option = 3;}
            else if(chosen_option == 3)
            chosen_option = 3;

        }

        else if(c == 10){
            final_choice = chosen_option;
        }

        login_menu_print(screen_height, screen_width, menu, chosen_option, options);
        if(final_choice){
            echo();
            nocbreak();
            break;
        }
    }

    switch(final_choice){
        case 1:
        login1(screen_height, screen_width, players_info, players_count);
        break;

        case 2: 
        login2(screen_height, screen_width, players_info, players_count);
        break;

        case 3:
        login3(screen_height, screen_width, players_info);
        break;
    }
}


void login_menu_print(int screen_height, int screen_width, WINDOW* menu, int chosen_option, char** options){
    box(menu, 0, 0);
    if(chosen_option == 1){
        wattron(menu, A_REVERSE);
        mvwprintw(menu, 2, 3, "%s", options[1]);
        wrefresh(menu);
        wattroff(menu, A_REVERSE);
    }

    else if(chosen_option == 2){
        wattron(menu, A_REVERSE);
        mvwprintw(menu, 3, 3, "%s", options[2]);
        wrefresh(menu);
        wattroff(menu, A_REVERSE);
    }

    else if(chosen_option == 3){
        wattron(menu, A_REVERSE);
        mvwprintw(menu, 4, 3, "%s", options[3]);
        wrefresh(menu);
        wattroff(menu, A_REVERSE);
    }

    wrefresh(menu);
}


void login1(int screen_height, int screen_width, player_info* players_info, int* players_count){
    char* user = (char*)malloc(50 * sizeof(char));
    char* pass = (char*)malloc(50 * sizeof(char));
    char* email = (char*)malloc(100 * sizeof(char));
    char* temp_user = (char*)malloc(50 * sizeof(char));
    char* temp_pass = (char*)malloc(50 * sizeof(char));
    char* temp_email = (char*)malloc(100 * sizeof(char));
    user = get_username1(screen_height, screen_width, players_info, players_count);
    user_pass_check1(screen_height, screen_width, players_info, players_count, &user);
    pass = get_password1(screen_height, screen_width, players_info, players_count);
    user_pass_check2(screen_height, screen_width, players_info, players_count, user, pass);

    /*FILE* user_pass = fopen("user_pass", "r");
    char* line = (char*)malloc(150 * sizeof(char));
    for(int i=1; i<=players_count; i++){
    fgets(line, sizeof(line), user_pass);
    sscanf(line, "%s %s %s", temp_email, temp_user, temp_pass);
    if(strcmp(user, temp_user) == 0){
        email = temp_email;
    }
    }
    fclose(user_pass);*/

    for(int i=1; i<=(*players_count); i++){
        if(strcmp(user, players_info[i].username) == 0){
            players_info[99].email = players_info[i].email;
            players_info[99].score = players_info[i].score;
            players_info[99].gold = players_info[i].gold;
            players_info[99].exprience = players_info[i].exprience;
        }
    }
    players_info[99].username = user;
    players_info[99].password = pass;
}


void login2(int screen_height, int screen_width, player_info* players_info, int* players_count){
    (*players_count)++;

    get_email(screen_height, screen_width, players_info, players_count);
    get_username2(screen_height, screen_width, players_info, players_count);
    user_exist_check(screen_height, screen_width, players_info, players_count);
    get_password2(screen_height, screen_width, players_info, players_count);

    FILE* user_pass = fopen("user_pass.txt", "a");
    fprintf(user_pass, "%s \n%s \n%s\n", players_info[*players_count].email, players_info[*players_count].username, players_info[*players_count].password);
    fprintf(user_pass, "%d %d %d\n", 0, 0, 0);
    fclose(user_pass);
    players_info[99].email = players_info[*players_count].email;
    players_info[99].username = players_info[*players_count].username;
    players_info[99].password = players_info[*players_count].password;
    players_info[99].score = 0;
    players_info[99].gold = 0;
    players_info[99].exprience = 0;
}


void login3(int screen_height, int screen_width, player_info* players_info){
    players_info[99].username = "guest";
}


void profile_menu(int screen_height, int screen_width, player_info* players_info, int* players_count){
    clear();
    refresh();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    cbreak();
    attron(A_BOLD | COLOR_PAIR(15));
    mvprintw(3, screen_width / 2 - 10, "HELLO %s", players_info[99].username);
    attroff(A_BOLD | COLOR_PAIR(15));

    attron(A_BOLD | COLOR_PAIR(17));
    mvprintw(6, screen_width / 2 - 20, "your username  :  %s", players_info[99].username);
    mvprintw(7, screen_width / 2 - 20, "your email  :  %s", players_info[99].email);
    mvprintw(9, screen_width /2 - 20, "press f to change your password");
    attroff(A_BOLD | COLOR_PAIR(17));

    attron(A_BOLD | COLOR_PAIR(12));
    mvprintw(11, screen_width / 2 - 20, "press space to go back");
    attroff(A_BOLD | COLOR_PAIR(12));
    refresh();

    int c = getch();
    //c = 'f';
    switch(c){
        case 'f' : 
        echo();
        clear();
        refresh();
        int a = 99;
        get_password2(screen_height, screen_width, players_info, &a);
        noecho();
        
        FILE* user_pass = fopen("user_pass.txt", "w");
        for(int i=1; i<=(*players_count); i++){
            if(strcmp(players_info[i].username, players_info[99].username) != 0){
                fprintf(user_pass, "%s \n%s \n%s\n", players_info[i].email, players_info[i].username, players_info[i].password);
                fprintf(user_pass, "%d %d %d\n", players_info[i].score, players_info[i].gold, players_info[i].exprience);
            }
        }
        fprintf(user_pass, "%s \n%s \n%s\n", players_info[99].email, players_info[99].username, players_info[99].password);
        fprintf(user_pass, "%d %d %d\n", players_info[99].score, players_info[99].gold, players_info[99].exprience);
        fclose(user_pass);

        profile_menu(screen_height, screen_width, players_info, players_count);
        break;

        case ' ' :
        clear();
        refresh();
        nocbreak();
        echo();
        curs_set(1);
        pregame_menu(screen_height, screen_width, players_info, players_count);
        break;
    }
}


void pregame_menu(int screen_height, int screen_width, player_info* players_info, int* players_count){
    clear();
    refresh();
    noecho();
    cbreak();
    curs_set(0);
    int chosen_option=1, final_choice=0;
    char** options = (char**)malloc(6 * sizeof(char*));
    options[1] = "new game";
    options[2] = "countinue";
    options[3] = "settings";
    options[4] = "scoreboard";
    options[5] = "profile";

    WINDOW *menu = newwin(9, 18, screen_height/2 - 4, screen_width/2 - 9);
    keypad(menu, TRUE);
    mvwprintw(menu, 2, 3, "%s", options[1]);
    mvwprintw(menu, 3, 3, "%s", options[2]);
    mvwprintw(menu, 4, 3, "%s", options[3]);
    mvwprintw(menu, 5, 3, "%s", options[4]);
    mvwprintw(menu, 6, 3, "%s", options[5]);
    wrefresh(menu);
    pregame_menu_print(screen_height, screen_width, menu, chosen_option, options);

    while(1){
        int c = wgetch(menu);
        switch (c) {
            case KEY_UP:
                if (chosen_option == 1)
                    chosen_option = 5;
                else
                    chosen_option--;
                break;
            case KEY_DOWN:
                if (chosen_option == 5)
                    chosen_option = 1;
                else 
                    chosen_option++;
                break;
            case 10:
                final_choice = chosen_option;
                break;
        }
        pregame_menu_print(screen_height, screen_width, menu, chosen_option, options);
    if(final_choice){
        echo();
        nocbreak();
        curs_set(1);
        break;
    }
    }

    switch(final_choice){
        case 1:
        new_game(screen_height, screen_width, players_info, players_count);
        break;

        case 2:
        load_game(screen_height, screen_width);
        break;

        case 3:
        settings(screen_height, screen_width, players_info, players_count);
        break;

        case 4:
        scoreboard(screen_height, screen_width, players_info, players_count);
        break;

        case 5:
        profile_menu(screen_height, screen_width, players_info, players_count);
        break;
    }

}


void pregame_menu_print(int screen_height, int screen_width, WINDOW* menu, int chosen_option, char** options){
    int y = 2;
    box(menu, 0, 0);
    for (int i=1; i<=5; i++) {
        if (chosen_option == i) {
            wattron(menu, A_REVERSE);
            mvwprintw(menu, y, 3, "%s", options[i]);
            wattroff(menu, A_REVERSE);
        } else {
            mvwprintw(menu, y, 3, "%s", options[i]);
        }
        y++;
    }
    wrefresh(menu);
}


void settings(int screen_height, int screen_width, player_info* players_info, int* players_count){
    clear();
    refresh();
    noecho();
    cbreak();
    curs_set(0);
    int chosen_option1=1, final_choice1=0;
    int chosen_option2=1, final_choice2=0;
    char** options1 = (char**)malloc(4 * sizeof(char*));
    char** options2 = (char**)malloc(5 * sizeof(char*));
    options1[1] = "easy";
    options1[2] = "normal";
    options1[3] = "hard";
    options2[1] = "blue";
    options2[2] = "green";
    options2[3] = "magenta";
    options2[4] = "cyan";
    
    mvprintw(screen_height/2 - 6, screen_width/2 - 21, "game difficulty");
    mvprintw(screen_height/2 - 6, screen_width/2 + 21, "player color");
    refresh();
    WINDOW *menu1 = newwin(7, 13, screen_height/2 - 4, screen_width/2 - 20);
    WINDOW *menu2 = newwin(8, 14, screen_height/2 - 4, screen_width/2 + 20);
    keypad(menu1, TRUE);
    keypad(menu2, TRUE);
    mvwprintw(menu1, 2, 3, "%s", options1[1]);
    mvwprintw(menu1, 3, 3, "%s", options1[2]);
    mvwprintw(menu1, 4, 3, "%s", options1[3]);
    wattron(menu2, COLOR_PAIR(3));
    mvwprintw(menu2, 2, 3, "**%s", options2[1]);
    wattroff(menu2, COLOR_PAIR(3));
    wattron(menu2, COLOR_PAIR(4));
    mvwprintw(menu2, 3, 3, "**%s", options2[2]);
    wattroff(menu2, COLOR_PAIR(4));
    wattron(menu2, COLOR_PAIR(5));
    mvwprintw(menu2, 4, 3, "**%s", options2[3]);
    wattroff(menu2, COLOR_PAIR(5));
    wattron(menu2, COLOR_PAIR(6));
    mvwprintw(menu2, 5, 3, "**%s", options2[4]);
    wattroff(menu2, COLOR_PAIR(6));
    
    wrefresh(menu1);
    wrefresh(menu2);

    setting_menu1_print(screen_height, screen_width, menu1, chosen_option1, options1);
    setting_menu2_print(screen_height, screen_width, menu2, chosen_option2, options2);
    wattron(menu2, COLOR_PAIR(3));
    mvwprintw(menu2, 2, 3, "**%s", options2[1]);
    wrefresh(menu2);
    wattroff(menu2, COLOR_PAIR(3));
    

    while(1){
        int c = wgetch(menu1);
        switch (c) {
            case KEY_UP:
                if (chosen_option1 == 1)
                    chosen_option1 = 3;
                else
                    chosen_option1--;
                break;
            case KEY_DOWN:
                if (chosen_option1 == 3)
                    chosen_option1 = 1;
                else 
                    chosen_option1++;
                break;
            case 10:
                final_choice1 = chosen_option1;
                break;
        }
        setting_menu1_print(screen_height, screen_width, menu1, chosen_option1, options1);
        if(final_choice1)
        break;
    }

    setting_menu2_print(screen_height, screen_width, menu2, chosen_option2, options2);

    while(1){
        int c = wgetch(menu2);
        switch (c) {
            case KEY_UP:
                if (chosen_option2 == 1)
                    chosen_option2 = 4;
                else
                    chosen_option2--;
                break;
            case KEY_DOWN:
                if (chosen_option2 == 4)
                    chosen_option2 = 1;
                else 
                    chosen_option2++;
                break;
            case 10:
                final_choice2 = chosen_option2;
                break;
        }
        setting_menu2_print(screen_height, screen_width, menu2, chosen_option2, options2);
        if(final_choice2){
        echo();
        nocbreak();
        curs_set(1);
        break;
        }
    }
    clear();
    refresh();
    pregame_menu(screen_height, screen_width, players_info, players_count);
}


void setting_menu1_print(int screen_height, int screen_width, WINDOW* menu1, int chosen_option1, char** options1){
    int y = 2;
    box(menu1, 0, 0);
    for (int i=1; i<=3; i++) {
        if (chosen_option1 == i) {
            wattron(menu1, A_REVERSE);
            mvwprintw(menu1, y, 3, "%s", options1[i]);
            wattroff(menu1, A_REVERSE);
        } 
        else {
            mvwprintw(menu1, y, 3, "%s", options1[i]);
        }
        y++;
    }
    wrefresh(menu1);
}


void setting_menu2_print(int screen_height, int screen_width, WINDOW* menu2, int chosen_option2, char** options2){
    int y = 2;
    box(menu2, 0, 0);
    for (int i=1; i<=4; i++) {
        if (chosen_option2 == i) {
            wattron(menu2, A_REVERSE);
            mvwprintw(menu2, y, 5, "%s", options2[i]);
            wattroff(menu2, A_REVERSE);
        } 
        else {
            wattron(menu2, COLOR_PAIR(i+2));
            mvwprintw(menu2, y, 3, "**%s", options2[i]);
            wattroff(menu2, COLOR_PAIR(i+2));
        }
        y++;
    }
    wrefresh(menu2);
}


void scoreboard(int screen_height, int screen_width, player_info* players_info, int* players_count){
    clear();
    refresh();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    char* current_user = (char*)malloc(50 * sizeof(char));
    
    current_user = players_info[99].username;

    FILE* score = fopen("score.txt", "r");
    fscanf(score, "%d %d %d", &players_info[99].score, &players_info[99].gold, &players_info[99].exprience);
    fclose(score);

    for(int i=1; i<=(*players_count); i++){
        if(strcmp(players_info[i].username, players_info[99].username) == 0){
            players_info[i] = players_info[99];
        }
    }
     
    FILE* user_pass = fopen("user_pass.txt", "w");
    for(int i=1; i<=(*players_count); i++){
        fprintf(user_pass, "%s \n%s \n%s\n", players_info[i].email, players_info[i].username, players_info[i].password);
        fprintf(user_pass, "%d %d %d\n", players_info[i].score, players_info[i].gold, players_info[i].exprience);
    }
    fclose(user_pass);
     
    player_info* temp_players_info = (player_info*)malloc(110 * sizeof(player_info));
    for(int i=1; i<=110; i++){
        temp_players_info[i].email = (char*)malloc(50 * sizeof(char));
        temp_players_info[i].username = (char*)malloc(50 * sizeof(char));
        temp_players_info[i].password = (char*)malloc(50 * sizeof(char));
    }

    for(int i=0; i<(*players_count); i++){
        temp_players_info[i] = players_info[i+1];
    }
    
    for(int i=0; i<(*players_count); i++){
        temp_players_info[i].rank = i + 1;
    }

    qsort(temp_players_info, (*players_count), sizeof(player_info), score_check);

    for(int i=0; i<(*players_count); i++){
        temp_players_info[i].rank = i + 1;
    }

    qsort(temp_players_info, (*players_count), sizeof(player_info), rank_check);

    for(int i=1; i<=(*players_count); i++){
        for(int j=1; j<(*players_count); j++){
            if((players_info[j].score > players_info[j+1].score) && (players_info[j].rank > players_info[j+1].rank)){
                int temp = players_info[j].rank;
                players_info[j].rank = players_info[j+1].rank;
                players_info[j+1].rank = temp;
            }

            else if((players_info[j].score < players_info[j+1].score) && (players_info[j].rank < players_info[j+1].rank)){
                int temp = players_info[j].rank;
                players_info[j].rank = players_info[j+1].rank;
                players_info[j+1].rank = temp;
            } 
        }
    }

    WINDOW *board = newwin(16, 75, screen_height/2 - 8, screen_width/2 - 37);
    box(board, 0, 0);
    wattron(board, A_BOLD);
    mvwprintw(board, 2, 12, "rank");
    mvwprintw(board, 2, 20, "username");
    mvwprintw(board, 2, 42, "score");
    mvwprintw(board, 2, 50, "gold");
    mvwprintw(board, 2, 57, "experience");
    wattroff(board, A_BOLD);

    for(int i=0; i<(*players_count); i++){
        int h = temp_players_info[i].rank + 3;
        if(temp_players_info[i].rank == 1){
        wattron(board, A_BOLD | COLOR_PAIR(7));
        mvwprintw(board, 4, 3, "champion");}
        if(temp_players_info[i].rank == 2){
        wattron(board, A_BOLD | COLOR_PAIR(6));
        mvwprintw(board, 5, 3, "legend");}
        if(temp_players_info[i].rank == 3){
        wattron(board, A_BOLD | COLOR_PAIR(4));
        mvwprintw(board, 6, 3, "hero");}

        if(strcmp(current_user, temp_players_info[i].username) == 0)
        wattron(board, A_UNDERLINE | A_BOLD);

        mvwprintw(board, h, 13, "%d", temp_players_info[i].rank);
        mvwprintw(board, h, 20, "%s", temp_players_info[i].username);
        mvwprintw(board, h, 42, "%d", temp_players_info[i].score);
        mvwprintw(board, h, 50, "%d", temp_players_info[i].gold);
        mvwprintw(board, h, 60, "%d", temp_players_info[i].exprience);

        if(strcmp(current_user, temp_players_info[i].username) == 0)
        wattroff(board, A_UNDERLINE | A_BOLD);

        if(temp_players_info[i].rank == 1)
        wattroff(board, A_BOLD | COLOR_PAIR(7));
        if(temp_players_info[i].rank == 2)
        wattroff(board, A_BOLD | COLOR_PAIR(6));
        if(temp_players_info[i].rank == 3)
        wattroff(board, A_BOLD | COLOR_PAIR(4));

        mvwaddstr(board, 4, 68, "🏆");
        mvwaddstr(board, 5, 68, "🥈");
        mvwaddstr(board, 6, 68, "🥉");
    }
    
    //

    /*for(int j=1; j<=players_count; j++){
    for(int i=1; i<=players_count; i++){
        int h = players_info[i].rank + 3;
        if(players_info[i].rank == 1){
        wattron(board, A_BOLD | COLOR_PAIR(7));
        mvwprintw(board, 4, 3, "champion");}
        if(players_info[i].rank == 2){
        wattron(board, A_BOLD | COLOR_PAIR(6));
        mvwprintw(board, 5, 3, "legend");}
        if(players_info[i].rank == 3){
        wattron(board, A_BOLD | COLOR_PAIR(4));
        mvwprintw(board, 6, 3, "hero");}
        
        if(strcmp(current_user, players_info[i].username) == 0)
        wattron(board, A_UNDERLINE | A_BOLD);

        if(players_info[i].rank == j){
        mvwprintw(board, h, 13, "%d", players_info[i].rank);
        mvwprintw(board, h, 20, "%s", players_info[i].username);
        mvwprintw(board, h, 42, "%d", players_info[i].score);
        mvwprintw(board, h, 50, "%d", players_info[i].gold);
        mvwprintw(board, h, 60, "%d", players_info[i].exprience);
        }

        if(strcmp(current_user, players_info[i].username) == 0)
        wattroff(board, A_UNDERLINE | A_BOLD);

        if(players_info[i].rank == 1)
        wattroff(board, A_BOLD | COLOR_PAIR(7));
        if(players_info[i].rank == 2)
        wattroff(board, A_BOLD | COLOR_PAIR(6));
        if(players_info[i].rank == 3)
        wattroff(board, A_BOLD | COLOR_PAIR(4));

        mvwaddstr(board, 4, 68, "🏆");
        mvwaddstr(board, 5, 68, "🥈");
        mvwaddstr(board, 6, 68, "🥉");
    }
    }*/

    wrefresh(board);
    
    getch();
    echo();
    curs_set(1);
    nocbreak();
    pregame_menu(screen_height, screen_width, players_info, players_count);
}


int score_check(const void *a, const void *b){
    return ((player_info *)b)->score - ((player_info *)a)->score;
}


int rank_check(const void *a, const void *b) {
    return ((player_info *)a)->rank - ((player_info *)b)->rank;
}


room_info* create_map_floor1(int screen_height, int screen_width){
    //clear();
    //refresh();
    
    room_info* rooms_info_floor1 = (room_info*)malloc(10 * sizeof(room_info));
    for(int i=1; i<=20; i++){
    rooms_info_floor1[i].state = 0;
    // 1 normal , 2 spell , 3 tresure
    rooms_info_floor1[i].type = 1;
    }
    rooms_info_floor1[2].state = 1;
    rooms_info_floor1[7].type = 2;

    char** map1 = create_map(screen_height, screen_width);
    int** unicode_map = (int**)malloc(screen_height * sizeof(int*));
    for(int i=1; i<=screen_height; i++){
        unicode_map[i] = (int*)malloc(screen_width * sizeof(int));
    }

    for(int i=1; i<=screen_height; i++){
        for(int j=1; j<=screen_width; j++){
            unicode_map[i][j] = 0;
        }
    }

    /*char** map1 = (char**)malloc(screen_height * sizeof(char*));
    for(int i=1; i<=screen_height; i++){
        map1[i] = (char*)malloc(screen_width * sizeof(char));
    }*/

    rooms_info_floor1[1].x = 38, rooms_info_floor1[1].y = 10, rooms_info_floor1[1].height = 5, rooms_info_floor1[1].width = 13;
    rooms_info_floor1[2].x = 65, rooms_info_floor1[2].y = 20, rooms_info_floor1[2].height = 6, rooms_info_floor1[2].width = 15;
    rooms_info_floor1[3].x = 95, rooms_info_floor1[3].y = 8, rooms_info_floor1[3].height = 5, rooms_info_floor1[3].width = 9;
    rooms_info_floor1[4].x = 115, rooms_info_floor1[4].y = 15, rooms_info_floor1[4].height = 5, rooms_info_floor1[4].width = 11;
    rooms_info_floor1[5].x = 45, rooms_info_floor1[5].y = 24, rooms_info_floor1[5].height = 4, rooms_info_floor1[5].width = 8;
    rooms_info_floor1[6].x = 98, rooms_info_floor1[6].y = 24, rooms_info_floor1[6].height = 8, rooms_info_floor1[6].width = 13;
    rooms_info_floor1[7].x = 10, rooms_info_floor1[7].y = 18, rooms_info_floor1[7].height = 7, rooms_info_floor1[7].width = 12;    

    for(int i=1; i<=7; i++){
        for(int j=rooms_info_floor1[i].y + 1; j<=rooms_info_floor1[i].y + rooms_info_floor1[i].height - 1; j++){
            for(int k=rooms_info_floor1[i].x + 1; k<=rooms_info_floor1[i].x + rooms_info_floor1[i].width - 1; k++){
                map1[j][k] = '.';
            }
        }
    }

    map1[9][98] = '<';
    map1[12][47] = 'O';
    map1[11][99] = 'O';
    map1[29][104] = 'O';
    map1[26][108] = 'O';
    map1[24][76] = 'O';
    
    // gold location
    unicode_map[14][40] = 1;
    unicode_map[18][124] = 1;
    unicode_map[25][102] = 1;
    unicode_map[31][108] = 1;
    
    // trap location
    unicode_map[13][41] = 99;
    unicode_map[18][123] = 99;
    unicode_map[27][104] = 99;
    unicode_map[30][108] = 99;
    unicode_map[26][49] = 99;
    unicode_map[26][51] = 99;
    unicode_map[22][72] = 99;

    // diamond location
    unicode_map[27][51] = 2;

    // dagger location
    unicode_map[21][77] = 3;

    // wand location
    unicode_map[11][47] = 4;

    // arrow location
    unicode_map[16][117] = 5;

    // food location
    unicode_map[10][101] = 73;
    unicode_map[23][76] = 71;
    unicode_map[25][67] = 72;

    //spell location 
    // 8 health , 9 speed , 10 damage
    unicode_map[20][12] = 10;
    unicode_map[21][19] = 8;
    unicode_map[23][11] = 9;
    unicode_map[23][17] = 10;

    // enemy location
    // 11 D , 12 F , 13 G , 14 S , 15 U
    map1[11][42] = 'F';
    map1[22][68] = 'D';
    map1[18][119] = 'G';

    
    door_placement(map1, 51, 13);
    door_placement(map1, 45, 15);
    door_placement(map1, 65, 22);
    door_placement(map1, 80, 24);
    door_placement(map1, 51, 13);
    door_placement(map1, 95, 11);
    door_placement(map1, 99, 13);
    door_placement(map1, 115, 17);
    door_placement(map1, 119, 20);
    door_placement(map1, 49, 24);
    door_placement(map1, 98, 28);
    door_placement(map1, 111, 29);
    door_placement(map1, 53, 26);
    door_placement(map1, 16, 25);

    doorway_placement(map1, 52, 13, 27, 2);
    doorway_placement(map1, 92, 28, 5, 2);
    doorway_placement(map1, 81, 24, 11, 2);
    doorway_placement(map1, 92, 24, 4, 1);
    doorway_placement(map1, 79, 11, 2, 1);
    doorway_placement(map1, 79, 11, 15, 2);
    doorway_placement(map1, 99, 14, 1, 1);
    doorway_placement(map1, 99, 15, 9, 2);
    doorway_placement(map1, 108, 15, 2, 1);
    doorway_placement(map1, 108, 17, 6, 2);
    doorway_placement(map1, 119, 21, 8, 1);
    doorway_placement(map1, 112, 29, 7, 2);
    doorway_placement(map1, 45, 16, 4, 1);
    doorway_placement(map1, 45, 20, 4, 2);
    doorway_placement(map1, 49, 20, 3, 1);
    doorway_placement(map1, 54, 26, 7, 2);
    doorway_placement(map1, 61, 22, 3, 2);
    doorway_placement(map1, 61, 22, 4, 1);

    rooms_info_floor1[1].map = map1;
    rooms_info_floor1[1].unicode_map = unicode_map;

    return rooms_info_floor1;
    
    //movement(map1, rooms_info_floor1, floor_number);
    //refresh();
    //getch();
}


room_info* create_map_floor2(int screen_height, int screen_width){
    room_info* rooms_info_floor2 = (room_info*)malloc(10 * sizeof(room_info));
    for(int i=1; i<=20; i++){
    rooms_info_floor2[i].state = 0;
    // 1 normal , 2 spell , 3 tresure
    rooms_info_floor2[i].type = 1;
    }
    rooms_info_floor2[4].type = 3;
    rooms_info_floor2[3].state = 1;

    char** map2 = create_map(screen_height, screen_width);
    int** unicode_map = (int**)malloc(screen_height * sizeof(int*));
    for(int i=1; i<=screen_height; i++){
        unicode_map[i] = (int*)malloc(screen_width * sizeof(int));
    }

    /*char** map2 = (char**)malloc(screen_height * sizeof(char*));
    for(int i=1; i<=screen_height; i++){
        map2[i] = (char*)malloc(screen_width * sizeof(char));
    }*/

    rooms_info_floor2[1].x = 25, rooms_info_floor2[1].y = 15, rooms_info_floor2[1].height = 4, rooms_info_floor2[1].width = 18;
    rooms_info_floor2[2].x = 68, rooms_info_floor2[2].y = 14, rooms_info_floor2[2].height = 6, rooms_info_floor2[2].width = 15;
    rooms_info_floor2[3].x = 95, rooms_info_floor2[3].y = 8, rooms_info_floor2[3].height = 5, rooms_info_floor2[3].width = 9;
    rooms_info_floor2[4].x = 120, rooms_info_floor2[4].y = 4, rooms_info_floor2[4].height = 7, rooms_info_floor2[4].width = 13;
    rooms_info_floor2[5].x = 51, rooms_info_floor2[5].y = 25, rooms_info_floor2[5].height = 6, rooms_info_floor2[5].width = 13;
    rooms_info_floor2[6].x = 100, rooms_info_floor2[6].y = 24, rooms_info_floor2[6].height = 5, rooms_info_floor2[6].width = 8;    

    for(int i=1; i<=6; i++){
        for(int j=rooms_info_floor2[i].y + 1; j<=rooms_info_floor2[i].y + rooms_info_floor2[i].height - 1; j++){
            for(int k=rooms_info_floor2[i].x + 1; k<=rooms_info_floor2[i].x + rooms_info_floor2[i].width - 1; k++){
                map2[j][k] = '.';
            }
        }
    }

    map2[9][98] = '<';
    map2[17][35] = 'O';
    map2[16][76] = 'O';
    map2[18][71] = 'O';
    map2[8][123] = 'O';
    map2[28][59] = 'O';
    
    // gold location
    unicode_map[18][30] = 1;
    unicode_map[18][76] = 1;
    unicode_map[30][56] = 1;
    unicode_map[9][130] = 1;
    unicode_map[28][104] = 1;
    unicode_map[5][129] = 1;
    unicode_map[7][122] = 1;
    unicode_map[6][125] = 1;
    unicode_map[10][123] = 1;

    // diamond location
    unicode_map[9][126] = 2;

    // wand location
    unicode_map[26][101] = 4;

    // sword location
    unicode_map[17][39] = 6;

    // wand location
    unicode_map[11][47] = 4;

    // food location
    unicode_map[27][54] = 72;
    unicode_map[29][61] = 71;
    unicode_map[12][96] = 72;
    unicode_map[15][70] = 73;

    //spell location 
    // 8 health , 9 speed , 10 damage
    unicode_map[19][70] = 8;
    unicode_map[16][27] = 10;

    // end portal location
    unicode_map[10][126] = 100;

    // s location
    map2[17][74] = 'S';

    // u location
    map2[10][102] = 'U';
    
    // trap location
    unicode_map[17][32] = 99;
    unicode_map[16][80] = 99;
    unicode_map[11][97] = 99;
    unicode_map[27][104] = 99;

    door_placement(map2, 35, 15);
    door_placement(map2, 74, 14);
    door_placement(map2, 68, 18);
    door_placement(map2, 83, 16);
    door_placement(map2, 95, 10);
    door_placement(map2, 104, 10);
    door_placement(map2, 120, 6);
    door_placement(map2, 99, 13);
    door_placement(map2, 108, 25);
    door_placement(map2, 59, 25);

    doorway_placement(map2, 35, 12, 2, 1);
    doorway_placement(map2, 35, 12, 39, 2);
    doorway_placement(map2, 74, 12, 1, 1);
    doorway_placement(map2, 84, 16, 6, 2);
    doorway_placement(map2, 90, 10, 6, 1);
    doorway_placement(map2, 90, 10, 4, 2);
    doorway_placement(map2, 105, 10, 8, 2);
    doorway_placement(map2, 113, 6, 4, 1);
    doorway_placement(map2, 113, 6, 6, 2);
    doorway_placement(map2, 59, 18, 8, 2);
    doorway_placement(map2, 59, 18, 6, 1);
    doorway_placement(map2, 99, 14, 6, 1);
    doorway_placement(map2, 99, 20, 13, 2);
    doorway_placement(map2, 112, 20, 5, 1);
    doorway_placement(map2, 109, 25, 3, 2);

    rooms_info_floor2[1].map = map2;
    rooms_info_floor2[1].unicode_map = unicode_map;

    return rooms_info_floor2;
}


char** create_map(int screen_height, int screen_width){
    char** map = (char**)malloc(screen_height * sizeof(char*));
    for(int i=1; i<=screen_height; i++){
        map[i] = (char*)malloc(screen_width * sizeof(char));
    }
    
    return map;
}


void draw_room(int y, int x, int height, int width, int type){
    room_color_on(type);

    mvhline(y, x, 0, width);             
    mvhline(y + height, x, 0, width);    
    mvvline(y, x, 0, height);            
    mvvline(y, x + width, 0, height);    
    mvaddch(y, x, ACS_ULCORNER);         
    mvaddch(y + height, x, ACS_LLCORNER);
    mvaddch(y, x + width, ACS_URCORNER); 
    mvaddch(y + height, x + width, ACS_LRCORNER);

    room_color_off(type);
}


void door_placement(char** map1, int x, int y){
    map1[y][x] = '+';
}


void doorway_placement(char** map1, int x, int y, int length, int alignment){
    // 1 : | , 2 : -
    switch(alignment){
        case 1 :
        for(int i=y; i<=y+length; i++){
            map1[i][x] = '#';
        }
        break;

        case 2 : 
        for(int i=x; i<=x+length; i++){
            map1[y][i] = '#';
        }
    }
}


void new_game(int screen_height, int screen_width, player_info* players_info, int* player_count){
    int floor_number = 1;
    room_info* rooms_info_floor1 = create_map_floor1(screen_height, screen_width);
    room_info* rooms_info_floor2 = create_map_floor2(screen_height, screen_width);
    game game_info;
    game_info.gold = 0;
    game_info.score = 0;
    game_info.health = 15;
    game_info.dagger = 0;
    game_info.wand = 0;
    game_info.arrow = 0;
    game_info.sword = 0;
    game_info.weapon = 1;
    game_info.hunger = 0;
    game_info.food = 0;
    game_info.food1 = 0;
    game_info.food2 = 0;
    game_info.food3 = 0;
    game_info.hunger_distance = 0;
    game_info.regen_distance = 0;
    game_info.hunger_health_distance = 0;
    game_info.exprience = 0;
    game_info.enemy_health = (int*)malloc(20 * sizeof(char));
    game_info.enemy_health[1] = 5;
    game_info.enemy_health[2] = 10;
    game_info.enemy_health[3] = 15;
    game_info.enemy_health[4] = 20;
    game_info.enemy_health[5] = 25;
    // 1 health , 2 speed , 3 damage
    game_info.spell = (int*)malloc(10 * sizeof(int));
    game_info.spell_state = (int*)malloc(10 * sizeof(int));

    char** explored_map = (char**)malloc(screen_height * sizeof(char*));
    for(int i=1; i<=screen_height; i++){
        explored_map[i] = (char*)malloc(screen_width * sizeof(char));
    }

    game_info.explored_map = explored_map;
    
    for(int i=1; i<=5; i++){
        game_info.spell[i] = 0;
        game_info.spell_state[i] = 0;
    }

    int game_state = gameplay(screen_height, screen_width, &floor_number, rooms_info_floor1, rooms_info_floor2, &game_info);
    if(game_state == 99){
        clear();
        refresh();
        save_game(&game_info, rooms_info_floor1, rooms_info_floor2, screen_height, screen_width);
        pregame_menu(screen_height, screen_width, players_info, player_count);
    }
    
    return;
}


void load_game(int screen_height, int screen_width){
    //room_info* rooms_info_floor1 = create_map_floor1(screen_height, screen_width);

    //
    room_info* rooms_info_floor1 = (room_info*)malloc(10 * sizeof(room_info));
    char** map1 = (char**)malloc(screen_height * sizeof(char*));
    for(int i=1; i<=screen_height; i++){
        map1[i] = (char*)malloc(screen_width * sizeof(char));
    }
    int** unicode_map = (int**)malloc(screen_height * sizeof(int*));
    for(int i=1; i<=screen_height; i++){
        unicode_map[i] = (int*)malloc(screen_width * sizeof(int));
    }
    rooms_info_floor1[1].map = map1;
    rooms_info_floor1[1].unicode_map = unicode_map;
    //rooms_info_floor1[1].unicode_map[1][1] = 9;
    //

    room_info* rooms_info_floor2 = create_map_floor2(screen_height, screen_width);
    game game_info;
    game_info.spell = (int*)malloc(10 * sizeof(int));
    char** explored_map = (char**)malloc(screen_height * sizeof(char*));
    for(int i=1; i<=screen_height; i++){
        explored_map[i] = (char*)malloc(screen_width * sizeof(char));
    }
    game_info.explored_map = explored_map;

    char* line = (char*)malloc((screen_width * 2) * sizeof(char));
    FILE* game_load = fopen("game.txt", "r");
    

    for (int i = 1; i <= screen_height; i++) {
        for (int j = 1; j <= screen_width; j++) {
            fgets(line, sizeof(line), game_load);
            sscanf(line, "%c", &rooms_info_floor1[1].map[i][j]);
        }
    }

    // Read data for rooms_info_floor2 map
    for (int i = 1; i <= screen_height; i++) {
        for (int j = 1; j <= screen_width; j++) {
            fgets(line, sizeof(line), game_load);
            sscanf(line, "%c", &rooms_info_floor2[1].map[i][j]);
        }
    }

    // Read data for rooms_info_floor1 unicode_map
    for (int i = 1; i <= screen_height; i++) {
        for (int j = 1; j <= screen_width; j++) {
            fgets(line, sizeof(line), game_load);
            sscanf(line, "%d", &rooms_info_floor1[1].unicode_map[i][j]);
        }
    }

    // Read data for rooms_info_floor1 state
    for (int i = 1; i <= 7; i++) {
        fgets(line, sizeof(line), game_load);
        sscanf(line, "%d", &rooms_info_floor1[i].state);
    }

    // Read data for rooms_info_floor2 state
    for (int i = 1; i <= 7; i++) {
        fgets(line, sizeof(line), game_load);
        sscanf(line, "%d", &rooms_info_floor2[i].state);
    }

    // Read data for game_info
    fgets(line, sizeof(line), game_load);
    sscanf(line, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d ", &game_info.arrow, &game_info.dagger, &game_info.floor,
    &game_info.food, &game_info.gold, &game_info.health, &game_info.hunger, &game_info.score, &game_info.spell[1],
    &game_info.spell[2], &game_info.spell[3], &game_info.sword, &game_info.wand, &game_info.weapon, &game_info.x, &game_info.y);

    // Read data for game_info explored_map
    for (int i = 1; i <= screen_height; i++) {
        for (int j = 1; j <= screen_width; j++) {
            fgets(line, sizeof(line), game_load);
            sscanf(line, "%c", &game_info.explored_map[i][j]);
        }
    }
    
    /*for(int i=1; i<=screen_height; i++){
        fgets(line, sizeof(line), game_load);
        printf("%s", line);
        for(int j=1; j<=screen_width; j++){
            sscanf(line, " %c", &rooms_info_floor1[1].map[i][j]);
            line[j] = ' ';
        }
    }*/

    /*for(int i=1; i<=screen_height; i++){
        fgets(line, sizeof(line), game_load);
        for(int j=1; j<=screen_width; j++){
            sscanf(line, " %c", &rooms_info_floor2[1].map[i][j]);
        }
    }*/
    
    /*for (int i = 1; i <= screen_height; i++) {
        for (int j = 1; j <= screen_width; j++) {
            fscanf(game_load, " %d", &rooms_info_floor1[1].unicode_map[i][j]);
        }
    }*/

    /*for(int i=1; i<=screen_height; i++){
        fgets(line, sizeof(line), game_load);
        for(int j=1; j<=screen_width; j++){
            sscanf(line, "%d", &rooms_info_floor1[1].unicode_map[i][j]);
            int a;
            sscanf(line, "%d", &a);
        }
    }*/
    
    //
    /*for(int i=1; i<=screen_height; i++){
        fgets(line, sizeof(line), game_load);
        for(int j=1; j<=screen_width; j++){
            sscanf(line, "%d", rooms_info_floor2[1].unicode_map[i][j]);
        }
    }*/
    //

   /*fgets(line, sizeof(line), game_load);
   for(int i=1; i<=14; i++){
    sscanf(line, "%d ", &rooms_info_floor1[i].state);
   }

   fgets(line, sizeof(line), game_load);
   for(int i=1; i<=14; i++){
    sscanf(line, "%d ", &rooms_info_floor2[i].state);
   }

   fgets(line, sizeof(line), game_load);
   sscanf(line, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d ", &game_info.arrow, &game_info.dagger, &game_info.floor,
    &game_info.food, &game_info.gold, &game_info.health, &game_info.hunger, &game_info.score, &game_info.spell[1],
    &game_info.spell[2], &game_info.spell[3], &game_info.sword, &game_info.wand, &game_info.weapon, &game_info.x, &game_info.y);

    for(int i=1; i<=screen_height; i++){
        fgets(line, sizeof(line), game_load);
        for(int j=1; j<=screen_width; j++){
            sscanf(line, " %c", &explored_map[i][j]);
        }
    }*/

    game_info.explored_map = explored_map;

    /*for(int i=1; i<=screen_height; i++){
        for(int j=1; j<=screen_width; j++){
            mvprintw(i, j, "%c", explored_map[i][j]);
        }
    }*/

    /*switch(game_info.floor){
        case 1 :
        in_room_check(rooms_info_floor1[1].map, rooms_info_floor1, game_info.x, game_info.y);
        break;
    }*/
    fclose(game_load);

    //gameplay(screen_height, screen_width, game_info.floor, rooms_info_floor1, rooms_info_floor2, &game_info);
    save_game(&game_info, rooms_info_floor1, rooms_info_floor2, screen_height, screen_width);
    return;
}


int gameplay(int screen_height, int screen_width, int* floor_number, room_info* rooms_info_floor1, room_info* rooms_info_floor2, 
game* game_info){
    clear();
    refresh();
    /*int floor_number = 1;
    room_info* rooms_info_floor1 = create_map_floor1(screen_height, screen_width);
    room_info* rooms_info_floor2 = create_map_floor2(screen_height, screen_width);
    game game_info;
    game_info.gold = 0;
    game_info.score = 0;
    game_info.health = 15;
    game_info.dagger = 0;
    game_info.wand = 0;
    game_info.arrow = 0;
    game_info.sword = 0;
    game_info.weapon = 1;
    game_info.hunger = 10;
    game_info.food = 4;
    game_info.spell = (int*)malloc(10 * sizeof(int));
    // 1 health , 2 speed , 3 damage

    char** explored_map = (char**)malloc(screen_height * sizeof(char*));
    for(int i=1; i<=screen_height; i++){
        explored_map[i] = (char*)malloc(screen_width * sizeof(char));
    }
    
    for(int i=1; i<=5; i++){
        game_info.spell[i] = 0;
    }*/
    
    while(1){
        int game_state = 0;
        clear();
        refresh();
        switch(*floor_number){
        case 1 : 
        (*game_info).floor = 1;
        game_state = movement(rooms_info_floor1[1].map, rooms_info_floor1, floor_number, screen_height, screen_width, game_info);
        if(game_state == 99){
            return 99;
        }

        else if(game_state == 101){
            (*floor_number) = 2;
        }
        break;

        case 2 :
        (*game_info).floor = 2;
        for(int i=1; i<=screen_height; i++){
            for(int j=1; j<=screen_width; j++){
                (*game_info).explored_map[i][j] = ' ';
            }
        }
        game_state = movement(rooms_info_floor2[1].map, rooms_info_floor2, floor_number, screen_height, screen_width, game_info);
        if(game_state == 99){
            return 99;
        }
        break;
        }
    }
    
    //save_game(game_info, rooms_info_floor1)
}


void save_game(game* game_info, room_info* rooms_info_floor1,room_info* rooms_info_floor2, int screen_height, int screen_width){
    /*
    1 map floor 1
    1 map floor 2
    2 unicode map floor 1
    2 unicode map floor 2
    3 room state floor 1
    3 room state floor 2
    4 game info
    5 explored map
    */
    FILE* game_save = fopen("game.txt", "w");

    for(int i=1; i<=screen_height; i++){
        for(int j=1; j<=screen_width; j++){
            fprintf(game_save, "%c ", rooms_info_floor1[1].map[i][j]);
        }
        fprintf(game_save, "\n");
    }

    for(int i=1; i<=screen_height; i++){
        for(int j=1; j<=screen_width; j++){
            fprintf(game_save, "%c ", rooms_info_floor2[1].map[i][j]);
        }
        fprintf(game_save, "\n");
    }

    for(int i=1; i<=screen_height; i++){
        for(int j=1; j<=screen_width; j++){
            fprintf(game_save, "%d ", rooms_info_floor1[1].unicode_map[i][j]);
        }
        fprintf(game_save, "\n");
    }

    /*FILE* game_save = fopen("game.txt", "a");
    for(int i=1; i<=screen_height; i++){
        for(int j=1; j<=screen_width; j++){
            fprintf(game_save, "%c ", rooms_info_floor2[1].unicode_map[i][j]);
        }
        fprintf(game_save, "\n");
    }*/

    for(int i=1; i<=7; i++){
        fprintf(game_save, "%d ", rooms_info_floor1[i].state);
    }
    fprintf(game_save, "\n");

    for(int i=1; i<=7; i++){
        fprintf(game_save, "%d ", rooms_info_floor2[i].state);
    }
    fprintf(game_save, "\n");

    fprintf(game_save, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d ", (*game_info).arrow, (*game_info).dagger, (*game_info).floor,
    (*game_info).food, (*game_info).gold, (*game_info).health, (*game_info).hunger, (*game_info).score, (*game_info).spell[1],
    (*game_info).spell[2], (*game_info).spell[3], (*game_info).sword, (*game_info).wand, (*game_info).weapon, (*game_info).x,
    (*game_info).y);
    fprintf(game_save, "\n");

    for(int i=1; i<=screen_height; i++){
        for(int j=1; j<=screen_width; j++){
            fprintf(game_save, "%c ", (*game_info).explored_map[i][j]);
        }
        fprintf(game_save, "\n");
    }

    fclose(game_save);
}


int movement(char** map, room_info* rooms_info, int *floor_number, int screen_height, int screen_width, game* game_info){
    char player_avatar = '@';
    int player_avatar_x, player_avatar_y;
    char** temp_map = (char**)malloc(screen_height * sizeof(char*));
    for(int i=1; i<=screen_height; i++){
        temp_map[i] = (char*)malloc(screen_width * sizeof(char));
    }
    
    switch(*floor_number){
        case 1 : 
        player_avatar_x = 72, player_avatar_y = 23;
        break;

        case 2 :
        new_floor_message();
        player_avatar_x = 98, player_avatar_y = 9;
        break;
    }
    noecho();
    curs_set(0);
    cbreak();
    keypad(stdscr, TRUE);
    in_room_check(map, rooms_info, player_avatar_x, player_avatar_y);
    mvprintw(player_avatar_y, player_avatar_x, "@");
    while(1){
        int c = getch();
        delete_message();
        //in_room_check(map, rooms_info, player_avatar_x, player_avatar_y);
        switch(c){
            case KEY_RIGHT :
            player_avatar_x++;
            if(move_check(map, temp_map, &player_avatar_x, &player_avatar_y,rooms_info[1].unicode_map, game_info)){
                move_initialize(map, player_avatar_x - 1, player_avatar_y, player_avatar_x, player_avatar_y);
            }
            else{
                player_avatar_x--;
            }
            break;

            case KEY_DOWN :
            player_avatar_y++;
            if(move_check(map, temp_map, &player_avatar_x, &player_avatar_y, rooms_info[1].unicode_map, game_info)){
                move_initialize(map, player_avatar_x, player_avatar_y - 1, player_avatar_x, player_avatar_y);
            }
            else{
                player_avatar_y--;
            }
            break;

            case KEY_LEFT :
            player_avatar_x--;
            if(move_check(map, temp_map, &player_avatar_x, &player_avatar_y, rooms_info[1].unicode_map, game_info)){
                move_initialize(map, player_avatar_x + 1, player_avatar_y, player_avatar_x, player_avatar_y);
            }
            else{
                player_avatar_x++;
            }
            break;
            
            case KEY_UP :
            player_avatar_y--;
            if(move_check(map, temp_map, &player_avatar_x, &player_avatar_y, rooms_info[1].unicode_map, game_info)){
                move_initialize(map, player_avatar_x, player_avatar_y + 1, player_avatar_x, player_avatar_y);
            }
            else{
                player_avatar_y++;
            }
            break;

            case 'm' :
            m_button_function(screen_height, screen_width, map, temp_map, rooms_info);
            break;

            case 's' :
            trap_search(map, rooms_info[1].unicode_map, game_info, player_avatar_x, player_avatar_y);
            break;

            case 'i' : 
            i_button_function(screen_height, screen_width, *game_info);
            break;

            case 'q' :
            q_button_function(game_info);
            break;

            case 'e' :
            e_button_function(screen_height, screen_width, game_info);
            break;

            case '1' :
            select_weapon(game_info, 1);
            break;

            case '2' :
            select_weapon(game_info, 2);
            break;

            case '3' :
            select_weapon(game_info, 3);
            break;

            case '4' :
            select_weapon(game_info, 4);
            break;

            case '5' :
            select_weapon(game_info, 5);
            break;

            case '6' :
            select_spell(screen_width, game_info);
            break;

            case 27 :
            return 99;
            break;
        }

        if((player_avatar_x == 49) && (player_avatar_y == 27)){
            rooms_info[7].state = 0;
            for(int i=rooms_info[7].y; i<=rooms_info[7].y + rooms_info[7].height; i++){
                for(int j=rooms_info[7].x; j<=rooms_info[7].x + rooms_info[7].width; j++){
                    mvprintw(i, j, " ");
                }
            }
        }

        in_room_check(map, rooms_info, player_avatar_x, player_avatar_y);
        doorway_check(map, rooms_info, player_avatar_x, player_avatar_y);

        attron(A_REVERSE | COLOR_PAIR(8));
        mvprintw(player_avatar_y, player_avatar_x, "@");
        attroff(A_REVERSE | COLOR_PAIR(8));
        
        health_regen(game_info);
        hunger_health(game_info);
        hunger(game_info);
        enemy_check(map, rooms_info, game_info, player_avatar_x, player_avatar_y, screen_height);
        game_status_print(screen_height, *game_info);

        refresh();

        if(map[player_avatar_y][player_avatar_x] == '<'){
            //(*floor_number)++;
            clear();
            refresh();
            return 101;
        }
        
        if(rooms_info[1].unicode_map[player_avatar_y][player_avatar_x] == 100){
            win_game(*game_info, screen_height, screen_width);
            return 99;
        }
        
        int game_state = no_health_death(*game_info, screen_height, screen_width);
        if(game_state){
            return 99;
        }
        
        /*else{
            mvprintw(18, 70, "%c", map[18][70]);
        }*/
    }
    echo();
    curs_set(1);
    nocbreak;
}


int move_check(char** map, char** temp_map, int* x, int* y, int** unicode_map, game* game_info){
    if((map[*y][*x] == '.') ||
       (map[*y][*x] == '+') ||
       (map[*y][*x] == '#') ||
       (map[*y][*x] == '<') ||
       (map[*y][*x] == '^')
       ){

        if((*game_info).regen_distance == 16){
            (*game_info).regen_distance = 0;
        }

        else{
            (*game_info).regen_distance++;
        }

        if((*game_info).hunger_distance == 31){
            (*game_info).hunger_distance = 0;
        }

        else{
            (*game_info).hunger_distance++;
        }

        if((*game_info).hunger_health_distance == 21){
            (*game_info).hunger_health_distance = 0;
        }

        else{
            (*game_info).hunger_health_distance++;
        }

        (*game_info).x = *x;
        (*game_info).y = *y;

        if(map[*y][*x] == '+'){
        temp_map[*y][*x] = '+';
        (*game_info).explored_map[*y][*x] = '+';
        }

        else if(map[*y][*x] == '#'){
        temp_map[*y][*x] = '#';
        (*game_info).explored_map[*y][*x] = '#';
        }


        if(unicode_map[*y][*x] == 1){
            unicode_map[*y][*x] = 0;
            (*game_info).gold += 50;
            (*game_info).score += 100;
            pick_gold_message();
        }

        else if(unicode_map[*y][*x-1] == 1){
            unicode_map[*y][*x-1] = 0;
            (*game_info).gold += 50;
            (*game_info).score += 100;
            pick_gold_message();
        }


        if(unicode_map[*y][*x] == 2){
            unicode_map[*y][*x] = 0;
            (*game_info).gold += 150;
            (*game_info).score += 300;
            pick_diamond_message();
        }

        else if(unicode_map[*y][*x-1] == 2){
            unicode_map[*y][*x-1] = 0;
            (*game_info).gold += 150;
            (*game_info).score += 300;
            pick_diamond_message();
        }


        if(unicode_map[*y][*x] == 3){
            int c = getch();
            if(c == 'f'){
                unicode_map[*y][*x] = 0;
                (*game_info).dagger += 10;
                (*game_info).score += 75;
                pick_dagger_message();
            }
        }

        else if(unicode_map[*y][*x-1] == 3){
            int c = getch();
            if(c == 'f'){
                unicode_map[*y][*x-1] = 0;
                (*game_info).dagger += 10;
                (*game_info).score += 75;
                pick_dagger_message();
            }
        }


        if(unicode_map[*y][*x] == 4){
            int c = getch();
            if(c == 'f'){
                unicode_map[*y][*x] = 0;
                (*game_info).wand += 8;
                (*game_info).score += 75;
                pick_wand_message();
            }
        }

        else if(unicode_map[*y][*x-1] == 4){
            int c = getch();
            if(c == 'f'){
                unicode_map[*y][*x-1] = 0;
                (*game_info).wand += 8;
                (*game_info).score += 75;
                pick_wand_message();
            }
        }


        if(unicode_map[*y][*x] == 5){
            int c = getch();
            if(c == 'f'){
                unicode_map[*y][*x] = 0;
            (*game_info).arrow += 20;
            (*game_info).score += 75;
            pick_arrow_message();
            }
        }

        else if(unicode_map[*y][*x-1] == 5){
            int c = getch();
            if(c == 'f'){
                unicode_map[*y][*x-1] = 0;
            (*game_info).arrow += 20;
            (*game_info).score += 75;
            pick_arrow_message();
            }
        }


        if(unicode_map[*y][*x] == 6){
            int c = getch();
            if(c == 'f'){
                if((*game_info).sword == 0){
                unicode_map[*y][*x] = 0;
                (*game_info).sword += 1;
                (*game_info).score += 75;
                pick_sword_message();
                }

                else{
                sword_have_message();
                }
            }
        }

        else if(unicode_map[*y][*x-1] == 6){
            int c = getch();
            if(c == 'f'){
                if((*game_info).sword == 0){
                unicode_map[*y][*x-1] = 0;
                (*game_info).sword += 1;
                (*game_info).score += 75;
                pick_sword_message();
                }

                else{
                    sword_have_message();
                }
            }
        }


        if((unicode_map[*y][*x] == 71) || (unicode_map[*y][*x] == 72) || (unicode_map[*y][*x] == 73)){
            int state = pick_food(game_info, unicode_map[*y][*x]);
            if(state){
                unicode_map[*y][*x] = 0;
            }
        }

        else if((unicode_map[*y][*x-1] == 71) || (unicode_map[*y][*x-1] == 72) || (unicode_map[*y][*x-1] == 73)){
            int state = pick_food(game_info, unicode_map[*y][*x-1]);
            if(state){
                unicode_map[*y][*x-1] = 0;
            }
        }


        if(unicode_map[*y][*x] == 8){
            int c = getch();
            if(c == 'f'){
                unicode_map[*y][*x] = 0;
            (*game_info).spell[1]++;
            (*game_info).spell_state[1] += 2;
            pick_spell_message(8);
            }
        }

        else if(unicode_map[*y][*x-1] == 8){
            int c = getch();
            if(c == 'f'){
                unicode_map[*y][*x-1] = 0;
            (*game_info).spell[1]++;
            (*game_info).spell_state[1] += 2;
            pick_spell_message(8);
            }
        }


        if(unicode_map[*y][*x] == 9){
            int c = getch();
            if(c == 'f'){
                unicode_map[*y][*x] = 0;
            (*game_info).spell[2]++;
            pick_spell_message(9);
            }
        }

        else if(unicode_map[*y][*x-1] == 9){
            int c = getch();
            if(c == 'f'){
                unicode_map[*y][*x-1] = 0;
            (*game_info).spell[2]++;
            pick_spell_message(9);
            }
        }


        if(unicode_map[*y][*x] == 10){
            int c = getch();
            if(c == 'f'){
                unicode_map[*y][*x] = 0;
            (*game_info).spell[3]++;
            (*game_info).spell_state[3] += 2;
            pick_spell_message(10);
            }
        }

        else if(unicode_map[*y][*x-1] == 10){
            int c = getch();
            if(c == 'f'){
                unicode_map[*y][*x-1] = 0;
            (*game_info).spell[3]++;
            (*game_info).spell_state[3] += 2;
            pick_spell_message(10);
            }
        }

        if(unicode_map[*y][*x] == 100){
            return 100;
        }

        else if(unicode_map[*y][*x-1] == 100){
            return 100;
        }


        if(unicode_map[*y][*x] == 99){
            (*game_info).health--;
            unicode_map[*y][*x] = 0;
            map[*y][*x] = '^';
            stepontrap_message();
        }
        
        //

       return 1;
    }

    else if((*x == 49) && (*y == 28)){
        *x = 16, *y = 19;
    }

    else if((*x == 16) && (*y = 25)){
        *x = 49, *y = 27;
    }

    else{
        return 0;
    }
}


void move_initialize(char** map, int x1, int y1, int x2, int y2){
    attron(A_REVERSE | COLOR_PAIR(8));
    mvprintw(y2, x2, "@");
    attroff(A_REVERSE | COLOR_PAIR(8));
    mvprintw(y1, x1, "%c", map[y1][x1]);
    refresh();
}


void in_room_check(char** map, room_info* rooms_info, int x, int y){
    char *money_bag = "💰";
    char *diamond = "💎";
    char *dagger = "🗡️";
    char *wand = "🔮";
    char *arrow = "🏹";
    char *sword = "⚔️";
    char* food1 = "🍎";
    char* food2 = "🍞";
    char* food3 = "🥩";
    char *spell1 = "❤️";
    char *spell2 = "⚡️";
    char *spell3 = "🔥";
    char *portal = "⚜️";

    for(int i=1; i<=7; i++){
        for(int j=rooms_info[i].y; j<=rooms_info[i].y + rooms_info[i].height; j++){
            for(int k=rooms_info[i].x; k<=rooms_info[i].x + rooms_info[i].width; k++){
                if((x == k) && (y == j)){
                    if(rooms_info[i].state == 0)
                    new_room_message(rooms_info[i].type);
                    rooms_info[i].state = 1;
                }
            }
        }
    }

    for(int i=1; i<=7; i++){
        /*if(i == 7){
            attron(COLOR_PAIR(15));
        }*/

        if(rooms_info[i].state){
            draw_room(rooms_info[i].y, rooms_info[i].x, rooms_info[i].height, rooms_info[i].width, rooms_info[i].type);
        }

        if(rooms_info[i].state){
                for(int j=rooms_info[i].y; j<=rooms_info[i].y + rooms_info[i].height; j++){
                    for(int k=rooms_info[i].x; k<=rooms_info[i].x + rooms_info[i].width; k++){
                        if((map[j][k]=='D') || (map[j][k]=='F') || (map[j][k]=='G') || (map[j][k]=='S') || (map[j][k]=='U')){
                            attron(A_BOLD | COLOR_PAIR(1));
                        }
                        mvprintw(j, k, "%c", map[j][k]);
                        if((map[j][k]=='D') || (map[j][k]=='F') || (map[j][k]=='G') || (map[j][k]=='S') || (map[j][k]=='U')){
                            attroff(A_BOLD | COLOR_PAIR(1));
                        }
                        if(rooms_info[1].unicode_map[j][k] == 1){
                            mvaddstr(j, k, money_bag);
                            room_color_on(rooms_info[i].type);
                            mvvline(j, rooms_info[i].x + rooms_info[i].width - 1, 0, 1);
                            room_color_off(rooms_info[i].type);
                            mvprintw(j, rooms_info[i].x + rooms_info[i].width, " ");
                        }

                        else if(rooms_info[1].unicode_map[j][k] == 2){
                            mvaddstr(j, k, diamond);
                            room_color_on(rooms_info[i].type);
                            mvvline(j, rooms_info[i].x + rooms_info[i].width, 0, 1);
                            room_color_off(rooms_info[i].type);
                            mvprintw(j, rooms_info[i].x + rooms_info[i].width + 1, " ");
                        }

                        else if(rooms_info[1].unicode_map[j][k] == 3){
                            mvaddstr(j, k, dagger);
                            room_color_on(rooms_info[i].type);
                            mvvline(j, rooms_info[i].x + rooms_info[i].width, 0, 1);
                            room_color_off(rooms_info[i].type);
                            mvprintw(j, rooms_info[i].x + rooms_info[i].width + 1, " ");
                        }

                        else if(rooms_info[1].unicode_map[j][k] == 4){
                            mvaddstr(j, k, wand);
                            room_color_on(rooms_info[i].type);
                            mvvline(j, rooms_info[i].x + rooms_info[i].width, 0, 1);
                            room_color_off(rooms_info[i].type);
                            mvprintw(j, rooms_info[i].x + rooms_info[i].width + 1, " ");
                        }

                        else if(rooms_info[1].unicode_map[j][k] == 5){
                            mvaddstr(j, k, arrow);
                            room_color_on(rooms_info[i].type);
                            mvvline(j, rooms_info[i].x + rooms_info[i].width, 0, 1);
                            room_color_off(rooms_info[i].type);
                            mvprintw(j, rooms_info[i].x + rooms_info[i].width + 1, " ");
                        }

                        else if(rooms_info[1].unicode_map[j][k] == 6){
                            mvaddstr(j, k, sword);
                            room_color_on(rooms_info[i].type);
                            mvvline(j, rooms_info[i].x + rooms_info[i].width, 0, 1);
                            room_color_off(rooms_info[i].type);
                            mvprintw(j, rooms_info[i].x + rooms_info[i].width + 1, " ");
                        }

                        else if(rooms_info[1].unicode_map[j][k] == 71){
                            mvaddstr(j, k, food1);
                            room_color_on(rooms_info[i].type);
                            mvvline(j, rooms_info[i].x + rooms_info[i].width, 0, 1);
                            room_color_off(rooms_info[i].type);
                            mvprintw(j, rooms_info[i].x + rooms_info[i].width + 1, " ");
                        }

                        else if(rooms_info[1].unicode_map[j][k] == 72){
                            mvaddstr(j, k, food2);
                            room_color_on(rooms_info[i].type);
                            mvvline(j, rooms_info[i].x + rooms_info[i].width, 0, 1);
                            room_color_off(rooms_info[i].type);
                            mvprintw(j, rooms_info[i].x + rooms_info[i].width + 1, " ");
                        }

                        else if(rooms_info[1].unicode_map[j][k] == 73){
                            mvaddstr(j, k, food3);
                            room_color_on(rooms_info[i].type);
                            mvvline(j, rooms_info[i].x + rooms_info[i].width, 0, 1);
                            room_color_off(rooms_info[i].type);
                            mvprintw(j, rooms_info[i].x + rooms_info[i].width + 1, " ");
                        }

                        else if(rooms_info[1].unicode_map[j][k] == 8){
                            mvaddstr(j, k, spell1);
                            room_color_on(rooms_info[i].type);
                            mvvline(j, rooms_info[i].x + rooms_info[i].width, 0, 1);
                            room_color_off(rooms_info[i].type);
                            mvprintw(j, rooms_info[i].x + rooms_info[i].width + 1, " ");
                        }

                        else if(rooms_info[1].unicode_map[j][k] == 9){
                            mvaddstr(j, k, spell2);
                            room_color_on(rooms_info[i].type);
                            mvvline(j, rooms_info[i].x + rooms_info[i].width, 0, 1);
                            room_color_off(rooms_info[i].type);
                            mvprintw(j, rooms_info[i].x + rooms_info[i].width + 1, " ");
                        }

                        else if(rooms_info[1].unicode_map[j][k] == 10){
                            mvaddstr(j, k, spell3);
                            room_color_on(rooms_info[i].type);
                            mvvline(j, rooms_info[i].x + rooms_info[i].width, 0, 1);
                            room_color_off(rooms_info[i].type);
                            mvprintw(j, rooms_info[i].x + rooms_info[i].width + 1, " ");
                        }

                        else if(rooms_info[1].unicode_map[j][k] == 100){
                            mvaddstr(j, k, portal);
                            room_color_on(rooms_info[i].type);
                            mvvline(j, rooms_info[i].x + rooms_info[i].width, 0, 1);
                            room_color_off(rooms_info[i].type);
                            mvprintw(j, rooms_info[i].x + rooms_info[i].width + 1, " ");
                        }
                    } 
                }
            }

            if(rooms_info[i].state){
                for(int j=rooms_info[i].y; j<=rooms_info[i].y + rooms_info[i].height; j++){
                    for(int k=rooms_info[i].x; k<=rooms_info[i].x + rooms_info[i].width; k++){
                        if(rooms_info[1].unicode_map[j][k] == 1){
                            mvaddstr(j, k, money_bag);
                            room_color_on(rooms_info[i].type);
                            mvvline(j, rooms_info[i].x + rooms_info[i].width, 0, 1);
                            room_color_off(rooms_info[i].type);
                            mvprintw(j, rooms_info[i].x + rooms_info[i].width + 1, " ");
                        }

                        else if(rooms_info[1].unicode_map[j][k] == 2){
                            mvaddstr(j, k, diamond);
                            room_color_on(rooms_info[i].type);
                            mvvline(j, rooms_info[i].x + rooms_info[i].width, 0, 1);
                            room_color_off(rooms_info[i].type);
                            mvprintw(j, rooms_info[i].x + rooms_info[i].width + 1, " ");
                        }

                        else if(rooms_info[1].unicode_map[j][k] == 3){
                            mvaddstr(j, k, dagger);
                            room_color_on(rooms_info[i].type);
                            mvvline(j, rooms_info[i].x + rooms_info[i].width, 0, 1);
                            room_color_off(rooms_info[i].type);
                            mvprintw(j, rooms_info[i].x + rooms_info[i].width + 1, " ");
                        }

                        else if(rooms_info[1].unicode_map[j][k] == 4){
                            mvaddstr(j, k, wand);
                            room_color_on(rooms_info[i].type);
                            mvvline(j, rooms_info[i].x + rooms_info[i].width, 0, 1);
                            room_color_off(rooms_info[i].type);
                            mvprintw(j, rooms_info[i].x + rooms_info[i].width + 1, " ");
                        }

                        else if(rooms_info[1].unicode_map[j][k] == 5){
                            mvaddstr(j, k, arrow);
                            room_color_on(rooms_info[i].type);
                            mvvline(j, rooms_info[i].x + rooms_info[i].width, 0, 1);
                            room_color_off(rooms_info[i].type);
                            mvprintw(j, rooms_info[i].x + rooms_info[i].width + 1, " ");
                        }

                        else if(rooms_info[1].unicode_map[j][k] == 6){
                            mvaddstr(j, k, sword);
                            room_color_on(rooms_info[i].type);
                            mvvline(j, rooms_info[i].x + rooms_info[i].width, 0, 1);
                            room_color_off(rooms_info[i].type);
                            mvprintw(j, rooms_info[i].x + rooms_info[i].width + 1, " ");
                        }

                        else if(rooms_info[1].unicode_map[j][k] == 71){
                            mvaddstr(j, k, food1);
                            room_color_on(rooms_info[i].type);
                            mvvline(j, rooms_info[i].x + rooms_info[i].width, 0, 1);
                            room_color_off(rooms_info[i].type);
                            mvprintw(j, rooms_info[i].x + rooms_info[i].width + 1, " ");
                        }

                        else if(rooms_info[1].unicode_map[j][k] == 72){
                            mvaddstr(j, k, food2);
                            room_color_on(rooms_info[i].type);
                            mvvline(j, rooms_info[i].x + rooms_info[i].width, 0, 1);
                            room_color_off(rooms_info[i].type);
                            mvprintw(j, rooms_info[i].x + rooms_info[i].width + 1, " ");
                        }

                        else if(rooms_info[1].unicode_map[j][k] == 73){
                            mvaddstr(j, k, food3);
                            room_color_on(rooms_info[i].type);
                            mvvline(j, rooms_info[i].x + rooms_info[i].width, 0, 1);
                            room_color_off(rooms_info[i].type);
                            mvprintw(j, rooms_info[i].x + rooms_info[i].width + 1, " ");
                        }

                        else if(rooms_info[1].unicode_map[j][k] == 8){
                            mvaddstr(j, k, spell1);
                            room_color_on(rooms_info[i].type);
                            mvvline(j, rooms_info[i].x + rooms_info[i].width, 0, 1);
                            room_color_off(rooms_info[i].type);
                            mvprintw(j, rooms_info[i].x + rooms_info[i].width + 1, " ");
                        }

                        else if(rooms_info[1].unicode_map[j][k] == 9){
                            mvaddstr(j, k, spell2);
                            room_color_on(rooms_info[i].type);
                            mvvline(j, rooms_info[i].x + rooms_info[i].width, 0, 1);
                            room_color_off(rooms_info[i].type);
                            mvprintw(j, rooms_info[i].x + rooms_info[i].width + 1, " ");
                        }

                        else if(rooms_info[1].unicode_map[j][k] == 10){
                            mvaddstr(j, k, spell3);
                            room_color_on(rooms_info[i].type);
                            mvvline(j, rooms_info[i].x + rooms_info[i].width, 0, 1);
                            room_color_off(rooms_info[i].type);
                            mvprintw(j, rooms_info[i].x + rooms_info[i].width + 1, " ");
                        }

                        else if(rooms_info[1].unicode_map[j][k] == 100){
                            mvaddstr(j, k, portal);
                            room_color_on(rooms_info[i].type);
                            mvvline(j, rooms_info[i].x + rooms_info[i].width, 0, 1);
                            room_color_off(rooms_info[i].type);
                            mvprintw(j, rooms_info[i].x + rooms_info[i].width + 1, " ");
                        }
                    }
                }
            }
    }

    refresh(); 
}


void room_color_on(int type){
    if(type == 1){
        attron(COLOR_PAIR(18));
    }
    else if(type == 2){
        attron(COLOR_PAIR(16));
    }
    else if( type == 3){
        attron(COLOR_PAIR(7));
    }
}


void room_color_off(int type){
    if(type == 1){
        attroff(COLOR_PAIR(18));
    }
    else if(type == 2){
        attroff(COLOR_PAIR(16));
    }
    else if( type == 3){
        attroff(COLOR_PAIR(7));
    }
}


void doorway_check(char** map, room_info* rooms_info, int x, int y){
    if(map[y-1][x] == '#'){
        mvprintw(y-1, x, "#");
    }

    if(map[y][x+1] == '#'){
        mvprintw(y, x+1, "#");
    }

    if(map[y+1][x] == '#'){
        mvprintw(y+1, x, "#");
    }

    if(map[y][x-1] == '#'){
        mvprintw(y, x-1, "#");
    }
}


void m_button_function(int screen_height, int screen_width, char** map, char** temp_map, room_info* rooms_info){

    for(int i=1; i<=7; i++){
        draw_room(rooms_info[i].y, rooms_info[i].x, rooms_info[i].height, rooms_info[i].width, rooms_info[i].type);
    }
    
    // changed i from 1 to 3
    for(int i=3; i<=screen_height; i++){
        for(int j=1; j<=screen_width; j++){
            //if((map[i][j] == '+') || (map[i][j] == '#')){
            mvprintw(i, j, "%c", map[i][j]);
            //}
        }
    }

    while(1){
        char c = getch();
        if(c == 'm')
        break;
    }

    clear();
    refresh();

    in_room_check(map, rooms_info, 1, 1);

    for(int i=1; i<=screen_height; i++){
        for(int j=1; j<=screen_width; j++){
            mvprintw(i, j, "%c", temp_map[i][j]);
        }
    }

    refresh();
}


void new_room_message(int type){
    attron(A_BOLD | COLOR_PAIR(3));
    switch(type){
        case 1 :
        attron(A_BOLD | COLOR_PAIR(3));
        mvprintw(2, 5, "YOU HAVE ENTERED A NEW ROOM");
        attroff(A_BOLD | COLOR_PAIR(3));
        break;

        case 2 :
        attron(A_BOLD | COLOR_PAIR(16));
        mvprintw(2, 5, "YOU HAVE ENTERED A SPELL ROOM");
        attroff(A_BOLD | COLOR_PAIR(16));
        break;

        case 3 :
        attron(A_BOLD | COLOR_PAIR(7));
        mvprintw(2, 5, "YOU HAVE ENTERED THE TREASURE ROOM");
        attroff(A_BOLD | COLOR_PAIR(7));
        break;
    }
    refresh();
}


void new_floor_message(){
    attron(A_BOLD | COLOR_PAIR(5));
    mvprintw(2, 5, "YOU HAVE ENTERED A NEW FLOOR");
    refresh();
    attroff(A_BOLD | COLOR_PAIR(5));
}


void pick_gold_message(){
    attron(A_BOLD | COLOR_PAIR(7));
    mvprintw(2, 5, "YOU EARNED 50 GOLDS");
    refresh();
    attroff(A_BOLD | COLOR_PAIR(7));
}


void pick_diamond_message(){
    attron(A_BOLD | COLOR_PAIR(6));
    mvprintw(2, 5, "YOU FOUND A DIAMOND");
    refresh();
    attroff(A_BOLD | COLOR_PAIR(6));
}


void pick_dagger_message(){
    attron(A_BOLD | COLOR_PAIR(9));
    mvprintw(2, 5, "YOU FOUND 10 DAGGERS");
    refresh();
    attroff(A_BOLD | COLOR_PAIR(9));
}


void pick_wand_message(){
    attron(A_BOLD | COLOR_PAIR(9));
    mvprintw(2, 5, "YOU FOUND 8 MAGICAL WANDS");
    refresh();
    attroff(A_BOLD | COLOR_PAIR(9));
}


void pick_arrow_message(){
    attron(A_BOLD | COLOR_PAIR(9));
    mvprintw(2, 5, "YOU FOUND 20 ARROWS");
    refresh();
    attroff(A_BOLD | COLOR_PAIR(9));
}


void pick_sword_message(){
    attron(A_BOLD | COLOR_PAIR(9));
    mvprintw(2, 5, "YOU FOUND A SWORD");
    refresh();
    attroff(A_BOLD | COLOR_PAIR(9));
}


void sword_have_message(){
    attron(A_BOLD | COLOR_PAIR(10));
    mvprintw(2, 5, "YOU ALREADY HAVE A SWORD");
    refresh();
    attroff(A_BOLD | COLOR_PAIR(10));
}


void delete_message(){
    mvprintw(2, 5, "                                                        ");
    refresh();
}


void trap_search(char** map, int** unicode_map, game* game_info, int x, int y){
    if(unicode_map[y-1][x] == 99){
        map[y-1][x] = '^';
        mvprintw(y-1, x, "^");
        (*game_info).score += 50;
        unicode_map[y-1][x] = 0;
        trap_found_message(); 
    }

    else if(unicode_map[y-1][x+1] == 99){
        map[y-1][x+1] = '^';
        mvprintw(y-1, x+1, "^");
        (*game_info).score += 50; 
        unicode_map[y-1][x+1] = 0;
        trap_found_message();
    }

    else if(unicode_map[y][x+1] == 99){
        map[y][x+1] = '^';
        mvprintw(y, x+1, "^");
        (*game_info).score += 50;
        unicode_map[y][x+1] = 0;
        trap_found_message(); 
    }

    else if(unicode_map[y+1][x+1] == 99){
        map[y+1][x+1] = '^';
        mvprintw(y+1, x+1, "^");
        (*game_info).score += 50; 
        unicode_map[y+1][x+1] = 0;
        trap_found_message();
    }

    else if(unicode_map[y+1][x] == 99){
        map[y+1][x] = '^';
        mvprintw(y+1, x, "^");
        (*game_info).score += 50; 
        unicode_map[y+1][x] = 0;
        trap_found_message();
    }

    else if(unicode_map[y+1][x-1] == 99){
        map[y+1][x-1] = '^';
        mvprintw(y+1, x-1, "^");
        (*game_info).score += 50; 
        unicode_map[y+1][x-1] = 0;
        trap_found_message();
    }

    else if(unicode_map[y][x-1] == 99){
        map[y][x-1] = '^';
        mvprintw(y, x-1, "^");
        (*game_info).score += 50;
        unicode_map[y][x-1] = 0;
        trap_found_message(); 
    }

    else if(unicode_map[y-1][x-1] == 99){
        map[y-1][x-1] = '^';
        mvprintw(y-1, x-1, "^");
        (*game_info).score += 50; 
        unicode_map[y-1][x-1] = 0;
        trap_found_message();
    }

    refresh();
}


void trap_found_message(){
    attron(A_BOLD | COLOR_PAIR(4));
    mvprintw(2, 5, "YOU FOUND A TRAP");
    refresh();
    attroff(A_BOLD | COLOR_PAIR(4));
}


void stepontrap_message(){
    attron(A_BOLD | COLOR_PAIR(1));
    mvprintw(2, 5, "YOU STEPED ON A TRAP");
    refresh();
    attroff(A_BOLD | COLOR_PAIR(1));
}


void game_status_print(int screen_height, game game_info){
    mvprintw(screen_height - 1, 3, "                                                                              ");
    attron(A_BOLD | COLOR_PAIR(11));
    mvprintw(screen_height - 1, 3, "CURRENT FLOOR : %d    HEALTH : %d / 15    GOLD : %d     SCORE : %d", game_info.floor, game_info.health,
    game_info.gold, game_info.score);
    refresh();
    attroff(A_BOLD | COLOR_PAIR(11));
}


void i_button_function(int screen_height, int screen_width, game game_info){
    char *mace = "🪓";
    char *dagger = "🗡️";
    char *wand = "🔮";
    char *arrow = "🏹";
    char*sword = "⚔️";

    int y = screen_height - 3;
    int x = screen_width - 5;
    
    attron(A_BOLD | COLOR_PAIR(9));

    mvprintw(2, x - 34, "NUMBER   TYPE   DISTANCE   DAMAGE");

    mvaddstr(3, x - 40 , mace);
    mvprintw(3, x - 36, ": %d", 1);
    mvprintw(3, x - 25, "C");
    mvprintw(3, x - 18, "%d", 1);
    mvprintw(3, x - 7, "%d", 5);
    mvaddstr(4, x - 40, dagger);
    mvprintw(4, x - 36, ": %d", game_info.dagger);
    mvprintw(4, x - 25, "W");
    mvprintw(4, x - 18, "%d", 5);
    mvprintw(4, x - 7, "%d", 12);
    mvaddstr(5, x - 40, wand);
    mvprintw(5, x - 36, ": %d", game_info.wand);
    mvprintw(5, x - 25, "W");
    mvprintw(5, x - 18, "%d", 10);
    mvprintw(5, x - 7, "%d", 15);
    mvaddstr(6, x - 40, arrow);
    mvprintw(6, x - 36, ": %d", game_info.arrow);
    mvprintw(6, x - 25, "W");
    mvprintw(6, x - 18, "%d", 5);
    mvprintw(6, x - 7, "%d", 5);
    mvaddstr(7, x - 40, sword);
    mvprintw(7, x - 36, ": %d", game_info.sword);
    mvprintw(7, x - 25, "C");
    mvprintw(7, x - 18, "%d", 1);
    mvprintw(7, x - 7, "%d", 10);

    refresh();
    attroff(A_BOLD | COLOR_PAIR(9));
    getch();

    for(int i=2; i<=8; i++){
        for(int j=x - 40; j<=x-2; j++){
            mvprintw(i, j, " ");
        }
    }

    refresh();
}


void q_button_function(game* game_info){
    if((*game_info).weapon){
        (*game_info).weapon = 0;
        attron(A_BOLD | COLOR_PAIR(10));
        mvprintw(2, 5, "YOU UNEQUIPPED YOUR WEAPON");
        refresh();
        attroff(A_BOLD | COLOR_PAIR(10));
    }

    else if((*game_info).weapon == 0){
        attron(A_BOLD | COLOR_PAIR(13));
        mvprintw(2, 5, "YOU DON'T HAVE ANY WEAPON EQUIPPED");
        refresh();
        attroff(A_BOLD | COLOR_PAIR(13));
    }
}


void select_weapon(game* game_info, int number){
    switch(number){
        case 1 :
        if((*game_info).weapon == 0){
        (*game_info).weapon = 1;
        attron(A_BOLD | COLOR_PAIR(12));
        mvprintw(2, 5, "YOU EQUIPPED A MACE");
        refresh();
        attroff(A_BOLD | COLOR_PAIR(12));
        }

        else{
        attron(A_BOLD | COLOR_PAIR(13));
        mvprintw(2, 5, "YOU MUST UNEQUIPPED YOUR WEAPON FIRST");
        refresh();
        attroff(A_BOLD | COLOR_PAIR(13));
        }
        break;

        case 2 :
        if((*game_info).weapon == 0){
        if((*game_info).dagger){
        (*game_info).weapon = 2;
        attron(A_BOLD | COLOR_PAIR(12));
        mvprintw(2, 5, "YOU EQUIPPED A DAGGER");
        refresh();
        attroff(A_BOLD | COLOR_PAIR(12));
        }

        else{
            attron(A_BOLD | COLOR_PAIR(13));
            mvprintw(2, 5, "YOU DON'T HAVE ANY DAGGER");
            refresh();
            attroff(A_BOLD | COLOR_PAIR(13));
        }
        }

        else{
        attron(A_BOLD | COLOR_PAIR(13));
        mvprintw(2, 5, "YOU MUST UNEQUIPPED YOUR WEAPON FIRST");
        refresh();
        attroff(A_BOLD | COLOR_PAIR(13));
        }
        break;
        
        case 3 :
        if((*game_info).weapon == 0){
        if((*game_info).wand){
        (*game_info).weapon = 3;
        attron(A_BOLD | COLOR_PAIR(12));
        mvprintw(2, 5, "YOU EQUIPPED A MAGICAL WAND");
        refresh();
        attroff(A_BOLD | COLOR_PAIR(12));
        }

        else{
            attron(A_BOLD | COLOR_PAIR(13));
            mvprintw(2, 5, "YOU DON'T HAVE ANY MAGICAL WAND");
            refresh();
            attroff(A_BOLD | COLOR_PAIR(13));
        }
        }

        else{
        attron(A_BOLD | COLOR_PAIR(13));
        mvprintw(2, 5, "YOU MUST UNEQUIPPED YOUR WEAPON FIRST");
        refresh();
        attroff(A_BOLD | COLOR_PAIR(13));
        }
        break;
        
        case 4 :
        if((*game_info).weapon == 0){
        if((*game_info).arrow){
        (*game_info).weapon = 4;
        attron(A_BOLD | COLOR_PAIR(12));
        mvprintw(2, 5, "YOU EQUIPPED AN ARROW");
        refresh();
        attroff(A_BOLD | COLOR_PAIR(12));
        }

        else{
            attron(A_BOLD | COLOR_PAIR(13));
            mvprintw(2, 5, "YOU DON'T HAVE ANY ARROW");
            refresh();
            attroff(A_BOLD | COLOR_PAIR(13));
        }
        }

        else{
        attron(A_BOLD | COLOR_PAIR(13));
        mvprintw(2, 5, "YOU MUST UNEQUIPPED YOUR WEAPON FIRST");
        refresh();
        attroff(A_BOLD | COLOR_PAIR(13));
        }
        break;
        
        case 5 :
        if((*game_info).weapon == 0){
        if((*game_info).sword){
        (*game_info).weapon = 5;
        attron(A_BOLD | COLOR_PAIR(12));
        mvprintw(2, 5, "YOU EQUIPPED A SWORD");
        refresh();
        attroff(A_BOLD | COLOR_PAIR(12));
        }

        else{
            attron(A_BOLD | COLOR_PAIR(13));
            mvprintw(2, 5, "YOU DON'T HAVE ANY SWORD");
            refresh();
            attroff(A_BOLD | COLOR_PAIR(13));
        }
        }

        else{
        attron(A_BOLD | COLOR_PAIR(13));
        mvprintw(2, 5, "YOU MUST UNEQUIPPED YOUR WEAPON FIRST");
        refresh();
        attroff(A_BOLD | COLOR_PAIR(13));
        }
        break;
    }
}


int pick_food(game* game_info, int food_number){
    if((*game_info).food <= 4){
        (*game_info).food++;
        attron(A_BOLD | COLOR_PAIR(13));
        mvprintw(2, 5, "YOU PICKED UP SOME FOOD");
        refresh();
        attroff(A_BOLD | COLOR_PAIR(13));

        switch(food_number){
            case 71 :
            (*game_info).food1++;
            break;

            case 72 :
            (*game_info).food2++;
            break;

            case 73 :
            (*game_info).food3++;
            break;
        }
        return 1;
    }

    else{
        attron(A_BOLD | COLOR_PAIR(13));
        mvprintw(2, 5, "YOU CAN'T PICK UP ANY MORE FOOD");
        refresh();
        attroff(A_BOLD | COLOR_PAIR(13));
        return 0;
    }
}


void e_button_function(int screen_height, int screen_width, game* game_info){
    int x = screen_width - 10;
    char* hunger = "🥣";
    char* food1 = "🍎";
    char* food2 = "🍞";
    char* food3 = "🥩";

    attron(A_BOLD | COLOR_PAIR(9));

    mvprintw(2, x - 15, "FOOD   NUMBER");
    mvaddstr(3, x - 15, food1);
    mvprintw(3, x -  10, ": %d", (*game_info).food1);
    mvaddstr(4, x - 15, food2);
    mvprintw(4, x -  10, ": %d", (*game_info).food2);
    mvaddstr(5, x - 15, food3);
    mvprintw(5, x -  10, ": %d", (*game_info).food3);
    mvprintw(6, x - 1, " /  10");
    //mvprintw(4, x - 3, "a");
    mvprintw(6, x - 15, "HUNGER  :  %d ", (*game_info).hunger);
    
    for(int i=0; i<(*game_info).hunger; i++){
        mvaddstr(7, x - 15 + 2*i, hunger);
    }

    for(int i=(*game_info).hunger-1; i<10; i++){
        mvprintw(7, x - 13 + 2*i, "  ");
    }

    refresh();
    attroff(A_BOLD | COLOR_PAIR(9));

    consume_food(screen_height, screen_width, game_info);
    //getch();
    for(int i=2; i<=7; i++){
        for(int j=x - 15; j<=screen_width; j++){
            mvprintw(i, j, " ");
        }
    }
    refresh();
}


void consume_food(int screen_height, int screen_width, game* game_info){
    while(1){
        int c = getch();
        if(c == 'e'){
            if((*game_info).food >= 1){
            int temp_hunger;
            if((*game_info).hunger >= 3){
                temp_hunger = (*game_info).hunger;
                (*game_info).hunger -= 3;
                //health_spell(game_info);
                consume_selected_food(game_info);
                //(*game_info).food--;

                if((*game_info).health <= 13){
                (*game_info).health += 2;
                health_spell(game_info);
                attron(A_BOLD | COLOR_PAIR(14));
                mvprintw(2, 5, "YOU GAINED SOME HEALTH");
                game_status_print(screen_height, *game_info);
                refresh();
                attroff(A_BOLD | COLOR_PAIR(14));
                }

                else if((*game_info).health == 14){
                    (*game_info).health += 1;
                    attron(A_BOLD | COLOR_PAIR(14));
                    mvprintw(2, 5, "YOU GAINED SOME HEALTH");
                    game_status_print(screen_height, *game_info);
                    refresh();
                    attroff(A_BOLD | COLOR_PAIR(14));
                }  

                else if((*game_info).health == 15){
                    attron(A_BOLD | COLOR_PAIR(14));
                    mvprintw(2, 5, "YOUR HEALTH IS FULL");
                    game_status_print(screen_height, *game_info);
                    refresh();
                    attroff(A_BOLD | COLOR_PAIR(14));
                    return;
                } 
            }

            else if((*game_info).hunger <= 2){
                temp_hunger = (*game_info).hunger;
                (*game_info).hunger = 0;
                consume_selected_food(game_info);
                health_spell(game_info);
                //(*game_info).food--;

                if((*game_info).health <= 13){
                (*game_info).health += 2;
                health_spell(game_info);
                attron(A_BOLD | COLOR_PAIR(14));
                mvprintw(2, 5, "YOU GAINED SOME HEALTH");
                game_status_print(screen_height, *game_info);
                refresh();
                attroff(A_BOLD | COLOR_PAIR(14));
                }

                else if((*game_info).health == 14){
                    (*game_info).health += 1;
                    attron(A_BOLD | COLOR_PAIR(14));
                    mvprintw(2, 5, "YOU GAINED SOME HEALTH");
                    game_status_print(screen_height, *game_info);
                    refresh();
                    attroff(A_BOLD | COLOR_PAIR(14));
                } 

                else if((*game_info).health == 15){
                    attron(A_BOLD | COLOR_PAIR(14));
                    mvprintw(2, 5, "YOUR HEALTH IS FULL");
                    game_status_print(screen_height, *game_info);
                    refresh();
                    attroff(A_BOLD | COLOR_PAIR(14));
                    return;
                } 
            }

            else if((*game_info).hunger == 0){
                if((*game_info).health <= 13){
                (*game_info).health += 2;
                health_spell(game_info);
                attron(A_BOLD | COLOR_PAIR(14));
                mvprintw(2, 5, "YOU GAINED SOME HEALTH");
                game_status_print(screen_height, *game_info);
                refresh();
                attroff(A_BOLD | COLOR_PAIR(14));
                consume_selected_food(game_info);
                //(*game_info).food--;
                }

                else if((*game_info).health == 14){
                    (*game_info).health += 1;
                    attron(A_BOLD | COLOR_PAIR(14));
                    mvprintw(2, 5, "YOU GAINED SOME HEALTH");
                    game_status_print(screen_height, *game_info);
                    refresh();
                    attroff(A_BOLD | COLOR_PAIR(14));
                    consume_selected_food(game_info);
                    //(*game_info).food--;
                }

                else if(temp_hunger == 0){
                    attron(A_BOLD | COLOR_PAIR(13));
                    mvprintw(2, 5, "YOUR HEALTH IS FULL AND YOU ARE NOT HUNGRY");
                    game_status_print(screen_height, *game_info);
                    refresh();
                    attroff(A_BOLD | COLOR_PAIR(13));
                    return;
                }
            }
        }

        else{
            attron(A_BOLD | COLOR_PAIR(13));
            mvprintw(2, 5, "YOU DON'T HAVE ENOUGH FOOD");
            refresh();
            attroff(A_BOLD | COLOR_PAIR(13));
            return;
        }
        
            /*if((*game_info).health <= 13){
                (*game_info).health += 2;
                attron(A_BOLD | COLOR_PAIR(14));
                mvprintw(2, 5, "YOU GAINED SOME HEALTH");
                refresh();
                attroff(A_BOLD | COLOR_PAIR(14));
            }

            else if((*game_info).health == 14){
                (*game_info).health += 1;
                attron(A_BOLD | COLOR_PAIR(14));
                mvprintw(2, 5, "YOU GAINED SOME HEALTH");
                refresh();
                attroff(A_BOLD | COLOR_PAIR(14));
            }

            else if(temp_hunger == 0){
                attron(A_BOLD | COLOR_PAIR(13));
                mvprintw(2, 5, "YOUR HEALTH IS FULL AND YOU ARE NOT HUNGRY");
                refresh();
                attroff(A_BOLD | COLOR_PAIR(13));
            }*/
            e_button_function(screen_height, screen_width, game_info);
        }

        else if(c == ' '){
            return;
        }
    }
}


void consume_selected_food(game* game_info){
    if((*game_info).food1 >= 1){
        (*game_info).food1--;
        (*game_info).food--;
    }

    else{
        if((*game_info).food2 >= 1){
            (*game_info).food2--;
            (*game_info).food--;
        }

        else{
            if((*game_info).food3 >= 1){
            (*game_info).food3--;
            (*game_info).food--;
            }
        }
    }
}


void health_spell(game* game_info){
    //if((*game_info).food){
    if((*game_info).spell_state[1]){
        if((*game_info).health <= 13){
            (*game_info).health += 2;
            (*game_info).spell_state--;
        }

        else if((*game_info).health == 14){
            (*game_info).health = 15;
            (*game_info).spell_state--;
        }
    //}
    }
}


void health_regen(game* game_info){
    if((*game_info).regen_distance == 15){
        if((*game_info).hunger == 0){
            if((*game_info).health <= 14){
                (*game_info).health++;
                (*game_info).hunger++;
            }
        }
    }
}


void hunger(game* game_info){
    if((*game_info).hunger_distance == 30){
        if((*game_info).hunger <= 9){
            (*game_info).hunger++;
        }
    }
}


void hunger_health(game* game_info){
    if((*game_info).hunger_health_distance == 20){
        if((*game_info).hunger == 10){
            (*game_info).health--;
        }
    }
}


void pick_spell_message(int number){
    switch(number){
        case 8 : 
        attron(A_BOLD | COLOR_PAIR(9));
        mvprintw(2, 5, "YOU FOUND A HEALTH SPELL");
        refresh();
        attroff(A_BOLD | COLOR_PAIR(9));
        break;
        
        case 9 : 
        attron(A_BOLD | COLOR_PAIR(9));
        mvprintw(2, 5, "YOU FOUND A SPEED SPELL");
        refresh();
        attroff(A_BOLD | COLOR_PAIR(9));
        break;

        case 10 : 
        attron(A_BOLD | COLOR_PAIR(9));
        mvprintw(2, 5, "YOU FOUND A DAMAGE SPELL");
        refresh();
        attroff(A_BOLD | COLOR_PAIR(9));
        break;
    }
}


void select_spell(int screen_width, game* game_info){
    char *spell1 = "❤️";
    char *spell2 = "⚡️";
    char *spell3 = "🔥";
    int x = screen_width - 5;
    int state = 0;

    attron(A_BOLD | COLOR_PAIR(9));

    mvprintw(2, x - 34, "NUMBER  DESCRIPTION");
    mvaddstr(3, x - 39 , spell1);
    mvprintw(3, x - 36, ": %d ", (*game_info).spell[1]);
    mvaddstr(4, x - 39 , spell2);
    mvprintw(4, x - 36, ": %d ", (*game_info).spell[2]);
    mvaddstr(5, x - 39 , spell3);
    mvprintw(5, x - 36, ": %d ", (*game_info).spell[3]);
    mvprintw(3, x - 26, "DOUBLE REGENERATION");
    mvprintw(4, x - 26, "DOUBLE SPEED");
    mvprintw(5, x - 26, "DOUBLE STRENGTH");

    attroff(A_BOLD | COLOR_PAIR(9));
    
    while(1){
        int c = getch();
        switch(c){
            case '1' : 
            if((*game_info).spell[1] >= 1){
                (*game_info).spell[1]--;
                attron(A_BOLD | COLOR_PAIR(12));
                mvprintw(2, 5, "YOU EQUIPPED A HEALTH SPELL");
                refresh();
                attroff(A_BOLD | COLOR_PAIR(12));
                state = 1;
            }

            else{
                attron(A_BOLD | COLOR_PAIR(13));
                mvprintw(2, 5, "YOU DON'T HAVE ANY HEALTH SPELL");
                refresh();
                attroff(A_BOLD | COLOR_PAIR(13));
            }
            break;

            case '2' :
            if((*game_info).spell[2] >= 1){
                (*game_info).spell[2]--;
                attron(A_BOLD | COLOR_PAIR(12));
                mvprintw(2, 5, "YOU EQUIPPED A SPEED SPELL");
                refresh();
                attroff(A_BOLD | COLOR_PAIR(12));
                state = 1;
            }

            else{
                attron(A_BOLD | COLOR_PAIR(13));
                mvprintw(2, 5, "YOU DON'T HAVE ANY SPEED SPELL");
                refresh();
                attroff(A_BOLD | COLOR_PAIR(13));
            }
            break;

            case '3' :
            if((*game_info).spell[3] >= 1){
                (*game_info).spell[3]--;
                attron(A_BOLD | COLOR_PAIR(12));
                mvprintw(2, 5, "YOU EQUIPPED A DAMAGE SPELL");
                refresh();
                attroff(A_BOLD | COLOR_PAIR(12));
                state = 1;
            }

            else{
                attron(A_BOLD | COLOR_PAIR(13));
                mvprintw(2, 5, "YOU DON'T HAVE ANY DAMAGE SPELL");
                refresh();
                attroff(A_BOLD | COLOR_PAIR(13));
            }
            break;

            case ' ' : 
            state = 1;
            break;
        }

        if(state){
            for(int i=2; i<=5; i++){
                for(int j=x - 39; j<=screen_width; j++){
                    mvprintw(i, j, " ");
                }
            }
            return;
        }
    }
}


void enemy_check(char** map, room_info* rooms_info, game* game_info, int x, int y, int screen_height){
    if((map[y+1][x]=='D') || (map[y+1][x]=='F') || (map[y+1][x]=='G') || (map[y+1][x]=='S') || (map[y+1][x]=='U')){
        enemy_action(rooms_info, game_info, map, x, y+1, screen_height);
    }

    else if((map[y][x+1]=='D') || (map[y][x+1]=='F') || (map[y][x+1]=='G') || (map[y][x+1]=='S') || (map[y][x+1]=='U')){
        enemy_action(rooms_info, game_info, map, x+1, y, screen_height);
    }

    else if((map[y-1][x]=='D') || (map[y-1][x]=='F') || (map[y-1][x]=='G') || (map[y-1][x]=='S') || (map[y-1][x]=='U')){
        enemy_action(rooms_info, game_info, map, x, y-1, screen_height);
    }

    else if((map[y][x-1]=='D') || (map[y][x-1]=='F') || (map[y][x-1]=='G') || (map[y][x-1]=='S') || (map[y][x-1]=='U')){
        enemy_action(rooms_info, game_info, map, x-1, y, screen_height);
    }
}


void enemy_action(room_info* rooms_info, game* game_info, char** map, int x, int y, int screen_height){
    int enemy;

    switch(map[y][x]){
        case 'D' :
        enemy = 1;
        break;

        case 'F' :
        enemy = 2;
        break;

        case 'G' :
        enemy = 3;
        break;

        case 'S' :
        enemy = 4;
        break;

        case 'U' :
        enemy = 5;
        break;
    }

    switch(map[y][x]){
        case 'D' :
        (*game_info).health -= 1;
        attron(A_BOLD | COLOR_PAIR(1));
        mvprintw(2, 5, "ENEMY LANDED A HIT ON YOU");
        refresh();
        attroff(A_BOLD | COLOR_PAIR(1));
        break;

        case 'F' :
        (*game_info).health -= 2;
        attron(A_BOLD | COLOR_PAIR(1));
        mvprintw(2, 5, "ENEMY LANDED A HIT ON YOU");
        refresh();
        attroff(A_BOLD | COLOR_PAIR(1));
        break;

        case 'G' :
        (*game_info).health -= 3;
        attron(A_BOLD | COLOR_PAIR(1));
        mvprintw(2, 5, "ENEMY LANDED A HIT ON YOU");
        refresh();
        attroff(A_BOLD | COLOR_PAIR(1));
        break;

        case 'S' :
        (*game_info).health -= 3;
        attron(A_BOLD | COLOR_PAIR(1));
        mvprintw(2, 5, "ENEMY LANDED A HIT ON YOU");
        refresh();
        attroff(A_BOLD | COLOR_PAIR(1));
        break;

        case 'U' :
        (*game_info).health -= 4;
        attron(A_BOLD | COLOR_PAIR(1));
        mvprintw(2, 5, "ENEMY LANDED A HIT ON YOU");
        refresh();
        attroff(A_BOLD | COLOR_PAIR(1));
        break;
    }

    game_status_print(screen_height, *game_info);
    refresh();
    
    int c = getch();
    delete_message();
    if(c == ' '){
        switch((*game_info).weapon){
            case 1 :
            (*game_info).enemy_health[enemy] -= 5;
            damage_spell(game_info, enemy, 5);
            attron(A_BOLD | COLOR_PAIR(4));
            mvprintw(2, 5, "YOU HIT THE ENEMY");
            refresh();
            attroff(A_BOLD | COLOR_PAIR(4));
            break;

            case 2 :
            (*game_info).enemy_health[enemy] -= 12;
            damage_spell(game_info, enemy, 12);
            attron(A_BOLD | COLOR_PAIR(4));
            mvprintw(2, 5, "YOU HIT THE ENEMY");
            refresh();
            attroff(A_BOLD | COLOR_PAIR(4));
            break;

            case 3 :
            (*game_info).enemy_health[enemy] -= 15;
            damage_spell(game_info, enemy, 15);
            attron(A_BOLD | COLOR_PAIR(4));
            mvprintw(2, 5, "YOU HIT THE ENEMY");
            refresh();
            attroff(A_BOLD | COLOR_PAIR(4));
            break;

            case 4 :
            (*game_info).enemy_health[enemy] -= 5;
            damage_spell(game_info, enemy, 5);
            attron(A_BOLD | COLOR_PAIR(4));
            mvprintw(2, 5, "YOU HIT THE ENEMY");
            refresh();
            attroff(A_BOLD | COLOR_PAIR(4));
            break;

            case 5 :
            (*game_info).enemy_health[enemy] -= 10;
            damage_spell(game_info, enemy, 10);
            attron(A_BOLD | COLOR_PAIR(4));
            mvprintw(2, 5, "YOU HIT THE ENEMY");
            refresh();
            attroff(A_BOLD | COLOR_PAIR(4));
            break;
        }

        if((*game_info).enemy_health[enemy] <= 0){
            map[y][x] = '.';
            attron(A_BOLD | COLOR_PAIR(9));
            mvprintw(2, 5, "YOU DEFEETED THE ENEMY");
            refresh();
            attroff(A_BOLD | COLOR_PAIR(9));
            mvprintw(y, x, ".");
            refresh();

            switch(enemy){
                case 1 :
                (*game_info).score += 50;
                break;

                case 2 :
                (*game_info).score += 100;
                break;

                case 3 :
                (*game_info).score += 150;
                break;

                case 4 :
                (*game_info).score += 200;
                break;

                case 5 :
                (*game_info).score += 250;
                break;
            }
            game_status_print(screen_height, *game_info);
            refresh();
        }
    }
}


void damage_spell(game* game_info, int enemy, int damage){
    if((*game_info).spell_state[3]){
        (*game_info).enemy_health[enemy] -= damage;
    }
}


int no_health_death(game game_info, int screen_height, int screen_width){
    if(game_info.health == 0){
        clear();
        refresh();
        int x = screen_width / 2 - 24;
        int y = 5;
        char *lost_art[] = {
        " __   _____  _   _   ____ ___ _____ ____  ",
        " \\ \\ / / _ \\| | | | |  _ \\_ _| ____|  _ \\ ",
        "  \\ V / | | | | | | | | | | ||  _| | | | |",
        "   | || |_| | |_| | | |_| | || |___| |_| |",
        "   |_| \\___/ \\___/  |____/___|_____|____/ " 
        };
        
        attron(A_BOLD | COLOR_PAIR(1));
        for(int i=0; i<5; i++){
            mvprintw(y+i, x, "%s", lost_art[i]);
        }
        refresh();
        attroff(A_BOLD | COLOR_PAIR(1));

        attron(A_BOLD | COLOR_PAIR(9));
        mvprintw(y+8, screen_width / 2 - 20, "YOU MANAGED TO GET THE SCORE OF  :  %d", game_info.score);
        attroff(A_BOLD | COLOR_PAIR(9));
        refresh();

        getch();
        clear();
        refresh();
        
        FILE* score = fopen("score.txt", "w");
        fprintf(score, "%d %d %d", game_info.score, game_info.gold, game_info.exprience);
        fclose(score);

        return 1;
    }

    return 0;
}


int win_game(game game_info, int screen_height, int screen_width){
    clear();
    refresh();
    int x = screen_width / 2 - 36;
    int y = 3;
    char *lost_art[] = {
    " __      __   ______   __    __        __       __   ______   __    __ ",
    "|  \\    /  \\ /      \\ |  \\  |  \\      |  \\  _  |  \\ /      \\ |  \\  |  \\",
    " \\$$\\  /  $$|  $$$$$$\\| $$  | $$      | $$ / \\ | $$|  $$$$$$\\| $$\\ | $$",
    "  \\$$\\/  $$ | $$  | $$| $$  | $$      | $$/  $\\| $$| $$  | $$| $$$\\| $$",
    "   \\$$  $$  | $$  | $$| $$  | $$      | $$  $$$\\ $$| $$  | $$| $$$$\\ $$",
    "    \\$$$$   | $$  | $$| $$  | $$      | $$ $$\\$$\\$$| $$  | $$| $$\\$$ $$",
    "    | $$    | $$__/ $$| $$__/ $$      | $$$$  \\$$$$| $$__/ $$| $$ \\$$$$",
    "    | $$     \\$$    $$ \\$$    $$      | $$$    \\$$$ \\$$    $$| $$  \\$$$",
    "     \\$$      \\$$$$$$   \\$$$$$$        \\$$      \\$$  \\$$$$$$  \\$$   \\$$"
    };

    attron(A_BOLD | COLOR_PAIR(4));
        for(int i=0; i<9; i++){
            mvprintw(y+i, x, "%s", lost_art[i]);
        }
        refresh();
        attroff(A_BOLD | COLOR_PAIR(4));

        attron(A_BOLD | COLOR_PAIR(9));
        mvprintw(y+12, screen_width / 2 - 20, "YOU MANAGED TO GET THE SCORE OF  :  %d", game_info.score);
        attroff(A_BOLD | COLOR_PAIR(9));
        refresh();

        getch();
        clear();
        refresh();
        
        game_info.exprience++;
        FILE* score = fopen("score.txt", "w");
        fprintf(score, "%d %d %d", game_info.score, game_info.gold, game_info.exprience);
        fclose(score);

        return 1;
}


//