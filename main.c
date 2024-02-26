#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

// Définition des structures pour le joueur, les monstres et le boss
typedef struct
{
    char name[50];
    int hp;
    int str;
} Player;

typedef struct
{
    char name[50];
    int hp;
    int str;
} Monster;

typedef struct
{
    char name[50];
    int hp;
    int str;
} Boss;

// Fonction pour afficher la barre de vie
void printHPBar(int currentHP, int maxHP)
{
    printf("HP: %d/%d [", currentHP, maxHP);
    int i;
    for (i = 0; i < 10; i++)
    {
        if (i * maxHP / 10 < currentHP)
            printf("<3");
        else
            printf("-");
    }
    printf("]\n");
}

// Fonction pour gerer le combat contre les monstres
void fightMonster(Player *player, Monster *monster)
{
    char choice[10];
    printf("Attack (1) or Heal (2): ");
    fgets(choice, 10, stdin);

    switch (atoi(choice))
    {
    case 1:
        monster->hp -= player->str;
        printf("You deal %d damage to %s!\n", player->str, monster->name);
        break;
    case 2:
        player->hp += player->hp * 0.5;
        printf("You healed yourself!\n");
        break;
    default:
        printf("Invalid choice!\n");
    }
}

// Fonction pour gerer le combat contre le boss
void fightBoss(Player *player, Boss *boss)
{
    char choice[10];
    printf("Attack (1) or Heal (2): ");
    fgets(choice, 10, stdin);

    switch (atoi(choice))
    {
    case 1:
        boss->hp -= player->str;
        printf("You deal %d damage to %s!\n", player->str, boss->name);
        break;
    case 2:
        player->hp += player->hp * 0.5;
        printf("You healed yourself!\n");
        break;
    default:
        printf("Invalid choice!\n");
    }
}
// Fonction pour gerer les degat pris par le joueur
void monsterDamage(Player *player, Monster *monster)
{
    if (player->hp > 0 && monster->hp > 0)
    {
        player->hp -= monster->str;
    }
}
// Fonction pour gerer les degat pris par le joueur
void bossDamage(Player *player, Boss *boss)
{
    if (player->hp > 0 && boss->hp > 0)
    {
        player->hp -= boss->str;
    }
}

int main()
{
    // Initialisation des variables
    srand(time(NULL));
    Player player = {"Link", 100, 20};
    Monster monster = {"Ganon", 50, 10};
    Boss boss = {"Dark Ganon", 100, 30};
    int i;

    // Combat contre les monstres
    for (i = 1; i <= 10;)
    {
        if (monster.hp > 0 && player.hp > 0)
        {
            printf("====== FIGHT %d ======\n", i);
            printf("%s\n", monster.name);
            printHPBar(monster.hp, 50);
            printf("%s\n", player.name);
            printHPBar(player.hp, 100);
            fightMonster(&player, &monster);
            monsterDamage(&player, &monster);

            if (monster.hp <= 0)
            {
                printf("You defeated %s!\n", monster.name);
                monster.hp = 50;
                i++;
            }

            if (player.hp <= 0)
            {
                printf("Game over! You lost against %s\n", monster.name);
                return 0;
            }
        }
    }

    // Combat contre le boss
    printf("====== LAST FIGHT ======\n");
    printf("%s\n", boss.name);
    printHPBar(boss.hp, 100);
    printf("%s\n", player.name);
    printHPBar(player.hp, 100);

    while (boss.hp > 0 && player.hp > 0)
    {
        fightBoss(&player, &boss);
        bossDamage(&player, &boss);

        if (boss.hp <= 0)
        {
            printf("You defeated %s!\n", boss.name);
            break;
        }

        if (player.hp <= 0)
        {
            printf("Game over! You lost against %s\n", boss.name);
            return 0;
        }
    }

    printf("Congratulations! You won!\n");

    return 0;
}
