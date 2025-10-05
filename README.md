Козинец Дмитрий ИУ9-51

# Анализ системы переписывания строк

## Система правил

Система переписывания строк $R$ определяется следующим набором правил:

$$
T = \left\\{ 
\begin{array}{ll}
abca & \rightarrow aaaa,\\\\
bcab & \rightarrow bbbb,\\\\
cabc & \rightarrow cccc,\\\\
abc  & \rightarrow aaa,\\\\
abc  & \rightarrow bbb,\\\\
abc  & \rightarrow ccc,\\\\
aabbcc & \rightarrow abcabc
\end{array}
\right\\}
$$

## 1) Завершимость

$f_1$: количество разных букв, стоящих рядом (здесь "рядом" - это в строке с длиной, равной длине правила, потому что длина строки нигде не меняется.

$f_2$: сумма позиций с

$f_3$: сумма позиций b

Итоговый порядок: $2^{\text{len}(w)} \cdot f_1 + f_2 + \left(\frac{1}{2}\right)^{f_3}$

Выбранный порядок гарантирует убывание правой части относительно левой, следовательно, система завершима

## 2) Классы эквивалентности

Любая строка после переписываний преобразуется к виду $x^{k_1} \dots y^{k_n} \dots$

Здесь на месте букв $x, y = \{a, b, c\}$ - любая из букв

Правила не меняют длины строк, поэтому имеем бесконечное число классов эквивалентности

## 3) Локальная конфлюэнтность

Поскольку имеем:
- $abc \rightarrow aaa$,
- $abc \rightarrow bbb$, 
- $abc \rightarrow ccc$,

то уже видим, что локальная конфлюэнтность не выполняется, поскольку терм $abc$ переписывается в 3 разных нормальных формы

## 4) Пополняемость по Кнуту-Бендиксу

Заметим, что правила:
- $abca \rightarrow aaaa$,
- $cabc \rightarrow cccc$,

излишни, так как покрываются другими правилами, значит их можно вычеркнуть

Далее:
- $abc \rightarrow bbb$,
- $abc \rightarrow ccc$,

можно также вычеркнуть и добавить правила согласно выбранному порядку:
- $bbb \rightarrow aaa$,
- $ccc \rightarrow aaa$,

Вообще говоря, в конечном итоге система получится очень большой (много правил, и длина правил возрастает с каждым добавлением), и непонятно, будет ли вообще алгоритм К-Б конечным, потому что на добавлении 20-го правила длиной в 10 букв я устал делать дальше. Поэтому достроим лишь несколько правил, чтобы система была удобной для применения.

Имеем систему:
1. $bcab \rightarrow bbbb$
2. $abc \rightarrow aaa$
3. $aabbcc \rightarrow abcabc$
4. $bbb \rightarrow aaa$
5. $ccc \rightarrow aaa$

Начнём рассматривать критические пары

1. $bbbb$ и $cccc$ дают новые два правила согласно порядку:
   - $aaab \rightarrow baaa$
   - $aaac \rightarrow caaa$
   
   тогда сразу $bcab \rightarrow baaa$
   
   и видно, что $aabbcc \rightarrow abcabc \rightarrow aaaaaa$ - по всем вариантам переписывания

2. $aaabc \rightarrow baaac \rightarrow bcaaa$ (по предыдущему пункту)
   
   $aaabc \rightarrow aaaaa$ (по правилу $abc \rightarrow aaa$)
   
   Добавляем $bcaaa \rightarrow aaaaa$

3. $bbbcab \rightarrow aaacab \rightarrow caaaab \rightarrow cabaaa$
   
   $bbbcab \rightarrow bbbaaa \rightarrow aaaaaa$
   
   Добавляем $cabaaa \rightarrow aaaaaa$

4. $abccc \rightarrow aaacc \rightarrow ccaaa$

   $abccc \rightarrow abaaa$

   Добавляем $ccaaa$ \rightarrow abaaa$

Можно продолжать этот процесс дальше, но правила будут некрасивыми и система будет только возрастать.

Конечная система T' имеет вид:

1. $bcab \rightarrow bbbb$
2. $abc \rightarrow aaa$
3. $aabbcc \rightarrow abcabc$
4. $bbb \rightarrow aaa$
5. $ccc \rightarrow aaa$
6. $aaab \rightarrow baaa$
7. $aaac \rightarrow caaa$
8. $ccaaa$ \rightarrow abaaa$
9. $cabaaa \rightarrow aaaaaa$
