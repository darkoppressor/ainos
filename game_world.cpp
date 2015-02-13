#include "game_world.h"
#include "world.h"
#include "render.h"

using namespace std;

Game_World::Game_World(){
    clear_world();
}

void Game_World::clear_world(){
    ///example_objects.clear();

    input_text="";
    output_text="";

    input_image=0;
    output_image=0;

    input_sound=0;
    output_sound=0;
}

void Game_World::generate_world(){
    clear_world();
}

string Game_World::get_seed_string(){
    string seed_string="";

    for(size_t i=0;i<seeds.size();i++){
        seed_string+=seeds[i];

        if(i<seeds.size()-1){
            seed_string+="\n";
        }
    }

    return seed_string;
}

void Game_World::set_seeds(const string& seed_string){
    seeds.clear();

    istringstream data;
    data.str(seed_string.c_str());

    while(!data.eof()){
        string line="";

        getline(data,line);

        seeds.push_back(line);
    }

    update_window_seeds();
}

void Game_World::save_seeds(){
    stringstream save("");

    for(size_t i=0;i<seeds.size();i++){
        save<<seeds[i];

        if(i<seeds.size()-1){
            save<<"\n";
        }
    }

    file_io.save_important_file(engine_interface.get_save_directory()+"seeds.txt",save.str());
}

void Game_World::load_seeds(){
    File_IO_Load load(engine_interface.get_save_directory()+"seeds.txt");

    if(load.file_loaded()){
        set_seeds(load.get_data());
    }
}

string Game_World::get_input_text(){
    return input_text;
}

string Game_World::get_output_text(){
    return output_text;
}

void Game_World::set_input_text(const string& text){
    input_text=text;

    for(size_t i=0;i<input_text.length();){
        if(input_text[i]!='\n' && (input_text[i]<' ' || input_text[i]>'~')){
            input_text.erase(input_text.begin()+i);
        }
        else{
            i++;
        }
    }

    update_window_cipher_text();
}

void Game_World::set_output_text(const string& text){
    output_text=text;

    update_window_cipher_text();
}

void Game_World::swap_input_output_text(){
    swap(input_text,output_text);

    update_window_cipher_text();
}

SDL_Surface* Game_World::get_input_image(){
    return input_image;
}

SDL_Surface* Game_World::get_output_image(){
    return output_image;
}

bool Game_World::set_input_image(string image_location){
    if(input_image!=0){
        SDL_FreeSurface(input_image);
    }

    input_image=load_image(image_location);

    update_image_input();

    update_window_cipher_image();

    if(input_image!=0){
        return true;
    }
    else{
        return false;
    }
}

void Game_World::set_output_image(SDL_Surface* surface){
    if(output_image!=0){
        SDL_FreeSurface(output_image);
    }

    output_image=surface;

    update_image_output();

    update_window_cipher_image();
}

void Game_World::swap_input_output_image(){
    swap(input_image,output_image);

    update_image_input();
    update_image_output();

    update_window_cipher_image();
}

void Game_World::update_image_input(){
    image.remove_image(CIPHER_IMAGE_INPUT);

    if(input_image!=0){
        double max_width=1267.0;
        double max_height=288.0;

        double width=input_image->w;
        double height=input_image->h;

        double width_delta=1.0;
        double height_delta=1.0;

        if(width>height){
            width_delta=width/height;
        }
        else{
            height_delta=height/width;
        }

        while(width>max_width || height>max_height){
            width-=width_delta;
            height-=height_delta;
        }

        double scale_x=width/(double)input_image->w;
        double scale_y=height/(double)input_image->h;

        if(scale_x<1.0 || scale_y<1.0){
            SDL_Surface* scaled=scale_surface(input_image,scale_x,scale_y);

            image.add_image(CIPHER_IMAGE_INPUT,scaled);

            SDL_FreeSurface(scaled);
        }
        else{
            image.add_image(CIPHER_IMAGE_INPUT,input_image);
        }
    }
}

void Game_World::update_image_output(){
    image.remove_image(CIPHER_IMAGE_OUTPUT);

    if(output_image!=0){
        double max_width=1267.0;
        double max_height=276.0;

        double width=output_image->w;
        double height=output_image->h;

        double width_delta=1.0;
        double height_delta=1.0;

        if(width>height){
            width_delta=width/height;
        }
        else{
            height_delta=height/width;
        }

        while(width>max_width || height>max_height){
            width-=width_delta;
            height-=height_delta;
        }

        double scale_x=width/(double)output_image->w;
        double scale_y=height/(double)output_image->h;

        if(scale_x<1.0 || scale_y<1.0){
            SDL_Surface* scaled=scale_surface(output_image,scale_x,scale_y);

            image.add_image(CIPHER_IMAGE_OUTPUT,scaled);

            SDL_FreeSurface(scaled);
        }
        else{
            image.add_image(CIPHER_IMAGE_OUTPUT,output_image);
        }
    }
}

Mix_Chunk* Game_World::get_input_sound(){
    return input_sound;
}

Mix_Chunk* Game_World::get_output_sound(){
    return output_sound;
}

bool Game_World::set_input_sound(string sound_location){
    if(input_sound!=0){
        Mix_FreeChunk(input_sound);
    }

    input_sound=Mix_LoadWAV(sound_location.c_str());

    update_sound_input();

    if(input_sound!=0){
        return true;
    }
    else{
        return false;
    }
}

void Game_World::set_output_sound(Mix_Chunk* chunk){
    if(output_sound!=0){
        Mix_FreeChunk(output_sound);
    }

    output_sound=chunk;

    update_sound_output();
}

void Game_World::swap_input_output_sound(){
    swap(input_sound,output_sound);

    update_sound_input();
    update_sound_output();
}

void Game_World::update_sound_input(){
    sound_system.stop_sounds();

    sound_system.remove_sound(CIPHER_SOUND_INPUT);

    if(input_sound!=0){
        sound_system.add_sound(CIPHER_SOUND_INPUT,input_sound);
    }
}

void Game_World::update_sound_output(){
    sound_system.stop_sounds();

    sound_system.remove_sound(CIPHER_SOUND_OUTPUT);

    if(output_sound!=0){
        sound_system.add_sound(CIPHER_SOUND_OUTPUT,output_sound);
    }
}

void Game_World::update_window_seeds(){
    Window* window=engine_interface.get_window("edit_seeds");

    window->set_info_text(0,get_seed_string());
}

void Game_World::update_window_cipher_text(){
    Window* window=engine_interface.get_window("cipher_text");

    window->set_info_text(0,input_text);
    window->set_info_text(1,output_text);
}

void Game_World::update_window_cipher_image(){
    Window* window=engine_interface.get_window("cipher_image");

    if(input_image==0){
        window->informations[1].set_sprite("");
    }
    else{
        window->informations[1].set_sprite(CIPHER_IMAGE_INPUT);
    }

    if(output_image==0){
        window->informations[3].set_sprite("");
    }
    else{
        window->informations[3].set_sprite(CIPHER_IMAGE_OUTPUT);
    }
}

void Game_World::tick(){
}

void Game_World::ai(){
}

void Game_World::movement(){
}

void Game_World::events(){
}

void Game_World::animate(){
}

void Game_World::render(){
}

void Game_World::update_background(){
}

void Game_World::render_background(){
    render_rectangle(0,0,main_window.SCREEN_WIDTH,main_window.SCREEN_HEIGHT,1.0,"ui_black");
}
