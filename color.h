#ifndef COLOR_H_
#define COLOR_H_

typedef struct {
	int id_col;
	char nombre_col[30];
}Color;

Color pedirColor(int id_col);
void imprimirColor(Color c);

#endif /* COLOR_H_ */
