#ifndef game_world_h
#define game_world_h

#include <vector>
#include <string>

#include <SDL.h>
#include <SDL_mixer.h>

const std::string CIPHER_IMAGE_INPUT="cipher_input";
const std::string CIPHER_IMAGE_OUTPUT="cipher_output";

const std::string CIPHER_SOUND_INPUT="cipher_input";
const std::string CIPHER_SOUND_OUTPUT="cipher_output";

class Game_World{
private:

    std::string input_text;
    std::string output_text;

    SDL_Surface* input_image;
    SDL_Surface* output_image;

    Mix_Chunk* input_sound;
    Mix_Chunk* output_sound;

public:

    std::vector<std::string> seeds;

    Game_World();

    void clear_world();
    void generate_world();

    std::string get_seed_string();
    void set_seeds(const std::string& seed_string);
    void save_seeds();
    void load_seeds();

    std::string get_input_text();
    std::string get_output_text();
    void set_input_text(const std::string& text);
    void set_output_text(const std::string& text);
    void swap_input_output_text();

    SDL_Surface* get_input_image();
    SDL_Surface* get_output_image();
    //Returns true if the image is loaded successfully
    //Returns false if the image cannot be loaded
    bool set_input_image(std::string image_location);
    void set_output_image(SDL_Surface* surface);
    void swap_input_output_image();
    void update_image_input();
    void update_image_output();

    Mix_Chunk* get_input_sound();
    Mix_Chunk* get_output_sound();
    bool set_input_sound(std::string sound_location);
    void set_output_sound(Mix_Chunk* chunk);
    void swap_input_output_sound();
    void update_sound_input();
    void update_sound_output();

    void update_window_seeds();
    void update_window_cipher_text();
    void update_window_cipher_image();

    void tick();
    void ai();
    void movement();
    void events();
    void animate();
    void render();

    void update_background();
    void render_background();
};

#endif
