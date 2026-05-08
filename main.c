#include "game.h"
#include <stdio.h>
#include <conio.h>

int main()
{
    int app_running = 1;
    while (app_running)
    {
        printf("\033[?25l\033[H\033[J");
        printf("\n\t\033[1;32m==============================\033[0m\n");
        printf("\t\033[1;32m       SNAKE TERMINAL         \033[0m\n");
        printf("\t\033[1;32m==============================\033[0m\n\n");

        printf("\t[1] \033[1;36mNoob\033[0m (Slow)\n");
        printf("\t[2] \033[1;33mHacker\033[0m (Normal)\n");
        printf("\t[3] \033[1;31mGod Mode\033[0m (Fast)\n");
        printf("\t[ESC] Exit\n\n");
        printf("\tChoose your difficult: ");

        int choice = _getch();
        int base_delay = 80;

        if (choice == 27)
        {
            app_running = 0;
            break;
        }

        else if (choice == '1')
            base_delay = 120;
        else if (choice == '2')
            base_delay = 70;
        else if (choice == '3')
            base_delay = 35;
        else
            continue;

        while (1)
        {
            run_game(base_delay);
            printf("\n\t\033[1;37mRetry? (Y/N):\033[0m ");
            int replay = _getch();
            if (replay == 'y' || replay == 'Y')
            {
                continue;
            }
            else
            {
                break;
            }
        }
    }
    printf("\033[?25h\033[H\033[J");
    return 0;
}