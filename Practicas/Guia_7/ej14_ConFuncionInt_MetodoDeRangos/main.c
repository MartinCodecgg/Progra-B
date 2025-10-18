#include <stdio.h>
#include <stdlib.h>

int esABBVerInt(arbol a, int min, int max) {
    if (a) {
        if (a->dato > min && a->dato < max)
            return esABBVerInt(a->izq, min, a->dato) &&
                   esABBVerInt(a->der, a->dato, max);
        else
            return 0;
    }
    else
        return 1;
}

int main()
{
    printf("Hello world!\n");
    return 0;
}

// EXPLICACION

/*

## 🎯 Idea central: La propiedad de ABB

**Un Árbol Binario de Búsqueda (ABB) tiene esta propiedad:**

Para cada nodo:
- **Todos** los nodos del subárbol izquierdo deben ser **menores** que él
- **Todos** los nodos del subárbol derecho deben ser **mayores** que él

**El truco:** En lugar de comparar con el padre inmediato, mantenemos un **rango válido** `(min, max)` que nos dice qué valores puede tener cada nodo.

---

## 📊 Explicación visual con ejemplo:
```
       50
      /  \
    30    70
   / \    / \
  20 40  60 80
Paso 1: Empezamos en la raíz
cesABBVerInt(50, -∞, +∞)

Nodo actual: 50
Rango permitido: (-∞, +∞) → puede ser cualquier valor
Pregunta: ¿50 está entre -∞ y +∞? SÍ ✓

Paso 2: Vamos al hijo izquierdo (30)
Cuando llamamos recursivamente al hijo izquierdo:
cesABBVerInt(a->izq, min, a->dato)
            ↓       ↓    ↓
esABBVerInt(30,    -∞,   50)
¿Por qué pasamos 50 como max?
Porque 30 está en el subárbol izquierdo de 50, entonces debe ser menor que 50.

Nodo actual: 30
Rango permitido: (-∞, 50) → debe ser menor que 50
Pregunta: ¿30 > -∞ Y 30 < 50? SÍ ✓

Paso 3: Vamos al hijo derecho del nodo 50 (70)
cesABBVerInt(a->der, a->dato, max)
            ↓       ↓       ↓
esABBVerInt(70,     50,    +∞)
```

**¿Por qué pasamos 50 como min?**
Porque 70 está en el subárbol derecho de 50, entonces **debe ser mayor que 50**.

- **Nodo actual:** 70
- **Rango permitido:** `(50, +∞)` → debe ser mayor que 50
- **Pregunta:** ¿70 > 50 Y 70 < +∞? **SÍ ✓**

---

## 🔍 Ejemplo con ERROR:
```
       20
      /  \
    10    30
   / \
  5  25  ← ¡ERROR! 25 > 20
```

### Traza del error:
```
esABBVerInt(20, -∞, +∞) → 20 está OK ✓
│
├─ esABBVerInt(10, -∞, 20) → 10 < 20 ✓
   │
   ├─ esABBVerInt(5, -∞, 10) → 5 < 10 ✓
   │
   └─ esABBVerInt(25, 10, 20)  ← ¡AQUÍ!
      │
      │ Verifica: 25 > 10 && 25 < 20?
      │           ✓ SÍ      ✗ NO (25 no es < 20)
      │
      └─ return 0; ❌
¿Por qué falla?

El nodo 25 está en el subárbol izquierdo de 20
Por ser hijo derecho de 10, debe estar en el rango (10, 20)
Pero 25 > 20, entonces viola el rango ❌
*/
