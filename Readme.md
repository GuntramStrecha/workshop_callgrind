# Callgrind: Profiling und Leistungsanalyse

---

<h2>Einführung in Callgrind</h2>

- **Was ist Callgrind?**
  - Ein Profiling-Tool für Programme, Teil der Valgrind-Suite.
  - Konzentriert sich auf Cache-Nutzung und Branch-Prädiktion.
  - Hilft Leistungsengpässe zu identifizieren.

- **Warum Callgrind verwenden?**
  - Erkenntnisse über die Codeausführung gewinnen.
  - Algorithmen optimieren und Leistung verbessern.

<h2>Benutzung von Callgrind</h2>

- **Funktionsweise:**
  - Führt das Programm in einer virtuellen Umgebung aus.
  - Zeichnet detaillierte Informationen über Funktionsaufrufe und Speicherzugriffe auf.

- **Compilierung:**
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

- **Aufruf:**
  - `valgrind --tool=callgrind [Argumente] ./programm [Programm-Argumente]`
  - Argumente:
    - `--callgrind-out-file=filename`: Legt die Ausgabedatei fest.
    - `--dump-instr=yes`: Zeichnet Instruktionen auf.
    - `--cache-sim=yes`: Aktiviert Cache-Simulation.
    - `--cacheuse=yes`: Aktiviert Cache-Nutzungsanalyse.
    - `--simulate-hwpref=yes`: Simuliert Hardware-Prefetch.
    - `--branch-sim=yes`: Simuliert Branch-Prädiktion.
    - `--collect-jumps=yes`: Zeichnet Sprünge auf.

---

<h2>Leistungsmessung mit Callgrind</h2>

<h3>Beispielaufruf</h3>

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

**Analyse der Callgrind-Ausgabe:** (Copilot)

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

<h2>Demonstration: Messung unterschiedlicher Fibonacci-Zahlen-Berechnungsalgorithmen</h2>

<h3>Definition:</h3>
  - Fibonacci-Folge: 0, 1, 1, 2, 3, 5, 8, 13, ...
  - Formel: F(n) = F(n-1) + F(n-2) mit F(0) = 0, F(1) = 1.

<h3>Algorithmen für Fibonacci-Zahlen</h3>

<h4>Rekursiver Algorithmus:</h4>

```cpp
#include "fibonacci/fibonacci_recursive.hpp"

uint64_t fibonacci_recursive(uint8_t n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}
```

<details>
<summary>Eigenschaften:</summary>

  - Einfach und elegant, aber ineffizient für große n.
  - Zeitkomplexität: O(2^n), Platzkomplexität: O(n) durch den Aufruf-Stack.

</details>

<h4>Dynamische Programmierung:</h4>

```cpp
#include "fibonacci/fibonacci_dp.hpp"
#include <vector>

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
<summary>Eigenschaften:</summary>

  - Verwendet ein Array, um zuvor berechnete Werte zu speichern.
  - Zeitkomplexität: O(n), Platzkomplexität: O(n).

</details>

<h4>Iterativer Ansatz I:</h4>

```cpp
#include "fibonacci/fibonacci_iterative_I.hpp"

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
<summary>Eigenschaften:</summary>

  - Verwendet eine Schleife zur iterativen Berechnung.
  - Benötigt konstanten Speicher.
  - Zeitkomplexität: O(n), Platzkomplexität: O(1).

</details>

<h4>Iterativer Ansatz II:</h4>

```cpp
#include "fibonacci/fibonacci_iterative_II.hpp"
#include <utility>

uint64_t fibonacci_iterative_II(uint8_t n) {
    if (n <= 1) {
        return n;
    }
    uint64_t prev = 0;
    uint64_t curr = 1;
    for (uint8_t i = 2; i <= n; ++i) {
        prev = std::exchange(curr, prev + curr);
    }
    return curr;
}
```

<details>
<summary>Eigenschaften:</summary>

  - Ähnlich wie iterativ, aber verwendet `std::exchange` für Klarheit.
  - Zeitkomplexität: O(n), Platzkomplexität: O(1).

</details>

<h4>Matrix-Exponentiation:</h4>

```cpp
#include "fibonacci/fibonacci_matrix.hpp"
#include <array>

using matrix_2x2 = std::array<std::array<uint64_t, 2>, 2>;

static matrix_2x2 multiply(matrix_2x2 const &a, matrix_2x2 const &b) {
    return {{
        {a[0][0] * b[0][0] + a[0][1] * b[1][0], a[0][0] * b[0][1] + a[0][1] * b[1][1]},
        {a[1][0] * b[0][0] + a[1][1] * b[1][0], a[1][0] * b[0][1] + a[1][1] * b[1][1]}
    }};
}

static matrix_2x2 matrix_pow(matrix_2x2 m, uint8_t n) {
    matrix_2x2 result = {{{1, 0}, {0, 1}}};
    while (n > 0) {
        if (n & 1) {
            result = multiply(result, m);
        }
        m = multiply(m, m);
        n >>= 1;
    }
    return result;
}

uint64_t fibonacci_matrix(uint8_t n) {
    if (n <= 1) {
        return n;
    }
    matrix_2x2 base = {{{1, 1}, {1, 0}}};
    auto res = matrix_pow(base, n - 1);
    return res[0][0];
}
```

<details>
<summary>Eigenschaften:</summary>

  - Verwendet Matrix-Exponentiation zur Berechnung in logarithmischer Zeit.
  - Zeitkomplexität: O(log n), Platzkomplexität: O(1).

</details>

<h4>Binetsche Formel:</h4>

```cpp
#include "fibonacci/fibonacci_binet.hpp"
#include <cmath>

uint64_t fibonacci_binet(uint8_t n) {
    static const double sqrt5 = std::sqrt(5.0);
    static const double phi = (1.0 + sqrt5) / 2.0;
    return static_cast<uint64_t>(std::round(std::pow(phi, n) / sqrt5));
}
```

<details>
<summary>Eigenschaften:</summary>

  - Verwendet die geschlossene Formel mit dem goldenen Schnitt.
  - Zeitkomplexität: O(1), kann aber bei großen n zu Genauigkeitsproblemen führen.

</details>

<h4>Fast Doubling:</h4>

```cpp
#include "fibonacci/fibonacci_fast_doubling.hpp"
#include <utility>

static std::pair<uint64_t, uint64_t> fib_pair(uint8_t n) {
    if (n == 0) {
        return {0, 1};
    }
    auto p = fib_pair(n >> 1);
    uint64_t c = p.first * (2 * p.second - p.first);
    uint64_t d = p.first * p.first + p.second * p.second;
    if (n & 1) {
        return {d, c + d};
    } else {
        return {c, d};
    }
}

uint64_t fibonacci_fast_doubling(uint8_t n) {
    return fib_pair(n).first;
}
```

<details>
<summary>Eigenschaften:</summary>

  - Nutzt Eigenschaften der Fibonacci-Zahlen zur Berechnung in logarithmischer Zeit.
  - Zeitkomplexität: O(log n), Platzkomplexität: O(1).
  - <b>Funktionsweise:</b> Fast Doubling verwendet die mathematischen Identitäten:
    - F(2k) = F(k) × [2F(k+1) − F(k)]
    - F(2k+1) = F(k+1)^2 + F(k)^2
    Dadurch kann der Algorithmus F(n) durch rekursives Halbieren von n effizient berechnen und vermeidet redundante Berechnungen.

</details>

<h4>Generator-basierter Ansatz (C++23):</h4>

```cpp
#include "fibonacci/fibonacci_generator.hpp"
#include <cstdint>
#include <generator>

std::generator<uint64_t> fibonacci_generator() {
    uint64_t prev = 0;
    uint64_t curr = 1;
    co_yield prev;
    co_yield curr;
    while (true) {
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
    for (uint8_t i = 0; i <= n && it != gen.end(); ++i, ++it) {
        value = *it;
    }
    return value;
}
```

<details>
<summary>Eigenschaften:</summary>

  - Verwendet C++23-Generatoren für Lazy Evaluation.
  - Effizient für das Streaming von Fibonacci-Zahlen.
  - Zeitkomplexität: O(n), Platzkomplexität: O(1).

</details>
