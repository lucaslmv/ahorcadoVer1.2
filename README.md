# Juego del Ahorcado - Versión 1.2

## Descripción
Este es un juego clásico del ahorcado implementado en lenguaje C, diseñado como una **versión argentina** con mensajes en español y un toque local en las palabras incluidas. La versión 1.2 incluye mejoras como soporte para emojis, sonidos con `Beep`, y la capacidad de borrar letras al ingresar palabras ocultas en el modo de dos jugadores.

El juego permite dos modos:
- **Un jugador**: Adivina palabras predefinidas de una lista temática que incluye términos argentinos y generales.
- **Dos jugadores**: Un jugador ingresa una palabra oculta y el otro intenta adivinarla, con soporte para borrar letras durante la entrada.

## Características
- **Idioma**: Español, con un enfoque argentino (palabras como "MATE", "TORTAFRITA", "MARADONA").
- **Emojis**: Visualización de emojis (🕹️, 😮, 💀) para una experiencia más divertida, habilitada con codificación UTF-8.
- **Sonidos**: Efectos de sonido con `Beep` para victorias (melodía ascendente) y derrotas (melodía descendente).
- **Estadísticas**: Guarda las estadísticas de los jugadores (jugadas, victorias, derrotas) en un archivo `estadisticas.txt`.
- **Entrada robusta**: En el modo de dos jugadores, permite borrar letras con la tecla `Backspace` y valida que solo se ingresen letras y espacios.

## Cómo fue programado
El juego está escrito en **lenguaje C** y utiliza bibliotecas estándar como `<stdio.h>`, `<stdlib.h>`, `<string.h>`, `<ctype.h>`, `<time.h>`, `<windows.h>` y `<conio.h>`. Las principales características técnicas incluyen:
- **Estructura de datos**: Usa una lista enlazada para almacenar estadísticas de jugadores dinámicamente.
- **Gestión de entrada/salida**: Implementa `getch()` para entrada sin eco en el modo de dos jugadores y `SetConsoleOutputCP(CP_UTF8)` para soportar emojis.
- **Sonidos**: Genera melodías simples con `Beep` para feedback auditivo.
- **Modularidad**: El código está organizado en funciones para manejar el juego, la interfaz, los sonidos y las estadísticas.
- **Compatibilidad**: Diseñado para Windows debido al uso de `windows.h` y `conio.h`.

Esta es la **versión 1.2**, que mejora la entrada de palabras ocultas (agregando soporte para `Backspace`) y asegura la liberación de memoria para evitar fugas.

## Requisitos
- Sistema operativo: Windows (por las bibliotecas `windows.h` y `conio.h`).
- Compilador C: GCC/MinGW o cualquier compilador compatible con Windows (por ejemplo, Visual Studio, Code::Blocks).
- Consola con soporte UTF-8: Recomendado usar Windows Terminal o una consola moderna para ver los emojis correctamente.

## Instalación y ejecución
1. Clona el repositorio:
   ```bash
   git clone https://github.com/tu-usuario/JuegoAhorcado.git

## Instrucciones de uso: 
-Selecciona un modo en el menú principal: 
1: Modo de un jugador (adivina palabras predefinidas).
2: Modo de dos jugadores (un jugador ingresa la palabra, el otro adivina).
0: Salir.

-En el modo de dos jugadores, usa la tecla Backspace para corregir la palabra oculta.
-Adivina letras o la palabra completa. Tienes 6 intentos antes de perder.
-Las estadísticas se guardan automáticamente en estadisticas.txt al salir.

## Notas: 
-Asegúrate de que tu consola soporte UTF-8 para ver los emojis correctamente.
-Los sonidos requieren un altavoz habilitado en el sistema.
-Para otros sistemas operativos, el código necesitaría modificaciones para reemplazar windows.h y conio.h.

AutorDesarrollado por LucasLMV "El Madri" . Versión Argentina, desarrollada en "La cueva".

### **README.md (English)**

# Hangman Game - Version 1.2

## Description
This is a classic hangman game implemented in C, designed as an **Argentine version** with messages in Spanish and a local flavor in the word list. Version 1.2 includes enhancements like emoji support, sound effects using `Beep`, and the ability to delete characters with `Backspace` when entering hidden words in two-player mode.

The game offers two modes:
- **Single Player**: Guess predefined words from a thematic list including Argentine and general terms.
- **Two Players**: One player enters a hidden word, and the other tries to guess it, with support for correcting input using `Backspace`.

## Features
- **Language**: Spanish, with an Argentine focus (words like "MATE", "TORTAFRITA", "MARADONA").
- **Emojis**: Displays emojis (🕹️, 😮, 💀) for a more engaging experience, enabled with UTF-8 encoding.
- **Sounds**: Sound effects using `Beep` for wins (ascending melody) and losses (descending melody).
- **Statistics**: Saves player stats (games played, wins, losses) to a `estadisticas.txt` file.
- **Robust Input**: In two-player mode, allows deleting characters with `Backspace` and validates that only letters and spaces are entered.

## How It Was Programmed
The game is written in **C** using standard libraries such as `<stdio.h>`, `<stdlib.h>`, `<string.h>`, `<ctype.h>`, `<time.h>`, `<windows.h>`, and `<conio.h>`. Key technical features include:
- **Data Structure**: Uses a linked list to dynamically store player statistics.
- **Input/Output Management**: Implements `getch()` for non-echoed input in two-player mode and `SetConsoleOutputCP(CP_UTF8)` for emoji support.
- **Sounds**: Generates simple melodies with `Beep` for audio feedback.
- **Modularity**: Code is organized into functions for gameplay, interface, sounds, and statistics.
- **Compatibility**: Designed for Windows due to the use of `windows.h` and `conio.h`.

This is **version 1.2**, which improves hidden word input (adding `Backspace` support) and ensures memory is freed to prevent leaks.

## Requirements
- Operating System: Windows (due to `windows.h` and `conio.h`).
- C Compiler: GCC/MinGW or any Windows-compatible compiler (e.g., Visual Studio, Code::Blocks).
- UTF-8 Console: Use Windows Terminal or a modern console for proper emoji display.

## Installation and Execution
1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/JuegoAhorcado.git

