# Zadání cvičení 1

Stanovte a ověřte časovou a paměťovou složitost funkce `vector_resize()`, která změní rozměr vektoru.
Funkce alokuje daný počet prvků a vloží do něj hodnoty z původního vektoru.

Pro řešení jsou připraveny zdrojové texty, z nichž některé je nutné doplnit o kód.
Pro vlastní testování je připravena funkce `resize_testing()` (soubor `main.c`), která zavolá testovanou funkci `vector_resize()` a změří čas jejího trvání.
Čas trvání se měří pomocí času získaného funkcí `timespec_get()` do struktury `timespec` (knihovna `time.h`). Ve struktuře jsou dva časové údaje, jeden udává celé sekundy a druhý nanosekundy (od určitého okamžiku v minulosti). Výpočet času v sekundách se provádí ve funkci `difftimespec()`.
Testovací funkce se volá z funkce `main()` pro různá množství paměti (parametrem je počet `int`ů, alokovaná paměť je tedy větší - kolikrát? Proč?)

Smysl použití `TVectorElement.h` a definovaného typu `TVectorElement` je v oddělení realizace `TVector` (souborů `TVector.c` a `TVector.h`) od konkrétního použitého typu. Pokud v budoucnu změníme datový typ, budeme měnit pouze soubor `TVectorElement.h`. Pro základní datové typy je nutné pouze upravit alias na typ v definici `TVectorElement`. Pokud ovšem typem bude struktura (např. komplexní číslo, zlomek, jméno a příjmení), budeme muset upravit i funkce v tomto souboru (ale zdrojové soubory vektoru zůstanou nezměněny). Načtení a uložení do souboru a způsob porovnávání podle velikosti, a vygenerování náhodné hodnoty. Z toho také plyne, že vektor bude pro obecný typ umět pouze načíst a uložit se do souboru, a seřadit se podle velikosti.

Rozdíl mezi API funkcemi `malloc()` a `calloc()`? Obě alokují bajty. Funkce `calloc` násobí proměnné sama a kontroluje přetečení. Funkce `calloc` předem nuluje přidělenou paměť efektivně pomocí mechanismu jádra operačního systému. Z toho plyne, že `malloc` použijeme tam, kde paměť (ihned) plníme svými daty. Funkci `calloc` použijeme v okamžiku, kdy nemáme data k přiřazení do prvků pole nebo chceme ponechat inicializaci prvků na nuly.

1. Prostudujte dodaný projekt a v něm dodané zdrojové kódy.
   - Projekt si překopírujte (na `P:`) a otevřete pomocí souboru `TVector.sln`.
   - Upravte si nastavení formátování zdrojového kódu označované v literatuře jako [Whitesmiths](https://en.wikipedia.org/wiki/Indentation_style#Whitesmiths_style) (`Tools` > `Options` > `TextEditor` > `C & C++` > `Formating` > `Indentation` a zde zaškrtněte první položku `Indent braces`).
   - Nastavení prostředí VS si uložte pro rychlejší načtení v dalších cvičeních (`Tools` > `Import and Export Settings` > `Export selected environment settings` > `Next` > `Next` > uložit soubor na plochu a zvolit `Finish`).
   - Prostudujte si funkce v souboru `main.c`.
   - Prostudujte si soubor `TVectorElement.h`, který obsahuje základní definice dat a pomocných metod (snažte se je ve svém kódu použít). Popište a zdůvodněte význam typu `TVectorElement` a makra `TVECTOR_ELEMENT_FRMSTR` (v případě nutnosti se inspirujte ve funkcích v `TVectorElement.h`). 
   - Prostudujte si soubor `TVector.h` (mimo sekci s iterátory) a vysvětlete jeho význam v projektu
   - Prostudujte soubor `TVector.c`.
   - Nastudujte si, jak pracuje funkce `assert()`, definovaná ve standardním souboru `assert.h`


2. Funkce `vector_init()` vytvoří vektor o dané délce s nulovými prvky - do proměnné, která je předána jako parametr. Předpokládáme, že v inicializované proměnné nejsou platná data (nebyla ještě použita).

        // test vstupních parametrů - je-li proměnná typu ukazatel NULL, ukončíme funkci (nulujeme proměnnou?)
        // alokujeme pole dané délky a uložíme ho do proměnné.
        // pokud došlo k chybě (není paměť) funkci ukončíme
        // ve struktuře nastavíme délku alokovaného pole
        // pole naplníme nulami

3. Funkce `vector_init_random()` vytvoří vektor o dané délce s náhodnými hodnotami - do proměnné, která je předána jako parametr.
 Od funkce `vector_init()` se liší vložením náhodných hodnot do prvků pole (použijte připravenou funkci v `TVectorElement.h`).

4. Funkce `vector_init_file()` vytvoří vektor o dané délce s danými hodnotami do proměnné, která je předána jako parametr. Druhým parametrem je proměnná typu `FILE*` představující otevřený soubor s počtem prvků pole a následným výčtem jednotlivých prvků pole. 

        // kontrola existence vstupních proměnných
        // načíst počet prvků ze souboru (s kontrolou)
        // alokace - kontrola - uložení do aVector
        // nastavení aVector - size
        // načtení prvku do vektoru (s kontrolou)

5. Funkce `vector_destroy()` uvolní získané zdroje (alokovanou paměť) a nastaví vnitřní složky proměnné `TVector` pro budoucí další použití. 

        // kontrola existence vstupních proměnných
        // uvolnění paměti
        // vynulování proměnných struktury

6. Funkce `vector_value()` vrátí hodnotu na dané pozici pole uloženého ve struktuře `TVector`.

        // kontrola existence proměnných a test, zda je index uvnitř délky uloženého pole
        // vrácení hodnoty

7. Funkce `vector_resize()` změní rozměr vnitřního pole na novou hodnotu. Předpokládá se, že proměnná již obsahuje platná data.

        // kontrola existence vstupních proměnných
        // pokud jsou stejně dlouhé, funkci ukončím
        // pokud je nová délka nulová, odalokuji, vynuluji a ukončím funkci
        // alokovat nový vektor pro dodaný rozměr (malloc/calloc) - kontrola alokace
        // provedení kopie dat do nového pole (zvolit délku pokud kopírujeme do menšího nebo většího)
        // uvolnění starého pole
        // zapsání nových dat do původní proměnné

8. Funkce `vector_clone()` vytvoří kopii prvku `aVector` (zdroj) do proměnné `aVectorClone`. Předpokládáme, že proměnná `aVectorClone` může již obsahovat platná data, které musí být případně odalokovány, pokud nebudou využity. 

        // test existence vstupních proměnných
        // test, zda vstup a výstup jsou různé proměnné - pokud jsou stejné ukončit funkci
        // pokud není originál alokován ("prázdna proměnná") - vynulovat kopii a skončit
        // alokovat paměť pro kopii - otestovat
        // překopírovat hodnoty do alokovaného pole
        // staré hodnoty (pole) v proměnné aVectorClone - uvolnit
        // přepsat do výstupní proměnné aVectorClone nově alokované pole a jeho délku

9. Funkce `vector_store_file()` představuje opak k načítání z pole (data uloží ve stejném formátu tak, aby šla opětovně načíst pomocí funkce `vector_init_file()`.

10. Funkce `vector_set_value()` má za úkol zapsat zadanou hodnotu na danou pozici v poli a provést kontroly platnosti takového operace.

---
`$Id: cv01_zadani_TVector.md 1019 2021-02-04 14:14:03Z petyovsky $`
