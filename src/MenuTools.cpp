#include <iostream>
#include <unordered_set>

#include "MenuTools.h"
#include "Windows/BaseWindow.h"

// MenuToolItem-----------------------------------------------------------


// Constructors / Deconstructors

MenuToolItem::MenuToolItem() 
{
    base_window = nullptr;
    type = VARIABLE;
}

MenuToolItem::MenuToolItem(BaseWindow* _base_window, 
    InputHandler* _input_handler, ItemType _type) 
{
    base_window = _base_window; 
    input_handler = _input_handler;
    type = _type;
}
 
MenuToolItem::~MenuToolItem() {}


// Public Functions

void MenuToolItem::render(Status status, std::string& cursor_color) {}

MenuToolItem::Status MenuToolItem::handle_input() { return NO_STATUS; }


// Private Functions

void MenuToolItem::apply_input_to_string(int key, std::string& targ_str, 
    StringType str_type, bool shift_pressed, bool ctrl_pressed)
{
    std::unordered_set<char> available_chars {'\'', ',', '-', '.', '/', ';', 
        '=', '[', '\\', ']', '~'};

    if(key == SDLK_BACKSPACE)
    {
        input_handler->set_delay(key);

        if(targ_str.size() == 0) return;

        if(ctrl_pressed) 
        {
            if(shift_pressed) 
            {
                targ_str.clear();
                return;
            }

            int i = targ_str.size() - 1;

            while(i > 0)
            {
                if(targ_str.at(i) == ' ')
                {
                    while(i > 0)
                    {
                        if(targ_str.at(i) != ' ')
                        {
                            i++;
                            goto AFTER_LOOP;
                        }

                        i--;
                    }
                }

                i --;
            }

            AFTER_LOOP:

            targ_str = targ_str.substr(0, i);
            return;
        }

        targ_str.pop_back();
        return;
    }

    // Variable type is an integer
    else if(str_type == INT || str_type == FLOAT)
    {
        if(key < 48 || key > 57) return;

        targ_str.push_back(char(key));
        input_handler->set_delay(key);
    }

    else if(key == SDLK_SPACE)
    {
        input_handler->set_delay(key);
        targ_str.push_back(' ');
    }

    else if(key == SDLK_TAB)
    {
        input_handler->set_delay(key);
        targ_str.append("    ");
    }

    else if(key >= 97 && key <= 122)
    {
        input_handler->set_delay(key);

        if(shift_pressed)
        {
            targ_str.push_back(char(key - 32));
            return;
        }

        targ_str.push_back(char(key));
    }

    else if(key >= 48 && key <= 57)
    {
        input_handler->set_delay(key);

        if(shift_pressed)
        {
            switch(key)
            {
                case '0':
                    targ_str.push_back(')');
                    break;
                
                case '1':
                    targ_str.push_back('!');
                    break;

                case '2':
                    targ_str.push_back('@');
                    break;
                
                case '3':
                    targ_str.push_back('#');
                    break;
                
                case '4':
                    targ_str.push_back('$');
                    break;
                
                case '5':
                    targ_str.push_back('%');
                    break;

                case '6':
                    targ_str.push_back('^');
                    break;

                case '7':
                    targ_str.push_back('&');
                    break;
                
                case '8':
                    targ_str.push_back('*');
                    break;

                case '9':
                    targ_str.push_back('(');
                    break;
            }
            return;
        }

        targ_str.push_back(char(key));
    }

    else if(available_chars.count(key) != 0)
    {
        input_handler->set_delay(key);

        if(shift_pressed)
        {
            switch(key)
            {
                case '\'':
                    targ_str.push_back('"');
                    break;

                case ',':
                    targ_str.push_back('<');
                    break;

                case '-':
                    targ_str.push_back('_');
                    break;
                
                case '.':
                    targ_str.push_back('>');
                    break;

                case '/':
                    targ_str.push_back('?');
                    break;

                case ';':
                    targ_str.push_back(':');
                    break;
                
                case '=':
                    targ_str.push_back('+');
                    break;

                case '[':
                    targ_str.push_back('{');
                    break;
                
                case '\\':
                    targ_str.push_back('|');
                    break;

                case ']':
                    targ_str.push_back('}');
                    break;
            }
            return;
        }
    
        targ_str.push_back(char(key));
    }
}


// MenuToolText ---------------------------------------------------------------

// Constructors / Deconstructor

MenuToolText::MenuToolText() : MenuToolItem() {}

MenuToolText::MenuToolText(BaseWindow* _base_window, 
    InputHandler* _input_handler, std::string _content) :
    MenuToolItem(_base_window, _input_handler, TEXT)
{
    content = _content;
}

MenuToolText::~MenuToolText() {}


// Public Functions

void MenuToolText::render(Status status, std::string& cursor_color)
{
    for(int i = 0; i < indent_num; i++)
    {
        base_window->add_ch(' ');
    
    }

    switch(status)
    {
        case NO_STATUS:

            base_window->add_str("   ");
            base_window->add_str(content);
            base_window->add_new_line();
            break;

        case HOVERED:

            base_window->add_ch(' ');
            base_window->add_ch(cursor_icon, cursor_color);
            base_window->add_ch(' ');
            base_window->add_str(content);
            base_window->add_new_line();
            break;

        case SELECTED:

            base_window->add_str("  ");
            base_window->add_ch(cursor_icon, cursor_color);
            base_window->add_ch(' ');
            base_window->add_str(content, cursor_color);
            base_window->add_ch('_', cursor_color);
            base_window->add_new_line();
            break;
    }
}

MenuToolItem::Status MenuToolText::handle_input()
{
    Status status = SELECTED;

    std::vector<Key*> keys = input_handler->get_active_keys();

    bool shift_key_pressed = false;

    bool ctrl_key_pressed = false;

    for(Key* key : keys)
    {
        if(key->id == SDLK_RETURN)
        {
            input_handler->set_delay(key->id, -1);
            status = HOVERED;
        }

        else if(key->id == SDLK_LSHIFT || key->id == SDLK_RSHIFT)
        {
            shift_key_pressed = true;
        }

        else if(key->id == SDLK_LCTRL || key->id == SDLK_RCTRL)
        {
            ctrl_key_pressed = true;
        }

        else 
        {
            apply_input_to_string(key->id, content, STRING, 
                shift_key_pressed, ctrl_key_pressed);
        }
    }

    return status;

}


// MenuToolVariable -----------------------------------------------------------

// Constructors / Deconstructor

MenuToolVariable::MenuToolVariable() : MenuToolItem() {}

MenuToolVariable::MenuToolVariable(BaseWindow* _base_window, 
    InputHandler* _input_handler, StringType _str_type, 
    std::string _name, std::string _content) :
    MenuToolItem(_base_window, _input_handler, VARIABLE)
{
    name = _name;
    str_type = _str_type;
    content = _content;
}

MenuToolVariable::~MenuToolVariable() {}


// Public Functions

void MenuToolVariable::render(Status status, std::string& cursor_color)
{
    for(int i = 0; i < indent_num; i++)
    {
        base_window->add_ch(' ');
    }

    switch(status)
    {
        case NO_STATUS:
            
            base_window->add_str("   ");
            base_window->add_str(name);
            base_window->add_ch(':');
            base_window->add_ch(' ');
            base_window->add_str(content);
            base_window->add_new_line();             
            break;
        
        case HOVERED:
            
            base_window->add_ch(' ');
            base_window->add_ch(cursor_icon, cursor_color);
            base_window->add_ch(' ');
            base_window->add_str(name);
            base_window->add_ch(':');
            base_window->add_ch(' ');
            base_window->add_str(content);
            base_window->add_new_line();
            break;

        case SELECTED:  

            base_window->add_str("  ");
            base_window->add_ch(cursor_icon, cursor_color);
            base_window->add_ch(' ');
            base_window->add_str(name);
            base_window->add_ch(':');
            base_window->add_ch(' ');
            base_window->add_str(content, cursor_color);
            base_window->add_ch('_', cursor_color);
            base_window->add_new_line();
            break;
    }
}

MenuToolItem::Status MenuToolVariable::handle_input() 
{

    Status status = SELECTED;

    std::vector<Key> keys = input_handler->get_raw_keys();

    bool shift_key_pressed = false;

    bool ctrl_key_pressed = false;

    for(Key key : keys)
    {
        if(key.id == SDLK_RETURN)
        {
            input_handler->set_delay(key.id, -1);
            status = HOVERED;
        }

        else if(key.id == SDLK_LSHIFT || key.id == SDLK_RSHIFT)
        {
            shift_key_pressed = true;
        }

        else if(key.id == SDLK_LCTRL || key.id == SDLK_RCTRL)
        {
            ctrl_key_pressed = true;
        }

        else if(str_type == FLOAT)
        {
            if(key.id == SDLK_PERIOD && !has_decimal && content.size() > 0)
            {
                has_decimal = true;
                content.push_back('.');
                // input_handler->set_delay('.');
                continue;
            }

            else if(key.id == SDLK_BACKSPACE && content.size() > 0)
            {
                // input_handler->set_delay(SDLK_BACKSPACE);

                if(ctrl_key_pressed)
                {
                    if(shift_key_pressed)
                    {
                        content.clear();
                        has_decimal = false;
                        continue;
                    }

                    if(content.at(content.size() - 1) == '.')
                    {
                        has_decimal = false;
                    }

                    content.pop_back();

                    int i = content.size() - 1;

                    while(i >= 0)
                    {
                        if(content.at(i) == '.')
                        {
                            break;
                        }

                        content.pop_back();
                        i--;
                    }

                    continue;
                }

                if(content.at(content.size() - 1) == '.')
                {
                    content.pop_back();
                    has_decimal = false;
                    input_handler->set_delay(SDLK_BACKSPACE);
                    continue;
                }
            }

            apply_input_to_string(key.id, content, str_type, 
                shift_key_pressed, ctrl_key_pressed);
        }

        else 
        {
            apply_input_to_string(key.id, content, str_type, 
                shift_key_pressed, ctrl_key_pressed);
        }
    }
    
    return status;
}


// MenuToolChoice -------------------------------------------------------------

// Constructors / Deconstructor

MenuToolChoice::MenuToolChoice() : MenuToolItem() {}

MenuToolChoice::MenuToolChoice(BaseWindow* base_window, 
    InputHandler* _input_handler, std::string _name,
    std::vector<Text>& _content, int _cursor_index) : 
    MenuToolItem(base_window, _input_handler, CHOICE)
{
    name = _name;
    content = _content;
    cursor_index = _cursor_index;
    selected_index = _cursor_index;
}

MenuToolChoice::~MenuToolChoice() {}


// Public Functions

void MenuToolChoice::render(Status status, std::string& cursor_color)
{
    for(int i = 0; i < indent_num; i++)
    {
        base_window->add_ch(' ');
    
    }

    switch(status)
    {
        case NO_STATUS:
            
            base_window->add_str("   ");
            base_window->add_str(name);
            base_window->add_ch(':');
            base_window->add_ch(' ');
            base_window->add_str(content.at(selected_index).content, 
                content.at(selected_index).color);
            base_window->add_new_line();
            break;

        case HOVERED:
            
            base_window->add_ch(' ');
            base_window->add_ch(cursor_icon, cursor_color);
            base_window->add_ch(' ');
            base_window->add_str(name);
            base_window->add_ch(':');
            base_window->add_ch(' ');
            base_window->add_str(content.at(selected_index).content, 
                content.at(selected_index).color);
            base_window->add_new_line();
            break;

        case SELECTED:

            base_window->add_str("   ");
            base_window->add_str(name, cursor_color);
            base_window->add_ch(':');
            base_window->add_new_line();

            for(int i = 0; i < content.size(); i++)
            {
                for(int i = 0; i < indent_num; i++)
                {
                    base_window->add_ch(' ');
                
                }

                if(i == cursor_index)
                {
                    base_window->add_str("     ");
                    base_window->add_ch(cursor_icon, cursor_color);
                    base_window->add_ch(' ');
                }
                
                else
                {
                    base_window->add_str("       ");
                }

                base_window->add_str(content.at(i).content, 
                    content.at(i).color);

                base_window->add_new_line();
            }

    }
}

std::string MenuToolChoice::get_selected() 
{ 
    return content.at(selected_index).content; 
}

MenuToolItem::Status MenuToolChoice::handle_input()
{
    Status status = SELECTED;

    std::vector<Key*> keys = input_handler->get_active_keys(); 

    bool shift_pressed = false;

    for(Key* key : keys)
    {
        if(key->id == SDLK_RETURN)
        {
            input_handler->set_delay(key->id, -1);
            selected_index = cursor_index;
            status = HOVERED;
        }

        else if(key->id == SDLK_LSHIFT ||
            key->id == SDLK_RSHIFT)
        {
            shift_pressed = true;
        }

        else if(key->id == SDLK_w)
        {
            input_handler->set_delay(key->id, 10);

            if(shift_pressed) 
            {
                cursor_index = 0;
                continue;
            }
            
            if(cursor_index - 1 >= 0) cursor_index--;
        }

        else if(key->id == SDLK_s) 
        {
            input_handler->set_delay(key->id, 10);

            if(shift_pressed)
            {
                cursor_index = content.size() - 1;
                continue;
            }

            if(cursor_index + 1 < content.size()) cursor_index++;
        }

        else if(key->id == SDLK_f)
        {
            input_handler->set_delay(key->id, -1);
            cursor_index = selected_index;
            status = HOVERED;
        }
    }

    return status; 
}


// MenuToolExitButton ---------------------------------------------------------

// Constructors / Deconstructor

MenuToolExitButton::MenuToolExitButton() : MenuToolItem() {}

MenuToolExitButton::MenuToolExitButton(BaseWindow* _base_window, 
    std::string _name) 
{
    base_window = _base_window;
    name = _name;
}

MenuToolExitButton::~MenuToolExitButton() {}


// Public Functions

void MenuToolExitButton::render(Status status, std::string& cursor_color) 
{
    for(int i = 0; i < indent_num; i++)
    {
        base_window->add_ch(' ');
    
    }

    switch(status)
    {
        case NO_STATUS:
            
            base_window->add_str("   ");
            base_window->add_ch('[', cursor_color);
            base_window->add_str(name, cursor_color);
            base_window->add_ch(']', cursor_color);
            base_window->add_new_line();
            break;

        case HOVERED:
            
            base_window->add_str(" ");
            base_window->add_ch(cursor_icon, cursor_color);
            base_window->add_ch(' ');
            base_window->add_ch('[', cursor_color);
            base_window->add_str(name, cursor_color);
            base_window->add_ch(']', cursor_color);
            base_window->add_new_line();
            break;

        case SELECTED:
            
            base_window->add_str(" ");
            base_window->add_ch(cursor_icon, cursor_color);
            base_window->add_ch(' ');
            base_window->add_ch('[', cursor_color);
            base_window->add_str(name, cursor_color);
            base_window->add_ch(']', cursor_color);
            base_window->add_new_line();
            break;
    }
}

MenuToolItem::Status MenuToolExitButton::handle_input() 
{
    return EXIT;
}


// MenuToolList ---------------------------------------------------------------

// Constructors / Deconstructor

MenuToolList::MenuToolList() : MenuToolItem() {}

MenuToolList::MenuToolList(BaseWindow* _base_window, 
    InputHandler* _input_handler, std::string _name, 
    std::vector<MenuToolItem*>& _content) : 
    MenuToolItem(_base_window, input_handler, LIST)
{

    name = _name;
    content = _content;
}

MenuToolList::~MenuToolList() {}


// Public Functions

void MenuToolList::render(Status status, std::string& cursor_color)
{
    for(int i = 0; i < indent_num; i++)
    {
        base_window->add_ch(' ');
    
    }

    switch(status)
    {
        case NO_STATUS:

            base_window->add_str("   ");
            base_window->add_str(name);
            base_window->add_ch(':');
            base_window->add_new_line();

            for(MenuToolItem* m : content)
            {
                m->indent_num = indent_num + 3;
                m->render(NO_STATUS, cursor_color);
            }
            break;

        case HOVERED:

            base_window->add_ch(' ');
            base_window->add_ch(cursor_icon, cursor_color);
            base_window->add_ch(' ');
            base_window->add_str(name);
            base_window->add_ch(':');
            base_window->add_new_line();

            for(MenuToolItem* m : content)
            {
                m->indent_num = indent_num + 3;
                m->render(NO_STATUS, cursor_color);
            }
            break;

        case SELECTED:

            base_window->add_str("   ");
            base_window->add_str(name, cursor_color);
            base_window->add_ch(':');
            base_window->add_new_line();

            for(int i = 0; i < content.size(); i++)
            {
                if(i == selected_index)
                {
                    content.at(i)->indent_num = indent_num + 3;
                    content.at(i)->render(SELECTED, cursor_color);
                }

                else if(i == cursor_index)
                {
                    content.at(i)->indent_num = indent_num + 3;
                    content.at(i)->render(HOVERED, cursor_color);
                }

                else
                {
                    content.at(i)->indent_num = indent_num + 3;
                    content.at(i)->render(NO_STATUS, cursor_color);
                }
            }
    }
}

MenuToolItem::Status MenuToolList::handle_input()
{
    Status status = SELECTED;

    if(selected_index > -1) 
    {
        Status return_status = content.at(selected_index)->handle_input();

        if(return_status == HOVERED)
        {
            cursor_index = selected_index;
            selected_index = -1;
        }

        return status;
    }

    std::vector<Key*> keys = input_handler->get_active_keys();

    bool shift_pressed = false;

    for(Key* key : keys)
    {
        if(key->id == SDLK_RETURN)
        {
            input_handler->set_delay(key->id, -1);
            selected_index = cursor_index;
        }

        else if(key->id == SDLK_LSHIFT || 
            key->id == SDLK_RSHIFT)
        {
            shift_pressed = true;
        }

        else if(key->id == SDLK_w)
        {
            input_handler->set_delay(key->id, 10);
            
            if(shift_pressed)
            {
                cursor_index = 0;
                continue;
            }

            if(cursor_index - 1 >= 0) cursor_index--;
        }

        else if(key->id == SDLK_s) 
        {
            input_handler->set_delay(key->id, 10);
            
            if(shift_pressed)
            {
                cursor_index = content.size() - 1;
                continue;
            }
            
            if(cursor_index + 1 < content.size()) cursor_index++;
        }

        else if(key->id == SDLK_f)
        {
            input_handler->set_delay(key->id, -1);
            status = HOVERED;
        }
    }

    return status; 
}


// MenuTools ------------------------------------------------------------------


// Constructors / Deconstructor

MenuTools::MenuTools()
{
    base_window = nullptr;
    cursor_color = "BLUE";
}

MenuTools::MenuTools(BaseWindow* _base_window, InputHandler* _input_handler)
{
    base_window = _base_window;
    input_handler = _input_handler;
    cursor_color = "BLUE";
}

MenuTools::~MenuTools() {}


// Public Functions

void MenuTools::render()
{
    base_window->render();
}

std::pair<int, bool> MenuTools::simulate_list_selection(std::string display,
    std::vector<Text>& choices, int cursor_pos, std::string& cursor_color,
    bool block_enter_key)
{
    std::vector<Key*> keys = input_handler->get_active_keys();

    bool shift_pressed = false;

    for(Key* key: keys)
    {
        switch(key->id)
        {
            case SDLK_LSHIFT:

                shift_pressed = true;
                break;

            case SDLK_RSHIFT:

                shift_pressed = true;
                break;

            case SDLK_RETURN:
                
                if(block_enter_key) input_handler->set_delay(key->id, -1);
                else input_handler->set_delay(key->id);

                return std::pair<int,bool>{cursor_pos, true};

            case SDLK_w:
                    
                input_handler->set_delay(key->id, 10);
                
                if(shift_pressed) 
                {
                    return std::pair<int,int>{0, false};
                }
                
                if(cursor_pos - 1 >= 0) 
                {
                    return std::pair<int,int>{cursor_pos - 1, false};
                }

                break;

            case SDLK_s:

                input_handler->set_delay(key->id, 10);

                if(shift_pressed) 
                {
                    return std::pair<int,int>{choices.size() - 1, false};
                }

                if(cursor_pos + 1 < choices.size())
                {
                    return std::pair<int,int>{cursor_pos + 1, false};
                }

                break;
        }
    }

    // Rendering

    base_window->clear_content();

    if(display.size() != 0)
    {
        base_window->add_str(display);
        // base_window->add_ch(':');
        base_window->add_new_line(2);
    }

    for(int i = 0; i < choices.size(); i++)
    {

        // This is the hovered item
        if(i == cursor_pos)
        {
            base_window->add_ch(' ');
            base_window->add_ch(cursor_icon, cursor_color);
            base_window->add_ch(' ');
            base_window->add_str(choices.at(i).content, choices.at(i).color);
            base_window->add_new_line();
            continue;
        }

        base_window->add_str("   ");
        base_window->add_str(choices.at(i).content, choices.at(i).color);
        base_window->add_new_line();
    }

    return std::pair<int, bool>{cursor_pos, false};
}

std::pair<int, int> MenuTools::simulate_menu(std::string display, 
    std::vector<MenuToolItem*>& menu_content, int cursor_pos, int sel_pos,
    std::string& cursor_color)
{

    if(display.size() != 0)
    {
        base_window->add_str(display);
        // base_window->add_ch(':');
        base_window->add_new_line(2);
    }

    // Render

    for(int i = 0; i < menu_content.size(); i++)
    {
        MenuToolItem::Status item_status = MenuToolItem::NO_STATUS;

        if(i == sel_pos)
        {
            item_status = MenuToolItem::SELECTED;
        }

        else if(i == cursor_pos)
        {
            item_status = MenuToolItem::HOVERED;
        }

        menu_content.at(i)->render(item_status, cursor_color);
    }

    base_window->render();


    // Handle Input

    // There is an item selected

    if(sel_pos > -1)
    {
        MenuToolItem::Status return_status = 
            menu_content.at(sel_pos)->handle_input();

        if(return_status == MenuToolItem::HOVERED)
        {
            return std::pair<int,int> {cursor_pos, -1};
        }

        else if(return_status == MenuToolItem::EXIT)
        {
            return std::pair<int,int> {-1, sel_pos};
        }
    }

    // No item is selected
    else
    {
        // int key = base_window->get_key_press();

        std::vector<Key*> keys = input_handler->get_active_keys();

        bool shift_pressed = false;

        for(Key* key : keys)
        {

            switch(key->id)
            {

                case SDLK_RETURN:

                    input_handler->set_delay(key->id, -1);
                    return std::pair<int,int> {cursor_pos, cursor_pos};

                case SDLK_LSHIFT:

                    shift_pressed = true;
                    break;

                case SDLK_RSHIFT:

                    shift_pressed = true;
                    break;                    

                case SDLK_w:
                    
                    input_handler->set_delay(key->id, 10);

                    if(shift_pressed)
                    {
                        return std::pair<int,int>{0, sel_pos};
                    }

                    if(cursor_pos - 1 >= 0) 
                    {
                        return std::pair<int,int>{cursor_pos - 1, sel_pos};
                    }

                    break;

                case SDLK_s:

                    input_handler->set_delay(key->id, 10);

                    if(shift_pressed)
                    {
                        return std::pair<int,int>{menu_content.size() - 1,
                            sel_pos};
                    }

                    if(cursor_pos + 1 < menu_content.size())
                    {
                        return std::pair<int,int>{cursor_pos + 1, sel_pos};
                    }

                    break;

                default:
                    return std::pair<int,int> {cursor_pos, sel_pos};
            }

        }
    }

    return std::pair<int,int> {cursor_pos, sel_pos};
}

std::string MenuTools::get_color_from_ratio(int ratio, 
        const std::vector<std::string>& colors)
{

    if(ratio <= 2) return colors.at(0);
    else if(ratio > 2 && ratio <= 4) return colors.at(1);
    else if(ratio > 4 && ratio <= 7) return colors.at(2);
    else return colors.at(3);
}

void MenuTools::set_cursor_color(const std::string& color)
{
    cursor_color = color;
}

void MenuTools::display_meter(std::string display, int num, int min, int max, 
    const std::vector<std::string>& color_ratio)
{
    if(display.size() != 0)
    {
        base_window->add_str(display);
        base_window->add_ch(':');
        base_window->add_ch(' ');
    }

    int ratio = ((num - min) / ((max - min) * 1.0)) * 10;

    std::string targ_color = get_color_from_ratio(ratio, color_ratio);

    base_window->add_str(std::to_string(num), targ_color);
    base_window->add_ch(' ');
    base_window->add_ch('[');

    for(int i = 0; i < int(ratio); i++)
    {
        base_window->add_ch('|', targ_color);
    }

    for(int i = int(ratio); i < 10; i++)
    {
        base_window->add_ch(' ');
    }

    base_window->add_ch(']');
    base_window->add_ch(' ');
    base_window->add_str(std::to_string(max));
}

std::string MenuTools::display_number(std::string display, float num, 
    float min, float max, const std::vector<std::string>& color_ratio)
{
    if(display.size() != 0)
    {
        base_window->add_str(display);
        base_window->add_ch(':');
        base_window->add_ch(' ');
    }

    int ratio = ((num - min) / ((max - min) * 1.0)) * 10;

    std::string targ_color = get_color_from_ratio(ratio, color_ratio);

    // If this float is a whole number, we don't want to print out the 
    // redundant '.0' after the number
    if(int(num) == num)
    {
         base_window->add_str(std::to_string(int(num)), targ_color);
    }

    else base_window->add_str(std::to_string(num), targ_color);

    return targ_color;
}
