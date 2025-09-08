# Callgrind: Profiling und Leistungsanalyse

---

# Inhaltsverzeichnis
- [Einführung in Callgrind](#einführung-in-callgrind)
  - [Was ist Callgrind](#was-ist-callgrind)
  - [Warum Callgrind verwenden](#warum-callgrind-verwenden)
- [Benutzung von Callgrind](#benutzung-von-callgrind)
  - [Funktionsweise](#funktionsweise)
  - [Compilierung](#compilierung)
  - [Aufruf](#aufruf)
  - [Kontrolle bei der Ausführung](#kontrolle-bei-der-ausführung)
  - [Visualisierung der Ergebnisse](#visualisierung-der-ergebnisse)
- [Leistungsmessung mit Callgrind](#leistungsmessung-mit-callgrind)
  - [Beispielaufruf](#beispielaufruf)
  - [Analyse der Callgrind-Ausgabe (Copilot)](#analyse-der-callgrind-ausgabe-copilot)
- [Demonstration: Messung unterschiedlicher Fibonacci-Zahlen-Berechnungsalgorithmen](#demonstration-messung-unterschiedlicher-fibonacci-zahlen-berechnungsalgorithmen)
  - [Definition](#definition)
  - [Algorithmen für Fibonacci-Zahlen](#algorithmen-für-fibonacci-zahlen)
    - [Rekursiver Algorithmus](#rekursiver-algorithmus)
    - [Dynamische Programmierung](#dynamische-programmierung)
    - [Iterativer Ansatz I](#iterativer-ansatz-i)
    - [Iterativer Ansatz II](#iterativer-ansatz-ii)
    - [Matrix-Exponentiation](#matrix-exponentiation)
    - [Binetsche Formel](#binetsche-formel)
    - [Fast Doubling](#fast-doubling)
    - [Generator-basierter Ansatz (C++23)](#generator-basierter-ansatz-c23)
  - [Vergleich der Profiling-Ergebnisse](#vergleich-der-profiling-ergebnisse)
    - [Instruktionen](#instruktionen)
    - [Datenzugriffe](#datenzugriffe)
    - [Branches](#branches)

---

# Einführung in Callgrind

## Was ist Callgrind

  - Ein Profiling-Tool für Programme, Teil der Valgrind-Suite.
  - Eine Erweiterung von Cachegrind.
  - Zählt Funktionsaufrufe, Instruktionen, Speicherzugriffe und Sprünge.
  - Simuliert Cache- und Branch-Prädiktion.

## Warum Callgrind verwenden

  - Erkenntnisse über die Codeausführung gewinnen
  - Algorithmen optimieren und Leistung verbessern.

---

# Benutzung von Callgrind

## Funktionsweise

  - Führt das Programm in einer virtuellen Umgebung aus.
  - Zeichnet Informationen über Instruktionen, Speicherzugriffe und Sprünge auf.

## Compilierung

  - Kompilieren mit Debug-Symbolen und Optimierungen.
  - Beispiel: `clang++ -g -O2 -o programm programm.cpp`
  - Anpassung des Codes nicht erforderlich aber möglich. Spezielle Makros:
    - `CALLGRIND_START_INSTRUMENTATION`: Startet die Instrumentierung.
    - `CALLGRIND_STOP_INSTRUMENTATION`: Stoppt die Instrumentierung.
    - `CALLGRIND_COLLECT`: Aktiviert die Datenerfassung.
    - `CALLGRIND_TOGGLE_COLLECT`: Schaltet die Datenerfassung um.
    - `CALLGRIND_ZERO_STATS`: Setzt die gesammelten Statistiken zurück.
    - `CALLGRIND_DUMP_STATS`: Speichert die aktuellen Statistiken in die Ausgabedatei.
    - ...

## Aufruf

  - `valgrind --tool=callgrind [Argumente] ./programm [Programm-Argumente]`
  - Argumente:
    - `--callgrind-out-file=filename`: Legt die Ausgabedatei fest.
    - `--dump-instr=yes`: Zeichnet Instruktionen auf.
    - `--cache-sim=yes`: Aktiviert Cache-Simulation.
    - `--cacheuse=yes`: Aktiviert Cache-Nutzungsanalyse.
    - `--simulate-hwpref=yes`: Simuliert Hardware-Prefetch.
    - `--branch-sim=yes`: Simuliert Branch-Prädiktion.
    - `--collect-jumps=yes`: Zeichnet Sprünge auf.

## Kontrolle bei der Ausführung

  - `callgrind_control`
  - Interaktives Tool zur Steuerung von Callgrind während der Programmausführung.
  - Optionen:
    - `--instr=on|off`: Instrumentierung ein- oder ausschalten.
    - `--zero`: Setzt die Zähler zurück.
    - `--back`: Zeigt dem Aufruf-Stack an.
    - ...

## Visualisierung der Ergebnisse

  - Console-Ausgabe
  - `callgrind_annotate`: Textbasiertes Tool zur Anzeige der Ergebnisse.
  - `kcachegrind`: GUI-Tool zur Visualisierung der Callgrind-Ausgabe.

---

# Leistungsmessung mit Callgrind

## Beispielaufruf

```sh
  ==20359== Callgrind, a call-graph generating cache profiler
  ==20359== Copyright (C) 2002-2017, and GNU GPL'd, by Josef Weidendorfer et al.
  ==20359== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
  ==20359== Command: ./examples/fibonacci/main_matrix 92
  ==20359==
  --20359-- warning: L3 cache found, using its data for the LL simulation.
  --20359-- warning: prefetch simulation can not be used with cache usage
  ==20359== For interactive control, run 'callgrind_control -h'.
  7540113804746346429
  ==20359==
  ==20359== Events    : Ir Dr Dw I1mr D1mr D1mw ILmr DLmr DLmw Bc Bcm Bi Bim AcCost1 SpLoss1 AcCost2 SpLoss2
  ==20359== Collected : 1900484 500436 175396 2040 13003 2612 1943 7130 1748 307331 13966 5207 1128 5318271 641178 1334619 244008
  ==20359==
  ==20359== I   refs:      1,900,484
  ==20359== I1  misses:        2,040
  ==20359== LLi misses:        1,943
  ==20359== I1  miss rate:      0.11%
  ==20359== LLi miss rate:      0.10%
  ==20359==
  ==20359== D   refs:        675,832  (500,436 rd + 175,396 wr)
  ==20359== D1  misses:       15,615  ( 13,003 rd +   2,612 wr)
  ==20359== LLd misses:        8,878  (  7,130 rd +   1,748 wr)
  ==20359== D1  miss rate:       2.3% (    2.6%   +     1.5%  )
  ==20359== LLd miss rate:       1.3% (    1.4%   +     1.0%  )
  ==20359==
  ==20359== LL refs:          17,655  ( 15,043 rd +   2,612 wr)
  ==20359== LL misses:        10,821  (  9,073 rd +   1,748 wr)
  ==20359== LL miss rate:        0.4% (    0.4%   +     1.0%  )
  ==20359==
  ==20359== Branches:        312,538  (307,331 cond +   5,207 ind)
  ==20359== Mispredicts:      15,094  ( 13,966 cond +   1,128 ind)
  ==20359== Mispred rate:        4.8% (    4.5%     +    21.7%   )
```

## Analyse der Callgrind-Ausgabe (Copilot)

| Abkürzung  | Wert     | Bedeutung                                                         |
|------------|----------|-------------------------------------------------------------------|
| Ir         | 1,900,484| Instruction reads (Anzahl ausgeführter Instruktionen)             |
| Dr         | 500,436  | Data reads (Anzahl gelesener Datenzugriffe)                       |
| Dw         | 175,396  | Data writes (Anzahl geschriebener Datenzugriffe)                  |
| I1mr       | 2,040    | Instruction L1 cache misses (Instruktions-Cache-Misses L1)        |
| D1mr       | 13,003   | Data L1 cache read misses (Daten-Lese-Cache-Misses L1)            |
| D1mw       | 2,612    | Data L1 cache write misses (Daten-Schreib-Cache-Misses L1)        |
| ILmr       | 1,943    | Instruction last-level cache misses (Instruktions-Cache-Misses LL)|
| DLmr       | 7,130    | Data last-level cache read misses (Daten-Lese-Cache-Misses LL)    |
| DLmw       | 1,748    | Data last-level cache write misses (Daten-Schreib-Cache-Misses LL)|
| Bc         | 307,331  | Conditional branches (Anzahl bedingter Sprungbefehle)             |
| Bcm        | 13,966   | Conditional branch mispredictions (Fehlvorhersagen bed. Sprünge)  |
| Bi         | 5,207    | Indirect branches (Anzahl indirekter Sprungbefehle)               |
| Bim        | 1,128    | Indirect branch mispredictions (Fehlvorhersagen ind. Sprünge)     |
| AcCost1    | 5,318,271| Access cost at cache level 1 (Zugriffskosten Cache-Level 1)       |
| SpLoss1    | 641,178  | Speculative loss at cache level 1 (Verlust spekulative Ausf. L1)  |
| AcCost2    | 1,334,619| Access cost at cache level 2 (Zugriffskosten Cache-Level 2)       |
| SpLoss2    | 244,008  | Speculative loss at cache level 2 (Verlust spekulative Ausf. L2)  |

- **Instruktionen und Datenzugriffe:**
  Ihr Programm hat ca. 1,9 Mio. Instruktionen ausgeführt und ca. 500 Tsd. Daten gelesen sowie 175 Tsd. Daten geschrieben.
- **Cache-Misses:**
  Die L1-Cache-Miss-Raten sind sehr niedrig (0.11% für Instruktionen, 2.3% für Daten). Das spricht für eine gute Cache-Lokalität.
  Die Last-Level-Cache-Miss-Raten sind noch niedriger (0.10% für Instruktionen, 1.3% für Daten).
- **Branches und Mispredictions:**
  Es gab ca. 312 Tsd. Sprungbefehle, davon ca. 15 Tsd. Fehlvorhersagen (Mispredicts). Die Fehlvorhersagerate ist mit 4.8% moderat.
- **Access Cost und Speculative Loss:**
  Diese Werte geben an, wie viel Zeit durch Speicherzugriffe und spekulative Ausführung verloren geht. Hohe Werte können auf Optimierungspotenzial hinweisen.

Das Programm zeigt eine effiziente Cache-Nutzung und eine moderate Anzahl an Sprung-Fehlvorhersagen. Die meisten Zugriffe werden erfolgreich aus dem Cache bedient, was für eine gute Performance spricht. Optimierungspotenzial besteht vor allem bei spekulativen Verlusten und Branch-Mispredictions, falls diese Werte in anderen Durchläufen deutlich höher ausfallen.

---

# Demonstration: Messung unterschiedlicher Fibonacci-Zahlen-Berechnungsalgorithmen

## Definition:

  - Fibonacci-Folge: 0, 1, 1, 2, 3, 5, 8, 13, ...
  - Formel: F(n) = F(n-1) + F(n-2) mit F(0) = 0, F(1) = 1.

## Algorithmen für Fibonacci-Zahlen

### Rekursiver Algorithmus:

```cpp
uint64_t fibonacci_recursive(uint8_t n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}
```

<details>
<summary>Arbeitsweise</summary>

  - Berechnet Fibonacci-Zahlen durch direkte Rekursion.
  - Jeder Aufruf teilt das Problem in zwei kleinere Teilprobleme auf.

</details>
<details>
<summary>Eigenschaften:</summary>

  - Zeitkomplexität: O(2^n) (Exponentiell, da viele Aufrufe redundant sind).
  - Platzkomplexität: O(n) (Aufgrund des Aufruf-Stacks).

</details>
<details>
<summary>Ausgabe</summary>

```sh
==5918== I   refs:      38,883,068
==5918== I1  misses:         2,182
==5918== LLi misses:             0
==5918== I1  miss rate:       0.01%
==5918== LLi miss rate:       0.00%
==5918==
==5918== D   refs:      15,500,942  (9,484,910 rd + 6,016,032 wr)
==5918== D1  misses:        22,870  (   15,622 rd +     7,248 wr)
==5918== LLd misses:           284  (      114 rd +       170 wr)
==5918== D1  miss rate:        0.1% (      0.2%   +       0.1%  )
==5918== LLd miss rate:        0.0% (      0.0%   +       0.0%  )
==5918==
==5918== LL refs:           25,052  (   17,804 rd +     7,248 wr)
==5918== LL misses:            284  (      114 rd +       170 wr)
==5918== LL miss rate:         0.0% (      0.0%   +       0.0%  )
==5918==
==5918== Branches:       5,101,980  (3,918,267 cond + 1,183,713 ind)
==5918== Mispredicts:      209,369  (  159,337 cond +    50,032 ind)
==5918== Mispred rate:         4.1% (      4.1%     +       4.2%   )
```
</details>

### Dynamische Programmierung:

```cpp
uint64_t fibonacci_dp(uint8_t n) {
    if (n <= 1) {
        return n;
    }
    std::vector<uint64_t> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;
    for (uint8_t i = 2; i <= n; ++i) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}
```

<details>
<summary>Arbeitsweise</summary>

  - Verwendet einen Vector, um bereits berechnete Fibonacci-Zahlen zu speichern.

</details>
<details>
<summary>Eigenschaften:</summary>

  - Zeitkomplexität: O(n) (Linear, da jede Zahl einmal berechnet wird).
  - Platzkomplexität: O(n) (Aufgrund des Vektors).

</details>
<details>
<summary>Ausgabe</summary>

```sh
==15709== I   refs:      7,787,562
==15709== I1  misses:           23
==15709== LLi misses:           22
==15709== I1  miss rate:      0.00%
==15709== LLi miss rate:      0.00%
==15709==
==15709== D   refs:      2,177,951  (  946,048 rd + 1,231,903 wr)
==15709== D1  misses:        3,852  (      463 rd +     3,389 wr)
==15709== LLd misses:          316  (        2 rd +       314 wr)
==15709== D1  miss rate:       0.2% (      0.0%   +       0.3%  )
==15709== LLd miss rate:       0.0% (      0.0%   +       0.0%  )
==15709==
==15709== LL refs:           3,875  (      486 rd +     3,389 wr)
==15709== LL misses:           338  (       24 rd +       314 wr)
==15709== LL miss rate:        0.0% (      0.0%   +       0.0%  )
==15709==
==15709== Branches:      1,173,006  (1,124,016 cond +    48,990 ind)
==15709== Mispredicts:      24,580  (   19,940 cond +     4,640 ind)
==15709== Mispred rate:        2.1% (      1.8%     +       9.5%   )
```
</details>

### Iterativer Ansatz I:

```cpp
uint64_t fibonacci_iterative_I(uint8_t n) {
    if (n <= 1) {
        return n;
    }
    uint64_t prev = 0;
    uint64_t curr = 1;
    for (uint8_t i = 2; i <= n; ++i) {
        auto const next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}
```

<details>
<summary>Arbeitsweise</summary>

  - Verwendet eine Schleife zur iterativen Berechnung.

</details>
<details>
<summary>Komplexität:</summary>

  - Zeitkomplexität: O(n) (Linear, da jede Zahl einmal berechnet wird).
  - Platzkomplexität: O(1)

</details>
<details>
<summary>Ausgabe</summary>

```sh
==15716== I   refs:      2,816,475
==15716== I1  misses:            1
==15716== LLi misses:            1
==15716== I1  miss rate:      0.00%
==15716== LLi miss rate:      0.00%
==15716==
==15716== D   refs:         10,000  ( 10,000 rd + 0 wr)
==15716== D1  misses:            0  (      0 rd + 0 wr)
==15716== LLd misses:            0  (      0 rd + 0 wr)
==15716== D1  miss rate:       0.0% (    0.0%   + 0.0%  )
==15716== LLd miss rate:       0.0% (    0.0%   + 0.0%  )
==15716==
==15716== LL refs:               1  (      1 rd + 0 wr)
==15716== LL misses:             1  (      1 rd + 0 wr)
==15716== LL miss rate:        0.0% (    0.0%   + 0.0%  )
==15716==
==15716== Branches:        464,533  (464,532 cond + 1 ind)
==15716== Mispredicts:      10,508  ( 10,508 cond + 0 ind)
==15716== Mispred rate:        2.3% (    2.3%     + 0.0%   )
```
</details>

### Iterativer Ansatz II:

```cpp
uint64_t fibonacci_iterative_II(uint8_t n) {
    if (n <= 1)
    {
        return n;
    }
    uint64_t prev = 0;
    uint64_t curr = 1;
    for (uint8_t i = 2; i <= n; ++i)
    {
        prev = std::exchange(curr, prev + curr);
    }
    return curr;
}
```

<details>
<summary>Arbeitsweise</summary>

  - Verwendet `std::exchange` für eine kompaktere Aktualisierung der Variablen.

</details>
<details>
<summary>Eigenschaften:</summary>

  - Zeitkomplexität: O(n) (Linear, da jede Zahl einmal berechnet wird).
  - Platzkomplexität: O(1)

</details>
<details>
<summary>Ausgabe</summary>

```sh
==15718== I   refs:      2,805,027
==15718== I1  misses:            1
==15718== LLi misses:            1
==15718== I1  miss rate:      0.00%
==15718== LLi miss rate:      0.00%
==15718==
==15718== D   refs:         10,000  ( 10,000 rd + 0 wr)
==15718== D1  misses:            0  (      0 rd + 0 wr)
==15718== LLd misses:            0  (      0 rd + 0 wr)
==15718== D1  miss rate:       0.0% (    0.0%   + 0.0%  )
==15718== LLd miss rate:       0.0% (    0.0%   + 0.0%  )
==15718==
==15718== LL refs:               1  (      1 rd + 0 wr)
==15718== LL misses:             1  (      1 rd + 0 wr)
==15718== LL miss rate:        0.0% (    0.0%   + 0.0%  )
==15718==
==15718== Branches:        462,597  (462,596 cond + 1 ind)
==15718== Mispredicts:       9,520  (  9,520 cond + 0 ind)
==15718== Mispred rate:        2.1% (    2.1%     + 0.0%   )
```
</details>

### Matrix-Exponentiation:

```cpp
using matrix_2x2 = std::array<std::array<uint64_t, 2>, 2>;

static matrix_2x2 multiply(matrix_2x2 const &a, matrix_2x2 const &b) {
    return {{
        {a[0][0] * b[0][0] + a[0][1] * b[1][0], a[0][0] * b[0][1] + a[0][1] * b[1][1]},
        {a[1][0] * b[0][0] + a[1][1] * b[1][0], a[1][0] * b[0][1] + a[1][1] * b[1][1]}
    }};
}

static matrix_2x2 matrix_pow(matrix_2x2 m, uint8_t n) {
    matrix_2x2 result = {{{1, 0}, {0, 1}}};
    while (n > 0)
    {
        if (n & 1)
        {
            result = multiply(result, m);
        }
        m = multiply(m, m);
        n >>= 1;
    }
    return result;
}

uint64_t fibonacci_matrix(uint8_t n) {
    if (n <= 1)
    {
        return n;
    }
    matrix_2x2 base = {{{1, 1}, {1, 0}}};
    auto res = matrix_pow(base, n - 1);
    return res[0][0];
}
```

<details>
<summary>Arbeitsweise</summary>

  - Die Fibonacci-Zahlen können durch Potenzieren der Matrix {{1,1},{1,0}} berechnet werden.
  - F(n) ist das Element `[0][0]` der Matrix {{1,1},{1,0}}^(n-1).

</details>
<details>
<summary>Eigenschaften:</summary>

  - Zeitkomplexität: O(log n) (Dank exponentieller Potenzierung).
  - Platzkomplexität: O(1)

</details>
<details>
<summary>Ausgabe</summary>

```sh
==15717== I   refs:      1,123,329
==15717== I1  misses:            3
==15717== LLi misses:            3
==15717== I1  miss rate:      0.00%
==15717== LLi miss rate:      0.00%
==15717==
==15717== D   refs:         10,000  (10,000 rd + 0 wr)
==15717== D1  misses:            0  (     0 rd + 0 wr)
==15717== LLd misses:            0  (     0 rd + 0 wr)
==15717== D1  miss rate:       0.0% (   0.0%   + 0.0%  )
==15717== LLd miss rate:       0.0% (   0.0%   + 0.0%  )
==15717==
==15717== LL refs:               3  (     3 rd + 0 wr)
==15717== LL misses:             3  (     3 rd + 0 wr)
==15717== LL miss rate:        0.0% (   0.0%   + 0.0%  )
==15717==
==15717== Branches:         96,659  (96,658 cond + 1 ind)
==15717== Mispredicts:      33,570  (33,570 cond + 0 ind)
==15717== Mispred rate:       34.7% (  34.7%     + 0.0%   )
```
</details>

### Binetsche Formel:

```cpp
uint64_t fibonacci_binet(uint8_t n) {
    static const double sqrt5 = std::sqrt(5.0);
    static const double phi = (1.0 + sqrt5) / 2.0;
    return static_cast<uint64_t>(std::round(std::pow(phi, n) / sqrt5));
}
```

<details>Arbeitsweise</details>

  - Basiert auf dem goldenen Schnitt φ = (1 + √5) / 2.
  - Nutzt die geschlossene Formel: F(n) = (φ^n - (1-φ)^n) / √5.
  - Führt für große n zu Rundungsfehlern, da (1-φ)^n gegen 0 geht.

</details>
<details>
<summary>Eigenschaften:</summary>

  - Zeitkomplexität: O(1)
  - Platzkomplexität: O(1)

</details>
<details>
<summary>Ausgabe</summary>

```sh
==15708== I   refs:      1,673,824
==15708== I1  misses:           24
==15708== LLi misses:           23
==15708== I1  miss rate:      0.00%
==15708== LLi miss rate:      0.00%
==15708==
==15708== D   refs:        438,042  (378,042 rd + 60,000 wr)
==15708== D1  misses:          776  (    776 rd +      0 wr)
==15708== LLd misses:           40  (     40 rd +      0 wr)
==15708== D1  miss rate:       0.2% (    0.2%   +    0.0%  )
==15708== LLd miss rate:       0.0% (    0.0%   +    0.0%  )
==15708==
==15708== LL refs:             800  (    800 rd +      0 wr)
==15708== LL misses:            63  (     63 rd +      0 wr)
==15708== LL miss rate:        0.0% (    0.0%   +    0.0%  )
==15708==
==15708== Branches:        138,299  (108,299 cond + 30,000 ind)
==15708== Mispredicts:       5,118  (  2,650 cond +  2,468 ind)
==15708== Mispred rate:        3.7% (    2.4%     +    8.2%   )
```
</details>

### Fast Doubling:

```cpp
static std::pair<uint64_t, uint64_t> fib_pair(uint8_t n) {
    if (n == 0)
    {
        return {0, 1};
    }
    auto p = fib_pair(n >> 1);
    uint64_t c = p.first * (2 * p.second - p.first);
    uint64_t d = p.first * p.first + p.second * p.second;
    if (n & 1)
    {
        return {d, c + d};
    }
    else
    {
        return {c, d};
    }
}

uint64_t fibonacci_fast_doubling(uint8_t n) {
    return fib_pair(n).first;
}
```

<details>
<summary>Arbeitsweise</summary>

  - Verwendet die mathematischen Identitäten:
    - F(2k) = F(k) × [2F(k+1) − F(k)]
    - F(2k+1) = F(k+1)^2 + F(k)^2
  - Berechnet F(2k) und F(2k+1) aus F(k) und F(k+1)
  - Reduziert die Anzahl der Berechnungen durch Halbierung von n.

</details>
<details>
<summary>Eigenschaften:</summary>

  - Zeitkomplexität: O(log n) (Dank Halbierung von n).
  - Platzkomplexität: O(1)

</details>
<details>
<summary>Ausgabe</summary>

```sh
==15710== I   refs:      1,327,047
==15710== I1  misses:            2
==15710== LLi misses:            2
==15710== I1  miss rate:      0.00%
==15710== LLi miss rate:      0.00%
==15710==
==15710== D   refs:        215,374  (112,687 rd + 102,687 wr)
==15710== D1  misses:            0  (      0 rd +       0 wr)
==15710== LLd misses:            0  (      0 rd +       0 wr)
==15710== D1  miss rate:       0.0% (    0.0%   +     0.0%  )
==15710== LLd miss rate:       0.0% (    0.0%   +     0.0%  )
==15710==
==15710== LL refs:               2  (      2 rd +       0 wr)
==15710== LL misses:             2  (      2 rd +       0 wr)
==15710== LL miss rate:        0.0% (    0.0%   +     0.0%  )
==15710==
==15710== Branches:        122,589  (122,588 cond +       1 ind)
==15710== Mispredicts:      29,149  ( 29,149 cond +       0 ind)
==15710== Mispred rate:       23.8% (   23.8%     +     0.0%   )
```
</details>

### Generator-basierter Ansatz (C++23):

```cpp
std::generator<uint64_t> fibonacci_generator() {
    uint64_t prev = 0;
    uint64_t curr = 1;
    co_yield prev;
    co_yield curr;
    while (true)
    {
        auto const next = prev + curr;
        co_yield next;
        prev = curr;
        curr = next;
    }
}

uint64_t fibonacci_generator(uint8_t n) {
    auto gen = fibonacci_generator();
    auto it = gen.begin();
    uint64_t value = 0;
    for (uint8_t i = 0; i <= n && it != gen.end(); ++i, ++it)
    {
        value = *it;
    }
    return value;
}
```

<details>
<summary>Arbeitsweise</summary>

  - Ähnlich dem iterativen Ansatz.
  - Definiert einen Generator, der unendlich viele Fibonacci-Zahlen erzeugt.
  - Verwendet `co_yield`, um Werte nacheinander zurückzugeben.

</details>
<details>
<summary>Eigenschaften:</summary>

  - Zeitkomplexität: O(n) (Linear, da jede Zahl einmal berechnet wird).
  - Platzkomplexität: O(1).

</details>
<details>
<summary>Ausgabe</summary>

```sh
==15713== I   refs:      7,260,400
==15713== I1  misses:            5
==15713== LLi misses:            5
==15713== I1  miss rate:      0.00%
==15713== LLi miss rate:      0.00%
==15713==
==15713== D   refs:      4,051,900  (3,310,200 rd + 741,700 wr)
==15713== D1  misses:            0  (        0 rd +       0 wr)
==15713== LLd misses:            0  (        0 rd +       0 wr)
==15713== D1  miss rate:       0.0% (      0.0%   +     0.0%  )
==15713== LLd miss rate:       0.0% (      0.0%   +     0.0%  )
==15713==
==15713== LL refs:               5  (        5 rd +       0 wr)
==15713== LL misses:             5  (        5 rd +       0 wr)
==15713== LL miss rate:        0.0% (      0.0%   +     0.0%  )
==15713==
==15713== Branches:      2,146,800  (1,615,100 cond + 531,700 ind)
==15713== Mispredicts:      10,174  (   10,121 cond +      53 ind)
==15713== Mispred rate:        0.5% (      0.6%     +     0.0%   )
```
</details>

## Vergleich der Profiling-Ergebnisse

### Instruktionen

| Algorithmus           | Instruktionen (Ir) | Visualisierung           |
|---------------------- |------------------- |--------------------------|
| Dynamische Programm.  | 7,787,562          | ██████████████████████   |
| Generator             | 7,260,400          | ████████████████████     |
| Iterativ I            | 2,816,475          | █████                    |
| Iterativ II           | 2,805,027          | █████                    |
| Binet                 | 1,673,824          | ███                      |
| Fast Doubling         | 1,327,047          | ██                       |
| Matrix                | 1,123,329          | ██                       |

### Datenzugriffe

| Algorithmus           | D refs     | Visualisierung           |
|---------------------- |-----------|---------------------------|
| Dynamische Programm.  | 2,177,951 | ████████████              |
| Generator             | 4,051,900 | █████████████████████████ |
| Iterativ I            | 10,000    |                           |
| Iterativ II           | 10,000    |                           |
| Binet                 | 438,042   | ██                        |
| Fast Doubling         | 215,374   | █                         |
| Matrix                | 10,000    |                           |

### Branches

| Algorithmus           | Branches  | Visualisierung(Branches) | Mispredicts | Mispredict rate (%) | Visualisierung (Mispredicts/Branches)  |
|---------------------- |-----------|--------------------------|-------------|---------------------|----------------------------------------|
| Dynamische Programm.  | 1,173,006 | ███████████              | 24,580      | 2.10                | █                                      |
| Generator             | 2,146,800 | ████████████████████████ | 10,174      | 0.47                |                                        |
| Iterativ I            | 464,533   | ███                      | 10,508      | 2.26                | █                                      |
| Iterativ II           | 462,597   | ███                      | 9,520       | 2.06                | █                                      |
| Binet                 | 138,299   | ██                       | 5,118       | 3.70                | ██                                     |
| Fast Doubling         | 122,589   | ██                       | 29,149      | 23.80               | ██████████████                         |
| Matrix                | 96,659    | █                        | 33,570      | 34.74               | ██████████████████                     |
