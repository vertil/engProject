#pragma once
#include "structs.hxx"
#include <vector>
#include <cstdint>
#include <iostream>

class animation{
    //vector of all sprites
    std::vector<sprite> sprites;

    //for render
    uint8_t position=0;
    bool active=false;

    //number of opengl texture
    uint8_t texture_number=1;

    //buff
    sprite buff;

    Uint32 current=0;
    int speed=1;


public:
    animation(uint8_t texture_number_in, uint8_t amount_in,uint8_t repeat){

        //---init
        texture_number=texture_number_in;
        //sprites.reserve(amount_in*repeat);

        //first sprite
        buff.triag_1.v[0].tex_x=0.0f;
        buff.triag_1.v[0].tex_y=1.0f;

        buff.triag_1.v[1].tex_x=0.0f;
        buff.triag_1.v[1].tex_y=0.0f;

        buff.triag_1.v[2].tex_x=1.0f/amount_in;
        buff.triag_1.v[2].tex_y=1.0f;

        //----
        buff.triag_2.v[0].tex_x=0.0f;
        buff.triag_2.v[0].tex_y=0.0f;

        buff.triag_2.v[1].tex_x=1.0f/amount_in;
        buff.triag_2.v[1].tex_y=0.0f;

        buff.triag_2.v[2].tex_x=1.0f/amount_in;
        buff.triag_2.v[2].tex_y=1.0f;

        //repeating
        for(int i=0;i<repeat;i++){
            sprites.push_back(buff);
        }
        //next sprites
        for(int i=1;i<(amount_in);i++){
           //---
           buff.triag_1.v[0].tex_x+=1.0/amount_in;

           buff.triag_1.v[1].tex_x+=1.0/amount_in;

           buff.triag_1.v[2].tex_x+=1.0/amount_in;
           //---
           buff.triag_2.v[0].tex_x+=1.0/amount_in;

           buff.triag_2.v[1].tex_x+=1.0/amount_in;

           buff.triag_2.v[2].tex_x+=1.0/amount_in;
           //repeating
           for(int i=0;i<repeat;i++){
               sprites.push_back(buff);
           }

        }

    }
    void info(){
        std::cout<<sprites.size()<<" sprite size"<<std::endl;
        std::cout<< std::to_string(texture_number)<<" texture_number"<<std::endl;

    }
    void setPlace(const triangle& place1,const triangle& place2){
        for(auto& i:sprites){
            //triag1
            //1
            i.triag_1.v[0].x+=place1.v[0].x;
            i.triag_1.v[0].y=place1.v[0].y;


            //2
            i.triag_1.v[1].x=place1.v[1].x;
            i.triag_1.v[1].y=place1.v[1].y;
            //3
            i.triag_1.v[2].x=place1.v[2].x;
            i.triag_1.v[2].y=place1.v[2].y;

            //triag2
            //1
            i.triag_2.v[0].x=place2.v[0].x;
            i.triag_2.v[0].y=place2.v[0].y;
            //2
            i.triag_2.v[1].x=place2.v[1].x;
            i.triag_2.v[1].y=place2.v[1].y;
            //3
            i.triag_2.v[2].x=place2.v[2].x;
            i.triag_2.v[2].y=place2.v[2].y;

        }

    }
    void start(){
        //std::cout<<"start animation"<<std::endl;
        active=true;
        position=0;
    }
    bool isactive(){
        return active;
    }
    sprite getframe(){

        if(position+1==sprites.size()){

            if(speed==current){
                position=0;
                current=0;
                return buff;
            }else{
                buff=sprites[position];
                current++;
                return buff;

            }


            //buff=sprites[position];
            //position=0;
            //active=false;
            //return buff;
        }else{

            if(speed==current){
                position++;
                current=0;
                return buff;
            }else{
                buff=sprites[position];
                current++;
                return buff;

            }



            //return buff;
        }

    }
    uint8_t get_tex_num(){
        return texture_number;
    }

    void setSpeed(int& speedIn){
        speed=speedIn;
    }
};

