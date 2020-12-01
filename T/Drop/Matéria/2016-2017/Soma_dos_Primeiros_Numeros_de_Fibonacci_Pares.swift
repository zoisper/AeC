//: Playground - noun: a place where people can play

import Cocoa


var c1=0, c2=0, c3=0;





func Fib(x :Int) -> Int {
    if (x==1) { return 1; }
    if (x==2) { return 2; }
    return Fib(x: x-1) + Fib(x: x-2);
}

// print(Fib(x: 30))
// Impraticável!!!












// O cálculo do x-ésimo número de Fibonacci em tempo linear (em x) 
// é bem conhecido.

func Fiblin(x :Int) -> Int {
    var a, b :Int
    a = 1
    b = 2
    if (x==1) { return a; }
    if (x==2) { return b; }
    for _ in (3...x) {
        (a,b) = (b,a+b);
        c1+=1
    }
    return b
}

//print(Fiblin(x: 50))









// uma primeira ideia é então usar a função anterior para 
// gerar a sequência

func sumFib_a(n :Int) -> Int {
    var f, k, sum :Int
    k = 1;
    f = 1;
    sum = 0;
    while (f<=n) {
        if (f%2 == 0) { sum += f }
        k += 1;
        f = Fiblin(x: k)
    }
    return sum
}

print(sumFib_a(n : 4000000000))
print(c1)










// o método anterior é muito ineficiente porque 
// para cada valor de k repete o cálculo
// dos k-i primeiros números, já calculados previamente.
// É fácil fazer melhor. 



func sumFib_b(n :Int) -> Int {
    var prev, f, sum :Int
    prev = 0
    f = 1
    sum = 0
    while (f <= n) {
        if (f%2 == 0) { sum += f }
        (prev,f) = (f,prev+f)
        c2 += 1
    }
    return sum
}

print(sumFib_b(n : 4000000000))
print(c2)


















// Uma última solução exige uma observação não-evidente:
// A sequência de números de Fibonacci pares:
// 2, 8, 34, 144, ...
// pode ser descrita também ela directamente por uma função recursiva:
// Fibpar(k) = 4*Fibpar(k-1) + Fibpar(k-2)
// Isto permite optimizar o cálculo, eliminando a necessidade de 
// percorrer todos os números testando se são pares.



func sumFib_c(n :Int) -> Int {
    var prev, k, sum :Int
    prev = 0
    k = 2
    sum = 0
    while (k <= n) {
        sum += k
        (prev,k) = (k,prev+4*k)
        c3 += 1
    }
    return sum
}

print(sumFib_c(n : 4000000000))
print(c3)



