#ifndef POSITION_H
#define POSITION_H
/**
 * @file config.h
 * @brief Plik zawieraj¹cy config, czyli dane np. iloœæ fps oraz rozmiar bloków.
 */
#define FPS 120  /**< Liczba klatek na sekundê */
#define TILE 85  /**< Rozmiar kafelka w pikselach */

 /**
  * @brief Struktura reprezentuj¹ca pozycjê.
  *
  * Struktura zawiera dwie zmienne typu float, które reprezentuj¹ wspó³rzêdne x i y.
  */
typedef struct {
    float x; /**< Wspó³rzêdna x */
    float y; /**< Wspó³rzêdna y */
} Position;

#endif /* POSITION_H */