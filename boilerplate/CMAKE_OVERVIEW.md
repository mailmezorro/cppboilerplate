# CMake Overview (boilerplate)

## Ziel dieses Projekts
Das `boilerplate` ist ein kleines C++17 Projekt mit sauberer Struktur:

- `src/` enthält die Library-Implementierung
- `include/` enthält Public Header
- `app/` enthält eine ausführbare Demo
- `tests/` enthält Unit Tests (GoogleTest)

## Wichtige Begriffe

### CMakeLists.txt
Eine `CMakeLists.txt` ist die Konfigurationsdatei (Build-Rezept).
Sie definiert, **was** gebaut wird und **wie** gebaut wird.

### Target
Ein CMake-Target ist eine Build-Einheit mit Eigenschaften:

- Quellen (`.cpp`)
- Include-Pfade
- Compiler-Flags
- Link-Abhängigkeiten

Beispiele in diesem Projekt:

- `mylib` (Library)
- `mylib_app` (Executable)
- `mylib_tests` (Executable)

Wichtig: Das Target ist ein CMake-Objekt. Die gebauten Dateien liegen danach im Build-Ordner (z. B. `libmylib.a`, `mylib_app`).

## Ablauf beim Konfigurieren und Bauen

1. CMake liest `boilerplate/CMakeLists.txt` (Root)
2. Root setzt globale Defaults (C++17, Warnungen, Optionen)
3. Root ruft `add_subdirectory(src|app|tests)` auf
4. In den Sub-CMakeLists werden konkrete Targets angelegt
5. Beim Build werden erst Objektdateien kompiliert, dann gelinkt

## Root CMakeLists.txt erklärt

Datei: `boilerplate/CMakeLists.txt`

- `cmake_minimum_required(VERSION 3.20)`
- `project(mylib)` setzt den Projektnamen
- C++ Standard global auf 17
- Compiler-Warnungen:
  - MSVC: `/W4`
  - GCC/Clang: `-Wall -Wextra -Wpedantic`

### Optionen

- `ENABLE_TIDY` (default `OFF`)
- `ENABLE_SANITIZERS` (default `OFF`)

Wenn `ENABLE_TIDY=ON`:

- `clang-tidy` wird gesucht
- falls vorhanden, wird `CMAKE_CXX_CLANG_TIDY` gesetzt
- Konfigurationsdatei: `boilerplate/.clang-tidy`

Wenn `ENABLE_SANITIZERS=ON`:

- Funktion `mylib_enable_sanitizers(target)` setzt
  - Compile-Flags: `-fsanitize=address,undefined`, `-O0`, `-g`, `-fno-omit-frame-pointer`
  - Link-Flags: `-fsanitize=address,undefined`

## GTest Integration

Im Root wird GoogleTest via `ExternalProject_Add(...)` eingebunden:

- Download von GitHub
- Build in lokalem Build-Baum
- Include- und Lib-Pfade werden in Variablen gespeichert

Diese Variablen werden in `tests/CMakeLists.txt` genutzt.

## Subdirectory CMakeLists

### src/CMakeLists.txt

- `add_library(mylib STATIC mylib.cpp)`
- `target_include_directories(mylib PUBLIC ...)` exportiert Headerpfade
- `target_compile_features(mylib PUBLIC cxx_std_17)`
- `mylib_enable_sanitizers(mylib)`

### app/CMakeLists.txt

- `add_executable(mylib_app main.cpp)`
- `target_link_libraries(mylib_app mylib)`
- erbt dadurch Public Includes der Library

### tests/CMakeLists.txt

- `add_executable(mylib_tests test_mylib.cpp)`
- linkt gegen `mylib`, `libgtest.a`, `libgtest_main.a`, `pthread`
- `add_dependencies(mylib_tests googletest)`
- `add_test(NAME mylib_tests COMMAND mylib_tests)`

## Warum Library + App trennen?

- Bessere Testbarkeit
- Wiederverwendbarkeit der Logik
- Klare Trennung zwischen Business-Logik und `main()`

Pattern:

- `src/mylib.cpp` -> Library
- `app/main.cpp` -> Executable (Entry Point)
- `tests/test_mylib.cpp` -> Test Executable

## Graph der Targets

Graph-Dateien wurden erzeugt:

- `boilerplate/build-graph/graph.dot`
- `boilerplate/build-graph/graph.png`

Wichtig: Der Graph wird **nicht automatisch** bei jedem CMake-Lauf erzeugt.
Nur mit explizitem Parameter:

```bash
cmake -S boilerplate -B boilerplate/build-graph --graphviz=boilerplate/build-graph/graph.dot
```

PNG rendern:

```bash
dot -Tpng boilerplate/build-graph/graph.dot -o boilerplate/build-graph/graph.png
```

## Nützliche Befehle

### Standard Build

```bash
cmake -S boilerplate -B boilerplate/build
cmake --build boilerplate/build
ctest --test-dir boilerplate/build --output-on-failure
```

### Mit clang-tidy

```bash
cmake -S boilerplate -B boilerplate/build-tidy -DENABLE_TIDY=ON
cmake --build boilerplate/build-tidy
```

### Mit Sanitizers

```bash
cmake -S boilerplate -B boilerplate/build-sanitize -DENABLE_SANITIZERS=ON
cmake --build boilerplate/build-sanitize
ctest --test-dir boilerplate/build-sanitize --output-on-failure
```

## Kurzantwort für Interview

"CMake Targets sind benannte Build-Einheiten (Library/Executable) mit ihren Build-Eigenschaften. `CMakeLists.txt` definiert diese Targets; der Build erzeugt daraus die konkreten Artefakte im Build-Ordner."
