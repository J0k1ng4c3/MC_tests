# include <stdio.h>
#include <iostream>
#include <cmath>
#include <vector>
//#include <mine_sweeper.h>

struct coord{
    int x_pos;
    int y_pos;
};

//Deklaration von Funktionen:
coord add_pos(coord p1, coord p2);
coord operator+(coord p1,coord p2);
bool same_position(coord p1,coord p2);

void print_coord(coord p1);
uint determine_class(coord p1, int max_x,int max_y);
coord update_position(coord p, uint c);

//Main
int main(){
    //std::cout<<"Noch ist nichts relevantes implementiert\n";
    uint c{0};
    uint times_to_run{10000};
    uint times_run{0};
    uint died{0};
    uint steps_per_run{25};
    
    int max_x = 5;//pm 5: Soll ein 10x10 Feld sein
    int max_y = 5;
    coord p_start{
        0,
        0
    };
    coord p = p_start;
    coord mine_0{
        4,
        2
    };
    coord mine_1{
        1,
        -3
    };
    coord mine_2{
        -2,
        -4
    };
    coord mine_3{
        -2,
        3
    };
    std::vector<coord> mines(4,p);
    mines.push_back(mine_0);
    mines.push_back(mine_1);
    mines.push_back(mine_2);
    mines.push_back(mine_3);
    //Die eigentliche Simulation:
    while(times_run <times_to_run){
        uint steps_taken{0};
        p = p_start;
        //25 Schritte pro versuch
        while(steps_taken < steps_per_run){
            print_coord(p);
            std::cout<<"Times run:"<<times_run<<",steps taken:"<<steps_taken<<"\n";
            c=determine_class(p, max_x, max_y);
            p = update_position(p, c);
            if(same_position(mines[0], p)||same_position(mines[1], p)||same_position(mines[2], p)||same_position(mines[3], p)){
                died++;
                break;
            }
            steps_taken++;
        }
        times_run++;
    }
    float death_rate = (float) died/times_run;
    std::cout<<"The walker died "<< died <<"-times.\n";
    std::cout<<"Which means we have an survival posibility of "<< 100*(1-death_rate) <<"%.\n";

    return 0;
}

//Implemenetation von Funktionen:
coord add_pos(coord p1,coord p2){
    p1.x_pos= p1.x_pos+p2.x_pos;
    p1.y_pos= p1.y_pos+p2.y_pos;
    return p1;
}
bool same_position(coord p1,coord p2){
    if(p1.x_pos==p2.x_pos && p1.y_pos==p2.y_pos){
        return true;
    }else{
        return false;
    }
}
//Operators:
coord operator+(coord p1,coord p2){
    return add_pos(p1,p2);
}

void print_coord(coord p1){
    std::cout<<"X-Position: "<<p1.x_pos <<",Y-Position: "<< p1.y_pos<< ".\n";
}

/*Idee abhänig von der Aktuellen position des Walkers wird seine aktuelle Klasse ermittelt:
*/
uint determine_class(coord p1,int max_x,int max_y){
    if(p1.x_pos < max_x && p1.x_pos > -max_x && p1.y_pos < max_y && p1.y_pos > -max_y ){
        return 0;}//Walker ist an keinem Rand
    else if( p1.y_pos == -max_y ){//Wir sind am unteren rand
        if(p1.x_pos == -max_x){//Untere linke Ecke
        return 8;
        }
        else if(p1.x_pos ==max_x){//Untere rechte Ecke
            return 2;
        }else if(p1.x_pos < max_x && p1.x_pos > -max_x){//Unterer Rand
            return 1;
        }else{
            throw std::invalid_argument("We are out of Bounds1");
        }
    }
    else if( p1.y_pos == max_y ){//Wir sind am oberen rand
        if(p1.x_pos == -max_x){//Obere linke Ecke
        return 6;
        }
        else if(p1.x_pos ==max_x){//Obere rechte Ecke
            return 4;
        }else if(p1.x_pos < max_x && p1.x_pos > -max_x){//Oberer Rand
            return 5;
        }else{
            throw std::invalid_argument("We are out of Bounds2");
        }
    }
    else{//Fall Wir sind am rechten oder linken Rand aber in keiner Ecke
        if(p1.x_pos == max_x){
            return 3;
        }else if(p1.x_pos == -max_x){
            return 7;
        }else{
            throw std::invalid_argument("We are out of Bounds3");
        }
    }
}
//Der eigentliche Rnd-Walk
coord update_position(coord p, uint c){
    int rnd_x = rand() %2;
    int rnd_y = rand() %2;
    int rnd_positive_x = rand() %2;//if rnd_positive_x =1 dann sind wir 1 in positive x-Richtung gelaufen.
    rnd_positive_x = (rnd_positive_x ==1) ? 1 : -1;
    int rnd_positive_y = rand() %2;
    rnd_positive_y = (rnd_positive_y ==1) ? 1 : -1;
    coord move{
        rnd_x*rnd_positive_x,
        rnd_y*rnd_positive_y
    };
    switch (c){
        case 0:
        break;                  //negativ positiv
        case 1:
        move.y_pos = (move.y_pos > 0) ? 0: 1;//y darf nicht negativ sein
        break;
        case 2:
        move.x_pos = (move.x_pos > 0) ? -1: 0;
        move.y_pos = (move.y_pos > 0) ? 0: 1;
        break;
        case 3:
        move.x_pos = (move.x_pos > 0) ? -1: 0;
        break;
        case 4:
        move.x_pos = (move.x_pos > 0) ? -1: 0;
        move.y_pos = (move.y_pos > 0) ? -1: 0;
        break;
        case 5:
        move.y_pos = (move.y_pos > 0) ? -1: 0;
        break;
        case 6:
        move.x_pos = (move.x_pos > 0) ? 0: 1;
        move.y_pos = (move.y_pos > 0) ? -1: 0;
        break;
        case 7:
        move.x_pos = (move.x_pos > 0) ? 0: 1;
        break;
        case 8:
        move.x_pos = (move.x_pos > 0) ? 0: 1;
        move.y_pos = (move.y_pos > 0) ? 0: 1;
        break;
        default:
        throw std::invalid_argument("Not a valid Class id.");

    };
    return move+p;
}