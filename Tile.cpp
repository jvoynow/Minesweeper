#include "Tile.h"

using namespace std;

Tile::Tile() {
}
bool Tile::get_flagged() const {
    return flagged;
}

int Tile::get_row() const {
    return row;
}

int Tile::get_column() const {
    return column;
}

int Tile::get_adj_bombs() {
    return adj_bombs;
}

void Tile::set_current_fill(color fill) {
    current_fill = fill;
}

void Tile::set_original_fill(color fill) {
    original_fill = fill;
}

void Tile::set_hover_fill(color fill) {
    hover_fill = fill;
}

void Tile::set_adj_bombs(int a_b) {
    adj_bombs = a_b;
}

void Tile::set_row(int row) {
    this->row = row;
}

void Tile::set_column(int column) {
    this->column = column;
}

void Tile::set_c1(double c1) {
    this->c1 = c1;
}

void Tile::set_c2(double c2) {
    this->c2 = c2;
}

void Tile::set_r1(double r1) {
    this->r1 = r1;
}

void Tile::set_r2(double r2) {
    this->r2 = r2;
}

void Tile::hover() {
    set_current_fill(hover_fill);
}

void Tile::stop_hover() {
    set_current_fill(original_fill);
}

bool Tile::is_overlapping(int x, int y) const {
    return x >= c1 && y >= r1 && x <= c2 && y <= r2;
}

