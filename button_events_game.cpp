#include "button_events.h"
#include "world.h"
#include "cipher.h"

#include <boost/algorithm/string.hpp>

#include <SDL.h>
#include <SDL_image.h>

using namespace std;

bool Button_Events::handle_button_event_game(string button_event,Window* parent_window,bool& window_opened_on_top){
    if(button_event=="window_edit_seeds"){
        game.world.update_window_seeds();

        Window* window=engine_interface.get_window("edit_seeds");
        window->toggle_on(true,true);
        window_opened_on_top=true;

        return true;
    }

    else if(button_event=="edit_seeds"){
        if(parent_window!=0){
            game.world.set_seeds(parent_window->get_info_text(0));

            game.world.save_seeds();

            parent_window->toggle_on(true,false);
        }

        return true;
    }

    else if(button_event=="cipher_text_clear_input"){
        game.world.set_input_text("");

        return true;
    }

    else if(button_event=="cipher_text_swap"){
        game.world.swap_input_output_text();

        return true;
    }

    else if(button_event=="encipher_text"){
        if(parent_window!=0){
            game.world.set_input_text(parent_window->get_info_text(0));

            Cipher cipher(game.world.seeds);

            game.world.set_output_text(cipher.encipher_copy(game.world.get_input_text()));
        }

        return true;
    }
    else if(button_event=="decipher_text"){
        if(parent_window!=0){
            game.world.set_input_text(parent_window->get_info_text(0));

            Cipher cipher(game.world.seeds);

            game.world.set_output_text(cipher.decipher_copy(game.world.get_input_text()));
        }

        return true;
    }

    else if(button_event=="cipher_text_to_clipboard"){
        SDL_SetClipboardText(game.world.get_output_text().c_str());

        return true;
    }

    else if(button_event=="cipher_text_save_file"){
        if(parent_window!=0){
            file_io.save_important_file(engine_interface.get_save_directory()+parent_window->get_info_text(0)+".txt",game.world.get_output_text());

            parent_window->toggle_on(true,false);
        }

        return true;
    }

    else if(button_event=="cipher_image_swap"){
        game.world.swap_input_output_image();

        return true;
    }

    else if(button_event=="encipher_image"){
        if(game.world.get_input_image()!=0){
            Cipher cipher(game.world.seeds);

            SDL_Surface* output=SDL_ConvertSurface(game.world.get_input_image(),game.world.get_input_image()->format,0);

            cipher.encipher(output);

            game.world.set_output_image(output);
        }

        return true;
    }
    else if(button_event=="decipher_image"){
        if(game.world.get_input_image()!=0){
            Cipher cipher(game.world.seeds);

            SDL_Surface* output=SDL_ConvertSurface(game.world.get_input_image(),game.world.get_input_image()->format,0);

            cipher.decipher(output);

            game.world.set_output_image(output);
        }

        return true;
    }

    else if(button_event=="cipher_image_save_file"){
        if(parent_window!=0){
            if(game.world.get_input_image()!=0){
                string path=engine_interface.get_save_directory()+parent_window->get_info_text(0)+".png";
                IMG_SavePNG(game.world.get_output_image(),path.c_str());
            }

            parent_window->toggle_on(true,false);
        }

        return true;
    }

    else if(button_event=="cipher_sound_input"){
        sound_system.play_sound(CIPHER_SOUND_INPUT);

        return true;
    }

    else if(button_event=="cipher_sound_output"){
        sound_system.play_sound(CIPHER_SOUND_OUTPUT);

        return true;
    }

    else if(button_event=="cipher_sound_swap"){
        game.world.swap_input_output_sound();

        return true;
    }

    else if(button_event=="encipher_sound"){
        if(game.world.get_input_sound()!=0){
            Cipher cipher(game.world.seeds);

            Mix_Chunk* output=Mix_QuickLoad_RAW(game.world.get_input_sound()->abuf,game.world.get_input_sound()->alen);

            cipher.encipher(output);

            game.world.set_output_sound(output);
        }

        return true;
    }
    else if(button_event=="decipher_sound"){
        if(game.world.get_input_sound()!=0){
            Cipher cipher(game.world.seeds);

            Mix_Chunk* output=Mix_QuickLoad_RAW(game.world.get_input_sound()->abuf,game.world.get_input_sound()->alen);

            cipher.decipher(output);

            game.world.set_output_sound(output);
        }

        return true;
    }

    else if(button_event=="cipher_sound_save_file"){
        if(parent_window!=0){
            if(game.world.get_input_sound()!=0){
                string path=engine_interface.get_save_directory()+parent_window->get_info_text(0)+".wav";
                ///IMG_SavePNG(game.world.get_output_image(),path.c_str());
            }

            parent_window->toggle_on(true,false);
        }

        return true;
    }

    return false;
}
