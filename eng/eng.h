#ifndef ENG_H
#define ENG_H

extern int actWidth;
extern int actHeight;

typedef void (*func)(void);

int goo(
    char* title,
    int width,
    int height,
    func init,
    func update,
    func render,
    func clean
);

#endif
