# 💻 Tetres

- **Zjednodušená verzia starej hry TETRIS vytvorená v jazyku C s použitím knížníc SDL2.**

## 📁 Inštalácia

### Linux (Ubuntu/Debian) - Odporúčané

```bash
sudo apt update
sudo apt install build-essential libsdl2-dev libsdl2-ttf-dev libsdl2-mixer-dev
git clone https://github.com/Patnixx/Tetres-C.git
cd Tetres-C
make
./tetres
```
### MacOS (Homebrew)

- **Ak máte homebrew nainštalovaný, prvý krok preskočte.**
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
brew install sdl2 sdl2_ttf sdl2_mixer
git clone https://github.com/Patnixx/Tetres-C.git
cd Tetres-C
make
./tetres
```
### Windows (MinGW32)

1. Nainštaluj si [MinGW32](https://www.msys2.org/)
2. Otvor MinGW32 terminál
```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_ttf mingw-w64-x86_64-SDL2_mixer make git
git clone https://github.com/Patnixx/Tetres-C.git
cd Tetres-C
make
./tetres.exe
```

## ⚡ Základné mechaniky

- **Originálny dojem** - hra využíva 7 základných blokov (O, I, S, Z, J, L, T) + ich rotácie
- **Príprava pred pádom** - hra hovorí hráčovi o následujúcom tvare
- **Symfónia** - jemná hudba v pozadí počas celého hrania
- **Interaktívne rozhranie** - hra dáva hráčovi možnosť preskúmať viacero herných okien
- **Zlepšovanie** - hra zaznamenáva hráčovi najlepšie 3 skóre
- **Variabilita** - hráč si vie vybrať z viacerých nastavení pre zlepšenie kvality hrania


## 🎮 Ovládanie

- **Hráč si vie v nastaveniach meniť 'layout' svojich kláves**

| ARROWS  |  WASD   | POKYN                           |
|---------|---------|---------------------------------|
| `←` `→` | `A` `D` |Posúvanie tvaru vľavo/vpravo     |
| `↓`     | `S`     |Zrýchlenie pádu                  |
| `↑`     | `W`     |Rotácia tvaru o 90°              |
| `Space` | `Space` |Hard drop (okamžitý pád)         |
| `Esc`   | `Esc`   |Návrat do menu / Ukončenie hry   |

## 📁 Štruktúra projektu

```
Tetres/
├── src/                    # Zdrojové súbory
│   ├── main.c              # Hra a jej bežanie
│   ├── mechs.c             # Herná logika
│   ├── audio.c             # Zvuky a hudba
│   ├── highscore.c         # Mechanika highscore
│   └── settings.c          # Fungovanie nastavení
├── include/                # Hlavičkové súbory
├── assets/                 # Prílohy
│   │── audio/              # Audio          
│   │   ├── theme.mp3       # Herná hudba
│   │   ├── gameover.mp3    # Audio po prehratí
│   │   └── line.mp3        # Zvuk pri zničení riadku
│   ├── font/               # Fonty
│   │   └── Jersey.ttf      # Font Jersey
│   └── txt/                # Textové súbory
│   │   │── settings.txt    # Uloženie nastavení
│   │   └── highscore.txt   # Ukladanie najvyššieho skóre
├── tetres                  # Generovaná hra
├── Makefile
└── README.md
```

## 🗿 Herné mechaniky

### 🎲 Náhoda
- **Hra generuje každý tvar náhodne spolu aj s jeho farbou**


## 🔗 Technológie

| Technológia                                      | Využitie                        |
|--------------------------------------------------|---------------------------------|
| **C (verzia 11)**                                | Programovací jazyk hry          |
| **Make**                                         | Systém generovania finálnej hry |
| [SDL2](https://www.libsdl.org/)                  | Grafika, mechanika a herné okno |
| [SDL2_ttf](https://wiki.libsdl.org/SDL2_ttf)     | Načítanie fontov a ich veľkosti |
| [SDL2_mixer](https://wiki.libsdl.org/SDL2_mixer) | Audio systém                    |

## 📍 Licencia
- **Hra je pre edukačné účely. Akákoľvek zhoda s už existujúcou realizáciou alebo assetom je čisto náhodná a nebola účelom projektu.**
- **Zároveň, je voľne dostupná na rework, prípadne iný prínos pre tento projekt.**

## Ostatné
- **Projekt bol commitovaný ako súčasť iného repozitára -> [UPR](https://github.com/Patnixx/upr), preto všetky commity sa nachádzajú práve tu.**

✌️ https://github.com/Patnixx/Tetres-C