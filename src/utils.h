#pragma once

void config();

void loadWeapons();
void loadElements();

int abs(int val);
int collision(Geometry_t g1, Geometry_t g2);

int onSurface(Geometry_t geo);
int belowSurface(Geometry_t geo);

void clearKeys();
void expireActors(Actor_t actors[], int * numAct);
void gravity();