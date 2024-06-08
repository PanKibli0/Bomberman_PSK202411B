#ifndef POSITION_H
#define POSITION_H
/**
 * @file config.h
 * @brief Plik zawieraj�cy config, czyli dane np. ilo�� fps oraz rozmiar blok�w.
 */
#define FPS 120  /**< Liczba klatek na sekund� */
#define TILE 85  /**< Rozmiar kafelka w pikselach */

 /**
  * @brief Struktura reprezentuj�ca pozycj�.
  *
  * Struktura zawiera dwie zmienne typu float, kt�re reprezentuj� wsp�rz�dne x i y.
  */
typedef struct {
    float x; /**< Wsp�rz�dna x */
    float y; /**< Wsp�rz�dna y */
} Position;

#endif /* POSITION_H */