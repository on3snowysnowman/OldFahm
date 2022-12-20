#pragma once 

#include <string>
#include <vector>

#include "Text.h"
#include "InputHandler.h"
#include "Windows/BaseWindow.h"

#define cursor_icon 127
#define checkmark_icon 128
#define cancel_icon 129

// MenuToolItem ---------------------------------------------------------------

class MenuToolItem
{   

public: 

    enum Status
    {
        NO_STATUS,
        HOVERED,
        SELECTED,
        EXIT
    };

    enum ItemType
    {
        TEXT,
        VARIABLE,
        CHOICE,
        LIST,
    };

    enum StringType
    {
        STRING,
        INT,
        FLOAT
    };

    int indent_num = 0;

    MenuToolItem();
    MenuToolItem(BaseWindow* _base_window, InputHandler* _input_handler, 
        ItemType _type);
    ~MenuToolItem();

    virtual void render(Status status, std::string& cursor_color);
    virtual Status handle_input();

protected:

    BaseWindow* base_window;
    InputHandler* input_handler;
    ItemType type;

    void apply_input_to_string(int key, std::string& targ_str,
        StringType str_type, bool shift_pressed, bool ctrl_pressed);
};


// MenuToolText ---------------------------------------------------------------

class MenuToolText: public MenuToolItem
{

public:

    std::string content;

    MenuToolText();
    MenuToolText(BaseWindow* _base_window, InputHandler* _input_handler, 
        std::string _content);
    ~MenuToolText();

    void render(Status status, std::string& cursor_color) override;
    Status handle_input() override;
};


// MenuToolVariable -----------------------------------------------------------

class MenuToolVariable: public MenuToolItem
{

public:

    std::string name;
    std::string content;

    MenuToolVariable();
    MenuToolVariable(BaseWindow* _base_window, 
        InputHandler* _input_handler, StringType _str_type,
        std::string _name, std::string _content);
    ~MenuToolVariable();

    void render(Status status, std::string& cursor_color) override;
    Status handle_input() override;

private:

    StringType str_type;

    bool has_decimal = false;
};


// MenuToolChoice -------------------------------------------------------------

class MenuToolChoice: public MenuToolItem
{

public:

    int selected_index = 0;
    int cursor_index = 0;

    std::string name;
    std::vector<Text> content;

    MenuToolChoice();
    MenuToolChoice(BaseWindow* base_window, InputHandler* _input_handler, 
        std::string _name, 
        std::vector<Text>& _content, int _cursor_index = 0);
    ~MenuToolChoice();

    void render(Status status, std::string& cursor_color) override;

    std::string get_selected();

    Status handle_input() override;

};


// MenuToolExitButton ---------------------------------------------------------

class MenuToolExitButton: public MenuToolItem
{

public:

    std::string name;

    MenuToolExitButton();
    MenuToolExitButton(BaseWindow* _base_window, std::string _name);
    ~MenuToolExitButton();

    void render(Status status, std::string& cursor_color) override;
    Status handle_input() override;
};


// MenuToolList

class MenuToolList: public MenuToolItem
{

public:

    int cursor_index = 0;
    int selected_index = -1;

    std::string name;
    std::vector<MenuToolItem*> content;

    MenuToolList();
    MenuToolList(BaseWindow* _base_window, InputHandler* _input_handler, 
        std::string _name,
        std::vector<MenuToolItem*>& _content);
    ~MenuToolList();

    void render(Status status, std::string& cursor_color) override;
    Status handle_input() override;
};

// MenuTools ------------------------------------------------------------------

class MenuTools
{

public:

    MenuTools();
    MenuTools(BaseWindow* _base_window, InputHandler* _input_handler);
    ~MenuTools();

    void render();

    void set_cursor_color(const std::string& color);

    std::pair<int, bool> simulate_list_selection(std::string display,
        std::vector<Text>& choices, int cursor_pos, 
        std::string& cursor_color, bool block_enter_key = true);

    std::pair<int, int> simulate_menu(std::string display, 
        std::vector<MenuToolItem*>& menu_content, int cursor_pos, int sel_pos,
        std::string& cursor_color);

    std::string get_color_from_ratio(int ratio, 
        const std::vector<std::string>& colors);

    void display_meter(std::string display, int num, int min, int max, 
        const std::vector<std::string>& color_ratio 
        = {"RED", "ORANGE", "YELLOW", "GREEN"});

    std::string display_number(std::string display, float num, 
        float min, float max, const std::vector<std::string>& 
        color_ratio = {"RED", "ORANGE", "YELLOW", "GREEN"});

private:

    std::string cursor_color;

    BaseWindow* base_window;
    InputHandler* input_handler;

};
