#pragma once
#include <string>

void demo_task_1();
void demo_task_2();
void demo_task_3();
void demo_task_4();
void demo_task_5();

void clear_input();
int choose_input_method();
int input_height();
std::string input_name_field(const std::string& field_name, bool allow_empty = true);
std::string input_city_name(const std::string& field_name);

void handle_task_1();
void handle_task_2();
void handle_task_3();
void handle_task_4();
void handle_task_5();