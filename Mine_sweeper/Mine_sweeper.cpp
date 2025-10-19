# include <stdio.h>
#include <iostream>
#include <cmath>
#include <unordered_map>


struct coord{
    int x_pos;
    int y_pos;
};

coord add_pos(coord p1, coord p2);
coord operator+(coord p1,coord p2);
int main(){

    return 0;
}


coord add_pos(coord p1,coord p2){
    p1.x_pos= p1.x_pos+p2.x_pos;
    p1.y_pos= p1.x_pos+p2.x_pos;
    return p1;
}

coord operator+(coord p1,coord p2){
    return add_pos(p1,p2);
}