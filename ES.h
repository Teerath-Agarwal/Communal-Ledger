// Project Started: 27 March 2022
// Last worked on: 26 NOvember 2022 (major update)

#ifndef ES_H
#define ES_H

#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>
#include <string>
#include <ios>
#include <limits>
#include <vector>
#include <ctime>
#include <unistd.h>
#include "SHA256.h"
using namespace std;

#ifdef _WIN32
#define clr "cls"
#else
#define clr "clear"
#endif

#define pwlen 32

const vector<vector<uint8_t>> pw_order = {{27,5,20,6,28,31,7,1,19,18,29,8,9,15,11,16,22,12,23,3,21,13,26,17,10,0,2,25,30,14,24,4},{13,14,3,2,20,6,0,24,7,28,21,17,26,27,5,12,18,25,29,23,1,4,11,31,10,16,19,8,15,22,30,9},{6,30,27,16,20,10,3,23,14,13,2,12,19,11,7,5,24,21,29,26,4,0,18,9,31,8,28,1,17,22,15,25},{7,1,17,9,2,22,19,12,26,16,0,18,28,29,24,11,31,5,4,30,20,6,8,27,13,25,15,10,3,23,14,21},{28,24,8,23,6,21,2,31,18,13,15,9,0,1,5,27,19,17,10,30,4,26,7,12,3,11,25,16,29,14,22,20},{24,31,17,18,30,13,27,2,11,9,20,6,28,0,14,1,3,23,29,15,7,5,10,21,4,12,8,19,26,25,22,16},{20,15,3,19,25,21,28,0,4,17,6,8,30,10,2,24,9,27,29,16,22,13,5,14,23,1,11,12,18,31,7,26},{2,22,1,26,10,12,3,24,19,17,29,18,25,8,13,23,28,5,4,21,31,15,7,16,0,27,20,11,9,14,6,30},{11,16,31,5,21,0,14,20,8,19,3,15,13,28,30,18,9,12,4,29,2,10,22,26,17,7,27,24,6,23,25,1},{11,6,20,27,4,14,30,7,23,2,24,16,8,28,26,12,31,17,10,15,13,29,21,25,0,18,3,19,22,5,9,1},{21,8,16,28,18,31,7,11,19,26,27,13,5,20,10,9,3,22,6,0,29,17,4,25,30,2,15,14,1,23,24,12},{18,15,20,12,8,29,4,1,19,30,21,11,5,13,25,22,3,26,27,10,28,24,2,14,7,9,17,23,31,16,6,0},{2,24,27,16,15,29,10,19,12,30,1,22,25,6,14,26,13,21,9,5,31,7,0,28,11,17,4,20,3,8,18,23},{3,6,26,22,5,25,30,31,17,28,8,7,29,2,0,12,20,13,16,14,10,24,1,27,4,9,21,15,18,11,19,23},{21,11,22,7,26,18,24,3,8,12,15,20,28,29,2,13,1,6,9,0,16,25,14,30,27,23,5,10,17,19,4,31},{1,6,4,28,16,17,13,27,0,21,12,5,7,10,26,25,9,19,2,3,14,15,30,11,31,23,24,20,29,22,8,18},{18,20,9,22,24,30,10,21,2,12,4,7,8,11,29,14,3,6,15,5,1,25,0,19,28,13,17,16,23,31,27,26},{1,17,20,15,7,22,24,6,12,14,30,29,11,4,23,0,3,8,13,5,19,27,18,25,2,26,9,21,10,16,31,28},{11,5,29,27,4,6,16,22,28,7,17,10,3,9,25,12,2,0,14,21,1,13,8,15,23,24,19,18,31,26,30,20},{31,23,21,16,8,10,5,11,29,20,28,14,25,26,4,27,3,19,13,12,22,9,1,7,15,6,17,30,24,2,0,18},{9,4,25,31,5,19,16,20,17,23,2,11,21,26,18,28,24,27,22,13,0,6,15,3,29,14,30,10,1,7,8,12},{26,19,17,1,9,28,29,20,5,4,31,22,25,6,15,12,0,7,30,2,21,14,16,23,24,11,13,10,8,27,18,3},{12,25,3,5,7,14,29,17,23,1,28,22,10,2,16,30,13,26,20,27,15,24,21,6,31,8,18,11,9,19,0,4},{28,31,12,15,7,27,1,13,19,8,29,0,21,25,23,11,3,26,22,6,18,17,30,2,5,14,20,10,16,9,24,4},{13,28,27,18,24,17,6,21,11,9,16,12,0,7,4,25,30,5,23,19,15,1,8,31,22,14,3,2,26,29,20,10},{22,27,28,1,14,2,9,6,31,20,7,15,25,10,21,18,23,30,13,12,19,29,24,26,5,17,16,0,3,4,11,8},{21,22,30,14,24,23,10,28,17,1,0,19,13,11,25,3,5,26,9,16,15,18,8,20,31,2,4,27,6,12,7,29},{24,7,14,22,13,0,31,23,5,30,11,19,6,20,26,27,16,28,21,3,18,17,8,2,10,29,9,12,4,25,1,15},{8,25,19,21,7,26,9,10,29,20,5,16,12,3,15,2,4,6,17,13,0,27,11,24,30,18,14,1,28,23,22,31},{27,29,13,23,26,6,8,22,25,4,28,17,10,15,30,2,21,9,31,11,1,24,3,12,16,5,18,20,0,7,19,14},{19,13,10,8,4,15,27,31,26,30,21,6,18,1,25,23,22,7,28,20,5,24,12,16,14,29,0,2,9,3,11,17},{9,6,7,19,30,11,2,16,26,13,27,17,10,5,31,20,24,21,23,28,15,25,3,29,8,18,0,1,22,14,12,4},{11,16,9,0,30,27,2,3,15,25,20,31,6,14,8,29,26,19,24,4,1,28,17,5,18,13,22,7,23,10,12,21},{30,25,14,29,24,23,2,11,17,9,1,15,10,31,22,12,18,5,0,4,13,7,8,19,20,21,27,26,3,6,28,16},{9,1,4,16,24,10,19,7,12,23,30,6,18,8,14,5,13,27,11,20,28,0,22,15,17,25,31,21,3,29,26,2},{2,11,31,28,27,19,12,18,5,8,30,20,15,9,14,1,10,25,6,0,13,29,3,22,26,7,24,4,21,23,16,17},{5,14,18,15,21,28,16,10,19,20,1,0,9,6,24,31,8,23,22,7,4,25,11,17,27,29,30,3,2,13,12,26},{20,22,9,19,8,12,5,23,11,14,29,24,0,25,6,1,21,7,16,13,15,4,26,27,2,31,30,18,28,17,3,10},{13,25,21,10,17,26,19,9,8,23,22,3,11,29,27,31,24,12,16,14,1,5,0,4,7,6,30,20,2,28,18,15},{14,15,12,31,23,1,3,10,29,27,5,16,28,20,6,26,25,2,4,13,24,8,7,17,22,21,9,18,30,0,19,11},{0,18,5,6,1,24,16,26,15,9,28,4,29,23,17,19,31,13,2,14,27,21,30,20,11,10,8,22,25,7,3,12},{16,7,19,14,18,29,2,31,20,24,27,15,22,0,11,5,12,26,23,4,3,6,8,25,30,10,17,28,21,9,1,13},{1,21,16,22,6,26,17,23,9,4,14,20,3,0,10,25,29,30,24,27,5,7,13,28,31,18,8,19,11,2,12,15},{3,30,23,29,27,5,14,13,22,15,17,11,19,18,4,6,25,16,9,28,10,20,21,2,26,31,24,8,12,0,1,7},{20,31,12,13,2,3,28,22,1,9,8,6,10,5,14,17,25,4,26,18,7,27,15,21,16,19,30,29,24,11,23,0},{18,0,13,16,20,19,2,3,23,14,31,24,26,15,22,28,25,17,30,12,29,7,10,1,21,11,8,6,4,9,27,5},{1,30,22,23,17,19,8,5,31,25,9,13,27,20,15,7,12,3,10,14,11,4,2,0,28,26,24,6,18,29,21,16},{8,22,28,13,26,9,14,21,5,0,31,24,23,12,10,25,2,29,30,20,7,19,1,16,3,27,18,17,11,4,15,6},{17,3,27,31,10,20,29,5,18,8,19,26,11,30,7,25,4,16,2,6,14,9,13,12,23,21,28,22,15,24,0,1},{27,1,22,30,13,31,29,24,20,9,15,26,0,2,18,16,10,5,14,25,19,21,11,12,4,6,23,3,17,7,8,28},{10,6,18,17,28,19,22,3,31,0,14,23,7,25,16,27,26,21,2,5,9,8,24,1,30,4,13,12,29,15,20,11},{15,11,3,17,6,22,5,29,1,25,14,16,13,30,19,21,12,0,18,9,4,26,20,28,7,24,8,2,23,31,10,27},{3,6,10,29,15,8,7,0,9,26,14,22,27,21,19,11,1,30,13,17,4,20,18,25,28,31,2,23,12,16,5,24},{15,25,2,11,5,8,0,21,26,29,10,30,13,4,12,16,3,7,6,31,1,18,14,22,27,28,9,24,20,17,23,19},{15,26,1,10,31,5,7,27,13,30,4,11,17,24,9,8,19,20,3,0,2,22,23,14,12,16,28,29,18,21,6,25},{30,0,8,17,28,11,14,15,18,24,7,23,19,9,26,5,13,2,3,20,29,21,6,16,12,22,1,10,4,25,31,27},{7,3,19,27,1,13,14,17,24,5,2,20,4,8,16,21,6,15,22,29,18,0,25,31,26,11,28,12,10,30,23,9},{0,19,8,6,24,28,3,7,15,9,14,11,20,2,21,1,25,22,31,27,29,30,4,13,12,10,23,17,26,16,5,18},{30,24,29,28,0,12,2,18,26,22,6,31,10,4,19,20,16,27,1,23,21,8,7,13,17,5,3,15,14,9,25,11},{24,4,12,6,26,2,21,3,17,31,0,30,18,20,10,14,29,22,8,9,7,5,19,28,25,11,13,23,16,27,1,15},{10,23,1,13,6,4,9,12,30,0,22,5,11,8,29,3,2,16,18,26,21,28,27,31,20,14,24,7,17,19,15,25},{16,5,25,20,8,27,15,12,13,1,28,14,3,11,10,21,23,30,19,7,22,29,26,31,9,2,24,6,4,17,18,0},{5,14,25,12,6,1,9,7,29,28,4,8,22,24,30,27,10,13,15,0,21,26,23,20,31,16,3,19,17,11,2,18},{18,26,23,28,17,20,1,6,9,15,4,19,13,3,5,29,30,31,27,21,8,0,10,16,24,11,25,12,22,2,14,7},{18,2,1,4,15,22,0,26,3,13,20,27,6,7,21,29,9,10,23,14,25,12,11,30,5,17,31,24,28,19,8,16},{6,2,10,12,27,23,0,9,22,16,31,18,30,14,26,29,19,15,1,11,7,4,28,17,8,13,21,24,5,20,3,25},{16,29,22,10,8,1,13,3,30,27,14,17,0,7,24,11,31,19,4,6,12,28,23,20,15,18,25,5,26,9,21,2},{1,15,10,16,29,2,30,4,27,24,14,21,12,11,28,3,8,5,17,19,18,26,0,6,25,9,22,13,23,31,7,20},{24,12,13,1,16,20,22,4,11,10,3,21,18,28,30,25,14,19,8,27,26,15,5,23,9,2,29,7,6,31,0,17},{29,6,17,19,16,25,8,4,2,28,31,9,30,12,14,1,11,5,26,21,23,0,18,7,13,15,10,20,22,3,24,27},{27,14,28,25,16,12,6,1,30,7,11,9,4,22,0,19,3,15,8,18,31,2,26,23,24,13,21,20,29,17,5,10},{2,1,27,21,10,7,31,12,13,23,25,6,18,28,26,4,8,9,11,3,30,0,29,20,22,5,15,17,24,14,19,16},{11,19,14,30,28,18,4,9,2,13,27,15,3,26,21,1,16,5,23,7,17,29,24,31,20,22,25,6,10,12,0,8},{10,31,27,28,29,2,13,1,8,0,22,25,12,19,7,30,18,14,11,21,23,26,4,3,5,20,6,16,24,15,9,17},{8,15,25,13,23,12,11,22,30,10,29,14,21,1,31,9,19,2,27,18,3,4,7,6,24,16,28,26,17,20,0,5},{15,30,1,3,27,9,6,25,5,23,10,26,24,22,13,29,18,21,8,11,4,28,2,16,12,14,7,17,31,19,0,20},{23,22,12,16,31,1,17,0,9,6,27,19,7,10,13,15,18,28,29,3,14,21,11,24,4,8,5,20,26,25,30,2},{22,8,11,26,7,0,15,29,23,24,2,21,19,12,31,30,4,28,18,16,10,9,25,6,3,1,5,14,20,27,13,17},{11,9,0,16,1,31,28,26,4,7,21,8,10,22,14,23,13,19,24,30,3,29,18,27,25,15,20,17,12,5,2,6},{21,28,30,2,17,7,15,11,12,19,26,9,31,1,20,4,24,18,25,8,0,29,6,27,16,23,5,13,3,10,22,14},{4,22,25,16,11,30,24,3,27,7,5,1,12,9,2,21,15,6,31,19,26,17,13,8,28,20,10,23,18,0,14,29},{29,8,31,1,13,27,23,9,30,28,11,18,14,26,2,25,20,22,7,5,15,4,17,12,10,24,21,6,3,19,0,16},{1,15,11,30,12,14,18,3,9,0,24,13,5,7,16,4,8,21,25,2,29,26,17,22,31,10,23,6,27,20,19,28},{31,14,19,11,2,3,25,26,18,23,6,7,15,4,20,8,9,12,30,29,1,28,22,5,0,27,17,24,10,13,21,16},{15,23,19,5,10,25,18,21,26,3,16,24,2,31,4,9,12,14,6,22,7,20,27,13,17,11,28,30,8,1,29,0},{23,21,15,0,7,2,8,24,4,3,30,12,16,28,25,6,17,10,26,1,22,13,14,18,31,9,27,5,19,11,20,29},{31,7,15,3,19,8,28,0,24,29,18,9,17,16,1,10,25,30,27,14,12,22,11,4,20,5,26,21,13,2,6,23},{15,20,13,27,8,29,1,7,10,2,23,5,6,22,19,0,16,31,9,3,12,21,26,28,11,17,30,14,4,25,18,24},{23,21,3,8,12,5,16,14,22,29,26,27,20,30,11,6,1,24,4,17,9,7,10,18,13,2,19,28,25,0,15,31},{8,30,28,9,1,0,21,26,2,7,17,22,5,20,27,23,29,14,18,25,24,10,19,3,16,12,6,15,11,4,13,31},{15,26,28,7,31,0,6,22,10,17,12,4,8,18,14,5,27,11,30,3,25,21,16,23,9,20,19,1,29,13,24,2},{30,16,6,11,31,1,0,22,21,4,25,28,10,23,12,19,29,13,3,26,24,15,17,7,8,5,14,20,27,18,9,2},{11,2,0,15,31,21,10,1,28,26,7,3,8,22,29,13,12,17,20,18,24,30,6,27,5,9,14,19,16,25,4,23},{29,8,30,1,21,22,27,18,0,6,24,16,4,7,31,11,20,13,3,2,12,23,9,28,15,25,10,14,5,26,17,19},{28,19,4,10,7,31,21,30,9,8,11,17,23,3,18,29,5,27,16,2,26,0,22,13,6,15,20,24,1,14,25,12},{14,15,22,31,21,11,29,9,24,13,17,19,4,1,12,18,5,20,25,16,8,7,28,23,3,0,2,30,27,26,6,10},{3,8,31,20,1,25,16,19,0,18,4,27,24,5,23,7,10,15,28,14,11,12,22,26,30,21,17,2,9,6,13,29},{19,16,2,8,22,6,24,15,20,0,7,31,18,3,28,17,11,9,26,1,23,25,27,29,14,4,21,12,10,13,5,30},{9,18,0,12,19,15,26,7,4,3,5,16,1,27,6,23,28,24,21,20,2,30,11,31,13,8,14,17,22,10,25,29},{2,16,19,28,29,4,17,22,0,9,21,27,26,10,3,25,5,7,23,13,1,20,11,14,30,18,6,12,31,24,15,8}};

extern int tc;
extern uint64_t int_code1;
extern uint64_t int_code2;
extern string str_code;

string file_name();

string new_pass();

char* to_char(string t);

int hex_to_dec(char c);

uint8_t* sha(string s);

uint8_t* sha(uint8_t* s, int length);

uint8_t* pass_check_util(string pw);

bool verify_pass(string f, string pw);

void encrypt(ifstream &inp, string f, string pw);

int count_alph(ifstream &inp);

void display(ifstream &k);

void display2(string t);

string decrypt(ifstream &inp, string pw);

string decrypt(string fl, string pw);

void enter();

string edit_name(string f);

void readme();

void time_lock(string f, string pw);

int d_to_m(uint8_t m);

uint64_t epoch_conv(uint64_t t);

string time_unlock(ifstream &inp, string p, string f);

#endif