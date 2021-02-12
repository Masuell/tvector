#ifndef __TVECTOR_H__
#define __TVECTOR_H__
/** \file TVector.h
 *  \brief Definice typu Basic Vector
 *  \author Petyovský
 *  \version 2021
 *  $Id: TVector.h 1028 2021-02-08 12:48:24Z petyovsky $
 */

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include "TVectorElement.h"
#include "check.h"
/** \defgroup TVector 2. Vector
 *  \brief Definice datového typu Basic Vector a jeho funkcí
 *  \{
 */

/** \brief Definice typu Basic Vector
 *  \details Typ Basic Vector spravuje dynamicky alokované pole prvků typu VectorElement a umožňuje s nimi pracovat pomocí definovaného API.
 */
struct TVector
	{
	TVectorElement *iValues;	///< Ukazatel na počáteční prvek pole hodnot typu VectorElement
	size_t iSize;				///< Počet elementů vektoru
	};

/** \brief Alokace vektoru a inicializace jeho elementů na hodnotu 0
 *  \details Dynamicky alokuje paměť pro pole o zadaném počtu elementů, inicializuje elementy na hodnotu 0.
 *  \param[in,out] aVector Ukazatel na místo v paměti určené pro inicializaci vektoru
 *  \param[in] aSize Požadovaný počet elementů vektoru
 *  \return \c true pokud byl vektor úspěšně alokován a inicializován
 */
bool vector_init(struct TVector *aVector, size_t aSize);

/** \brief Alokace vektoru a inicializace jeho elementů na náhodné hodnoty
 *  \details Dynamicky alokuje paměť pro pole o zadaném počtu elementů, inicializuje elementy na náhodné hodnoty.
 *  \param[in,out] aVector Ukazatel na místo v paměti určené pro inicializaci vektoru
 *  \param[in] aSize Požadovaný počet elementů vektoru
 *  \return \c true pokud byl vektor úspěšně alokován a inicializován
 */
bool vector_init_random(struct TVector *aVector, size_t aSize);

/** \brief Alokace vektoru a inicializace jeho prvků ze souboru
 *  \details Načte ze souboru počet elementů vektoru, dynamicky alokuje paměť pro vektor o načteném počtu elementů, načte ze souboru hodnoty jednotlivých elementů.
 *  \param[in,out] aVector Ukazatel na místo v paměti určené pro inicializaci vektoru
 *  \param[in,out] aInputFile Ukazatel na soubor otevřený v módu pro čtení
 *  \return \c true pokud byl vektor z dat v souboru úspěšně alokován a inicializován
 */
bool vector_init_file(struct TVector *aVector, FILE *aInputFile);

/** \brief Vytvoření úplné kopie vektoru
 *  \details Dynamicky alokuje paměť pro nové pole o shodném počtu elementů, nakopíruje hodnoty všech elementů ze starého do nového vektoru.
 *  \param[in] aVector Ukazatel na místo v paměti určené pro inicializaci vektoru
 *  \param[out] aVectorClone Ukazatel na místo v paměti určené pro vytvořenou kopii
 *  \return \c true pokud byl nový vektor úspěšně alokován a inicializován
 */
bool vector_clone(const struct TVector *aVector, struct TVector *aVectorClone);

/** \brief Uložení vektoru a jeho prvků do souboru
 *  \details Uloží do souboru počet elementů vektoru a hodnoty jednotlivých elementů.
 *  \param[in] aVector Ukazatel na existujicí vektor
 *  \param[in,out] aOutputFile Ukazatel na soubor otevřený v módu pro zápis
 *  \return \c true pokud byl vektor a jeho elementy úspěšně uloženy do souboru
 */
bool vector_store_file(const struct TVector *aVector, FILE *aOutputFile);

/** \brief Přečtení hodnoty elementu z vektoru na požadované pozici
 *  \details Přečte hodnotu elementu z dané pozice (indexu) vektoru
 *  \param[in] aVector Ukazatel na existujicí vektor
 *  \param[in] aPos Požadovaná pozice (index) elementu
 *  \return Hodnota elementu uložená ve vektoru \p aVector na pozici \p aPos
 *  \attention Funkce ověřuje platnost ukazatele a rozsah parametru \p aPos \b pouze při překladu v režimu `Debug`, kdy pomocí `assert` hlásí běhovou chybu!
 */
TVectorElement vector_value(const struct TVector *aVector, size_t aPos);

/** \brief Zapsání hodnoty elementu do vektoru na požadovanou pozici
 *  \details Zápis nové hodnoty elementu do vektoru na požadovanou pozici (index)
 *  \param[in] aVector Ukazatel na existujicí vektor
 *  \param[in] aPos Požadovaná pozice (index) elementu
 *  \param[in] aValue Nová hodnota elementu
 *  \attention Funkce ověřuje platnost ukazatele a rozsah parametru \p aPos \b pouze při překladu v režimu `Debug`, kdy pomocí `assert` hlásí běhovou chybu!
 */
void vector_set_value(struct TVector *aVector, size_t aPos, TVectorElement aValue);

/** \brief Přečtení počtu elementů vektoru
 *  \details Získání velikosti (počtu elementů) vektoru.
 *  \param[in] aVector Ukazatel na existujicí vektor
 *  \return Počet elementů vektoru nebo hodnota 0 v případě chyby
 */
size_t vector_size(const struct TVector *aVector);

/** \brief Změna velikosti existujicího vektoru
 *  \details Změna počtu elementů vektoru, alokace nové dynamické paměti pro pole o novém počtu prvků, kopie prvků z původního pole, inicializace doplněných prvků na hodnoty 0, dealokace dynamické paměti původního pole.
 *  \param[in,out] aVector Ukazatel na existujicí vektor
 *  \param[in] aNewSize Nový počet elementů vektoru
 *  \return \c true pokud byl vektor úspěšně přealokován a všechny elementy nového vektoru byly úspěšně inicializovány
 */
bool vector_resize(struct TVector *aVector, size_t aNewSize);

/** \brief Dealokace vektoru
 *  \details Dealokace dynamicky alokovaného pole, nastaveni počtu elementů i ukazatele na hodnotu 0 (NULL).
 *  \param[in,out] aVector Ukazatel na existujicí vektor
 */
void vector_destroy(struct TVector *aVector);
/** \} TVector */

/** \defgroup TVectorIterator 4. VectorIterator
 *  \brief Definice datového typu Basic VectorIterator a jeho funkcí
 *  \{
 */

/** \brief Definice typu Basic VectorIterator
 *  \details Basic VectorIterator se při vzniku naváže na zvolený vektor a následně umožňuje přistupovat k jednotlivým prvkům pomocí definovaného API.
 */
struct TVectorIterator
	{
	struct TVector *iVector;	///< Ukazatel na navázaný vektor (mutable iterátor - umožňuje měnit prvky VectorElement)
	size_t iPos;				///< Aktuální pozice pro indexaci prvku v navázaném vektoru
	};

/** \brief Vytvoření nového iterátoru ukazujícího na počáteční element
 *  \details Vytvoří a vrací nový iterátor, který je navázán (asociován) na zadaný vektor a ukazuje na jeho počáteční element
 *  \param[in] aVector Ukazatel na existujicí vektor
 *  \return Nový iterátor asociovaný s vektorem \p aVector ukazující na počáteční element vektoru
 */
struct TVectorIterator vector_iterator_begin(const struct TVector *aVector);

/** \brief Vytvoření nového iterátoru ukazujícího na zadanou pozici
 *  \details Vytvoří a vrací nový iterátor, který je navázán (asociován) na zadaný vektor a ukazuje na element na zadané pozici
 *  \param[in] aVector Ukazatel na existujicí vektor
 *  \param[in] aPos Zadaná pozice
 *  \return Nový iterátor asociovaný s vektorem \p aVector ukazující na element na zadané pozici \p aPos
 */
struct TVectorIterator vector_iterator_pos(const struct TVector *aVector, size_t aPos);

//struct TVectorIterator vector_iterator_last(const struct TVector *aVector);

/** \brief Zjištění platnosti iterátoru
 *  \details Funkce (predikát) vracející \c bool hodnotu definující platnost iterátoru.
 *  \param[in] aIter Ukazatel na existujicí iterátor
 *  \return \c true pokud je iterátor platný a ukazuje na platné místo v asociovaném vektoru
 */
bool vector_iterator_is_valid(const struct TVectorIterator *aIter);

/** \brief Posunutí iterátoru vpřed
 *  \details Funkce ověří platnost iterátoru, a pokud je platný, zajistí jeho posun vpřed (tj. na následujicí element v asociovaném vektoru).
 *  \param[in,out] aIter Ukazatel na existujicí iterátor
 *  \return \c true pokud je iterátor platný a ukazuje i po posunutí na platné místo v asociovaném vektoru
 */
bool vector_iterator_to_next(struct TVectorIterator *aIter);

/** \brief Posunutí iterátoru vzad
 *  \details Funkce ověří platnost iterátoru, a pokud je platný, zajistí jeho posun vzad (tj. na předchozí element v asociovaném vektoru).
 *  \param[in,out] aIter Ukazatel na existujicí iterátor
 *  \return \c true pokud je iterátor platný a ukazuje i po posunutí na platné místo v asociovaném vektoru
 */
bool vector_iterator_to_prev(struct TVectorIterator *aIter);

/** \brief Přečtení hodnoty elementu z vektoru pomocí iterátoru
 *  \details Přečte hodnotu elementu vektoru z pozice (indexu) určeného iterátorem.
 *  \param[in] aIter Ukazatel na existujicí iterátor
 *  \return Hodnota elementu vektoru z pozice na kterou ukazuje iterátor \p aIter, nebo nulový prvek (pokud je iterátor neplatný).
 */
TVectorElement vector_iterator_value(const struct TVectorIterator *aIter);

/** \brief Zapsání hodnoty elementu do vektoru pomocí iterátoru
 *  \details Zápis nové hodnoty elementu do vektoru na pozici určenou iterátorem.
 *  \param[in] aIter Ukazatel na existujicí iterátor
 *  \param[in] aValue Nová hodnota elementu
 *  \return \c true pokud je iterátor platný a zápis mohl proběhnout na platné místo v asociovaném vektoru
 */
bool vector_iterator_set_value(const struct TVectorIterator *aIter, TVectorElement aValue);

/** \} TVectorIterator */

/** \defgroup IteratorAlgorithms 5. Univerzální funkce pro práci s iterátory
 *  \brief Definice funkcí používajicí iterátory
 *  \{
 */

/** \brief Zavolání zvolené funkce na element vektoru určený pomocí iterátoru a také na všechny následující elementy vektoru
 *  \details Zavolá zvolenou funkci na každý element vektoru od pozice definované iterátorem až do konce vektoru.
 *  \param[in] aIter Ukazatel na existujicí iterátor
 *  \param[in] aOperation Ukazatel na funkci vracejicí \c void s jedním parametrem typu ukazatel na iterátor
 */
static inline void vector_for_each(struct TVectorIterator aIter, void(*aOperation)(const struct TVectorIterator *aIter))
	{
	for(; vector_iterator_is_valid(&aIter); vector_iterator_to_next(&aIter))
		aOperation(&aIter);
	}

/** \} IteratorAlgoritms */

#endif /* __TVECTOR_H__ */
