#pragma once
#ifndef RENDERER_H
#define RENDERER_H

void Init(void);
void render();

void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void mouseMove(int x, int y);

#endif