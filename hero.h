#ifndef HERO_H
#define HERO_H

typedef struct {
    char name[20];
    int scissors;
    int rock;
    int paper;
} Hero;

void select_heroes(Hero team[3]);
void random_heroes(Hero team[3]);
int random_move(Hero *hero);
int player_move(Hero *hero);

#endif // HERO_H
